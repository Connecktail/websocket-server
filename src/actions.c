#include "../include/actions.h" 

extern PGconn *conn;
extern struct ws_events evs;
extern client_t *clients;
extern int nb_clients;
extern int shmid;

void sendCocktails(ws_cli_conn_t *client){
    cJSON *respObject = cJSON_CreateObject();
    cJSON *action = cJSON_CreateString("get_cocktails");
    cJSON *cocktails = cJSON_CreateArray();
    cJSON *cocktail;
    cJSON *cocktail_id;
    cJSON *cocktail_name;
    cJSON *cocktail_description;
    cJSON *cocktail_price;
    cJSON *cocktail_image_url;

    cJSON_AddItemToObject(respObject, "action", action);
    cJSON_AddItemToObject(respObject, "cocktails", cocktails);

	cocktail_t **liste_cocktails;
    int length;

    liste_cocktails = get_cocktails(conn, &length);

	for(int i = 0; i < length; i++) {
        if(!liste_cocktails[i]->personalized) {
            cocktail = cJSON_CreateObject();
            cJSON_AddItemToArray(cocktails, cocktail);

            cocktail_id = cJSON_CreateNumber(*liste_cocktails[i]->id);
            cocktail_name = cJSON_CreateString(liste_cocktails[i]->name);
            cocktail_description = cJSON_CreateString(liste_cocktails[i]->description);
            cocktail_price = cJSON_CreateNumber(liste_cocktails[i]->price);
            cocktail_image_url = cJSON_CreateString(liste_cocktails[i]->image_url);

            cJSON_AddItemToObject(cocktail, "id", cocktail_id);
            cJSON_AddItemToObject(cocktail, "name", cocktail_name);
            cJSON_AddItemToObject(cocktail, "description", cocktail_description);
            cJSON_AddItemToObject(cocktail, "price", cocktail_price);
            cJSON_AddItemToObject(cocktail, "image_url", cocktail_image_url);
        }
    }

    char *string = cJSON_Print(respObject);

    ws_sendframe_txt(client, string);
}

void sendBottles(ws_cli_conn_t *client){
    cJSON *respObject = cJSON_CreateObject();
    cJSON *action = cJSON_CreateString("get_bottles");
    cJSON *bottles = cJSON_CreateArray();
    cJSON *bottle;
    cJSON *bottle_id;
    cJSON *bottle_name;
    cJSON *bottle_quantity;
    cJSON *bottle_url;
    cJSON *bottle_price;

    cJSON_AddItemToObject(respObject, "action", action);
    cJSON_AddItemToObject(respObject, "bottles", bottles);

	bottle_t **liste_bottles;
    int length;

    liste_bottles = get_bottles(conn, &length);

	for(int i = 0; i < length; i++) {
        bottle = cJSON_CreateObject();
        cJSON_AddItemToArray(bottles, bottle);

        bottle_id = cJSON_CreateNumber(*liste_bottles[i]->id);
        bottle_name = cJSON_CreateString(liste_bottles[i]->name);
        bottle_quantity = cJSON_CreateNumber(liste_bottles[i]->quantity);
        bottle_url = cJSON_CreateString(liste_bottles[i]->url);
        bottle_price = cJSON_CreateNumber(liste_bottles[i]->price);

        cJSON_AddItemToObject(bottle, "id", bottle_id);
        cJSON_AddItemToObject(bottle, "name", bottle_name);
        cJSON_AddItemToObject(bottle, "quantity", bottle_quantity);
        cJSON_AddItemToObject(bottle, "url", bottle_url);
        cJSON_AddItemToObject(bottle, "price", bottle_price);
    }

    char *string = cJSON_Print(respObject);

    ws_sendframe_txt(client, string);
}

void processOrder(ws_cli_conn_t *client, cJSON *json_order){
    if(nb_clients+1 <= MAX_CLIENTS) {
        order_t *order = malloc(sizeof(order_t));
        cocktail_t *cocktail = malloc(sizeof(cocktail_t));

        cJSON *j_cocktail;
        cJSON *j_cocktails = cJSON_GetObjectItemCaseSensitive(json_order, "cocktails");
        cJSON *price = cJSON_GetObjectItemCaseSensitive(json_order, "total");

        order->nb_cocktails = 0;
        order->cocktails = NULL;
        if (price->valuedouble > 0){
            order->price = price->valuedouble;
        }
        cJSON_ArrayForEach(j_cocktail, j_cocktails) {
            cJSON *cocktail_id = cJSON_GetObjectItemCaseSensitive(j_cocktail, "recipe");
            cJSON *cocktail_number = cJSON_GetObjectItemCaseSensitive(j_cocktail, "number");
            id_db_t id = malloc(sizeof(id_db_t));
            *id = cocktail_id->valueint;
            int number = cocktail_number->valueint;

            cocktail = get_cocktail_by_id(conn, id);

            for(int i = 0; i < number; i++) {
                order->cocktails = realloc(order->cocktails, sizeof(cocktail_t *) * (order->nb_cocktails + 1));
                order->cocktails[order->nb_cocktails++] = cocktail;
            }
        }

        insert_order(conn, order);

        add_client(client, order);

        shm_t *shm;
        shm = get_shm();

        kill(shm->device_handler_pid, SIGUSR2);
    } else {
        // nbr max clients
    }
}