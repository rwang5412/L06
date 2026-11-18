#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: parentcreates <iterations>\n");
        exit(1);
    }

    int iterations = strtol(argv[1], NULL, 10);
    int children = 0;

    for (int i = 0; i < iterations; i++) {
        int n = fork();
        if (n < 0) {
            perror("fork");
            exit(1);
        }
        printf("ppid = %d, pid = %d, i = %d\n", getppid(), getpid(), i);
        fflush(stdout);
        if (n == 0) {
            return 0;
        }
        children++;
    }

    while (children > 0) {
        if (wait(NULL) < 0) {
            perror("wait");
            exit(1);
        }
        children--;
    }

    return 0;
}