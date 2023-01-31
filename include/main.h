#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <cjson/cJSON.h>
#include <ws.h>
#include <db-utils/dbutils.h>

#define PORT 6543

void onopen(ws_cli_conn_t *client);
void onclose(ws_cli_conn_t *client);
void onmessage(ws_cli_conn_t *client, const unsigned char *msg, uint64_t size, int type);
void onerror(ws_cli_conn_t *client, char *message, size_t length);
void *send_status();