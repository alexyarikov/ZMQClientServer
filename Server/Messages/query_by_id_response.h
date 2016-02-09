#ifndef QUERY_BY_ID_SERVER_RESPONSE_H_
#define QUERY_BY_ID_SERVER_RESPONSE_H_

#include "../main.h"

// get zmq message
bool query_by_id_response__get_message(Employee *request_result, zmq_msg_t *msg);

#endif /* QUERY_BY_ID_SERVER_RESPONSE_H_ */
