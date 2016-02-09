#include "query_by_id_request.h"
#include "query_by_id_response.h"
#include "../Database/database.h"

// process request
void query_by_id_request__process(zmq_msg_t *msg_req, zmq_msg_t *msg_res)
{
    assert(msg_req);
    assert(msg_res);

    // get request message data and size
    unsigned char *req_data = zmq_msg_data(msg_req);
    size_t req_data_size = zmq_msg_size(msg_req);

    // unpack protobuf message (first byte is message type)
    QueryByIdRequest *query_request = query_by_id_request__unpack(NULL, req_data_size - 1, req_data + 1);
    assert(query_request);

    // initialize employee
    char employee_name[EMPLOYEE_NAME_SIZE] = { 0 };

    Employee employee;
    employee__init(&employee);
    employee.name = employee_name;

    // query data from database
    database__lookup(query_request->id, &employee);

    // free protobuf message
    query_by_id_request__free_unpacked(query_request, NULL);

    // get response message
    query_by_id_response__get_message(&employee, msg_res);

    printf("[%lu] query by id request processed\r\n", pthread_self());
}
