/* ======================================================== */
/*   Parser.h		        								*/
/* ======================================================== */
#ifndef PARSER_H
#define PARSER_H

//---------------------------------------------------------------------------
//----------------------------- Includes ------------------------------------
//---------------------------------------------------------------------------
#include "definitions.h"
#include "polygon_filter.h"

//---------------------------------------------------------------------------
//----------------------------- Parser Related Defines ----------------------
//---------------------------------------------------------------------------
#define CORD_BIT_MASK	0xFF	//coordinates parsing mask (groups og 8 bits)
#define SHIFT_FACTOR	16		//shift of the data between each two vetcies

//---------------------------------------------------------------------------
//---------------------- Parser Typedefs and Enumerations -------------------
//---------------------------------------------------------------------------
typedef enum { HEXAGON = 6, HEPTAGON = 7, OCTAGON = 8 } EPolygonType;
typedef enum { CURRENT=0, ALL_HEXAGONS=6, ALL_HEPTAGONS=7, ALL_OCTAGONS=8, ALL_PolygonS=15} ETargetOfCommand;

typedef struct {
	EBoolType execute_print_poly;
	EBoolType execute_print_perim;
	EBoolType execute_print_area;
	EBoolType execute_print_diag;
} ParsedUserOutputRequest;

typedef struct {
    EBoolType end_execution;
    EBoolType new_Polygon_insertion;
	EPolygonType type;
	ParsedUserOutputRequest output;
	ETargetOfCommand Polygon_target_subgroup;
}ParsedUserCommand;

//---------------------------------------------------------------------------
//---------------------- Public Methods Prototypes---------------------------
//---------------------------------------------------------------------------
EExecutionStatus 
parse_user_command(ParsedUserCommand* Parsed_Command, ULL_INPUT_TYPE input);

void 
initialize__user_command(ParsedUserCommand *u_psd_cmd);

void 
parse_and_divide_input(FILE** i_proc_ptrs,
					   ParsedUserCommand i_prsd_u_cmd, 
	                   ULL_INPUT_TYPE i_input_cmd,
					   ULL_INPUT_TYPE *i_user_input_cords);

#endif // PARSER_H