#ifndef SRC_GREP_GREP_H_
#define SRC_GREP_GREP_H_

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#define LEN_FILE 2048

enum flag_type {no_flag, e, i, v, c, l, n, wrong_flag, pattern};

void grep(int argc, char *argv[]);
void define_flags(char *flag, enum flag_type *choice_flag);
void make_grep(char *file_name, char *str_template, enum flag_type choice_flag,
               int count_file);
void regex_and_flag(FILE *file, char *file_name, char *str_template, enum flag_type choice_flag,
          int count_file);
int make_flag(enum flag_type choice_flag, int *cflags);
int output(char *file_name, char *tmp_str, enum flag_type choice_flag, int status,
           int count, int count_file);
void make_flag_l(char *file_name);
void make_flag_e_i_v_n(char *file_name, char *tmp_str, enum flag_type choice_flag,
                       int count_str, int count_file);
void make_flag_c(char *file_name, int count_str, int count_file);

#endif  // SRC_GREP_GREP_H_
