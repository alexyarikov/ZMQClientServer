#ifndef QUERY_BY_ID_CLIENT_H_
#define QUERY_BY_ID_CLIENT_H_

#include "../main.h"

// get zmq message
bool query_by_id_request__get_message(zmq_msg_t *msg);

#endif /* QUERY_BY_ID_CLIENT_H_ */
