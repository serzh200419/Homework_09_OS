#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> 

void* print_numbers(void* arg) {
    int thread_num = *((int*)arg);
    for (int i = 1; i <= 5; i++) {
        printf("Thread %d (ID: %lu) prints: %d\n", thread_num, pthread_self(), i);
        usleep(100000);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[3];
    int thread_nums[3];

    for (int i = 0; i < 3; i++) {
        thread_nums[i] = i + 1;
        if (pthread_create(&threads[i], NULL, print_numbers, &thread_nums[i]) != 0) {
            perror("Error creating thread");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads finished printing.\n");
    return 0;
}

