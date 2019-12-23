/* ======================================================== */
/*   definitions.h		        						    */
/* ======================================================== */
#ifndef DEFENITIONS_H
#define DEFENITIONS_H

//---------------------------------------------------------------------------
//----------------------------- Includes ------------------------------------
//---------------------------------------------------------------------------
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

//---------------------------------------------------------------------------
//----------------------------- General Defines -----------------------------
//---------------------------------------------------------------------------

//Filenames
#define HEX_IN "hex_in.tmp"
#define HEX_OUT "hex_out.log"
#define HEPT_IN "hept_in.tmp"
#define HEPT_OUT "hept_out.log"
#define OCT_IN "oct_in.tmp"
#define OCT_OUT "oct_out.log"
#define HELPER_PROG "ex2_q1_helper.exe"

//Method types (ease of read)
#define PRIVATE
#define PUBLIC

//Shapes types - used for indexing files storing the relevant inputs
#define HEXA 0
#define HEPTA 1
#define OCTA 2

//alias for stdin & stdout
#define STDIN 0
#define STDOUT 1

//some more general defines
#define NONE 0
#define NUM_OF_FILES 3
#define END_OF_INPUT "1\n"
#define START_OF_FILE 0
#define INP_BIT 1
#define SMALLEST_POLYGON 6

//---------------------------------------------------------------------------
//----------------------------- General Typedefs ----------------------------
//---------------------------------------------------------------------------
typedef enum { FALSE=0, TRUE=1 } EBoolType;
typedef enum { SUCCESS = 0, FAILURE = 1 } EExecutionStatus;
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