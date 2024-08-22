#pragma once

typedef struct Listener_Socket listener_socket_t;


/** @brief Initializes a listener socket that listens on the provided
 *         port on all of the interfaces for the host.
 *
 *  @param sock The listener_socket_t to initialize.
 *
 *  @param port The port on which to listen.
 *
 *  @return 0, indicating success, or -1, indicating that it failed to
 *          listen.
 */
int listener_init(listener_socket_t *sock, unsigned int port);


/** @brief Accept a new connection
 *
 *  @param sock The Listener_Socket from which to get the new
 *              connection.
 *
 *  @return An socket descriptor (int) for the new connection, or -1, if there is an
 *          error. Sets errno according to any errors that occur.
 */
int listener_accept(listener_socket_t *sock);
