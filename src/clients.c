#include "../include/clients.h"

extern PGconn *conn;
extern struct ws_events evs;
extern client_t *clients;
extern int nb_clients;

void add_client(ws_cli_conn_t *client, order_t *order) {
    clients = (client_t *)realloc(clients, sizeof(client_t) * (nb_clients + 1));
    clients[nb_clients] = (client_t) {0};
    clients[nb_clients].client = client;
    clients[nb_clients].order = order;

    clients[nb_clients].status = init_status(order);

    send_status_to_client(&clients[nb_clients]);

    nb_clients++;
}

status_message_t *init_status(order_t *order) {
    status_message_t *status = (status_message_t *)malloc(sizeof(status_message_t));
    status->step = 0;
    status->total_step = order->nb_cocktails;
    status->bottle = 0;
    status->total_bottle = 0;
    strcpy(status->message, "Order waiting to be taken");
    return status;
}

void send_status_to_client(client_t *client) {
    cJSON *respObject = cJSON_CreateObject();
    cJSON *action = cJSON_CreateString("status");
    cJSON *step = cJSON_CreateNumber(client->status->step);
    cJSON *total_step = cJSON_CreateNumber(client->status->total_step);
    cJSON *bottle = cJSON_CreateNumber(client->status->bottle);
    cJSON *total_bottle = cJSON_CreateNumber(client->status->total_bottle);
    cJSON *message = cJSON_CreateString(client->status->message);

    cJSON_AddItemToObject(respObject, "action", action);
    cJSON_AddItemToObject(respObject, "step", step);
    cJSON_AddItemToObject(respObject, "total_step", total_step);
    cJSON_AddItemToObject(respObject, "bottle", bottle);
    cJSON_AddItemToObject(respObject, "total_bottle", total_bottle);
    cJSON_AddItemToObject(respObject, "message", message);

    char *string = cJSON_Print(respObject);

    ws_sendframe_txt(client->client, string);
}