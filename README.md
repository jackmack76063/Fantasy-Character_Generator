# Fantasy Character Generator

This program acts as a brainstorming tool to plan and visualize new fantasy characters.

Users have the option to:
- manually enter a new character and add it to a local DB.
- randomly generate a character with our given attributes (stored in "character_generator.csv")
- browse personality types
- browse species types
- browse our full "database" of characters (stored in "character_db.csv")
- search by personality type
- -search by species type

## Instructions: Users will need to compile and run each sepearate microservice, along with our main program, in sepearate terminals.

## Main Program: fantasy_db.c

### Language: C 

### compile: gcc fantasy_db.c -o fantasy_db -lzmq

Description: As stated, our main program that holds the functionality for creating a character,

researching species and personality types, searching by specific types, and 

browsing our "character_db.csv"

## Microservice 1: random_server.py

### Language: Python

### compile: python random_server.py

Description: This microservice performs the task of randomly generating a character.

-Recieves message via ZeroMQ from main program 

-The message, a file name, will open up the file character_generator.csv

-This file will give attributes of a character and all the options available in each attribute

-It will then randomly generate each attribute, group the responses together, and return to main program.

## Microservice 2: add_server.c

### Language: C

### compile: gcc add_server.c -o add_server -lzmq

Description: This microservice adds a new character to our file "character_db.csv"

-Recieves message via ZeroMQ with a character's name, along with all of their seleceted attributes.

-The attributes will then append to the end of our file used to hold all of our characters.

-It will then send a message confirming the character has been added to our database. 

## Microservice 3: search_personality.c

### Language: C

### Compile: gcc search_personality.c -o search_personality -lzmq

Description: This microservice will search for characters by a specific personality type.

-Recieves message via ZeroMQ with a personality type entered by the user.

-Stores and searches our database file "character_db.csv" to find matches

-Sends the characters names back to our main program

## Microservice 4: search_species.c

### Language: C

### Compile: gcc search_species.c -o search_species -lzmq

Description: This microservice will search for characters by a specific species type.

-Recieves message via ZeroMQ with a species type entered by the user.

-Stores and searches our database file "character_db.csv" to find matches

-Sends the characters names back to our main program

## character_db.csv

A file in csv format that acts a "database" for characters and their attributes.

## character_generator.csv

A file in csv format that holds a list of attributes (sans "name") and their

options. Used to randomly generate a character.



