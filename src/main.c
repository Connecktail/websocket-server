#include "../include/main.h"

PGconn *conn;
struct ws_events evs;
client_t *clients;
int nb_clients;
int shmid;
int msqid;


int main(int argc, char **argv)
{
    msqid = init_message_queue();

	clients = (client_t*)malloc(sizeof(client_t));
	nb_clients = 0;

    shmid = init_shared_memory();
	change_websocket_pid(getpid());

	// setup websocket server
	evs.onopen    = &onopen;
	evs.onclose   = &onclose;
	evs.onmessage = &onmessage;
	ws_socket(&evs, PORT, 1, 1000);

	// setup database connection
	conn = db_connect(db_host, db_database, db_user, db_password);

	int length;

	order_t **orders = get_orders(conn, &length);

	for(int i = 0; i < length; i++) {
		delete_order(conn, orders[i]->id);
	}

	// start thread to send order status to clients
	pthread_t thread_send_status;
	pthread_create(&thread_send_status, NULL, check_status_update, NULL);

	pthread_join(thread_send_status, NULL);

	return (0);
}

void *check_status_update() {	
	while (1) {
		msq_msg_t msg;
		receive_message(&msg, UPDATE_ORDER_STATUS, 0);

		for(int i = 0; i < nb_clients; i++) {
			if(*clients[i].order->id == msg.message.order_status.id_order) {
				clients[i].status->step = msg.message.order_status.step;
				clients[i].status->total_step = msg.message.order_status.total_step;
				clients[i].status->bottle = msg.message.order_status.bottle;
				clients[i].status->total_bottle = msg.message.order_status.total_bottle;
				strcpy(clients[i].status->message, msg.message.order_status.message);
				send_status_to_client(&clients[i]);
			}
		}
	}
}