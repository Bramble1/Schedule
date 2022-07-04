#include "functions.h"

void remove_newline(char *buf)
{
	int length=strlen(buf);
	if(buf[length-1]=='\n')
	{
		printf("[+]Found newline and removing byte.[+]\n");
		buf[length-1]='\0';
	}
}

void time_regex(char *buf)
{
	int byte_length=(int)strlen(buf);
	int length=0;

	if(byte_length!=5)
	{
		printf("[!]Insufficient number of bytes.\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		if((buf[0]-'0'<0||buf[0]-'0'>9)||(buf[1]-'0'<0||buf[1]-'0'>9))
		{
			printf("[!]hh must be numerical characters.\n");
			exit(EXIT_FAILURE);
		}
		if(buf[2]!=':')
		{
			printf("[!]Incorrect format.[+].\'hh:mm\'\n");
			exit(EXIT_FAILURE);
		}
		if((buf[3]-'0'<0||buf[3]-'0'>9)||(buf[4]-'0'<0||buf[4]-'0'>9))
		{
			printf("[!]mm must be numerical characters.\n");
			exit(EXIT_FAILURE);
		}
		if(((buf[3]-'0')*10)+(buf[4]-'0')>=60)
		{
			printf("[!]mm must be less than 60.\n");
			exit(EXIT_FAILURE);
		}
	}

}

int divisor_regex(char *buf)
{
	if(buf[0]-'0'<0||buf[0]-'0'>9)
	{
		printf("[!]divisor must be a numerical value.\n");
		exit(EXIT_FAILURE);
	}

	return (buf[0]-'0');
}

int convert_to_minutes(char *buf)
{
	int hour=buf[0]-'0';hour*10;hour+=buf[1]-'0';hour*=60;
	int minutes=buf[3]-'0';minutes*=10;minutes+=buf[4]-'0';


	int total_minutes = hour + minutes;

	printf("total minutes=%d\n",total_minutes);
	
	return total_minutes;
}

double calculate_average(int numerator,int divisor)
{
	return(numerator*pow(divisor,-1));
}


void init_schedule(Schedule *matrix,double average,int divisor)
{
	for(int i=0;i<divisor;i++)
	{
		matrix[i].task.time=average;
	}	
}

void alter_average(int index,Schedule *matrix,int divisor)
{
	int new_divisor=divisor-1;
	int temp=10;

	printf("percentage=%1f\n",percent);

	double shared_amount = percent * pow(new_divisor,-1);
	double added_amount=0;

	for(int i=0;i<new_divisor;i++)
		printf("amount half needs subtracting=%1f\n",shared_amount);

	for(int i=0;i<divisor;i++)
		if(i!=index)
		{
			added_amount=0;
			added_amount=(matrix[i].task.time * shared_amount);
			matrix[i].task.time-=added_amount;
			matrix[index].task.time+=added_amount;
		}
}

void print_schedule(Schedule *matrix,int divisor)
{
	printf("__________________________________\n\n");
	for(int i=0;i<divisor;i++)
		printf("[%d]:%s\t%.2f minutes.\n",i,matrix[i].task.name,matrix[i].task.time);
	
	printf("\t\t\tpercentage=%.1f\n",percent);
	printf("__________________________________\n\n");

}


void save_to_file(Schedule *matrix,int divisor,char *schedule_name)
{

	remove(schedule_name);

	int fd;
	fd=open(schedule_name,O_WRONLY|O_CREAT|O_APPEND,S_IRWXU);
	if(fd==-1)
	{
		perror("open:");
		exit(EXIT_FAILURE);
	}

	char output[200]="\0";

	for(int i=0;i<divisor;i++)
	{
		sprintf(output,"[%d]:%s\t%.2f minutes.\n",i,matrix[i].task.name,matrix[i].task.time);
		write(fd,output,strlen(output));	
		memset(output,'\0',200);
	}

	close(fd);

	printf("[+]Schedule saved as %s in current directory.\n",schedule_name);
}

