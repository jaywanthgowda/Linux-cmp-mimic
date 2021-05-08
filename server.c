#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include "interface.h"

//Function Declaration module
//Validation for file pointer
void file_handling_check(int ,char **);

//cmp modules
void cmp_usage(FILE *,FILE *,int,int,char **,int,int,int);

//cmp sub-modules
void cmp_base(FILE *,FILE *,int,int,char **);
void cmp_b(FILE *,FILE *,int,int,char **);
void cmp_n(FILE *,FILE *,int,int,int,char **);

//Other functions
int size_of_file(FILE *);
int num_grab(char *);
bool is_num_check(char);

//This is used to greet the user regarding the functioning of the program
void initial_display_module()
{
	printf("\n Welcome to my Program\n");
	printf(" This program replicates the functioning of cmp command.\n");
	printf(" The functioning of the program requires command line parameters just as you would to invoke cmp command on linux.\n");
	printf(" An executable called output shall be created after using make.\n");
	printf(" This executable should be used with cmp in a particular format as shown.\n");
	printf(" Please use the following format\n");
	printf("\toutput cmp file_1.ext file_2.ext [FLAGS] [SKIP1] [SKIP2]\n");
	printf(" Flags supported are:\n");
	printf(" (1.) -b flag : To display differing byte at the differentiating byte position.\n");
	printf(" (2.) -n flag : To limit the number of bytes of the cmp command.To be used with an integer denoting LIMIT_bytes(also as a command-line parameter\n\n");
}

//This is the start of the program recognizing the command line arguments
void initialise_program(int argc,char **argv)
{	
	//Initial verification if command corresponding to cmp has been entered
	if(strcmp(argv[1],"cmp")==0)
	{
		if(argc>9)
		{
			//Arguments are more than the max criteria for cmp
			printf("Invalid number of arguments.\n");
		}
		else if(argc == 2)
		{
			//If only cmp was entered
			printf("Missing operands after 'cmp'.\n");
		}
		else if(argc == 3)
		{
			//If only one file following cmp has been entered
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

//This Deals with the initialisation of the file pointers and redirects based on specific command line arguments
void file_handling_check(int argc,char **argv)
{
	//FILE Initialisation and access
	FILE *f1,*f2;
	f1=fopen(argv[2],"r+");
	f2=fopen(argv[3],"r+");
	
	//Initial values -1 correspond to default conditions of cmp
	int skip1=-1;
	int skip2=-1;
	int n_bytes=-1;
	
	//If fopen() fails or file does not exist
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
	//If files have been successfully opened
	else
	{
		//Corresponds to 4 arguments and cmp file1.ext file2.ext
		if(argc == 4)
		{
			//Base cmp condition with no skip or flags
			cmp_usage(f1,f2,0,argc,argv,0,0,0);
		}
		
		else if(argc == 5)
		{
			/*
				Corresponds to the following valid conditions
				cmp file1.ext file2.ext -b
				cmp file1.ext file2.ext skip1
			*/
				
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
			/*
				Corresponds to the following valid conditions
				cmp file1.ext file2.ext -b skip1
				cmp file1.ext file2.ext -n n_bytes
				cmp file1.ext file2.ext skip1 skip2
			*/
			
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
			/*
				Corresponds to the following valid conditions
				cmp file1.ext file2.ext -b skip1 skip2
				cmp file1.ext file2.ext -n n_bytes skip1
				cmp file1.ext file2.ext -b -n n_bytes
 				cmp file1.ext file2.ext -n n_bytes -b
			*/
			
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
			/*
				Corresponds to the following valid conditions			
				cmp file1.ext file2.ext -n n_bytes skip1 skip2
				cmp file1.ext file2.ext -b -n n_bytes skip1
				cmp file1.ext file2.ext -n n_bytes -b skip1
			*/
			
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
			/*
				Corresponds to the following valid conditions
				cmp file1.ext file2.ext -b -n n_bytes skip1 skip2
				cmp file1.ext file2.ext -n n_bytes -b skip1 skip2
			*/
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


	
/*This function redirects cmp based on n parameter leading to corresponding conditions as shown below
	0 base cmp with skip1 and skip 2
	1 -b cmp with skip1 and skip 2
	2 -n cmp with skip1 and skip 2*/
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

//Function to mimic cmp without flags
void cmp_base(FILE *f1,FILE *f2,int skip1_bytes,int skip2_bytes,char **argv)
{
	char ch_from_file1,ch_from_file2;//To store characters simulataneuosly from both files
	int byte_count=0;//To store bytes
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
		
		//To check if EOF has occured
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
		
		//To check if bytes are different
		if((ch_from_file1!=ch_from_file2)&&flag)
		{
			printf("%s %s differ: byte %d, line %d\n",argv[2],argv[3],byte_count,line_count);
			diff_count++;
			flag=0;
		}
		
		//To check if a new line character has been found.
		if((ch_from_file1=='\n')&&flag)
		{
			line_count++;
		}
	}while(flag);
	
	//Default display to show in case files are identical.
	if(diff_count==0)
	{
		printf("Files are identical byte-wise.\n");
	}		
}

//Function to mimic cmp with -b flag
void cmp_b(FILE *f1,FILE *f2,int skip1_bytes,int skip2_bytes,char **argv)
{
	char ch_from_file1,ch_from_file2;//To store characters simulataneuosly from both files
	int byte_count=0;//To store bytes
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
		
		//To check if EOF has occured
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
		
		//To check if bytes are different
		if((ch_from_file1!=ch_from_file2)&&flag)
		{
			//Display differs as the differing characters are displayed.
			printf("%s %s differ: byte %d, line %d.\n%x in %s and %x in %s",argv[2],argv[3],byte_count,line_count,ch_from_file1,argv[2],ch_from_file2,argv[3]);
			diff_count++;
			flag=0;
		}
		//To check if a new line character has been found.
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

//Function to mimic cmp with -n flag
void cmp_n(FILE *f1,FILE *f2,int skip1_bytes,int skip2_bytes,int n_bytes,char **argv)
{
	char ch_from_file1,ch_from_file2;//To store characters simulataneuosly from both files
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
		//To check if EOF has occured
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
		
		//To check if bytes are different
		if((ch_from_file1!=ch_from_file2)&&flag)
		{
			printf("%s %s differ: byte %d, line %d\n",argv[2],argv[3],byte_count,line_count);
			diff_count++;
			flag=0;
		}
		//To check if a new line character has been found.
		if((ch_from_file1=='\n')&&flag)
		{
			line_count++;
		}
	}while(flag && byte_count<n_bytes);
	//While condition differs and stops when byte_count reaches n_bytes
	if(diff_count==0)
	{
		printf("Files are identical byte-wise upto %d bytes.\n",n_bytes);
	}		
}

//To find the number of bytes of a file
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

//To convert the command-line argument to the corresponding integer
int num_grab(char *str)
{
	if (*str == '\0')
	{
		return -1;
	}
	long res = 0;
	long counter = 0;

	if (str[0] == '-')
	{
		return -1;
	}
	
	for (; str[counter] != '\0'; ++counter)
	{
		if (is_num_check(str[counter]) == false)
		{
			return -1;
		}
		res = res * 10 + str[counter] - '0';
	}
	return res;
}

//To check if the character is specifically a number
bool is_num_check(char ch)
{
	return (ch>='0' && ch<='9')?true:false;
}
