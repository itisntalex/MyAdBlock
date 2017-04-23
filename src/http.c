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

static struct __SHttpStatusCodePair statusCodePairs[] = {
    {100, Continue},
    {101, SwitchingProtocols},

    {200, Ok},
    {201, Created},
    {202, Accepted},
    {203, NonAuthoritativeInformation},
    {204, NoContent},
    {205, ResetContent},
    {206, PartialContent},

    {300, MultipleChoices},
    {301, MovedPermanently},
    {302, Found},
    {303, SeeOther},
    {304, NotModified},
    {305, UseProxy},
    {306, Unused},
    {307, TemporaryRedirect},

    {400, BadRequest},
    {400, Unauthorized},
    {400, PaymentRequired},
    {400, Forbidden},
    {400, NotFound},
    {400, MethodNotAllowed},
    {400, NotAcceptable},
    {400, ProxyAuthenticationRequired},
    {400, RequestTimeout},
    {400, Conflict},
    {400, Gone},
    {400, LengthRequired},
    {400, PreconditionFailed},
    {400, RequestEntityTooLarge},
    {400, RequestUrlTooLong},
    {400, UnsupportedMediaType},
    {400, RequestRangeNotSatisfiable},
    {400, ExpectationFailed},

    {500, InternalServerError},
    {500, NotImplemented},
    {500, BadGateway},
    {500, ServiceUnavailable},
    {500, GatewayTimeout},
    {500, HTTPVersionNotSupported},
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

enum EHttpStatusCode __identityHttpStatusCode(const char *message) {
    long code = strtol(message, NULL, 10);

    for (unsigned int i = 0; i < sizeof(statusCodePairs); i++) {
        if (code == statusCodePairs[i].code_i) {
            return statusCodePairs[i].code_e;
        }
    }

    return None;
}
