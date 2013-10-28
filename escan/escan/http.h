#ifndef ESCAN_HTTP_H_
#define ESCAN_HTTP_H_

int http_init(char *hostname, char *addr);
int http_post(char *content, size_t len);
int http_get(char *url, char *info, int len);

#endif