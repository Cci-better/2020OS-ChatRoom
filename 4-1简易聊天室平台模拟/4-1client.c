/* 由于线程pthread库不是Linux系统默认的库，连接时需要使用库libpthread.a,所以程序中有使用pthread_create，在编译中要加-lpthread参数

gcc client.c -o client -lpthread 

*/

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<netdb.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/wait.h>
#include<unistd.h>
#include<pthread.h>
#define TRUE 1
#define PORT 5000
int quit=0; //quit表示是否用户确定退出
void *get_server(void *);
int main(void)
{
int connfd,snd,slenth;
struct sockaddr_in server;
struct hostent *hp;
char honame[20],msg2[1024],msg1[1024],cln[102],qstr[]={"Quit"}; //qstr的值表示用户在输入"Quit"时和服务器断开链接
pthread_t tid;
printf("请输入服务器IP地址\n");
scanf("%s*",honame);
printf("正在建立套接口...\n");
if((connfd= socket(AF_INET, SOCK_STREAM, 0))<0) //建立套接口
printf("建立套接口失败\n");
if ((hp= gethostbyname(honame))== NULL) //获取服务器IP地址
{
printf("获取服务器IP地址失败\n");
exit(1);
}
else printf("套接口建立成功，链接服务器中...\n");
memcpy(&server.sin_addr,hp->h_addr,hp->h_length); //将服务器IP地址放入结构体server中
server.sin_family = AF_INET;
server.sin_port=htons(PORT);
if(connect(connfd,(struct sockaddr*)&server,sizeof(server))<0) //链接套接口 
{
printf("链接服务器失败\n");
exit(1);
}
printf("链接服务器成功\n"); //链接成功显示成功的登录信息
printf("欢迎来到聊天室\n");
//聊天室
printf("请输入你的用户昵称\n");
scanf("%s",msg1);
slenth=strlen(msg1);
msg1[slenth]=':';
msg1[slenth+1]='\0';
strcpy(cln,msg1); //保存用户昵称在名为cln的数组中
pthread_create(&tid,NULL,&get_server,(void *)(intptr_t)connfd);//为客户端创建一个线程用于监听，调用get_server函数
printf("\n开始聊天吧 (\"Quit\"断开链接)\n");
while(TRUE)
{
printf("\n");
scanf("%s",msg2);
if(strcmp(msg2,qstr)==0)
{
close(connfd);
quit=1; //若用户输入"Quit"字符则关闭发送套接口,并将quit置为1
}
else
{
strcat(msg1,msg2);//将消息前加上用户昵称
snd=send(connfd,msg1,strlen(msg1)+1,0);//否则发送消息给服务器
strcpy(msg1,cln);
if(snd<0)
printf("\n发送错误\n");
}
}
}
void *get_server(void* sockfd) //get_server函数，用于接受服务器转发的消息
{
char buf[1024];
int rev;
if(((intptr_t)sockfd)<0)
printf("\n接受服务器消息失败\n");
else
{
printf("\n\007\n");
for(;;)
{
if(!quit)//只要quit不为1，则一直接受服务器消息
{
if ((rev = recv((intptr_t)sockfd,buf,1024,0))>0)
printf("\n\007%s\n", buf);
if (rev==0)
{
printf("\n服务器终止链接\n");
quit=1;
continue;
}
printf("\n");
}
else
{
close((intptr_t)sockfd);//关闭此套接口
break;
}
}
return(NULL);
}
}