// Programmer: Quoc Tran
// Project 1 
// Date: 9/15/2024
// Description: Linux, C++, 
// Command Line Argument, stdin/stdout/stderr,
// File I/O, Formatted Output, Memory Management, 
// Linked List, Modular Design


#include "structs.h"
#include "list_read.h"
#include "list_write.h"
#include <stdio.h>
#include <stdlib.h>

// Function to release (free) all nodes in the list
void listRelease(LIST *pLIST) {
    if (!pLIST) {
        fprintf(stderr, "Error in listRelease: NULL list\n");
        return;
    }

    NODE *current = pLIST->head;
    NODE *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    pLIST->head = NULL;
    pLIST->length = 0; // Ensure length is reset after releasing the list
}

// Function to insert a new node with the given key at the head of the list
NODE *listInsert(LIST *pLIST, double key) {
    if (!pLIST) {
        fprintf(stderr, "Error in listInsert: NULL list\n");
        return NULL;
    }

    NODE *newNode = (NODE *)malloc(sizeof(NODE));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    newNode->key = key;
    newNode->next = pLIST->head;
    pLIST->head = newNode;

    pLIST->length++; // Increment length when a new node is inserted
    return newNode;
}

// Function to append a new node with the given key to the end of the list
NODE *listAppend(LIST *pLIST, double key) {
    if (!pLIST) {
        fprintf(stderr, "Error in listAppend: NULL list\n");
        return NULL;
    }

    NODE *newNode = (NODE *)malloc(sizeof(NODE));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    newNode->key = key;
    newNode->next = NULL;

    if (pLIST->head == NULL) {
        pLIST->head = newNode;
    } else {
        NODE *current = pLIST->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }

    pLIST->length++; // Increment length when a new node is appended
    return newNode;
}

// Function to delete the first node with the given key
NODE *listDelete(LIST *pLIST, double key) {
    if (!pLIST || !pLIST->head) {
        fprintf(stderr, "Error in listDelete: NULL list or empty list\n");
        return NULL;
    }

    NODE *current = pLIST->head;
    NODE *previous = NULL;

    while (current != NULL && current->key != key) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        fprintf(stderr, "Warning in listDelete: Key %lf not in list\n", key);
        return NULL; // Key not found
    }

    if (previous == NULL) {
        // The node to delete is the head
        pLIST->head = current->next;
    } else {
        previous->next = current->next;
    }

    free(current);
    pLIST->length--; // Decrement length when a node is deleted
    return pLIST->head; // Return the new head after deletion
}


