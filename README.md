# ZMQClientServer

PROBLEM:

Implement an in-memory database that consists of indexed table for storing sales data for a set of sales employees. The data stored will be: employee-id, employee name, gender, date of birth, plus data
for the last 10 years of annual salary, annual bonus, and annual sales etc.

Implement features for insert, delete and lookups with key. Another feature is to query the number of employees within a certain range specified by the user.

The queries could be very simple: lookup a single employee data given the key OR the query could be a bit complex like find the number of employees within a range of the following:
- annual bonus range
- annual compensation range (salary + bonus)
- annual sales range
- age range

REQUIREMENTS:

Use Red-Black tree data structures and algorithms to organize that data.

The implementation can be in the model with several clients and a single server where the server maintains an in-mem database.
The clients accept the user input and send the request to the server and the server processes those and returns the result/success/failure to the client. The client will show the result to the user.

Implementation should allow for the scaling up to a very large number (few hundred thousand at least) of entries without any performance loss.

The implementation should allow for large #s of simultaneous queries for information (via multiple threading in the server) to reduce the latency.

ZMQ is used as communication between the clients and the server.



* To build go to project root folder and run make all.
* To build testcases go to project root folder and run make test.
  Run only one client application instance to perform testcases.

* To run client specify server IP address and port command line arguments:
./client 192.168.0.12 55555

* To run server specify bind port command line argument:
./server 55555

Due to lack of time I didn't implement some features in this task.
Below are such restrictions and suggestions regarding this.

1. If client says that it is connected to server, it doesn't really mean
that connection has been established. Because ZMQ message queue is used as sockets implementation.
Handshake/heartbeat messages should be implemented.

2. In Client application all user input is implemented using scanf function.
Of course, this is very unsafe as it doesn't control buffer size, format of data etc.
Some C string input functions like fgets should be used instead.

3. Only two database indexes are implemented: by employee id and by compensation range.

4. Thread safety for shared database is implemented using standard Linux read-write Mutex
for the following reasons:

a) Not lock-free. It would be faster to use lock-free CAS based red black tree
implementation, but we have to support few database indexes and perform all database operations
in one transaction (e.g. insert into first and second index trees).

b) Not an spinlock and futex. Transaction length is big enough. At least it should be
RB tree traverse (to search the place to insert or node to delete) n times (where n - number of tree indexes)
and possible RB tree rebalancing n times as well. Probably it's faster to switch task context than
waiting in the spinlock loop and waste CPU performance (on SMP). On single processor spinlock would kill performance at all.

c) Because of specific business data nature (employees) I assume lookup database operations are usually more frequent than amend operations.
So, number of database readers is much more than database writers. That's why RW lock is used.

Unfortunately, no exact benchmark calculations were performed to proof this.

5. Terminate signals are not handled in client and server application. So currently it doesn't free resources properly.
No exit application feature is implemented in server application.

6. All server database memory management (data and tree nodes allocation/release) is primitive.
Of course, it will lead to memory fragmentation and in real life some custom memory allocator should be used instead.

7. All floating point numbers comparation are primitive (using standard c operators <, >, =).