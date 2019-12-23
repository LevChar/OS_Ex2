/* ======================================================== */
/*   polygon_filter.c		        						*/
/* ======================================================== */

//---------------------------------------------------------------------------
//----------------------------- Includes ------------------------------------
//---------------------------------------------------------------------------
#include "../include/polygon_filter.h"
#include "../include/file_handler.h"
#include "../include/parser.h"

//---------------------------------------------------------------------------
//---------------------- Private Methods Prototypes -------------------------
//---------------------------------------------------------------------------
ULL_INPUT_TYPE 
get_64Bit_hexadecimal_input(void);

EExecutionStatus 
get_poly_coordinates(ULL_INPUT_TYPE *i_cords_array);

void 
print_results(int i_pid, int i_status, int *i_children);

//---------------------------------------------------------------------------
//-----------------------Private Methods Implementations---------------------
//---------------------------------------------------------------------------

/***************************************************************************\
description:
Used for getting the input from the console.

parameters: None

return:
returns the input from the console, in 64 bit Hex format representation.
****************************************************************************/
PRIVATE
ULL_INPUT_TYPE 
get_64Bit_hexadecimal_input(void)
{
	ULL_INPUT_TYPE user_input;
	scanf("%llx", &user_input);
	return user_input;
}

/***************************************************************************\
description:
Used for getting the coordinates input of the Polygon from the user.

parameters:
new_poly_to_fill - this structure has field which will hold the raw input.

return:
success(0) \ failure(!=0)
****************************************************************************/
PRIVATE 
EExecutionStatus 
get_poly_coordinates(ULL_INPUT_TYPE *i_cords_array)
{
	i_cords_array[0] = get_64Bit_hexadecimal_input();
	i_cords_array[1] = get_64Bit_hexadecimal_input();

	return SUCCESS;
}

//---------------------------------------------------------------------------
//---------------------- Public Methods Implementations----------------------
//---------------------------------------------------------------------------

/***************************************************************************\
description: the main function of this program, containing the main execution
loop for running till the user decides to stop, getting the input, 
proccessing and story it, and printing whenever requested.

parameters: None

return:
success(0) \ failure(!=0)
****************************************************************************/
PUBLIC 
void 
execute_polygon_filter_program(void)
{
	FILE *proc_ptrs[NUM_OF_FILES], *res_ptrs[NUM_OF_FILES];
	char* proc_files[NUM_OF_FILES] = { HEX_IN, HEPT_IN, OCT_IN };
	char* res_files[NUM_OF_FILES] =  { HEX_OUT, HEPT_OUT, OCT_OUT };
	ULL_INPUT_TYPE user_input_cmd, user_input_cords[2];
	char* argv_to_helper[2] = {HELPER_PROG, NULL };
	int children[NUM_OF_FILES], pid = 0, status;
	ParsedUserCommand u_psd_cmd;
	
	//Opening of temp files for writing the specified input
	for (size_t i = 0; i < NUM_OF_FILES; i++)
	{
		file_loader(proc_files[i], APPEND_PLUS, &proc_ptrs[i]);
	}

	do
	{
		initialize__user_command(&u_psd_cmd);
		user_input_cmd = get_64Bit_hexadecimal_input();
		parse_user_command(&u_psd_cmd, user_input_cmd);

		//If we need to get input coordinates - that's the place we do it.
		if (u_psd_cmd.new_Polygon_insertion)
		{
			get_poly_coordinates(user_input_cords);
		}
		
		//Call to the function which parses the input and devide it to 3
		//different input files, according to the relevant shape.
		parse_and_divide_input(proc_ptrs, 
							   u_psd_cmd,
							   user_input_cmd, 
							   user_input_cords);
	
		if (u_psd_cmd.end_execution)
		{
			break;
		}

	} while (TRUE);

	//Mark last command in each file as end of input point and rewind to the begining of
	//the file, as preparation for helper program.
	for (size_t i = 0; i < NUM_OF_FILES; i++)
	{
		dprintf(fileno(proc_ptrs[i]), END_OF_INPUT);
		lseek(fileno(proc_ptrs[i]), START_OF_FILE, SEEK_SET);
	}

	for (size_t i = 0; i < NUM_OF_FILES; i++)
	{
		//Child Section
		if ((children[i] = fork()) == 0)
		{
			//Redirect input
			dup2(fileno(proc_ptrs[i]), STDIN);
			
			//Redirect output
			file_loader(res_files[i], APPEND_PLUS, &res_ptrs[i]);
			dup2(fileno(res_ptrs[i]), STDOUT);

			execve(argv_to_helper[0], argv_to_helper, NULL);
			fprintf(stderr, "*** ERROR: *** EXEC of %s FAILED\n", argv_to_helper[0]);
			exit(1);
		}
		//Error Section
		if (pid <0)
		{
			perror("Cannot fork()");
			exit(EXIT_FAILURE);
		}
	}

	for (size_t i = 0; i < NUM_OF_FILES; i++)
	{
		int pid = wait(&status);
		print_results(pid, status, children);
	}

	printf("all child processes terminated\n");

	exit(0);
}

PRIVATE void print_results(int i_pid, int i_status, int* i_children)
{
	
	printf("child terminated – created %d", WEXITSTATUS(i_status));

	if (i_pid == i_children[HEXA])
	{
		printf(" hexagons\n");
	}
	else if (i_pid == i_children[HEPTA])
	{
		printf(" heptagons\n");
	}
	else if (i_pid == i_children[OCTA])
	{
		printf(" octatagons\n");
	}
}