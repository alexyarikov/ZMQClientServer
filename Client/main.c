#include "main.h"
#include "client.h"
#include "Testcases/testcases.h"

int main(int argc, char *argv[])
{
   if (argc != 3)
   {
      printf("Client\r\nUsage: client <server_address> <server_port>\r\n");
      printf("Example: client 127.0.0.1 5555\r\n");
      return 0;
   }

   if (argv[1] == '\0' || atoi(argv[1]) == 0 || argv[2] == '\0')
   {
      printf("Server\r\nInvalid server address/port\r\n");
      return 255;
   }

#ifndef TEST
   return client__run(argv[1], atoi(argv[2])) ? 0 : 255;
#else
   testcases__run(argv[1], atoi(argv[2]));
   return 0;
#endif
}
