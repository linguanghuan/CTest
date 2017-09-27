#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define NGX_ERROR  -1
#define NGX_OK  0

int make_daemon()
{
  int  fd;

  switch (fork()) {//用fork创建守护进程
  case -1://fork返回-1创建失败   	
    return NGX_ERROR;
    
  case 0://子进程返回
    break;

  default://父进程返回
    exit(0);//父进程退出
  }

  pid_t pid = getpid();
  printf("child pid:%d\n", pid);

  if (setsid() == -1) {//建立新的会话，然后子进程称为会话组长
    printf("setsid() failed\n");
    return NGX_ERROR;
  }

  umask(0);//重设文件创建掩模

  /*重定向标准输入、输出到/dev/null(传说中的黑洞)*/
  fd = open("/dev/null", O_RDWR);
  if (fd == -1) {
    printf("open(\"/dev/null\") failed\n");
    return NGX_ERROR;
  }

  if (dup2(fd, STDIN_FILENO) == -1) {//输入重定向到fd，即从/dev/null输入
    printf("dup2(STDIN) failed\n");
    return NGX_ERROR;
  }

  if (dup2(fd, STDOUT_FILENO) == -1) {//输出重定向到fd，即所有输出到/dev/null
    printf("dup2(STDOUT) failed\n");
    return NGX_ERROR;
  }


  if (fd > STDERR_FILENO) {
    if (close(fd) == -1) {
      printf("close() failed");
      return NGX_ERROR;
    }
  }

  return NGX_OK;
}

int main()
{
	printf("parent pid:%d\n", getpid());
	if(NGX_ERROR==make_daemon()){
		return 0;
	}
	
	char *ch  = (char *)malloc(100000*1000);  // 100M
	printf("%x\n", ch);
	sleep(10);

	char *ch2 = (char *)malloc(100000*1000); // 100M
	printf("%x\n", ch2);
	sleep(10);

	char *ch3 = (char *)malloc(100000*1000);  // 100M
	printf("%x\n", ch3);
	sleep(10);
	sleep(2);

	char *ch4 = (char *)malloc(100000*1000);   //100M
	printf("%x\n", ch4);
	sleep(10);

	return 0;
}
