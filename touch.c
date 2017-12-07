#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char *argv[]){

  int fd,i;
  if(argc <= 1){
    printf(1, "Usage : touch filename.\n");
    exit();
  }
  
  for(i=1;i<argc;i++){
  if((fd = open(argv[i], O_RDONLY)) < 0) {
     printf(1,"File created.\n");  
     fd = open(argv[i],O_CREATE);
     close(fd);
  }
  else {
    printf(1,"File exist.\n");
  }
  }
  exit();
}
