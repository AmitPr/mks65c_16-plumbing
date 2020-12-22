#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>

void sighandler(int signo){
    if (signo==SIGINT){
        int fd = open(".raw", O_WRONLY);
        write(fd,"\0",1);
        close(fd);
        remove(".raw");
        remove(".processed");
        exit(0);
    }
}

int main()
{
    signal(SIGINT,sighandler);
    //Create the pipes
    mkfifo(".raw", 0664);
    mkfifo(".processed", 0664);
    int fd;
    char user_input[100], output_str[100];
    while (1)
    {
        printf("Enter a line: ");
        fgets(user_input, 100, stdin);
        fd = open(".raw", O_WRONLY);
        write(fd, user_input, 100);
        close(fd);

        fd = open(".processed", O_RDONLY);
        read(fd, output_str, 100);
        printf("Swapped Case: %s\n", output_str);
        close(fd);
    }
    return 0;
}