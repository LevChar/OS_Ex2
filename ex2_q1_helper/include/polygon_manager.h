/* ======================================================== */
/*   Polygon_Manager.h		        						*/
/* ======================================================== */
#ifndef Polygon_MANAGER_H
#define Polygon_MANAGER_H

//---------------------------------------------------------------------------
//----------------------------- Includes ------------------------------------
//---------------------------------------------------------------------------
#include <stdlib.h>
#include "definitions.h"

//---------------------------------------------------------------------------
//---------------- Polygon Manager Typedefs and Enumerations ----------------
//---------------------------------------------------------------------------
typedef enum { HEXAGON = 6, HEPTAGON = 7, OCTAGON = 8 } EPolygonType;

typedef struct _Point {
	signed char x;
	signed char y;
} Point;

typedef struct _Polygon {
	EPolygonType type;
	Point *vertices;
	ULL_INPUT_TYPE *raw_input_coardinates;
	EBoolType vertices_data_parsed;
	double perimeter;
	double area;
	double total_diagonal_length;
} Polygon;

typedef void(*pt2Function) (Polygon*);

//---------------------------------------------------------------------------
//---------------------- Public Methods Prototypes---------------------------
//---------------------------------------------------------------------------
void
execute_polygon_program(void);

ULL_INPUT_TYPE 
get_64Bit_hexadecimal_input(void);

Polygon* 
allocate_polygon(EPolygonType Polygon_type);

void 
free_polygon(pVoid data);

EExecutionStatus 
get_poly_coordinates(Polygon* new_poly_to_fill);

void 
add_polygon(Polygon*);

#endif // Polygon_MANAGER_H