/**
 * src/server.c - Server-side of the proxy
 * Licensed under the terms of the MIT License
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#
#include "server.h"

static char client_buffer[2 << 20];

void initServer(struct SProxyServer *server, unsigned short port) {
    server->sock = -1;
    server->client_sock = -1;
    server->port = port;
}

void openServer(struct SProxyServer *server) {
    if (server->sock != -1) {
        fprintf(stderr, "Error: server already initialized\n");
        exit(1);
    }

    server->sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in sin = {0};

    if (server->sock == -1) {
        perror("An error occured while initializing the server");
        exit(errno);
    }

    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_port = htons(server->port);
    sin.sin_family = AF_INET;

    if (bind(server->sock, (struct sockaddr *) &sin, sizeof(sin)) == -1) {
        perror("An error occured while initializing the server");
        exit(errno);
    }

    if (listen(server->sock, 1) == -1) {
        perror("An error occured while initializing the server");
        exit(errno);
    }
}

void closeServer(struct SProxyServer *server) {
    close(server->sock);
}

void acceptConnection(struct SProxyServer *server) {
    struct sockaddr_in client;
    int len = sizeof(struct sockaddr_in);

    if (server->sock == -1) {
        fprintf(stderr, "Error: unable to accept a connection with invalid server information\n");
    }

    if ((server->client_sock = accept(server->sock, (struct sockaddr *) &client, (socklen_t *) &len)) == -1) {
        perror("Failure on connection acceptation");
        exit(errno);
    }
}

void readClientData(struct SProxyServer *server, char **message) {
    short read_size, total_size = 0;
    int len;

    memset(client_buffer, 0x0, 2 << 20);

    while ((read_size = recv(server->client_sock, client_buffer + total_size, 2 << 20, 0)) > 0
           && strstr(client_buffer, "\r\n\r\n") == NULL) {
        total_size += read_size;
    }

    len = strlen(client_buffer);

    if (read_size == -1) {
        perror("An error occured while reading the client data");
        exit(errno);
    }

    *message = malloc(len + 1);

    memcpy(*message, client_buffer, len + 1);
}
