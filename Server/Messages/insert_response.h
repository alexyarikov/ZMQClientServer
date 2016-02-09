#ifndef INSERT_SERVER_RESPONSE_H_
#define INSERT_SERVER_RESPONSE_H_

#include "../main.h"

bool insert_response__get_message(const bool request_result, char *request_result_msg, zmq_msg_t *msg);

#endif /* INSERT_SERVER_RESPONSE_H_ */
