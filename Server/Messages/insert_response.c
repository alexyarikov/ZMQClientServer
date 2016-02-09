#include "insert_response.h"

// get protobuf message data
void insert_response__get_data(InsertResponse *msg, void **data, size_t *data_size)
{
    assert(msg);
    assert(data_size);

    // message size = size of protobuf packed message + 1 byte for message type
    *data_size = insert_response__get_packed_size(msg) + 1;

    // allocate memory for message data
    *data = malloc(*data_size);
    assert(*data);

    // write message type
    unsigned char *ptr = *data;
    *ptr = MSG_INSERT_RESPONSE;

    // write protobuf message data
    insert_response__pack(msg, ptr + 1);
}

// get response message
bool insert_response__get_message(const bool request_result, char *request_result_msg, zmq_msg_t *msg)
{
    assert(request_result_msg);

    // initialize protobuf message
    InsertResponse insert_response;
    insert_response__init(&insert_response);
    insert_response.result = request_result;
    insert_response.result_msg = request_result_msg;

    // get protobuf message data
    void *data = NULL;
    size_t data_size = 0;
    insert_response__get_data(&insert_response, &data, &data_size);

    // set zmq message data size
    assert(zmq_msg_init_size(msg, data_size) == 0);

    // set zmq message data
    memcpy(zmq_msg_data(msg), data, data_size);

    // free protobuf message data
    free(data);

    return true;
}
