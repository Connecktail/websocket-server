#include "../include/websocket.h"
#include "../include/main.h"
#include "../include/actions.h"
#include <cjson/cJSON.h>

extern PGconn *conn;
extern struct ws_events evs;

void onopen(ws_cli_conn_t *client)
{
	((void)client);
	printf("Connected!\n");
}

void onclose(ws_cli_conn_t *client)
{
	((void)client);
	printf("Disconnected!\n");
}

void onmessage(ws_cli_conn_t *client, const unsigned char *msg, uint64_t size, int type)
{
	cJSON *json = cJSON_Parse((const char*)msg);
	cJSON *json_action = cJSON_GetObjectItemCaseSensitive(json, "action");
	printf("Action: %s\n", json_action->valuestring);
	
	if (strcmp(json_action->valuestring, "get_cocktails") == 0) {
        sendCocktails(client);
	}
	if (strcmp(json_action->valuestring, "get_bottles") == 0) {
        sendBottles(client);
	}
	if (strcmp(json_action->valuestring, "order") == 0) {
	    cJSON *json_order = cJSON_GetObjectItemCaseSensitive(json, "order");
		printf("order\n");
		// process client order
        processOrder(client, json_order);
	}
}