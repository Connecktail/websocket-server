#include "../include/actions.h" 

extern PGconn *conn;
extern struct ws_events evs;

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
    printf("nothing\n");
}