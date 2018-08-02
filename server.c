#include <stdio.h>
#include <signal.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/socket.h>
#include <errno.h>
#include <sys/wait.h>
#include <ctype.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <fcntl.h>
#include <time.h>
#include "struct.h"

#define LENGTH 512
#define PORT 8080
char user[20];

void new_waiting_task(char * task);
void new_ready_task(char * task, char * value, double time_taken);
int total_tasks(char * task);
char * decrypt(char taskstring[],char value3[]);
char * encrypt(char value1[],char value3[]);
char * delete(char * value,char * portion,char * ptr4);
char *rep(char * value,char * portion);
char * rev(char * value);
void blacklist_task(char * task, char * value, double time_taken);
void bzeronew(char * strg);

int main (int argc, char *argv[])
{

	int server_fd;
	int newsocket;
	int valread;
	int rcv_bytes;
        pid_t childpid;
        struct sockaddr_in newAddr;
	struct sockaddr_in addr_local;
	struct sockaddr_in addr_remote;
	int addrlen = sizeof(struct sockaddr_in);
        time_t timer;
        char buffer[26];
        struct tm* tm_info;
	int id;
	int status;
	int count;
	socklen_t addr_size;
	puts("Performing system checks...\n");

	if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0 )
	{
		perror("Socket failed!");
		exit(EXIT_FAILURE);
	}
	memset(&addr_local,'\0',sizeof(addr_local));//added
	addr_local.sin_family = AF_INET;
	addr_local.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr_local.sin_port = htons(PORT);

	bzero(&(addr_local.sin_zero), 8);   // want to know


	if(bind(server_fd, (struct sockaddr*)&addr_local, sizeof(addr_local)) < 0)
	{
		perror("Binding Socket to the PORT failed!");
		exit(EXIT_FAILURE);
	}

	puts("System check identified no issues (0 silenced).");
    time(&timer);
    tm_info = localtime(&timer);

    strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
    puts(buffer);
	puts("G-6 Server version 1.0.0");

	if(listen(server_fd, 10) < 0)
	{
		perror("Listening to the Connection Failed!");
		exit(EXIT_FAILURE);
	}

	printf ("Listening the PORT %d \n",8080);


	while(1){
		newsocket = accept(server_fd, (struct sockaddr*)&newAddr, &addr_size);
		if(newsocket < 0){
			exit(1);
		}
	printf("Starting development server at http://%s:%d\n", inet_ntoa(addr_remote.sin_addr), ntohs(addr_local.sin_port));
	printf("Client is connected %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
	      	printf("Client is %d\n",ntohs(newAddr.sin_port));

int i;
if((childpid =fork()) == 0){
	   for(i=0;i<1;i++)
		 {
			 printf("Number:%d\n",getpid() );
		 }
      close(server_fd);
	id = read(newsocket,user,1024);
	user[id] =('\0');
	printf("Client Id:%s\n",user);


	while(1)
	{
		char task[10000],feedback[1024];
		char * ptr;
		char * nptr;
        char * mcommand;
        char * mvalue;
        char * content;
        char *word;
        char *word2;
        char *ptr2;
        char *ptr3;
        char *ptr4;
        char command[1024];
        char *value;
        char part1[10][10]={'0'};
        char *portion;
        char value3[200];
        char value1[200];
         struct id client[200];
		bzero(task,10000);

		bzero(feedback,1024);
		valread = read(newsocket, task, LENGTH);


		 if(valread==0||task[0] =='q'){
                                    printf("connection closed\n");
                                    return 0;
                                             }


		if(valread < 0)
		{
			perror("Error in reading path of command from client");
			exit(EXIT_FAILURE);
		}

	    printf("Tasks: %s\n",task);
              count = total_tasks(task);
			send(newsocket, &count, sizeof(int), 0);

		if(count>0) {
		    //puts("Server is free");

			time_t t = time(NULL);
			struct tm tm = *localtime(&t);
			clock_t x;
			x =clock();
                        int y;
			double time_taken;


                        int i=0;

			for(content = strtok_r(task,";", &ptr); content!=NULL; content=strtok_r(NULL, ";",&ptr))
			{
				if(strlen(content) < 2) {
                                                          continue;
                                                         }
 
                                              for( mcommand= strtok_r(content," ", &ptr2); mcommand!=NULL;mcommand=strtok_r(NULL, " ",&ptr2)) 
                                                     {
                                                        if(strcmp(mcommand,"delete")==0||strcmp(mcommand,"replace")==0)
                                                                {
                                                                 char *mvalue = strtok_r(NULL, " ", &ptr2);
                                                                  char *word3 = strtok_r(NULL, " ", &ptr2);
                                                                   
                                                                   client[i].command = mcommand;
				                                   client[i].value = mvalue;
                                                                   client[i].ID = user;
                                                                   client[i].part =word3;
                                                                }
                                                         else
                                                                {
                                                                 char *mvalue = strtok_r(NULL, " ", &ptr2);
                                                             
                                                                  
                                                                   client[i].command = mcommand;
				                                   client[i].value = mvalue;
                                                                   client[i].ID = user;
                                                                   client[i].part= part1[0];
                                                                }
                                                          
                                                     
                                                            
                                                     }   
                                                  
				
				printf("%s,%s,%s,%s\n",client[i].part,client[i].command,client[i].value,client[i].ID);	
                               i++;
				
		
			}
                           
                  
                     char name[250][100],tname[50][50],xname[50][50], temp[100],temp2[100],temp3[100];
                     int j,n=count;
                     
                          for(i=0;i<n;i++)
                               {
                         
                         
                        strcpy(name[i],client[i].value);
                        strcpy(tname[i],client[i].command);
                        strcpy(xname[i],client[i].part);
                                }
                       for (i = 0; i < n - 1 ; i++)

        {

            for (j = i + 1; j < n; j++)

            {

                if (strlen(name[i])> strlen(name[j])) 

                {

                    strcpy(temp, name[i]);
                    strcpy(temp2, tname[i]);
                     strcpy(temp3, xname[i]);
                    strcpy(name[i], name[j]);
                    strcpy(tname[i], tname[j]);
                    strcpy(xname[i], xname[j]);
                    strcpy(name[j], temp);
                    strcpy(tname[j], temp2);
                    strcpy(xname[j], temp3);

                }

            }

        }

 

        printf("\n---------------------------------------------------------------\n");

        printf("Part            Prior   Unsorted.T      Sorted.T       Commands         ID\n");

        printf("-----------------------------------------------------------------\n");

  //Determining priorities
       

        for (i = 0; i < n; i++) 
          
        {
      
      const char *priority[] ={"4","3","1","0"};
          if(strlen(name[i])<=strlen(name[0]) && strcmp(tname[i],"replace")==0)
                  {
           
            printf("%s\t\t%s\t%s\t\t%s\t\t%s\t\t%s",xname[i],priority[0],client[i].value , name[i],tname[i],user);
             
         //saving sorted priotized data into the waiting list
         
                 FILE *ptr;
                 ptr=fopen("waiting.txt","a+");
	         time_t t = time(NULL);
	         struct tm tm = *localtime(&t);
     fprintf(ptr,"%s\t%s\t%s\t%s\t%s\t%d:%d:%d\t%s",xname[i],priority[0],client[i].value,name[i],tname[i],tm.tm_hour,tm.tm_min,tm.tm_sec,client[i].ID);
                 fclose(ptr);

                   }
          else if(strlen(name[i])<=strlen(name[0])) 	
                 {
                   
                    printf("\n%s\t\t%s\t%s\t\t%s\t\t%s\t%s",xname[i],priority[1],client[i].value , name[i],tname[i],user);
                 

                    FILE *ptr;
                    ptr=fopen("waiting.txt","a+");
	            time_t t = time(NULL);
	         struct tm tm = *localtime(&t);
     fprintf(ptr,"%s\t%s\t%s\t%s\t%s\t%d:%d:%d\t%s",xname[i],priority[1],client[i].value,name[i],tname[i],tm.tm_hour,tm.tm_min,tm.tm_sec,client[i].ID);
                    fclose(ptr); 
                  }

          else if(strcmp(tname[i],"replace")==0) 	
                 {
                   
                    printf("\n%s\t\t%s\t%s\t\t%s\t\t%s\t%s",xname[i],priority[2],client[i].value , name[i],tname[i],user); 
          
                    FILE *ptr;
                    ptr=fopen("waiting.txt","a+");
	            time_t t = time(NULL);
	            struct tm tm = *localtime(&t);
    fprintf(ptr,"%s\t%s\t%s\t%s\t%s\t%d:%d:%d\t%s",xname[i],priority[2],client[i].value,name[i],tname[i],tm.tm_hour,tm.tm_min,tm.tm_sec,client[i].ID);
                    fclose(ptr); 
                  }
        
          else 
                 {
                   
                    printf("\n%s\t\t%s\t%s\t\t%s\t\t%s\t\t%s",xname[i],priority[3],client[i].value , name[i],tname[i],user); 
 
                    FILE *ptr;
                    ptr=fopen("waiting.txt","a+");
   
    fprintf(ptr,"%s\t%s\t%s\t%s\t%s\t%d:%d:%d\t%s",xname[i],priority[3],client[i].value,name[i],tname[i],tm.tm_hour,tm.tm_min,tm.tm_sec,client[i].ID);
                    fclose(ptr); 
              
                  }
                   

        }

 

        printf("------------------------------------------------------------------\n");

//Reading data from the waiting file for processing-------
        
        struct array client[256];
	FILE *fptr;
	fptr = fopen("waiting.txt","r");
	 i = 0;


  while(fscanf(fptr,"%s\t%s\t%s\t%s\t%s\t%s\t%s",client[i].first,client[i].second,client[i].third,client[i].fourth,client[i].fifth,client[i].sixth,client[i].seventh)!=EOF){		

	i++;
     }
                //printf("%s %s %s\n",client[0].first,client[1].second,client[2].third);
 //processing data for the client;
 
    //priority 1
            for(j=0;j<count;j++)
                         {  
                             
	                         sleep(1);
                            if(strcmp(client[j].second,"4")==0)
                                  {
                                     if (strcmp(client[j].fifth,"replace")==0 && strlen(client[j].fifth)<=50)
					{

                                                value = client[j].fourth;
                                                portion =client[j].first;
						rep(value,portion);

						printf("SENDING: %s \n", value);
						send(newsocket,value,strlen(value),0);

                                                x=clock()-x;
						time_taken =((double)x)/CLOCKS_PER_SEC;
						new_ready_task(content, value, time_taken);
					}
	                     else
		                    {
		                        value = client[j].fourth;
					x=clock()-x;
					time_taken =((double)x)/CLOCKS_PER_SEC;
					blacklist_task(content, value, time_taken);
					send(newsocket,"Task Blacklisted for begin too long", strlen("Task Blacklisted for begin too long"),0);
				    }
		                     
			                        
                                  }
                         }


   //priority 2
            for(j=0;j<count;j++)
                         {
                                sleep(1);
                            if(strcmp(client[j].second,"3")==0 && strlen(client[j].fifth)<=50)
                                  {
					printf("%s", client[j].fifth);                                         
                                    if (strcmp(client[j].fifth,"double")==0)
					{
						value = client[j].fourth;
                                               
						printf("SENDING: %s \n", value);
						send(newsocket,value,strlen(value),0);

					}
                                  else if(strcmp(client[j].fifth,"rev")==0)
					{
                          
                                                value = client[j].fourth;
						rev(value);
						printf("SENDING: %s \n", value);
						send(newsocket,value,strlen(value),0);
					}
                                   else if(strcmp(client[j].fifth,"encrypt")==0)
					{       

                                                value = client[j].fourth;
                                                strcpy(value1,value);
						ptr4 = encrypt(value1,value3);
                                                strcpy(ptr4,value3);
						printf("SENDING: %s \n", ptr4);
						send(newsocket,ptr4,strlen(ptr4),0);
					} 
				   else if(strcmp(client[j].fifth,"decrypt")==0)
					{

                                                value = client[j].fourth;
                                                strcpy(value1,value);
						ptr4 = decrypt(value1,value3);
                                                strcpy(ptr4,value3);

						printf("SENDING: %s \n", ptr4);
						send(newsocket,ptr4,strlen(ptr4),0);
					} 
				   else if (strcmp(client[j].fifth,"delete")==0)
					{
						value = client[j].fourth;
                                                portion =client[j].first;
                                                delete(value,portion,ptr4);

						printf("SENDING: %s \n", ptr4);
						send(newsocket,ptr4,strlen(ptr4),0);
					}
				     else 
					{
						puts("Command Not Found");
						send(newsocket,"Command Not Found", strlen("Command Not Found"),0);
					}
                                x=clock()-x;
				time_taken =((double)x)/CLOCKS_PER_SEC;
				new_ready_task(content, value, time_taken);

                                    
                                  }
                               
                         else if(strcmp(client[j].second,"3")==0 && strlen(client[j].fifth)>50)
				{

                                        value = client[j].fourth;
					x=clock()-x;
					time_taken =((double)x)/CLOCKS_PER_SEC;
					blacklist_task(content, value, time_taken);
					send(newsocket,"Task Blacklisted : too long", strlen("Task Blacklisted : too long"),0);
				}
                          
                         }

      //priority 3
               for(j=0;j<count;j++)
                         {
                                  sleep(1);
                            if(strcmp(client[j].second,"1")==0 && strlen(client[j].fifth)<=50)
                                  {
                                     if (strcmp(client[j].fifth,"replace")==0)
					{
						
                                                value = client[j].fourth;
                                                portion =client[j].first;
                                                rep(value,portion);

						printf("SENDING: %s \n", value);
						send(newsocket,value,strlen(value),0);
                                                
			                        x=clock()-x;
						time_taken =((double)x)/CLOCKS_PER_SEC;
						new_ready_task(content, value, time_taken); 
					}
                                        else 
					{
						puts("Command Not Found");
						send(newsocket,"Command Not Found", strlen("Command Not Found"),0);
					}
                                  }
                           else if(strcmp(client[j].second,"1")==0 && strlen(client[j].fifth)>50)
                                    {
                                        value = client[j].fourth;
					x=clock()-x;
					time_taken =((double)x)/CLOCKS_PER_SEC;
					blacklist_task(content, value, time_taken);
					send(newsocket,"Task Blacklisted for begin too long", strlen("Task Blacklisted for begin too long"),0);
				    }
                          
                         }
         //priority 4

                 for(j=0;j<count;j++)
                         {
                                 sleep(1);
                            if(strcmp(client[j].second,"0")==0 && strlen(client[j].fifth)<=50)
                                  {
                                     if (strcmp(client[j].fifth,"double")==0)
					{
						value = client[j].fourth;
                                                strcat(value,value);
						printf("SENDING: %s \n", value);
						send(newsocket,value,strlen(value),0);

					}
                                  else if(strcmp(client[j].fifth,"rev")==0)
					{
                          
                                                value = client[j].fourth;

						printf("SENDING: %s \n", value);
						send(newsocket,value,strlen(value),0);
					}
                                   else if(strcmp(client[j].fifth,"encrypt")==0)
					{
                                                value = client[j].fourth;
                                                strcpy(value1,value);
						ptr4 = encrypt(value1,value3);
						printf("SENDING: %s \n", ptr4);
						send(newsocket,ptr4,strlen(ptr4),0);
					} 
				   else if(strcmp(client[j].fifth,"decrypt")==0)
					{
                                                value = client[j].fourth;
                                                strcpy(value1,value);
						ptr4 = decrypt(value1,value3);
                                                strcpy(ptr4,value3);

						printf("SENDING: %s \n", ptr4);
						send(newsocket,ptr4,strlen(ptr4),0);
					} 
				   else if (strcmp(client[j].fifth,"delete")==0)
					{
                                                value = client[j].fourth;
                                                portion =client[j].first;
						delete(value,portion,ptr4);

						printf("SENDING: %s \n",ptr4 );
						send(newsocket,ptr4,strlen(ptr4),0);
					}
				     else 
					{
						puts("Command Not Found");
						send(newsocket,"Command Not Found", strlen("Command Not Found"),0);
					}
                                x=clock()-x;
				time_taken =((double)x)/CLOCKS_PER_SEC;
				new_ready_task(content, value, time_taken);

                                    
                                  }
                           else if(strcmp(client[j].second,"0")==0 && strlen(client[j].fifth)>50)
                                   {
                                        value = client[j].fourth;
					x=clock()-x;
					time_taken =((double)x)/CLOCKS_PER_SEC;
					blacklist_task(content, value, time_taken);
					send(newsocket,"Task Blacklisted for begin too long", strlen("Task Blacklisted for begin too long"),0);
				    }
                         }
 

             	remove("waiting.txt");
            FILE *ptr;
            ptr=fopen("waiting.txt","w");

	// task is done
			// check saved tasks
			//status = 0;
		} 
                   
                 
                   


		
                 }
             }
             
	}
   // close(newsocket);
	return 0;
}




   
   


void new_ready_task(char * task, char * value, double time_taken)
{
    FILE *ptr;
    ptr=fopen("ready.dat","a+");
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	fprintf(ptr,"%s\t%s\t%d-%d-%d \t %d:%d:%d \t %f \t %s \n",task, value,tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec,time_taken,user);
    fclose(ptr);

    printf("\nTask Added to Ready Jobs successfully!\n");
}

void blacklist_task(char * task, char * value, double time_taken)
{
    FILE *ptr;
    ptr=fopen("blacklist.dat","a+");
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	fprintf(ptr,"%s\t%s\t%d-%d-%d \t %d:%d:%d \t %f \t %s \n",task, value,tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec,time_taken,user);
    fclose(ptr);

    printf("\nTask Added to Ready Jobs successfully!\n");
}

int total_tasks(char * task) {

	int count =0,i;

	for(i=0;i<strlen(task);i++)
	{
		if(task[i] == ';') count++;
	}

	return count;
}

char * delete(char * value,char * portion,char * ptr4) {

			
                        char stringoptions[30];
			char string[80];

		strcpy(string,value);
		strcpy(stringoptions,portion);
		char arr2[20],z[20],ll[20],r[8][3],b[20];
		int l,i=0,d,f,g,h,n,j=0,k,x[20],p;
		l = strlen(stringoptions);

		for(i=0,j=0; i<l; i++,j++)
                           {
		
		            if(i%2==0)
                                {
		
					 z[i/2] = stringoptions[i];
					 ll[0] = stringoptions[i];
					 strcpy(r[i/2],ll);

		                 } 

                            if(i==(l-1))
                                 {

		                     p = i/2;
		                  }

		           }

		int len = l-p;
		int e = atoi(z);
		    for(d=0;d<len;d++)
                              {
		                x[d] = atoi(r[d]);

		              }

		   int rn = strlen(string);

		   int ww = sizeof(x)/sizeof(int);

		   int fr = rn-len+1;

		   int shar=0;
		   int xy=0;

		//process to delete
		   for(i=0; i<fr+2; i++)
                           {
		             shar=0;
		               for(j=0; j<(l-p); j++)
                                      {
		                          if(i==(x[j]-1))
                                                   { 
                                                      shar++;  
                                                         i++; 
                                                        xy++;
                                                    }
				        }

			  arr2[i-xy]= string[i];

                           }
                     strcpy(ptr4,arr2);
	
}

char * encrypt(char value1[],char value3[]) {

	
        int x,y;
	char data[100][100],value2[1000];
	char data1[]={'|','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y',
		     'z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

	strcpy(data[0],"|");
	strcpy(data[1],"A"); strcpy(data[2],"B"); 
	strcpy(data[3],"C"); strcpy(data[4],"D");
	strcpy(data[5],"E"); strcpy(data[6],"F"); strcpy(data[7],"G");
	strcpy(data[8],"H"); strcpy(data[9],"I");strcpy(data[10],"1iA0");
	strcpy(data[11],"1jB1"); strcpy(data[12],"1kC2"); strcpy(data[13],"1lD3");
	strcpy(data[14],"1mE4"); strcpy(data[15],"1nF5"); strcpy(data[16],"1oG6");
	strcpy(data[17],"1pH7");strcpy(data[18],"1qI8"); strcpy(data[19],"1r1Ai09");
	strcpy(data[20],"2s1Bj10"); strcpy(data[21],"2t1Ck21");strcpy(data[22],"2u1Dl32");
	strcpy(data[23],"2v1Em43"); strcpy(data[24],"2w1Fn54"); strcpy(data[25],"2x1Go65");
	strcpy(data[26],"2y1Hp76"); strcpy(data[27],"2z1Iq87"); strcpy(data[28],"2a1r1Ai098"); 
	strcpy(data[29],"2b2s1Bj109");strcpy(data[30],"3c2t1Ck210"); strcpy(data[31],"3d2u1Dl321");
	strcpy(data[32],"3e2v1Em432"); strcpy(data[33],"3f2w1Fn543");strcpy(data[34],"3g2x1Go654");
	strcpy(data[35],"3h2y1Hp765");strcpy(data[36],"3i2z1Iq876"); strcpy(data[37],"3j2a1rA1i0987");
	strcpy(data[38],"3k2b2sB1j1098"); strcpy(data[39],"3l3c2tC1k2109"); strcpy(data[40],"4m3d2uD1l3210");
	strcpy(data[41],"4n3e2vE1m4321"); strcpy(data[42],"4o3f2wF1n5432"); strcpy(data[43],"4p3g2xG1o6543");
	strcpy(data[44],"4q3h2yH1p7654"); strcpy(data[45],"4r3i2zI1q8765"); strcpy(data[46],"4s3j2a1rA1i09876");
	strcpy(data[47],"4t3k2b2sB1j10987");strcpy(data[48],"4u3l3c2tC1k21098"); strcpy(data[49],"4v4m3d2uD1l32109"); 
	strcpy(data[50],"5w4n3e2vE1m43210");strcpy(data[51],"5x4o3f2wF1n54321"); strcpy(data[52],"5y4p3g2xG1o65432");
	strcpy(value2," ");

		for(x=0;x<strlen(value1);x++)
		            { 
		               for(y=0;y<sizeof(data1);y++)
		                            { 
		                               if(value1[x]==data1[y])
		                                    {
		                                       strcat(value2,data[y]);
		                                    }
		                             }
		             }
		
	             strcpy(value3,value2);

		return value3;
}

char * decrypt(char taskstring[],char value3[]) 
{
	int i,a,tmpn=0,fnex=0,chfound=0,stt=0,end=0;
	char tempp[28];
	char validvs[54][18],finalstr[1000], alphabets[]={' ','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	strcpy(validvs[0],"?"); strcpy(validvs[1],"A"); strcpy(validvs[2],"B"); strcpy(validvs[3],"C"); strcpy(validvs[4],"D");
	strcpy(validvs[5],"E"); strcpy(validvs[6],"F"); strcpy(validvs[7],"G"); strcpy(validvs[8],"H"); strcpy(validvs[9],"I");
	strcpy(validvs[10],"1iA0"); strcpy(validvs[11],"1jB1"); strcpy(validvs[12],"1kC2"); strcpy(validvs[13],"1lD3");
	strcpy(validvs[14],"1mE4"); strcpy(validvs[15],"1nF5"); strcpy(validvs[16],"1oG6"); strcpy(validvs[17],"1pH7");
	strcpy(validvs[18],"1qI8"); strcpy(validvs[19],"1r1Ai09");  strcpy(validvs[20],"2s1Bj10"); strcpy(validvs[21],"2t1Ck21");
	strcpy(validvs[22],"2u1Dl32");  strcpy(validvs[23],"2v1Em43"); strcpy(validvs[24],"2w1Fn54"); strcpy(validvs[25],"2x1Go65");
	strcpy(validvs[26],"2y1Hp76"); strcpy(validvs[27],"2z1Iq87"); strcpy(validvs[28],"2a1r1Ai098"); strcpy(validvs[29],"2b2s1Bj109");
	strcpy(validvs[30],"3c2t1Ck210"); strcpy(validvs[31],"3d2u1Dl321"); strcpy(validvs[32],"3e2v1Em432"); strcpy(validvs[33],"3f2w1Fn543");
	strcpy(validvs[34],"3g2x1Go654");  strcpy(validvs[35],"3h2y1Hp765"); strcpy(validvs[36],"3i2z1Iq876"); strcpy(validvs[37],"3j2a1rA1i0987");
	strcpy(validvs[38],"3k2b2sB1j1098"); strcpy(validvs[39],"3l3c2tC1k2109"); strcpy(validvs[40],"4m3d2uD1l3210"); strcpy(validvs[41],"4n3e2vE1m4321"); strcpy(validvs[42],"4o3f2wF1n5432"); strcpy(validvs[43],"4p3g2xG1o6543");
	strcpy(validvs[44],"4q3h2yH1p7654"); strcpy(validvs[45],"4r3i2zI1q8765"); strcpy(validvs[46],"4s3j2a1rA1i09876"); strcpy(validvs[47],"4t3k2b2sB1j10987");
	strcpy(validvs[48],"4u3l3c2tC1k21098"); strcpy(validvs[49],"4v4m3d2uD1l32109"); strcpy(validvs[50],"5w4n3e2vE1m43210");
	strcpy(validvs[51],"5x4o3f2wF1n54321"); strcpy(validvs[52],"5y4p3g2xG1o65432");
		 do{
		    tmpn=0; /*reset tmpn*/
		    for(i=stt;i<=end;i++){ sprintf(&tempp[tmpn],"%c",taskstring[i]); tmpn++; }
		    for(a=1;a<=52;a++){ if(!strcmp(tempp,validvs[a])){ sprintf(&finalstr[fnex],"%c",alphabets[a]);  fnex++; chfound=1; stt=end+1; end=end+1; bzeronew(tempp); break; } }
		    if(chfound==0){end=end+3; }else{chfound=0;}
		    if(taskstring[end]==' ' || end >= strlen(taskstring)){ break; }
		 }while(chfound==0);
	             strcpy(value3,finalstr);
		return value3;
     }

void bzeronew(char * strg){ for(int i=0;i<sizeof(strg);i++){ strg[i]='\0'; } }


char * rep(char * value,char * portion) {

	char * result;
        int i,j=0,pos;
	char pch[3];
    while(j<strlen(portion))
            {
	if(portion[j]==' ')
                  {
		            break;
		
		   }
                sprintf(pch,"%c",portion[j]);
		pos=atoi(pch); 
		value[pos-1]=portion[j+2]; 
		j+=4;
             }
   

	return result;
}


char * rev(char * value) 
                   {

	char * result;
	int x = strlen(value) - 1;
	int y = 0;
	char ch;

		while (x > y)
		{
			ch = value[x];
			value[x] = value[y];
			value[y] = ch;
			x--;
			y++;
		}
	return result;
           }

