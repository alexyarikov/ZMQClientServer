#ifndef QUERY_BY_COMPENSATION_RANGE_SERVER_RESPONSE_H_
#define QUERY_BY_COMPENSATION_RANGE_SERVER_RESPONSE_H_

#include "../main.h"

// get zmq message
bool query_by_compensation_range_response__get_message(const uint64_t request_result, zmq_msg_t *msg);

#endif /* QUERY_BY_COMPENSATION_RANGE_SERVER_RESPONSE_H_ */
