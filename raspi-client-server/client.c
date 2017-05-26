#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <netdb.h>
#include <errno.h>
#include <string.h>





int main(){

	int socket_fd;
	struct sockaddr_in caddr;
	char *ip="10.42.0.249";
	char msg[100];

       

	
	//Socket Address
	caddr.sin_family=AF_INET;
	caddr.sin_port=htons(7774);  //you can give port number as you want ,but can not special port or already used port
	if(inet_aton(ip,&caddr.sin_addr)==0){
		return (-1);
	}
	
	//Create socket
	socket_fd=socket(PF_INET,SOCK_STREAM,0);
	if(socket_fd == -1){
		printf("Error on socket creation [%s] \n",strerror(errno));
		return (-1); 
	}
	
	//Establish connection
	if(connect(socket_fd, (const struct sockaddr *)&caddr,sizeof(struct sockaddr))== -1){
		printf("Error on socket connect [%s] \n",strerror(errno));
		return (-1);
	}

	//Read and write data
	//client sent word until the user input "quit" message
	
	while(strncmp(msg,"quit",4)){
		printf("Enter a word: ");
		scanf("%s",msg);

		if(write(socket_fd,msg,sizeof(msg))!=sizeof(msg)){
			printf("Error writing [%s] \n",strerror(errno));
		}
		else{
			printf("Sent data [%s] \n",msg);
		}
	}
           
       

	//Close the connection
	close(socket_fd);
	return 0;

}





