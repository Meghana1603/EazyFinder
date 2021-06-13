#include<stdio.h>
#include<conio.h>
#include<string.h>

void main()
{
     const int maxPasswordLength = 16;
     char password[maxPasswordLength + 1]; // 1 more space for '\0'
     char ch;
     int i = 0;
     printf("Password: ");
     
     while(1){
          ch = getch();
          if(ch == 13){ // if enter key
               break;
          } else if(ch == 32 || ch == 9){ // if space or tab key
               continue;
          } else if(ch == 8){ // if backspace
               if(i > 0){
                    i--;
                    password[i] = '\0';
                    printf("\b \b");
               }
          } else{
               if(i < maxPasswordLength){
                    password[i] = ch;
                    i++;
                    printf("*");
               }
          }
     }
     password[i] = '\0';

     printf("\n%s", password);
}
