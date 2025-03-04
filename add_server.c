#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zmq.h>

#define CSV_FILE "character_db.csv"

int main(){
    char buffer[256];
    void *context = zmq_ctx_new();
    void *socket = zmq_socket(context, ZMQ_REP);
    
    if (zmq_bind(socket, "tcp://*:5556") != 0) {
        printf("Error in binding microservice to port 5556.\n");
        return -1;
    }
    printf("Microservice is running...");

    while(1){

        int size = zmq_recv(socket, buffer, sizeof(buffer) - 1, 0);
        if (size > 0) {
            buffer[size] = '\0';
        }
        printf("Data Recieved: %s\n", buffer);

        FILE *file = fopen(CSV_FILE, "a");
        if (!file) {
            printf("Error: Could not open %s for writing.\n", CSV_FILE);
            return -1;
        }
        //appending data to our character DB
        fprintf(file, "%s\n", buffer);
        fclose(file);

        //sending response back
        const char *message = "Character added to DB";
        zmq_send(socket, message, strlen(message), 0);
        break;
    
    } 
    zmq_close(socket);
    zmq_ctx_destroy(context);
    return 0;
    
}
