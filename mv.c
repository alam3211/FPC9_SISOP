#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"

void move(char *src, char *dest)
{
 
  if (link(src, dest)!=0) {
    printf(1,"Unable to move\n");
    exit();
  }

  if (unlink(src)!=0) {
    printf(1,"Unable to delete the old one\n");
    exit();
  }
}

int main(int argc, char *argv[]){

	int cek,i,lndest,fd;
	char buf[512];
	struct stat st;
	
	if((fd = open(argv[argc-1],O_RDONLY))<0)
		
	
	if (argc<2){
		printf(1,"Usage: mv file dest\n");
	}

	if (argc==2){
		move(argv[1],argv[2]);
		exit();
	}

	cek=stat(argv[argc-1],&st);
	lndest=strlen(argv[argc-1]);
	
	if(cek==0 && st.type != T_DIR){
		printf(1,"Dest %s is not a directory.\n",argv[argc-1]);
		exit();
	}

	for(i=1; i<argc-1; i++){

		strcpy(buf,argv[argc-1]);
		strcpy(&buf[lndest],"/");
		strcpy(&buf[lndest+1],argv[i]);
		move(argv[i],buf);        
	}
	exit();
}