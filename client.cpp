#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <iostream>
#include <string>
#define PORT 8082

using namespace std;

int main(int argc, char const *argv[]) 
{ 
    // Set up server address structure
    struct sockaddr_in serv_addr; 
    serv_addr.sin_family = AF_INET; 
    inet_pton(AF_INET, "127.0.0.1", &(serv_addr.sin_addr));
    serv_addr.sin_port = htons(PORT); 

    // Establish a TCP connection with the server
    int client_fd = socket(AF_INET, SOCK_STREAM, 0); 
    int status = connect(client_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    
    // Check connection
    if(status < 0)
    {
        cout<<"Error connecting to socket"<<endl; 
    }

    cout << "Connected to the server" << endl;
    

    // Message handling loop
    char buffer[1024] = {0}; 
    while(1)
    {
      // Get the message
      cout << ">";
      string msg;
      getline(cin, msg);
      memset(&buffer, 0, sizeof(buffer));
      strcpy(buffer, msg.c_str());

      // Send the message
      send(client_fd, (char*)&buffer, strlen(buffer),0);
      
      cout << "Awaiting server response" << endl;

      // Reset buffer to receive the message
      memset(&buffer, 0, sizeof(buffer));
      recv(client_fd, (char*)&buffer, sizeof(buffer), 0);

    if (msg == "exit" || !strcmp(buffer, "exit")) {
        break;
    }
      cout << "Server: " << buffer << endl;
    }

    close(client_fd);
    cout << "Connection closed" << endl;
    return 0; 
} 
