#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <signal.h>

#define SHM_NAME "/my_shm"
#define SHM_SIZE 4096

int shm_fd;
void *shm_ptr;

void cleanup() {
    munmap(shm_ptr, SHM_SIZE);
}

void sigint_handler(int sig) {
    cleanup();
    exit(0);
}

int main() {
    srand(time(NULL));
    signal(SIGINT, sigint_handler);

    shm_fd = shm_open(SHM_NAME, O_RDWR, 0600);
    shm_ptr = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    int *data = (int *) shm_ptr;

    while (1) {
        if (*data == 0) {
            int number = (rand() % 100) + 1;
            *data = number;
            sleep(1);
            printf("Sent number %d\n", number);
        }
    }

    cleanup();
    return 0;
}
