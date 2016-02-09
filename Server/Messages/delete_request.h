#ifndef DELETE_REQUEST_H_
#define DELETE_REQUEST_H_

#include "../main.h"

// process request
void delete_request__process(zmq_msg_t *msg_req, zmq_msg_t *msg_res);

#endif /* DELETE_REQUEST_H_ */
