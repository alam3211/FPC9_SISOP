#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

char buf[512];

int main(int argc, char *argv[]){
  int fd0, fd1, i;

  if(argc <= 2){
    printf(1, "Membutuhkan 2 argumen. cp *argumen1 *argumen2");
    exit();
  }

  if((fd0 = open(argv[1], O_RDONLY)) < 0){
      printf(1, "cp: file tidak bisa dibuka %s\n", argv[1]);
      exit();
    }
  if((fd1 = open(argv[2], O_RDWR)) < 0){
      printf(1, "cp: file tidak bisa dicuka %s\n", argv[2]);
      exit();
    }
    while ((i= read(fd0,buf,sizeof(buf))) > 0){
	write(fd1,buf,i);
    }
    close(fd0);
    close(fd1);
  exit();
}
