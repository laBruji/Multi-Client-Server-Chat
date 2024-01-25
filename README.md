# Client-Server Chat
This repository contains a simple C++ implementation of a client-server chat application using socket programming. The project consists of two files: client.cpp and server.cpp.

client.cpp: This file represents the client-side code. It establishes a connection to a server, sends messages to it, and receives responses. The client can initiate the termination of the chat session by typing "exit."

server.cpp: This file represents the server-side code. It creates a server socket, listens for incoming connections, and communicates with connected clients. The server echoes received messages and terminates the chat session upon receiving an "exit" command from the client.