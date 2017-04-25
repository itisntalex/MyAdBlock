/**
 * src/server.h - Server-side of the proxy
 * Licensed under the terms of the MIT License
 */

#ifndef __SERVER_H__
#define __SERVER_H__

struct SProxyServer {
    int sock;
    int client_sock;
    unsigned short port;
};

void initServer(struct SProxyServer *server, unsigned short port);
void openServer(struct SProxyServer *server);
void closeServer(struct SProxyServer *server);

void acceptConnection(struct SProxyServer *server);
void disocnnectClient(struct SProxyServer *server);
void readClientData(struct SProxyServer *server, char **message);
void sendClientData(struct SProxyServer *server, const char *message);

#endif // __SERVER_H__
