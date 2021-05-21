#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<conio.h>

void SignUp_LogIn(char ch){
     char username[20], password[20], scannedUsername[20], scannedPassword[20], c, found = '0';
     FILE *adminFile;
     int i = 0;
     if(ch == 'S'){
          printf("Username: ");
          scanf("%s", username);
          adminFile = fopen("LogInSignUpDatabase.txt", "r");
          while(fscanf(adminFile, "%s %s\n", scannedUsername, scannedPassword) != EOF){
               if(strcmp(scannedUsername, username) == 0){
                    found = '1';
                    printf("Username already taken\nProgram Exiting...\n");
                    Sleep(1000);
                    exit(0);
               }
          }

          if(found == '0'){
               printf("Set Password: ");
               while(i < 20){
                    password[i] = getch();
                    c = password[i];
                    if(c == 13) break; // 13 is the ASCII value of \n, this takes input untill the user clicks enter key
                    else printf("*"); // If not enter key, to hide password we print "*"
                    i++;
               }
               password[i] = '\0';
               printf("\n");
          }

          fclose(adminFile);
          adminFile = fopen("LogInSignUpDatabase.txt" , "a");
          fprintf(adminFile, "%s %s\n", username, password);
          fclose(adminFile);
          printf("Account Created Successfully\n");
     }

     else{
          printf("Username: ");
          scanf("%s", username);
          printf("Password: ");
          while(i < 20){
               password[i] = getch();
               c = password[i];
               if(c == 13) break;
               else printf("*");
               i++;
          }
          password[i] = '\0';
          printf("\n");
          adminFile = fopen("LogInSignUpDatabase.txt", "r");
          while(fscanf(adminFile, "%s %s\n", scannedUsername, scannedPassword) != EOF){
               if((strcmp(scannedUsername, username)) == 0 && strcmp(scannedPassword, password) == 0)
               {
                    found = '1';
                    printf("Logged In Successfully\n");
                    break;
               }
          }
          fclose(adminFile);
          if(found == '0')
          {
               printf("No User with the Given Credentials\nProgram Exiting...\n");
               Sleep(1000);
               exit(0);
          }
     }
}