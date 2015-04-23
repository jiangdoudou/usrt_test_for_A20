/*
* file uart_test.c
* for rk3288 uart test   
* author by jiangdou
* time 2015-04-07
*/

//jiangdou   #################
/*test by */
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>



/*�򿪴���*/
int open_port(int fd,int comport)
{
	char *dev[]={"/dev/ttyS0","/dev/ttyS1","/dev/ttyS2"};
	long vdisable;
	if (comport==1)//���� 1
	{
		fd = open( "/dev/ttyS6", O_RDWR|O_NOCTTY|O_NDELAY);
	if (-1 == fd){
		perror("Can't Open Serial Port...\n");
		return(-1);
		}
	}
	else if(comport==2)//���� 2
	{
		fd = open( "/dev/ttyS1", O_RDWR|O_NOCTTY|O_NDELAY);
		if (-1 == fd){
			perror("Can't Open Serial Port");
			return(-1);
		}
	}
	else if (comport==3)//���� 3
	{
		fd = open( "/dev/ttyS2", O_RDWR|O_NOCTTY|O_NDELAY);
		if (-1 == fd){
		perror("Can't Open Serial Port");
		return(-1);
		}
	}

/*�ָ�����Ϊ����״̬*/

	if(fcntl(fd, F_SETFL, 0)<0)
		printf("fcntl failed!\n");
	else
		//printf("fcntl=%d\n",fcntl(fd, F_SETFL,0));

	/*�����Ƿ�Ϊ�ն��豸*/

	if(isatty(STDIN_FILENO)==0)
		printf("standard input is not a terminal device\n");
	else
		//printf("isatty success!\n");
	//printf("fd-open=%d\n",fd);
	return fd;
}
///////////////////////
//set_opt
//////////////////////
int set_opt(int fd,int nSpeed, int nBits, char nEvent, int nStop)
{
	struct termios newtio,oldtio;
	/*����������д��ڲ�������,������������ںŵȳ���,������صĳ�����Ϣ*/
	if ( tcgetattr( fd,&oldtio) != 0) {
		perror("SetupSerial 1");
		return -1;
	}
	bzero( &newtio, sizeof( newtio ) );
	/*����һ,�����ַ���С*/
	newtio.c_cflag |= CLOCAL | CREAD;
	newtio.c_cflag &= ~CSIZE;
	/*����ֹͣλ*/
	switch( nBits )
	{
	case 7:
		newtio.c_cflag |= CS7;
		break;
	case 8:
		newtio.c_cflag |= CS8;
		break;
	}
/*������żУ��λ*/
	switch( nEvent )
	{
	case 'O': //����
		newtio.c_cflag |= PARENB;
		newtio.c_cflag |= PARODD;
		newtio.c_iflag |= (INPCK | ISTRIP);
		break;
	case 'E': //ż��
		newtio.c_iflag |= (INPCK | ISTRIP);
		newtio.c_cflag |= PARENB;
		newtio.c_cflag &= ~PARODD;
		break;
	case 'N': //����żУ��λ
		newtio.c_cflag &= ~PARENB;
	break;
	}
	/*���ò�����*/
	switch( nSpeed )
	{
	case 2400:
		cfsetispeed(&newtio, B2400);
		cfsetospeed(&newtio, B2400);
		break;
	case 4800:
		cfsetispeed(&newtio, B4800);
		cfsetospeed(&newtio, B4800);
		break;
	case 9600:
		cfsetispeed(&newtio, B9600);
		cfsetospeed(&newtio, B9600);
		break;
	case 115200:
		cfsetispeed(&newtio, B115200);
		cfsetospeed(&newtio, B115200);
		break;
	case 460800:
		cfsetispeed(&newtio, B460800);
		cfsetospeed(&newtio, B460800);
		break;
	default:
		cfsetispeed(&newtio, B9600);
		cfsetospeed(&newtio, B9600);
		break;
	}
	/*����ֹͣλ*/
	if( nStop == 1 )
		newtio.c_cflag &= ~CSTOPB;
	else if ( nStop == 2 )
		newtio.c_cflag |= CSTOPB;
	/*���õȴ�ʱ�����С�����ַ�*/
	newtio.c_cc[VTIME] = 0;
	newtio.c_cc[VMIN] = 0;
	/*����δ�����ַ�*/
	tcflush(fd,TCIFLUSH);
	/*����������*/
	if((tcsetattr(fd,TCSANOW,&newtio))!=0)
	{
		perror("com set error");
	return -1;
	}
	//printf("set done!\n");
return 0;
}


int main(void)
{
	int fd;
	int nwrite,i;
	char buff0[]="\n\r";
	char buff1[]="uart_test by jiang_dou QQ:344283973\n\r";
	char buff[80];
	if((fd=open_port(fd,1))<0)
	{//�򿪴���
		perror("open_port error");
		return;
	}
	if((i=set_opt(fd,115200,8,'N',1))<0){//���ô���
		perror("set_opt error");
	return;
	}
	//printf("fd=%d\n",fd);
	printf("uart-test, baud is 115200,  is RX\n\r");
	printf("uart test to starting. press 'enter 'key to continue.......\n");
	getchar();
	
	
	nwrite=write(fd,buff0,strlen(buff0));//д����
	for(i=0; i<2000; i++){
		sprintf(buff, "receive data_%d  %s", i, buff1);
		printf("nwrite=%d,send data_%d %s\n",nwrite, i, buff1);
		nwrite=write(fd, buff, strlen(buff));//д����
		//buff = buff1;
		sleep(1);
	}
	close(fd);
	return;
}
