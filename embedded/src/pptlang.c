/*
 * pptlang.c
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "inc/string_t.h"
#include "inc/pptlang.h"


uint64_t * const fabric_base_addr = (uint64_t *)0x61000000U;


//#define INFOLEN 138U
//uint8_t g_print_line[INFOLEN];
// =====================================================================
// PeekPokeTestLang (PPTL)
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


string_t g_line_parts[NUM_LINE_PARTS];
string_t g_tmp_str;



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
    const uint8_t num_words = string_get_words(line, g_line_parts, NUM_LINE_PARTS);

    const bool just_print_variable = (g_line_parts[0].len > 0) &&
            (g_line_parts[1].len == 0) &&
            !string_in_list(&g_line_parts[0], "dumpvars");
    if (just_print_variable) {
        // Change from: a to: a = a
        string_copy(&g_line_parts[1], &g_line_parts[0]);
        string_copy(&g_line_parts[2], &g_line_parts[0]);
        string_init(&g_line_parts[0], "=");
    } else if (string_in_list(&g_line_parts[1], "=")) {
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
        ppl_dumpvars(ppl_vm);
        string_init(msg, "");
        return 0;
    }

    /*
    const bool just_print_the_value = (num_words == 1);
    if (just_print_the_value) {
        bool data1_is_number;
        uint32_t data1 = ppl_get_data_mem_offset(ppl_vm, &g_line_parts[2], &data1_is_number);
        const data1_is_declared = (data1 != 0);
        if  (!data1_is_number && !data1_is_declared) {
            string_init4(msg, "ERR 0.1. Undeclared address '", g_line_parts[2].txt, "'\r\n", "");
            return 1;
        }
        char hexstr[9];
        string_init2(msg, "0x", int_to_hex(data1, hexstr));
        return err_code;
    }
*/

    if (opcode == 0U) {
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


