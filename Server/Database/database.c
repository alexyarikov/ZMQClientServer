#include "database.h"
#include "rbtree.h"

// database instances
struct rbtree *employees_by_id = NULL;
struct rbtree *employees_by_compensation = NULL;

// read preferred RW lock
pthread_rwlock_t lock = PTHREAD_RWLOCK_INITIALIZER;

// employees by id compare function
int compare_employees_by_id(void *left, void *right)
{
   struct DatabaseItem *lft = (struct DatabaseItem*)left;
   struct DatabaseItem *rgh = (struct DatabaseItem*)right;

   if (lft->id < rgh->id)
      return -1;
   if (lft->id > rgh->id)
      return 1;
   return 0;
}

// employees by compensation (salary + bonus) + id compare function
int compare_employees_by_compensation(void *left, void *right)
{
   struct DatabaseItem *lft = (struct DatabaseItem*)left;
   struct DatabaseItem *rgh = (struct DatabaseItem*)right;

   double compensation_lft = lft->last_10_annual_salary + lft->last_10_annual_bonus;
   double compensation_rgh = rgh->last_10_annual_salary + rgh->last_10_annual_bonus;

   if (compensation_lft < compensation_rgh)
      return -1;
   if (compensation_lft > compensation_rgh)
      return 1;

   // compensations are equal, then compare by id as compensation is not unique key
   return (compare_employees_by_id(left, right));
}

// create database
void database__create()
{
   // create trees
   employees_by_id = rbtree__create(compare_employees_by_id);
   assert(employees_by_id);

   employees_by_compensation = rbtree__create(compare_employees_by_compensation);
   assert(employees_by_compensation);
}

// destroy database
void database__destroy()
{
   // destroy trees
   rbtree__destroy(employees_by_id, true);
   employees_by_id = NULL;

   rbtree__destroy(employees_by_compensation, true);
   employees_by_compensation = NULL;

   // destroy lock
   pthread_rwlock_destroy(&lock);
}

// insert employeepthread_rwlock_rdlock
bool database__insert(const Employee *employee, char *result_msg)
{
   assert(employee);
   assert(result_msg);
   assert(employees_by_id);
   assert(employees_by_compensation);

   // fill database item data
   struct DatabaseItem *item = malloc(sizeof(struct DatabaseItem));
   assert(item);

   item->id = employee->id;
   strcpy(item->name, employee->name);
   item->gender = employee->gender;
   item->date_of_birth = employee->date_of_birth;
   item->last_10_annual_salary = employee->last_10_annual_salary;
   item->last_10_annual_bonus = employee->last_10_annual_bonus;
   item->last_10_annual_sales = employee->last_10_annual_sales;

   // write lock
   assert(pthread_rwlock_wrlock(&lock) == 0);

   // insert into database by identifier
   bool exist = false;
   struct DatabaseItem *old_item = rbtree__insert(employees_by_id, item, &exist);
   assert(old_item);

   // check update case
   if (exist)
   {
      // updating data can make second index inconsistent
      // hence we should rebuild the second index (delete item with old data && insert item with new data)
      assert(rbtree__delete(employees_by_compensation, old_item));
      assert(rbtree__insert(employees_by_compensation, item, NULL));

      // write unlock
      assert(pthread_rwlock_unlock(&lock) == 0);

      // free old item
      free(old_item);

      // set result
      strcpy(result_msg, "item updated");
   }
   else
   {
      // insert case:
      // insert into database by compensation
      assert(rbtree__insert(employees_by_compensation, item, NULL));

      // write unlock
      assert(pthread_rwlock_unlock(&lock) == 0);

      // set result
      strcpy(result_msg, "item inserted");
   }

   return true;
}

// delete employee
bool database__delete(const uint64_t employee_id)
{
   assert(employees_by_id);
   assert(employees_by_compensation);

   // fill database item data
   struct DatabaseItem item = { 0 };
   item.id = employee_id;

   // write lock
   assert(pthread_rwlock_wrlock(&lock) == 0);

   // delete from database by identifier
   struct DatabaseItem *deleted_item = rbtree__delete(employees_by_id, &item);

   // delete from database by compensation range
   if(deleted_item)
      assert(rbtree__delete(employees_by_compensation, deleted_item));

   // write unlock
   assert(pthread_rwlock_unlock(&lock) == 0);

   // free delete item
   free(deleted_item);

   return deleted_item != NULL;
}

// lookup employee by id
bool database__lookup(const uint64_t employee_id, Employee *employee)
{
   assert(employee);
   assert(employees_by_id);

   // fill database item data
   struct DatabaseItem item = { 0 };
   item.id = employee_id;

   // read lock
   assert(pthread_rwlock_rdlock(&lock) == 0);

   // lookup database
   struct DatabaseItem *lookup_item = (struct DatabaseItem*) rbtree__lookup(employees_by_id, &item);

   bool res = false;

   // copy employee data if found
   if (lookup_item)
   {
      employee->id = lookup_item->id;
      strcpy(employee->name, lookup_item->name);
      employee->gender = lookup_item->gender;
      employee->date_of_birth = lookup_item->date_of_birth;
      employee->last_10_annual_bonus = lookup_item->last_10_annual_bonus;
      employee->last_10_annual_salary = lookup_item->last_10_annual_salary;
      employee->last_10_annual_sales = lookup_item->last_10_annual_sales;
      res = true;
   }

   // read unlock
   assert(pthread_rwlock_unlock(&lock) == 0);

   return res;
}

// get count of employees by compensation range
uint64_t database__get_count_by_compensation_range(const double min, const double max)
{
   assert(employees_by_compensation);

   // fill database item min data so that salary + bonus = min
   struct DatabaseItem item_min = { 0 };
   item_min.last_10_annual_salary = min;

   // fill database item max data so that salary + bonus = max
   struct DatabaseItem item_max = { 0 };
   item_max.last_10_annual_salary = max;

   // read lock
   assert(pthread_rwlock_rdlock(&lock) == 0);

   // get count
   uint64_t res = rbtree__range_count(employees_by_compensation, &item_min, &item_max);

   // read unlock
   assert(pthread_rwlock_unlock(&lock) == 0);

   return res;
}
