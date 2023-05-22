# Websocket server

## Purpose :

This process communicates with the web application via a websocket. It will handle the incoming messages from the web application and send the response to it. It will process the incoming orders, add them to the database and inform the device manager process, then the device manager process will send back new order's status and the websocket server will send it to the client concerned.

## Compilation :

### Prerequisites :

- lib cJSON installed
- lib pq installed
- lib ws installed
- lib db-utils installed
- lib msq-utils installed
- lib shm-utils installed

### Instructions : 

- clone the repository
- move to the root of the project
- execute the following commands :

```bash
make
```

It will create a build folder with the executable inside.

You are now able to launch the process with the following command :

```bash
./build/main
```

## Data structures :

**Client :**

Client structure that contains the client informations (websocket, order and status information).

```c
typedef struct {
    ws_cli_conn_t *client;
    order_t *order;
    status_message_t *status;
} client_t;
```

## Files :

### Actions :

This file contains the differents functions that will be called when an action is received via the websocket. For example, when the client send the "get_cocktails" action via the websocket, the "sendCocktails" function is called to send the list of cocktails to the client.

- Function called when the client send the "get_cocktails" action via the websocket :
```c
void sendCocktails(ws_cli_conn_t *client);
```

- Function called when the client send the "get_bottles" action via the websocket :
```c
void sendBottles(ws_cli_conn_t *client);
```

- Function called when the client send the "order" action via the websocket (when he validates his order) :
```c
void processOrder(ws_cli_conn_t *client, cJSON *json_order);
```

- Function called when the client send the "check_order" action via the websocket (when he wants to know if he already has an order in progress) :
```c
void checkOrder(ws_cli_conn_t *client);
```

### Clients :

This file contains the functions used to manage the clients connected to the websocket server and the informations about their orders.

- Function to add a new client with his order to the list of clients :
```c
void add_client(ws_cli_conn_t *client, order_t *order)
```

- Function to initialize the status of a client (called in the previous function) :
```c
status_message_t *init_status(order_t *order)
```

- Function to send the new status of an order to the client concerned :
```c
void send_status_to_client(client_t *client)
```

### Websocket :

This file contains the event handlers for the websocket server (connection, disconnection and message received)

- Function called when a client connects to the websocket server :
```c
void onopen(ws_cli_conn_t *client);
```

- Function called when a client disconnects from the websocket server :
```c
void onclose(ws_cli_conn_t *client);
```

- Function called when a client sends a message to the websocket server :
```c
void onmessage(ws_cli_conn_t *client, const unsigned char *msg, uint64_t size, int type);
```

### Status : 

This file contains the functions for the thread that wait for message of type 1 in the message queue. When a message of type 1 is received, it means that an order's status has been updated, so we found the client who has the order concerned and we send him its new status.

```c
void *check_status_update()
```