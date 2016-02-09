#ifndef QUERY_BY_ID_SERVER_REQUEST_H_
#define QUERY_BY_ID_SERVER_REQUEST_H_

#include "../main.h"

// process request
void query_by_id_request__process(zmq_msg_t *msg_req, zmq_msg_t *msg_res);

#endif /* QUERY_BY_ID_SERVER_REQUEST_H_ */
