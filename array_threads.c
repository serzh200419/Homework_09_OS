#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 8

int arr[SIZE] = {3, 7, 2, 8, 10, 5, 4, 6};

typedef struct {
    int start;
    int end;
} ThreadData;

void* sum_array_part(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int sum = 0;

    for (int i = data->start; i < data->end; i++) {
        sum += arr[i];
    }

    printf("Partial sum from index %d to %d = %d, thread id: %lu)\n",
           data->start, data->end - 1, sum, pthread_self());
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[2];
    ThreadData tdata[2];
    int mid = SIZE / 2;

    tdata[0].start = 0;
    tdata[0].end = mid;

    tdata[1].start = mid;
    tdata[1].end = SIZE;

    for (int i = 0; i < 2; i++) {
        if (pthread_create(&threads[i], NULL, sum_array_part, &tdata[i]) != 0) {
            perror("Error creating thread");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Both threads have completed their sums.\n");
    return 0;
}

