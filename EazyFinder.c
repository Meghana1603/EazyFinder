#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#include<ctype.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#define max_num_of_characters 20
#define noOfPlaces sizeof(places)/sizeof(*places)
#define noOfVehicles 5
     
/*
     Take Places from file
     Displaying Map of our Services on user interest
     Discounts on prices
     Traffic
     Checking Availability of Vehicles based on booking time
     Add services for other places too (Bengaluru, Chennai.....)
     Print Bill
*/

char SignUp_LogIn(char ch);
void connect_places(int src, int dest, int distance);
void formCity();
void location_check(char* source, char* destination);
void check_for_case(char* source, char* destination, int source_index, int destination_index, int case_);
void change_location(char source[], char destination[], int case_);
int SingleSourceShortestPath(int source_index, int destination_index, int case_);
void printRoute(int source_index, int destination_index, int shortestPath[], int path[], int case_);
void EazyFinder();

// Add-Ons
void displayMap();
void modeOfTransportBasedOnTraffic(int k, char route[][k]);

//Take values from file
char places[][max_num_of_characters]={"lbnagar", "kothapet", "ameerpet", "chaithanyapuri", "vanasthalipuram"};
char vehicles[][6] = {"Bus", "Bike", "Auto", "Metro", "Cab"};
int cost_per_km[] = {5, 10, 20, 30, 50}, metro[noOfPlaces] = {1, 0, 1, 0, 1};
int city_adj_mat[noOfPlaces][noOfPlaces];

// Preparing the Adjacency Matrix
void connect_places(int source, int destinsation, int distance){
        city_adj_mat[source][destinsation] = city_adj_mat[destinsation][source] = distance;
}

void formCity(){
     // Connections of Cities will be done here
     connect_places(0, 1, 10);
	connect_places(0, 3, 30);
	connect_places(0, 4, 100);
	connect_places(1, 2, 50);
	connect_places(2, 3, 20);
	connect_places(2, 4, 10);
	connect_places(3, 4, 60);
}

typedef struct mode_of_transport{
          char source[max_num_of_characters], destination[max_num_of_characters], mst[6];
          int cost;
} transport;

void generate_bill(transport mst_array[], int k){
     int i, total_cost = 0;
     printf("Mode of Transport | From | To | Price\n");
     for(i = k-2 ; i >= 0 ; i--){
          printf("%-20s %-20s -> %-20s: %d\n", mst_array[i].mst, mst_array[i].source, mst_array[i].destination, mst_array[i].cost);
          total_cost += mst_array[i].cost;
     }
     printf("Total Cost: %d\n", total_cost);
}

void modeOfTransportBasedOnTraffic(int k, char route[noOfPlaces][k]){
     int i, j, id;
     char trafficChoice;
     float traffic[k];
     int source_index, destination_index;
     transport mst_array[k-1];

     printf("Want to Check the Traffic [Y/N]: ");
     scanf(" %c", &trafficChoice);
     if(tolower(trafficChoice) == 'y'){
          srand(time(0));
          printf("\n\n");
          for(i = k ; i >= 0 ; i--){
               printf("%s ", route[i]);
          }
          printf("\n\n");
          for(i = k ; i >= 0 ; i--){
               printf("%-20s: ", route[i]);
               traffic[i] = (float)rand()/RAND_MAX;
               if(traffic[i] == 0) printf("No Traffic");
               else if(traffic[i] > 0 && traffic[i] <= 0.5) printf("Moderate Traffic");
               else if(traffic[i] > 0.5 && traffic[i] <= 1) printf("Heavy Traffic");
               printf("\n");
          }

          // Display Cost Per Vehicle Table
          printf("\nCost Per Kilometer of Vehicles Available:\n");
          printf("Id \t Vehicle \t Price\n");
		for (i = 0; i < 5; i++){ // 5 Vehicles
			printf("%d \t %s \t\t %d\n", i + 1, vehicles[i], cost_per_km[i]);
          }

          for(i = k ; i > 0 ; i--){
               if(traffic[i] == 0){
                    printf("The route is Clear from %s to %s\n", route[i], route[i-1]);
               } else if(traffic[i] > 0 && traffic[i] <= 0.5){
                    printf("Their is Moderate Traffic from %s to %s\n", route[i], route[i-1]);
               } else if(traffic[i] > 0.5 && traffic[i] <= 1){
                    printf("The route is Clear from %s to %s. Choose a Better Transport\n", route[i], route[i-1]);
               }
               printf("Enter the ID of Mode of Transport you Prefer: ");
               scanf("%d", &id);
               while(id == 4 && metro[id-1] == 0){
                    printf("Metro not Available at %s", route[i]);
                    printf("Please Select another mode of transport: ");
                    scanf("%d", &id);
               }
               strcpy(mst_array[i].source, route[i]);
               strcpy(mst_array[i].destination, route[i-1]);
               strcpy(mst_array[i].mst, vehicles[id-1]);
               for(j = 0 ; j < noOfPlaces ; j++){
                    if(strcmp(places[j], route[i]) == 0) source_index = j;
                    if(strcmp(places[j], route[i-1]) == 0) destination_index = j;
               }
               mst_array[i].cost = (SingleSourceShortestPath(source_index, destination_index, 2))*cost_per_km[id-1];
          }

          printf("Your Bill:\n");
          generate_bill(mst_array, k);
     }
}

void printRoute(int source_index, int destination_index, int shortestPath[], int path[], int case_){
     int i, j, k;
     char route[noOfPlaces][max_num_of_characters], trafficChoice;
     j = destination_index;
     strcpy(route[0], places[destination_index]);
     k = 1;
     while(path[j] != source_index){
          strcpy(route[k], places[path[j]]);
          j = path[j];
          k++;
     }
     strcpy(route[k], places[source_index]);
     float traffic[k];
     
     // Display the Path
     printf("Route: ");
     for(i = k ; i >= 0 ; i--){
          printf("%s ", route[i]);
          if(i != 0) printf("->");
     }
     printf("\nTotal Distance: %d\n", shortestPath[destination_index]);
     if(case_ != 0)
          modeOfTransportBasedOnTraffic(k, route); 
}

int SingleSourceShortestPath(int source_index, int destination_index, int case_){
     int i, j, k, shortestPath[noOfPlaces], visited[noOfPlaces], path[noOfPlaces], min_dist, min_dist_vertex;
     
     // Initializations
     for(i = 0 ; i < noOfPlaces ; i++){
          if(city_adj_mat[source_index][i])
            shortestPath[i] = city_adj_mat[source_index][i];
          else
            shortestPath[i] = INT_MAX;
          visited[i] = 0;
          path[i] = source_index;
     }
     shortestPath[source_index] = 0;

     for(i = 0 ; i < noOfPlaces ; i++){
          min_dist = INT_MAX;
          for(k = 0 ; k < noOfPlaces ; k++){
               // Select the vertices that are unvisited and are nearer to sourceVertex
               if(visited[k] == 0 && min_dist >= shortestPath[k]){
                    min_dist = shortestPath[k];
                    min_dist_vertex = k;
               }
          }

          // min_dist_vertex is at minimum distance to sourceVertex. So put it in solution
          visited[min_dist_vertex] = 1;

          for (j = 0; j < noOfPlaces; j++){
               if(!visited[j] && city_adj_mat[min_dist_vertex][j] && shortestPath[min_dist_vertex] != INT_MAX && 
                  shortestPath[j] > shortestPath[min_dist_vertex] + city_adj_mat[min_dist_vertex][j]){
                    shortestPath[j] = shortestPath[min_dist_vertex] + city_adj_mat[min_dist_vertex][j];
                    path[j] = min_dist_vertex;
               }
          }
    }
     if(case_ == 0){
          for (i = 0; i < noOfPlaces; i++){
               if(i != source_index)
                    printRoute(source_index, i, shortestPath, path, case_);
          }
     } else if(case_ == 1) {
          printRoute(source_index, destination_index, shortestPath, path, case_);
     } else if(case_ == 2){
          return shortestPath[destination_index];
     }
     return;
}

void change_location(char *source, char *destination, int case_){
     char choice;
     int i, j, distance;
     printf("Want to Change the Location(s) (Type 'N' to exit) [Y/N]: ");
     scanf(" %c", &choice);
     if(choice == 'Y' || choice == 'y'){
          if(case_ == 1) {
               printf("Enter the Source Location Again: ");
               scanf("%s[^\n]",source);
               printf("Enter the Destination Again: ");
               scanf("%s[^\n]",destination);
          } else if(case_ == 2) {
               printf("Enter the Source Location Again: ");
               scanf("%s[^\n]",source);
          } else if(case_ == 3) {
               printf("Enter the Destination Again: ");
               scanf("%s[^\n]",destination);
          }
          // Check the location again after re-entering
          location_check(source, destination); // This calls check_for_case
     } else {
          printf("Have A Great Day Ahead :)\n");
          exit(0);
     }
}

/* 
     Checks for the case based on source and destination:
     case 1: source and destination are wrong
     case 2: source is wrong
     case 3: destination is wrong
     case 4: source and destination are correct
*/
void check_for_case(char* source, char* destination, int source_index, int destination_index, int case_){
     if(case_ == 4){
          SingleSourceShortestPath(source_index, destination_index, 1);
     } else if(case_ == 1) {
          printf("Sorry! Our Services are not available at %s and %s\nOr you have entered wrong locations. Please recheck the spellings\n", source, destination);
     } else if(case_ == 2) {
          printf("Sorry! Our Services are not available at %s\n", source);
     } else if(case_ == 3){
          printf("Sorry! We do not serve from %s to %s\nOr You have eneterd a wrong Destination\n", source, destination);
          printf("\nYou can Reach the following destinations from %s:\n", places[source_index]);
          SingleSourceShortestPath(source_index, destination_index, 0);
     }
     if(case_ != 4){
          change_location(source, destination, case_);
     }
}

void location_check(char *source, char *destination){
     int i, source_index = -1, destination_index = -1, case_;

     // Checking for the index of source in places array
     for(i = 0 ; i < noOfPlaces ; i++){
          if(strcmp(source, places[i]) == 0){
               source_index = i;
               break;
          }
     }

     // Checking for the index of destination in places array
     for(i = 0 ; i < noOfPlaces ; i++){
          if(strcmp(destination, places[i]) == 0){
               destination_index = i;
               break;
          }
     }

     if (source_index == -1 && destination_index == -1) case_ = 1;
     else if (source_index == -1) case_ = 2;
     else if (destination_index == -1) case_ = 3;
     else case_ = 4;
     check_for_case(source, destination, source_index, destination_index, case_);
}

void EazyFinder(){
     char source[max_num_of_characters], destination[max_num_of_characters];
     int i, j;
     printf("Enter the Starting Point: ");
     scanf("%s[^\n]",source);
     printf("Enter the Destination: ");
     scanf("%s[^\n]",destination);
     strcpy(source, strlwr(source));
     strcpy(destination, strlwr(destination));
     
     location_check(source, destination);
}

// Add-Ons
void check_traffic(){

}

void displayMap(){
     int i, j;
     // printf("From\t\t\tTo\t\tCost\n");
     for(i = 0 ; i <  noOfPlaces ; i++){
          for(j = 0 ; j <  noOfPlaces ; j++){
               if(city_adj_mat[i][j]){
                    printf("%-20s %-20s %-20d\n", places[i], places[j], city_adj_mat[i][j]);
               }
          }
          printf("\n");
     }
}

// Signup and Login Code
/*char SignUp_LogIn(char ch){
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
                    printf("Username already taken\n");
                    return '0';
               }
          }

          if(found == '0'){
               printf("Set Password: ");
               while(i < 20){
                    password[i] = getch();
                    c = password[i];
                    if(c == 13) break;
                    else printf("*");
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
          return '1';
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
}*/

void main()
{
     /*char returned, choice;*/
     int i, j;
     char mapChoice;
     /*do{
          returned = callSignupLogin();
          if(returned == '1'){*/
               for(i = 0 ; i < noOfPlaces ; i++)
                    for(j = 0 ; j < noOfPlaces ; j++)
                         city_adj_mat[i][j] = 0; // Initializing the adj_mat
               formCity();    // Connects the Places in form of a graph and forms a city
               printf("Want To See the Map [Y/N]: ");
               scanf(" %c", &mapChoice);
               if(tolower(mapChoice) == 'y'){
                    printf("\nMap:\n");
                    displayMap();
               }
               printf("\n");
               EazyFinder();
               /*choice = 'N';*/
          /*} else {
               printf("Want to Try Again [Y/N]: ");
               scanf(" %c", &choice); // If 'Y' the user will get a chance to again signup/login
          }
          if(choice == 'N' || choice == 'n')
               printf("Have A Great Day Ahead! :)\n");
     }while(choice == 'Y' || choice == 'y');*/
}
