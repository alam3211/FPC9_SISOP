#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"


void rmrecursive(char *path){

  char buf[512], *p;
  int fd;


  struct dirent de;
  struct stat st;

  if((fd = open(path, 0)) < 0){
    printf(2, "ls: cannot open %s\n", path);
    return;
  }

  if(fstat(fd, &st) < 0){
    printf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }

  switch(st.type){
  case T_FILE:
    //printf(1, "%s %d %d %d\n", fmtname(path), st.type, st.ino, st.size);
    //break;

  case T_DIR:
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf(1, "ls: path too long\n");
      break;
    }
    strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';

    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      if(de.inum == 0)
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if(stat(buf, &st) < 0){
        printf(1, "ls: cannot stat %s\n", buf);
        continue;
      }
      //ini diotak atik
      //menampilkan isi direktori dan menghapus isinya
      printf(1, "ini folder=%s buf=%s\n", path, buf);
      if(unlink(buf) < 0)
        printf(1, "rm: %s failed to delete\n", buf);  
    }
    //ini juga
    //menghapus direktori kosong
    if(unlink(path) < 0)
      printf(1, "rm: %s failed to delete\n", path);

    break;
  }
  close(fd);

}


int main(int argc, char *argv[])
{
  int i;

  printf(2,"argc : %d argv: %s %s \n", argc, argv[0], argv[1]);

  if(strcmp(argv[1],"-r")==0){
    for(i = 2; i < argc; i++){
      printf(2,"rm -r dijalankan\n");
      rmrecursive(argv[i]);
    }
    exit();
  } 

  if(argc < 2){
    printf(2, "Usage: rm files...!\n");
    exit();
  }

  for(i = 1; i < argc; i++){
    if(unlink(argv[i]) < 0){
      printf(2, "rm: %s failed to delete\n", argv[i]);
      break;
    }
  }
  exit();
}