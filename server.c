#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<ctype.h>
#include "interface.h"

//void initialise_program(int argc,char **argv);
//Validation for file pointers
void file_handling_check(int ,char **);

//cmp modules
void cmp_usage(FILE *,FILE *,int,int,char **,int,int,int);
void cmp_base(FILE *,FILE *,int,int,char **);
void cmp_b(FILE *,FILE *,int,int,char **);
void cmp_n(FILE *,FILE *,int,int,int,char **);

//Other functions
int size_of_file(FILE *);
int num_grab(char *);
bool is_num_check(char);


void initialise_program(int argc,char **argv)
{	
	if(argc > 1)
	{
		if(strcmp(argv[1],"cmp")==0)
		{
			if(argc>9)
			{
				printf("Invalid number of arguments.\n");
			}
			else if(argc == 2)
			{
				printf("Missing operands after 'cmp'.\n");
			}
			else if(argc == 3)
			{
				printf("cmp requires exactly 2 files to compare.\n");
			}
			else
			{
				file_handling_check(argc,argv);
			}
		}
		else
		{
			printf("Invalid command.\nPlease enter cmp only.\n");
		}
	}
	else
	{
		printf("No commands or files as source.\n");
		printf("File assumes command line arguments of the form\nexecutable_file cmp file_to_be_compared_1 file_to_be_compared_2 [FLAGS] [SKIP1] [SKIP2]\n");
		printf("FLAG and SKIP are optional");
		printf("Please note all parameters passed are case-sensitive.\n");
		exit(0);
	}
}

void file_handling_check(int argc,char **argv)
{
	FILE *f1,*f2;
	f1=fopen(argv[2],"r");
	f2=fopen(argv[3],"r");
	int skip1=-1;
	int skip2=-1;
	int n_bytes=-1;
	if(f1==NULL)
	{
		printf("%s does not exist in the directory or is invalid\n",argv[2]);
		exit(1);
	}
	else if(f2==NULL)
	{
		printf("%s does not exist in the directory or is invalid\n",argv[3]);
		exit(1);
	}
	else
	{
		//int n_parameter=0; 
		if(argc == 4)
		{
			//Base cmp condition with no skip or flags
			cmp_usage(f1,f2,0,argc,argv,0,0,0);
		}
		else if(argc == 5)
		{
			//Condition is valid if flag = -b or bytes to be skipped from 1st file
			if(strcmp(argv[4],"-b")==0)
			{
				cmp_usage(f1,f2,1,argc,argv,0,0,0);
			}
			else
			{
				if((skip1=num_grab(argv[4]))>-1)
				{
					cmp_usage(f1,f2,0,argc,argv,skip1,0,0);
				}
				else
				{
					printf("Invalid parameters\n");
				}
			}
		}
		else if(argc == 6)
		{
			if((strcmp(argv[4],"-b")==0)&&((skip1=num_grab(argv[5]))>-1))
			{
				cmp_usage(f1,f2,1,argc,argv,skip1,0,0);
			}
			else if((strcmp(argv[4],"-n")==0)&&((n_bytes=num_grab(argv[5]))>-1))
			{
				cmp_usage(f1,f2,2,argc,argv,0,0,n_bytes);
			}
			else if(((skip1=num_grab(argv[4]))>-1)&&((skip2=num_grab(argv[5]))>-1))
			{
				cmp_usage(f1,f2,0,argc,argv,skip1,skip2,0);
			}
			else
			{
				printf("Invalid Parameters.\n");
			}
		}
		else if(argc == 7)
		{
			//validation_for_7_arguments();
			if((strcmp(argv[4],"-b")==0)&&((skip1=num_grab(argv[5]))>-1)&&((skip2=num_grab(argv[6]))>-1))
			{
				cmp_usage(f1,f2,1,argc,argv,skip1,skip2,0);
			}
			else if((strcmp(argv[4],"-n")==0)&&((n_bytes=num_grab(argv[5]))>-1)&&(((skip1=num_grab(argv[6]))>-1)))
			{
				cmp_usage(f1,f2,2,argc,argv,skip1,0,n_bytes);
			}
			else if((strcmp(argv[4],"-b")==0)&&(strcmp(argv[5],"-n")==0)&&((n_bytes=num_grab(argv[6]))>-1))
			{
				cmp_usage(f1,f2,1,argc,argv,0,0,n_bytes);
			}
			else if((strcmp(argv[4],"-n")==0)&&((n_bytes=num_grab(argv[5]))>-1)&&(strcmp(argv[6],"-b")==0))
			{
				cmp_usage(f1,f2,2,argc,argv,0,0,n_bytes);
			}
			else
			{
				printf("Invalid Parameters.\n");
			}
		}
		else if(argc == 8) 
		{
			//validation_for_8_arguments();
			if((strcmp(argv[4],"-n")==0)&&((n_bytes=num_grab(argv[5]))>-1)&&((skip1=num_grab(argv[6]))>-1)&&((skip2=num_grab(argv[7]))>-1))
			{
				cmp_usage(f1,f2,2,argc,argv,skip1,skip2,n_bytes);
			}
			else if((strcmp(argv[4],"-b")==0)&&(strcmp(argv[5],"-n")==0)&&((n_bytes=num_grab(argv[6]))>-1)&&((skip1=num_grab(argv[7]))>-1))
			{
				cmp_usage(f1,f2,1,argc,argv,skip1,0,n_bytes);
			}
			else if((strcmp(argv[4],"-n")==0)&&((n_bytes=num_grab(argv[5]))>-1)&&(strcmp(argv[6],"-b")==0)&&((skip1=num_grab(argv[7]))>-1))
			{
				cmp_usage(f1,f2,2,argc,argv,skip1,0,n_bytes);
			}
			else
			{
				printf("Invalid Parameters.\n");
			}
		}
		else if(argc == 9)
		{
			if((strcmp(argv[4],"-b")==0)&&(strcmp(argv[5],"-n")==0)&&((n_bytes=num_grab(argv[6]))>-1)&&((skip1=num_grab(argv[7]))>-1)&&((skip2=num_grab(argv[8]))>-1))
			{
				cmp_usage(f1,f2,1,argc,argv,skip1,skip2,n_bytes);
			}
			else if((strcmp(argv[4],"-n")==0)&&((n_bytes=num_grab(argv[5]))>-1)&&(strcmp(argv[6],"-b")==0)&&((skip1=num_grab(argv[7]))>-1)&&((skip2=num_grab(argv[8]))>-1))
			{
				cmp_usage(f1,f2,2,argc,argv,skip1,skip2,n_bytes);
			}
			else
			{
				printf("Invalid Parameters.\n");
			}
		}
		else
		{
			printf("Too many parameters.\n");
		}
	}
	fclose(f1);
	fclose(f2);		
}


	

//0 base cmp with skip1 and skip 2
//1 -b cmp with skip1 and skip 2
//2 -n cmp with skip1 and skip 2
void cmp_usage(FILE *f1,FILE *f2,int n,int argc ,char **argv,int skip1,int skip2,int n_bytes)
{
	//OFFSET Module to find size of the files
	int offset_file1=size_of_file(f1);
	int offset_file2=size_of_file(f2);
	if(skip1>offset_file1)
	{
		printf("EOF on %s.\n",argv[2]);
	}
	else if(skip2>offset_file2)
	{
		printf("EOF on %s.\n",argv[3]);
	}
	else
	{
		if(n==0)
		{
			cmp_base(f1,f2,skip1,skip2,argv);
		}
		else if(n==1)
		{
			cmp_b(f1,f2,skip1,skip2,argv);
		}
		else
		{
			cmp_n(f1,f2,skip1,skip2,n_bytes,argv);
		}
	}
}


void cmp_base(FILE *f1,FILE *f2,int skip1_bytes,int skip2_bytes,char **argv)
{
	char ch_from_file1,ch_from_file2;
	int byte_count=0;
	int line_count=1;
	int flag=1;int diff_count=0;
	
	//Module to skip bytes
	if(skip1_bytes!=0)
	{
		fseek(f1,skip1_bytes,SEEK_SET);
	}
	
	if(skip2_bytes!=0)
	{
		fseek(f2,skip2_bytes,SEEK_SET);
	}
	
	do
	{
		ch_from_file1=fgetc(f1);
		ch_from_file2=fgetc(f2);
		byte_count++;
		if(feof(f1))
		{
			printf("EOF on %s after byte %d,line %d\n",argv[2],byte_count,line_count-1);
			flag=0;
		}
		if(feof(f2)&&flag)
		{
			printf("EOF on %s after byte %d,line %d\n",argv[3],byte_count,line_count-1);
			flag=0;
		}
		if((ch_from_file1!=ch_from_file2)&&flag)
		{
			printf("%s %s differ: byte %d, line %d\n",argv[2],argv[3],byte_count,line_count);
			diff_count++;
			flag=0;
		}
		if((ch_from_file1=='\n')&&flag)
		{
			line_count++;
		}
	}while(flag);
	if(diff_count==0)
	{
		printf("Files are identical byte-wise.\n");
	}		
}

void cmp_b(FILE *f1,FILE *f2,int skip1_bytes,int skip2_bytes,char **argv)
{
	char ch_from_file1,ch_from_file2;
	int byte_count=0;
	int line_count=1;
	int flag=1;int diff_count=0;
	
	//Module to skip bytes
	if(skip1_bytes!=0)
	{
		fseek(f1,skip1_bytes,SEEK_SET);
	}
	
	if(skip2_bytes!=0)
	{
		fseek(f2,skip2_bytes,SEEK_SET);
	}
	
	do
	{
		ch_from_file1=fgetc(f1);
		ch_from_file2=fgetc(f2);
		byte_count++;
		if(feof(f1))
		{
			printf("EOF on %s after byte %d,line %d\n",argv[2],byte_count,line_count);
			flag=0;
		}
		if(feof(f2)&&flag)
		{
			printf("EOF on %s after byte %d,line %d\n",argv[3],byte_count,line_count);
			flag=0;
		}
		if((ch_from_file1!=ch_from_file2)&&flag)
		{
			printf("%s %s differ: byte %d, line %d.\n%x in %s and %x in %s",argv[2],argv[3],byte_count,line_count,ch_from_file1,argv[2],ch_from_file2,argv[3]);
			diff_count++;
			flag=0;
		}
		if((ch_from_file1=='\n')&&flag)
		{
			line_count++;
		}
	}while(flag);
	if(diff_count==0)
	{
		printf("Files are identical byte-wise.\n");
	}		
}

void cmp_n(FILE *f1,FILE *f2,int skip1_bytes,int skip2_bytes,int n_bytes,char **argv)
{
	char ch_from_file1,ch_from_file2;
	int byte_count=0;
	int line_count=1;
	int flag=1;int diff_count=0;
	
	//Module to skip bytes
	if(skip1_bytes!=0)
	{
		fseek(f1,skip1_bytes,SEEK_SET);
	}
	
	if(skip2_bytes!=0)
	{
		fseek(f2,skip2_bytes,SEEK_SET);
	}
	
	do
	{
		ch_from_file1=fgetc(f1);
		ch_from_file2=fgetc(f2);
		byte_count++;
		if(feof(f1))
		{
			printf("EOF on %s after byte %d,line %d\n",argv[2],byte_count,line_count);
			flag=0;
		}
		if(feof(f2)&&flag)
		{
			printf("EOF on %s after byte %d,line %d\n",argv[3],byte_count,line_count);
			flag=0;
		}
		if((ch_from_file1!=ch_from_file2)&&flag)
		{
			printf("%s %s differ: byte %d, line %d\n",argv[2],argv[3],byte_count,line_count);
			diff_count++;
			flag=0;
		}
		if((ch_from_file1=='\n')&&flag)
		{
			line_count++;
		}
	}while(flag && byte_count<n_bytes);
	if(diff_count==0)
	{
		printf("Files are identical byte-wise upto %d bytes.\n",n_bytes);
	}		
}


int size_of_file(FILE *fp)
{
	if(fp==NULL)
	{
		return 0;
	}
	fseek(fp , 0L , SEEK_END);
	int size = ftell(fp);
	fseek(fp , 0L , SEEK_SET);
	return size;
}

int num_grab(char *str)
{
	if (*str == '\0')
	{
		return -1;
	}
	long res = 0;
	long i = 0;

	if (str[0] == '-')
	{
		return -1;
	}
	
	for (; str[i] != '\0'; ++i)
	{
		if (is_num_check(str[i]) == false)
		{
			return -1;
		}
		res = res * 10 + str[i] - '0';
	}
	return res;
}

bool is_num_check(char ch)
{
	return (ch>='0' && ch<='9')?true:false;
}




