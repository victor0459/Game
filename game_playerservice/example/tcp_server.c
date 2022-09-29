#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<ctype.h>
struct msg{
	int msgid;
	int msglen;
	float speed;
	float px;
	float py;
	float pz;
	float rx;
	float ry;
	float rz;
};


int main(int argc,const char*argv[])
{
	//创建用于监听的套接字
	int lfd=socket(AF_INET,SOCK_STREAM,0);
	if(lfd==-1)
	{
		perror("socket error");
		exit(1);
	}
	//绑定
	struct sockaddr_in serv_addr;
	//init 初始化
	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;//本地族协议 ipv4
	serv_addr.sin_port=htons(8888);//本地端口 需要转换为大端
	//serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);//0是本机的任意IP
	inet_aton("192.168.101.17",&serv_addr.sin_addr);
	
	//设置端口复用
	int flag=1;
	setsockopt(lfd,SOL_SOCKET,SO_REUSEADDR,&flag,sizeof(flag));

	int ret=bind(lfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	if(ret==-1)
	{
		perror("bind error");
		exit(1);
	}

	//设置监听
	ret=listen(lfd,64);
	if(ret==-1)
	{
		perror("listen error");
		exit(1);
	}

	//等待并接受连接请求
	struct sockaddr_in clien_addr;
	socklen_t clien_len=sizeof(clien_addr);
	int cfd=accept(lfd,(struct sockaddr*)&clien_addr,&clien_len);
	if(cfd==-1)
	{
		perror("accept error");
		exit(1);
	}
	
	char ipbuf[64];
	printf("client ip:%s,port:%d\n",
	inet_ntop(AF_INET,&clien_addr.sin_addr.s_addr,ipbuf,sizeof(ipbuf)),
	ntohs(clien_addr.sin_port));
	struct msg m;
	//通信
	while(1)
	{
		//先接收数据
		char buf[1024]={0};
		int len=read(cfd,buf,sizeof(buf));
		if(len==-1)
		{
			perror("read error");
			exit(1);
		}
		else if(len>0)
		{
			memcpy(&m,buf,36);
			//顺利读出了数据
			//printf("read buf=%s\n",buf);
			printf("有效数据长度%ld\n",strlen(buf));
			printf("read msgid=%d msglen=%d speed=%f px=%f\n",m.msgid,m.msglen,m.speed,m.px);
			//将小写转换成大写
			for(int i=0;i<len;++i)
			{
				buf[i]=toupper(buf[i]);
			}
			//printf("--toupper:%s\n",buf);
			//将数据发送给客户
			write(cfd,buf,strlen(buf)+1);
		}
		else if(len==0)
		{
			printf("client disconnect...\n");
			break;
		}
	}
	close(lfd);
	close(cfd);
	return 0;
}

