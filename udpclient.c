/* 
 * udpclient.c - A simple UDP client
 * usage: udpclient <host> <port>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

#define BUFSIZE 1024

/* 
 * error - wrapper for perror
 */
void error(char *msg) {
    perror(msg);
    exit(0);
}

int main(int argc, char **argv) {
    int sockfd, portno, n,i,n1,n2;
    int serverlen;
    struct sockaddr_in serveraddr;
    struct hostent *server;
    char *hostname;
    char buf[BUFSIZE];
    char task[1000] , server_reply[2000], data[100], data1[100], data2[100], item_no[20], quan[20];

    /* check command line arguments */
    if (argc <3) {
       fprintf(stderr,"usage: %s <hostname> <port>\n", argv[0]);
       exit(0);
    }
    hostname = argv[1];
    portno = atoi(argv[2]);

    /* socket: create the socket */
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");

    /* gethostbyname: get the server's DNS entry */
    server = gethostbyname(hostname);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host as %s\n", hostname);
        exit(0);
    }

    /* build the server's Internet address */
    bzero((char *) &serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
	  (char *)&serveraddr.sin_addr.s_addr, server->h_length);
    serveraddr.sin_port = htons(portno);

    //send the message to the server
    serverlen = sizeof(serveraddr);
    strcpy(buf,argv[3]);
    n = sendto(sockfd, buf, strlen(buf), 0,(struct sockaddr *)&serveraddr, serverlen);

     if(strcmp(argv[3],"list")==0)
     {
        
         printf("\nItem\tTitle \t Quantity");
         for (i=0;i< 3;i++)
       {
        //Receive a reply from the server   n = recvfrom(sockfd, buf, strlen(buf), 0, &serveraddr, &serverlen);

      n=recvfrom(sockfd ,data ,50,0, (struct sockaddr *)&serveraddr,&serverlen);
        data[n]=0;
     //printf("\n%s\t", data); 
      n1=recvfrom(sockfd ,data1 , 50,0, (struct sockaddr *)&serveraddr,&serverlen);
      data1[n1]=0;
    // printf("\n%s\t", data1); 
      n2=recvfrom(sockfd ,data2 , 50 ,   0,(struct sockaddr *)&serveraddr,&serverlen);
      data2[n2]=0;
 printf("\n%s\t%s\t%s\n",data,data1, data2); 
   /*if( (n && n1 && n2)   < 0)\
        {
            puts("recv failed");
            break;
        }
         */
        
                 
         //, l1[i].title, l1[i].quantity);
     }      
     close(sockfd);
    }
    else if(strcmp(argv[3],"order")==0)
   { 
	printf("Order sent");
      
       // strcpy(task,argv[2]);
       //strcpy(data1,"54");
       sendto(sockfd,argv[4], sizeof(argv[4]),0,(struct sockaddr *)&serveraddr, serverlen);    // n = sendto(sockfd, buf, strlen(buf), 0, &serveraddr, serverlen);
       sendto(sockfd,argv[5], sizeof(argv[5]),0,(struct sockaddr *)&serveraddr, serverlen);   
       //read(sock, data2, sizeof(data2));
      n= recvfrom(sockfd, data2, 50, 0, (struct sockaddr *)&serveraddr, &serverlen);
        data2[n]=0;
       printf("\n%s", data2);    
       close(sockfd);
   }

  
    return 0;
}
