/* ======================================================== */
/*   file_handler.c		        							*/
/* ======================================================== */

//---------------------------------------------------------------------------
//----------------------------- Includes ------------------------------------
//---------------------------------------------------------------------------
#include "../include/file_handler.h"

//---------------------------------------------------------------------------
//---------------------- Private Methods Prototypes -------------------------
//---------------------------------------------------------------------------
EExecutionStatus
raed_mode_file_loader(char* f_name, FILE **f_ptr);

EExecutionStatus
write_mode_file_loader(char* f_name, FILE **f_ptr);

EExecutionStatus 
append_mode_file_loader(char* f_name, FILE **f_ptr);

EExecutionStatus 
raed_plus_mode_file_loader(char* f_name, FILE **f_ptr);

EExecutionStatus 
write_plus_mode_file_loader(char* f_name, FILE **f_ptr);

EExecutionStatus 
append_plus_mode_file_loader(char* f_name, FILE **f_ptr);

void 
prompt_exit_on_file_error(EFileOpenModes mode_during_error, char* f_name);
									   
//---------------------------------------------------------------------------
//-----------------------Private Methods Implementations---------------------
//---------------------------------------------------------------------------
PRIVATE 
EExecutionStatus 
raed_mode_file_loader(char* f_name, FILE **f_ptr)
{
	return (NULL == (*f_ptr = fopen(f_name, "r"))) ? FAILURE : SUCCESS;
}

PRIVATE 
EExecutionStatus 
write_mode_file_loader(char* f_name, FILE **f_ptr)
{
	return (NULL == (*f_ptr = fopen(f_name, "w"))) ? FAILURE : SUCCESS;
}

PRIVATE 
EExecutionStatus 
append_mode_file_loader(char* f_name, FILE **f_ptr)
{	
	return (NULL == (*f_ptr = fopen(f_name, "a"))) ? FAILURE : SUCCESS;
}

PRIVATE 
EExecutionStatus 
raed_plus_mode_file_loader(char* f_name, FILE **f_ptr)
{
	return (NULL == (*f_ptr = fopen(f_name, "r+"))) ? FAILURE : SUCCESS;
}

PRIVATE 
EExecutionStatus 
write_plus_mode_file_loader(char* f_name, FILE **f_ptr)
{
	return (NULL == (*f_ptr = fopen(f_name, "w+"))) ? FAILURE : SUCCESS;
}

PRIVATE 
EExecutionStatus 
append_plus_mode_file_loader(char* f_name, FILE **f_ptr)
{
	return (NULL == (*f_ptr = fopen(f_name, "a+"))) ? FAILURE : SUCCESS;
}

PRIVATE
void 
prompt_exit_on_file_error(EFileOpenModes mode_during_error, char* f_name)
{
		if (mode_during_error == READ || mode_during_error == READ_PLUS)
		{
			fprintf(stderr, "File: %s Doesn't exist.\n Terminating.\n", f_name);
		}
		else if(mode_during_error == WRITE || mode_during_error == WRITE_PLUS || 
				mode_during_error == APPEND || mode_during_error == APPEND_PLUS)
		{
			fprintf(stderr, 
					"Probelm opening \\ creating File: %s.\n Terminating.\n", 
					f_name);
		}
		else if(mode_during_error == UNKNOWN_ERROR)
		{
			fprintf(stderr, "Unknown Error.\nTerminating.\n");
		}
		
		exit(mode_during_error);
}

//---------------------------------------------------------------------------
//---------------------- Public Methods Implementations----------------------
//---------------------------------------------------------------------------
PUBLIC 
void 
file_loader(char *f_name, EFileOpenModes o_mode, FILE **file_to_load)
{
	EExecutionStatus status;
	
	switch (o_mode)
	{
		case READ: 	      status = raed_mode_file_loader(f_name, file_to_load);
			break;
			
		case WRITE:       status = write_mode_file_loader(f_name, file_to_load);
			break;
			
		case APPEND:      status = append_mode_file_loader(f_name, file_to_load);
			break;
			
		case READ_PLUS:   status = raed_plus_mode_file_loader(f_name, file_to_load);
			break;
			
		case WRITE_PLUS:  status = write_plus_mode_file_loader(f_name, file_to_load);
			break;
			
		case APPEND_PLUS: status = append_plus_mode_file_loader(f_name, file_to_load);
			break;
			
		default:
			o_mode = UNKNOWN_ERROR;
			status = FAILURE;
			break;
	}
	
	(status == FAILURE ? prompt_exit_on_file_error(o_mode, f_name) : FALSE);
}