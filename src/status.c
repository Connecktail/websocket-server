#include "../include/status.h"
#include <msq-utils/msqtypes.h>

extern int nb_clients;
extern int msqid;
extern client_t *clients;

void *check_status_update() {	
	while (1) {
		msq_msg_t msg;
		receive_message(&msg, UPDATE_ORDER_STATUS, 0);

		for(int i = 0; i < nb_clients; i++) {
			if(*clients[i].order->id == msg.message.order_status.id_order) {
				clients[i].status->cocktail = msg.message.order_status.cocktail;
				clients[i].status->total_cocktail = msg.message.order_status.total_cocktail;
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