/**
 * src/app.h - Application source file
 * Licensed under the terms of the MIT License
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#
#include "app.h"
#
#include "http.h"
#include "server.h"
#include "client.h"
#include "blocked.h"

static struct SProxyServer server;
static struct SProxyClient client;
struct SBlockedResources blockedRes;

static void __appInit(unsigned short server_port) {
    initBlockedResources(&blockedRes, "assets/blocked.txt");
    loadBlockedResources(&blockedRes);

    // Initializing the server...
    initServer(&server, server_port);

    openServer(&server);

    // Initializing the client...
    initClient(&client);
}

static void __appClose() {
    // Closing the sever...
    closeServer(&server);

    // Closing the client...
    closeClient(&client);

    destroyBlockedResources(&blockedRes);
}

static void __appProc() {
    struct SHttpRequestInfo request_info;
    char *browser_proxy_request, *proxy_server_request, *server_response;

    acceptConnection(&server);

    // Catching a browser request and translation HTTP/1.1 --> HTTP/1.1
    readClientData(&server, &browser_proxy_request);

    if (strlen(browser_proxy_request) == 0) {
        free(browser_proxy_request);
        return;
    }

    getHttpRequestInfo(&request_info, browser_proxy_request);

    // Displaying request details...
    printf("=== Request received ===\n");

    printf("Host: %s\nURI: %s\n\n", request_info.host, request_info.uri);

    createHttpRequest(&request_info, &proxy_server_request);

    // Sending a request to the targeted remote server...
    openClient(&client);
    connectClient(&client, request_info.host);

    sendServerData(&client, proxy_server_request, &server_response);

    printf("Blocked resources lookup... ");
    if (isBlocked(&blockedRes, request_info.uri) == 1) {
        printf("This resource has been black listed... Aborting request.\n\n");
        closeClient(&client);
        return;
    }

    // Sending the response back to the browser.
    sendClientData(&server, server_response);

    closeClient(&client);

    // Freeing allocated memory.
    destroyHttpRequestInfo(&request_info);

    free(browser_proxy_request);
    free(proxy_server_request);
    free(server_response);
}

void app(unsigned short server_port) {
    // Initialization...
    __appInit(server_port);

    // Let's do the work...
    while (1) {
        __appProc();
    }

    // That's a wrap...
    __appClose();
}
