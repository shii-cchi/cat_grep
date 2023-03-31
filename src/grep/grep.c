#include "grep.h"

void grep(int argc, char *argv[]) {
  enum flag_type choice_flag = no_flag;
  if (argc < 3) {
    fprintf(stderr, "No file/flag/pattern");
  }
  if (argc >= 3) {
    define_flags(argv[1], &choice_flag);
    if (choice_flag == wrong_flag) {
      fprintf(stderr, "No such flag");
    } else {
      int index_file = 0, index_pattern = 0, count_file = 0;
      if (choice_flag == pattern) {
        index_file = 2, index_pattern = 1, choice_flag = e, count_file = argc - 2;
      } else {
        index_file = 3, index_pattern = 2, count_file = argc - 3;
      }
      while (index_file < argc) {
        make_grep(argv[index_file], argv[index_pattern], choice_flag, count_file);
        index_file++;
      }
    }
  }
}

void define_flags(char *flag, enum flag_type *choice_flag) {
  if (flag[0] == '-' && strlen(flag) == 2) {
    switch (flag[1]) {
      case 'e':
        *choice_flag = e;
        break;
      case 'i':
        *choice_flag = i;
        break;
      case 'v':
        *choice_flag = v;
        break;
      case 'c':
        *choice_flag = c;
        break;
      case 'l':
        *choice_flag = l;
        break;
      case 'n':
        *choice_flag = n;
        break;
      default:
        *choice_flag = wrong_flag;
        break;
    }
  } else {
    *choice_flag = pattern;
    if (flag[0] == '-') {
      *choice_flag = wrong_flag;
    }
  }
}

void make_grep(char *file_name, char *str_template, enum flag_type choice_flag,
               int count_file) {
  FILE *file = fopen(file_name, "r");
  if (file != NULL) {
    regex_and_flag(file, file_name, str_template, choice_flag, count_file);
    fclose(file);
  } else {
    fprintf(stderr, "No such file or directory");
  }
}

void regex_and_flag(FILE *file, char *file_name, char *str_template, enum flag_type choice_flag,
          int count_file) {
  regex_t regex;
  size_t len = 0;
  int cflags, status, count_symb = 0, count_str = 1;
  cflags = make_flag(choice_flag, &cflags);
  regcomp(&regex, str_template, cflags);
  while (count_symb != EOF) {
    char *tmp_str = NULL;
    count_symb = getline(&tmp_str, &len, file);
    if (tmp_str && count_symb != EOF) {
      status = regexec(&regex, tmp_str, 0, NULL, 0);
      if (status == 2) {
        status = 0;
      }
      count_str = output(file_name, tmp_str, choice_flag, status, count_str,
                         count_file);
      if (choice_flag == n) {
        count_str++;
      }
    }
    free(tmp_str);
  }
  if (choice_flag == c) {
    make_flag_c(file_name, count_str, count_file);
  }
  regfree(&regex);
}

int make_flag(enum flag_type choice_flag, int *cflags) {
  *cflags = REG_EXTENDED;
  if (choice_flag == i) {
    *cflags |= REG_ICASE;
  } else if (choice_flag == v) {
    *cflags |= REG_NOMATCH;
  }
  return *cflags;
}

int output(char *file_name, char *tmp_str, enum flag_type choice_flag, int status,
           int count_str, int count_file) {
  if (status == 0) {
    if (choice_flag == l && count_str == 1) {
      count_str++;
      make_flag_l(file_name);
    }
    if (choice_flag != v && choice_flag != l && choice_flag != c) {
      make_flag_e_i_v_n(file_name, tmp_str, choice_flag, count_str, count_file);
    }
    if (choice_flag == c) {
      count_str++;
    }
  } else {
    if (choice_flag == v) {
      make_flag_e_i_v_n(file_name, tmp_str, choice_flag, count_str, count_file);
    }
  }
  return count_str;
}

void make_flag_l(char *file_name) {
  printf("%s", file_name);
  if (file_name[strlen(file_name) - 1] != '\n') {
    printf("\n");
  }
}

void make_flag_e_i_v_n(char *file_name, char *tmp_str, enum flag_type choice_flag,
                       int count_str, int count_file) {
  if (count_file > 1) {
    printf("%s:", file_name);
  }
  if (choice_flag == n || choice_flag == v) {
    if (choice_flag == n) {
      printf("%d:", count_str);
    }
  }
  printf("%s", tmp_str);
  if (tmp_str[strlen(tmp_str) - 1] != '\n') {
    printf("\n");
  }
}

void make_flag_c(char *file_name, int count_str, int count_file) {
  if (count_file > 1) {
    printf("%s:", file_name);
  }
  printf("%d\n", count_str - 1);
}
