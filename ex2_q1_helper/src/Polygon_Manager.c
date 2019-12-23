/* ======================================================== */
/*   Polygon_Manager.c		        						*/
/* ======================================================== */

//---------------------------------------------------------------------------
//----------------------------- Includes ------------------------------------
//---------------------------------------------------------------------------
#include <stdio.h>
#include "../include/linked_list_manager.h"
#include "../include/polygon_manager.h"
#include "../include/parser.h"
#include "../include/print.h"

//----------------------------------------------------------------------------
//-------------------------- Global Variables---------------------------------
//----------------------------------------------------------------------------
Singly_Linked_List g_Polygon_list;
pt2Function g_poly_functions[] = { add_polygon, 
								   print_polygon, 
								   print_perimeter,
								   print_area,
								   print_diagonals };

//---------------------------------------------------------------------------
//---------------------- Private Methods Prototypes -------------------------
//---------------------------------------------------------------------------
EExecutionStatus 
get_and_add_new_polygon(ParsedUserCommand initial_poly_detailes);

void 
main_print_manager(ParsedUserCommand print_plan);

void 
filtered_print_curr_poly(ParsedUserOutputRequest print_plan, 
					     Polygon* poly_to_print);
	 
void 
filtered_print_poly_series(ParsedUserOutputRequest print_cmd, 
						   ETargetOfCommand sub_group);
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
PRIVATE ULL_INPUT_TYPE get_64Bit_hexadecimal_input(void)
{
	ULL_INPUT_TYPE user_input;
	scanf("%llx", &user_input);
	return user_input;
}

/***************************************************************************\
description:
Used for getting the input from the console.

parameters: 
initial_poly_detailes - stores the current parsed command of the user,
we use it here to check which type of Polygon is desired.

return:
success(0) \ failure(!=0)
****************************************************************************/
PRIVATE EExecutionStatus 
get_and_add_new_polygon(ParsedUserCommand initial_poly_detailes)
{
	Polygon *new_poly = allocate_polygon(initial_poly_detailes.type);
	initial_poly_detailes.coardinates_filled = 
		get_poly_coordinates(new_poly) ^ TRUE;
	g_poly_functions[ADD_POLY](new_poly);

	return SUCCESS;
}

/***************************************************************************\
description:
Used for getting the coordinates input of the Polygon from the user.

parameters:
new_poly_to_fill - this structure has field which will hold the raw input.

return:
success(0) \ failure(!=0)
****************************************************************************/
PRIVATE EExecutionStatus get_poly_coordinates(Polygon* new_poly_to_fill)
{
	new_poly_to_fill->raw_input_coardinates[0] = 
		get_64Bit_hexadecimal_input();
	new_poly_to_fill->raw_input_coardinates[1] = 
		get_64Bit_hexadecimal_input();

	return SUCCESS;
}

/***************************************************************************\
description:
Used for adding new Polygon to the list of Polygons (Wrapper function).

parameters:
new_poly_to_add - this is the new Polygon to add.

return:
Void (No-return value).
****************************************************************************/
PRIVATE void add_polygon(Polygon* new_Polygon_to_add)
{
	append_To_List(&g_Polygon_list, new_Polygon_to_add);
}

/***************************************************************************\
description:
Used for allocation and initialization of new Polygon.

parameters:
Polygon - the type of desired Polygon.

return:
Returns newly dynamically allocated Polygon.
****************************************************************************/
PRIVATE Polygon* allocate_polygon(EPolygonType Polygon_type)
{
	Polygon* new_Polygon = NULL;

	new_Polygon = (Polygon*)malloc(sizeof(Polygon));
	new_Polygon->vertices = (Point*)malloc(Polygon_type * sizeof(Point));
	new_Polygon->raw_input_coardinates = 
			(ULL_INPUT_TYPE*)malloc(NUM_INPT_ROWS * sizeof(ULL_INPUT_TYPE));
	new_Polygon->type = Polygon_type;
	new_Polygon->area = -1.0;
	new_Polygon->perimeter = -1.0;
	new_Polygon->total_diagonal_length = -1.0;
	new_Polygon->vertices_data_parsed = FALSE;

	return new_Polygon;
}

/***************************************************************************\
description: Used for de-allocation of desired Polygon.

parameters:
data - pointer to the Polygon that needed to be dealocated.

return:
Void (No-return value).
****************************************************************************/
PRIVATE void free_polygon(pVoid data)
{
	free(((Polygon*)(data))->vertices);
	free(((Polygon*)(data))->raw_input_coardinates);
}

/***************************************************************************\
description: The general print function.

parameters:
print_plan - Parsed user command, containing information about the desired 
way of printing.

return:
Void (No-return value).
****************************************************************************/
PRIVATE void main_print_manager(ParsedUserCommand print_plan)
{
	if (print_plan.Polygon_target_subgroup == CURRENT)
	{
		filtered_print_curr_poly(print_plan.output, 
								 (Polygon*)(g_Polygon_list.tail->data));
	}
	else
	{
		filtered_print_poly_series(print_plan.output, 
								   print_plan.Polygon_target_subgroup);
	}
}

/***************************************************************************\
description: function for print analyzing and deciding, for one 
given Polygon.

parameters:
print_command - Part of the parsed user command, the data that tells which
kind of print to perform.
poly_to_print - pointer to the current polynom that is being proccessed.

return:
Void (No-return value).
****************************************************************************/
PRIVATE void filtered_print_curr_poly(ParsedUserOutputRequest print_command,
									  Polygon* poly_to_print)
{
	if (!poly_to_print->vertices_data_parsed)
	{
		parse_poly_coordinates(poly_to_print);
	}

	if (print_command.execute_print_poly)
	{
		g_poly_functions[PRINT_POLY](poly_to_print);
	}

	if (print_command.execute_print_perim)
	{
		g_poly_functions[PRINT_PERIM](poly_to_print);
	}

	if (print_command.execute_print_area)
	{
		g_poly_functions[PRINT_AREA](poly_to_print);
	}

	if (print_command.execute_print_diag)
	{
		g_poly_functions[PRINT_DIAG](poly_to_print);
	}
}

/***************************************************************************\
description: function for printing analyzing and deciding, for series
of Polygon which meets the sub_group criteria.

parameters:
print_command - Part of the parsed user command, the data that tells which
kind of print to perform.
sub_group - holding the type\s of Polygon's needed for print.

return:
Void (No-return value).
****************************************************************************/
PRIVATE void filtered_print_poly_series(ParsedUserOutputRequest print_cmd,
									    ETargetOfCommand sub_group)
{
	Singly_Linked_Node* curr_proccessed_node = g_Polygon_list.head;
	Polygon* current_poly;

	while (curr_proccessed_node)
	{
		current_poly = (Polygon*)(curr_proccessed_node->data);
		if ((current_poly->type == (EPolygonType)sub_group) || 
			(sub_group == ALL_PolygonS))
		{
			filtered_print_curr_poly(print_cmd, current_poly);
		}

		curr_proccessed_node = curr_proccessed_node->next;
	}
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
PUBLIC void execute_polygon_program(void)
{
	int counter = 0;
	ParsedUserCommand u_psd_cmd;
	ULL_INPUT_TYPE user_input;

	initialize_Empty_List(&g_Polygon_list, sizeof(Polygon), free_polygon);

	do
	{
		initialize__user_command(&u_psd_cmd);
		user_input = get_64Bit_hexadecimal_input();
		parse_user_command(&u_psd_cmd, user_input);

		if (u_psd_cmd.new_Polygon_insertion)
		{
			get_and_add_new_polygon(u_psd_cmd);
		}

		if (u_psd_cmd.execute_some_print)
		{
			main_print_manager(u_psd_cmd);
		}

		if (u_psd_cmd.end_execution)
		{
			break;
		}

		counter++;
		
	} while (TRUE);

	destroy_List(&g_Polygon_list);

	exit(counter);
}