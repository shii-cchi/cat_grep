#ifndef SRC_CAT_CAT_H_
#define SRC_CAT_CAT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN_FILE 2048

enum flag_type {no_flag, b, e, E, n, s, t, T, v, wrong_flag, file, wrong_gnu_flag};

void cat(int argc, char *argv[]);
void define_flags(char *flag, enum flag_type *choice_flag);
int define_long_flags(char *flag);
void make_cat(char *file_name, enum flag_type choice_flag);
void just_print(FILE *file);
void cat_with_flags(FILE *file, enum flag_type choice_flag);
int make_flag_b_n(char *str, enum flag_type choice_flag, int count_str);
void make_flag_e_E(char *str, enum flag_type choice_flag);
void make_flag_t_T(char *str, enum flag_type choice_flag);
int make_flag_s(char *str, int count_str);
void make_flag_v(char ch);
void make_empty_str(char *str);
int backward_strlen(const char *str);

#endif  // SRC_CAT_CAT_H_
