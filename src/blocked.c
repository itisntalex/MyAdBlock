/**
 * src/blocked.c - Utilities to manage the list of blocked ressources
 * Licensed under the terms of the MIT License
 */

#include <unistd.h>
#include <fcntl.h>
#
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#
#include "blocked.h"

struct SResource* __createNode(const char *resource) {
    struct SResource *newNode;

    // Ensuring the memory allocation, actually happened...
    if ((newNode = malloc(sizeof(struct SResource))) == NULL) {
        return NULL;
    }

    // Now copying the resources...
    if ((newNode->resource = malloc(strlen(resource) + 1)) == NULL) {
        free(newNode);

        return NULL;
    }

    strcpy(newNode->resource, resource);
    newNode->next = NULL;

    // Everything is OK :D
    return newNode;
}

int __addResource(struct SResource *node, const char *resource) {
    // Creating a brand new node...
    struct SResource *newNode;

    if ((newNode = __createNode(resource)) == NULL) {
        return -1;
    }

    // Applying the new node to the given one.
    node->next = newNode;

    return 0;
}

struct SResource* __deleteResource(struct SResource *node) {
    struct SResource *nextNode = node->next;

    free(node->resource);
    free(node);

    return nextNode;
}

void __deleteRecursiveResource(struct SResource *node) {
    struct SResource *currentNode = node;

    while (currentNode != NULL) {
        currentNode = __deleteResource(currentNode);
    }
}

int __compare(struct SResource *node, const char *comp) {
    return (strstr(comp, node->resource) != NULL) ? 1 : 0;
}

int initBlockedResources(struct SBlockedResources *res, const char *filename) {
    if ((res->filename = malloc(strlen(filename) + 1)) == NULL) {
        return -1;
    }

    strcpy(res->filename, filename);
    res->node = NULL;
    res->stream = NULL;

    return 0;
}

int loadBlockedResources(struct SBlockedResources *res) {
    struct SResource *currentNode;
    char *line = NULL;
    size_t len;
    ssize_t nread;

    if ((res->stream = fopen(res->filename, "r")) == NULL) {
        perror("Unable to open the resources' file");
        return -1;
    }

    getline(&line, &len, res->stream);

    res->node = __createNode(line);
    currentNode = res->node;

    while ((nread = getline(&line, &len, res->stream)) > 0) {
        if (nread == -1) {
            perror("An error occured while reading the resources' file");

            return -1;
        }

        if (line[0] == '!') {
            continue;
        }

        // Removing trailing new line...
        strtok(line, "\n");

        __addResource(currentNode, line);
        currentNode = currentNode->next;
    }

    free(line);

    return 0;
}

void destroyBlockedResources(struct SBlockedResources *res) {
    fclose(res->stream);

    __deleteRecursiveResource(res->node);
}

int isBlocked(struct SBlockedResources *res, const char *comp) {
    struct SResource *currentNode = res->node;

    while (currentNode != NULL) {
        if (__compare(currentNode, comp) == 1) {
            return 1;
        }

        currentNode = currentNode->next;
    }

    return 0;
}
