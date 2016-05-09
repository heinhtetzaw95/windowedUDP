#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

using namespace std;

#define BUF_MAX 512

	//this function is to handle the timers
static void timerHandler( int sig, siginfo_t *si, void *uc) {
    timer_t *tidp;
    tidp = (timer_t *) si->si_value.sival_ptr;
    
    return 0;
}

	//this function create timers with a few amount of time
static int makeTimer(const char *name, timer_t *timerID, int expireMS, int intervalMS ) {
    struct sigevent         te;
    struct itimerspec       its;
    struct sigaction        sa;
    int                     sigNo = SIGRTMIN;

    	/* Set up signal handler. */
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = timerHandler;
    sigemptyset(&sa.sa_mask);

    if (sigaction(sigNo, &sa, NULL) == -1) return(-1);

   		/* Set and enable alarm */
    te.sigev_notify = SIGEV_SIGNAL;
    te.sigev_signo = sigNo;
    te.sigev_value.sival_ptr = timerID;
    timer_create(CLOCK_REALTIME, &te, timerID);

    its.it_interval.tv_sec = intervalMS / 1000;   
    its.it_interval.tv_nsec = (intervalMS % 1000) * 1000000;
    its.it_value.tv_sec = expireMS / 1000;        
    its.it_value.tv_nsec = (expireMS % 1000) * 1000000;
    timer_settime(*timerID, 0, &its, NULL);

    return(0);
}

int main(int argc, char *argv[]){

			//check the arguments and throw error if not correct
	if (argc != 3){
		cout << "Usage Error!\nArguments must be: " 
			<< argv[0] << " <server address> <port number>" << endl;
	
		return 1;
	}

		//declare variables for timers
    int expireMS1 = 100; // 100 ms in future
    int expireMS2 = 250; // 250 ms in future
    int expireMS3 = 500; // 500 ms in future
    int intervalMS1 = 0; // timer does not re-initialize
    int intervalMS2 = 0; // timer does not re-initialize
    int intervalMS3 = 0; // timer does not re-initialize

		//declare variables for socket and connection
	int mySocket, portNumber, nBytes;
	char buffer[BUF_MAX];
	struct sockaddr_in serverAddr;
	socklen_t addr_size;

	memset(serverAddr.sin_zero, 0, sizeof serverAddr.sin_zero);

		//configure client address structure
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(atoi(argv[2]));
	serverAddr.sin_addr.s_addr = inet_addr(argv[1]);

		//create UDP socket
	if (mySocket = socket(PF_INET, SOCK_DGRAM, 0) < 0){
		perror("Cannot create socket!");
		return 1;
	}else cout << "Socket created!" << endl;


	addr_size = sizeof serverAddr;

		//show message to the user
	cout << "Your message will be sent to " << argv[1] << " at port " << argv[2] << endl;

	while (true){
		cout << "Message: ";

				//get the message
		cin.getline(buffer, sizeof(buffer));
		char *storage = buffer;
		nBytes = strlen(buffer) + 1;

		for ( ; ; ) {

				//send the message
			sendto(mySocket, buffer, nBytes, 0, (struct sockaddr *)&serverAddr, addr_size);

				//timer 1
	       	makeTimer(ID1.c_str(), &Slots[i].timerID1, expireMS1 + i*500, intervalMS1); 

	       		//wait for the ACK to arrive back
			if ((nBytes = recvfrom (mySocket, buffer, BUF_MAX, 0, NULL, NULL)) > 0){
				cout << "ACK received!" << endl;
			}
       		timer_delete(Slots[j].timerID1);

				//send the message
			sendto(mySocket, buffer, nBytes, 0, (struct sockaddr *)&serverAddr, addr_size);

       			//timer 2
	       	makeTimer(ID2.c_str(), &Slots[i].timerID2, expireMS2 + i*500, intervalMS2);
	      
	       		//wait for the ACK to arrive back
			if ((nBytes = recvfrom (mySocket, buffer, BUF_MAX, 0, NULL, NULL)) > 0){
				cout << "ACK received!" << endl;
			}
       		timer_delete(Slots[j].timerID2);

				//send the message
			sendto(mySocket, buffer, nBytes, 0, (struct sockaddr *)&serverAddr, addr_size);
			
       			//timer 3
	      	makeTimer(ID3.c_str(), &Slots[i].timerID3, expireMS3 + i*500, intervalMS3);
	       		//wait for the ACK to arrive back
			if ((nBytes = recvfrom (mySocket, buffer, BUF_MAX, 0, NULL, NULL)) > 0){
				cout << "ACK received!" << endl;
			}
       		timer_delete(Slots[j].timerID3);

       			//keep the timer counting
		    do {
		      	timeleft = sleep(timeleft);
		      	if ((count % 100) == 0)count++;
		   	} while (timeleft > 0); 

		   	if (buffer != )
		}
	}
	return 0;
}
