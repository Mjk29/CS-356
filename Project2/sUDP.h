
// #include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "funct.h"

using namespace std;


dataTable updateServerTable(dataTable &table){

	std::cout<<"TEST OF A SERVER UPDATE THREAD"<<std::endl;

			std::cout<<&table<<endl;
			std::cout<<table.table[0];
			std::cout<<table.table[1];
			std::cout<<table.table[2];
			std::cout<<table.table[3]<<endl<<std::endl;

	return table;

}

int testFun();
dataTable updateAll(dataTable &table);




	///////////////////////////////////////////
    ///////////     UDP SERVER     ////////////
    ///////////////////////////////////////////

void runServer(int portNum, dataTable &table){


	int client, server, n;
	message M,T;
	int messageSize = sizeof(M);

	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	socklen_t size = sizeof(server_addr);

	bool isExit = false;
	bool function;
	bool ak = 0;

	M.header[0]= 2;
	M.header[1]= 3;
	M.header[2]= 3;

	M.body[0]=table.table[0];
	M.body[1]=table.table[1];
	M.body[2]=table.table[2];
	M.body[3]=table.table[3];


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

    if (client < 0) {
       std::cout<<endl<<"Socket creation error"<<endl;
        exit(0);
    }

    std::cout<<endl<<"Socket created"<<endl;

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

	M.body[0]=table.table[0];
	M.body[1]=table.table[1];
	M.body[2]=table.table[2];
	M.body[3]=table.table[3];

		recvfrom(client,temp,14,0,(struct sockaddr *)&client_addr,&size);

		//CLient pushing data
		if (T.header[2]==0){
	
			M = T;
			
			table.table[0] = T.body[0];
            table.table[1] = T.body[1];
            table.table[2] = T.body[2];
            table.table[3] = T.body[3];

          	std::cout<<"Router Table Updated"<<endl;


			printTable(T);
			sendto(client,ack,2,0,(struct sockaddr *)&client_addr,size);

			
		}

		//client pulling data
		if (T.header[2]==1){
			std::cout<<"Client pull update "<<endl;
			std::cout<<"Client IP address  : "<<inet_ntoa(client_addr.sin_addr)<<endl;
			std::cout<<"Connected on Port  : "<<ntohs(client_addr.sin_port)<<endl<<endl;
			sendto(client,buffer,14,0,(struct sockaddr *)&client_addr,size);


		}
		
		// client printing data
		if (T.header[2]==2){
			std::cout<<"Client print command "<<endl;
			std::cout<<"Client IP address  : "<<inet_ntoa(client_addr.sin_addr)<<endl;
			std::cout<<"Connected on Port  : "<<ntohs(client_addr.sin_port)<<endl<<endl;
			sendto(client,buffer,14,0,(struct sockaddr *)&client_addr,size);
		}

		//Client Update Command
		if (T.header[2]==3){
			std::cout<<"Client update command "<<endl;
			std::cout<<"Client IP address  : "<<inet_ntoa(client_addr.sin_addr)<<endl;
			std::cout<<"Connected on Port  : "<<ntohs(client_addr.sin_port)<<endl<<endl;
			sendto(client,temp,14,0,(struct sockaddr *)&client_addr,size);

		}

		
	}


    ///////////////////////////////////////////
    /////////  Terminate Connection  //////////
    ///////////////////////////////////////////


   	int shutdown(int socket, int SHUT_RDWR);
   	std::cout<<"Connection terminated "<<endl;
	close(server);
	exit(0);


}
