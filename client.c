//Program to mimic cmp command

#include<stdio.h>
#include<stdlib.h>
#include "interface.h"
int main(int argc, char **argv)
{	
	if(argc < 1)
	{
		exit(EXIT_FAILURE);
	}
	else
	{
		initialise_program(argc,argv);
	}
	return 0;
}
