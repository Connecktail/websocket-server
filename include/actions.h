#ifndef ACTION_H
#define ACTION_H
#include "main.h"

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
 * @brief Process the order from a client
 * @param client A pointer to a ws_cli_conn_t object
 * @param json_order A pointer to a cJSON object that contains the information about the client's order
*/
void processOrder(ws_cli_conn_t *client, cJSON *json_order);

/**
 * @brief Check if a client already has an order (and if he has, send its status to him)
 * @param client A pointer to a ws_cli_conn_t object
*/
void checkOrder(ws_cli_conn_t *client);

#endif