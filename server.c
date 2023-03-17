#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

#define SHM_NAME "/my_shm"
#define SHM_SIZE 4096

int shm_fd;
void *shm_ptr;

void cleanup() {
    munmap(shm_ptr, SHM_SIZE);
    shm_unlink(SHM_NAME);
}

void sigint_handler(int sig) {
    cleanup();
    exit(0);
}

int main() {
    signal(SIGINT, sigint_handler);

    shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0600);
    ftruncate(shm_fd, SHM_SIZE);
    shm_ptr = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    int *data = (int *) shm_ptr;

    while (1) {
        if (*data != 0) {
            printf("Received: %d\n", *data);
            *data = 0;
        }
        sleep(1);
    }

    cleanup();
    return 0;
}
