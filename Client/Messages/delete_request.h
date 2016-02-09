#ifndef DELETE_CLIENT_REQUEST_H_
#define DELETE_CLIENT_REQUEST_H_

#include "../main.h"

// get zmq message
bool delete_request__get_message(zmq_msg_t *msg);

#endif /* DELETE_CLIENT_REQUEST_H_ */
