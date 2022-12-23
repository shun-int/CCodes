#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
    char buf[64]={0};
    int fd = open("/dev/devtest",O_RDWR);
    if(fd<0){
        printf("open err\n");
        return fd;
    }else{
        printf("open success. %d\n",fd);
    }
    close(fd);
    return 0;
}