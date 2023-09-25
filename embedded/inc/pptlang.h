/*
 * pptlang.h
 *
 */

#ifndef PPTLANG_H_
#define PPTLANG_H_

#define PPLT_NUM_INSTRUCTIONS 128
#define PPLT_NUM_VARIABLES     64
#define PPLT_NUM_TAGS          64
#define PPLT_NAME_SIZE         12
#define PPLT_NUM_LINE_PARTS 5
typedef struct {
    uint32_t data1;
    uint32_t data2;
    uint8_t  opcode; // {cmd[7:4], op[3:0]}
    uint8_t  result_tag_addr;
    bool     data1_is_number;
    bool     data2_is_number;
} pptl_instr_t;

typedef struct {
    uint32_t val;
    uint8_t  name[PPLT_NAME_SIZE];
} pptl_data_t;

typedef struct {
    uint32_t inst_i;
    uint8_t  tag_name[PPLT_NAME_SIZE];
} pptl_tag_t;

typedef struct {
    uint8_t inst_i;
    uint8_t inst_len;
    uint8_t data_len;
    uint8_t tag_len;
    uint8_t unused_tag_i;
    pptl_instr_t inst_mem[PPLT_NUM_INSTRUCTIONS];
    pptl_data_t  data_mem[PPLT_NUM_VARIABLES];
    pptl_tag_t   tag_table[PPLT_NUM_TAGS];
    size_t       test_count;
    size_t       test_fail;
} pptl_t;

void pptl_reset(pptl_t *ppl_vm);
uint32_t pptl_get_data_mem_offset(pptl_t *ppl_vm, string_t *name, bool *is_number);
uint8_t pptl_get_tag_index(pptl_t *ppl_vm, string_t *tag_name);
uint8_t pptl_append_data(pptl_t *ppl_vm, string_t *data_name);
void pptl_compute_data(pptl_t *ppl_vm, uint8_t result, uint8_t data1, uint8_t operation, uint8_t data2);
void pptl_add_tag(pptl_t *ppl_vm, string_t *tag_name);
uint8_t pptl_remove_tag(pptl_t *ppl_vm, string_t *tag_name);
void pptl_dumpvars(pptl_t *ppl_vm);
bool pptl_append_inst(pptl_t *ppl_vm, uint8_t op, uint8_t rta, uint32_t d1, uint32_t d2, bool d1_is_num, bool d2_is_num);
uint8_t pptl_get_opcode(string_t *cmd_string, string_t *op_string);
uint8_t pptl_err_check(pptl_t *ppl_vm, string_t tokens[], uint8_t opcode, string_t *msg);
void pptl_run_cmd(pptl_t *ppl_vm, uint8_t pc, string_t *msg);
uint8_t pptl_compile_line(pptl_t *ppl_vm, string_t *line, string_t *msg);

#endif /* PPTLANG_H_ */
