#ifndef QUERY_BY_COMPENSATION_RANGE_SERVER_REQUEST_H_
#define QUERY_BY_COMPENSATION_RANGE_SERVER_REQUEST_H_

#include "../main.h"

// process request
void query_by_compensation_range_request__process(zmq_msg_t *msg_req, zmq_msg_t *msg_res);

#endif /* QUERY_BY_COMPENSATION_RANGE_SERVER_REQUEST_H_ */
