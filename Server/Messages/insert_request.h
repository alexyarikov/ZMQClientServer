#ifndef INSERT_SERVER_REQUEST_H_
#define INSERT_SERVER_REQUEST_H_

#include "../main.h"

// process request
void insert_request__process(zmq_msg_t *msg_req, zmq_msg_t *msg_res);

#endif /* INSERT_SERVER_REQUEST_H_ */
