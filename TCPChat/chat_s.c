#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>
#include <stdio.h>

int main(){
	char str[100];
	char buffer[100];
	int listen_fd, comm_fd;
	struct sockaddr_in servaddr;
	listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	
	bzero(&servaddr, sizeof(servaddr));
	
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(22000);
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	
	bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	
	listen(listen_fd, 10);
	
	while(1){
	
	comm_fd = accept(listen_fd, (struct sockaddr *) NULL, NULL);
	
	bzero(str,100);
	bzero(buffer, 100);
	
	while(1){
		recv(comm_fd, buffer,100,0);
		printf("\nClient: %s", buffer);
		if(buffer[0] == "X")
			close(comm_fd);
		
		fgets(str,100,stdin);
		send(comm_fd, str, strlen(str), 0);
		
	}
	
	close(comm_fd);
	}
}
