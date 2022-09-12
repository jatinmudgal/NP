#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>  
#define PORT 5000
  
int main()
{   
    char buffer[100];
    char message[100];
    int sockfd, n, len;
    
    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);
    servaddr.sin_family = AF_INET;
  
    while(1){
    	len = sizeof(servaddr);
    	fgets(message, 100, stdin);
    	sendto(sockfd, message, sizeof(message), MSG_CONFIRM, (struct sockaddr*) &servaddr, sizeof(servaddr));
      
    	n = recvfrom(sockfd, buffer, sizeof(buffer), MSG_WAITALL, (struct sockaddr*) &servaddr, &len);
    	buffer[n] = '\0';
    	printf("Server: %s", buffer);    	
}
	close(sockfd);
}
