#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 5

int numbers[SIZE] = {1, 2, 3, 4, 5};

void* calculate_square(void* arg) {
    int num = *((int*)arg);
    int square = num * num;
    printf("Square of %d is %d, thread id: %lu)\n", num, square, pthread_self());
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[SIZE];

    for (int i = 0; i < SIZE; i++) {
        if (pthread_create(&threads[i], NULL, calculate_square, &numbers[i]) != 0) {
            perror("Error creating thread");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < SIZE; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads finished calculating squares.\n");
    return 0;
}

