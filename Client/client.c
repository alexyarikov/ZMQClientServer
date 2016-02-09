#include "client.h"
#include "Messages/messages.h"

// functions
enum result client__get_request(zmq_msg_t *msg);
bool client__receive_response(void *socket, zmq_msg_t *msg);
bool client__send_request(void *socket, zmq_msg_t *msg);
bool client__process_response(zmq_msg_t *msg);

// request preparing result
enum result
{
    OK, ERROR, EXIT
};

// run client
bool client__run(const char *address, const int port)
{
    // zmq context
    void *context = zmq_ctx_new();
    assert(context);

    // zmq socket to talk to server
    void *socket = zmq_socket(context, ZMQ_REQ);
    assert(socket);

    // make connect address
    char bind_addr[128] = { 0 };
    sprintf(bind_addr, "tcp://%s:%d", address, port);

    // connect to server
    bool res = zmq_connect(socket, bind_addr) == 0;
    if (res)
        printf("connection to server on %s established\r\n\n", bind_addr);
    else
        printf("failed to connect to server on %s: %s\r\n\n", bind_addr, zmq_strerror(errno));

    // exchange messages
    bool stop = !res;
    while (res && !stop)
    {
        // fill zmq message with request data
        zmq_msg_t msg_req;
        switch (client__get_request(&msg_req))
        {
            case OK:
            {
                // send request
                res = client__send_request(socket, &msg_req);
                // receive && process response
                zmq_msg_t msg_res;
                res = res && client__receive_response(socket, &msg_res);
                res = res && client__process_response(&msg_res);
                break;
            }
            case ERROR:
                break;
            case EXIT:
            {
                stop = true;
                break;
            }
        }
    }

    // free zmq
    zmq_close(socket);
    zmq_ctx_destroy(context);

    return res;
}

// get next request message
enum result client__get_request(zmq_msg_t *msg)
{
    printf("Choose action:\r\n");
    printf("1. Add/update employee data\r\n");
    printf("2. Delete employee data\r\n");
    printf("3. Get employee data by identifier data\r\n");
    printf("4. Get employees count by compensation range\r\n");
    printf("5. Exit application\r\n");

    int action;
    if (scanf("%d", &action) != 1)
        return EXIT;

    switch (action)
    {
        case 1:
            return insert_request__get_message(msg) ? OK : ERROR;
        case 2:
            return delete_request__get_message(msg) ? OK : ERROR;
        case 3:
            return query_by_id_request__get_message(msg) ? OK : ERROR;
        case 4:
            return
                query_by_compensation_range_request__get_message(msg) ? OK : ERROR;
        default:
            break;
    }

    return EXIT;
}

// receive response
bool client__receive_response(void *socket, zmq_msg_t *msg)
{
    assert(socket);
    assert(msg);

    // initialize response message
    assert(zmq_msg_init(msg) == 0);

    // receive response message
    int received = zmq_msg_recv(msg, socket, 0);
    if (received < 1)
    {
        printf("failed to receive response: %s\r\n", zmq_strerror(errno));
        return false;
    }

    return true;
}

// send request message
bool client__send_request(void *socket, zmq_msg_t *msg)
{
    assert(socket);
    assert(msg);

    // send message
    int msg_size = zmq_msg_size(msg);
    bool res = zmq_msg_send(msg, socket, 0) == msg_size;

    if (!res)
        printf("failed to send request: %s\r\n", zmq_strerror(errno));

    return res;
}

// process response
bool client__process_response(zmq_msg_t *msg)
{
    assert(msg);

    // get response data
    unsigned char *data = zmq_msg_data(msg);
    assert(data);

    // check response message type
    switch (data[0])
    {
        case MSG_INSERT_RESPONSE:
        {
            insert_response__process(msg);
            break;
        }
        case MSG_DELETE_RESPONSE:
        {
            delete_response__process(msg);
            break;
        }
        case MSG_QUERY_BY_ID_RESPONSE:
        {
            query_by_id_response__process(msg);
            break;
        }
        case MSG_QUERY_BY_COMPENSATION_RANGE_RESPONSE:
        {
            query_by_compensation_range_response__process(msg);
            break;
        }
        default:
            printf("unknown message received, will be skipped\r\n");
            return true;
    }

    return true;
}
