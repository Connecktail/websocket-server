#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <cjson/cJSON.h>
#include <wsserver/ws.h>
#include <db-utils/dbutils.h>
#include "websocket.h"
#include "actions.h"

#define db_host "localhost"
#define db_database "connecktail"
#define db_user "admin"
#define db_password "admin"

#define PORT 6543 // port to listen to

void *send_status();
