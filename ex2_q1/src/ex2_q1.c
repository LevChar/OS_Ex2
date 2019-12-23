/* ======================================================== */
/*   ex2_q1.c	        								    */
/* ======================================================== */
/*   XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX */
/*   Exercise: 02										    */
/*   Question: 01										    */
/*   Lecturer: Tzvi Melamed								    */
/* ======================================================== */
/* Purpose: This Program was written as part of second 		*/
/* assgnment in OS course. This is a wrapper program of the */
/* first program that was written in first assignment. It   */
/* still receives 64 bit encoded input data from user.      */
/* data which represents a command and an input 		    */
/* of Polygon coordinates, the supported commands include	*/
/* adding new Polygon to the Polygon database, and couple 	*/
/* of prnting operations, with different filters.			*/
/* But, the main difference is that this program isn't      */
/* executing or storing the input, instead, it filters each */
/* inserted command and data to the appropriate input file. */ 
/* After proccessing all the input in this way, it starts	*/
/* 3 instances of helper program (the program from Ex1).	*/
/* Each instance treats only commands of one type, so there */
/* there is one instance for dealing with Hexagons, one 	*/
/* instance for dealing with Heptagons and one instance for */
/* dealing with Octagons.									*/
/* ======================================================== */

#include "../include/polygon_filter.h"

int main(void)
{
	execute_polygon_filter_program();
	return 0;
}