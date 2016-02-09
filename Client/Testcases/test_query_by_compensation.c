#include "test_query_by_compensation.h"

// functions
QueryByCompensationRangeResponse *test_query_by_compensation__query(void *socket, const double min, const double max);

// do query by compensation range test
void test_query_by_compensation__do(void *socket)
{
    // query whole range
    QueryByCompensationRangeResponse *res = test_query_by_compensation__query(socket, 9.99, 100008.01);
    assert(res);
    assert(res->count == 25000);
    query_by_compensation_range_response__free_unpacked(res, NULL);

    // query part range
    res = test_query_by_compensation__query(socket, 11.99, 20.01);
    assert(res);
    assert(res->count == 3);
    query_by_compensation_range_response__free_unpacked(res, NULL);
}

// query number of employees by compensation range
QueryByCompensationRangeResponse *test_query_by_compensation__query(void *socket, const double min, const double max)
{
    assert(socket);

    // fill protobuf message
    QueryByCompensationRangeRequest query_request;
    query_by_compensation_range_request__init(&query_request);
    query_request.min = min;
    query_request.max = max;

    // get protobuf message data
    size_t data_req_size = query_by_compensation_range_request__get_packed_size(&query_request) + 1;
    unsigned char *data_req = (unsigned char *)malloc(data_req_size);
    assert(data_req);
    *data_req = MSG_QUERY_BY_COMPENSATION_RANGE_REQUEST;

    // write protobuf message data
    query_by_compensation_range_request__pack(&query_request, data_req + 1);

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
    assert(data_res[0] == MSG_QUERY_BY_COMPENSATION_RANGE_RESPONSE);
    assert(data_res_size > 0);

    // unpack protobuf message
    return query_by_compensation_range_response__unpack(NULL, data_res_size - 1, data_res + 1);
}
