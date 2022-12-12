#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define IP4LEN 16

typedef struct ip4sock_s
{

	char ip[IP4LEN];
	int port;
	int fd;
	int type;
} ip4sock_t;

/* Open a TCP socket */
static int tcp_sock_init(ip4sock_t *s)
{
	if (!strlen(s->ip) || !s->port) {
		printf("Invalid IP/Port.\n");
		return 1;
	}

	int type = -1;
	type = ((s->type == AF_INET) || (s->type == AF_INET6));
	if (!type) {
		printf("Invalid IP type\n");
		return 1;
	}

	int fd = -1;
	fd = socket(s->type, SOCK_STREAM, 0);
	if (fd < 0) {
		perror("tcp_sock_init_socket");
		return 1;
	}

	/* Set IP/Port reuse options */
	int optval = 1;
	socklen_t slen = sizeof(struct sockaddr_in);
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &optval, slen) < 0) {
		perror("tcp_sock_init_setsockopt");
		return 1;
	}
	s->fd = fd;
	return 0;
}

int main(void)
{
	ip4sock_t tcpsock = {0};
	snprintf(tcpsock.ip, sizeof(tcpsock.ip), "127.0.0.1");	
	tcpsock.port = 2083;
	tcpsock.type = AF_INET;
	if (tcp_sock_init(&tcpsock)) {
		printf("Failed to initialize tcp socket for ip:port - %s:%d\n", tcpsock.ip, tcpsock.port);
		return 1;
	}
	printf("TCP socket initialized for ip:port - %s:%d\n", tcpsock.ip, tcpsock.port);
	return 0;
}
