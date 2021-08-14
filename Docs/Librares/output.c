#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "output.h"

#ifndef MAX_FILE_NAME_LEN
#define MAX_FILE_NAME_LEN 31
#endif

FILE * outputHandling(int arg_num, char * output){
  if (arg_num == 5) {   // if arg_num == 5 then an Output File was specified
    char output_path[38] = "Output/";
    char c = output[0];
    int counter = 0;
    while (c != '\0'){
      output_path[counter + 7] = output[counter];
      c = output[counter++];
    }

    // File's name check
    if(checkOutputName(output_path)){
      printf("ERROR: invalid output file name\n");
      return NULL;
    }

    // Check if the file's name has the .csv extention
    char extention[5] = ".csv";
    int flag = 1, j = 0, i = (strlen(output_path) - 4);
    if (i < 0) {flag = 0;}
    while(i < strlen(output_path) && flag != 0){
      if(output[i] != extention[j]){flag = 0;}
      i++; j++;
    }

    if(flag){
      return fopen(output_path, "w");
    } else {
      printf("\nThe .csv extention will be added to \"%s\"\n", output_path);
      int len = (strlen(output_path) + strlen(extention) + 1);
      char new_out[len];
      strcpy(new_out, output_path);
      int j = 0, i = strlen(output_path);
      while(i < len) {
        new_out[i] = extention[j];
        i++; j++;
      }
      printf("\nOUTPUT FILE: \"%s\"\n", new_out);
      return fopen(new_out, "w");
    }
  } else {
    printf("\nOUTPUT FILE: \"converted.csv\"\n");
    return fopen("Output/converted.csv", "w");
  }
}


// The checkOutputName function checks if the output file's name is legal
int checkOutputName(char *output){

  // Check if the file's name is too long
  if (strlen(output) > MAX_FILE_NAME_LEN) {return 1;}

  // Check if the file's name starts or ends with a blank space
  if (output[0] == ' ' || output[strlen(output) - 1] == ' ') {
    return 1;
  }

  // Check if the file's name contains crl chars or punctuation chars
  int flag = 0, i = 0, numOfPoints = 0, numOfSlashes = 0;
  while(i < strlen(output)) {
    if(ispunct((unsigned char)output[i])){flag = 1;}
    if(iscntrl((unsigned char)output[i])){flag = 1;}
    if (output[i] == '/' && numOfSlashes == 0){
      flag = 0;
      numOfSlashes++;
    }
    if (output[i] == '_') {
      flag = 0;
    } else if (output[i] == '.') {
      flag = 0;
      numOfPoints++;
    }
    i++;
  }

  if (numOfPoints == strlen(output)) {
    flag = 1;
  }

  return flag;
}
