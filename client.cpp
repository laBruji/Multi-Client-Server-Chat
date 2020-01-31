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
    int client_fd = 0; 
    struct sockaddr_in serv_addr; 
    char buffer[1024] = {0}; 
    
    client_fd = socket(AF_INET, SOCK_STREAM, 0);   
    serv_addr.sin_family = AF_INET; 
    inet_pton(AF_INET, "127.0.0.1", &(serv_addr.sin_addr));
    serv_addr.sin_port = htons(PORT); 

    int status = connect(client_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if(status < 0)
    {
        cout<<"Error connecting to socket"<<endl; 
    }

    cout << "Connected to the server" << endl;
    
    while(1)
    {
      cout << ">";
      string msg;
      getline(cin, msg);
      memset(&buffer, 0, sizeof(buffer));
      strcpy(buffer, msg.c_str());
      if(msg == "exit")
      {
	send(client_fd, (char*)&buffer, strlen(buffer), 0);
	break;
      }
      send(client_fd, (char*)&buffer, strlen(buffer),0);
      cout << "Awaiting server response" << endl;
      memset(&buffer, 0, sizeof(buffer));
      recv(client_fd, (char*)&buffer, sizeof(buffer), 0);
      if(!strcmp(buffer, "exit"))
      {
	cout << "Server has quit the session" << endl;
	break;
      }
      cout << "Server: " << buffer << endl;
    }
    close(client_fd);
    cout << "Connection closed" << endl;
    return 0; 
} 
