
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>

using namespace std;

struct message{
	short header[3];
	short body[4];
};


void printTable(message M){
	///////////////////////////////////////////
    //////////     Display Table     //////////
    ///////////////////////////////////////////

	string type;

	if (M.header[1]!=0){
		if (M.header[1] == 1)
			type = "Request ";
		if (M.header[1] == 2)
			type = "Response";
	}

	std::cout<<endl;
	std::cout<<"*---------------HEADER----------------*"<<endl;
	std::cout<<"*  Version |     Type    | Identifier *"<<endl;
	std::cout<<"*     "	<<M.header[0]<<"    |   "	<<type<<"  |     "	
	<<M.header[2]<<"      *"<<endl;
	std::cout<<"*          |             |            *"<<endl;

	std::cout<<"*----------------BODY-----------------*"<<endl;
	std::cout<<"*             Destination Routers     *"<<endl;
	std::cout<<"* Source |  R0  |  R1  |  R2  |  R3   *"<<endl;
	std::cout<<"*-------------------------------------*"<<endl;
	std::cout<<"*   R0   |  "<<M.body[0]<<"   |  "<<M.body[1]<<"   |  "
	<<M.body[2]<<"   |   "<<M.body[3]<<"   *"<<endl;
	std::cout<<"*-------------------------------------*"<<endl<<endl;
}

bool argCheck(int argc, char*argv[]){

	bool check = false;
	bool function;

	if (argc != 2){
		std::cout<<" ARGC Use either -push or -pull to get or send data"<<endl<<endl;
		exit(0);
	}

	if (strcmp(argv[1], "-push") == 0){
		check=true;
		function = 0;
	}

	if (strcmp(argv[1], "-pull") == 0){
		check=true;
		function = 1;
	}

	if (check == false){
		std::cout<<" ARGV Use either -push or -pull to get or send data"<<endl<<endl;
		exit(0);
	}

	return function;
}

	///////////////////////////////////////////
    ///////////     UDP SERVER     ////////////
    ///////////////////////////////////////////

int main(){


	int client, server, n;
	int portNum = 28329;
	message M,T;
	int messageSize = sizeof(M);

	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	socklen_t size = sizeof(server_addr);

	bool isExit = false;
	bool function;
	bool ak = 0;

	M.header[0]= 1;
	M.header[1]= 2;
	M.header[2]= 1;

	M.body[0]=0;
	M.body[1]=1;
	M.body[2]=3;
	M.body[3]=7;

	char *buffer = (char *) &M;
	char *temp = (char *) &T;
    char *ack = (char *) &ak;

 	///////////////////////////////////////////
    //////////     DISPLAY DATA     ///////////
    ///////////////////////////////////////////

     
    std::cout<<"Initial Routing Table"<<endl;
    printTable(M);


	///////////////////////////////////////////
	//////////     Create Socket     //////////
	///////////////////////////////////////////


	client = socket(AF_INET, SOCK_DGRAM, 0);
	// client.setTimeout(30,5);

    if (client < 0) {
       std::cout<<endl<<"Socket creation error"<<endl;
        exit(0);
    }

    std::cout<<endl<<"Socket created"<<endl;
    std::cout<<server_addr.sin_port<<endl;

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(portNum);


    ///////////////////////////////////////////
    ///////////     Bind Socket     ///////////
    ///////////////////////////////////////////


	if ((bind(client,(struct sockaddr*)&server_addr,sizeof(server_addr)))< 0){
		std::cout << "	Socket Bind Error " << endl;
		exit(0);
    }
	
	size = sizeof(server_addr);
	std::cout << "Waiting for connection " << endl;


	///////////////////////////////////////////
    //////////    DATA TRANSFER     ///////////
    ///////////////////////////////////////////

	while (1) {


		recvfrom(client,temp,14,0,(struct sockaddr *)&client_addr,&size);

		if (T.header[1]==1){
			std::cout<<"Client push update "<<endl;
			std::cout<<"Client IP address  : "<<inet_ntoa(client_addr.sin_addr)<<endl;
			std::cout<<"Connected on Port  : "<<ntohs(client_addr.sin_port)<<endl;
			M = T;
			std::cout<<"Router Table Updated"<<endl;
			printTable(M);
			sendto(client,ack,2,0,(struct sockaddr *)&client_addr,size);
		}

		if (T.header[1]==2){
			std::cout<<"Client pull update "<<endl;
			std::cout<<"Client IP address  : "<<inet_ntoa(client_addr.sin_addr)<<endl;
			std::cout<<"Connected on Port  : "<<ntohs(client_addr.sin_port)<<endl<<endl;
			sendto(client,buffer,14,0,(struct sockaddr *)&client_addr,size);
		}

		std::cout<<"Enter Command "<<endl;
	string command;
	cin>>command;

	
	}


    ///////////////////////////////////////////
    /////////  Terminate Connection  //////////
    ///////////////////////////////////////////


   	int shutdown(int socket, int SHUT_RDWR);
   	std::cout<<"Connection terminated "<<endl;
	close(server);
	exit(0);


}
