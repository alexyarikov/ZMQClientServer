#include "delete_response.h"

// process response
void delete_response__process(zmq_msg_t *msg)
{
   assert(msg);

   // get response message data and size (first byte is message type)
   unsigned char *data = zmq_msg_data(msg);
   size_t data_size = zmq_msg_size(msg);

   // unpack protobuf message (first byte is message type)
   DeleteResponse *delete_response = delete_response__unpack(NULL, data_size - 1, data + 1);
   assert(delete_response);

   // check request result
   if (delete_response->result)
      printf("[OK] request processed successfully\r\n\n");
   else
      printf("[OK] request failed: employee not found\r\n\n");

   // free protobuf message
   delete_response__free_unpacked(delete_response, NULL);
}
