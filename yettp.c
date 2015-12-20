#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

#define PORT 8000

int main(int argc, char *argv[])
{
	int listen_fd, conn_fd;
	sockaddr_in server_addr = {};

	printf("listen_fd: %d\n", listen_fd = socket(PF_INET, SOCK_STREAM, 0));

	server_addr.sin_family = PF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(PORT);

	printf("bind status: %d\n", bind(listen_fd, (const sockaddr*)&server_addr, sizeof(server_addr)));
	printf("listen status: %d\n", listen(listen_fd, 10));

	puts("\ninit completed, waiting for request...\n");

	for (;;)
	{
		printf("conn_fd: %d\n", conn_fd = accept(listen_fd, (sockaddr*)NULL, NULL));

		/* do something */

		//test
		send(conn_fd, (const void*)"HTTP/1.1 200 OK\r\nServer: yettp/0.0.1\r\n\r\n", sizeof(char) * 40, 0);

		printf("connection close status: %d\n\n", close(conn_fd));
	}

	return 0;
}
