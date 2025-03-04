# Fantasy Character Generator

This program acts as a brainstorming tool to plan and visualize new fantasy characters.

Users have the option to manually enter a new character and add it to a local DB.

A microservice is also provided that assists in randomly generating a new character.

compiler: gcc --std=gnu99 -o character_generator *.c

## Main Program: fantasy_db.c

### Language: C 

### compile: gcc fantasy_db.c -o fantasy_db -lzmq

Description: As stated, our main program that holds the functionality for creating a character,

researching species and personality types, searching by specific types, and 

browsing our "character_db.csv"

## Microservice 1: random_server.py

### Language: Python

### compile: python random_server.py

Description: This Microservice performs the task of randomly generating a character.

-Recieves message via ZeroMQ from main program 

-The message, a file name, will open up the file character_generator.csv

-This file will give attributes of a character and all the options available in each attribute

-It will then randomly generate each attribute, group the responses together, and return to main program.

## character_db.csv

A file in csv format that acts a "database" for characters and their attributes.

## cgaracter_generator.csv

A file in csv format that holds a list of attributes (sans "name") and their

options. Used to randomly generate a character.

##Main Program: fantasy_db.c

compile: gcc fantasy_db.c -o fantasy_db -lzmq

As stated, our main program that holds the functionality for creating a character,

researching species and personality types, searching by specific types, and 

browsing our "character_db.csv"

##Microservice 1: random_server.py

compile: python random_server.py

##character_db.csv

A file in csv format that acts a "database" for characters and their attributes.