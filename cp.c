#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"

void cp(char *src, char *dest){
  int fd0, fd1, i;
  char buf[512];
  char temp[512];
  char temp2[512];
  struct stat sb;
  if(dest[strlen(dest)-1]=='/')
	dest[strlen(dest)-1]=0;

  fd1=open(dest,O_CREATE|O_WRONLY);

  if((fd0 = open(src, O_RDONLY)) < 0){
      printf(1, "cp: cannot open %s\n", src);
      exit();
    }

  if(stat(dest,&sb) == 0 && sb.type == T_DIR){
	printf(1, "cp: %s is a directory.\n",dest);
	strcpy(temp2,dest); strcpy(temp,src);
	int lnsrc = strlen(src);
	int lndest = strlen(dest);
	strcpy(&temp2[lndest],"/");
	printf(1,"%s\n",temp2);
	int n = lnsrc-1;
	while(n--)
		if(temp[n] == '/')
		break;
	n++;
	strcpy(&temp2[lndest+1],&temp[n]);
	printf(1,"%s\n",temp2);
	fd1=open(temp2,O_CREATE|O_WRONLY);
  }

  while ((i= read(fd0,buf,sizeof(buf))) > 0){
	write(fd1,buf,i);
    }
    close(fd0);
    close(fd1);
}

void aster(char* path){
	int cek,fd;
	char buf[512],*p;
	struct stat sb;
	struct dirent de;

	cek= stat(path, &sb);
	if(cek == 0 && sb.type != T_DIR){
		printf(1,"cp : dest is not a directory.\n");
		exit();
	}
	fd=open(".",O_RDONLY);
	strcpy(buf,".");
    	p = buf+strlen(buf);
    	*p++ = '/';

    	while(read(fd, &de, sizeof(de)) == sizeof(de)){
      	
	memmove(p, de.name, DIRSIZ);
      	p[DIRSIZ] = 0;
 	if(stat(buf, &sb) < 0){
        	printf(1, "cp: cannot stat %s\n", buf);
        	continue;
        }
        cp(buf,path);
	}
}

int main(int argc,char *argv[]){
  if(argc < 3){
    printf(1, "Usage : cp [opt] src dest\n");
    exit();
  }

  if(strcmp(argv[1], "*") == 0){
	aster(argv[2]);
	exit();
  } 

  cp(argv[1],argv[2]);
  exit();
}
