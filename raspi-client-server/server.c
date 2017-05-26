#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <netdb.h>
#include <errno.h>
#include <string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>


int main(){

	int server_fd,client_fd;
	struct sockaddr_in caddr,saddr;
	char *ip="10.42.0.249"; //server ip
	char msg[100];
	
	FILE *file;
	char* filename="kayit.txt";

       file=fopen(filename,"w+");

		
	//Server Socket Address
	saddr.sin_family=AF_INET;
	saddr.sin_port=htons(7774); //create port

	saddr.sin_addr.s_addr=htonl(INADDR_ANY);

	//Create server socket
	server_fd=socket(PF_INET,SOCK_STREAM,0);
	if(server_fd == -1){
		printf("Error on socket creation [%s] \n",strerror(errno));
		return (-1); 
	}

	//Bind the address to server socket
	if(bind(server_fd,(struct sockaddr *)&saddr, sizeof(struct sockaddr))==-1){
		printf("Error socket bind [%s] \n",strerror(errno));
		return (-1); 
	}

	//Listen for a connection request
	if(listen(server_fd,1)){
		printf("Error socket listen [%s] \n",strerror(errno));
		return (-1); 
	}
 //Bind the address to server socket
        if(bind(server_fd,(struct sockaddr *)&saddr, sizeof(struct sockaddr))==$
                printf("Error socket bind [%s] \n",strerror(errno));
                return (-1); 
        }


	//Accept connection request and connect
	socklen_t addrSize=sizeof(caddr);	
	if((client_fd=accept(server_fd,(struct sockaddr*)&caddr,&addrSize))==-1){
		printf("Error socket accept [%s] \n",strerror(errno));
		close(server_fd);
		return (-1); 
	}
	printf("Server new connecton has been established [%s/%d]\n",inet_ntoa(caddr.sin_addr),caddr.sin_port);


	int size;
	int client=0;
	int ind=0;

	while(!client){
			//read and write maeesages
			if((size=read(client_fd,msg,sizeof(msg)))==-1){
				printf("Error reading [%s] \n",strerror(errno));
 			}
			else{
				msg[size]='\0';

				 if(fputs(msg,file)!=-1){
                                printf("Recorded data  [%s]\n",msg);
                               
                                }

 			
			}
			
			fflush(file);
			if(!strncmp(msg,"quit",4)){  // if client send quit word ,  client connection and server are closed
				printf("Record ending....\n");
				close(client);
				client=1;
			}

	}

	//Close connections
    fclose(file);
	close(server_fd);
	return 0;
}
