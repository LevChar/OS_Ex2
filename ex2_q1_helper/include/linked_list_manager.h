/* ======================================================== */
/*   Linked_List_Manager.h	       						    */
/* ======================================================== */
#ifndef LINKED_LIST_MANAGER_H
#define LINKED_LIST_MANAGER_H

//---------------------------------------------------------------------------
//----------------------------- Includes ------------------------------------
//---------------------------------------------------------------------------
#include <stdlib.h>
#include "definitions.h"

//---------------------------------------------------------------------------
//-------------------Generic Singly Linked List Data Structure---------------
//---------------------------------------------------------------------------
typedef void(*freeFunction)(pVoid);

typedef struct _Singly_Linked_Node {
    pVoid data;
    struct _Singly_Linked_Node *next;
} Singly_Linked_Node;

typedef Singly_Linked_Node S_L_N;

typedef struct _Singly_Linked_List {
    Singly_Linked_Node *head;
    Singly_Linked_Node *tail;
    size_t logical_length;
    size_t element_size;
    freeFunction freeFn;
} Singly_Linked_List;

typedef Singly_Linked_List S_L_L;

//---------------------------------------------------------------------------
//---------------------- Public Methods Prototypes---------------------------
//---------------------------------------------------------------------------
void 
initialize_Empty_List(Singly_Linked_List *list,
						 size_t Element_Size, 
						 freeFunction free_Fn);

void 
append_To_List(Singly_Linked_List *list, pVoid element);

void 
destroy_List(Singly_Linked_List *list);

#endif // LINKED_LIST_MANAGER_H