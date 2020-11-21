#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#define MAXLINE 1024

int main(int argc, char **argv)
{
	int rfd, wfd;
	char buf[MAXLINE];
	char str[MAXLINE]="";
	pid_t pid;

	mkfifo("/tmp/myfifo_r", S_IRUSR|S_IWUSR);
	mkfifo("/tmp/myfifo_w", S_IRUSR|S_IWUSR);


	if( (rfd = open("/tmp/myfifo_r", O_RDWR)) == -1)
	{
		perror("rfd error");
		return 0;
	}
	if ( (wfd = open("/tmp/myfifo_w", O_RDWR)) == -1)
	{
		perror("wfd error");
		return 0;
	}

	for(int i=0; i<3; i++)
	{
	pid = fork();
	if(pid==0){
		memset(buf, 0x00, MAXLINE);
		if(read(rfd,buf,MAXLINE) < 0)
		{
			perror("Read Error");
			return 0;
		}
		printf("Read : %s", buf);
		strcat(str,buf);
		printf("str: %s", str);
		write(wfd, str, MAXLINE);
		lseek(wfd, 0, SEEK_SET);
	} else{
		//close(wfd);
		//close(rfd);
	}
	}

//	write(wfd, str, MAXLINE);
//	lseek(wfd, 0, SEEK_SET);
	close(wfd);
	close(rfd);

	return 0;
}

