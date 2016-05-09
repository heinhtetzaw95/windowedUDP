#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

using namespace std;

#define BUF_MAX 512

int main(int argc, char *argv[]){

	if (argc != 2){
		cout << "Usage Error!\nArguments must be: " << argv[0] << " <port number>" << endl;
	
		return 1;
	}

	int mySocket, nBytes, i;
	char buffer[BUF_MAX];
	struct sockaddr_in serverAddr, clientAddr;
	struct sockaddr_storage serverStorage;
	socklen_t addr_size, clientAddr_size;

		//create UDP socket
	mySocket = socket(PF_INET, SOCK_DGRAM, 0);

		//configure socket address, and port
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(atoi(argv[1]));
	serverAddr.sin_addr.s_addr = inet_addr("localhost");
	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

		//bind socket with address struct
	if (bind(mySocket, (struct sockaddr *) &serverAddr, sizeof (serverAddr))) 
		cout << "Binding OK!\nListening at Port Number: " << argv[1] << endl;
	else 
		cout << "Binding Error!" << endl;
	
		//store the size of server address
	addr_size = sizeof serverStorage;

		//wait for any incoming messages
	while(true){
		nBytes = recvfrom(mySocket, buffer, BUF_MAX, 0, (struct sockaddr *)&serverStorage, &addr_size);

			//print the message received
		cout << "Message received: " << buffer << endl;

			//send the message just received back to client
		sendto(mySocket, buffer, nBytes, 0, (struct sockaddr *)&serverAddr, addr_size);

	}

	return 0;
}
