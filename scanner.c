

#include "stdio.h"
#include "sys/socket.h"
#include "errno.h"
#include "netdb.h"
#include "string.h"
#include "stdlib.h"
#include "arpa/inet.h"
#include "unistd.h"

#define RESPONSE_SIZE 10000
#define SEND_SIZE 100

#define SRC_PORT 55490
#define SRC_ADDR "144.126.12.173"


/**
 purpose: send data to the socket and recieve reply
 input: the socket descriptor, the open port
 output: the reply if there is one 0_0
**/
void send_data(int desc, char* host, int port, char* response, char* msg) {
 
  printf("sending data to port %d\n", port);
  
  //send data
  if(send(desc, msg, strlen(msg), 0) < 0)
  {
    printf("send was jerried :(\n");
  }
  else
  {
    printf("full send :)\n");
  }
  
  //receive reply
  printf("getting response from port %d\n", port);
  //int recv_stat = recv(desc, response, RESPONSE_SIZE, 0);
  int a = 0;
  while((recv(desc, response, RESPONSE_SIZE, 0) < 0))// && a < 1000000)
  {
    printf("Here's some stuff\n");
    printf("%s %d \n", response, a);
    a++;
  }
}

/*
  purpose: scans for open ports
  returns: returns the socket descriptor 
*/
void scan_ports(char* ip_addr, char* msg) {
  int err, i, sd;
  int start = 0; 
  int end = 55000;
  struct sockaddr_in sa;
  char reply[RESPONSE_SIZE];


  //initialize sockaddr_in
  sa.sin_addr.s_addr = inet_addr(ip_addr);
  sa.sin_family = AF_INET;

  printf("%d \n",  sa.sin_addr.s_addr );  

  printf("starting port scan\n");
 
   for(i = start; i < end; i ++)
   {

     sa.sin_port = htons(i);
     sd = socket(AF_INET, SOCK_STREAM, 0);
     
     if(sd < 0)
     {
       printf("socket didn't make it\n");
     }

     err = connect(sd, (struct sockaddr*) &sa, sizeof(sa));

    if(err == 0)
    {
       printf("----------------------------------------------------\n");
       printf("port %d is OPEN\n", i);
        
       send_data(sd, ip_addr, i, reply, msg);
    }

    close(sd);
  }
}

int main(int argc, char **argv)
{
  if(argc < 3)
  {
    printf("Missing an Argment \n");
    printf("Usage: scanner <ip4 address> <message to send to open ports>\n");
    exit(-1);
  }
  scan_ports(argv[1], argv[2]);
  return 0;
}

