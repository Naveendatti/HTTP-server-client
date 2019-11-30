#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include<string>
#include<iostream>
using namespace std;
int main(){
int client=socket(AF_INET,SOCK_STREAM,0);
if(client<0){
cout<<"failed to create client"<<endl;
exit(EXIT_FAILURE);
}
const int port=8080;
struct sockaddr_in address;
memset((char *)&address,0,sizeof(address));
address.sin_family=AF_INET;
address.sin_port=htons(port);
if(inet_pton(AF_INET,"3.133.134.221",&address.sin_addr)<0){
cout<<"invalid address"<<endl;
return 0;
}

if(connect(client,(struct sockaddr *)&address,sizeof(address))<0){
cout<<"connection faile"<<endl;
return 0;
}
int n=0;
do{
string message;
cin>>message;
n=message.size();
send(client,message.c_str(),message.size(),0);
cout<<"message sent"<<endl;
char response [4096];
recv(client,response,4096,0);
cout<<"message received: ";
cout<<response<<endl;
}while(n>0);

return 0;
}
