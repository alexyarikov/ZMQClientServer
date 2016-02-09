#include "insert_request.h"
#include "insert_response.h"
#include "../Database/database.h"

// process request
void insert_request__process(zmq_msg_t *msg_req, zmq_msg_t *msg_res)
{
    assert(msg_req);
    assert(msg_res);

    // get request message data and size
    unsigned char *req_data = zmq_msg_data(msg_req);
    size_t req_data_size = zmq_msg_size(msg_req);

    // unpack protobuf message (first byte is message type)
    InsertRequest *insert_request = insert_request__unpack(NULL, req_data_size - 1, req_data + 1);
    assert(insert_request);

    // insert data into database
    char result_msg[64] = { 0 };
    bool result = database__insert(insert_request->employee, result_msg);

    // free protobuf message
    insert_request__free_unpacked(insert_request, NULL);

    // get response message
    insert_response__get_message(result, result_msg, msg_res);

    if (result)
        printf("[%lu] insert request processed: %s\r\n", pthread_self(), result_msg);
    else
        printf("[%lu] insert request failed: %s\r\n", pthread_self(), result_msg);
}
