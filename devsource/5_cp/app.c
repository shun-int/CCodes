#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
    char buf_get[32]={0};
    char buf_set[32]="copy to kernel test.";
    int fd = open("/dev/devtest",O_RDWR);
    if(fd<0){
        printf("open err: %d\n",fd);
        return fd;
    }else{
        printf("open success. %d\n",fd);
    }
    read(fd,buf_get,sizeof(buf_get));
    printf("copy from kernel: %s\n",buf_get);

    if(write(fd,buf_set,sizeof(buf_set))<0){
        printf("write err\n");
    }

    close(fd);
    return 0;
}