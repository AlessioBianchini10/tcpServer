#include <iostream>
#include <pthread.h>
#include <cstring>

#include <chrono>
#include <thread>

#include "PracticalSocket.h"

#define PORT_NUMBER             4425
#define SOCK_BUFFER_SIZE        100


void *ThreadMain( void *p_tcpSocketThread );

int main() {
    try {
        // Open new socket on port PORT_NUMBER
        TCPServerSocket l_TCPserverSocket( PORT_NUMBER );
        cout << "Server is now listening on port " << PORT_NUMBER << endl;

        // Run forever
        for ( ;; )
        {
            TCPSocket *l_TCPsocket = l_TCPserverSocket.accept();

            // New threadID
            pthread_t pthreadID;

            // Start new thread
            if ( pthread_create( &pthreadID , NULL , ThreadMain , (void *) l_TCPsocket ) != 0 )
            {
                // Error while creating new thread
                std::cout << "Unable to create thread " << pthreadID << std::endl;
            }
        }
    }
    catch ( SocketException &e )
    {
        std::cerr << e.what() << std::endl;
        exit( 1 );
    }

}

void *ThreadMain( void *p_tcpSocketThread )
{
    char l_rcvBuffer[ SOCK_BUFFER_SIZE ];

    // Initialize memory to 0
    memset( l_rcvBuffer , 0 , SOCK_BUFFER_SIZE );

    // Cast from void* to TCPSocket*
    TCPSocket *l_tcpSocket = (TCPSocket *) p_tcpSocketThread;

    // Receive data from socket (timeout 30 seconds)
    int l_iMessageSize = l_tcpSocket->recv( l_rcvBuffer , SOCK_BUFFER_SIZE );

    if ( l_iMessageSize != 0 )
    {
        std::cout << l_rcvBuffer << std::endl;
    }
}