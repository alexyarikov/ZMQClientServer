#include "query_by_compensation_range_response.h"

// get protobuf message data
void query_by_compensation_range_response__get_data(QueryByCompensationRangeResponse *msg, void **data, size_t *data_size)
{
    assert(msg);
    assert(data_size);

    // message size = size of protobuf packed message + 1 byte for message type
    *data_size = query_by_compensation_range_response__get_packed_size(msg) + 1;

    // allocate memory for message data
    *data = malloc(*data_size);
    assert(*data);

    // write message type
    unsigned char *ptr = *data;
    *ptr = MSG_QUERY_BY_COMPENSATION_RANGE_RESPONSE;

    // write protobuf message data
    query_by_compensation_range_response__pack(msg, ptr + 1);
}

// get response message
bool query_by_compensation_range_response__get_message(const uint64_t request_result, zmq_msg_t *msg)
{
    // initialize protobuf message
    QueryByCompensationRangeResponse query_response;
    query_by_compensation_range_response__init(&query_response);
    query_response.count = request_result;

    // get protobuf message data
    void *data = NULL;
    size_t data_size = 0;
    query_by_compensation_range_response__get_data(&query_response, &data, &data_size);

    // set zmq message data size
    assert(zmq_msg_init_size(msg, data_size) == 0);

    // set zmq message data
    memcpy(zmq_msg_data(msg), data, data_size);

    // free protobuf message data
    free(data);

    return true;
}
