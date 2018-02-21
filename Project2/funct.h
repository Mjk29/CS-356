
#include <iostream>
#include <string>
#include <typeinfo>
#include <sstream>
// #include "cUDP.h"


#ifndef FUNCT_H
#define FUNCT_H


struct dataTable{

    short table[4];
};

struct message{
    short header[3];
    short body[4];
};



// dataTable runClient(short* argument, dataTable &table);



// dataTable updateAll(dataTable &table){

//  dataTable temp =table;
//  short* argument = new short[3];
//  argument[0]=1;
//  argument[1]=28330;
//  argument[2]=1;

//  //BELLMNAN FORD ALGORTHIM 
//  for (int i = 0; i < 4; ++i){
//      //pull from server then increment port
//      temp = runClient(argument,temp);
//      argument[1] +=1;

//      //add cost from local server to pulled data
//      for (int k = 0; k < 4; ++k){
//          temp.table[k] += table.table[i];
//      }

//      //compare and update
//      for (int j = 0; j < 4; ++j){
//          if (temp.table[j] < table.table[j]){
//              table.table[j] = temp.table[j];
//          }
//      }
//      //Send update signal to other servers
//  argument[0]=3;
//  runClient(argument,table);
//  }

    
// }






void printTable(message M){
    std::string type;
    std::string ident;


    if (M.header[2]==0)
        ident = "PUSH";

        if (M.header[2]==1)
            ident = "PULL";
        if (M.header[2]==2)
            ident = "PRINT";
        if (M.header[2]==3)
          ident = "INIT ";

    if (M.header[1]!=0){
        if (M.header[1] == 1)
            type = "Request ";
        if (M.header[1] == 2)
            type = "Response";
        if (M.header[1] == 3)
            type = "INITIAL ";

    }

    std::cout<<std::endl;
    std::cout<<"*---------------HEADER----------------*"<<std::endl;
    std::cout<<"*  Version |     Type    | Identifier *"<<std::endl;
    std::cout<<"*     " <<M.header[0]<<"    |   "   <<type<<"  |   "  
    <<ident<<"    *"<<std::endl;
    std::cout<<"*          |             |            *"<<std::endl;

    std::cout<<"*----------------BODY-----------------*"<<std::endl;
    std::cout<<"*             Destination Routers     *"<<std::endl;
    std::cout<<"* Source |  R0  |  R1  |  R2  |  R3   *"<<std::endl;
    std::cout<<"*-------------------------------------*"<<std::endl;
    std::cout<<"*   R0   |  "<<M.body[0]<<"   |  "<<M.body[1]<<"   |  "
    <<M.body[2]<<"   |   "<<M.body[3]<<"   *"<<std::endl;
    std::cout<<"*-------------------------------------*"<<std::endl<<std::endl;
}



short* argCheck(){
    short *argument = new short[3];
    bool check;
    short portn;
    std::string input;
    std::string command;


    while (1){

        std::cout<<"ENTER COMMAND : "<<std::endl<<"> ";
        argument[2]=0;
        std::getline(std::cin, input);
        std::istringstream iss (input);
        iss >> std::noskipws;
        iss >> command >> std::ws >> portn;
        std::cout<<std::endl;


    if (portn == 0 ){
        if (command == "update") {
            std::cout<<"UPDATE COMMAND"<<std::endl;
            argument[2] = 1;
            argument[0] = 3;
            return argument;
    }
        std::cout<<"Enter command (push / pull / print) followed blank space then by port number"<<std::endl;
        std::cout<<"e.g.  push 80   to push table to server on port 80.  "<<std::endl;
        std::cout<<"      print 1 to print local table. "<<std::endl<<std::endl;
        break;
    }
        argument[1]=portn;
        portn = 0;


    if (command == "push"){
        std::cout<<"PUSH COMMAND"<<std::endl;
        argument[2] = 1;
        argument[0] = 0;
        return argument;
    }

    if (command == "pull"){
        std::cout<<"PULL COMMAND"<<std::endl;
        argument[2] = 1;
        argument[0] = 1;
        return argument;

    }

    if (command == "print"){
        std::cout<<"PRINT COMMAND"<<std::endl;
        argument[2] = 1;
        argument[0] = 2;
        return argument;

    }
    // if (command == "update")
    // {
    //     std::cout<<"UPDATE COMMAND"<<std::endl;
    //     argument[2] = 1;
    //     argument[0] = 3;
    //     return argument;
    // }

    if (check == false){
        std::cout<<"Enter command (push / pull / print) followed blank space then by port number"<<std::endl<<std::endl;
        std::cout<<" e.g.      push 80    "<<std::endl;
        break;
    }

}
}







#endif