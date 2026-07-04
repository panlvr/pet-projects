#include "s21_cat.h"

#include <string.h>

int main(int argc, char* argv[]) {
  // initialize flags
  struct flags flags;
  flags.b = 0;
  flags.e = 0;
  flags.n = 0;
  flags.s = 0;
  flags.t = 0;
  flags.v = 0;
  flags.E = 0;
  flags.T = 0;
  // loop over arguments to read the files
  int is_new_line = 1;
  int line_number = 1;
  int empty_line_seen = 0;
  int flag = 0;
  for (int i = 1; i < argc; i++) {
    // check if the argument is a flag
    if (argv[i][0] == '-') {
      if (parse_flags(argv[i], &flags, &flag) != 0) return 1;
    } else {
      input(argv[i], &flags, &is_new_line, &line_number, &empty_line_seen);
    }
  }
  return 0;
}

int char_flags(char* input, struct flags* flags) {
  // iterate until we run out of flags
  int flag = 0;
  int len = strlen(input);
  for (int i = 1; i < len; i++) {
    int recognized = 0;
    if (input[i] == 's') {
      flags->s = 1;
      recognized = 1;
    }
    if (input[i] == 'e') {
      flags->e = 1;
      flags->v = 1;
      recognized = 1;
    }
    if (input[i] == 't') {
      flags->t = 1;
      flags->v = 1;
      recognized = 1;
    }
    if (input[i] == 'n') {
      flags->n = 1;
      recognized = 1;
    }
    if (input[i] == 'b') {
      flags->b = 1;
      recognized = 1;
    }
    if (input[i] == 'E') {
      flags->E = 1;
      recognized = 1;
    }
    if (input[i] == 'T') {
      flags->T = 1;
      recognized = 1;
    }
    if (input[i] == 'v') {
      flags->v = 1;
      recognized = 1;
    }
    if (!recognized) {
      flag = 1;
    }
  }
  return flag;
}

int string_flags(char* input, struct flags* flags) {
  int flag = 0;
  int recognized = 0;
  if (strcmp(input, "--squeeze-blank") == 0) {
    flags->s = 1;
    recognized = 1;
  }
  if (strcmp(input, "--number") == 0) {
    flags->n = 1;
    recognized = 1;
  }
  if (strcmp(input, "--number-nonblank") == 0) {
    flags->b = 1;
    flags->n = 0;
    recognized = 1;
  }
  if (!recognized) {
    flag = 1;
  }
  return flag;
}

int parse_flags(char* input, struct flags* flags, int* flag) {
  if (input[1] != '-') {
    // parse character flags
    int result = char_flags(input, flags);
    if (result == 1) {
      *flag = 1;
    }
  } else {
    // parse  flags
    int res = string_flags(input, flags);
    if (res == 1) {
      *flag = 1;
    }
  }
  if (*flag == 1) {
    printf("Flag doesn't exist, please enter valid flag");
    return 1;
  }
  return 0;
}

void input(char* file, struct flags* flags, int* is_new_line, int* line_number,
           int* empty_line_seen) {
  FILE* fptr = fopen(file, "r");
  if (fptr != NULL) {
    process_file(flags, fptr, is_new_line, line_number, empty_line_seen);
    fclose(fptr);
  } else {
    printf("Couldn't open file %s", file);
  }
}

void process_file(struct flags* flags, FILE* fptr, int* is_new_line,
                  int* line_number, int* empty_line_seen) {
  int ch;
  while ((ch = fgetc(fptr)) != EOF) {
    int original_ch = ch;
    int allowed = 1;
    if (*is_new_line) {
      is_allowed(flags, &original_ch, empty_line_seen, &allowed);
      if (allowed) {
        numbering(flags, &original_ch, line_number);
      }
    }
    if (allowed) {
      if (flags->e || flags->t || flags->v) {
        flag_v(&ch);
      }
      if (flags->e || flags->E) {
        flag_e(&ch);
      }
      if (flags->t || flags->T) {
        flag_t(&ch);
      }
      putchar(ch);
    }
    if (original_ch == '\n') {
      *is_new_line = 1;
    } else {
      *is_new_line = 0;
    }
  }
}

void is_allowed(struct flags* flags, int* ch, int* empty_line_seen,
                int* allowed) {
  if (flags->s && *ch == '\n') {
    if (*empty_line_seen == 0) {
      *empty_line_seen = 1;
    } else {
      *allowed = 0;
    }
  } else if (*ch != '\n') {
    *empty_line_seen = 0;
  }
}

void numbering(struct flags* flags, int* ch, int* line_number) {
  if (flags->b) {
    if (*ch != '\n') {
      printf("%6i\t", *line_number);
      (*line_number)++;
    }
  } else if (flags->n) {
    printf("%6i\t", *line_number);
    (*line_number)++;
  }
}

void flag_v(int* ch) {
  if (*ch < 32 && *ch != 9 && *ch != 10) {
    putchar('^');
    *ch = *ch + 64;
  } else if (*ch == 127) {
    putchar('^');
    *ch = *ch - 64;
  }
}

void flag_e(int* ch) {
  if (*ch == '\n') {
    putchar('$');
  }
}

void flag_t(int* ch) {
  if (*ch == '\t') {
    putchar('^');
    *ch = *ch + 64;
  }
}