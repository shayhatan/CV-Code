//
// Created by USER on 07/10/2021.
//


#include<stdio.h>
#include <stdbool.h>
#include<stdlib.h>
#include "DrySpring2021.h"

struct node_t {
    int x; // void* DATA
    //cmpFunction
    struct node_t *next; // next.
};


Node nodeCreate(Node* node, ErrorCode *error){
    *node = malloc(sizeof (Node));
    if(!(*node)){
        *error = MEMORY_ERROR;
        return NULL;
    }
    (*node)->next = NULL;
    return *node;
}

void destroyList(Node head) {
    if (!head) {
        return;
    }
    destroyList(head->next);
    free(head);
}

void insertCurrent(Node* current, Node* to_insert, ErrorCode *error){
    (*current)->x = (*to_insert)->x;
    *current = nodeCreate(&((*current)->next), error);
    *to_insert = (*to_insert)->next;
}

bool isListSorted(Node head) {
    if (head == NULL) {
        return true;
    }
    for (Node t = head; t->next != NULL; t = t->next) {
        if (t->x > t->next->x) {
            return false;
        }
    }
    return true;
}

ErrorCode checkErrors(Node list1, Node list2) {
    if ((!list1) || (!list2)) {
        return NULL_ARGUMENT;
    }
    if ((!isListSorted(list1)) || (!isListSorted(list2))) {
        return UNSORTED_LIST;
    }
    return SUCCESS;
}


Node mergeSortedLists(Node list1, Node list2, ErrorCode *error) {
    *error = checkErrors(list1, list2);

    Node merged_lists = nodeCreate(&merged_lists, error);
    Node current = merged_lists;
    while(list1 && list2 && *error == SUCCESS){
        if(list1->x < list2->x) {
            insertCurrent(&current, &list1, error);
        } else{
            insertCurrent(&current, &list2, error);
        }
    }
    if (list1) {
        while (list1->next && *error == SUCCESS) {
            insertCurrent(&current, &list1, error);
        }
        current->x = list1->x;
    }
    if (list2) {
        while (list2->next && *error == SUCCESS) {
            insertCurrent(&current, &list2, error);
        }
        current->x = list2->x;
    }
    if(*error == SUCCESS) {
        return merged_lists;
    }
    destroyList(merged_lists);
    return NULL;
}














/** ----------------------------- A TEST --------------------------------*/




void push(Node *head, int x) {
    Node new_node = malloc(sizeof(*new_node));
    if (new_node == NULL) {
        perror("error in push()");
        exit(1);
    }
    new_node->x = x;
    new_node->next = (*head);
    (*head) = new_node;
}

void printList(Node node) {
    while (node != NULL) {
        printf("%d -> ", node->x);
        node = node->next;
    }
    printf("NULL\n");
}


int main() {
    // Node merged_out = NULL;
    Node list1 = NULL;
    Node list2 = NULL;
/* Create two sorted linked lists
list1: 1->4->9, list2: 2->4->8 */
    push(&list1, 8);
    push(&list1, 4);
    push(&list1, 2);
    push(&list2, 9);
    push(&list2, 4);
    push(&list2, 1);
    printf("before:\n");
    printf("list1:\n");
    printList(list1);
    printf("list2:\n");
    printList(list2);
    printf("\n\n");
    ErrorCode error_code = NULL_ARGUMENT;
    Node merged = mergeSortedLists(list1, list2, &error_code);
    printf("after:\n");
    printList(merged);
    printf("error_code = %d (0 is SUCCESS)\n", error_code);
    printf("\n");
    printf("double check that list1 and list2 didn't change -\n");
    printf("list1:\n");
    printList(list1);
    printf("list2:\n");
    printList(list2);

    destroyList(merged);
    return 0;

}






