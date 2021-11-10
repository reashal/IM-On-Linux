#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<unistd.h>
#include<iostream>
#include<sys/types.h>
#include<arpa/inet.h>    
#include<sys/socket.h>
#include<netinet/in.h>
using namespace std;
char ip_address[20],mess[2222],msg_rec[2222];
int soc_cli,soc_rec,con_rec,fin;
struct sockaddr_in  servaddr,cliaddr;

void in_ip()
{
  printf("--please input the server ip address:\n");
  stpcpy(ip_address,"47.94.1.16");
//  scanf("%s",ip_address);
  // If you run the server program locally, illegal input other than the IP will still connect successfully
  // but if run in the server,the illegal input will not successfully connect
  // ( illegal input such as:"hhh" )
//  std::cin.ignore();
  // ignore '\n', or it will get error in connection  
  return ;
}

int con_ser()
{
  soc_cli=socket(AF_INET,SOCK_STREAM,0);
  // set socket | error-1
  // AF_INET:ipv4  SOCK_STREAM:full duplex  0:automatic choose agreement of type(2)
  if(soc_cli==-1)
  {
    printf("--failed to create socket\n");
    return 0;
  }
  servaddr.sin_family=AF_INET;
  // choose ipv4 but not ipv6
  servaddr.sin_port=htons(6666);
  // defult ip  port
  if(inet_pton(AF_INET,ip_address,&servaddr.sin_addr)==-1)
  {
    printf("--failed to inet_tion\n");
    return 0;
  }
  // transform the ip address to binary
  if(connect(soc_cli,(struct sockaddr*)&servaddr,sizeof(servaddr))==-1)
  //        (description,server socket address,length of socket address)
  {
    printf("--failed to connection\n");
    return 0;
  }
  //printf("++%s\n",ip_address); ps:to tese local/server difference
  // the client connect to the server
  printf("--connection success!\n");
  return 1;
}

int send_info()
{
  fgets(mess,2222,stdin);
  // buffer | stop when '\n' what want to send 
  if(send(soc_cli,mess,strlen(mess),0)==-1)
  // (socket description,buffer,length,0)
  {
    printf("--failed to send this  message!\n");
    return 0;
  }
  return 1;
}

int con_recv()
{
	soc_rec=socket(AF_INET,SOCK_STREAM,0);
	cliaddr.sin_family=AF_INET;
	cliaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	cliaddr.sin_port=htons(6666);
	bind(soc_rec,(struct sockaddr*)&cliaddr,sizeof(cliaddr));
	listen(soc_rec,8);
	printf("--I'm listening the server program\n");
	while(1)
	{
		if((con_rec=accept(soc_rec,(struct sockaddr*)NULL,NULL))==-1)
			continue;
		while(1)
		{
			fin=recv(con_rec,msg_rec,2222,0);
			msg_rec[fin]='\0';
			if(fin!=0) printf("--message from server: %s\n",msg_rec);
			else break;
		}
	close(con_rec);
	}
	close(soc_rec);
	return 0;
}

int main()
{
  // init
  memset(&servaddr,0,sizeof(servaddr));
  //
  memset(&cliaddr,0,sizeof(cliaddr));
  //
  // input server ip address
//  in_ip();
  // wait for result
//  printf("--please wait to see if the connection is succeed.\n");
//  if(!con_ser()) return 0;
  // connect failed
  sleep(1); 
  // connect buffer for success
//  printf("--now you can send your message: \n");
  // if(!send_info()) return 0;
/*
  while(1)
  {
    if(!send_info()) break;
    // send failed. exit
  }
*/
  con_recv();
//  close(soc_cli);
  // close socket. or the server program may have wrong
  return 0;
}
