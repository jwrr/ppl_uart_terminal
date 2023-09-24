/*
 * string_t.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "inc/string_t.h"


void string_init(string_t *str, const uint8_t ch_array[])
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
    string_init(dest, src->txt);
    return true;
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


uint8_t string_get_words(string_t *cmd_line, string_t parts[], uint8_t num_line_parts) {
    string_rtrim(cmd_line);
    uint8_t num_words = 0;
    for (int i=0; i<num_line_parts; i++) {
        string_get_word(cmd_line, &parts[i]);
        if (parts[i].len == 0 && num_words == 0) {
            num_words = i + 1;
        }
    }
    return num_words;
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


