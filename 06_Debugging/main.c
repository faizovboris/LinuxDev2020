#include <stdlib.h>
#include <stdio.h>

#define N 2

int main(void) {
    int *data = malloc(N * sizeof(*data));
    for (int i = 0; i < N; i++) {
        data[i] = i;
    }
    printf("%d\n", data[0]);

    free(data);
    free(data);
    return 0;
}