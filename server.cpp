#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<cstring>
#include<arpa/inet.h>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
int main(){


/*->creating socket. parameters are (type of address(here i am using IPV4),type of service(VCS),protocol) 
   ->creating socket is like  requesting a telephone  line. */


int server_id,new_socket,addrlength;
 server_id=socket(AF_INET,SOCK_STREAM,0);

if(server_id<0){
cout<<"unable to create a socket, i am sorry,bye: "<<endl;
exit(EXIT_FAILURE);
}
/*->now we assign ip address and port number for our socket.
 parameters are:
-> our socket,address structure,length of address structure 
-> this is like aassigning phone number to our telephone line. */

struct sockaddr_in address;
addrlength=sizeof(address);
const int port=8080;
memset((char *)&address,0,sizeof(address));

address.sin_family=AF_INET;
address.sin_addr.s_addr=htonl(INADDR_ANY); //INADDR_ANY means os  decides. symbolic representation of 0.0.0.0
address.sin_port=htons(port);

if(bind(server_id,(struct sockaddr *)&address,sizeof(address))<0){
cout<<"cannot bind address :"<<endl;
exit(EXIT_FAILURE);
}
/*
here our socket listen for connections and accept connections.
a new socket is created by accepting which transfers data not listening socket
*/
if(listen(server_id,100)<0){
cout<<"socket is failed to listen: "<<endl;
exit(EXIT_FAILURE);
}
while(true){
cout<<"waiting for connection"<<endl;
new_socket=accept(server_id,(struct sockaddr*)&address,(socklen_t *)&addrlength);
if(new_socket<0){
cout<<"failed to accept connection"<<endl;
 exit(EXIT_FAILURE);
}
/*
sending and receiving message between server and client using read and write functions. we can use send and recieve function also
*/
vector<char> buffer (4096);
string message;
do{
long val=recv(new_socket,&buffer[0],4096,0);
 if(val==0){
cout<<"client dont want to send anything"<<endl;
return 0;
}

message.append(buffer.cbegin(),buffer.cend());
reverse(message.begin(),message.end());

send(new_socket,&message[0],message.size(),0);
}while(message.size()!=0);

close(new_socket);
}
return 0;

}

