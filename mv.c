#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"

void move(char *src, char *dest)
{
 
  if (link(src, dest)!=0) {
    printf(1,"Unable to move, file cant link or not found\n");
    exit();
  }
  //else printf(1,"Success.\n");

  if (unlink(src)!=0) {
    printf(1,"Unable to delete the old one\n");
    exit();
  }
  //else printf(1,"Delete the old one.\n");
}

void aster(char *dest){
	int fd= open(".",O_RDONLY),cek;
	int lndest= strlen(dest);
	struct stat st;
	struct dirent de;
	char buf[512];

	 while(read(fd, &de, sizeof(de)) == sizeof(de)) {
        cek= stat(de.name, &st); 
        if(cek == 0 && st.type == T_FILE) {
            strcpy(buf, dest);
            strcpy(&buf[lndest],"/");
			strcpy(&buf[lndest+1], de.name);
			//printf(1,"%s\n",buf);
			move(de.name,buf);
		}
	}
}

int main(int argc, char *argv[]){

	int cek,i,lndest,fd;
	char buf[512];
	struct stat st;
	
	if((fd = open(argv[argc-1],O_RDONLY))<0){
	}
	cek=stat(argv[argc-1],&st);
	lndest=strlen(argv[argc-1]);
	
	if (argc<2){
		printf(1,"Usage: mv file dest\n");
	}

	if(strcmp(argv[1],"*")==0){
			//printf(1,"masuk\n");
			aster(argv[2]);
			exit();
	}
	

	
	if(cek==0 && st.type != T_DIR){
		printf(1,"Dest %s is not a directory.\n",argv[argc-1]);
		exit();
	}

	for(i=1; i<argc-1; i++){

		strcpy(buf,argv[argc-1]);
		strcpy(&buf[lndest],"/");
		strcpy(&buf[lndest+1],argv[i]);
		move(argv[i],buf);       
		//printf(1,"ngeeng\n"); 
	}
	exit();
}