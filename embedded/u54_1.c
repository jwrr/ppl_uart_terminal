/*******************************************************************************
 * Copyright 2019-2021 Microchip FPGA Embedded Systems Solutions.
 *
 * SPDX-License-Identifier: MIT
 *
 * Application code running on U54_1
 *
 * Example project demonstrating the use of polled and interrupt driven
 * transmission and reception over MMUART. Please refer README.md in the root
 * folder of this example project
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "mpfs_hal/mss_hal.h"
#include "drivers/mss/mss_mmuart/mss_uart.h"
#include "inc/common.h"

#define PRINT(S) string_init(&g_tmp_str, S); MSS_UART_polled_tx(&g_mss_uart1_lo, g_tmp_str.txt, g_tmp_str.len);


uint64_t * const fabric_base_addr = (uint64_t *)0x61000000U;


/******************************************************************************
 * Instruction message. This message will be transmitted over the UART when
 * the program starts.
 *****************************************************************************/

const uint8_t g_message1[] = "POLARFIRE SOC MSS MMUART PPL REPL\r\n\r\n";

const uint8_t g_message2[] =
        "This program is run from u54_1\r\n\
        \r\n\
Type 0  Show hart 1 debug message\r\n\
Type 1  Show this menu\r\n\
Type 2  Send message using polled method\r\n\
Type 3  send message using interrupt method\r\n\
";

const uint8_t polled_message[] =
        "This message has been transmitted using polled method. \r\n";

const uint8_t intr_message[] =
        " This message has been transmitted using interrupt method. \r\n";


#define RX_BUFF_SIZE    64U
uint8_t g_rx_buff[RX_BUFF_SIZE] = { 0 };
volatile uint32_t count_sw_ints_h1 = 0U;
volatile uint8_t g_rx_size = 0U;
static volatile uint32_t irq_cnt = 0;

#define LINE_SIZE 128U
typedef struct {
    size_t size;
    size_t len;
    size_t cur;
    uint8_t txt[LINE_SIZE];
} string_t;

string_t g_line;
#define NUM_LINE_PARTS 5
string_t g_line_parts[NUM_LINE_PARTS];
string_t g_tmp_str;
string_t g_msg;

bool g_line_ready = false;
bool g_echo = true;

//#define INFOLEN 138U
//uint8_t g_print_line[INFOLEN];

void string_init(string_t *str, uint8_t ch_array[])
{
    str->size = sizeof(str->txt) - 1; // minus 1 accounts for null terminator
    str->len = 0U; // len is <= size < sizeof(txt)
    str->cur = 0U;
    for (int i=0; i < str->size; i++) {
        str->txt[i] = 0U;
    }
    int i = 0;
    for (i=0; i < str->size; i++) {
        if (ch_array[i] == 0U) break;
        str->txt[i] = ch_array[i];
    }
    str->len = i;
}


bool string_copy(string_t *dest, const string_t *src)
{
    string_init(dest, "");
    dest->len = (src->len <= dest->size) ? src->len : dest->size;
    int i = 0;
    for (; i <= dest->len; i++) {
        dest->txt[i] = src->txt[i];
    }
    dest->txt[i] = 0U;
    bool success = dest->len == src->len;
    return success;
}


size_t string_append(string_t *str, const uint8_t ch_array[], size_t n)
{
    if (str->len + n > str->size) {
        return 0;
    }
    for (int i=0; i<n; i++) {
        if (ch_array[i] == 0U) break;
        str->txt[str->len++] = ch_array[i];
    }
    str->cur = str->len;
    str->txt[str->len] = 0U;
    return n;
}


size_t string_append2(string_t *str, const uint8_t s1[], const uint8_t s2[])
{
    size_t orig1_len = str->len;
    size_t s1_len = strlen(s1);
    if (s1_len) {
        string_append(str, s1, s1_len);
        size_t new_len = str->len;
        if (new_len == orig1_len) return 0;
    }
    size_t orig2_len = str->len;
    size_t s2_len = strlen(s2);
    if (s2_len) {
        string_append(str, s2, s2_len);
        size_t new_len = str->len;
        if (new_len == orig2_len) return 0;
    }
    return str->len - orig1_len;
}


size_t string_append4(string_t *str, const uint8_t s1[], const uint8_t s2[], const uint8_t s3[], const uint8_t s4[])
{
    size_t num_added = string_append2(str, s1, s2);
    if (num_added == 0) return 0;
    num_added += string_append2(str, s3, s4);
    return num_added;
}


size_t string_init2(string_t *str, const uint8_t s1[], const uint8_t s2[])
{
    string_init(str, "");
    string_append2(str, s1, s2);
    return str->len;
}


size_t string_init4(string_t *str, const uint8_t s1[], const uint8_t s2[], const uint8_t s3[], const uint8_t s4[])
{
    string_init(str, "");
    string_append4(str, s1, s2, s3, s4);
    return str->len;
}


void string_rtrim(string_t *s)
{
    while (isspace(s->txt[s->len-1])) {
        s->len--;
        s->txt[s->len] = 0U;
    }
    s->cur = 0;
}


bool string_skip_spaces(string_t *str)
{
    while ((str->cur < str->len) && isspace(str->txt[str->cur])) {
        str->cur++;
    }
    return str->cur < str->len; // return true if line has more txt
}


size_t string_get_word(string_t *str, string_t *word)
{
    string_init(word, "");
    string_skip_spaces(str);
    while ((str->cur < str->len) && !isspace(str->txt[str->cur])) {
        string_append(word, &(str->txt[str->cur]), 1);
        str->cur++;
    }
    return word->len; // return true if word is not empty
}


void string_get_words(string_t *cmd_line, string_t parts[]) {
    string_rtrim(cmd_line);
    for (int i=0; i<NUM_LINE_PARTS; i++) {
        string_get_word(cmd_line, &parts[i]);
    }
}


size_t string_get_to_eoln(string_t *str, string_t *word)
{
    string_init(word, "");
    string_skip_spaces(str);
    while (str->cur < str->len) {
        string_append(word, &(str->txt[str->cur]), 1);
        str->cur++;
    }
    return word->len; // return true if word is not empty
}


bool string_in_list(const string_t *s, const uint8_t list[])
{
    if (s->len == 0) return false;
    return (NULL != strstr(list, s->txt));
}


void string_swap(string_t *s1, string_t *s2)
{
    size_t len = (s1->len > s2->len) ? s1->len : s2->len;
    uint8_t ch1;
    size_t tmp;

    tmp = s1->size;
    s1->size = s2->size;
    s2->size = tmp;

    tmp = s1->len;
    s1->len = s2->len;
    s2->len = tmp;

    s1->cur = 0U;
    s2->cur = 0U;

    for (int i=0; i<=len; i++) {
        ch1 = s1->txt[i];
        s1->txt[i] = s2->txt[i];
        s2->txt[i] = ch1;
    }
    return;
}


void string_print(string_t *str)
{
    if (str == NULL || str->len == 0) return;
    MSS_UART_polled_tx(&g_mss_uart1_lo, str->txt, str->len);
}


char * int_to_hex(uint32_t val, char str[])
{
    uint32_t mask = 0xf;
    uint8_t ch = 0U;
    uint8_t hexdigit = 0U;
    str[8] = 0U;
    for (int i=0; i<8; i++) {
        hexdigit = val & mask;
        uint8_t hexchar = (hexdigit < 10) ? '0' + hexdigit : 'A' + hexdigit - 10;
        str[7-i] = hexchar;
        val = val >> 4;
    }
    return str;
}


// =====================================================================
// PeekPokeLang (PPL)
// =====================================================================

/**
1 = (set) result = a op b
2 peek addr value
3 poke addr value

4 if a op b
5 elif a op b
6 else
7 end [if, while]
8 while



addr = 0x8000_0000
loop_cnt = 0
while loop_cnt < 1000
    peek addr value
    if i < 10
        va1ue = value + 1
    elif i < 100
        value = value + 10
    else
        value = value + 100
    end
    poke addr value
    addr = addr + 4
    loop_cnt = loop_cnt + 1
end while


addr = 0x8000_0000
loop_cnt = 0
while wtag1 loop_cnt < 1000
    peek addr value
    if iftag1 i < 10
        va1ue = value + 10
    else iftag1
        if iftag2 i < 100
            value = value + 100
        else iftag2
            if iftag3 i < 1000
                value = value + 1000
            else iftag3
                value = value + 10000
            end iftag3
         end iftag2
    end iftag1
    poke addr value
    addr = addr + 4
    loop_cnt = loop_cnt + 1
end wtag1


addr = 0x8000_0000
loop_cnt = 0
while wtag1 loop_cnt < 1000

    peek addr value
    if iftag1 i < 10
        va1ue = value + 10
    else iftag1
    if iftag2 i < 100
        value = value + 100
    else iftag2
    if iftag3 i < 1000
        value = value + 1000
    else iftag3
        value = value + 10000
    end iftag3
    end iftag2
    end iftag1
    poke addr value
    addr = addr + 4
    loop_cnt = loop_cnt + 1
end wtag1



// = (set) : 1, a, op, b, v
// peek    : 2, a,  -, -, v
// poke    : 3, a,  -, -, v
// while   : 4, a, op, b, L
// if      : 5, a, op, b, L
// else    : 6, -,  -, -, L
// end     : 6, -,  -, -, -
**/

#define NUM_INSTRUCTIONS 128
#define NUM_VARIABLES     64
#define NUM_TAGS          64
#define NAME_SIZE         12
typedef struct {
    uint32_t data1;
    uint32_t data2;
    uint8_t  opcode; // {cmd[7:4], op[3:0]}
    uint8_t  result_tag_addr;
    bool     data1_is_number;
    bool     data2_is_number;
} instr_t;

typedef struct {
    uint32_t val;
    uint8_t  name[NAME_SIZE];
} data_t;

typedef struct {
    uint32_t inst_i;
    uint8_t  tag_name[NAME_SIZE];
} tag_t;

typedef struct {
    uint8_t inst_i;
    uint8_t inst_len;
    uint8_t data_len;
    uint8_t tag_len;
    uint8_t unused_tag_i;
    instr_t inst_mem[NUM_INSTRUCTIONS];
    data_t  data_mem[NUM_VARIABLES];
    tag_t   tag_table[NUM_TAGS];
} ppl_t;

ppl_t   g_ppl_vm;


void ppl_reset(ppl_t *ppl_vm)
{
    ppl_vm->inst_i = 0;
    ppl_vm->inst_len = 0;
    ppl_vm->data_len = 0;
    ppl_vm->tag_len = 0;
}


uint32_t ppl_get_data_mem_offset(ppl_t *ppl_vm, string_t *name, bool *is_number)
{
    *is_number = name->len > 0U && isdigit(name->txt[0]);
    uint32_t number = 0U;
    if (*is_number) {
        if ((name->len > 2) && (name->txt[0] == '0') && (name->txt[1] == 'x')) {
            for (int i = 2; i <  name->len; i++) {
                *is_number = isxdigit(name->txt[i]);
                if (!(*is_number)) break;
            }
            if (*is_number) {
                uint32_t number = (uint32_t)strtol(name->txt, NULL, 16);
                return number;
            }
        } else {
            for (int i = 0; i <  name->len; i++) {
                *is_number = isdigit(name->txt[i]);
                if (!(*is_number)) break;
            }
            if (*is_number) {
                uint32_t number = (uint32_t)strtol(name->txt, NULL, 10);
                return number;
            }
        }
    }

    int i = 1;
    for (; i < ppl_vm->data_len; i++) {
        if (string_in_list(name, ppl_vm->data_mem[i].name)) {
            break;
        }
    }
    if (i >= ppl_vm->data_len) i = 0;
    return i;
}


uint8_t ppl_get_tag_index(ppl_t *ppl_vm, string_t *tag_name)
{
    int i = 1;
    for (; i < ppl_vm->tag_len; i++) {
        if (string_in_list(tag_name, ppl_vm->tag_table[i].tag_name)) {
            break;
        }
        if (ppl_vm->tag_table[i].inst_i == 0U) {
            ppl_vm->unused_tag_i = i;
        }
    }
    if (i >= ppl_vm->tag_len) i = 0;
    return i;
}

uint8_t ppl_append_data(ppl_t *ppl_vm, string_t *data_name)
{
    if (data_name->len == 0) return 0;
    if (ppl_vm->data_len == 0) {
        ppl_vm->data_len++; // keep entry 0 empty
    }
    uint8_t ii = ppl_vm->data_len;
    ppl_vm->data_mem[ii].val = 0U;
    strncpy(ppl_vm->data_mem[ii].name, data_name->txt, NAME_SIZE-1);
    ppl_vm->data_mem[ii].name[NAME_SIZE-1] = 0U;
    ppl_vm->data_len++;
    return ii;
}

void ppl_compute_data(ppl_t *ppl_vm, uint8_t result, uint8_t data1, uint8_t operation, uint8_t data2)
{
    return;
}

void ppl_add_tag(ppl_t *ppl_vm, string_t *tag_name)
{
    uint8_t ii = ppl_vm->tag_len;
    if (ppl_vm->unused_tag_i > 0 && ppl_vm->unused_tag_i < ppl_vm->tag_len) {
        ii =  ppl_vm->unused_tag_i;
    }
    ppl_vm->tag_table[ii].inst_i = ppl_vm->inst_i;
    strncpy(ppl_vm->tag_table[ii].tag_name, tag_name->txt, NAME_SIZE-1);
    ppl_vm->tag_table[ii].tag_name[NAME_SIZE-1] = 0U;
    ppl_vm->unused_tag_i = 0;
    if (ii == ppl_vm->tag_len) {
        ppl_vm->tag_len++;
    }
}


uint8_t ppl_remove_tag(ppl_t *ppl_vm, string_t *tag_name)
{
    uint8_t tag_index = ppl_get_tag_index(ppl_vm, tag_name);
    if (tag_index == ppl_vm->tag_len) {
        return 0;
    }
    ppl_vm->tag_table[tag_index].tag_name[0] = 0U;
    ppl_vm->tag_table[tag_index].inst_i = 0U;
    ppl_vm->unused_tag_i = tag_index;
    return tag_index;
}



void ppl_dumpvars(ppl_t *ppl_vm)
{
    char str_i[12];
    char str_val[12];
    for (int i = 1; i < ppl_vm->data_len; i++) {
        int_to_hex(i, str_i);
        int_to_hex(ppl_vm->data_mem[i].val, str_val);
        string_init4(&g_tmp_str, str_i, ": ", ppl_vm->data_mem[i].name, " = 0x");
        string_append2(&g_tmp_str, str_val, "\r\n");
        string_print(&g_tmp_str);
    }
}


bool ppl_append_inst(ppl_t *ppl_vm, uint8_t op, uint8_t rta, uint32_t d1, uint32_t d2, bool d1_is_num, bool d2_is_num)
{
    bool ok = true;
    if (ppl_vm->inst_i == 0) {
        ppl_vm->inst_i = 1;
    }
    if (ppl_vm->inst_i >= sizeof(ppl_vm->inst_mem)) {
        return !ok;
    }
    ppl_vm->inst_mem[ppl_vm->inst_i].opcode = op;
    ppl_vm->inst_mem[ppl_vm->inst_i].data1 = d1;
    ppl_vm->inst_mem[ppl_vm->inst_i].data2 = d2;
    ppl_vm->inst_mem[ppl_vm->inst_i].data1_is_number = d1_is_num;
    ppl_vm->inst_mem[ppl_vm->inst_i].data2_is_number = d2_is_num;
    ppl_vm->inst_mem[ppl_vm->inst_i].result_tag_addr = rta;
    ppl_vm->inst_i++;
    return ok;
}


uint8_t ppl_get_opcode(string_t *cmd_string, string_t *op_string)
{
    uint8_t operation = 0U;
    if (string_in_list(op_string, "==")) {
        operation = 0x1;
    } else if (string_in_list(op_string, "<")) {
        operation = 0x2;
    } else if (string_in_list(op_string, ">")) {
        operation = 0x3;
    } else if (string_in_list(op_string, "<=")) {
        operation = 0x4;
    } else if (string_in_list(op_string, ">=")) {
        operation = 0x5;
    } else if (string_in_list(op_string, "!=")) {
        operation = 0x6;
    } else if (string_in_list(op_string, "+")) {
        operation = 0x7;
    } else if (string_in_list(op_string, "-")) {
        operation = 0x8;
    } else if (string_in_list(op_string, "*")) {
        operation = 0x9;
    } else if (string_in_list(op_string, "/")) {
        operation = 0xa;
    } else if (string_in_list(op_string, "&")) {
        operation = 0xb;
    } else if (string_in_list(op_string, "|")) {
        operation = 0xc;
    } else if (string_in_list(op_string, "%")) {
        operation = 0xd;
    } else if (string_in_list(op_string, "<<")) {
        operation = 0xe;
    } else if (string_in_list(op_string, ">>")) {
        operation = 0xf;
    }

    uint8_t opcode = 0U;
    if (string_in_list(cmd_string, "=")) {
        opcode = 0x10 + operation;
     } else if (string_in_list(cmd_string, "peek")) {
        opcode = 0x20;
    } else if (string_in_list(cmd_string, "poke")) {
        opcode = 0x30;
    } else if (string_in_list(cmd_string, "while")) {
        opcode = 0x40 + operation;
    } else if (string_in_list(cmd_string, "if")) {
        opcode = 0x50 + operation;
    } else if (string_in_list(cmd_string, "else")) {
        opcode = 0x60;
    } else if (string_in_list(cmd_string, "end")) {
        opcode = 0x70;
    }
    return opcode;
}

uint8_t ppl_err_check(ppl_t *ppl_vm, string_t tokens[], uint8_t opcode, string_t *msg)
{
    uint8_t err_code = 0;
    if (string_in_list(&tokens[0], "=")) {
        bool data1_is_number;
        const uint32_t data1 = ppl_get_data_mem_offset(ppl_vm, &tokens[2], &data1_is_number);
        const bool data1_is_declared = (data1 != 0U);
        bool data2_is_number;
        const uint32_t data2 = ppl_get_data_mem_offset(ppl_vm, &tokens[4], &data2_is_number);
        const bool data2_is_declared = (data2 != 0U);
        const bool valid_op = (opcode & 0xF);
        const bool op_is_on_line = (tokens[3].len > 0);
        const bool data1_is_on_line = (tokens[2].len > 0);
        const bool data2_is_on_line = (tokens[4].len > 0);

        if (!data1_is_on_line) {
            err_code = 1;
            string_init(msg, "ERR 1.1: Missing value or variable to be assigned\r\n");
        } else if (!data1_is_number && !data1_is_declared) {
            err_code = 1;
            string_init(msg, "ERR 1.2: Undefined variable in expression '");
            string_append(msg, tokens[2].txt, tokens[2].len);
            string_append(msg, "'\r\n", 3);
        } else if (!valid_op && op_is_on_line) {
            err_code = 1;
            string_init(msg, "ERR 1.3. Invalid operator '");
            string_append(msg, tokens[3].txt, tokens[3].len);
            string_append(msg, "'\r\n", 3);
        } else if (valid_op && !data2_is_on_line) {
            err_code = 1;
            string_init(msg, "ERR 1.4: Missing value or variable after operator\r\n");
        } else if (valid_op && !data2_is_number && !data2_is_declared) {
            err_code = 1;
            string_init(msg, "ERR  1.5: Undefined variable after operator '");
            string_append(msg, tokens[4].txt, tokens[4].len);
            string_append(msg, "'\r\n", 3);
        }
    } else if (string_in_list(&tokens[0], "peek poke")) {
        bool data1_is_number;
        const uint32_t data1 = ppl_get_data_mem_offset(ppl_vm, &tokens[2], &data1_is_number);
        const bool data1_is_declared = (data1 != 0U);
        bool data2_is_number;
        const uint32_t data2 = ppl_get_data_mem_offset(ppl_vm, &tokens[4], &data2_is_number);
        const bool data2_is_declared = (data2 != 0U);
        const bool data1_is_on_line = (tokens[2].len > 0);
        const bool data2_is_on_line = (tokens[4].len > 0);
        const bool cmd_is_peek = string_in_list(&tokens[0], "peek");
        const bool cmd_is_poke = string_in_list(&tokens[0], "poke");

        if (!data1_is_on_line) {
            err_code = 1;
            string_init2(msg, "ERR 2.1: Missing address\r\n" , "");
        } else if (!data1_is_number && !data1_is_declared) {
            err_code = 1;
            string_init4(msg, "ERR 2.2. Undefined address '", tokens[2].txt, "'\r\n", "");
        } else if (cmd_is_peek && data2_is_number) {
            err_code = 1;
            string_init4(msg, "ERR 2.4. return variable is actually a number '", tokens[4].txt, "'\r\n", "");
        } else if (cmd_is_poke && !data2_is_on_line) {
            err_code = 1;
            string_init2(msg, "ERR 2.3: Missing poke value or variable after address\r\n" , "");
        } else if (cmd_is_poke && !data2_is_number && !data2_is_declared) {
            err_code = 1;
            string_init4(msg, "ERR 2.5. Undefined variable '", tokens[4].txt, "'\r\n", "");
        }
    }

    return err_code;
}


void ppl_run_cmd(ppl_t *ppl_vm, uint8_t pc, string_t *msg)
{
    if (pc >= ppl_vm->inst_len) return;

    uint8_t  opcode = ppl_vm->inst_mem[pc].opcode;
    uint8_t  result_tag_addr = ppl_vm->inst_mem[pc].result_tag_addr;
    uint32_t data1 = ppl_vm->inst_mem[pc].data1;
    uint32_t data1_is_number = ppl_vm->inst_mem[pc].data1_is_number;
    uint32_t data2 = ppl_vm->inst_mem[pc].data2;
    uint32_t data2_is_number = ppl_vm->inst_mem[pc].data2_is_number;

    const uint8_t data_mem_result_offset2 = (result_tag_addr == 0) ?
            ppl_append_data(ppl_vm, &g_line_parts[1]) : result_tag_addr;
    const uint32_t x1 = data1_is_number ? data1 : ppl_vm->data_mem[data1].val;
    const uint32_t x2 = data2_is_number ? data2 : ppl_vm->data_mem[data2].val;
    const uint8_t op = opcode & 0xF;
    uint32_t y = ppl_vm->data_mem[data_mem_result_offset2].val;
    switch (op) {
    case  0: y = x1; break;
    case  1: y = (x1 == x2); break;
    case  2: y = (x1 < x2); break;
    case  3: y = (x1 > x2); break;
    case  4: y = (x1 <= x2); break;
    case  5: y = (x1 >= x2); break;
    case  6: y = (x1 != x2); break;
    case  7: y = (x1 + x2); break;
    case  8: y = (x1 - x2); break;
    case  9: y = (x1 * x2); break;
    case 10: y = (x1 / x2); break;
    case 11: y = (x1 & x2); break;
    case 12: y = (x1 | x2); break;
    case 13: y = (x1 % x2); break;
    case 14: y = (x1 << x2); break;
    case 15: y = (x1 >> x2); break;
    default: ;
    }

    ppl_vm->data_mem[data_mem_result_offset2].val = y;
    char hexstr[9];
    string_init2(msg, "0x", int_to_hex(y, hexstr));
    string_append2(msg, "; # op=0x", int_to_hex(op, hexstr));
    string_append2(msg, " x1=0x", int_to_hex(x1, hexstr));
    if (op != 0) {
        string_append2(msg, ", x2=0x", int_to_hex(x2, hexstr));
    }
    string_append2(msg, "\r\n", "");
}


uint8_t ppl_compile_line(ppl_t *ppl_vm, string_t *line, string_t *msg)
{
    uint8_t err_code = 0;
    string_get_words(line, g_line_parts);
    if (string_in_list(&g_line_parts[1], "=")) {
        // change from: v = a + b   to: = v + a b
        string_swap(&g_line_parts[0], &g_line_parts[1]);
    } else if (string_in_list(&g_line_parts[0], "peek poke")) {
        // change from: peek a b    to: peek - a - v
        string_swap(&g_line_parts[2], &g_line_parts[4]);
        string_swap(&g_line_parts[1], &g_line_parts[2]);
    }

    // v     = a + b
    // =     v a + b (swap)
    // while t i < 9
    // if    t i < 9
    // peek  a v
    // poke  a v
    // else  t
    // end   t

    uint8_t opcode = ppl_get_opcode(&g_line_parts[0], &g_line_parts[3]);

    string_init(msg, "No errors detected\r\n");
    if (string_in_list(&g_line_parts[0], "dumpvars")) {
        err_code = 1;
        ppl_dumpvars(ppl_vm);
        string_init(msg, "");
        return 0;
    } else if (opcode == 0U) {
        err_code = 1;
        string_init(msg, "ERR 1: Unrecognized command '");
        string_append(msg, g_line_parts[0].txt, g_line_parts[0].len);
        string_append(msg, "'\r\n", 3);
        return 1;
    }

    if (string_in_list(&g_line_parts[0], "=")) {
        bool data1_is_number;
        uint32_t data1 = ppl_get_data_mem_offset(ppl_vm, &g_line_parts[2], &data1_is_number);
        bool data2_is_number;
        uint32_t data2 = ppl_get_data_mem_offset(ppl_vm, &g_line_parts[4], &data2_is_number);

        bool result_is_number = false;
        uint8_t data_mem_result_offset = (uint8_t)ppl_get_data_mem_offset(ppl_vm, &g_line_parts[1], &result_is_number);

        err_code = ppl_err_check(ppl_vm, g_line_parts, opcode, msg);
        if (err_code) return err_code;

        const uint8_t data_mem_result_offset2 = (data_mem_result_offset == 0) ?
                ppl_append_data(ppl_vm, &g_line_parts[1]) : data_mem_result_offset;
        ppl_append_inst(ppl_vm, opcode, data_mem_result_offset2, data1, data2, data1_is_number, data2_is_number);
        // ppl_run_cmd(ppl_vm, ppl_vm->inst_len-1, msg);

        const uint32_t x1 = data1_is_number ? data1 : ppl_vm->data_mem[data1].val;
        const uint32_t x2 = data2_is_number ? data2 : ppl_vm->data_mem[data2].val;
        const uint8_t op = opcode & 0xF;
        uint32_t y = ppl_vm->data_mem[data_mem_result_offset2].val;
        switch (op) {
        case  0: y = x1; break;
        case  1: y = (x1 == x2); break;
        case  2: y = (x1 < x2); break;
        case  3: y = (x1 > x2); break;
        case  4: y = (x1 <= x2); break;
        case  5: y = (x1 >= x2); break;
        case  6: y = (x1 != x2); break;
        case  7: y = (x1 + x2); break;
        case  8: y = (x1 - x2); break;
        case  9: y = (x1 * x2); break;
        case 10: y = (x1 / x2); break;
        case 11: y = (x1 & x2); break;
        case 12: y = (x1 | x2); break;
        case 13: y = (x1 % x2); break;
        case 14: y = (x1 << x2); break;
        case 15: y = (x1 >> x2); break;
        default: ;
        }

        ppl_vm->data_mem[data_mem_result_offset2].val = y;
        char hexstr[9];
        string_init2(msg, "0x", int_to_hex(y, hexstr));
        string_append2(msg, "; # op=0x", int_to_hex(op, hexstr));
        string_append2(msg, " x1=0x", int_to_hex(x1, hexstr));
        if (op != 0) {
            string_append2(msg, ", x2=0x", int_to_hex(x2, hexstr));
        }
        string_append2(msg, "\r\n", "");

    } else if (string_in_list(&g_line_parts[0], "peek poke")) {
        bool data1_is_number;
        uint32_t data1 = ppl_get_data_mem_offset(ppl_vm, &g_line_parts[2], &data1_is_number);
        bool data2_is_number;
        uint32_t data2 = ppl_get_data_mem_offset(ppl_vm, &g_line_parts[4], &data2_is_number);

        bool result_is_number = false;
        uint8_t dest_mem_result_offset = (uint8_t)ppl_get_data_mem_offset(ppl_vm, &g_line_parts[1], &result_is_number);

        err_code = ppl_err_check(ppl_vm, g_line_parts, opcode, msg);
        if (err_code) return err_code;

        if (string_in_list(&g_line_parts[0], "peek")) {
            ppl_append_inst(ppl_vm, opcode, dest_mem_result_offset, data1, data2, data1_is_number, data2_is_number);

            const uint32_t fabric_offset = data1_is_number ? data1 : ppl_vm->data_mem[data1].val;
            const uint32_t val_from_fabric = (uint32_t)fabric_base_addr[fabric_offset];
            const uint8_t dest_mem_offset = data2_is_number ? 0 : (uint8_t)data2;
            const bool dest_is_declared = dest_mem_offset != 0;
            const bool create_new_variable = (!data2_is_number && !dest_is_declared);
            const uint32_t dest_mem_offset2 = create_new_variable ?
                    ppl_append_data(ppl_vm, &g_line_parts[4]) : dest_mem_offset;
            ppl_vm->data_mem[dest_mem_offset2].val = val_from_fabric;
            const uint32_t val_from_data_mem = ppl_vm->data_mem[dest_mem_offset2].val;
            char hexstr[9];
            string_init2(msg, "0x", int_to_hex(val_from_data_mem, hexstr));
            string_append4(msg, "; # peek[0x", int_to_hex(fabric_offset, hexstr), "]", "\r\n");
         } else if (string_in_list(&g_line_parts[0], "poke")) {
            ppl_append_inst(ppl_vm, opcode, dest_mem_result_offset, data1, data2, data1_is_number, data2_is_number);
            const uint32_t fabric_offset = data1_is_number ? data1 : ppl_vm->data_mem[data1].val;
            const uint32_t val_to_fabric = data2_is_number ? data2 : ppl_vm->data_mem[data2].val;
            fabric_base_addr[fabric_offset] = (uint64_t)val_to_fabric;
            char hexstr[9];
            string_init2(msg, "0x", int_to_hex(val_to_fabric, hexstr));
            string_append4(msg, "; # poke [0x", int_to_hex(fabric_offset, hexstr), "]", "\r\n");
        }
    } else if (string_in_list(&g_line_parts[0], "while if")) {
        bool data1_is_number;
        uint32_t data1 = ppl_get_data_mem_offset(ppl_vm, &g_line_parts[2], &data1_is_number);
        bool data2_is_number;
        uint32_t data2 = ppl_get_data_mem_offset(ppl_vm, &g_line_parts[4], &data2_is_number);
        uint8_t result_tag_addr = 0;
        if (g_line_parts[2].len == 0) {
            err_code = 2;
            string_init(msg, "ERR 2: Missing data 1 value or variable\r\n");
        } else if (data1 == 0 && !data1_is_number) {
            err_code = 3;
            string_init(msg, "ERR 3: Undefined data 1 value variable '");
            string_append(msg, g_line_parts[2].txt, g_line_parts[2].len);
            string_append(msg, "'\r\n", 3);
        } else if ((g_line_parts[3].len > 0) && (opcode & 0xF == 0)) {
            err_code = 4; // Invalid operator
            string_init(msg, "ERR 4. Invalid operator\r\n");
        } else if ((opcode & 0xF) && (data2 == 0U && !data2_is_number)) {
            err_code = 5; // Invalid or missing operand 2
            string_init(msg, "ERR 5: Invalid or missing operand 2\r\n");
        }  if (string_in_list(&g_line_parts[0], "if while")) {
            if (g_line_parts[1].len == 0) {
                err_code = 6;
                string_init(msg, "ERR 6: Missing tag\r\n");
            } else if (result_tag_addr != 0) {
                err_code = 7;
                string_init(msg, "ERR 7: Reusing active tag\r\n");
            }
        }
    } else if (string_in_list(&g_line_parts[0], "else end")) {
        bool data1_is_number;
        uint32_t data1 = ppl_get_data_mem_offset(ppl_vm, &g_line_parts[2], &data1_is_number);
        bool data2_is_number;
        uint32_t data2 = ppl_get_data_mem_offset(ppl_vm, &g_line_parts[4], &data2_is_number);
        uint8_t result_tag_addr = 0;
        if (g_line_parts[1].len == 0) {
            err_code = 11;
            string_init(msg, "ERR 11: Missing tag\r\n");
        } else if (result_tag_addr == 0) {
            err_code = 12; // undefined tag
            string_init(msg, "ERR 12: Undefined tag\r\n");
        }
    }

/*
    if (err_code == 0) {
        ppl_vm->inst_mem[ppl_vm->inst_i].opcode = opcode;
        ppl_vm->inst_mem[ppl_vm->inst_i].data1 = data1;
        ppl_vm->inst_mem[ppl_vm->inst_i].data2 = data2;
        ppl_vm->inst_mem[ppl_vm->inst_i].data1_is_number = data1_is_number;
        ppl_vm->inst_mem[ppl_vm->inst_i].data2_is_number = data2_is_number;
        ppl_vm->inst_mem[ppl_vm->inst_i].result_tag_addr = result_tag_addr;
        if (string_in_list(&g_line_parts[0], "=")) {

        } else if (string_in_list(&g_line_parts[0], "if while")) {
            ppl_add_tag(ppl_vm, &g_line_parts[1]);
        } else if (string_in_list(&g_line_parts[0], "end")) {
            ppl_remove_tag(ppl_vm, &g_line_parts[1]);
        }
    }
*/

    return err_code;
}


// =====================================================================
// =====================================================================

void rx_append(void) {
    string_append(&g_line, g_rx_buff, g_rx_size);
    if (g_rx_buff[0] == '\n' || g_rx_buff[0] == '\r') {
        g_line_ready = true;
    }
}


void rx_echo(void) {
    if (g_echo && g_rx_size) {
        MSS_UART_polled_tx(&g_mss_uart1_lo, &g_rx_buff[g_rx_size-1], 1);
    }
}


/* This is the handler function for the UART RX interrupt.
 * In this example project UART0 local interrupt is enabled on hart0.
 */
void uart1_rx_handler(mss_uart_instance_t *this_uart) {
    static int prev_rx_size = 0;
    uint32_t hart_id = read_csr(mhartid);
    int8_t info_string[50];

    /* This will execute when interrupt from hart 1 is raised */
    g_rx_size = MSS_UART_get_rx(this_uart, g_rx_buff, sizeof(g_rx_buff));
    rx_echo();
    rx_append();
    irq_cnt++;
    // sprintf(info_string, "UART1 Interrupt count = 0x%x \r\n\r\n", irq_cnt);
    // MSS_UART_polled_tx(&g_mss_uart1_lo, info_string, strlen(info_string));
}


/* Main function for the hart1(U54 processor).
 * Application code running on hart1 is placed here.
 * MMUART1 local interrupt is enabled on hart1.
 * In the respective U54 harts, local interrupts of the corresponding MMUART
 * are enabled. e.g. in U54_1.c local interrupt of MMUART1 is enabled. */

void u54_1(void) {
    uint64_t mcycle_start = 0U;
    uint64_t mcycle_end = 0U;
    uint64_t delta_mcycle = 0U;
    uint64_t hartid = read_csr(mhartid);

    string_init(&g_line, "");

    clear_soft_interrupt();
    set_csr(mie, MIP_MSIP);

#if (IMAGE_LOADED_BY_BOOTLOADER == 0)

    /* Put this hart in WFI. */
    do
    {
        __asm("wfi");
    }while(0 == (read_csr(mip) & MIP_MSIP));

    /* The hart is now out of WFI, clear the SW interrupt. Here onwards the
     * application can enable and use any interrupts as required */

    clear_soft_interrupt();

#endif

    __enable_irq();

    /* Bring all the MMUARTs out of Reset */
    (void) mss_config_clk_rst(MSS_PERIPH_MMUART1, (uint8_t) 1, PERIPHERAL_ON);
    (void) mss_config_clk_rst(MSS_PERIPH_MMUART2, (uint8_t) 1, PERIPHERAL_ON);
    (void) mss_config_clk_rst(MSS_PERIPH_MMUART3, (uint8_t) 1, PERIPHERAL_ON);
    (void) mss_config_clk_rst(MSS_PERIPH_MMUART4, (uint8_t) 1, PERIPHERAL_ON);
    (void) mss_config_clk_rst(MSS_PERIPH_CFM, (uint8_t) 1, PERIPHERAL_ON);

    /* All clocks ON */

    MSS_UART_init(&g_mss_uart1_lo,
    MSS_UART_115200_BAUD,
    MSS_UART_DATA_8_BITS | MSS_UART_NO_PARITY | MSS_UART_ONE_STOP_BIT);
    MSS_UART_set_rx_handler(&g_mss_uart1_lo, uart1_rx_handler, MSS_UART_FIFO_SINGLE_BYTE);

    MSS_UART_enable_local_irq(&g_mss_uart1_lo);

    /* Demonstrating polled MMUART transmission */
    // MSS_UART_polled_tx(&g_mss_uart1_lo,g_message1, sizeof(g_message1));
    MSS_UART_polled_tx(&g_mss_uart1_lo,"PPL Command Interface\r\n", 23);

    /* Demonstrating interrupt method of transmission */
//    MSS_UART_irq_tx(&g_mss_uart1_lo, g_message2, sizeof(g_message2));

    /* Makes sure that the previous interrupt based transmission is completed
     * Alternatively, you could register TX complete handler using
     * MSS_UART_set_tx_handler() */
//    while (0u == MSS_UART_tx_complete(&g_mss_uart1_lo)) {
//        ;
//    }

    mcycle_start = readmcycle();

    // WRITE AND READ AXI FABRIC
    MSS_UART_polled_tx(&g_mss_uart1_lo, "START MEMORY TEST\r\n", 17);
    SYSREG->SOFT_RESET_CR &= ~(SOFT_RESET_CR_FIC0_MASK | SOFT_RESET_CR_FPGA_MASK);
    SYSREG->SUBBLK_CLOCK_CR = 0xffffffff;
    for (uint64_t x = 0; x < 0xf; x++) {
        fabric_base_addr[x] = x;
    }

    for (volatile uint64_t data = 0, x = 0; x < 0xf; x++) {
        data = fabric_base_addr[x];
        if (data == x) {
            MSS_UART_polled_tx(&g_mss_uart1_lo, "p", 1);
        } else {
            MSS_UART_polled_tx(&g_mss_uart1_lo, "F", 1);
       }
    }
    MSS_UART_polled_tx(&g_mss_uart1_lo, "\r\nEND MEMORY TEST\r\n", 19);
    MSS_UART_polled_tx(&g_mss_uart1_lo, "=> ", 3);

    while (1u) {
        if (g_line_ready) {
            g_line_ready = false;
            uint8_t err_code = ppl_compile_line(&g_ppl_vm, &g_line, &g_msg);
            string_init(&g_line, "");
            if (g_msg.len > 0U) {
                string_print(&g_msg);
            }
            MSS_UART_polled_tx(&g_mss_uart1_lo, "=> ", 3);

//            switch (g_rx_buff[0u]) {
//
//            case '0':
//                mcycle_end = readmcycle();
//                delta_mcycle = mcycle_end - mcycle_start;
//                sprintf(info_string, "hart %ld, %ld delta_mcycle \r\n", hartid,
//                        delta_mcycle);
//                MSS_UART_polled_tx(&g_mss_uart1_lo, info_string,
//                        strlen(info_string));
//                break;
//            case '1':
//                /* show menu */
//                MSS_UART_irq_tx(&g_mss_uart1_lo, g_message2,
//                        sizeof(g_message2));
//                break;
//            case '2':
//
//                /* polled method of transmission */
//                MSS_UART_polled_tx(&g_mss_uart1_lo, polled_message,
//                        sizeof(polled_message));
//
//                break;
//            case '3':
//
//                /* interrupt method of transmission */
//                MSS_UART_irq_tx(&g_mss_uart1_lo, intr_message,
//                        sizeof(intr_message));
//                break;
//
//            default:
//                // MSS_UART_polled_tx(&g_mss_uart1_lo, g_rx_buff, g_rx_size);
//                break;
//            }
//
//            g_rx_size = 0u;
        }
    }
}

/* hart1 Software interrupt handler */

void Software_h1_IRQHandler(void) {
    uint64_t hart_id = read_csr(mhartid);
    count_sw_ints_h1++;
}
