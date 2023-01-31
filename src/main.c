#include "../include/main.h"

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

void onmessage(ws_cli_conn_t *client,
    const unsigned char *msg, uint64_t size, int type)
{
	cJSON *json = cJSON_Parse((const char*)msg);
	cJSON *json_action = cJSON_GetObjectItemCaseSensitive(json, "action");
	printf("Action: %s\n", json_action->valuestring);
	
	if (strcmp(json_action->valuestring, "getCocktails") == 0) {
		printf("Get cocktails\n");
		// envoyer liste cocktails
	}
	if (strcmp(json_action->valuestring, "getBottles") == 0) {
		printf("Get bottles\n");
		// envoyer liste bouteilles
	}
	if (strcmp(json_action->valuestring, "order") == 0) {
		printf("order\n");
		// traiter la commande
	}

    // ws_sendframe_txt(client, "{\"test\": \"commande\"}");
}

PGconn *conn;

int main(int argc, char **argv)
{
	struct ws_events evs;
	evs.onopen    = &onopen;
	evs.onclose   = &onclose;
	evs.onmessage = &onmessage;
	ws_socket(&evs, PORT, 1, 1000);

	pthread_t thread_send_status;
	pthread_create(&thread_send_status, NULL, send_status, NULL);
	pthread_join(thread_send_status, NULL);

	return (0);
}

void *send_status() 
{	
	while (1) {
		// check boite aux lettres
		sleep(1);
	}
	printf("Rien\n");
}