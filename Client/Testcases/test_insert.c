#include "test_insert.h"

// functions
InsertResponse *test_insert__insert(void *socket, const uint64_t id, const char *name, const Employee__Gender gender, const time_t date_of_birth, const double bonus, const double salary, const double sales);

// do insert test
void test_insert__do(void *socket)
{
   // insert 5000 employees
   int i;
   for (i = 0; i < 50000; i++)
   {
      char name[EMPLOYEE_NAME_SIZE] = { 0 };
      sprintf(name, "Name %d", i);

      InsertResponse *res = test_insert__insert(socket, i, name,
            (i % 2 == 0) ? EMPLOYEE__GENDER__MALE : EMPLOYEE__GENDER__FEMALE, str2date("01/01/2001"), i, i + 10.00, i + 20.00);
      assert(res);
      assert(res->result);
      insert_response__free_unpacked(res, NULL);
   }
}

// insert employee
InsertResponse *test_insert__insert(void *socket, const uint64_t id, const char *name, const Employee__Gender gender, const time_t date_of_birth, const double bonus, const double salary, const double sales)
{
   assert(socket);
   assert(name);

   // fill protobuf message
   char emp_name[EMPLOYEE_NAME_SIZE] = { 0 };

   Employee employee;
   employee__init(&employee);
   employee.name = emp_name;

   InsertRequest insert_request;
   insert_request__init(&insert_request);
   insert_request.employee = &employee;

   insert_request.employee->id = id;
   strcpy(insert_request.employee->name, name);
   insert_request.employee->gender = gender;
   insert_request.employee->date_of_birth = date_of_birth;
   insert_request.employee->last_10_annual_bonus = bonus;
   insert_request.employee->last_10_annual_salary = salary;
   insert_request.employee->last_10_annual_sales = sales;

   // get protobuf message data
   size_t data_req_size = insert_request__get_packed_size(&insert_request) + 1;
   unsigned char *data_req = (unsigned char *) malloc(data_req_size);
   assert(data_req);
   *data_req = MSG_INSERT_REQUEST;

   // write protobuf message data
   insert_request__pack(&insert_request, data_req + 1);

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
   assert(data_res[0] == MSG_INSERT_RESPONSE);
   assert(data_res_size > 0);

   // unpack protobuf message
   return (insert_response__unpack(NULL, data_res_size - 1, data_res + 1));
}
