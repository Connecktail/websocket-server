#ifndef CLIENT_H
#define CLIENT_H
#include "main.h"

typedef struct {
    ws_cli_conn_t *client;
    order_t *order;
    status_message_t *status;
} client_t;

/**
 * @brief Add a client to the list of clients
 * @param client A pointer to a ws_cli_conn_t object
*/
void add_client(ws_cli_conn_t *client, order_t *order);

/**
 * @brief Initialize the status of a client
 * @param order A pointer to a order_t object
 * @return A pointer to a status_t object
*/
status_message_t *init_status(order_t *order);

/**
 * @brief Send the status of an order to the client
 * @param client A pointer to a client_t object
*/
void send_status_to_client(client_t *client);

#endif