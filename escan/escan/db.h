#ifndef ESCAN_DB_H_
#define ESCAN_DB_H_

int db_init();
int db_scan(char *md5);
int db_update(char *md5s[], size_t length);
int db_free();

#endif