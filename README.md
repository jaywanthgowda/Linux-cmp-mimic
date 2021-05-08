	#13. Program to mimic cmp command.
	The program here mimics cmp command and its flags.
	-b:Displays Differing byte.
	-n:Limits the bytecount for cmp command as per user's choice.
	It is also able to skip bytes as per user choice.
	The program compares byte by byte(or character) from two valid files.
	It redirects to functions specified in server.c which performs just as cmp command would and give relevant output.
	
	The 3 files used are:
	1.) client.c: Used only to redirect to modules based on command line arguments and provide interface to usage of cmp via this program.
	2.) interface.h: Used to link the functions common to both client.c and server.c files.
	3.) server.c:Contains the main backend bit of working of cmp command(with flags).
	
	Syntax to be followed:
		output cmp file_1.ext file_2.ext [FLAGS] [SKIP1] [SKIP2]
	
	NOTE:
	1.)Since command line arguments are used,please do not execute the file directly.
	2.)Please specify the arguments with proper spaces and proper names.
	3.)The arguments are to be case-sensitive as the filenames may change.
	4.)The flags should use hyphens(eg. it's only 'b' and not '-b').
	5.)Skip value of file2 can be omitted for skipping bytes only from file1 but has to accompany skip value of file1 to skip byes from file2.(just as vanilla cmp command)
	6.)The order of the flags is irrelevant but please make sure the LIMIT_bytes regarding -n flag is immediately after it.
	
	BUGS:
		All errors encountered by me have been addressed.
	
	LIMITATIONS:
		-Can compare only 2 files at a time(just like vanilla cmp command)
		
	Thank You,
	Jaywanth J
	PES2UG19CS165
	Section F
	PES University 
