#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"


void rmforcerecursive(char *path){

  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;


  if(fstat(fd = open(path, O_RDONLY), &st) < 0){   //membuka dan mengambil stat file
    //printf(2, "%s tidak ada\n", path);        
    close(fd);
    return;
  }

  switch(st.type){
  case T_FILE:                                      //jika st.type adalah file
    if(unlink(path) < 0)
      //printf(1, "rm: %s failed to delete\n", buf); 
    //else printf(1,"file %s dihapus\n", buf); 
    break;

  case T_DIR:                                       //jika st.type adalah direktori

    strcpy(buf, path);
    p = buf+strlen(buf);
    *p = '/';
    p++;

    while(read(fd, &de, sizeof(de)) == sizeof(de)){

      //printf(1, "dirent de.name: %s\nde size %d\n", de.name, sizeof(de));
      if(de.inum==0||strcmp(de.name, ".")==0||strcmp(de.name,"..")==0)continue;

      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;

      if(stat(buf, &st)<0){
        //printf(1,"%s tidak ada\n", buf);
        continue;
      } 

      //ini diotak atik
      //menampilkan isi direktori dan menghapus isinya
      //printf(1, "ini folder=%s buf=%s\n", path, buf);
      if(st.type==T_DIR) rmforcerecursive(buf);
      else unlink(buf);
      /*{
        if(unlink(buf) < 0)
          printf(1, "rm: %s failed to delete\n", buf); 
        else printf(1,"file %s dihapus\n", buf);
      }*/   
    }
    //ini juga
    //menghapus direktori kosong
    if(unlink(path) < 0) return;
      //printf(1, "rm: %s failed to delete\n", path);
    //else printf(1,"direktori %s dihapus\n", path);

    break;
  }
  close(fd);

}


int main(int argc, char *argv[])
{
  int i;

//  printf(2,"argc : %d argv: %s %s \n", argc, argv[0], argv[1]);

  if(strcmp(argv[1],"-rf")==0){
    for(i = 2; i < argc; i++){
      //printf(2,"rm -rf dijalankan\n");
      rmforcerecursive(argv[i]);
    }
    exit();
  } 

  if(argc < 2){
    printf(2, "Usage: rm files...!\n");
    exit();
  }

  for(i = 1; i < argc; i++){
    if(unlink(argv[i]) < 0){
      //printf(2, "rm: %s failed to delete\n", argv[i]);
      break;
    }
  }
  exit();
}