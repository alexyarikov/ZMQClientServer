#include "server.h"
#include "Database/database.h"
#include "Messages/messages.h"

// worker threads
#define THREADS_COUNT 10
pthread_t threads[THREADS_COUNT];

// worker threads work flag
volatile int threads_work_flag = 0;

// functions
bool initialize(void *context, void *clients_socket, void *workers_socket, const int port);
bool initialize_clients(void *context, void *socket, const int port);
bool initialize_workers(void *context, void *socket);
void shutdown();
bool process_request(zmq_msg_t *msg_req, zmq_msg_t *msg_res);
void *worker_routine(void *context);

// start server
bool run(const int port)
{
   // zmq context
   void *context = zmq_ctx_new();
   assert(context);

   // zmq socket to talk to clients
   void *clients = zmq_socket(context, ZMQ_ROUTER);
   assert(clients);

   //  socket to talk to workers
   void *workers = zmq_socket(context, ZMQ_DEALER);
   assert(workers);

   // initialize server
   bool res = initialize(context, clients, workers, port);

   if (res)
   {
      //  connect work threads to client threads via a queue proxy
      printf("server started, waiting for incoming request...\r\n");
      printf("press <Ctrl-C> for exit\r\n");
      zmq_proxy(clients, workers, NULL);
   }

   // free zmq
   zmq_close(clients);
   zmq_close(workers);
   zmq_ctx_destroy(context);

   return res;
}

// initialize server
bool initialize(void *context, void *clients_socket, void *workers_socket, const int port)
{
   // initialize clients
   bool res = initialize_clients(context, clients_socket, port);
   // initialize workers
   res = res && initialize_workers(context, workers_socket);
   // create database
   if (res)
      database__create();

   return res;
}

// initialize clients
bool initialize_clients(void *context, void *socket, const int port)
{
   assert(context);
   assert(socket);

   // make bind address
   char bind_addr[16] = { 0 };
   sprintf(bind_addr, "tcp://*:%d", port);

   // bind clients socket
   if (zmq_bind(socket, bind_addr) != -1)
   {
      printf("clients socket has been bound on %s\r\n", bind_addr);
      return true;
   }
   else
   {
      printf("failed to bind clients socket on %s: %s\r\n", bind_addr, zmq_strerror(errno));
      return false;
   }
}

// initialize workers
bool initialize_workers(void *context, void *socket)
{
   assert(context);
   assert(socket);

   // bind workers socket
   if (zmq_bind(socket, "inproc://workers") == -1)
   {
      printf("failed to bind workers socket: %s\r\n", zmq_strerror(errno));
      return (false);
   }

   // set threads work flag
   __sync_fetch_and_add(&threads_work_flag, 1);

   //  launch pool of worker threads
   int i, threads_count = sizeof(threads) / sizeof(threads[0]);
   for (i = 0; i < threads_count; i++)
   {
      if (pthread_create(&threads[i], NULL, worker_routine, context) != 0)
      {
         printf("failed to create worker thread\r\n");
         return false;
      }
   }

   return true;
}

// shutdown server
// (TODO: to be called in server application terminate signals handler)
void shutdown()
{
   // stop threads
   __sync_fetch_and_sub(&threads_work_flag, 1);

   int i, threads_count = sizeof(threads) / sizeof(threads[0]);
   for (i = 0; i < threads_count; i++)
      pthread_join(threads[i], NULL);

   // destroy database
   database__destroy();
}

// process request
bool process_request(zmq_msg_t *msg_req, zmq_msg_t *msg_res)
{
   assert(msg_req);
   assert(msg_res);

   // get request data
   unsigned char *data_req = zmq_msg_data(msg_req);
   assert(data_req);

   // check request message type
   switch (data_req[0])
   {
      case MSG_INSERT_REQUEST:
      {
         printf("[%lu] insert request received\r\n", pthread_self());
         insert_request__process(msg_req, msg_res);
         break;
      }
      case MSG_DELETE_REQUEST:
      {
         printf("[%lu] delete request received\r\n", pthread_self());
         delete_request__process(msg_req, msg_res);
         break;
      }
      case MSG_QUERY_BY_ID_REQUEST:
      {
         printf("[%lu] query by id request received\r\n", pthread_self());
         query_by_id_request__process(msg_req, msg_res);
         break;
      }
      case MSG_QUERY_BY_COMPENSATION_RANGE_REQUEST:
      {
         printf("[%lu] query by compensation range request received\r\n", pthread_self());
         query_by_compensation_range_request__process(msg_req, msg_res);
         break;
      }
      default:
         printf("[%lu] unknown message received\r\n", pthread_self());
         return false;
   }

   return true;
}

// worker routine
void *worker_routine(void *context)
{
   assert(context);

   //  socket to talk to dispatcher
   void *socket = zmq_socket(context, ZMQ_REP);
   assert(socket);

   // connect to worker
   if (zmq_connect(socket, "inproc://workers") != 0)
   {
      printf("[%lu] failed to connect worker socket: %s\r\n", pthread_self(), zmq_strerror(errno));
      return NULL;
   }

   // handle messages
   while (__sync_fetch_and_add(&threads_work_flag, 0) > 0)
   {
      // initialize zmq request message
      zmq_msg_t msg_req, msg_res;
      assert(zmq_msg_init(&msg_req) == 0);

      // receive zmq request message
      int received = zmq_msg_recv(&msg_req, socket, 0);
      if (received > 0)
      {
         // process request message
         if (process_request(&msg_req, &msg_res))
         {
            // get response message size
            int msg_size = zmq_msg_size(&msg_res);
            // send zmq response message
            if (zmq_msg_send(&msg_res, socket, 0) != msg_size)
               printf("[%lu] failed to send response message: %s\r\n", pthread_self(), zmq_strerror(errno));
         }
      }

      // close request message
      assert(zmq_msg_close(&msg_req) == 0);
   }

   // free socket
   zmq_close(socket);

   return NULL;
}
