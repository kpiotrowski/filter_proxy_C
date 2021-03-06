#ifndef FILTER_PROXY_C_REQUEST_H
#define FILTER_PROXY_C_REQUEST_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <sys/epoll.h>

struct request{
    struct headerCookie* headers;
    struct headerCookie* cookies;
    int headersCount;
    int cookiesCount;

    char *requestData;
    int dataLen;
};

struct headerCookie{
    char *name;
    char *value;
    char *cookieAttr;
};

struct requestStruct{
    int clientSoc;
    int serverSoc;
    int clientHandled;
    int serverHandled;

    struct request* clientRequest;
    struct request* serverResponse;
    time_t time;
};

extern int maxTimeMsc;


/**
 * Create new request structure and allocate memory
 * @return pointer to request structure
 */
struct requestStruct * newRequestStruct();

/**
 * Create new request and allocate memory
 * @return pointer to request
 */
struct request * newRequest();

/**
 *
 * @param req request/response structure
 * @param type type od structure (request :  or response : 1 , different cookie header)
 * @return request as string (to send it to server or client)
 */
char *requestToString(struct request req, int* size, int type);

/**
 * Free memory for given request struct pointer
 * @param req pointer to request struct
 */
void freeRequest(struct request* req);

/**
 * Close sockets, free memory and delete request struct from requests array
 * @param requestIndex request index in requests array
 * @param requests pointer to pointer to request
 */
void removeRequestStruct(struct requestStruct *requestIndex, struct requestStruct ***requests, int *connections, int epoolFd,
                         int *threadCount);

int readData(struct request *req, int socket, int *threadAlive);

#endif //FILTER_PROXY_C_REQUEST_H
