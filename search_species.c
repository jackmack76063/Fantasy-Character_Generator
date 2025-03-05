#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>
#include <zmq.h>

#define CSV_FILE "character_db.csv"

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
Record* loadCharactersFromFile(const char *filePath);
void freeList(Record *head);

int main(){
    char *filePath = malloc(256 * sizeof(char));
    const char *no_match = "No characters were found with that personality type.";
    Record *head = NULL;
    Record *temp = NULL;
    bool matchFound = false;
    char buffer[256];
    char message[256];
    strcpy(filePath, CSV_FILE);

    void *context = zmq_ctx_new();
    void *socket = zmq_socket(context, ZMQ_REP);
    if (zmq_bind(socket, "tcp://*:5558") != 0) {
        printf("Error in binding microservice to port 5558.\n");
        return -1;
    }
    //populating struct with db file
    head = loadCharactersFromFile(filePath); 
    
    while(1){

        int size = zmq_recv(socket, buffer, sizeof(buffer) - 1, 0);
        if (size > 0) {
            buffer[size] = '\0';
        }
        printf("Data Recieved: %s\n", buffer);

        //checking is client sends a quit request
        if (strcmp(buffer, "quit") == 0) {
            printf("Received 'quit' command. Shutting down...\n");
            break;
        }

        matchFound = false;
        temp = head;
        message[0] = '\0';  
        while(temp != NULL){
            if (strcmp(temp->species, buffer) == 0){
                matchFound = true;
                 // Check if we have enough space in the buffer
                if (strlen(message) + strlen(temp->name) + 2 < sizeof(message)) {
                    if (strlen(message) > 0) {
                        strcat(message, ",");  // Add a comma between names
                    }
                    strcat(message, temp->name);
                } else {
                    printf("Warning: Message buffer full, please allocate more memory.\n");
                    break;
                }
            }
            temp = temp->next;
        }

        //sending response back
        if (matchFound){
            zmq_send(socket, message, strlen(message), 0); 
        }
        else{
            zmq_send(socket, no_match, strlen(no_match), 0);  
        }
    
    } 
    zmq_close(socket);
    zmq_ctx_destroy(context);
    freeList(head);
    return 0;
}

Record* loadCharactersFromFile(const char *filePath){
    char *currLine = NULL;
    char *line = NULL;
    char *token = NULL;
    size_t len = 0;
    size_t line_count = 0;
    int lineTrack = 0;
    int pSize = 0;
    Record *head = NULL, *current = NULL, *temp = NULL;
    FILE *characterFile = fopen(filePath, "r");

    // Getting file line amount for memmory allocation
    while(getline(&line, &len, characterFile) != -1) {
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
        else {
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
    
    return head;
}

/*This function frees the memory by going through each attribute*/
void freeList(Record *head) {
    Record *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;

        free(temp->name);
        free(temp->gender);
        free(temp->species);
        free(temp->weapon);
        free(temp->personality);
        free(temp->hair);
        free(temp->eye);
        free(temp);
    }
}