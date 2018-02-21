#include <iostream>
#include <thread>
#include "cUDP.h"
#include "sUDP.h"
#include "funct.h"

int command(){

	
	string input;
	string command;
	short portn;
	short* commTable;
	short* argument;


	std::cout<<"Enter command (push / pull / print) followed blank space then by port number"<<endl;
    std::cout<<"e.g.  push 80   to push table to server on port 80.  "<<std::endl;
    std::cout<<"      print 1 to print local table. "<<std::endl<<std::endl;
	
	while (1){
		//Clear variables
		input.clear();
        command.clear();
        portn =0;

        //Run input stream through check
        //Get array [2] back
       	//[0] = command, push pull print
       	//[1] = port number
       	//[2] = acceptance check, 1 is good 0 is not good
		argument = argCheck();

		if (argument[2]==1){
			//Run client code with command and destination port
			//Client returns message with updated table or print table 
			commTable = runClient(argument);
		}
		
	}
}



int main(){


short table[3];
table[0] = 1;
table[1] = 0;
table[2] = 1;
table[3] = -1;


std::thread first (runServer, 28331);
std::thread second(command);


second.join();
first.join();



}