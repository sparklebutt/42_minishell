#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int main() {
    char *argv[] = { "/bin/ls", "-l", NULL };
    char *envp[] = { NULL };

    printf("Before execve()\n");

    if (execve("/bin/ls", argv, envp) == -1) {
        perror("execve failed");
        // Handle the error, for example by exiting the program
        exit(EXIT_FAILURE);
    }

    // This line will never be reached if execve() is successful
    printf("After execve()\n");

    return 0;
}