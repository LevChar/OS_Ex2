/* ======================================================== */
/*   Linked_List_Manager.c	       						    */
/* ======================================================== */

//---------------------------------------------------------------------------
//----------------------------- Includes ------------------------------------
//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include "../include/linked_list_manager.h"

//---------------------------------------------------------------------------
//---------------------- Private Methods Prototypes -------------------------
//---------------------------------------------------------------------------
Singly_Linked_Node 
*allocate_list_cell(pVoid data_ptr);

//---------------------------------------------------------------------------
//-----------------------Private Methods Implementations---------------------
//---------------------------------------------------------------------------

/***************************************************************************\
description:
Used for allocation of new node in the list.

parameters:
data_ptr - Pointer to the Polygon information the the node will point to.

return:
new list node
****************************************************************************/
PRIVATE Singly_Linked_Node *allocate_list_cell(pVoid data_ptr)
{
	//S_L_N is a Typedef for Singly_Linked_Node
    S_L_N *cell = (S_L_N*)malloc(sizeof(S_L_N));
    if(NULL == cell)
    {
        printf("Memory allocation error!\n");
        exit(1);
    }

    cell->data = data_ptr;
    cell->next = NULL;

    return cell;
}

//---------------------------------------------------------------------------
//---------------------- Public Methods Implementations----------------------
//---------------------------------------------------------------------------

/***************************************************************************\
description:
Used for initialization of new list.

parameters:
*list - The list to be initialized.
Element_Size - The size in bytes of the data pointed by each node of the list.
free_Fn - A function that is used for releasing resources pointed by data.

return:
Void (No-return value).
****************************************************************************/
PUBLIC void initialize_Empty_List(Singly_Linked_List *list,
						 size_t Element_Size, 
						 freeFunction free_Fn)
{
	list->head = list->tail = NULL;
	list->element_size = Element_Size;
	list->logical_length = 0;
	list->freeFn = free_Fn;
}

/***************************************************************************\
description:
Used for insertion of new data to the end of the list, using another function
for creating the node out of the received data.

parameters:
*list - The list that the new data should be added to.
element - A pointer to the data element that should be inserted to the list.

return:
Void (No-return value)
****************************************************************************/
PUBLIC void append_To_List(Singly_Linked_List *list, pVoid element)
{
  Singly_Linked_Node *cell = allocate_list_cell(element);

  if(list->logical_length == 0)
    {
        list->head = list->tail = cell;
    }
  else
    {
        list->tail->next = cell;
        list->tail = cell;
    }

  list->logical_length++;
}

/***************************************************************************\
description:
Used for distruction (memory release) of a given list.

parameters:
*list - The list that should be destroyed by this function.

return:
Void (No-return value)
****************************************************************************/
PUBLIC void destroy_List(Singly_Linked_List *list)
{
	Singly_Linked_Node *current = list->head;

	while (current != NULL) {
		list->head = current->next;

		if (list->freeFn) {
			list->freeFn(current->data);
		}

		free(current->data);
		free(current);

		list->logical_length--;

		current = list->head;
	}
}