# ZMQClientServer===================================================================================================
* To build go to project root folder and run make all.
* To build testcases go to project root folder and run make test.
  Run only one client application instance to perform testcases.

* To run client specify server IP address and port command line arguments:
./client 192.168.0.12 55555

* To run server specify bind port command line argument:
./server 55555
===================================================================================================
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
