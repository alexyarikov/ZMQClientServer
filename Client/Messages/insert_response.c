#include "insert_response.h"

// process response
void insert_response__process(zmq_msg_t *msg)
{
    assert(msg);

    // get response message data and size (first byte is message type)
    unsigned char *data = zmq_msg_data(msg);
    size_t data_size = zmq_msg_size(msg);

    // unpack protobuf message (first byte is message type)
    InsertResponse *insert_response = insert_response__unpack(NULL, data_size - 1, data + 1);
    assert(insert_response);

    // check request result
    if (insert_response->result)
        printf("[OK] request processed successfully: %s\r\n\n", insert_response->result_msg);
    else
        printf("[ERROR] request failed: %s\r\n\n", insert_response->result_msg);

    // free protobuf message
    insert_response__free_unpacked(insert_response, NULL);
}
