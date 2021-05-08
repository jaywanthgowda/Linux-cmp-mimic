//Program to mimic cmp command

#include<stdio.h>
#include<stdlib.h>
#include "interface.h"
int main(int argc, char **argv)
{	
	if(argc < 1)
	{
		//Condition where no parameters have been passed
		exit(EXIT_FAILURE);
	}
	else if(argc == 1)
	{
		//Greeting condition and to redirect user to working of Program
		initial_display_module();
	}
	else
	{
		//This redirects to the command functioning module where the backend comes into play and the errors are addressed.
		initialise_program(argc,argv);
	}
	return 0;
}
