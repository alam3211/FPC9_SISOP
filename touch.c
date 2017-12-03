#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char *argv[]){

  int fd;
  if(argc <= 1){
    printf(1, "Argument kurang.gunakan touch *namafile*");
    exit();
  }
  
  if((fd = open(argv[1], O_RDONLY)) < 0) {
     printf(1,"File tidak ada, file akan dibuat.\n");  
     fd = open(argv[1],O_CREATE);
     close(fd);
  }
  else {
    printf(1,"File sudah ada\n");
  }

  exit();
}
