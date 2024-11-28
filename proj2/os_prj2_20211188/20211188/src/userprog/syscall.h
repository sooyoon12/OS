#ifndef USERPROG_SYSCALL_H
#define USERPROG_SYSCALL_H

#include "lib/user/syscall.h"
#include <stdbool.h>

typedef int pid_t;
extern struct lock lock_file;

void syscall_init(void);

void HALT(void);
void EXIT(int status);
int EXEC(const char *cmd_lime);
int WAIT(int pid);
bool CREATE(const char *file, unsigned size);
bool REMOVE(const char *file);
int FILESIZE(int fd);
int OPEN(const char *file);
void SEEK(int fd, unsigned position);
int READ(int fd, void *buffer, unsigned size);
unsigned TELL(int fd);
void CLOSE(int fd);
int WRITE(int fd, const void *buffer, unsigned size);
int FIBONACCI(int n);
int MAX_OF_FOUR_INT(int a, int b, int c, int d);

#endif /* userprog/syscall.h */
