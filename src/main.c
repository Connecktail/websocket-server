#include "../include/main.h"

PGconn *conn;
struct ws_events evs;
client_t *clients;
int nb_clients;
int shmid;


int main(int argc, char **argv)
{
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

	// start thread to send order status to clients
	pthread_t thread_send_status;
	pthread_create(&thread_send_status, NULL, check_status_update, NULL);

	pthread_join(thread_send_status, NULL);

	return (0);
}

void *check_status_update() {	
	while (1) {
		// check for messages in queue
		sleep(1);
	}
}