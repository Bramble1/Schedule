#include "functions.h"


int main(int argc,char **argv)
{
	if(argv[1]==NULL)
	{
		printf("./schedule <schedule_name> <hh:mm> <divisor>\n");
		exit(EXIT_SUCCESS);
	}

	char user_input[150]="\0";
	time_regex(argv[2]);
	int divisor=divisor_regex(argv[3]);
	int total_minutes=convert_to_minutes(argv[2]);
	

	double average=calculate_average(total_minutes,divisor);
	Schedule *table=malloc(sizeof(Schedule)*divisor);

	printf("[*]\tSchedule:%s\t[*]\n",argv[1]);
	printf("_________________________________\n\n");

	while(1)
	{
		for(int i=0;i<divisor;i++)
		{
			memset(user_input,'\0',150);
			printf("Enter Task: ");
			fgets(user_input,149,stdin);
			remove_newline(user_input);
			strcpy(table[i].task.name,user_input);
		}
		memset(user_input,'\0',150);
		init_schedule(table,average,divisor);
		print_schedule(table,divisor);

		printf("\nEdit ratios (y/n)?: ");
		fgets(user_input,149,stdin);
		remove_newline(user_input);

		percent=(double)10;

		if(strcmp(user_input,"y")==0)
		{
			system("clear");
			printf("\t[*]Ratio mode[*]\n\n");
			printf("\ttype 'h' for command list\n\n");
			print_schedule(table,divisor);
			while(1)
			{
				printf("\n");
				memset(user_input,'\0',150);
				printf("\n:prompt: ");
				fgets(user_input,149,stdin);
				remove_newline(user_input);

				if(strcmp(user_input,"h")==0)
				{
					system("clear");
					print_schedule(table,divisor);
					
					printf("\n'p' - set percentage.\n");
					printf("type index number to increase task time.\n");
					printf("'c'- clear the terminal.\n");
					printf("'r' - revert table back to original.\n");
					printf("'done' - to proceed.\n");
					
				}
				if(strcmp(user_input,"p")==0)
				{
					system("clear");
					print_schedule(table,divisor);
					printf("Set percentage increase: ");
					int perc=0;
					scanf("%d",&perc);
					percent=(double)perc/100;
					printf("Percentage=%1f\n",percent);
				}
				if(strcmp(user_input,"c")==0)
				{
					system("clear");
					printf("[*]Ratio mode[*]\n\n");
					printf("\ttype 'h'  for command list\n\n");
					print_schedule(table,divisor);
					printf("\n");;
				}
				if(strcmp(user_input,"r")==0)
				{
					init_schedule(table,average,divisor);
					system("clear");
					print_schedule(table,divisor);
				}
				if(strcmp(user_input,"done")==0)
					break;

				char tmp_buffer[100]="\0";
				for(int i=0;i<divisor;i++)
				{
					sprintf(tmp_buffer,"%d",i);
					if(strcmp(user_input,tmp_buffer)==0)
					{
						system("clear");
						print_schedule(table,divisor);
						int number=(int)user_input[0]-'0';
						alter_average(number,table,divisor);
					}
				}
			}//end of while loop
		}//end of if statement
		break;
	}//end of main while loop



	system("clear");
	print_schedule(table,divisor);

	printf("\n");
	save_to_file(table,divisor,argv[1]);
	free(table);

	return 0;
}


