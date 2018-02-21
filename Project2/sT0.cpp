#include <iostream>
#include <thread>
#include <unistd.h>
#include "cUDP.h"
#include "sUDP.h"
#include "funct.h"

dataTable updateAll(dataTable &table);
int command(dataTable &table);


dataTable runClient(short* argument, dataTable &table);



int testFun(){
		std::cout<<endl<<"TEST OF FUNCTION *********************"<<endl;
}



int command(dataTable &table){

	
	string input;
	string command;
	short portn;
	short* returnTable;
	short* argument;
	dataTable temp;

	std::cout<<"Enter command (push / pull / print) followed blank space";
	std::cout<<" then by port number"<<endl;
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
			if (argument[0] != 3){

				std::cout<<"ARG push pull print "<<endl;
				runClient(argument, table);
			}

			if (argument[0] == 3){
				std::cout<<"ARG 3 UPDATE"<<endl;
				for (int i = 0; i < 2; ++i){
					usleep(100000);
					updateAll(table);
					
				}
			}

			//Updates table on server 
			updateServerTable(table);

		}		
	}
}



dataTable updateAll(dataTable &table){


	dataTable temp =table;
	short* argument = new short[3];
	argument[0]=1;
	argument[1]=28330;
	argument[2]=1;

	//BELLMNAN FORD ALGORTHIM 
	for (int i = 0; i < 4; ++i){
		//pull from server then increment port
		temp = runClient(argument,temp);
		argument[1] +=1;

		//add cost from local server to pulled data
		for (int k = 0; k < 4; ++k){
			temp.table[k] += table.table[i];
		}

		//compare and update
		for (int j = 0; j < 4; ++j){
			if (temp.table[j] < table.table[j]){
				table.table[j] = temp.table[j];
			}
		}
	}	
}





int main(){

dataTable table;

//Initial table
table.table[0] = 0;
table.table[1] = 1;
table.table[2] = 3;
table.table[3] = 7;

std::thread first (runServer, 28330, std::ref(table));
usleep(100000);
std::thread second(command, std::ref(table));

second.join();
first.join();


}