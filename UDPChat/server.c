#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include<netinet/in.h>
#define PORT 5000
  
int main()
{   
    char buffer[100];
    char message[100];
    int listenfd,len,n;
    struct sockaddr_in servaddr, cliaddr;
    bzero(&servaddr, sizeof(servaddr));
  
    listenfd = socket(AF_INET, SOCK_DGRAM, 0);    
        
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
    servaddr.sin_family = AF_INET; 
   
    bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
       
    while(1){
    len = sizeof(cliaddr);
    n = recvfrom(listenfd, buffer, sizeof(buffer), MSG_WAITALL, (struct sockaddr*)&cliaddr, &len); 
    buffer[n] = '\0';
    printf("Client: %s", buffer);
          
    fgets(message, 100, stdin);
    sendto(listenfd, message, sizeof(message), MSG_CONFIRM,
          (struct sockaddr*)&cliaddr, sizeof(cliaddr));
}
}
