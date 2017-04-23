/**
 * src/client.h - Client-side of the proxy
 * Licensed under the terms of the MIT License
 */

#ifndef __CLIENT_H__
#define __CLIENT_H__

struct SProxyClient {
    int sock;
    unsigned short port;
};

void initClient(struct SProxyClient *client);
void openClient(struct SProxyClient *client);
void connectClient(struct SProxyClient *client, const char *addr);
void closeClient(struct SProxyClient *client);

void sendServerData(struct SProxyClient *client, const char *message, char **reply);

#endif // __CLIENT_H__
