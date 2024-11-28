#ifndef USERPROG_SYSCALL_INTERFACE_H
#define USERPROG_SYSCALL_INTERFACE_H

#include "lib/user/syscall.h"

typedef int pid_t;

void syscall_initialize(void);

int file_open(const char *file);
bool file_remove(const char *file);
int file_read(int fd, void *buffer, unsigned size);
int file_get_size(int fd);
int file_write(int fd, const void *buffer, unsigned size);
void file_seek(int fd, unsigned position);
unsigned file_tell(int fd);
void file_close(int fd);

bool file_create(const char *file, unsigned initial_size);

void system_halt(void);
void process_terminate(int status); // 이름 변경: process_exit -> process_terminate
pid_t process_exec(const char *cmd_line);
int process_wait(pid_t pid);

int fibonacci(int n);
int max_of_four_int(int a, int b, int c, int d);

#endif /* USERPROG_SYSCALL_INTERFACE_H */
