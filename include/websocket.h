#ifndef WEBSOCKET_H
#define WEBSOCKET_H
#include <ws.h>

/**
 * @brief Callback when a client connects to the websocket
 * @param client A pointer to a ws_cli_conn_t object
*/
void onopen(ws_cli_conn_t *client);

/**
 * @brief Callback when a client disconnects from the websocket
 * @param client A pointer to a ws_cli_conn_t object
*/
void onclose(ws_cli_conn_t *client);

/**
 * @brief Callback when a client sends a message to the server through the websocket
 * @param client A pointer to a ws_cli_conn_t object
 * @param msg A pointer to the message sent by the client
 * @param size The size of the message
 * @param type The type of the message
*/
void onmessage(ws_cli_conn_t *client, const unsigned char *msg, uint64_t size, int type);

#endif