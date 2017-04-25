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

enum EHttpStatusCode {
    None,
    
    // 1xx: Information
    Continue,
    SwitchingProtocols,

    // 2xx: Successful
    Ok,
    Created,
    Accepted,
    NonAuthoritativeInformation,
    NoContent,
    ResetContent,
    PartialContent,

    // 3xx: Redirection
    MultipleChoices,
    MovedPermanently,
    Found,
    SeeOther,
    NotModified,
    UseProxy,
    Unused,
    TemporaryRedirect,

    // 4xx: Client error
    BadRequest,
    Unauthorized,
    PaymentRequired,
    Forbidden,
    NotFound,
    MethodNotAllowed,
    NotAcceptable,
    ProxyAuthenticationRequired,
    RequestTimeout,
    Conflict,
    Gone,
    LengthRequired,
    PreconditionFailed,
    RequestEntityTooLarge,
    RequestUrlTooLong,
    UnsupportedMediaType,
    RequestRangeNotSatisfiable,
    ExpectationFailed,

    // 5xx: Server error
    InternalServerError,
    NotImplemented,
    BadGateway,
    ServiceUnavailable,
    GatewayTimeout,
    HTTPVersionNotSupported
};

struct SHttpRequestInfo {
    enum EHttpRequestMethod method;
    char *uri;
    char *host;
};

struct SHttpResponseInfo {
    enum EHttpStatusCode statusCode;
    const char *reasonPhrase;
    const char *message;
};

void createHttpRequest(struct SHttpRequestInfo *info, char **request);
void getHttpRequestInfo(struct SHttpRequestInfo *info, const char *request);
void destroyHttpRequestInfo(struct SHttpRequestInfo *info);

const char* buildHttpResponse(struct SHttpResponseInfo *info);

struct __SHttpMethodPair {
    char *method_s;
    enum EHttpRequestMethod method_e;
};

struct __SHttpStatusCodePair {
    unsigned int code_i;
    enum EHttpStatusCode code_e;
};

enum EHttpRequestMethod __identityHttpMethod(const char *message);
enum EHttpStatusCode __identityHttpStatusCode(const char *message);

#endif // __HTTP_H__
