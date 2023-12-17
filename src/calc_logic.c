#include "calc_logic.h"

/*---main fuction--*/
int get_result(char *input_str, double input_x, double *result) {
  int error = FAILURE;
  error = check_input_str(input_str);
  if (error == SUCCESS) {
    char rebuild_str[512];
    memset(rebuild_str, 0, sizeof(rebuild_str));
    double x = is_find_x(input_str) ? input_x : 0.0;

    rebuild_string(rebuild_str, input_str);

    Stack_op op;
    Stack_op *pst_op = &op;
    init_stack_op(pst_op);

    Stack_op polish;
    Stack_op *pst_polish = &polish;
    init_stack_op(pst_polish);

    create_polish(pst_polish, pst_op, rebuild_str);

    error = make_calculation(polish.arr_char, x, result);
  }
  return error;
}

/*---check input str---*/
int check_input_str(char *str) {
  int result = SUCCESS;
  if (!check_length_str(str)) {
    result = 2;
  } else if (!check_correct_chars(str)) {
    result = 3;
  } else if (!check_number_brackets(str)) {
    result = 4;
  } else if (!check_functions_names(str)) {
    result = 5;
  } else if (!check_brackets(str)) {
    result = 6;
  } else if (!check_dots(str)) {
    result = 7;
  } else if (!check_x(str)) {
    result = 8;
  } else if (!check_operator_plus_minus(str)) {
    result = 9;
  } else if (!check_operator_mde(str)) {
    result = 10;
  } else if (!check_mod(str)) {
    result = 11;
  } else if (check_functions(str) != SUCCESS) {
    result = 12;
  }
  return result;
}

int check_length_str(const char *str) {
  int result = SUCCESS;
  int length = strlen(str);
  if (length > 255 || length == 0) {
    result = FAILURE;
  }
  return result;
}

int check_number_brackets(const char *str) {
  int result = SUCCESS;
  int num_opbr = 0;
  int num_clsbr = 0;
  char opbr = '(';
  char clsbr = ')';
  for (; *str; str++) {
    if (*str == opbr) num_opbr++;
    if (*str == clsbr) num_clsbr++;
  }
  if (num_opbr != num_clsbr) {
    result = FAILURE;
  }
  return result;
}

int check_correct_chars(const char *str) {
  int result = SUCCESS;
  for (; *str; str++) {
    if (!strchr("0123456789+-*/^().xcosintaqrlgmd", *str)) {
      result = FAILURE;
      break;
    }
  }
  return result;
}
/*end check_correct_chars*/

/*---check_functions_names---*/
int check_functions_names(const char *str) {
  int result = SUCCESS;
  char temp[256] = {0};
  for (; *str;) {
    if ((*str >= 'a' && *str <= 'w') || (*str >= 'y' && *str <= 'z')) {
      memset(temp, 0, sizeof(temp));
      char *tmp = temp;
      int tmp_result = 1;
      while ((*str >= 'a' && *str <= 'w') || (*str >= 'y' && *str <= 'z')) {
        *tmp = *str;
        str++;
        tmp++;
      }
      tmp_result = check_name(temp);
      if (tmp_result != 0) {
        result = FAILURE;
        break;
      }
    } else {
      str++;
    }
  }
  return result;
}

// if find return - 0, else return - 22
int check_name(const char *str) {
  int result = 22;
  int length = (int)strlen(str);
  char names[43] = "acos asin atan cos ln log mod sin sqrt tan";
  char *save_ptr;
  char *pchar = strtok_r(names, " ", &save_ptr);
  while (pchar != NULL) {
    result = strncmp(str, pchar, length);
    if (result == 0) {
      break;
    }
    pchar = strtok_r(NULL, " ", &save_ptr);
  }
  return result;
}

int check_brackets(const char *str) {
  int result = SUCCESS;
  regex_t regex;
  char *search = "^\\)|\\($|[0-9]\\(|\\)[0-9a-ln-zA-Z]|\\)\\(|\\(\\)";
  if (regcomp(&regex, search, REG_EXTENDED) == 0) {
    result = regexec(&regex, str, 0, NULL, 0);
  }
  regfree(&regex);
  return result;
}

int check_dots(const char *str) {
  int result = SUCCESS;
  regex_t regex;
  char *search =
      "[a-ce-fh-mo-ru-zA-Z]\\.|\\.[bd-kn-ru-zA-Z]|\\)\\.\\(|"
      "[0-9]\\.{2,}|[0-9]+\\.+[0-9]+\\.+|\\.+[0-9]+\\.+";

  if (regcomp(&regex, search, REG_EXTENDED) == 0) {
    result = regexec(&regex, str, 0, NULL, 0);
  }
  regfree(&regex);
  return result;
}

int check_x(const char *str) {
  int result = SUCCESS;
  regex_t regex;
  char *search =
      "\\)x\\(|\\)x|x\\(|[a-ce-zA-Z]x|x[a-ln-zA-Z]|"
      "x(mOd)|(mOd)x|[0-9]x|x[0-9]|[0-9]+\\.x|x\\.[0-9]+";
  if (regcomp(&regex, search, REG_EXTENDED) == 0) {
    result = regexec(&regex, str, 0, NULL, 0);
  }
  regfree(&regex);
  return result;
}

int check_operator_plus_minus(const char *str) {
  int result = SUCCESS;
  regex_t regex;
  char *search = "[+\\-]\\)|[+\\-]$|[+\\-]\\*|[+\\-]\\^|[+\\-]\\/";
  if (regcomp(&regex, search, REG_EXTENDED) == 0) {
    result = regexec(&regex, str, 0, NULL, 0);
  }
  regfree(&regex);
  return result;
}

int check_operator_mde(const char *str) {
  int result = SUCCESS;
  regex_t regex;
  char *search =
      "^[*\\^\\/]|[*\\^\\/]$|\\([*\\^\\/]|[*\\^\\/]\\)|"
      "[*\\^\\/]\\*|[*\\^\\/]\\/|[*\\^\\/]\\^";
  if (regcomp(&regex, search, REG_EXTENDED) == 0) {
    result = regexec(&regex, str, 0, NULL, 0);
  }
  regfree(&regex);
  return result;
}

int check_mod(const char *str) {
  int result = SUCCESS;
  int length = (int)strlen(str);
  for (int i = 0; i < length && result == SUCCESS; i++) {
    if (str[i] == 'm') {
      if (str[i + 1] == 'o' && str[i + 2] == 'd') {
        if (i == 0) {
          result = FAILURE;
        } else if (!(str[i - 1] >= '0' && str[i - 1] <= '9') &&
                   str[i - 1] != ')' && str[i - 1] != 'x' &&
                   str[i - 1] != '.') {
          result = FAILURE;
        } else if (str[i + 3] == '*' || str[i + 3] == '/' ||
                   str[i + 3] == '^' || str[i + 3] == 'm' ||
                   str[i + 3] == ')' || str[i + 3] == '\0') {
          result = FAILURE;
        }
      } else {
        result = FAILURE;
      }
    }
  }
  return result;
}

/*--- functions check ---*/

int check_functions(const char *str) {
  int result = SUCCESS;
  if (!check_acos(str)) {
    result = 13;
  } else if (!check_asin(str)) {
    result = 14;
  } else if (!check_atan(str)) {
    result = 15;
  } else if (!check_cos(str)) {
    result = 16;
  } else if (!check_sin(str)) {
    result = 17;
  } else if (!check_tan(str)) {
    result = 18;
  } else if (!check_sqrt(str)) {
    result = 19;
  } else if (!check_ln(str)) {
    result = 20;
  } else if (!check_log(str)) {
    result = 21;
  }
  return result;
}

int check_acos(const char *str) {
  int result = SUCCESS;
  int length = (int)strlen(str);
  for (int i = 0; i < length && result == SUCCESS; i++) {
    if (str[i] == 'a' && str[i + 1] == 'c' && str[i + 2] == 'o' &&
        str[i + 3] == 's') {
      if (i - 1 >= 0 && str[i - 1] == ')') {
        result = FAILURE;
      } else if (str[i + 4] == '*' || str[i + 4] == '/' || str[i + 4] == '^' ||
                 str[i + 4] == 'm' || str[i + 4] == ')' || str[i + 4] == '\0') {
        result = FAILURE;
      }
    }
  }
  return result;
}

int check_asin(const char *str) {
  int result = SUCCESS;
  int length = (int)strlen(str);
  for (int i = 0; i < length && result == SUCCESS; i++) {
    if (str[i] == 'a' && str[i + 1] == 's' && str[i + 2] == 'i' &&
        str[i + 3] == 'n') {
      if (i - 1 >= 0 && str[i - 1] == ')') {
        result = FAILURE;
      } else if (str[i + 4] == '*' || str[i + 4] == '/' || str[i + 4] == '^' ||
                 str[i + 4] == 'm' || str[i + 4] == ')' || str[i + 4] == '\0') {
        result = FAILURE;
      }
    }
  }
  return result;
}

int check_atan(const char *str) {
  int result = SUCCESS;
  int length = (int)strlen(str);
  for (int i = 0; i < length && result == SUCCESS; i++) {
    if (str[i] == 'a' && str[i + 1] == 't' && str[i + 2] == 'a' &&
        str[i + 3] == 'n') {
      if (i - 1 >= 0 && str[i - 1] == ')') {
        result = FAILURE;
      } else if (str[i + 4] == '*' || str[i + 4] == '/' || str[i + 4] == '^' ||
                 str[i + 4] == 'm' || str[i + 4] == ')' || str[i + 4] == '\0') {
        result = FAILURE;
      }
    }
  }
  return result;
}

int check_cos(const char *str) {
  int result = SUCCESS;
  int length = (int)strlen(str);
  for (int i = 0; i < length && result == SUCCESS; i++) {
    if (str[i] == 'c' && str[i + 1] == 'o' && str[i + 2] == 's' &&
        str[i - 1] != 'a') {
      if (i - 1 >= 0 && str[i - 1] == ')') {
        result = FAILURE;
      } else if (str[i + 3] == '*' || str[i + 3] == '/' || str[i + 3] == '^' ||
                 str[i + 3] == 'm' || str[i + 3] == ')' || str[i + 3] == '\0') {
        result = FAILURE;
      }
    }
  }
  return result;
}

int check_sin(const char *str) {
  int result = SUCCESS;
  int length = (int)strlen(str);
  for (int i = 0; i < length && result == SUCCESS; i++) {
    if (str[i] == 's' && str[i + 1] == 'i' && str[i + 2] == 'n' &&
        str[i - 1] != 'a') {
      if (i - 1 >= 0 && str[i - 1] == ')') {
        result = FAILURE;
      } else if (str[i + 3] == '*' || str[i + 3] == '/' || str[i + 3] == '^' ||
                 str[i + 3] == 'm' || str[i + 3] == ')' || str[i + 3] == '\0') {
        result = FAILURE;
      }
    }
  }
  return result;
}

int check_tan(const char *str) {
  int result = SUCCESS;
  int length = (int)strlen(str);
  for (int i = 0; i < length && result == SUCCESS; i++) {
    if (str[i] == 't' && str[i + 1] == 'a' && str[i + 2] == 'n' &&
        str[i - 1] != 'a') {
      if (i - 1 >= 0 && str[i - 1] == ')') {
        result = FAILURE;
      } else if (str[i + 3] == '*' || str[i + 3] == '/' || str[i + 3] == '^' ||
                 str[i + 3] == 'm' || str[i + 3] == ')' || str[i + 3] == '\0') {
        result = FAILURE;
      }
    }
  }
  return result;
}

int check_sqrt(const char *str) {
  int result = SUCCESS;
  int length = (int)strlen(str);
  for (int i = 0; i < length && result == SUCCESS; i++) {
    if (str[i] == 's' && str[i + 1] == 'q' && str[i + 2] == 'r' &&
        str[i + 3] == 't') {
      if (i - 1 >= 0 && str[i - 1] == ')') {
        result = FAILURE;
      } else if (str[i + 4] == '*' || str[i + 4] == '/' || str[i + 4] == '^' ||
                 str[i + 4] == 'm' || str[i + 4] == ')' || str[i + 4] == '\0') {
        result = FAILURE;
      }
    }
  }
  return result;
}

int check_log(const char *str) {
  int result = SUCCESS;
  int length = (int)strlen(str);
  for (int i = 0; i < length && result == SUCCESS; i++) {
    if (str[i] == 'l' && str[i + 1] == 'o' && str[i + 2] == 'g') {
      if (i - 1 >= 0 && str[i - 1] == ')') {
        result = FAILURE;
      } else if (str[i + 3] == '*' || str[i + 3] == '/' || str[i + 3] == '^' ||
                 str[i + 3] == 'm' || str[i + 3] == ')' || str[i + 3] == '\0') {
        result = FAILURE;
      }
    }
  }
  return result;
}

int check_ln(const char *str) {
  int result = SUCCESS;
  int length = (int)strlen(str);
  for (int i = 0; i < length && result == SUCCESS; i++) {
    if (str[i] == 'l' && str[i + 1] == 'n') {
      if (i - 1 >= 0 && str[i - 1] == ')') {
        result = FAILURE;
      } else if (str[i + 2] == '*' || str[i + 2] == '/' || str[i + 2] == '^' ||
                 str[i + 2] == 'm' || str[i + 2] == ')' || str[i + 2] == '\0') {
        result = FAILURE;
      }
    }
  }
  return result;
}
/*---end check input str---*/

/*--- search x---*/
int is_find_x(const char *str) {
  int result = FAILURE;
  int count = 0;
  for (; *str; str++) {
    if (*str == 'x') count++;
  }
  if (count) result = SUCCESS;
  return result;
}

/*--- rebuild string before back polish notanion ---*/

void rebuild_string(char *dst, char *src) {
  char tmp1[512];
  char tmp2[512];
  memset(tmp1, 0, sizeof(tmp1));
  memset(tmp2, 0, sizeof(tmp2));
  rename_functions(tmp1, src);
  rebuild_signs(tmp2, tmp1);
  memset(tmp1, 0, sizeof(tmp1));
  rebuild_unary_plus_minus(tmp1, tmp2);
  memset(tmp2, 0, sizeof(tmp2));
  add_zero_to_number(tmp2, tmp1);
  add_multi_to_function(dst, tmp2);
}

void rename_functions(char *dst, char *src) {
  for (; *src;) {
    if (*src == 'a' && *(src + 1) == 'c') {
      *dst = 'o';
      dst++;
      src = src + 4;
    } else if (*src == 'a' && *(src + 1) == 's') {
      *dst = 'i';
      dst++;
      src = src + 4;
    } else if (*src == 'a' && *(src + 1) == 't') {
      *dst = 'a';
      dst++;
      src = src + 4;
    } else if (*src == 'c' && *(src + 1) == 'o') {
      *dst = 'c';
      dst++;
      src = src + 3;
    } else if (*src == 's' && *(src + 1) == 'i') {
      *dst = 's';
      dst++;
      src = src + 3;
    } else if (*src == 't' && *(src + 1) == 'a') {
      *dst = 't';
      dst++;
      src = src + 3;
    } else if (*src == 's' && *(src + 1) == 'q') {
      *dst = 'q';
      dst++;
      src = src + 4;
    } else if (*src == 'l' && *(src + 1) == 'n') {
      *dst = 'n';
      dst++;
      src = src + 2;
    } else if (*src == 'l' && *(src + 1) == 'o') {
      *dst = 'g';
      dst++;
      src = src + 3;
    } else if (*src == 'm' && *(src + 1) == 'o') {
      *dst = 'm';
      dst++;
      src = src + 3;
    } else {
      *dst = *src;
      dst++;
      src++;
    }
  }
}

void rebuild_signs(char *dst, char *src) {
  int length = (int)strlen(src);
  int i = 0;
  int j = 0;
  for (; i < length;) {
    if (src[i] == '-' || src[i] == '+') {
      if ((src[i + 1] == '-' || src[i + 1] == '+')) {
        int flag = 0;
        if (src[i] == '-')
          flag = -1;
        else if (src[i] == '+')
          flag = 1;
        i = i + 1;
        while (src[i] == '-' || src[i] == '+') {
          if (src[i] == '-') flag *= -1;
          i++;
        }
        if (flag == -1) {
          dst[j] = '-';
        } else {
          dst[j] = '+';
        }
        j = j + 1;
      } else {
        dst[j] = src[i];
        i++;
        j++;
      }
    } else {
      dst[j] = src[i];
      i++;
      j++;
    }
  }
}

void rebuild_unary_plus_minus(char *dst, char *src) {
  int length = (int)strlen(src);
  int i = 0, j = 0;
  for (; i < length;) {
    if (src[i] == '-' || src[i] == '+') {
      if (i == 0) {
        if (src[i] == '-') {
          dst[j] = 'u';
          i++;
          j++;
        } else if (src[i] == '+') {
          i++;
        }
      } else if (src[i - 1] == '(' || src[i - 1] == 'o' || src[i - 1] == 'i' ||
                 src[i - 1] == 'a' || src[i - 1] == 'c' || src[i - 1] == 's' ||
                 src[i - 1] == 't' || src[i - 1] == 'q' || src[i - 1] == 'n' ||
                 src[i - 1] == 'g' || src[i - 1] == 'm' || src[i - 1] == '*' ||
                 src[i - 1] == '/' || src[i - 1] == '^') {
        if (src[i] == '-') {
          dst[j] = 'u';
          i++;
          j++;
        } else if (src[i] == '+') {
          i++;
        }
      } else {
        dst[j] = src[i];
        j++;
        i++;
      }
    } else {
      dst[j] = src[i];
      j++;
      i++;
    }
  }
}

void add_zero_to_number(char *dst, char *src) {
  int length = (int)strlen(src);
  int i = 0, j = 0;
  for (; i < length;) {
    if (src[i] == '.' && (src[i - 1] >= '0' && src[i - 1] <= '9') &&
        !(src[i + 1] >= '0' && src[i + 1] <= '9')) {
      dst[j] = src[i];
      j++;
      dst[j] = '0';
      i++;
      j++;
    } else if (src[i] == '.' && (src[i + 1] >= '0' && src[i + 1] <= '9') &&
               !(src[i - 1] >= '0' && src[i - 1] <= '9')) {
      dst[j] = '0';
      j++;
      dst[j] = src[i];
      j++;
      i++;
    } else {
      dst[j] = src[i];
      i++;
      j++;
    }
  }
}

void add_multi_to_function(char *dst, char *src) {
  int length = (int)strlen(src);
  int i = 0, j = 0;
  for (; i < length;) {
    if ((src[i] >= '0' && src[i] <= '9') &&
        (src[i + 1] == 'c' || src[i + 1] == 's' || src[i + 1] == 't' ||
         src[i + 1] == 'o' || src[i + 1] == 'i' || src[i + 1] == 'a' ||
         src[i + 1] == 'q' || src[i + 1] == 'n' || src[i + 1] == 'q')) {
      dst[j] = src[i];
      j++;
      dst[j] = '*';
      j++;
      i++;
    } else {
      dst[j] = src[i];
      i++;
      j++;
    }
  }
}

/*--- back polish notation functions ---*/

void create_polish(Stack_op *pst_polish, Stack_op *pst_op, char *pstr) {
  int ch_pr;
  char peek_ch;
  int peek_ch_pr;
  for (; *pstr; pstr++) {
    char ch = *pstr;
    if (ch >= '0' && ch <= '9') {
      while ((ch >= '0' && ch <= '9') || ch == '.') {
        push_stack_op(pst_polish, ch);
        pstr++;
        ch = *pstr;
      }
      push_stack_op(pst_polish, ' ');
    }
    if (ch == 'x') {
      push_stack_op(pst_polish, ch);
      push_stack_op(pst_polish, ' ');
    }
    if (ch == 'c' || ch == 's' || ch == 't' || ch == 'o' || ch == 'i' ||
        ch == 'a' || ch == 'q' || ch == 'n' || ch == 'g' || ch == 'u') {
      push_stack_op(pst_op, ch);
    }
    if (ch == '(') {
      push_stack_op(pst_op, ch);
    }
    if (ch == ')') {
      ch = peek_stack_op(pst_op);
      while (ch != '(') {
        ch = pop_stack_op(pst_op);
        push_stack_op(pst_polish, ch);
        push_stack_op(pst_polish, ' ');
        ch = peek_stack_op(pst_op);
      }
      ch = peek_stack_op(pst_op);
      if (ch == '(') {
        ch = pop_stack_op(pst_op);
      }
    }
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == 'm') {
      ch_pr = get_priority(ch);
      peek_ch = peek_stack_op(pst_op);
      peek_ch_pr = get_priority(peek_ch);
      if (peek_ch_pr >= ch_pr) {
        while (peek_ch_pr >= ch_pr) {
          peek_ch = pop_stack_op(pst_op);
          push_stack_op(pst_polish, peek_ch);
          push_stack_op(pst_polish, ' ');
          peek_ch = peek_stack_op(pst_op);
          peek_ch_pr = get_priority(peek_ch);
        }
      }
      push_stack_op(pst_op, ch);
    }
    if (ch == '^') {
      ch_pr = get_priority(ch);
      peek_ch = peek_stack_op(pst_op);
      peek_ch_pr = get_priority(peek_ch);
      if (peek_ch_pr > ch_pr) {
        while (peek_ch_pr > ch_pr) {
          peek_ch = pop_stack_op(pst_op);
          push_stack_op(pst_polish, peek_ch);
          push_stack_op(pst_polish, ' ');
          peek_ch = peek_stack_op(pst_op);
          peek_ch_pr = get_priority(peek_ch);
        }
      }
      if (peek_ch_pr == ch_pr) {
        push_stack_op(pst_op, ch);
      } else {
        push_stack_op(pst_op, ch);
      }
    }
  }
  if (is_empty_stack_op(pst_op)) {
    for (int i = pst_op->pos; i > 0; i--) {
      peek_ch = pop_stack_op(pst_op);
      push_stack_op(pst_polish, peek_ch);
      push_stack_op(pst_polish, ' ');
    }
  }
}

int get_priority(char ch) {
  int result = 0;
  if (ch == '(' || ch == ')') {
    result = 0;
  } else if (ch == '+' || ch == '-') {
    result = 1;
  } else if (ch == '*' || ch == '/' || ch == 'm') {
    result = 2;
  } else if (ch == 'c' || ch == 's' || ch == 't' || ch == 'o' || ch == 'i' ||
             ch == 'a' || ch == 'q' || ch == 'n' || ch == 'g') {
    result = 5;
  } else if (ch == '^') {
    result = 6;
  } else if (ch == 'u') {
    result = 7;
  }
  return result;
}

/*--- stack functions ---*/

void init_stack_op(Stack_op *st) {
  memset(st->arr_char, '\0', sizeof(st->arr_char));
  st->priority = 0;
  st->pos = 0;
}

void push_stack_op(Stack_op *st, char value) {
  st->arr_char[st->pos] = value;
  st->pos++;
}

char pop_stack_op(Stack_op *st) {
  char result;
  result = st->arr_char[st->pos - 1];
  st->arr_char[st->pos - 1] = '\0';
  st->pos--;
  return result;
}

char peek_stack_op(Stack_op *st) {
  char result;
  if (st->pos > 0)
    result = st->arr_char[st->pos - 1];
  else
    result = st->arr_char[st->pos];
  return result;
}

int is_empty_stack_op(Stack_op *st) { return st->pos; }

void init_stack_num(Stack_num *st) {
  memset(st->arr_num, 0, sizeof(st->arr_num));
  st->pos = 0;
}

void push_stack_num(Stack_num *st, double value) {
  st->arr_num[st->pos] = value;
  st->pos++;
}

double pop_stack_num(Stack_num *st) {
  double result = 0.0;
  result = st->arr_num[st->pos - 1];
  st->arr_num[st->pos - 1] = 0.0;
  st->pos--;
  return result;
}

int is_empty_stack_num(Stack_num *st) { return st->pos; }

/*--- back polish notation processing function ---*/

int make_calculation(char *str, double x, double *result) {
  int error = SUCCESS;
  Stack_num num;
  Stack_num *pst_num = &num;
  init_stack_num(pst_num);

  double number1 = 0.0;
  double number2 = 0.0;
  double number_tmp;
  char *save_ptr;
  char *token = strtok_r(str, " ", &save_ptr);
  while (token != NULL && error == SUCCESS) {
    if (*token == 'u') {
      if (is_empty_stack_num(pst_num)) {
        number_tmp = pop_stack_num(pst_num) * (-1);
        push_stack_num(pst_num, number_tmp);
      } else {
        error = FAILURE;
      }
    } else if (*token == '+') {
      if (is_empty_stack_num(pst_num)) {
        number1 = pop_stack_num(pst_num);
      } else {
        error = FAILURE;
      }
      if (is_empty_stack_num(pst_num)) {
        number2 = pop_stack_num(pst_num);
      } else {
        error = FAILURE;
      }
      number_tmp = number2 + number1;
      push_stack_num(pst_num, number_tmp);
    } else if (*token == '-') {
      if (is_empty_stack_num(pst_num)) {
        number1 = pop_stack_num(pst_num);
      } else {
        error = FAILURE;
      }
      if (is_empty_stack_num(pst_num)) {
        number2 = pop_stack_num(pst_num);
      } else {
        error = FAILURE;
      }
      number_tmp = number2 - number1;
      push_stack_num(pst_num, number_tmp);
    } else if (*token == '*') {
      if (is_empty_stack_num(pst_num)) {
        number1 = pop_stack_num(pst_num);
      } else {
        error = FAILURE;
      }
      if (is_empty_stack_num(pst_num)) {
        number2 = pop_stack_num(pst_num);
      } else {
        error = FAILURE;
      }
      number_tmp = number2 * number1;
      push_stack_num(pst_num, number_tmp);
    } else if (*token == '/') {
      if (is_empty_stack_num(pst_num)) {
        number1 = pop_stack_num(pst_num);
      } else {
        error = FAILURE;
      }
      if (is_empty_stack_num(pst_num)) {
        number2 = pop_stack_num(pst_num);
      } else {
        error = FAILURE;
      }
      number_tmp = number2 / number1;
      push_stack_num(pst_num, number_tmp);
    } else if (*token == 'm') {
      if (is_empty_stack_num(pst_num)) {
        number1 = pop_stack_num(pst_num);
      } else {
        error = FAILURE;
      }
      if (is_empty_stack_num(pst_num)) {
        number2 = pop_stack_num(pst_num);
      } else {
        error = FAILURE;
      }
      number_tmp = fmod(number2, number1);
      push_stack_num(pst_num, number_tmp);
    } else if (*token == '^') {
      if (is_empty_stack_num(pst_num)) {
        number1 = pop_stack_num(pst_num);
      } else {
        error = FAILURE;
      }
      if (is_empty_stack_num(pst_num)) {
        number2 = pop_stack_num(pst_num);
      } else {
        error = FAILURE;
      }
      number_tmp = pow(number2, number1);
      push_stack_num(pst_num, number_tmp);
    } else if (*token == 'c') {
      if (is_empty_stack_num(pst_num)) {
        number1 = pop_stack_num(pst_num);
      } else {
        error = FAILURE;
      }
      number_tmp = cos(number1);
      push_stack_num(pst_num, number_tmp);
    } else if (*token == 's') {
      if (is_empty_stack_num(pst_num)) {
        number1 = pop_stack_num(pst_num);
      } else {
        error = FAILURE;
      }
      number_tmp = sin(number1);
      push_stack_num(pst_num, number_tmp);
    } else if (*token == 't') {
      if (is_empty_stack_num(pst_num)) {
        number1 = pop_stack_num(pst_num);
      } else {
        error = FAILURE;
      }
      number_tmp = tan(number1);
      push_stack_num(pst_num, number_tmp);
    } else if (*token == 'o') {
      if (is_empty_stack_num(pst_num)) {
        number1 = pop_stack_num(pst_num);
      } else {
        error = FAILURE;
      }
      number_tmp = acos(number1);
      push_stack_num(pst_num, number_tmp);
    } else if (*token == 'i') {
      if (is_empty_stack_num(pst_num)) {
        number1 = pop_stack_num(pst_num);
      } else {
        error = FAILURE;
      }
      number_tmp = asin(number1);
      push_stack_num(pst_num, number_tmp);
    } else if (*token == 'a') {
      if (is_empty_stack_num(pst_num)) {
        number1 = pop_stack_num(pst_num);
      } else {
        error = FAILURE;
      }
      number_tmp = atan(number1);
      push_stack_num(pst_num, number_tmp);
    } else if (*token == 'q') {
      if (is_empty_stack_num(pst_num)) {
        number1 = pop_stack_num(pst_num);
      } else {
        error = FAILURE;
      }
      number_tmp = sqrt(number1);
      push_stack_num(pst_num, number_tmp);
    } else if (*token == 'g') {
      if (is_empty_stack_num(pst_num)) {
        number1 = pop_stack_num(pst_num);
      } else {
        error = FAILURE;
      }
      number_tmp = log10(number1);
      push_stack_num(pst_num, number_tmp);
    } else if (*token == 'n') {
      if (is_empty_stack_num(pst_num)) {
        number1 = pop_stack_num(pst_num);
      } else {
        error = FAILURE;
      }
      number_tmp = log(number1);
      push_stack_num(pst_num, number_tmp);
    } else {
      if (*token == 'x') {
        number_tmp = x;
        push_stack_num(pst_num, number_tmp);
      } else {
        number_tmp = strtod(token, NULL);
        push_stack_num(pst_num, number_tmp);
      }
    }
    token = strtok_r(NULL, " ", &save_ptr);
  }
  if (error == SUCCESS) {
    *result = pop_stack_num(pst_num);
  }

  return error;
}
