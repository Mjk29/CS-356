
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

int main()
{
   
    int client, server;
    int portNum = 28333;
    bool isExit = false;
    int bufsize = 1024;
    char buffer[bufsize];

    struct sockaddr_in server_addr;
    socklen_t size;


    struct message{
        //Header
         // Version number
         // message type
         // identifier

        //Body
         // routing update  
    };


    // std::cout<<"client init: "<<client<<endl;
    // std::cout<<"server init: "<<server<<endl;

    ///////////////////////////////////////////
    //////////     Create Socket     //////////
    ///////////////////////////////////////////

    client = socket(AF_INET, SOCK_STREAM, 0);

    if (client < 0) {
       std::cout<<endl<<"Socket creation error"<<endl;
        exit(1);
    }

    std::cout<<endl<<"Socket created";
    std::cout<<endl<<"Socket number : "<<client<<endl;

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(portNum);

    ///////////////////////////////////////////
    ///////////     Bind Socket     ///////////
    ///////////////////////////////////////////


    if ((bind(client, (struct sockaddr*)&server_addr,sizeof(server_addr))) < 0) 
    {
        cout << "=> Error binding connection, the socket has already been established..." << endl;
        return -1;
    }

   

    size = sizeof(server_addr);
    cout << "=> Looking for clients..." << endl;

    /* ------------- LISTENING CALL ------------- */
    /* ---------------- listen() ---------------- */

    listen(client, 1);

   

    /* ------------- ACCEPTING CLIENTS  ------------- */
    /* ----------------- listen() ------------------- */

   
    int clientCount = 1;
    server = accept(client,(struct sockaddr *)&server_addr,&size);

    // first check if it is valid or not
    if (server < 0) 
        cout << "=> Error on accepting..." << endl;

    while (server > 0) 
    {
        strcpy(buffer, "=> Server connected...\n");
        send(server, buffer, bufsize, 0);
        cout << "=> Connected with the client #" << clientCount << ", you are good to go..." << endl;
        cout << "\n=> Enter # to end the connection\n" << endl;

       

        cout << "Client: ";
        do {
            recv(server, buffer, bufsize, 0);
            cout << buffer << " ";
            if (*buffer == '#'){
                *buffer = '*';
                isExit = true;
            }
        } while (*buffer != '\n');

        do {
            cout << "\nServer: ";
            do {
                cin >> buffer;
                send(server, buffer, bufsize, 0);
                if (*buffer == '#') {
                    send(server, buffer, bufsize, 0);
                    *buffer = '*';
                    isExit = true;
                }
            } while (*buffer != '*');

            cout << "Client: ";
            do {
                recv(server, buffer, bufsize, 0);
                cout << buffer << " ";
                if (*buffer == '#') {
                    *buffer == '*';
                    isExit = true;
                }
            } while (*buffer != '*');
        } while (!isExit);

      

        /* ---------------- CLOSE CALL ------------- */
        /* ----------------- close() --------------- */

       
       
        cout << "\n\n=> Connection terminated with IP " << inet_ntoa(server_addr.sin_addr);
        close(server);
        cout << "\nGoodbye..." << endl;
        isExit = false;
        exit(1);
    }

    close(client);
    return 0;
}