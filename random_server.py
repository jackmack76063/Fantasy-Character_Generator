import zmq, random, time

context = zmq.Context()
socket = context.socket(zmq.REP)
socket.bind("tcp://*:5555")

print("Microservice is running...")
while True:
    # Wait for request from client
    message = socket.recv()
    filename = message.decode().strip()  # Convert bytes to string

    # Check for shutdown request
    if filename.lower() == 'q':
        print("Received shutdown request. Closing the server.")
        break
    try:
        file = open(filename, 'r')
        print("File opened successfully.")
    except FileNotFoundError:
        print(f"Error: The file {filename} was not found.")
        break
    except Exception as e:
        print(f"An error occurred: {e}")
        break
    print("Received request for file:", filename)

    # Initialize lists to store character attributes
    gender = []
    species = []
    weapon = []
    personality = []
    hair = []
    eyes = []

    try:
        with open(filename, 'r') as file:
            
            lines = file.readlines()

            gender = lines[0].strip().split(',')
            species = lines[1].strip().split(',')
            weapon = lines[2].strip().split(',')
            personality = lines[3].strip().split(',')
            hair = lines[4].strip().split(',')
            eyes = lines[5].strip().split(',')

    except Exception as e:
        print(f"An error occurred while reading the file: {e}")

            # Create a random character
    character = {
        'gender': random.choice(gender),
        'species': random.choice(species),
        'weapon': random.choice(weapon),
        'personality': random.choice(personality),
        'hair': random.choice(hair),
        'eyes': random.choice(eyes)
    }
    # formatting response to be in csv format
    response = f"{character['gender']},{character['species']},{character['weapon']},{character['personality']},{character['hair']},{character['eyes']}"
    socket.send_string(response)  # Send formatted response

    
