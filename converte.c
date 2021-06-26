#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
  char c;
  char ext[5] = {'.', 'c','s','v','\0'};
  FILE *fp_in;
  FILE *fp_out;

  if ((fp_in = fopen(argv[1], "r")) == NULL) {
    printf("ERROR: failed to open file\n");
    return 1;
  }

  if (argc > 2) {
    if(strstr(argv[2], ext) != NULL){
      fp_out = fopen(argv[2], "w");
    } else {
      printf("\nThe .csv  extention will be added to \"%s\"\n", argv[2]);
      int len = (strlen(argv[2]) + strlen(ext) + 1);
      char new_out[len];
      strcpy(new_out, argv[2]);
      int j = 0;
      for (int i = strlen(argv[2]); i < len; i++) {
        new_out[i] = ext[j];
        j++;
      }
      printf("\nOUTPUT FILE: \"%s\"\n", new_out);
      fp_out = fopen(new_out, "w");
    }
  } else {
    fp_out = fopen("converted.csv", "w");
  }

  while((fscanf(fp_in, "%c", &c)) != EOF){
    if (c == ',') {
      fprintf(fp_out, "%s", ";");
    } else {
      fprintf(fp_out, "%c", c);
    }
  }

  fclose(fp_in);
  fclose(fp_out);

  printf("\nConversion Completed!\n");

  return 0;
}
