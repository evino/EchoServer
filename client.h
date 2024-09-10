#pragma once


/**
 * @brief Create a new socket for the client
 * 
 * @param void
 * 
 * @return A socket descriptor (int) for the new socket, or -1, if there is an
 *          error. Sets errno according to any errors that occur.
 * 
 */
int Client_Socket_Init();


/**
 * @brief Connect client-side socket to server
 * 
 * @param sockfd Socket-descriptor of client-side socket
 * 
 * @return 0 for success, -1 for errors. In case of error, updates errno.
 * 
 */
int Client_Connect(int sockfd);
