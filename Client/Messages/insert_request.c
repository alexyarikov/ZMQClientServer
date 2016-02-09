#include "insert_request.h"

// functions
bool insert_request__get_message(zmq_msg_t *msg);
bool insert_request__fill(InsertRequest *msg);
void insert_request__get_data(InsertRequest *msg, void **data, size_t *data_size);

// get zmq message
bool insert_request__get_message(zmq_msg_t *msg)
{
   // initialize protobuf message
   char name[EMPLOYEE_NAME_SIZE] = { 0 };

   Employee employee;
   employee__init(&employee);
   employee.name = name;

   InsertRequest insert_request;
   insert_request__init(&insert_request);
   insert_request.employee = &employee;

   // fill protobuf message data
   if (!insert_request__fill(&insert_request))
      return false;

   // get protobuf message data
   void *data = NULL;
   size_t data_size = 0;
   insert_request__get_data(&insert_request, &data, &data_size);

   // set zmq message data size
   assert(zmq_msg_init_size(msg, data_size) == 0);

   // set zmq message data
   memcpy(zmq_msg_data(msg), data, data_size);

   // free protobuf message data
   free(data);

   return true;
}

// fill message with user input data
bool insert_request__fill(InsertRequest *msg)
{
   assert(msg);

   // id
   printf("id: ");
   scanf("%ld", &msg->employee->id);

   // name
   printf("name: ");
   scanf("%s", msg->employee->name);

   // gender
   printf("gender (m/f): ");
   char str[16] = { 0 };
   scanf("%s", str);

   if (str[0] != 'm' && str[0] != 'f')
   {
      printf("invalid gender\r\n\n");
      return false;
   }

   msg->employee->gender =
         (str[0] == 'm') ? EMPLOYEE__GENDER__MALE : EMPLOYEE__GENDER__FEMALE;

   // date of birth
   printf("date of birth (dd/mm/yyyy): ");
   scanf("%s", str);
   if ((msg->employee->date_of_birth = str2date(str)) == 0)
   {
      printf("invalid date\r\n\n");
      return false;
   }

   // last 10 years annual data
   printf("last 10 years annual salary: ");
   scanf("%lf", &msg->employee->last_10_annual_salary);

   printf("last 10 years annual bonus: ");
   scanf("%lf", &msg->employee->last_10_annual_bonus);

   printf("last 10 years annual sales: ");
   scanf("%lf", &msg->employee->last_10_annual_sales);

   printf("\r\n");

   return true;
}

// get protobuf message data
void insert_request__get_data(InsertRequest *msg, void **data, size_t *data_size)
{
   assert(msg);
   assert(data_size);

   // message size = size of protobuf packed message + 1 byte for message type
   *data_size = insert_request__get_packed_size(msg) + 1;

   // allocate memory for message data
   *data = malloc(*data_size);
   assert(*data);

   // write message type
   unsigned char *ptr = *data;
   *ptr = MSG_INSERT_REQUEST;

   // write protobuf message data
   insert_request__pack(msg, ptr + 1);
}
