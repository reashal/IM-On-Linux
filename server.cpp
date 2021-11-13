#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<netdb.h>
#include<signal.h>
#include<unistd.h>
#include<iostream>
#include<pthread.h>
#include<sys/types.h>
#include<arpa/inet.h>    
#include<sys/socket.h>
#include<netinet/in.h>
using namespace std;

int soc_ser,lst,acpt,fin,k,soc_lst,tot=0;
struct sockaddr_in seraddr,cliaddr;
char msg_rec[2222],mess[2222];
socklen_t l_size;
int clients[10],flag=-1;

int init()
{
	memset(clients,-0x3f,sizeof(clients));
	soc_ser=socket(AF_INET, SOCK_STREAM, 0);
	if(soc_ser==-1)
	{
		printf("--failed creating socket description\n");
		return 0;
	}
	l_size=sizeof(struct sockaddr_in);
	memset(&seraddr,0,sizeof(seraddr));
	seraddr.sin_family=AF_INET;
	seraddr.sin_addr.s_addr=htonl(INADDR_ANY);
	seraddr.sin_port=htons(6666);
//	soc_lst=socket(AF_INET,SOCK_STREAM,0);
	if(bind(soc_ser,(struct sockaddr*)&seraddr,sizeof(seraddr))==-1)
	{
		printf("--failed bind\n");
		return 0;
	}
	lst=listen(soc_ser,10);
	if(lst==-1)
	{
		printf("--failed listen\n");
		return 0;
	}
	printf("--Listen success,now begin accept:\n");
	return 1;
}

int send_info() {
	stpcpy(mess,"I have rcv your messages  from server!\n");
    if (send(soc_ser, mess, strlen(mess), 0) == -1)
    {
        printf("--failed to send this  message!\n");
        return 0;
    }
    return 1;
}

void *ser_rcv(void *q)
{
	fin=0;
	k=*(int *)q;
	bzero(msg_rec,sizeof(msg_rec));
	while(read(k,msg_rec,sizeof(msg_rec))&&strlen(msg_rec))
	// 如果读入失败,字符数组清零,连'\0'都没有,踩坑好久
	{
		// The string is zeroed out each time a message is received
		if(msg_rec[0]=='!'&&msg_rec[1]=='q')
		{
			tot--;
			break;
		}
		else
		{
			if(msg_rec)
			printf("--messages from clients: ");
			fputs(msg_rec,stdout);
			printf("\n");
			for(int i=0;i<10;i++)
			{
				if(clients[i]!=-0x3f)
				{
					stpcpy(mess,msg_rec);
					send(clients[i], mess, strlen(mess), 0);
				}
			}
			bzero(msg_rec,sizeof(msg_rec));
		}
	}
	for(int i=0;i<10;i++)
	{
		if(clients[i]==k)
		{
			clients[i]=-0x3f;
			break;
		}
	}
    return 0;
}
int main()
{
	if(!init())
	  return 1;
	while(1)
	{
		acpt=accept(soc_ser,(struct sockaddr *)&cliaddr,&l_size);
		if(acpt!=-1)
		{
			tot++;
			if(tot>10)
			{
				tot--;
				break;
			}
			while(1)
			{
				++flag;
				if(flag>9) flag-=10;
				if(clients[flag]!=-0x3f)
				{
					clients[flag]=acpt;
					break;
				}
			}
			pthread_t k;
			pthread_create(&k,NULL,ser_rcv,&acpt);
		}
	}
	close(soc_ser);
	return 0;
}