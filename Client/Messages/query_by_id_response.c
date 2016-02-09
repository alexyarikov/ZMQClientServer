#include "query_by_id_response.h"

// process response
void query_by_id_response__process(zmq_msg_t *msg)
{
   assert(msg);

   // get response message data and size (first byte is message type)
   unsigned char *data = zmq_msg_data(msg);
   size_t data_size = zmq_msg_size(msg);

   // unpack protobuf message (first byte is message type)
   QueryByIdResponse *query_response = query_by_id_response__unpack(NULL, data_size - 1, data + 1);
   assert(query_response);

   // print result
   if (query_response->employee && query_response->employee->name && query_response->employee->name[0] != '\0')
   {
      char str[16] = { 0 };

      printf("[OK] employee found:\r\n\n");
      printf("id:                          %lu\r\n", query_response->employee->id);
      printf("name:                        %s\r\n", query_response->employee->name);
      printf("gender:                      %s\r\n",
            query_response->employee->gender == EMPLOYEE__GENDER__MALE ? "male" : "female");
      printf("date of birth:               %s\r\n", date2str(query_response->employee->date_of_birth, str));
      printf("last 10 years annual salary: %.2f\r\n", query_response->employee->last_10_annual_salary);
      printf("last 10 years annual bonus:  %.2f\r\n", query_response->employee->last_10_annual_bonus);
      printf("last 10 years annual sales:  %.2f\r\n\n", query_response->employee->last_10_annual_sales);
   }
   else
      printf("[OK] employee not found\r\n\n");

   // free protobuf message
   query_by_id_response__free_unpacked(query_response, NULL);
}
