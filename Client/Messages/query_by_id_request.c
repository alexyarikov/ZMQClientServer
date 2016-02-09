#include "query_by_id_request.h"

// functions
bool query_by_id_request__fill(QueryByIdRequest *msg);
void query_by_id_request__get_data(QueryByIdRequest *msg, void **data, size_t *data_size);

// get zmq message data
bool query_by_id_request__get_message(zmq_msg_t *msg)
{
   QueryByIdRequest query_request;
   query_by_id_request__init(&query_request);

   // fill protobuf message data with user input
   if (!query_by_id_request__fill(&query_request))
      return false;

   // get protobuf message data
   void *data = NULL;
   size_t data_size = 0;
   query_by_id_request__get_data(&query_request, &data, &data_size);

   // set zmq message data size
   assert(zmq_msg_init_size(msg, data_size) == 0);

   // set zmq message data
   memcpy(zmq_msg_data(msg), data, data_size);

   // free protobuf message data
   free(data);

   return true;
}

// fill message with user input data
bool query_by_id_request__fill(QueryByIdRequest *msg)
{
   assert(msg);

   // name
   printf("id: ");
   scanf("%ld", &msg->id);

   printf("\r\n");

   return true;
}

// get protobuf message data
void query_by_id_request__get_data(QueryByIdRequest *msg, void **data, size_t *data_size)
{
   assert(msg);
   assert(data_size);

   // message size = size of protobuf packed message + 1 byte for message type
   *data_size = query_by_id_request__get_packed_size(msg) + 1;

   // allocate memory for message data
   *data = malloc(*data_size);
   assert(*data);

   // write message type
   unsigned char *ptr = *data;
   *ptr = MSG_QUERY_BY_ID_REQUEST;

   // write protobuf message data
   query_by_id_request__pack(msg, ptr + 1);
}
