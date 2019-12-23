/* ======================================================== */
/*   Parser.c		        								*/
/* ======================================================== */

//---------------------------------------------------------------------------
//----------------------------- Includes ------------------------------------
//---------------------------------------------------------------------------
#include <stdio.h>
#include "../include/parser.h"
#include "../include/definitions.h"

//---------------------------------------------------------------------------
//---------------------- Private Methods Prototypes -------------------------
//---------------------------------------------------------------------------
BYTE 
extract_input(ULL_INPUT_TYPE input, BYTE start_bit, BYTE last_Bit);

//---------------------------------------------------------------------------
//-----------------------Private Methods Implementations---------------------
//---------------------------------------------------------------------------

/***************************************************************************\
description:
Used for extrEAction of data stored from start to last bits of the input.

parameters:
input - the input from which the data should be extracted
start_bit - the first bit of the desired data
last_bit - the last bit of the desired data

return:
The extracted data masked to unsigned char(8 bits), represented as BYTE
****************************************************************************/
PRIVATE
BYTE
extract_input(ULL_INPUT_TYPE input, BYTE start_bit, BYTE last_Bit)
{
	ULL_INPUT_TYPE temp_bit_result = 
		input & MASK_WITH_RANGE_BITS_SET(ULL_INPUT_TYPE, 
										 start_bit, 
										 last_Bit);

	return (BYTE)(temp_bit_result >> start_bit);
}

//---------------------------------------------------------------------------
//---------------------- Public Methods Implementations----------------------
//---------------------------------------------------------------------------

/***************************************************************************\
description:
Used for parsing the command out of the input, which is made in Hex format.

parameters:
Parsed_Command - a structure used to store the parsed command
input - the raw input command

return:
success(0) \ failure(!=0)
****************************************************************************/
PUBLIC EExecutionStatus parse_user_command(ParsedUserCommand* Parsed_Command,
										  ULL_INPUT_TYPE input)
{
	Parsed_Command->end_execution = extract_input(input, 0, 0);
	Parsed_Command->new_Polygon_insertion = extract_input(input, 1, 1);
	Parsed_Command->type = extract_input(input, 2, 5);
	Parsed_Command->output.execute_print_poly = extract_input(input, 6, 6);
	Parsed_Command->output.execute_print_perim = extract_input(input, 7, 7);
	Parsed_Command->output.execute_print_area = extract_input(input, 8, 8);
	Parsed_Command->output.execute_print_diag = extract_input(input, 9, 9);
	Parsed_Command->Polygon_target_subgroup = extract_input(input, 10, 13);
	
	return SUCCESS;
}

/***************************************************************************\
description:
Used for initialization of the structure holding the parsed command.

parameters:
*u_psd_cmd - the structure holding the parsed command.

return:
Void (No-return value).
****************************************************************************/
PUBLIC void initialize__user_command(ParsedUserCommand *u_psd_cmd)
{
	u_psd_cmd->end_execution = FALSE;
	u_psd_cmd->new_Polygon_insertion = FALSE;
	u_psd_cmd->type = NONE;
	u_psd_cmd->output.execute_print_poly = FALSE;
	u_psd_cmd->output.execute_print_perim = FALSE;
	u_psd_cmd->output.execute_print_area = FALSE;
	u_psd_cmd->output.execute_print_diag = FALSE;
	u_psd_cmd->Polygon_target_subgroup = NONE;
}

PUBLIC 
void
parse_and_divide_input(FILE** i_proc_ptrs,
	ParsedUserCommand i_prsd_u_cmd,
	ULL_INPUT_TYPE i_input_cmd,
	ULL_INPUT_TYPE *i_user_input_cords)
{
	int poly_type_to_print = i_prsd_u_cmd.Polygon_target_subgroup;

	//In case there is no input
	if (!i_prsd_u_cmd.new_Polygon_insertion)
	{	
		switch (poly_type_to_print)
		{
			//In case of self print(0000) with no input - nothing to do.
			case (CURRENT):
				break;
			case (ALL_HEXAGONS):
			case (ALL_HEPTAGONS):
			case (ALL_OCTAGONS):
				dprintf(fileno(i_proc_ptrs[poly_type_to_print - SMALLEST_POLYGON]),
						"%llx\n", 
						i_input_cmd);
				break;
			//ALL_PolygonS
			default:
				dprintf(fileno(i_proc_ptrs[HEXA]),"%llx\n", i_input_cmd);
				dprintf(fileno(i_proc_ptrs[HEPTA]),"%llx\n", i_input_cmd);
				dprintf(fileno(i_proc_ptrs[OCTA]),"%llx\n", i_input_cmd);
				break;
		}
	}
	//In case there is input
	else
	{
		switch (poly_type_to_print)
		{
			case (CURRENT):
				dprintf(fileno(i_proc_ptrs[i_prsd_u_cmd.type - SMALLEST_POLYGON]),
						"%llx\n", 
						i_input_cmd);
				break;

			case (ALL_HEXAGONS):
				dprintf(fileno(i_proc_ptrs[HEXA]), "%llx\n", i_input_cmd);
				if (i_prsd_u_cmd.type == HEPTAGON || i_prsd_u_cmd.type == OCTAGON)
				{
					dprintf(fileno(i_proc_ptrs[i_prsd_u_cmd.type - SMALLEST_POLYGON]),
							"%llx\n",
							i_input_cmd);
				}
				break;
				
			case (ALL_HEPTAGONS):
				dprintf(fileno(i_proc_ptrs[HEPTA]), "%llx\n", i_input_cmd);
				if (i_prsd_u_cmd.type == HEXAGON || i_prsd_u_cmd.type == OCTAGON)
				{
					dprintf(fileno(i_proc_ptrs[i_prsd_u_cmd.type - SMALLEST_POLYGON]),
				    		"%llx\n", 
							i_input_cmd);
				}
				break;

			case (ALL_OCTAGONS):
				dprintf(fileno(i_proc_ptrs[OCTA]), "%llx\n", i_input_cmd);
				if (i_prsd_u_cmd.type == HEXAGON || i_prsd_u_cmd.type == HEPTAGON)
				{
					dprintf(fileno(i_proc_ptrs[i_prsd_u_cmd.type - SMALLEST_POLYGON]),
							"%llx\n", 
							i_input_cmd);
				}
				break;

				//ALL_PolygonS
			default:
				dprintf(fileno(i_proc_ptrs[HEXA]), "%llx\n", i_input_cmd);
				dprintf(fileno(i_proc_ptrs[HEPTA]), "%llx\n", i_input_cmd);
				dprintf(fileno(i_proc_ptrs[OCTA]), "%llx\n", i_input_cmd);
				break;
		}
		
		//If there was input, the next to do (in either case) is to store the cords
		dprintf(fileno(i_proc_ptrs[i_prsd_u_cmd.type - SMALLEST_POLYGON]),
				"%llx\n",
				i_user_input_cords[0]);
		dprintf(fileno(i_proc_ptrs[i_prsd_u_cmd.type - SMALLEST_POLYGON]),
				"%llx\n",
				i_user_input_cords[1]);
	}
}