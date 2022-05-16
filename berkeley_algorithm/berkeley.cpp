#include<iostream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>                  
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<errno.h>
#include<unistd.h>
#include<netinet/in.h>
#include<ctime>
#include<math.h>

using namespace std;

/*

Main method to synchronize the logical clock values.
 
*/

int main(int argc, char** argv)
{
     
	srand(time(NULL)-atoi(argv[1]));
	
	int logicalClock = rand()%50;
	int total_num_process = atoi(argv[3])-1;
	
	int base =4000;
	int arr[total_num_process];
	
	struct sockaddr_in remoteProcessaddr[total_num_process];
	int nodesock[total_num_process];
	
	if(atoi(argv[1]) == atoi(argv[2]))
	{
         
	int j =1 ;
	for(int i = 0; i < total_num_process; i++)
	{
	//comparison of the process_id and the timedaemon id to identify which process is the time daemon
	if(j == atoi(argv[2]))
	{
	j++;
	}
          	
	remoteProcessaddr[i].sin_family = AF_INET;
	remoteProcessaddr[i].sin_port = htons(base+ j);
	remoteProcessaddr[i].sin_addr.s_addr = inet_addr("127.0.0.1"); 
          	
	bzero(&remoteProcessaddr[i].sin_zero,8);
	nodesock[i] = socket(AF_INET,SOCK_STREAM,0);
          	
	if(nodesock[i]==-1)
	{
	perror("Error creating the socket");
	exit(-1);
	}
                
	if(connect(nodesock[i],(struct sockaddr*)&remoteProcessaddr[i],sizeof(struct sockaddr_in))==-1)
	{
	perror("error connecting to other node"); 	
	exit(-1); 	
	}
        j++;
	}
           
	for(int i=0; i < total_num_process; i++)
	{
	int sen = send(nodesock[i],&logicalClock,sizeof(logicalClock),0);
           
           //each process in the distributed system sends its local time to the time daemon
	}
           
	int diff ,sum =0;
	for(int i=0; i < total_num_process; i++)
	{
	int   receive = recv(nodesock[i],&diff,sizeof(diff),0);
	arr[i] = diff;
	sum = sum+ diff;
	}
           
           //calculating the average time of all the processes
	float avg = sum*1.0f/(total_num_process+1);
	int timeSetting = ceil(logicalClock + avg);
           //sending the offset time needed to adjust
	for(int i=0; i< total_num_process; i++)
	{
	float adjust = arr[i]*1.0f - avg;
	adjust = -adjust;
	adjust = ceil(adjust);
	int send_adjust = (int)adjust; 
	int sendtime = send(nodesock[i],&send_adjust,sizeof(timeSetting),0);
	close(nodesock[i]);
	}
       
        cout << "Process "<<argv[1]<< " : logical time before sync: "<< logicalClock << ", logical time after sync:"<< timeSetting <<"  --Time Daemon--" <<endl;
	}    
	else
	{
          // recieves messages from the time daemon asking to adjust the clock
 	int mysock, timeDaemonSock;
	struct sockaddr_in myaddr,timeDaemonaddr;
	
	mysock = socket(AF_INET,SOCK_STREAM,0);
	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(base+atoi(argv[1]));
	myaddr.sin_addr.s_addr = INADDR_ANY;
	
	bzero(&myaddr.sin_zero,8);
	unsigned int length = sizeof(struct sockaddr_in);

	if(::bind(mysock,(struct sockaddr*)&myaddr,length)==-1)
	{
	perror("error in binding");
	exit(-1);
	}
	
	if(listen(mysock,3)==-1)
	{
	perror("Error while listening");
	exit(-1); 
	}
          
	timeDaemonSock = accept(mysock,(struct sockaddr*)&timeDaemonaddr,&length);
	if(timeDaemonSock==-1)
	{
	perror("error connecting to TimeDaemon");
	}
         
	int msg;   
         
	int received = recv(timeDaemonSock,&msg,sizeof(msg),0); 
	int difference = logicalClock - msg;
             
         //send the difference of its local clock and TimeDaemon clock
	int sent1 = send(timeDaemonSock,&difference,sizeof(difference),0);
         //recieve message from Time Daemon asking to adjust its clock
	int setTime=0;   
	int  received1 = recv(timeDaemonSock, &setTime,sizeof(setTime),0);
	setTime = logicalClock + setTime;
	cout << "Process "<<argv[1]<< " : logical time before sync: "<< logicalClock << ", logical time after sync:"<< setTime<< endl;
	close(timeDaemonSock);
	} 
}   
