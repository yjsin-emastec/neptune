#ifndef __SOCKET_H__
#define __SOCKET_H__

//----------------------------------------------------------------------------
// Types and defines:
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// External function prototypes:
//----------------------------------------------------------------------------
int socket_print(int sock, const char *formatstr, ...);
int socket_recv(int sock, void *data, int len);
int socket_send(int sock, void *data, int len);
int socket_readline(int sock, char *line, int length);
int tcp_connect(const char *ip, int port);
int data_socket_and_listen(const char *ip);
int data_socket_and_listen_withport(const char *ip, int port);
int start_tcp_server(const char *ip, int port, void *func, void *func_arg);

#endif
