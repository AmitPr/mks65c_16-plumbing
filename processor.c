#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

void switch_case(char *str)
{
    char *C = str;
    while (*C)
    {
        if (isupper(*C))
        {
            *C = tolower(*C);
        }
        else if (islower(*C))
        {
            *C = toupper(*C);
        }
        *C++; // If only we were using it :(
    }
}

int main()
{
    while (access(".raw", F_OK) != 0)
        ;
    int fd;
    char input_str[100];
    while (1)
    {
        fd = open(".raw", O_RDONLY);
        read(fd, input_str, 100);
        close(fd);
        if (!*input_str)
            exit(0);

        switch_case(input_str);

        fd = open(".processed", O_WRONLY);
        write(fd, input_str, 100);
        close(fd);
    }
    return 0;
}