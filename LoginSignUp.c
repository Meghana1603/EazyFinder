#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<conio.h>

// Signup and Login Code
char SignUp_LogIn(char ch){
     const int maxPasswordLength = 16;
     char username[20], password[maxPasswordLength+1], scannedUsername[20], scannedPassword[maxPasswordLength+1], c, found = '0';
     FILE *adminFile;
     int i = 0;
     if(ch == 'S'){
          do{
               printf("Username: ");
               scanf("%s", username);
               adminFile = fopen("LogInSignUpDatabase.txt", "r");
               while(fscanf(adminFile, "%s %s\n", scannedUsername, scannedPassword) != EOF){
                    if(strcmp(scannedUsername, username) == 0){
                         found = '1';
                         printf("Username already taken\n");
                         break;
                    } else {
                         found = '0';
                    }
               }
          } while(found != '0'); // Only comes out when the username is a different one

          printf("Set Password: ");
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
          printf("\n");

          fclose(adminFile);
          adminFile = fopen("LogInSignUpDatabase.txt" , "a");
          fprintf(adminFile, "%s %s\n", username, password);
          fclose(adminFile);
          printf("Account Created Successfully\n");
          return '1';
     }

     else{
          printf("Username: ");
          scanf("%s", username);
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
          printf("\n");
          adminFile = fopen("LogInSignUpDatabase.txt", "r");
          while(fscanf(adminFile, "%s %s\n", scannedUsername, scannedPassword) != EOF){
               if((strcmp(scannedUsername, username)) == 0 && strcmp(scannedPassword, password) == 0){
                    found = '1';
                    printf("Logged In Successfully\n");
                    return '1';
               }
          }
          fclose(adminFile);
          if(found == '0'){
               printf("No User with the Given Credentials\n");
               return '0';
          }
     }
}

char callSignupLogin(){
     char SLChoice[7], ret;
     printf("SignUp or LogIn: ");
     scanf("%s",SLChoice);
     if(strcmp(strlwr(SLChoice), "signup") == 0)
          return SignUp_LogIn('S');
     return SignUp_LogIn('L');
}

void main()
{
     char returned, choice;
     do{
          returned = callSignupLogin();
          if(returned == '1'){
               // Write your Code Here
               printf("Welcome User!"); // Dummy Sentence
          } else {
               printf("Want to Try Again [Y/N]? ");
               scanf(" %c", &choice); // If 'Y' the user will get a chance to again signup/login
          }
          if(choice == 'N' || choice == 'n')
               printf("Have A Great Day Ahead! :)\n");
     }while(choice == 'Y' || choice == 'y');
}
