//
// Created by USER on 07/10/2021.
//
#include <stdlib.h>
#include <stdbool.h>
#ifndef QUEENGAMBITGAME_INTIGERSLIST_H
#define QUEENGAMBITGAME_INTIGERSLIST_H


typedef struct node_t* Node;

typedef enum {
    SUCCESS=0,
    MEMORY_ERROR,
    UNSORTED_LIST,
    NULL_ARGUMENT
} ErrorCode;

/** creates Node when given a pointer
 * ERROR CODES: MEMORY_ERROR if allocation fails */
Node nodeCreate(Node* node, ErrorCode *error);

/** this func is destroying the list recursively*/
void destroyList(Node head);

/** insert to current place in the list
 * ERROR CODE - MEMORY_ERROR if fails into 'error'
 */
void insertCurrent(Node* current, Node* to_insert, ErrorCode *error);

bool isListSorted(Node head);

/** checks ERROR CODE:
* UNSORTED_LIST: if one of the lists isn't sorted
* NULL_ARGUMENT: if one of the list is NULL
* SUCCESS : if none above is TRUE
*/
ErrorCode checkErrors(Node list1, Node list2);

/** merge to sorted lists into ONE
 * ERROR CODE:
 * return null if one of the following fails:
 * One of the lists isn't sorted
 * Allocation fails
 * also 'error' is enum that indicate ether  success ether fail
 */
Node mergeSortedLists(Node list1, Node list2, ErrorCode *error);





#endif //QUEENGAMBITGAME_INTIGERSLIST_H
