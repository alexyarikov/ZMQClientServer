#include "delete_request.h"

// functions
bool delete_request__fill(DeleteRequest *msg);
void delete_request__get_data(DeleteRequest *msg, void **data, size_t *data_size);

// get zmq message data
bool delete_request__get_message(zmq_msg_t *msg)
{
    DeleteRequest delete_request;
    delete_request__init(&delete_request);

    // fill protobuf message data with user input
    if (!delete_request__fill(&delete_request))
        return false;

    // get protobuf message data
    void *data = NULL;
    size_t data_size = 0;
    delete_request__get_data(&delete_request, &data, &data_size);

    // set zmq message data size
    assert(zmq_msg_init_size(msg, data_size) == 0);

    // set zmq message data
    memcpy(zmq_msg_data(msg), data, data_size);

    // free protobuf message data
    free(data);

    return true;
}

// fill message with user input data
bool delete_request__fill(DeleteRequest *msg)
{
    assert(msg);

    // name
    printf("id: ");
    scanf("%lu", &msg->id);

    printf("\r\n");

    return true;
}

// get protobuf message data
void delete_request__get_data(DeleteRequest *msg, void **data, size_t *data_size)
{
    assert(msg);
    assert(data_size);

    // message size = size of protobuf packed message + 1 byte for message type
    *data_size = delete_request__get_packed_size(msg) + 1;

    // allocate memory for message data
    *data = malloc(*data_size);
    assert(*data);

    // write message type
    unsigned char *ptr = *data;
    *ptr = MSG_DELETE_REQUEST;

    // write protobuf message data
    delete_request__pack(msg, ptr + 1);
}
