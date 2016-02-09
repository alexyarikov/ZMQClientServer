#include "delete_response.h"

// get protobuf message data
void delete_response__get_data(DeleteResponse *msg, void **data, size_t *data_size)
{
   assert(msg);
   assert(data_size);

   // message size = size of protobuf packed message + 1 byte for message type
   *data_size = delete_response__get_packed_size(msg) + 1;

   // allocate memory for message data
   *data = malloc(*data_size);
   assert(*data);

   // write message type
   unsigned char *ptr = *data;
   *ptr = MSG_DELETE_RESPONSE;

   // write protobuf message data
   delete_response__pack(msg, ptr + 1);
}

// get response message
bool delete_response__get_message(const bool request_result, zmq_msg_t *msg)
{
   // initialize protobuf message
   DeleteResponse delete_response;
   delete_response__init(&delete_response);
   delete_response.result = request_result;

   // get protobuf message data
   void *data = NULL;
   size_t data_size = 0;
   delete_response__get_data(&delete_response, &data, &data_size);

   // set zmq message data size
   assert(zmq_msg_init_size(msg, data_size) == 0);

   // set zmq message data
   memcpy(zmq_msg_data(msg), data, data_size);

   // free protobuf message data
   free(data);

   return true;
}
