#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc,char *argv[])
{
    int fd;
    char read_buf[32];
    char write_buf[32]="copy to kernel ok..";
    fd = open("/dev/led",O_RDWR);
    if(fd<0){
        printf("open err: %d\n",fd);
        return -1;
    }
    close(fd);
    return 0;
}