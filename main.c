#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    srand(time(NULL));
    printf("Parent: Forking...\n");

    int pid1 = 0;
    int pid2 = 0;

    pid1 = fork();
    if (pid1) {
        rand();  // yeah...
        pid2 = fork();
    }
    
    if (pid1 && pid2) {
        if (pid1 < 0 || pid2 < 0) {
            printf("Parent: Error: %s\n", strerror(errno));
            return -1;
        }

        int status1;
        waitpid(pid1, &status1, 0);

        int status2;
        waitpid(pid2, &status2, 0);

        printf("Parent: Done forking!\n");
        printf("Parent: Child pid %d slept for %d seconds!\n", pid1, WEXITSTATUS(status1));
        printf("Parent: Child pid %d slept for %d seconds!\n", pid2, WEXITSTATUS(status2));
    }
    else {
        printf("Child: My pid is %d!\n", getpid());
        
        int sleep_time = (rand() % 4) + 2;
        sleep(sleep_time);

        printf("Child: Done sleeping! (pid: %d)\n", getpid());
        
        return sleep_time;
    }
    
    return 0;
}
