#include <stdio.h>
#include "errors.h"

FILE * errorHandling(int arg_num, char * input){

  if (arg_num < 4) {
    printf("ERROR: too few parameters\n");
    return NULL;
  }

  if (arg_num > 5) {
    printf("ERROR: too many parameters\n");
    return NULL;
  }

  char input_path[38] = "Input/";
  char c = input[0];
  int counter = 0;
  while (c != '\0'){
    input_path[counter + 6] = input[counter];
    c = input[counter++];
  }

  if ((fopen(input_path, "r")) == NULL) {
    printf("ERROR: failed to open file\n");
    return NULL;
  }

  printf("%s\n", input_path);
  return fopen(input_path, "r");
}
