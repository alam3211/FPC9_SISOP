#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
 
 int main(int argc, char *argv[]){
 	printf(1,"cd.c dijalankan");
 	if(argc<2){
 		printf(1,"need 2 arguments\n");
 		exit();
 	}
 	if(chdir(argv[1])<0){
 		printf(1,"Failed to change directory\n");
 	}
 	exit();
 }