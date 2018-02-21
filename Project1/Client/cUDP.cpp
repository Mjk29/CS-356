
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

struct message{
    short header[3];
    short body[4];
};


void printTable(message M){
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
    std::cout<<"*     " <<M.header[0]<<"    |   "   <<type<<"  |     "  
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

short argCheck(int argc, char*argv[]){

    bool check = false;
    short function;

    if (argc != 2){
        std::cout<<"ARGC Use either -push or -pull or -print to get or send or print data"<<endl<<endl;
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

    if (strcmp(argv[1], "-print") == 0){
        check=true;
        function = 3;
    }

    if (check == false){
        std::cout<<"ARGC Use either -push or -pull or -print to get or send or print data"<<endl<<endl;
        exit(0);
    }

    return function;
}

    ///////////////////////////////////////////
    ///////////     UDP CLIENT     ////////////
    ///////////////////////////////////////////


int main(int argc, char*argv[])
{
   
    int client=0;
    int portNum = 28333;
    short function;
    bool ak = 0;

    message M;
    int messageSize = sizeof(M);
    char *buffer = (char *) &M;
    char *ack = (char *) &ak;

    struct sockaddr_in server_addr;
    socklen_t size = sizeof(server_addr);

    function = argCheck(argc, argv);

    M.header[0]= 9;
    M.header[1]= 1;
    M.header[2]= 9;

    M.body[0]=9;
    M.body[1]=9;
    M.body[2]=9;
    M.body[3]=9;

    ///////////////////////////////////////////
    //////////     DISPLAY DATA     ///////////
    ///////////////////////////////////////////

     
    std::cout<<"Initial Routing Table"<<endl;
    printTable(M);
    if (function == 3){
        std::cout<<"Table Printed, Terminating"<<endl;
        exit(0);
    }


    ///////////////////////////////////////////
    //////////     Create Socket     //////////
    ///////////////////////////////////////////
    

    client = socket(AF_INET, SOCK_DGRAM, 0);

    if (client < 0){
       std::cout<<endl<<"Socket creation error"<<endl;
       exit(0);
    }

    std::cout<<endl<<"Socket created"<<endl;

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("173.63.70.232");
    server_addr.sin_port = htons(portNum);


    ///////////////////////////////////////////
    ////////     Connect to Server    /////////
    ///////////////////////////////////////////


    if (connect(client,(struct sockaddr *)&server_addr, sizeof(server_addr))<0){
        std::cout<<"No connection to server"<<endl;
        exit(0);
    }
  

    ///////////////////////////////////////////
    //////////     Data Transfer     //////////
    ///////////////////////////////////////////


    size = sizeof(server_addr);

    if (function == 0){
        std::cout<<"Pushing data to : "<<inet_ntoa(server_addr.sin_addr)<<endl;
        std::cout<<"On port : "<<ntohs(server_addr.sin_port)<<endl;

        M.header[1]=1;
        sendto(client,buffer,14,0,(struct sockaddr *)&server_addr,size);
        if(recvfrom(client,ack,2,0,(struct sockaddr *)&server_addr, &size)>0)
            std::cout<<"Data sent successfully "<<endl;
        else 
            std::cout<<"Data not sent successfully"<<endl;
    }

    if (function == 1){
        std::cout<<"Pulling data from : "<<inet_ntoa(server_addr.sin_addr)<<endl;
        std::cout<<"On port : "<<ntohs(server_addr.sin_port)<<endl;
        
        M.header[1]=2;
        sendto(client,buffer,14,0,(struct sockaddr *)&server_addr,size);
        if (recvfrom(client,buffer,14,0,(struct sockaddr *)&server_addr, &size)>0){
            std::cout<<"Data received successfully"<<endl;
            printTable(M);
        }
        else
            std::cout<<"Data not received successfully"<<endl;
    }


    ///////////////////////////////////////////
    /////////  Terminate Connection  //////////
    ///////////////////////////////////////////
   
    std::cout<<"Connection terminated "<<endl;
    close(client);
    exit(0);

}