#include "main.h"
#include "server.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: server <bind_port>\r\n");
        printf("Example: server 5555\r\n");
        return 0;
    }

    int port = atoi(argv[1]);
    if (port < 1)
    {
        printf("Invalid port\r\n");
        return 255;
    }

    return run(port) ? 0 : 255;
}
