#include "cat.h"

void cat(int argc, char *argv[]) {
  enum flag_type choice_flag = no_flag;
  if (argc == 1) {
    fprintf(stderr, "No file and flag");
  }
  if (argc >= 2) {
    define_flags(argv[1], &choice_flag);
    if (choice_flag == wrong_flag || choice_flag == wrong_gnu_flag) {
      fprintf(stderr, "No such flag");
    } else {
      int index_first_file;
      if (choice_flag == file) {
        index_first_file = 1, choice_flag = no_flag;
      } else {
        index_first_file = 2;
      }
      while (index_first_file < argc) {
        make_cat(argv[index_first_file], choice_flag);
        index_first_file++;
      }
    }
  }
}

void define_flags(char *flag, enum flag_type *choice_flag) {
  int gnu_flag = 1;
  if (strlen(flag) > 2 && flag[0] == '-') {
    gnu_flag = define_long_flags(flag);
  }
  if (flag[0] == '-' && gnu_flag == 1) {
    switch (flag[1]) {
      case 'b':
        *choice_flag = b;
        break;
      case 'e':
        *choice_flag = e;
        break;
      case 'E':
        *choice_flag = E;
        break;
      case 'n':
        *choice_flag = n;
        break;
      case 's':
        *choice_flag = s;
        break;
      case 't':
        *choice_flag = t;
        break;
      case 'T':
        *choice_flag = T;
        break;
      case 'v':
        *choice_flag = v;
        break;
      default:
        *choice_flag = wrong_flag;
        break;
    }
  } else {
    *choice_flag = file;
    if (gnu_flag == 0 && flag[0] == '-') {
      *choice_flag = wrong_gnu_flag;
    }
  }
}

int define_long_flags(char *flag) {
  int flag_exist = 0;
  int comp_b = strcmp(flag, "--number-nonblank");
  int comp_n = strcmp(flag, "--number");
  int comp_s = strcmp(flag, "--squeeze-blank");
  if (comp_b == 0 || comp_n == 0 || comp_s == 0) {
    if (comp_b == 0) {
      flag[1] = 'b';
    }
    if (comp_n == 0) {
      flag[1] = 'n';
    }
    if (comp_s == 0) {
      flag[1] = 's';
    }
    flag_exist = 1;
  }
  return flag_exist;
}

void make_cat(char *file_name, enum flag_type choice_flag) {
  FILE *file = fopen(file_name, "r");
  if (file != NULL) {
    if (choice_flag == no_flag) {
      just_print(file);
    } else {
      cat_with_flags(file, choice_flag);
    }
    fclose(file);
  } else {
    fprintf(stderr, "No such file or directory\n");
  }
}

void just_print(FILE *file) {
  char str_for_print[LEN_FILE] = {0};
  while (!feof(file)) {
    make_empty_str(str_for_print);
    fgets(str_for_print, LEN_FILE, file);
    int length = backward_strlen(str_for_print);
    for (int i = 0; i < length; i++) {
      printf("%c", str_for_print[i]);
    }
  }
}

void cat_with_flags(FILE *file, enum flag_type choice_flag) {
  int index_str = 0, count_str = 1;
  char **str = (char **)malloc(sizeof(char *));
  while (!feof(file)) {
    str[index_str] = (char *)malloc(sizeof(char) * LEN_FILE);
    make_empty_str(str[index_str]);
    fgets(str[index_str], LEN_FILE, file);
    if (choice_flag == b || choice_flag == n) {
      count_str = make_flag_b_n(str[index_str], choice_flag, count_str);
    }
    if (choice_flag == e || choice_flag == E) {
      make_flag_e_E(str[index_str], choice_flag);
    }
    if (choice_flag == s) {
      count_str = make_flag_s(str[index_str], count_str);
    }
    if (choice_flag == t || choice_flag == T) {
      make_flag_t_T(str[index_str], choice_flag);
    }
    if (choice_flag == v) {
      int length = backward_strlen(str[index_str]);
      for (int i = 0; i < length; i++) {
        make_flag_v(str[index_str][i]);
      }
    }
    index_str++;
    char **tmp = (char **)realloc(str, sizeof(char *) * (index_str + 1));
    if (tmp) {
      str = tmp;
    }
  }
  for (int i = 0; i < index_str; i++) {
    free(str[i]);
  }
  free(str);
}

int make_flag_b_n(char *str, enum flag_type choice_flag, int count_str) {
  int length = backward_strlen(str);
  if (((strcmp(str, "\n\0") != 0 && length != 0 && choice_flag == b) ||
       (choice_flag == n && length != 0))) {
    printf("%6d\t", count_str);
    for (int i = 0; i < length; i++) {
      printf("%c", str[i]);
    }
    count_str++;
  } else {
    if (length != 0) {
      printf("\n");
    }
  }
  return count_str;
}

void make_flag_e_E(char *str, enum flag_type choice_flag) {
  int length = backward_strlen(str);
  for (int j = 0; j < length; j++) {
    if (str[j] == '\n') {
      printf("$\n");
    } else if (choice_flag == e) {
      make_flag_v(str[j]);
    } else if (choice_flag == E) {
      printf("%c", str[j]);
    }
  }
}

int make_flag_s(char *str, int count_str) {
  int length = backward_strlen(str);
  if (backward_strlen(str) == 1 && str[backward_strlen(str) - 1] == '\n') {
    count_str++;
    if (count_str == 2) {
      for (int i = 0; i < length; i++) {
        printf("%c", str[i]);
      }
    }
  } else {
    count_str = 1;
    for (int i = 0; i < length; i++) {
      printf("%c", str[i]);
    }
  }
  return count_str;
}

void make_flag_t_T(char *str, enum flag_type choice_flag) {
  int length = backward_strlen(str);
  for (int j = 0; j < length; j++) {
    if (str[j] == '\t') {
      printf("^I");
    } else if (choice_flag == t) {
      make_flag_v(str[j]);
    } else if (choice_flag == T) {
      printf("%c", str[j]);
    }
  }
}

void make_flag_v(char ch) {
  int c = ch;
  if (c == '\t') {
    printf("\t");
  } else if (c == '\n') {
    printf("\n");
  } else if (c >= 0 && c < 32) {
    printf("^");
    printf("%c", c + 64);
  } else if (c >= 32 && c < 127) {
    printf("%c", c);
  } else if (c == 127) {
    printf("^?");
  } else if (c >= -128 && c < -(128 - 32)) {
    printf("M-^");
    printf("%c", c + 128 + 64);
  }
}

void make_empty_str(char *str) {
  for (int i = 0; i <= LEN_FILE - 1; i++) {
    str[i] = '\0';
  }
}

int backward_strlen(const char *str) {
  int length = 0;
  for (int i = LEN_FILE - 1; i >= 0; i--) {
    if (str[i] != '\0') {
      length = i + 1;
      break;
    }
  }
  return length;
}
