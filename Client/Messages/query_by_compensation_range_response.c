#include "query_by_compensation_range_response.h"

// process response
void query_by_compensation_range_response__process(zmq_msg_t *msg)
{
    assert(msg);

    // get response message data and size (first byte is message type)
    unsigned char *data = zmq_msg_data(msg);
    size_t data_size = zmq_msg_size(msg);

    // unpack protobuf message (first byte is message type)
    QueryByCompensationRangeResponse *query_response = query_by_compensation_range_response__unpack(NULL, data_size - 1, data + 1);
    assert(query_response);

    // print result
    printf("[OK] %lu employee(-s) found\r\n\n", query_response->count);

    // free protobuf message
    query_by_compensation_range_response__free_unpacked(query_response, NULL);
}
