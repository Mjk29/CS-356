
ooooooooo.   oooooooooooo       .o.       oooooooooo.   ooo        ooooo oooooooooooo 
`888   `Y88. `888'     `8      .888.      `888'   `Y8b  `88.       .888' `888'     `8 
 888   .d88'  888             .8"888.      888      888  888b     d'888   888         
 888ooo88P'   888oooo8       .8' `888.     888      888  8 Y88. .P  888   888oooo8    
 888`88b.     888    "      .88ooo8888.    888      888  8  `888'   888   888    "    
 888  `88b.   888       o  .8'     `888.   888     d88'  8    Y     888   888       o 
o888o  o888o o888ooooood8 o88o     o8888o o888bood8P'   o8o        o888o o888ooooood8 
                                                                                      



Project contains two files

Client			Server

cUDP.cpp	&	sUDP.cpp


Both are compiled on linux with:

g++ sUDP.cpp -sUDP
g++ cUDP.cpp -cUDP


Server listens on port 28333
This can be changed on line 87 in server, and 85 in client 

		int portNum = 28333;


Client attempts to connect to server on a specified port 
This can be changed on line 136

    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");


To run programs, start server first, then run client

For server use command :

	./sUDP

For client use commands :

	./cUDP -push
	./cUDP -pull
	./cUDP -print

-push sends routing table to server
-pull gets routing table from server
-print prints routing table without connecting to server

Client program was tested on afsaccess2 on 3/18/17 by connecting to 
server running on non local machine. 

Program tests were successful in all aspects, no bugs were found. 