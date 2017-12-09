#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"

void ls(char *path)
{
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if(fstat(fd = open(path, O_RDONLY), &st) < 0){   //membuka dan mengambil stat file
    printf(1, "%s tidak ada\n", path);        
    close(fd);
    return;
  }

  switch(st.type){ 
  case T_FILE:                                     //jika st.type adalah file
    printf(1, "%s\t\t %d\n", path, st.size);
    break;

  case T_DIR:                                     //jika st.type adalah dir
    strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';

    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      if(de.inum==0||strcmp(de.name, ".")==0||strcmp(de.name,"..")==0)continue;
      //printf(1,"buf %s size %d\n", buf, sizeof(buf));
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;                     //memberi terminate 0

      if(stat(buf, &st) < 0){
        printf(1, "%s tidak ada %s\n", buf);
        continue;
      }

      printf(1, "%s\n", buf);
    }
    break;
  }
  close(fd);
}

int
main(int argc, char *argv[])
{
  int i;
  if(argc < 2){                                   //ls aja
    ls(".");
    exit();
  }

  
  for(i=1; i<argc; i++)                           //ls dengan path/nama
    ls(argv[i]);
  exit();
}