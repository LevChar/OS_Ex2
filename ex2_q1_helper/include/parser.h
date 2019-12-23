/* ======================================================== */
/*   Parser.h		        								*/
/* ======================================================== */
#ifndef PARSER_H
#define PARSER_H

//---------------------------------------------------------------------------
//----------------------------- Includes ------------------------------------
//---------------------------------------------------------------------------
#include "definitions.h"
#include "polygon_manager.h"

//---------------------------------------------------------------------------
//----------------------------- Parser Related Defines ----------------------
//---------------------------------------------------------------------------
#define CORD_BIT_MASK	0xFF	//coordinates parsing mask (groups og 8 bits)
#define SHIFT_FACTOR	16		//shift of the data between each two vetcies

//---------------------------------------------------------------------------
//---------------------- Parser Typedefs and Enumerations -------------------
//---------------------------------------------------------------------------
typedef enum {ADD_POLY, PRINT_POLY, PRINT_PERIM, PRINT_AREA, PRINT_DIAG} EAction;
typedef enum {CURRENT=0, ALL_HEXAGONS=6, ALL_HEPTAGONS=7, ALL_OCTAGONS=8, ALL_PolygonS=15} ETargetOfCommand;

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
	EBoolType coardinates_filled;
	EBoolType execute_some_print;
}ParsedUserCommand;

//---------------------------------------------------------------------------
//---------------------- Public Methods Prototypes---------------------------
//---------------------------------------------------------------------------
EExecutionStatus 
parse_user_command(ParsedUserCommand* Parsed_Command, ULL_INPUT_TYPE input);

EExecutionStatus 
parse_poly_coordinates(Polygon* parsed_cords);

void 
initialize__user_command(ParsedUserCommand *u_psd_cmd);

#endif // PARSER_H