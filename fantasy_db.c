/*Source Codes:
Referenced Code from previous courses, including CS374 and PCC's CS162. All code is my own.
Referenced code for strrchr(): https://www.tutorialspoint.com/c_standard_library/c_function_strrchr.htm
Adapted Code for random numbers in range: https://www.geeksforgeeks.org/generating-random-number-range-c/
Referenced for popular character personality types: https://www.personality-database.com/profile?pid=2
*/

/*Required headers*/
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>
#include <stdbool.h>
#include <time.h>

/*Stores characters*/
struct fantasy{
    char* name;
    char* gender;
    char* species;
    char* weapon;
    char* personality;
    char* hair;
    char* eye;
    struct fantasy *next;
};
typedef struct fantasy Record;

/*Functions*/
void browsePersonalities(void);
void browseCharacters(Record* head);
void processFile(Record** head, char* filePath);
void browseSpecies();



int main(void) {
    char *filePath = malloc(256 * sizeof(char));
    int option = 0;
    char warning[1];
    bool ifTrue = false;
    int pSize = 0;
    char *line = NULL;
    int lineTrack = 0;
    size_t len = 0;
    size_t line_count = 0;
    char *currLine = NULL; 
    char *token = NULL;
    char *endptr = NULL;
    Record* head = NULL;
    Record* temp;
    Record* current;

strcpy(filePath, "character_db.csv");
//Welcome Message
    printf("Welcome to my Character Generator!\n\n");
    printf("I am going to help you create your own characters!\n\n");
    printf("You will be given the options to manually create a fantasy character.\n\n");
    printf("You can also search by personality and species, or have us create one for you!\n");

//Main Menu


    do{
        printf("\nTo begin, enter the correct number option you wish to carry out.\n Typing '8' will exit the program!\n\n");
        printf("\n1. Add New Character\n");
        printf("2. Randomly Generate Character\n");
        printf("3. Browse Personality Types\n");
        printf("4. Browse Different Species\n");
        printf("5. Browse All Characters\n");
        printf("6. Search Matching Personalities\n");
        printf("7. Search Matching Species\n");
        printf("8. EXIT PROGRAM\n");

        
        printf("\nEnter Option: ");
        scanf("%d", &option);

        //validating input
        while(option < 1 || option > 8 )
            {
                printf("\nYou entered an incorrect option.\n");
                printf("\nEnter Option: ");
                scanf("%d", &option);
            } 
        switch(option){

            case 1:
            
            break;
            
            case 2:
            
            break;

            case 3:

                browsePersonalities();
            break;

            case 4:
                browseSpecies();

            break;

            case 5: ;
                
                // Getting file line amount for memmory allocation
                FILE *characterFile = fopen(filePath, "r");

                while(getline(&line, &len, characterFile) != -1)
                {
                //printf("%s", currLine);
                line_count++;
                }
                line_count--;
                pSize = line_count;
                // Free the memory allocated by getline for currLine
                free(line);
                // Close the file
                fclose(characterFile);

                //Processing file into our struct.  
                //Open the file to read the data and store it in our struct
                characterFile = fopen(filePath, "r");
                    // Read the file line by line
                
                while(getline(&currLine, &len, characterFile) != -1)
                    {  
                    
                    //ignoring first line that contains headers
                    if(lineTrack == 0){
                            lineTrack++;
                            continue;
                    }  
                    
                    temp = (Record *) malloc(sizeof(Record));
                    token = strtok(currLine, ",");
                    //store the length of our token in size, to dynamically allocate
                    //1st token is our name
                    temp->name= calloc(strlen(token) + 1, sizeof(char)); 
                    if (temp->name != NULL) {
                        strcpy(temp->name, token);     
                    }
                    //2nd token is our gender
                    token = strtok(NULL, ",");
                    temp->gender = calloc(strlen(token) + 1, sizeof(char)); 
                    if (temp->gender != NULL) {
                        strcpy(temp->gender, token);       
                    }
                    //3rd token is our species
                    token = strtok(NULL, ",");
                    temp->species = calloc(strlen(token) + 1, sizeof(char)); 
                    if (temp->species != NULL) {
                        strcpy(temp->species, token);       
                    }
                    //4th token is our weapon
                    token = strtok(NULL, ",");
                    temp->weapon = calloc(strlen(token) + 1, sizeof(char)); 
                    if (temp->weapon != NULL) {
                        strcpy(temp->weapon, token);       
                    } 
                    //5th token is our personality
                    token = strtok(NULL, ",");
                    temp->personality = calloc(strlen(token) + 1, sizeof(char)); 
                    if (temp->personality != NULL) {
                        strcpy(temp->personality, token);       
                    } 
                    //6th token is our hair color
                    token = strtok(NULL, ",");
                    temp->hair = calloc(strlen(token) + 1, sizeof(char)); 
                    if (temp->hair != NULL) {
                        strcpy(temp->hair, token);       
                    } 
                    //6th token is our eye color
                    token = strtok(NULL, ",");
                    temp->eye = calloc(strlen(token) + 1, sizeof(char)); 
                    if (temp->eye != NULL) {
                        strcpy(temp->eye, token);       
                    } 

                    temp->next = NULL;

                    
                    if (head == NULL){
                        head = temp;
                    }
                    else{
                        current = head;
                        while (current->next != NULL){
                            current = current->next;
                        }
                        current->next = temp;
                    }  

                }    
                // Free the memory allocated by getline for currLine
                free(currLine);
                // Close the file
                fclose(characterFile);                
                browseCharacters(head);

                break;

            case 6:

            break;

            case 7:

            break;

            case 8: 

                printf("Warning: Are you sure you want to quit?! Quitting will delete any unsaved prograss! (Y/N): ");
                scanf("%s", warning);
                if(strcmp(warning, "y") == 0 || strcmp(warning, "y") == 0)  {
                    ifTrue = true;
                }
            break;

        }
    } while (option!=8 || (!ifTrue));

}

/*Function Lists static data regarding personality types.
Might change format later to hide all the details unless
user requests it.
Paramaters: None
Returns: None*/
void browsePersonalities(void){
    char option[10];

    printf("Personality Types: \n\n");
    printf("\nINTJ: “The Architect”- Strategic, Analytical, Independent\n");
    printf("INTP: “The Logician”- Logical, Inventive, Intellectual \n");
    printf("INFJ: “The Advocate”- Intuitive, Creative, Idealisti\n");
    printf("INFP: “Mediator”- Loyal, Driven, Empathetic\n");
    printf("ISTJ: “Logistician”- Responsible, Hardworking, Reserved\n");
    printf("ISFJ: “The Protector”- Gentle, Warm, Helpful\n");
    printf("ISTP: “The Crafter”- Practical, Action-Oriented, Adventurous\n");
    printf("ISFP: “The Artist”- Sensitive, Flexible, Gentle\n");
    printf("ENTJ: “The Commander”- Efficient, Outgoing, Ambitious\n");
    printf("ENTP: “The Innovator”- Inventive, Versatile, Inquisitive\n");
    printf("ENFJ: “The Protagonist”- Organized, Diplomatic, Responsible\n");
    printf("ENFP: “The Campaigner” - Energetic, Spontaneous, Playful\n");
    printf("ESTJ: “The Supervisor”- Efficient, Dependable, Realistic\n");
    printf("ESFJ: “The Caregiver”- Friendly, Helpful, Organized\n");
    printf("ESTP: “Adventurer”- Curious, Problem-Solver, Spontaneous\n");
    printf("ESFP: “The Entertainer”- Tactful, Playful, Friendly\n");
    
    printf("\nEnter 'exit' to go back to main menu: ");
    scanf("%s", option);
    while(strcmp(option, "exit") !=0) {
        printf("\nInocorrect option, enter 'exit' to go back to main menu: ");
        scanf("%s", option);
    }
}


 
      

/*Function reads off linked list of characters
Only names are displayed, then user has option
to see more details of each character.
Prereqs: "character_db.csv" must be processed
prior to calling this function.*/
void browseCharacters(Record * head){
    Record* temp = head;
    char details[30];
    bool ifFound = false;
    printf("Now Displaying All Characters Saved\n\n");
     
    while(temp != NULL){
        printf("%s\n", temp->name);
        temp = temp->next;
    }
    do{

        temp = head;
        printf("\nEnter name to show more details, or 'quit' to exit to main menu: ");
        scanf("%s", details);
        while(temp!=NULL){
            ifFound = false;
            if(strcmp(details, temp->name) == 0){
                printf("\n\nName: %s Gender: %s Species: %s Weapon: %s Personality: %s Hair Color: %s Eye Color: %s\n", 
                temp->name, temp->gender, temp->species, temp->weapon, temp->personality, temp->hair, temp->eye);
                ifFound = true;
            }
            else if(strcmp(details, "quit") ==0){
                break;
            }
            temp = temp->next;
        }
        if(ifFound){
            printf("Character not found, try again.");
        }
    }while(strcmp(details, "quit") != 0);
}

void browseSpecies(){
    char option[10];
    
    printf("Personality Types: \n\n");
    printf("\nElf :folk tale creature who is a small, elusive figure with pointy ears and magical abilities.\n");
    printf("\nDwarf:  mythical race of short, stocky humanlike creatures who are generally skilled in mining and metalworking.\n");
    printf("\nFae: A beautiful, supernatural being often depicted as tricksters.\n");
    printf("\nHuman: Average in appearance, can be reckless and brutal.\n");
    printf("\nWerewolf: Mythical creature capable of transforming into a wolf and likely aggressive.\n");
    printf("\nWizard: Being capable of wielding magic and have an affinity for mythical creatures. \n");
    printf("\nVampire: Undead humanoids who have pale skin, fangs, and an affinity for human blood\n");

    printf("\nEnter 'exit' to go back to main menu: ");
    scanf("%s", option);
    while(strcmp(option, "exit") !=0) {
        printf("\nInocorrect option, enter 'exit' to go back to main menu: ");
        scanf("%s", option);
    }


}
