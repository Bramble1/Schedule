#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<math.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>


double percent;

typedef struct
{
	char name[100];
	double time;
}Task;

typedef struct
{
	Task task;
}Schedule;

/*functions*/
void remove_newline(char *buf);
int convert_to_minutes(char *buf);
void time_regex(char *buf);
int divisor_regex(char *buf);
double calculate_average(int numerator,int divisor);

void init_schedule(Schedule *matrix,double average,int divisor);
void alter_average(int index,Schedule *matrix,int divisor);
void print_schedule(Schedule *matrix,int divisor);

void save_to_file(Schedule *matrix,int divisor,char *schedule_name);
