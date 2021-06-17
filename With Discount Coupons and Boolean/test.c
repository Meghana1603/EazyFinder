#include<stdio.h>
#include<string.h>

void main()
{
     char path[100], userFileName[100], ch;
     getcwd(path, sizeof(path));
     strcat(path, "\\TransactionHistories\\");
     FILE *userFilePointer = fopen(strcat(path, "rohith.txt"), "r");
     printf("Your Transaction History:\n");
     while((ch = fgetc(userFilePointer) != EOF))
          printf("%c", ch);
     printf("\n");
     fclose(userFilePointer);
}