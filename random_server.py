import zmq, random, time

context = zmq.Context()
socket = context.socket(zmq.REP)
socket.bind("tcp://*:5555")

while True:
    # Wait for request from client
    message = socket.recv()
    filename = message.decode().strip()  # Convert bytes to string

    # Check for shutdown request
    if filename.lower() == 'q':
        print("Received shutdown request. Closing the server.")
        break

    print("Received request for file:", filename)

    try:
        with open(filename, 'r') as file:
            lines = file.readlines()

            if len(lines) < 6:
                print(f"Error: File {filename} does not have enough lines.")
                socket.send_string("Error: Invalid file format")
                continue

            gender = lines[0].strip().split(',')
            species = lines[1].strip().split(',')
            weapon = lines[2].strip().split(',')
            personality = lines[3].strip().split(',')
            hair = lines[4].strip().split(',')
            eyes = lines[5].strip().split(',')

            # Create a random character
            character = {
                'gender': random.choice(gender),
                'species': random.choice(species),
                'weapon': random.choice(weapon),
                'personality': random.choice(personality),
                'hair': random.choice(hair),
                'eyes': random.choice(eyes)
            }
            print(f"Generated character: {character}")
            response = f"{character['gender']},{character['species']},{character['weapon']},{character['personality']},{character['hair']},{character['eyes']}"
            print(f"Debug: Sending response to client: {response}")
            socket.send_string(response)  # Send formatted response

    except FileNotFoundError:
        print(f"Error: The file {filename} was not found.")
        socket.send_string("Error: File not found")
    except Exception as e:
        print(f"An error occurred: {e}")
        socket.send_string(f"Error: {e}")
