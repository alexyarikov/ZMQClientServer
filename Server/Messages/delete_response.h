#ifndef DELETE_RESPONSE_H_
#define DELETE_RESPONSE_H_

#include "../main.h"

// get zmq message
bool delete_response__get_message(const bool request_result, zmq_msg_t *msg);

#endif /* DELETE_RESPONSE_H_ */
