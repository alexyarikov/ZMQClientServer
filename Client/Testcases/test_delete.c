#include "test_delete.h"

// functions
DeleteResponse *test_delete__delete(void *socket, const uint64_t id);

// do delete test
void test_delete__do(void *socket)
{
   // delete every second employee, last 5 shouldn't exists
   int i;
   for (i = 0; i < 50005; i = i + 2)
   {
      DeleteResponse *res = test_delete__delete(socket, i);
      assert(res);

      if (i < 50000)
         assert(res->result);
      else
         assert(!res->result);

      delete_response__free_unpacked(res, NULL);
   }
}

// delete employee
DeleteResponse *test_delete__delete(void *socket, const uint64_t id)
{
   assert(socket);

   // fill protobuf message
   DeleteRequest delete_request;
   delete_request__init(&delete_request);
   delete_request.id = id;

   // get protobuf message data
   size_t data_req_size = delete_request__get_packed_size(&delete_request) + 1;
   unsigned char *data_req = (unsigned char *) malloc(data_req_size);
   assert(data_req);
   *data_req = MSG_DELETE_REQUEST;

   // write protobuf message data
   delete_request__pack(&delete_request, data_req + 1);

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
   assert(data_res[0] == MSG_DELETE_RESPONSE);
   assert(data_res_size > 0);

   // unpack protobuf message
   return (delete_response__unpack(NULL, data_res_size - 1, data_res + 1));
}
