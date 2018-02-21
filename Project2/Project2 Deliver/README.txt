
ooooooooo.   oooooooooooo       .o.       oooooooooo.   ooo        ooooo oooooooooooo 
`888   `Y88. `888'     `8      .888.      `888'   `Y8b  `88.       .888' `888'     `8 
 888   .d88'  888             .8"888.      888      888  888b     d'888   888         
 888ooo88P'   888oooo8       .8' `888.     888      888  8 Y88. .P  888   888oooo8    
 888`88b.     888    "      .88ooo8888.    888      888  8  `888'   888   888    "    
 888  `88b.   888       o  .8'     `888.   888     d88'  8    Y     888   888       o 
o888o  o888o o888ooooood8 o88o     o8888o o888bood8P'   o8o        o888o o888ooooood8 
                                                                                      



Project contains seven files

	sT0.cpp
	sT1.cpp
	sT2.cpp
	sT3.cpp
	sUDP.h
	cUDP.h
	funct.h


All are compiled on linux with:

	"g++", "-std=c++11", "-pthread", "${file}", "-o", "${file_path}/${file_base_name}

Which results in the following commands

	g++ -std=c++11 -pthread sT0.cpp -o sT0
	g++ -std=c++11 -pthread sT1.cpp -o sT1
	g++ -std=c++11 -pthread sT2.cpp -o sT2
	g++ -std=c++11 -pthread sT3.cpp -o sT3


	g++ -std=c++11 -pthread sUDP.h -o sUDP
	g++ -std=c++11 -pthread cUDP.h -o cUDP
	g++ -std=c++11 -pthread funct.h -o funct


Operating the program:
After compiling, the four server files sT0 sT1 sT2 sT3 must be executed

	./sT0

The program will start and will wait for input commands. 




=========PORT NUMBERS==========



Each server is the same except for its individual port and routing values


	Name 	Port 		   Table
	sT0		28330		0  1  3  7
	sT1 	28331 		1  0  1  99
	sT2 	28332 		3  1  0  2
	sT3 	28333 		7  99 2  0

If needed the port can be changed, it is referenced once in line 120 in each .cpp file

							   |port number|
	std::thread first (runServer, 28330, std::ref(table));


If the port number is changed for any reason, the four ports all must be changed to be sequential
If this is not done, the program will not be able to update

If all ports are changed, the lowest port number must be changed in line 83
This is the starting port for the update command

		argument[1]=28330;




=====COMMANDS=======


The program accepts four commands
	
	push	pull 	print 	update

Push pull and print must be followed by the port number of the server you are conecting to



	push 28330 

This will push the current table to server on port 28330



	pull 28331

THis will pull the table from the server on port 28331 and update the local table



	print 28333

This will print the table from the server on port 28333


	print 1

A port number of 1 will print the local table



The Update function does not need a port number 

	update

This will start the update process for the server

**Important**

This command will only update the local server using the BELLMNAN FORD ALGORTHIM 
To update all four servers, the update command must be executed on each server





==========NOTES=========


This program was only tested locally on a single machine
The NJIT servers were not connectable 
This is most likely due to port forwarding settings that I have no control over

This program was tested on 

	Linux PC-Ubuntu 4.4.0-71-generic #92-Ubuntu SMP Fri Mar 24 12:59:01 UTC 2017 x86_64 x86_64 x86_64 GNU/




