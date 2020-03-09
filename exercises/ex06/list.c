/* Example code for Exercises in C.

Based on an example from http://www.learn-c.org/en/Linked_lists

Copyright 2016 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node *next;
} Node;


/* Makes a new node structure.
*
* val: value to store in the node.
* next: pointer to the next node
*
* returns: pointer to a new node
*/
Node *make_node(int val, Node *next) {
    Node *node = malloc(sizeof(Node));
    node->val = val;
    node->next = next;
    return node;
}


/* Prints the values in a list.
*
* list: pointer to pointer to Node
*/
void print_list(Node **list) {
    Node *current = *list;

    printf("[ ");
    while (current != NULL) {
        printf("%d ", current->val);
        current = current->next;
    }
    printf("]\n");
}


/* Removes and returns the first element of a list.
*
* list: pointer to pointer to Node
*
* returns: int or -1 if the list is empty
*/
int pop(Node **list) {

    // Set current to the current head of the list
    Node *current = *list;

    // If head is NULL, list is empty
    if (current == NULL)
    {
      return -1;
    }

    // Store value of head node
    int val = current->val;

    // Set the head to the second node
    *list = current->next;

    // Free the current head (should I do this?)
    free(current);

    // Return zero
    return val;
}


/* Adds a new element to the beginning of the list.
*
* list: pointer to pointer to Node
* val: value to add
*/
void push(Node **list, int val) {

    // Make new node
    Node *new = make_node(val, NULL);

    // Set current to the current head of the head of the list
    Node *current = *list;

    // Make new->next be the second element in list
    new->next = current;

    // Make list double pointer point to the new node
    *list = new;
}


/* Removes the first element with the given value
*
* Frees the removed node.
*
* list: pointer to pointer to Node
* val: value to remove
*
* returns: number of nodes removed
*/
int remove_by_value(Node **list, int val) {

    // Set current to the current head of the list
    Node *current = *list;

    // If the node to remove is the first, call
    // pop on the list.
    if (current->val == val)
    {
      pop(list);
      return 1;
    }

    // Iterate through the nodes until the
    // desired value is found or the end of
    // the list is reached.
    while(current->next != NULL)
    {
      if(current->next->val == val)
      {
        // Set tmp pointer to node to remove
        Node *tmp = current->next;

        // Skip node to be deleted with pointer on
        // current node
        current->next = current->next->next;

        // Free the node to be deleted
        free(tmp);

        // Return that we deleted one node
        return 1;
      }

      // Iterate through nodes
      current = current->next;
    }

    // Return that we removed no nodes if value
    // is not present in the list
    return 0;
}


/* Reverses the elements of the list.
*
* Does not allocate or free nodes.
*
* list: pointer to pointer to Node
*/
void reverse(Node **list) {
    // FILL THIS IN!
}


int main() {
    Node *head = make_node(1, NULL);
    head->next = make_node(2, NULL);
    head->next->next = make_node(3, NULL);
    head->next->next->next = make_node(4, NULL);

    Node **list = &head;
    print_list(list);

    int retval = pop(list);
    print_list(list);

    push(list, retval+10);
    print_list(list);

    remove_by_value(list, 3);
    print_list(list);

    remove_by_value(list, 7);
    print_list(list);

    reverse(list);
    print_list(list);
}
