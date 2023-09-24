/*
 * pptlang.h
 *
 */

#ifndef SRC_APPLICATION_INC_PPTLANG_H_
#define SRC_APPLICATION_INC_PPTLANG_H_

#define NUM_INSTRUCTIONS 128
#define NUM_VARIABLES     64
#define NUM_TAGS          64
#define NAME_SIZE         12
#define NUM_LINE_PARTS 5
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

void ppl_reset(ppl_t *ppl_vm);
uint32_t ppl_get_data_mem_offset(ppl_t *ppl_vm, string_t *name, bool *is_number);
uint8_t ppl_get_tag_index(ppl_t *ppl_vm, string_t *tag_name);
uint8_t ppl_append_data(ppl_t *ppl_vm, string_t *data_name);
void ppl_compute_data(ppl_t *ppl_vm, uint8_t result, uint8_t data1, uint8_t operation, uint8_t data2);
void ppl_add_tag(ppl_t *ppl_vm, string_t *tag_name);
uint8_t ppl_remove_tag(ppl_t *ppl_vm, string_t *tag_name);
void ppl_dumpvars(ppl_t *ppl_vm);
bool ppl_append_inst(ppl_t *ppl_vm, uint8_t op, uint8_t rta, uint32_t d1, uint32_t d2, bool d1_is_num, bool d2_is_num);
uint8_t ppl_get_opcode(string_t *cmd_string, string_t *op_string);
uint8_t ppl_err_check(ppl_t *ppl_vm, string_t tokens[], uint8_t opcode, string_t *msg);
void ppl_run_cmd(ppl_t *ppl_vm, uint8_t pc, string_t *msg);
uint8_t ppl_compile_line(ppl_t *ppl_vm, string_t *line, string_t *msg);

#endif /* SRC_APPLICATION_INC_PPTLANG_H_ */
