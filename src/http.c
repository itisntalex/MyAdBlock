/**
 * src/http.c - Utilities to manage HTTP requests and responses
 * Licensed under the terms of the MIT License
 */

#include <stdlib.h>
#include <string.h>
#
#include "http.h"

static struct __SHttpMethodPair methodePairs[] = {
    {"GET", GET},
    {"HEAD", HEAD},
    {"POST", POST},
    {"PUT", PUT},
    {"DELETE", DELETE},
    {"CONNECT", CONNECT},
    {"OPTIONS", OPTIONS},
    {"TRACE", TRACE}
};

void getHttpRequestInfo(struct SHttpRequestInfo *info, const char *request) {
    char *s, *s2;
    int len;

    info->method = __identityHttpMethod(request);

    // Looking for the Request-URI.
    s = strchr(request, ' ') + 1;
    s2 = strchr(s, ' ');
    len = s2 - s;

    info->uri = malloc(len + 1);
    memcpy(info->uri, s, len);
    info->uri[len] = 0x0;

    // Looking the host.
    s = strstr(request, "Host");
    s = strchr(s, ' ') + 1;
    s2 = strstr(s, "\r\n");
    len = s2 - s;

    info->host = malloc(len + 1);
    memcpy(info->host, s, len);
    info->host[len] = 0x0;
}

void destroyHttpRequestInfo(struct SHttpRequestInfo *info) {
    free(info->uri);
    free(info->host);
}

enum EHttpRequestMethod __identityHttpMethod(const char *message) {
    for (unsigned char i = 0; i < sizeof(methodePairs); i++) {
        if (strstr(message, methodePairs[i].method_s) != NULL) {
            return methodePairs[i].method_e;
        }
    }

    return NONE;
}
