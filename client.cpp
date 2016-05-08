#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

#define BUF_MAX 512

int main(int argc, char *argv[]){
	if (argc != 3){
		cout << "Usage Error!\nArguments must be: " 
			<< argv[0] << " <server address> <port number>" << endl;
	
		return 1;
	}

	int mySocket, portNumber, nBytes;
	char buffer[BUF_MAX];
	struct sockaddr_in serverAddr;
	socklen_t addr_size;

		//create UDP socket
	mySocket = socket(PF_INET, SOCK_DGRAM, 0);

		//configure client address structure
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(atoi(argv[2]));
	serverAddr.sin_addr.s_addr = inet_addr(argv[1]);
	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

	addr_size = sizeof serverAddr;

	cout << "Your message will be sent to " << argv[1] << " at port " << argv[2] << endl;

	while (true){
		cout << "Message: ";
		cin >> buffer;

		nBytes = strlen(buffer) + 1;

			//send the message
		sendto(mySocket, buffer, nBytes, 0, (struct sockaddr *)&serverAddr, addr_size);

		//nBytes = recvfrom (mySocket, buffer, BUF_MAX, 0, NULL, NULL);
		//cout << buffer; 
	}

	return 0;
}