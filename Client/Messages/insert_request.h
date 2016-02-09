#ifndef INSERT_CLIENT_REQUEST_H_
#define INSERT_CLIENT_REQUEST_H_

#include "../main.h"

// get zmq message
bool insert_request__get_message(zmq_msg_t *msg);

#endif /* INSERT_CLIENT_REQUEST_H_ */
