// CSV TO CSV CONVERTER - by Giocrom
// version (alpha) 2.3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_FILE_NAME_LEN 31

FILE * errorHandling(int arg_num, char * input);
FILE * outputHandling(int arg_num, char * output);
int checkOutputName(char *output);
void fieldCheck(FILE *input, FILE *output, char current, char new, char c, int counter);

int main(int argc, char *argv[]){

  //argv[1] = InputFileName (i.e. "times.csv")
  //argv[2] = OutputFileName  (optional)
  //argv[3] = CurrentEncoding (i.e. ",")
  //argv[4] = WantedEncoding (i.e. ";")

  // ERROR handling
  FILE *fp_in = errorHandling(argc, argv[1]);
  if(fp_in == NULL){
    fclose(fp_in);
    return -1;
  }

  // Output File handling
  FILE *fp_out = outputHandling(argc, argv[2]);
  if(fp_out == NULL){
    fclose(fp_in);
    return -1;
  }

  char c;   // Currently analyzed char
  while((fscanf(fp_in, "%c", &c)) != EOF){
    if (c == argv[argc - 2][0]) {
        fprintf(fp_out, "%c", argv[argc - 1][0]);
    } else if (c == '"') {
      fprintf(fp_out, "\"");
      fieldCheck(fp_in, fp_out, argv[argc - 2][0], argv[argc - 1][0], c, 1);
    } else {
      fprintf(fp_out, "%c", c);
    }
  }

  fclose(fp_in);
  fclose(fp_out);

  printf("\nConversion Completed!\n");

  return 0;
}


FILE * errorHandling(int arg_num, char * input){
  if ((fopen(input, "r")) == NULL) {
    printf("ERROR: failed to open file\n");
    return NULL;
  }

  if (arg_num < 4) {
    printf("ERROR: too few parameters\n");
    return NULL;
  }

  if (arg_num > 5) {
    printf("ERROR: too many parameters\n");
    return NULL;
  }

  return fopen(input, "r");
}


FILE * outputHandling(int arg_num, char * output){
  if (arg_num == 5) {   // if arg_num == 5 then an Output File was specified

    // File's name check
    if(checkOutputName(output)){
      printf("ERROR: invalid output file name\n");
      return NULL;
    }

    // Check if the file's name has the .csv extention
    char extention[5] = ".csv";
    int flag = 1, j = 0, i = (strlen(output) - 4);
    if (i < 0) { flag = 0; }
    while(i < strlen(output) && flag != 0){
      if(output[i] != extention[j]){ flag = 0; }
      i++; j++;
    }

    if(flag){
      return fopen(output, "w");
    } else {
      printf("\nThe .csv extention will be added to \"%s\"\n", output);
      int len = (strlen(output) + strlen(extention) + 1);
      char new_out[len];
      strcpy(new_out, output);
      int j = 0, i = strlen(output);
      while(i < len) {
        new_out[i] = extention[j];
        i++; j++;
      }
      printf("\nOUTPUT FILE: \"%s\"\n", new_out);
      return fopen(new_out, "w");
    }
  } else {
    printf("\nOUTPUT FILE: \"converted.csv\"\n");
    return fopen("converted.csv", "w");
  }
}


// The checkOutputName function checks if the output file's name is legal
int checkOutputName(char *output){

  // Check if the file's name is too long
  if (strlen(output) > MAX_FILE_NAME_LEN) {return 1;}

  // Check if the file's name starts or ends with a blank space
  if ((output[0] || output[strlen(output) - 1]) == ' ') {
    return 1;
  }

  // Check if the file's name contains crl chars or punctuation chars
  int flag = 0;
  int i = 0;
  while(i < strlen(output)) {
    if(ispunct((unsigned char)output[i])){flag = 1;}
    if(iscntrl((unsigned char)output[i])){flag = 1;}
    if (output[i] == '_' || output[i] == '.') {
      flag = 0;
    }
    i++;
  }
  return flag;
}


// The fieldCheck function skips the convertion of fields enclosed by ""
void fieldCheck(FILE *input, FILE *output, char current, char new, char c, int counter){
  while ((fscanf(input, "%c", &c) != EOF) && c != current) {
    if (c == '"'){ counter++; }
    fprintf(output, "%c", c);
  }

  if (c != current) {
    return;
  }

  if ((counter % 2) == 1) {
    fprintf(output, "%c", current);
    fieldCheck(input, output, current, new, c, counter);
  } else {
    fprintf(output, "%c", new);
    return;
  }
}
