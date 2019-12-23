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
void 
validate_shape(EPolygonType type);

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
PRIVATE BYTE extract_input(ULL_INPUT_TYPE input,
						   BYTE start_bit, 
						   BYTE last_Bit)
{
	ULL_INPUT_TYPE temp_bit_result = 
		input & MASK_WITH_RANGE_BITS_SET(ULL_INPUT_TYPE, 
										 start_bit, 
										 last_Bit);

	return (BYTE)(temp_bit_result >> start_bit);
}


/***************************************************************************\
description:
Used for validation that the curent type of Polygon is ligal for the program

parameters:
type - the amount of vertices of the inspected Polygon

return:
Void (No-return value).
****************************************************************************/
PRIVATE void validate_shape(EPolygonType type)
{
	if (type != HEXAGON && type != HEPTAGON && type != OCTAGON)
	{
		printf("Unsupported Polygon type, exiting...!\n");
		exit(1);
	}
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
	
	validate_shape(Parsed_Command->type);

	Parsed_Command->output.execute_print_poly = extract_input(input, 6, 6);
	Parsed_Command->output.execute_print_perim = extract_input(input, 7, 7);
	Parsed_Command->output.execute_print_area = extract_input(input, 8, 8);
	Parsed_Command->output.execute_print_diag = extract_input(input, 9, 9);
	Parsed_Command->Polygon_target_subgroup = extract_input(input, 10, 13);
	
	if (extract_input(input, 6, 9) != NONE)
	{
		Parsed_Command->execute_some_print = TRUE;
	}
	
	return SUCCESS;
}

/***************************************************************************\
description:
Used for parsing the Polygon coordinates oyt of the raw data stored in the 
Polygon structure.

parameters:
parsed_cords - Polygon struct, used for both - input and output, the raw 
data stored at one of the fields of this structure used for the input, and 
the parsed coordinates are stored in some other field of this same structure.

return:
success(0) \ failure(!=0)
****************************************************************************/
PUBLIC EExecutionStatus parse_poly_coordinates(Polygon* parsed_cords)
{
	size_t shift_x, shift_y, i;
	unsigned short temp_exp;
	unsigned char current_row_of_input = FIRST_RAW_INPUT;

	//we are going through the first input, which is 8 bytes long
	//we need one byte for each x and one byte for each y,
	//so total of 4 coordinates in the first input
	for (i = 0 ; i < (unsigned)(parsed_cords->type) ; i++)
	{
		shift_x = (i % AMOUNT_OF_VERTICES_IN_EACH_ROW) * SHIFT_FACTOR;
		shift_y = shift_x + (SHIFT_FACTOR / 2);

		temp_exp = 
			parsed_cords->raw_input_coardinates[current_row_of_input] 
			>> shift_x;

		temp_exp &= CORD_BIT_MASK;
		parsed_cords->vertices[i].x = (signed char)temp_exp;

		temp_exp = 
			parsed_cords->raw_input_coardinates[current_row_of_input] 
			>> shift_y;
		temp_exp &= CORD_BIT_MASK;
		parsed_cords->vertices[i].y = (signed char)temp_exp;

		if (i == (AMOUNT_OF_VERTICES_IN_EACH_ROW - 1))
		{
			current_row_of_input = SECOND_RAW_INPUT;
		}
	}

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
	u_psd_cmd->coardinates_filled = FALSE;
	u_psd_cmd->execute_some_print = FALSE;
}