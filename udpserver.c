/* 
 * udpserver.c - A simple UDP echo server 
 * usage: udpserver <port>
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFSIZE 1024

struct list1
  {
    char item[50];
    char title[50];
    char quantity[50];
} ;

/*
 * error - wrapper for perror
 */
void error(char *msg) {
  perror(msg);
  exit(1);
}

int main(int argc, char **argv) {
   struct list1 l[3]=     { "1", "Star Wars", "100", "2", "Harry Potter", "80",  "3", "Inside Out", "50"};
  int sockfd; /* socket */
  int portno; /* port to listen on */
  int clientlen; /* byte size of client's address */
  struct sockaddr_in serveraddr; /* server's addr */
  struct sockaddr_in clientaddr; /* client addr */
  struct hostent *hostp; /* client host info */
  char buf[BUFSIZE], data[100], data1[100], data2[100]; /* message buf */
  char *hostaddrp; /* dotted decimal host addr string */
  int optval; /* flag value for setsockopt */
  int n; /* message byte size */
  int i,quant,item,on,ret; // iterators
  /* 
   * check command line arguments 
   */
 
  //portno = atoi(5000);
 while(1)
{
  /* 
   * socket: create the parent socket 
   */
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0) 
    error("ERROR opening socket");

  /* setsockopt: Handy debugging trick that lets 
   * us rerun the server immediately after we kill it; 
   * otherwise we have to wait about 20 secs. 
   * Eliminates "ERROR on binding: Address already in use" error. 
   */
  optval = 1;
  setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, 
	     (const void *)&optval , sizeof(int));

  /*
   * build the server's Internet address
   */
  bzero((char *) &serveraddr, sizeof(serveraddr));
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  serveraddr.sin_port = htons(8888);

  /* 
   * bind: associate the parent socket with a port 
   */
  if (bind(sockfd, (struct sockaddr *) &serveraddr, 
	   sizeof(serveraddr)) < 0) 
    error("ERROR on binding");

  /* 
   * main loop: wait for a datagram, then echo it
   */
  clientlen = sizeof(clientaddr);
  n = recvfrom(sockfd, buf, BUFSIZE, 0, (struct sockaddr *) &clientaddr, &clientlen);
   buf[n]=0;
 if (n < 0)
      error("ERROR in recvfrom");
    printf(" \nClient Requested %s\n ", buf);
     
   if (strcmp(buf,"list")==0)
{    
       puts("test");
        for(i=0;i <3; i++)
       {
        //write(client_sock,l[i].item , sizeof(l[i].item));        
        sendto(sockfd, l[i].item, 50, 0, (struct sockaddr *) &clientaddr, clientlen);
        sendto(sockfd, l[i].title,50 , 0, (struct sockaddr *) &clientaddr, clientlen);             // write(client_sock,l[i].title , sizeof(l[i].title));       
        sendto(sockfd, l[i].quantity, 50, 0, (struct sockaddr *) &clientaddr, clientlen);              //write(client_sock,l[i].quantity , sizeof(l[i].quantity));
       }
 close(sockfd);
 //close(socket_desc);
}
      //memset(data, 0, sizeof(data));
   
    else  if(strcmp(buf, "order")==0)
     {
	printf("Order accepted");          

	n=recvfrom(sockfd, data, sizeof(data), 0, (struct sockaddr *) &clientaddr, &clientlen);
   // read(client_sock, data, sizeof(data));	
          data[n]=0;
    item= atoi(data);
   n=recvfrom(sockfd, data1, sizeof(data1), 0, (struct sockaddr *) &clientaddr, &clientlen);
      data1[n]=0;
    //read(client_sock, data1, sizeof(data1));  
    quant=atoi(data1); 
    printf("\n%d\t %d\t\n",item ,quant);
     int b;
      
         for(i=0;i<3;i++)
{          
           char buffer[100];
           if(atoi(l[i].item)== item && (b=atoi(l[i].quantity))>quant)
          {          // b= b-quant;
                 //char num[50];
                char buffer [50];
                 int n;
               sprintf (buffer, " %d",b-quant);
                 printf ("[%s] is a string \n",buffer);
                strcpy( l[i].quantity, buffer);   
                 strcpy( buffer, "Request fullfilled");
              // write(client_sock, "Request fullfilled\n", 100);           
               sendto(sockfd, buffer,100 , 0, (struct sockaddr *) &clientaddr, clientlen);
         }
         if(atoi(l[i].item)== item && (b=atoi(l[i].quantity))<quant)
                 //write(client_sock, "Request cannot fullfilled\n", 100);
              strcpy( buffer, "Request not fullfilled");
              sendto(sockfd, buffer, 100, 0, (struct sockaddr *) &clientaddr, clientlen);
}

    //close(client_sock);
    close(sockfd);
   } 





   

     
     // gethostbyaddr: determine who sent the datagram
    
    hostp = gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr, 
			  sizeof(clientaddr.sin_addr.s_addr), AF_INET);
    if (hostp == NULL)
      error("ERROR on gethostbyaddr");
    hostaddrp = inet_ntoa(clientaddr.sin_addr);
    if (hostaddrp == NULL)
      error("ERROR on inet_ntoa\n");
    printf("server received datagram from %s (%s)\n", 
	   hostp->h_name, hostaddrp);
      int sizebuf= strlen(buf);
    printf("server received %d/%d bytes: %s\n", sizebuf, n, buf);
    
    
      
  }
}
