#include <iostream>
#include <string>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <thread>
#include <vector>

#define PORT 8082
using namespace std;

// To be executed in a separate thread for each connected client. 
void handleClient(int client_socket) {
    char buffer[1024] = {0};

    while (1) {
        memset(&buffer, 0, sizeof(buffer));
        recv(client_socket, buffer, sizeof(buffer), 0);

        if (!strcmp(buffer, "exit")) {
            cout << "Client has quit the session" << endl;
            break;
        }

        cout << "Client: " << buffer << endl;

        // Reset the buffer to send message
        memset(&buffer, 0, sizeof(buffer));

        string msg;
        getline(cin, msg);
        strcpy(buffer, msg.c_str());
        send(client_socket, (char*)&buffer, sizeof(buffer), 0);
        if (msg == "exit" || !strcmp(buffer, "exit")) {
                break;
        }
    }

    close(client_socket);
}


int main(int argc, char const *argv[]) 
{ 
    // Create socket and bind to address
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(server_fd < 0)
    {
        cerr << "Error establishing the server socket" << endl;
        exit(0);
    }

    struct sockaddr_in address; 
    int addrlen = sizeof(address); 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = htonl(INADDR_ANY); 
    address.sin_port = htons(PORT); 
       
    int b_status = ::bind(server_fd, (struct sockaddr *)&address,sizeof(address));
    if(b_status < 0)
    {
        cerr << "Error binding socket to local address" << endl;
        exit(0);
    }

    cout << "Waiting for client to connect" << endl;
    listen(server_fd, 3); //listening to 3 requests at a time

    while (1) {
        int new_socket = accept(server_fd, (sockaddr *)&address, (socklen_t*)&addrlen);
        if(new_socket < 0)
        {
            cerr << "Error accepting request from client!" << endl;
            exit(1);
        }
        cout << "Connected with client" << endl;

        // Spawn a new thread to handle the client
        thread clientThread(handleClient, new_socket);
        clientThread.detach();  // Detach the thread to allow it to run independently
    }

    close(server_fd);
    return 0; 
} 
