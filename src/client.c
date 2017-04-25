/**
 * src/client.c - Client-side of the proxy
 * Licensed under the terms of the MIT License
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <unistd.h>
#
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#
#include "client.h"

static char server_buffer[2 << 20];

void initClient(struct SProxyClient *client) {
    client->sock = -1;
    client->port = 80;
}

void openClient(struct SProxyClient *client) {
    if (client->sock != -1) {
        fprintf(stderr, "Client already initialized\n");
        exit(1);
    }

    client->sock = socket(AF_INET, SOCK_STREAM, 0);

    if (client->sock == -1) {
        perror("An error occured while initializing the client");
        exit(errno);
    }
}

void connectClient(struct SProxyClient *client, const char *addr) {
    struct sockaddr_in server;
    struct hostent *host_info;

    if ((host_info = gethostbyname(addr)) == NULL) {
        fprintf(stderr, "Unknown host %s\n", addr);
        exit(1);
    }

    server.sin_addr = *(struct in_addr *) host_info->h_addr;
    server.sin_port = htons(client->port);
    server.sin_family = AF_INET;

    if (connect(client->sock, (struct sockaddr *) &server, sizeof(server)) < 0) {
        perror("Connection to remote server failed");
        exit(errno);
    }
}

void closeClient(struct SProxyClient *client) {
    close(client->sock);

    client->sock = -1;
}

void sendServerData(struct SProxyClient *client, const char *message, char **reply) {
    int len, read_size, total_size = 0;

    if (send(client->sock, message, strlen(message), 0) < 0) {
        perror("An error occured while sending data to the remote server");
        exit(errno);
    }

    memset(server_buffer, 0x0, sizeof(server_buffer));

    while ((read_size = recv(client->sock, server_buffer + total_size, 2 << 20, 0)) > 0) {
        total_size += read_size;
    }

    if (read_size == -1) {
        perror("An error occured while reading the server response");
        exit(errno);
    }

    len  = strlen(server_buffer);

    if (read_size == -1) {
        perror("An error occured while reading the server response");
        exit(errno);
    }

    *reply = malloc(len + 1);

    memcpy(*reply, server_buffer, len + 1);
}
