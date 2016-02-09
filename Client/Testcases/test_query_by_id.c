#include "test_query_by_id.h"

// functions
QueryByIdResponse *test_query_by_id__query(void *socket, const uint64_t id);

// do query by id test
void test_query_by_id__do(void *socket)
{
    // get non existing employee by id
    QueryByIdResponse *res = test_query_by_id__query(socket, 100);
    assert(res);
    assert(res->employee);
    assert(res->employee->name);
    assert(res->employee->name[0] == '\0');
    query_by_id_response__free_unpacked(res, NULL);

    // get non existing employee by id
    res = test_query_by_id__query(socket, 101);
    assert(res);
    assert(res->employee);
    assert(res->employee->name);
    assert(res->employee->id == 101);
    assert(strcmp(res->employee->name, "Name 101") == 0);
    assert(res->employee->gender == EMPLOYEE__GENDER__FEMALE);
    assert(res->employee->last_10_annual_bonus == 101.00);
    assert(res->employee->last_10_annual_salary == 111.00);
    assert(res->employee->last_10_annual_sales == 121.00);
    query_by_id_response__free_unpacked(res, NULL);
}

// query employee by id
QueryByIdResponse *test_query_by_id__query(void *socket, const uint64_t id)
{
    assert(socket);

    // fill protobuf message
    QueryByIdRequest query_request;
    query_by_id_request__init(&query_request);
    query_request.id = id;

    // get protobuf message data
    size_t data_req_size = query_by_id_request__get_packed_size(&query_request) + 1;
    unsigned char *data_req = (unsigned char *)malloc(data_req_size);
    assert(data_req);
    *data_req = MSG_QUERY_BY_ID_REQUEST;

    // write protobuf message data
    query_by_id_request__pack(&query_request, data_req + 1);

    // set zmq message data
    zmq_msg_t msg_req, msg_res;
    assert(zmq_msg_init_size(&msg_req, data_req_size) == 0);
    memcpy(zmq_msg_data(&msg_req), data_req, data_req_size);
    free(data_req);

    // send
    int msg_req_size = zmq_msg_size(&msg_req);
    assert(zmq_msg_send(&msg_req, socket, 0) == msg_req_size);

    // receive
    assert(zmq_msg_init(&msg_res) == 0);
    int received = zmq_msg_recv(&msg_res, socket, 0);
    assert(received > 0);

    // get response data
    unsigned char *data_res = zmq_msg_data(&msg_res);
    size_t data_res_size = zmq_msg_size(&msg_res);
    assert(data_res);
    assert(data_res[0] == MSG_QUERY_BY_ID_RESPONSE);
    assert(data_res_size > 0);

    // unpack protobuf message
    return query_by_id_response__unpack(NULL, data_res_size - 1, data_res + 1);
}
