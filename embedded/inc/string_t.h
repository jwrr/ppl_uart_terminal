/*
 * string_t.h
 */

#ifndef SRC_APPLICATION_INC_STRING_T_H_
#define SRC_APPLICATION_INC_STRING_T_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define LINE_SIZE 128U
typedef struct {
    size_t size;
    size_t len;
    size_t cur;
    uint8_t txt[LINE_SIZE];
} string_t;

void string_init(string_t *str, const uint8_t ch_array[]);
bool string_copy(string_t *dest, const string_t *src);
size_t string_append(string_t *str, const uint8_t ch_array[], size_t n);
size_t string_append2(string_t *str, const uint8_t s1[], const uint8_t s2[]);
size_t string_append4(string_t *str, const uint8_t s1[], const uint8_t s2[], const uint8_t s3[], const uint8_t s4[]);
size_t string_init2(string_t *str, const uint8_t s1[], const uint8_t s2[]);
size_t string_init4(string_t *str, const uint8_t s1[], const uint8_t s2[], const uint8_t s3[], const uint8_t s4[]);
void string_rtrim(string_t *s);
bool string_skip_spaces(string_t *str);
size_t string_get_word(string_t *str, string_t *word);
uint8_t string_get_words(string_t *cmd_line, string_t parts[], uint8_t num_line_parts);
size_t string_get_to_eoln(string_t *str, string_t *word);
bool string_in_list(const string_t *s, const uint8_t list[]);
void string_swap(string_t *s1, string_t *s2);
char * int_to_hex(uint32_t val, char str[]);
void string_print(string_t *str);


#endif /* SRC_APPLICATION_INC_STRING_T_H_ */
