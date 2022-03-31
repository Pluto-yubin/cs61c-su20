#include "list.h"

/* Add a node to the end of the linked list. Assume head_ptr is non-null. */
void append_node(node** head_ptr, int new_data)
{
    /* First lets allocate memory for the new node and initialize its attributes */
    /* YOUR CODE HERE */

    node* newNode = (node*)malloc(sizeof(node));
    newNode->val = new_data;
    newNode->next = NULL;
    /* If the list is empty, set the new node to be the head and return */
    if (*head_ptr == NULL) {
        // head_ptr = &newNode;
        *head_ptr = newNode;
        return;
    }
    node* curr = *head_ptr;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = newNode;
}

/* Reverse a linked list in place (in other words, without creating a new list).
   Assume that head_ptr is non-null. */
void reverse_list(node** head_ptr)
{
    node* prev = NULL;
    node* cur = *head_ptr;
    node* next = NULL;
    while (cur != NULL) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    /* Set the new head to be what originally was the last node in the list */
    *head_ptr = prev; /* INSERT CODE HERE */
}
