#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <memory.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <errno.h>
#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;



int main(){

	int result = 0;
    int sock = socket(AF_INET, SOCK_DGRAM, 0);


    sockaddr_in addrListen = {}; 
    addrListen.sin_family = AF_INET;
    result = bind(sock, (sockaddr*)&addrListen, sizeof(addrListen));
  

    if (result == -1)
    {
       int lasterror = errno;
       std::cout << "error: " << lasterror;
       exit(1);
    }


    sockaddr_storage addrDest = {};


	int client;
    addrinfo* result_list = NULL;
    addrinfo hints = {};
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM; // without this flag, getaddrinfo will return 3x the number of addresses (one for each socket type).
    client = getaddrinfo("127.0.0.1", "28333", &hints, &result_list);
    if (client == 0)
    {
        memcpy(&addrDest, result_list->ai_addr, result_list->ai_addrlen);
        freeaddrinfo(result_list);
    }


    if (client != 0)
    {
       int lasterror = errno;
       std::cout << "error: " << lasterror;
       exit(1);
    }

    const char* msg = " COCKS \n";
    size_t msg_length = strlen(msg);

    client = sendto(sock, msg, msg_length, 0, (sockaddr*)&addrDest, sizeof(addrDest));

     std::cout << client << " bytes sent" << std::endl;

     client  = recvfrom(sock, msg, msg_length, 0, (sockaddr*)&addrDest, &sizeof(addrDest));

    return 0;















}