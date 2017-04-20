/**
 * src/blocked.h - Utilities to manage the list of blocked resources
 * Licensed under the terms of the MIT License
 */

#ifndef __BLOCKED_H__
#define __BLOCKED_H__

struct SResource {
    char *resource;
    struct SResource *next;
};

struct SResource* __createNode(const char *resource);
int __addResource(struct SResource *node, const char *resource);
struct SResource* __deleteResource(struct SResource *node);
void __deleteRecursiveResource(struct SResource *node);
int __compare(struct SResource *node, const char *comp);

struct SBlockedResources {
    FILE *stream;
    char *filename;
    struct SResource *node;
};

int initBlockedResources(struct SBlockedResources *res, const char *filename);
int loadBlockedResources(struct SBlockedResources *res);
void destroyBlockedResources(struct SBlockedResources *res);
int isBlocked(struct SBlockedResources *res, const char *comp);

#endif // __BLOCKED_H__
