#ares_connection.py

import socket

# hostname = socket.gethostname()
# ip = socket.gethostbyname(hostname)
# print(f'Hostname: {hostname}')
# print(f'IP: {ip}')

# Server to connect to

SERVER_HOST = '10.95.97.134'   # Server IPv4 address
SERVER_PORT = 30000       # Server port

# Create an IPv4 TCP socket
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client:
    # Connect to the server; blocks until connection is established
    client.connect((SERVER_HOST, SERVER_PORT))
    print(f"Connected to {SERVER_HOST}:{SERVER_PORT}")

    # Receive response (up to 4096 bytes)
    # response = client.recv(4096)
    # print(f"Server response: {response.decode('utf-8')}")
# Socket is automatically closed when exiting the 'with' block