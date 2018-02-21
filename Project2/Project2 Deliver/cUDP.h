
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include "funct.h"

using namespace std;



dataTable runClient(short* argument, dataTable &table)
{
   std::cout<<" CLIENT RUNNING "<<std::endl;
    int client=0;
    short portNum = argument[1];
    bool ak = 0;

    message M;
    int messageSize = sizeof(M);
    char *buffer = (char *) &M;
    char *ack = (char *) &ak;

    struct sockaddr_in server_addr;
    socklen_t size = sizeof(server_addr);

    size = sizeof(server_addr);


    M.header[0]= 9;
    M.header[1]= 1;
    M.header[2]= 9;

    M.body[0]=table.table[0];
    M.body[1]=table.table[1];
    M.body[2]=table.table[2];
    M.body[3]=table.table[3];



     ///////////////////////////////////////////
    //////////     Create Socket     //////////
    ///////////////////////////////////////////
    

    client = socket(AF_INET, SOCK_DGRAM, 0);

    if (client < 0){
       std::cout<<endl<<"Socket creation error"<<endl;
    }

    std::cout<<endl<<"Socket created"<<endl;

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(portNum);


    ///////////////////////////////////////////
    ////////     Connect to Server    /////////
    ///////////////////////////////////////////


    if (connect(client,(struct sockaddr *)&server_addr, sizeof(server_addr))<0){
        std::cout<<"No connection to server"<<endl;
        // exit(0);
    }
  
    ///////////////////////////////////////////
    //////////     PRINT TABLE      ///////////
    ///////////////////////////////////////////

     
    std::cout<<"Initial Routing Table"<<endl;

    if (argument[0] == 2){

        M.header[1]=1;
        M.header[2]=2;

        //Port 1 = selft print
        if (argument[1] == 1){
            printTable(M);
        }
        
        //Connect to server, get table, print table
        if (argument[1] >= 2){
            std::cout<<"Pulling data from : "<<inet_ntoa(server_addr.sin_addr)<<endl;
            std::cout<<"On port : "<<ntohs(server_addr.sin_port)<<endl;
            
            M.header[1]=2;
            M.header[2]=2;

            sendto(client,buffer,14,0,(struct sockaddr *)&server_addr,size);
            if (recvfrom(client,buffer,14,0,(struct sockaddr *)&server_addr, &size)>0){
                std::cout<<"Data received successfully"<<endl;
                printTable(M);
            }
            else
                std::cout<<"Data not received successfully"<<endl;
        }
    }



    ///////////////////////////////////////////
    //////////       PUSH TABLE      //////////
    ///////////////////////////////////////////



    if (argument[0] == 0){

        std::cout<<"Pushing data to : "<<inet_ntoa(server_addr.sin_addr)<<endl;
        std::cout<<"On port : "<<ntohs(server_addr.sin_port)<<endl;

        M.header[1]=0;
        M.header[2]=0;

        std::cout<<"IN CLIENT  "<<M.body[0]<<endl;
        sendto(client,buffer,14,0,(struct sockaddr *)&server_addr,size);
        if(recvfrom(client,ack,2,0,(struct sockaddr *)&server_addr, &size)>0)
            std::cout<<"Data sent successfully "<<endl;
        else 
            std::cout<<"Data not sent successfully"<<endl;

    }


    ///////////////////////////////////////////
    //////////      PULL TABLE       //////////
    ///////////////////////////////////////////




    if (argument[0] == 1){

        std::cout<<"Pulling data from : "<<inet_ntoa(server_addr.sin_addr)<<endl;
        std::cout<<"On port : "<<ntohs(server_addr.sin_port)<<endl;
        
        M.header[1]=2;
        M.header[2]=2;

        sendto(client,buffer,14,0,(struct sockaddr *)&server_addr,size);
        if (recvfrom(client,buffer,14,0,(struct sockaddr *)&server_addr, &size)>0){
            std::cout<<"Data received successfully"<<endl;
            printTable(M);
            table.table[0] = M.body[0];
            table.table[1] = M.body[1];
            table.table[2] = M.body[2];
            table.table[3] = M.body[3];
            return table;

        }
        else
            std::cout<<"Data not received successfully"<<endl;
    }


    ///////////////////////////////////////////
    //////////    UPDATE COMMAND     //////////
    ///////////////////////////////////////////


     if (argument[0] == 3){
        M.header[1]=2;
        M.header[2]=3;

        std::cout<<"UPDATE COMMAND "<<inet_ntoa(server_addr.sin_addr)<<endl;
        std::cout<<"Sending to  : "<<ntohs(server_addr.sin_port)<<endl;

        std::cout<<"IN CLIENT  "<<M.body[0]<<endl;
        sendto(client,buffer,14,0,(struct sockaddr *)&server_addr,size);
        if(recvfrom(client,ack,2,0,(struct sockaddr *)&server_addr, &size)>0)
            std::cout<<"Data sent successfully "<<endl;
        else 
            std::cout<<"Data not sent successfully"<<endl;

    }


    ///////////////////////////////////////////
    /////////  Terminate Connection  //////////
    ///////////////////////////////////////////
   
    std::cout<<"Connection terminated "<<endl;
    close(client);

}