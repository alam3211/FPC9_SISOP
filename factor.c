#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"

void factor(int n)
{
    if (n==1||n==0){
	printf(1,"\n");
        return;
    }
    int num=2;
    while (n%num != 0)
        num++;
    printf(1,"%d ",num);
    factor(n/num);

}

int main (int argc,char *argv[])
{
  int n;
  for(n=1;n<argc;n++){
  	printf(1,"%d: ",atoi(argv[n]));
  	factor(atoi(argv[n]));
  }
  exit();
}

