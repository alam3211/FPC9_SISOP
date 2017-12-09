#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"

int main(int argc,char *argv[]){


	char buf[512],fd;
	int n;

	fd= open(argv[1],O_RDWR);
	while ((n = read(0, buf, sizeof(buf))) > 0) {
			write(fd, buf,n);
	}
	close(fd);
}