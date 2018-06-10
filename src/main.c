#include <stdio.h> 
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>


int main() {

    pid_t pid;
    int ret = 0;

    pid = fork();
    if (pid < 0) {
        fprintf(stderr, "Fork Failed"); 
        exit(-1);
	}
	else if (pid == 0) {
        ret = execlp("./src/add","add",NULL); 
	}
    else{
        wait(0);
    }
    return ret;
}
