#include "delete_request.h"
#include "delete_response.h"
#include "../Database/database.h"

// process request
void delete_request__process(zmq_msg_t *msg_req, zmq_msg_t *msg_res)
{
    assert(msg_req);
    assert(msg_res);

    // get request message data and size
    unsigned char *req_data = zmq_msg_data(msg_req);
    size_t req_data_size = zmq_msg_size(msg_req);

    // unpack protobuf message (first byte is message type)
    DeleteRequest *delete_request = delete_request__unpack(NULL, req_data_size - 1, req_data + 1);
    assert(delete_request);

    // delete data in database
    bool res = database__delete(delete_request->id);

    // free protobuf message
    delete_request__free_unpacked(delete_request, NULL);

    // get response message
    delete_response__get_message(res, msg_res);

    printf("[%lu] delete request processed\r\n", pthread_self());
}
