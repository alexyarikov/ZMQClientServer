#ifndef DATABASE_H_
#define DATABASE_H_

#include "../main.h"
#include "rbtree.h"

// database item
struct DatabaseItem
{
   uint64_t id;
   char name[EMPLOYEE_NAME_SIZE];
   Employee__Gender gender;
   uint64_t date_of_birth;
   double last_10_annual_salary;
   double last_10_annual_bonus;
   double last_10_annual_sales;
};

// database operations
void database__create();
void database__destroy();
bool database__insert(const Employee *employee, char *result_msg);
bool database__delete(const uint64_t employee_id);
bool database__lookup(const uint64_t employee_id, Employee *employee);
uint64_t database__get_count_by_compensation_range(const double min, const double max);

#endif /* DATABASE_H_ */
