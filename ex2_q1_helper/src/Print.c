/* ======================================================== */
/*   Print.c				        						*/
/* ======================================================== */

//---------------------------------------------------------------------------
//----------------------------- Includes ------------------------------------
//---------------------------------------------------------------------------
#include <stdio.h>
#include <math.h>
#include "../include/definitions.h"
#include "../include/polygon_manager.h"
#include "../include/print.h"
#include "../include/parser.h"

//---------------------------------------------------------------------------
//---------------------- Private Methods Prototypes -------------------------
//---------------------------------------------------------------------------
double 
perimeter_calculation_utility(Polygon* poly_to_calc);

double
diagonals_calculation_utility(Polygon* poly_to_calc);

double
area_calculation_utility(Polygon* poly_to_calc);

//---------------------------------------------------------------------------
//-----------------------Private Methods Implementations---------------------
//---------------------------------------------------------------------------

/***************************************************************************\
description:
Used for calculating given Polygon's perimeter.

parameters:
*poly_to_calc - Pointer to the Polygon that this calculation is executing on.

return:
Void (No-return value).
****************************************************************************/
PRIVATE double perimeter_calculation_utility(Polygon* poly_to_calc)
{
	size_t i;
	poly_to_calc->perimeter = 0;
	double delta_x = 0.0;
	double delta_y = 0.0;

	for (i = 0; i < (unsigned)(poly_to_calc->type) ; i++)
	{

		delta_y = poly_to_calc->vertices[(i + 1) % poly_to_calc->type].y
			- poly_to_calc->vertices[i].y;

		delta_x = poly_to_calc->vertices[(i + 1) % poly_to_calc->type].x
			- poly_to_calc->vertices[i].x;

		poly_to_calc->perimeter += sqrt(pow(delta_x, 2) + pow(delta_y, 2));
	}

	return poly_to_calc->perimeter;
}

/***************************************************************************\
description:
Used for calculating given Polygon's total diagonal length.

parameters:
*poly_to_calc - Pointer to the Polygon that this calculation is executing on.

return:
Void (No-return value).
****************************************************************************/
PRIVATE double diagonals_calculation_utility(Polygon* poly_to_calc)
{
	poly_to_calc->total_diagonal_length = 0;
	EBoolType first_round = TRUE;
	double delta_x, delta_y;
	double result_diagonals = 0.0;
	size_t vertices_amount = poly_to_calc->type;
	size_t last_vertex = vertices_amount - 1;	//vertices index start at '0'

	//2 neighbours can't be connected, 
	//so no point checking one before last vertex 
	size_t last_vertex_for_diagonal = last_vertex - 2;

	for (size_t i = 0; i <= last_vertex_for_diagonal; i++)
	{
		for (size_t j = i + 2; j <= last_vertex; j++)
		{
			//Test to eliminate the case where 
			//i=0 and j=last vertex - shouldn't be connected - I
			if (j != last_vertex || ((j == last_vertex) && !first_round))
			{
				delta_y = 
					poly_to_calc->vertices[j].y-poly_to_calc->vertices[i].y;
				delta_x = 
					poly_to_calc->vertices[j].x-poly_to_calc->vertices[i].x;
				result_diagonals += sqrt(pow(delta_x, 2) + pow(delta_y, 2));
			}

			//Test to eliminate the case where i=0 and j=last vertex
			//- shouldn't be connected - II
			first_round = 
				first_round ? ((j == last_vertex) ? FALSE : TRUE) : FALSE;
		}
	}

	poly_to_calc->total_diagonal_length = result_diagonals;
	return poly_to_calc->total_diagonal_length;
}

/***************************************************************************\
description:
Used for calculating given Polygon's area.

parameters:
*poly_to_calc - Pointer to the Polygon that this calculation is executing on.

return:
Void (No-return value).
****************************************************************************/
PRIVATE double area_calculation_utility(Polygon* poly_to_calc)
{
	poly_to_calc->area = 0.0;
	double result_area = 0.0;
	size_t i;

	for (i = 0; i < (unsigned)(poly_to_calc->type - 1) ; i++)
	{
		result_area += 
			poly_to_calc->vertices[i].x * poly_to_calc->vertices[i + 1].y
			- 
			poly_to_calc->vertices[i + 1].x * poly_to_calc->vertices[i].y;
	}

	result_area += 
		poly_to_calc->vertices[i].x * poly_to_calc->vertices[FIRST_VERTEX].y
		-
		poly_to_calc->vertices[FIRST_VERTEX].x * poly_to_calc->vertices[i].y;

	poly_to_calc->area = sqrt(pow((result_area / 2.0), 2));
	return poly_to_calc->area;
}

//---------------------------------------------------------------------------
//---------------------- Public Methods Implementations----------------------
//---------------------------------------------------------------------------

/***************************************************************************\
description:
Used for printing given Polygon's type and vertices list.

parameters:
*poly_to_print - Pointer to the Polygon that is supposed to be printed.

return:
Void (No-return value).
****************************************************************************/
PUBLIC void print_polygon(Polygon* poly_to_print)
{
	const char* poly_types[] = { "hexagon", "heptagon", "octagon" };

	if (!poly_to_print->vertices_data_parsed)
	{
		parse_poly_coordinates(poly_to_print);
	}

	printf("%s ", poly_types[poly_to_print->type % SMALLEST_Polygon]);

	for (size_t i = 0; i < (unsigned)(poly_to_print->type) ; i++)
	{
		printf("{%d, %d} ", 
			   poly_to_print->vertices[i].x, 
			   poly_to_print->vertices[i].y);
	}

	printf("\n");
}

/***************************************************************************\
description:
Used for printing given Polygon's perimeter.

parameters:
*poly_to_print - Pointer to the Polygon that is supposed to be printed.

return:
Void (No-return value).
****************************************************************************/
PUBLIC void print_perimeter(Polygon* poly_to_print)
{
	double poly_perimeter = poly_to_print->perimeter != -1.0 ?
		poly_to_print->perimeter :
		perimeter_calculation_utility(poly_to_print);

	printf("perimeter = %.1f\n", poly_perimeter);
}

/***************************************************************************\
description:
Used for printing given Polygon's area.

parameters:
*poly_to_print - Pointer to the Polygon that is supposed to be printed.

return:
Void (No-return value).
****************************************************************************/
PUBLIC void print_area(Polygon* poly_to_print)
{
	double poly_area = poly_to_print->area != -1.0 ?
		poly_to_print->area :
		area_calculation_utility(poly_to_print);

	printf("area = %.1f\n", poly_area);
}

/***************************************************************************\
description:
Used for printing given Polygon's total diagonals length.

parameters:
*poly_to_print - Pointer to the Polygon that is supposed to be printed.

return:
Void (No-return value).
****************************************************************************/
PUBLIC void print_diagonals(Polygon* poly_to_print)
{
	double poly_diagonals_length = 
		poly_to_print->total_diagonal_length != -1.0 ?
		poly_to_print->total_diagonal_length :
		diagonals_calculation_utility(poly_to_print);

	printf("diagonals = %.1f\n", poly_diagonals_length);
}