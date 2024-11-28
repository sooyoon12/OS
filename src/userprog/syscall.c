#include "syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "threads/vaddr.h"
<<<<<<< HEAD

=======
typedef int32_t off_t;
struct lock lock_file;
>>>>>>> 3c6c1dc (Add proj2 folder and its files)
// 시스템 콜 핸들러 함수 선언
static void syscall_handler(struct intr_frame *);

// 유효한 사용자 메모리 주소인지 확인하는 함수
<<<<<<< HEAD
void check_addr(void *addr) {
    if (!is_user_vaddr(addr) || addr == NULL) {
        EXIT(-1);  // 잘못된 주소일 경우 프로세스 종료
    }
}

// 시스템 콜 초기화 함수
void syscall_init(void) {
=======
void check_addr(void *addr, unsigned size) {
    if (addr == NULL || !is_user_vaddr(addr) || !is_user_vaddr((uint8_t *)addr + size - 1)) {
        EXIT(-1);  // 잘못된 주소 범위일 경우 프로세스 종료
    }
}
struct file {
    struct ino *inode;
    off_t pos;
    bool deny_write;
};
// 시스템 콜 초기화 함수
void syscall_init(void) {
    lock_init(&lock_file);
>>>>>>> 3c6c1dc (Add proj2 folder and its files)
    intr_register_int(0x30, 3, INTR_ON, syscall_handler, "syscall");
}

// 시스템 콜 핸들러 함수
static void syscall_handler(struct intr_frame *f UNUSED) {
    // 시스템 호출 번호를 저장할 변수
    int syscall_num = 0;

    // 시스템 호출 번호를 스택 포인터에서 가져옴
    syscall_num = *(int *)(f->esp);

    // 시스템 호출 번호가 음수인 경우 오류 처리
    if (syscall_num < 0) {
        printf("Invalid system call number\n");
        thread_exit();
    }

    // 시스템 호출 번호에 따라 각 기능 처리
    switch (syscall_num) {
        case SYS_HALT:
            HALT();
            break;

        case SYS_EXIT:
<<<<<<< HEAD
            // 유효한 메모리 주소인지 확인
            check_addr(f->esp + 4);
            EXIT(*(uint32_t *)(f->esp + 4)); // 시스템 종료
            break;

        case SYS_EXEC:
            check_addr(f->esp + 4);
            f->eax = EXEC((const char *)*(uint32_t *)(f->esp + 4)); // 프로그램 실행
            break;

        case SYS_WAIT:
            check_addr(f->esp + 4);
            f->eax = WAIT(*(uint32_t *)(f->esp + 4)); // 프로세스 대기
            break;

        case SYS_READ:
            check_addr(f->esp + 4);
            check_addr(f->esp + 8);
            check_addr(f->esp + 12);
            f->eax = READ((int)*(uint32_t *)(f->esp + 4), (void *)*(uint32_t *)(f->esp + 8), (unsigned)*(uint32_t *)(f->esp + 12));
            break;

        case SYS_WRITE:
            check_addr(f->esp + 4);
            check_addr(f->esp + 8);
            check_addr(f->esp + 12);
=======
            check_addr(f->esp + 4, sizeof(uint32_t));
            EXIT(*(uint32_t *)(f->esp + 4));
            break;

        case SYS_EXEC:
            check_addr(f->esp + 4, sizeof(char *));
            f->eax = EXEC((const char *)*(uint32_t *)(f->esp + 4));
            break;

        case SYS_WAIT:
            check_addr(f->esp + 4, sizeof(uint32_t));
            f->eax = WAIT(*(uint32_t *)(f->esp + 4));
            break;

        case SYS_CREATE:
            check_addr(f->esp + 4, sizeof(char *));
            check_addr(f->esp + 8, sizeof(uint32_t));
            f->eax = CREATE((const char *)*(uint32_t *)(f->esp + 4), *(uint32_t *)(f->esp + 8));
            break;

        case SYS_REMOVE:
            check_addr(f->esp + 4, sizeof(char *));
            f->eax = REMOVE((const char *)*(uint32_t *)(f->esp + 4));
            break;

        case SYS_FILESIZE:
            check_addr(f->esp + 4, sizeof(uint32_t));
            f->eax = FILESIZE(*(uint32_t *)(f->esp + 4));
            break;

        case SYS_OPEN:
            check_addr(f->esp + 4, sizeof(char *));
            f->eax = OPEN((const char *)*(uint32_t *)(f->esp + 4));
            break;

        case SYS_SEEK:
            check_addr(f->esp + 4, sizeof(uint32_t));
            check_addr(f->esp + 8, sizeof(uint32_t));
            SEEK((int)*(uint32_t *)(f->esp + 4), (unsigned)*(uint32_t *)(f->esp + 8));
            break;

        case SYS_READ:
            check_addr((void *)*(uint32_t *)(f->esp + 8), (unsigned)*(uint32_t *)(f->esp + 12));
            f->eax = READ((int)*(uint32_t *)(f->esp + 4), (void *)*(uint32_t *)(f->esp + 8), (unsigned)*(uint32_t *)(f->esp + 12));
            break;

        case SYS_TELL:
            check_addr(f->esp + 4, sizeof(uint32_t));
            f->eax = TELL(*(uint32_t *)(f->esp + 4));
            break;

        case SYS_CLOSE:
            check_addr(f->esp + 4, sizeof(uint32_t));
            CLOSE(*(uint32_t *)(f->esp + 4));
            break;

        case SYS_WRITE:
            check_addr((const void *)*(uint32_t *)(f->esp + 8), (unsigned)*(uint32_t *)(f->esp + 12));
>>>>>>> 3c6c1dc (Add proj2 folder and its files)
            f->eax = WRITE((int)*(uint32_t *)(f->esp + 4), (const void *)*(uint32_t *)(f->esp + 8), (unsigned)*(uint32_t *)(f->esp + 12));
            break;

        case SYS_FIBONACCI:
<<<<<<< HEAD
            check_addr(f->esp + 4);
            f->eax = FIBONACCI((int)*(uint32_t *)(f->esp + 4)); // 피보나치 계산
            break;

        case SYS_MAX_OF_FOUR_INT:
            check_addr(f->esp + 4);
            check_addr(f->esp + 8);
            check_addr(f->esp + 12);
            check_addr(f->esp + 16);
            f->eax = MAX_OF_FOUR_INT((int)*(uint32_t *)(f->esp + 4), (int)*(uint32_t *)(f->esp + 8), (int)*(uint32_t *)(f->esp + 12), (int)*(uint32_t *)(f->esp + 16)); // 4개의 정수 중 최대값 계산
=======
            check_addr(f->esp + 4, sizeof(uint32_t));
            f->eax = FIBONACCI((int)*(uint32_t *)(f->esp + 4));
            break;

        case SYS_MAX_OF_FOUR_INT:
            check_addr(f->esp + 4, sizeof(uint32_t));
            check_addr(f->esp + 8, sizeof(uint32_t));
            check_addr(f->esp + 12, sizeof(uint32_t));
            check_addr(f->esp + 16, sizeof(uint32_t));
            f->eax = MAX_OF_FOUR_INT((int)*(uint32_t *)(f->esp + 4), (int)*(uint32_t *)(f->esp + 8), (int)*(uint32_t *)(f->esp + 12), (int)*(uint32_t *)(f->esp + 16));
>>>>>>> 3c6c1dc (Add proj2 folder and its files)
            break;

        default:
            printf("Unknown system call: %d\n", syscall_num);
            thread_exit();
            break;
<<<<<<< HEAD
=======

>>>>>>> 3c6c1dc (Add proj2 folder and its files)
    }
}

// 시스템 종료 함수
void HALT(void) {
    shutdown_power_off();
}

// 프로세스 종료 함수
void EXIT(int status) {
    printf("%s: exit(%d)\n", thread_current()->name, status);
    thread_current()->exit_status = status;
<<<<<<< HEAD
=======
    for (int i = 3; i < 128; i++) {
        if (thread_current()->FD[i] != NULL) {
            CLOSE(i);
        }
    }
>>>>>>> 3c6c1dc (Add proj2 folder and its files)
    thread_exit();
}

// 프로그램 실행 함수
int EXEC(const char *cmd_lime) {
    // process_execute 함수에서 파일을 제대로 처리하고 있는지 확인
<<<<<<< HEAD
    check_addr((void *)cmd_lime);
=======
    check_addr((void *)cmd_lime, strlen(cmd_lime) + 1);

>>>>>>> 3c6c1dc (Add proj2 folder and its files)
    int pid = process_execute(cmd_lime);

    // 파일을 찾지 못하거나 실행에 실패했을 경우 -1 반환
    if (pid == -1) {
        return -1;
    }

    return pid;
}

// 프로세스 대기 함수
int WAIT(int pid) {
    return process_wait(pid);
}

<<<<<<< HEAD
// 데이터 읽기 함수 (파일 디스크립터를 통한 입력 처리)
int READ(int fd, void *buffer, unsigned size) {
    if (fd == 0) { // 표준 입력
        for (unsigned i = 0; i < size; i++) {
            *((uint8_t *)buffer + i) = input_getc();
        }
        return size;
    }
    return -1;
}

// 데이터 쓰기 함수 (파일 디스크립터를 통한 출력 처리)
int WRITE(int fd, const void *buffer, unsigned size) {
    if (fd == 1) { // 표준 출력
        putbuf(buffer, size);
        return size;
    }
    return -1;
}

=======
bool CREATE(const char *file, unsigned size ){
    if (file == NULL) {
        EXIT(-1);
    }
    bool success = filesys_create(file, size);
        return success;  
}

bool REMOVE(const char *file){
    if(file==NULL){
        EXIT(-1);
    }
    bool success = filesys_remove(file);
        return success; 
}

int FILESIZE(int fd){
    if (fd <= 0 || thread_current()->FD[fd] == NULL) {
        EXIT(-1);
    }
    int length = file_length(thread_current()->FD[fd]);
    return length;
}

int OPEN(const char *file){
    if (file == NULL) {
        EXIT(-1);
    }
    check_addr((void *)file, strlen(file) + 1);
    lock_acquire(&lock_file);

    struct file *opened_file = filesys_open(file);
    int fd_index = -1;

    if (opened_file == NULL) {
        lock_release(&lock_file);
        return fd_index;
    }
    // 할당
    for (int i = 3; i < 128; i++) {
        if (thread_current()->FD[i] == NULL) {
            if (strcmp(thread_current()->name, file) == 0) {
                file_deny_write(opened_file);
            }
            thread_current()->FD[i] = opened_file;
            fd_index = i;
            break;
        }
    }

    lock_release(&lock_file);
    return fd_index;

}

void SEEK(int fd, unsigned position){
    if (fd < 0 || thread_current()->FD[fd] == NULL) {
        EXIT(-1);
    }
    file_seek(thread_current()->FD[fd], position);
}

// 데이터 읽기 함수 (파일 디스크립터를 통한 입력 처리)
int READ(int fd, void *buffer, unsigned size) {
    if (buffer == NULL || thread_current()->FD[fd] == NULL) {
        EXIT(-1);
    }

    check_addr(buffer, size);

    if (fd == 0) {
        lock_acquire(&lock_file);
        for (unsigned i = 0; i < size; i++) {
            *((uint8_t *)buffer + i) = input_getc();
        }
        lock_release(&lock_file);
        return size;
    }
    
    if (fd > 2) {
        lock_acquire(&lock_file);
        int bytes_read = file_read(thread_current()->FD[fd], buffer, size);
        lock_release(&lock_file);
        return bytes_read;
    }

    return -1;
}

unsigned TELL(int fd) {
    if (thread_current()->FD[fd] == NULL) {
        EXIT(-1);
    }
    return file_tell(thread_current()->FD[fd]);
}

void CLOSE(int fd) {
    if (thread_current()->FD[fd] == NULL) {
        EXIT(-1);
    }
    file_close(thread_current()->FD[fd]);
    thread_current()->FD[fd] = NULL;
}


// 데이터 쓰기 함수 (파일 디스크립터를 통한 출력 처리)
int WRITE(int fd, const void *buffer, unsigned size) {
    if (buffer == NULL) {
        EXIT(-1);
    }

    check_addr(buffer,size);

    if (fd == 1) {
        lock_acquire(&lock_file);
        putbuf(buffer, size);
        lock_release(&lock_file);
        return size;
    } 

    if (fd > 2) {
        if (thread_current()->FD[fd] == NULL) {
            EXIT(-1);
        }
        lock_acquire(&lock_file);
        int bytes_written = file_write(thread_current()->FD[fd], buffer, size);
        lock_release(&lock_file);
        return bytes_written;
    }

    return -1;
}


>>>>>>> 3c6c1dc (Add proj2 folder and its files)
// 피보나치 계산 함수
int FIBONACCI(int n) {
  int first = 1, second = 1;
    int next_term, count;

    if (n == 0) {
        return 0;
    } else if (n == 1 || n == 2) {
        return 1;
    } else if (n < 0) {
        printf("Error: Input must be a non-negative integer. (result=-1)\n");
        return -1;
    }
    for (count = 3; count <= n; count++) {
        next_term = first + second;
        first = second;
        second = next_term;
    }

    return second;
}

// 4개의 정수 중 최대값을 계산하는 함수
int MAX_OF_FOUR_INT(int a, int b, int c, int d) {
    // 첫 번째 두 수(a, b) 중 최대값 찾기
    int max_first_pair;
    if (a > b) {
        max_first_pair = a;
    } else {
        max_first_pair = b;
    }

    // 두 번째 두 수(c, d) 중 최대값 찾기
    int max_second_pair;
    if (c > d) {
        max_second_pair = c;
    } else {
        max_second_pair = d;
    }

    // 첫 번째 두 수의 최대값과 두 번째 두 수의 최대값 비교
    int overall_max;
    if (max_first_pair > max_second_pair) {
        overall_max = max_first_pair;
    } else {
        overall_max = max_second_pair;
    }

    return overall_max;
}