/**
 * src/http.h - Utilities to manage HTTP requests and responses
 * Licensed under the terms of the MIT License
 */

#ifndef __HTTP_H__
#define __HTTP_H__

enum EHttpRequestMethod {
    NONE,
    GET,
    HEAD,
    POST,
    PUT,
    DELETE,
    CONNECT,
    OPTIONS,
    TRACE
};

struct SHttpRequestInfo {
    enum EHttpRequestMethod method;
    char *uri;
    char *host;
};

void getHttpRequestInfo(struct SHttpRequestInfo *info, const char *request);
void destroyHttpRequestInfo(struct SHttpRequestInfo *info);

struct __SHttpMethodPair {
    char *method_s;
    enum EHttpRequestMethod method_e;
};

enum EHttpRequestMethod __identityHttpMethod(const char *message);

#endif // __HTTP_H__
