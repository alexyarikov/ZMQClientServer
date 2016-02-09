#include "query_by_compensation_range_request.h"
#include "query_by_compensation_range_response.h"
#include "../Database/database.h"

// process request
void query_by_compensation_range_request__process(zmq_msg_t *msg_req, zmq_msg_t *msg_res)
{
   assert(msg_req);
   assert(msg_res);

   // get request message data and size
   unsigned char *req_data = zmq_msg_data(msg_req);
   size_t req_data_size = zmq_msg_size(msg_req);

   // unpack protobuf message (first byte is message type)
   QueryByCompensationRangeRequest *query_request = query_by_compensation_range_request__unpack(NULL, req_data_size - 1, req_data + 1);
   assert(query_request);

   // query data from database
   uint64_t count = database__get_count_by_compensation_range(query_request->min, query_request->max);

   // free protobuf message
   query_by_compensation_range_request__free_unpacked(query_request, NULL);

   // get response message
   query_by_compensation_range_response__get_message(count, msg_res);

   printf("[%lu] query by compensation range request processed\r\n", pthread_self());
}
