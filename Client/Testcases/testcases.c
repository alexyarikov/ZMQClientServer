#include "testcases.h"
#include "test_insert.h"
#include "test_delete.h"
#include "test_query_by_id.h"
#include "test_query_by_compensation.h"

// functions
void testcases__run(const char *address, const int port);
void testcases__connect(const char *address, const int port);

// zmq
void *context = NULL;
void *socket = NULL;

// run testcases
void testcases__run(const char *address, const int port)
{
    // initialize random number generator
    srand(time(NULL));

    // connect to server
    testcases__connect(address, port);

    // do tests
    test_insert__do(socket);
    test_delete__do(socket);
    test_query_by_id__do(socket);
    test_query_by_compensation__do(socket);

    // free zmq
    zmq_close(socket);
    zmq_ctx_destroy(context);
}

// connect to server
void testcases__connect(const char *address, const int port)
{
    assert(address);
    assert(port > 0);

    // zmq context
    context = zmq_ctx_new();
    assert(context);

    // zmq socket to talk to server
    socket = zmq_socket(context, ZMQ_REQ);
    assert(socket);

    // make connect address
    char bind_addr[128] = { 0 };
    sprintf(bind_addr, "tcp://%s:%d", address, port);

    // connect to server
    assert(zmq_connect(socket, bind_addr) == 0);
}
