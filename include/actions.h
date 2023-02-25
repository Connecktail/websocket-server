#ifndef ACTION_H
#define ACTION_H
#include <ws.h>
#include "main.h"

/**
 * @brief Callback when a client connects to the websocket
*/
void clientConnected(ws_cli_conn_t *client);

/**
 * @brief Callback when a client disconnects from the websocket
*/
void clientDisconnected(ws_cli_conn_t *client);

/**
 * @brief Send the list of cocktails to the client
 * @param client A pointer to a ws_cli_conn_t object
*/
void sendCocktails(ws_cli_conn_t *client);

/**
 * @brief Send the list of bottles to the client
 * @param client A pointer to a ws_cli_conn_t object
*/
void sendBottles(ws_cli_conn_t *client);

/**
 * @brief Process the order from a clien
 * @param client A pointer to a ws_cli_conn_t object
 * @param json_order A pointer to a cJSON object that contains the information about the client's order
*/
void processOrder(ws_cli_conn_t *client, cJSON *json_order);

#endif