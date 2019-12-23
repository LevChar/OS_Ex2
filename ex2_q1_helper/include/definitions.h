/* ======================================================== */
/*   Definitions.h		        						    */
/* ======================================================== */
#ifndef DEFENITIONS_H
#define DEFENITIONS_H

//---------------------------------------------------------------------------
//----------------------------- General Defines -----------------------------
//---------------------------------------------------------------------------
#define PRIVATE
#define PUBLIC
#define SMALLEST_Polygon 6
#define AMOUNT_OF_VERTICES_IN_EACH_ROW 4
#define NUM_INPT_ROWS 2
#define FIRST_RAW_INPUT 0
#define SECOND_RAW_INPUT 1
#define NONE 0
#define FIRST_VERTEX 0

//---------------------------------------------------------------------------
//----------------------------- General Typedefs ----------------------------
//---------------------------------------------------------------------------
typedef enum { FALSE=0, TRUE=1 } EBoolType;
typedef enum { SUCCESS = 0, FAILURE = 1 } EExecutionStatus;
typedef void* pVoid;
typedef unsigned long long ULL_INPUT_TYPE;
typedef unsigned char BYTE;

//---------------------------------------------------------------------------
//----------------------------- Bit Handling Maks ---------------------------
//---------------------------------------------------------------------------
#define TYPED_LSB_MASK(TYPE) ((TYPE)1)

#define MASK_WITH_N_LSBS_SET(TYPE, N) \
	((TYPED_LSB_MASK(TYPE) << N) - 1)

#define MASK_WITH_RANGE_BITS_SET(TYPE, FROM, TO) \
	(MASK_WITH_N_LSBS_SET(TYPE, ((TO-FROM)+1))  << FROM)

#endif // DEFENITIONS_H
