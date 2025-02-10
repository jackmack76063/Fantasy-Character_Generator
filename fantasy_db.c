/*Source Codes:
Referenced Code from previous courses, including CS374 and PCC's CS162. All code is my own.
Referenced code for strrchr(): https://www.tutorialspoint.com/c_standard_library/c_function_strrchr.htm
Adapted Code for random numbers in range: https://www.geeksforgeeks.org/generating-random-number-range-c/
Referenced for popular character personality types: https://www.personality-database.com/profile?pid=2
*/

void browsePersonalities(void);

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>
#include <stdbool.h>
struct fantasy{
    char* name;
    char* gender;
    char* species;
    char* personality;
    char* hair;
    char* eye;
    struct movie *next;
};
typedef struct fantasy Record;

int main(void) {
    int option = 0;
    char warning[1];
    bool ifTrue = false;

//Welcome Message
    printf("Welcome to my Character Generator!\n\n");
    printf("I am going to help you create your own characters!\n\n");
    printf("You will be given the options to manually create a fantasy character.\n\n");
    printf("You can also search by personality and species, or have us create one for you!\n");

//Main Menu

    printf("\nTo begin, enter the correct number option you wish to carry out.\n\n");

    do{
        printf("1. Add New Character\n");
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

            break;

            case 5:

            break;

            case 6:

            break;

            case 7:

            break;

            case 8: 

                printf("Warning: Are you sure you want to quit?! (Y/N): ");
                scanf("%s", warning);
                if(strcmp(warning, "y") == 0 || strcmp(warning, "y") == 0)  {
                    ifTrue = true;
                }
            break;

        }
    } while (option!=8 || (!ifTrue));

}

void browsePersonalities(void){

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

}