#include <iostream>
#include <string>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define PORT 8082
using namespace std;

int main(int argc, char const *argv[]) 
{ 
    int server_fd, new_socket; 
    struct sockaddr_in address; 
    int addrlen = sizeof(address); 
    char msg[1024] = {0}; 
    
    // Creating socket file 
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(server_fd < 0)
    {
        cerr << "Error establishing the server socket" << endl;
        exit(0);
    }
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = htonl(INADDR_ANY); 
    address.sin_port = htons(PORT); 
       
    int b_status = ::bind(server_fd, (struct sockaddr *)&address,
			    sizeof(address));
    if(b_status < 0)
    {
        cerr << "Error binding socket to local address" << endl;
        exit(0);
    }

    cout << "Waiting for client to connect" << endl;
    
    listen(server_fd, 3); //listening to 3 requests at a time

    sockaddr_in newSockAddr;
    socklen_t newSockAddrSize = sizeof(newSockAddr);
    new_socket = accept(server_fd, (sockaddr *)&newSockAddr, &newSockAddrSize);
    if(new_socket < 0)
    {
        cerr << "Error accepting request from client!" << endl;
        exit(1);
    }
    cout << "Connected with client" << endl;

    
    while(1){
      cout << "Awaiting client response." << endl;
      memset(&msg, 0, sizeof(msg)); // clear the buffer
      recv(new_socket, (char*)&msg, sizeof(msg), 0);

      if(!strcmp(msg, "exit"))
      {
	cout << "Client has quit the session" << endl;
	break;
      }
      
      cout << "Client: " << msg << endl;
      cout << ">";
      
      string data;
      getline(cin, data);
      memset(&msg, 0, sizeof(msg)); //clear the buffer
      strcpy(msg, data.c_str());
      if(data == "exit")
      {
	  send(new_socket, (char*)&msg, strlen(msg), 0);
	  break;
      }
      
      send(new_socket, (char*)&msg, strlen(msg), 0);
    }
    close(new_socket);
    close(server_fd);
    return 0; 
} 
