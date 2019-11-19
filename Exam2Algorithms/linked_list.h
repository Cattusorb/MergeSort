#ifndef LINKED_LIST_H_INCLUDED
#define LINKED_LIST_H_INCLUDED

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct Node Node;
typedef struct LinkedList LinkedList;

/*
 * Structure: Node
 * ----------------------------
 * represents a node in a singly linked list
 *
 *	data: data held by node
 *  next: next node in list, NULL if this is the last node in the list
 *
 */
struct Node {
    void* data;
    Node* next;
};

/*
 * Structure: LinkedList
 * ----------------------------
 * represents a singly linked list
 *
 *	first: first, or head, node in list; NULL if list is empty
 *
 */
struct LinkedList {
    Node* first;
};

// BASIC OPERATIONS //
Node* create_node(const void*, const size_t);
LinkedList* create_list();
void destroy(Node*);
int list_size(const LinkedList*);
char* get_string(const LinkedList*, char* (void*));

// ADDITION //
bool add_n(LinkedList*, const int, const void*, const size_t);
bool add_beginning(LinkedList*, const void*, const size_t);
bool add_end(LinkedList*, const void*, const size_t);

// ACCESS //
void* get_n(const LinkedList*, const int);
void* get_first(const LinkedList*);
void* get_last(const LinkedList*);

// DELETION //
bool remove_n(LinkedList*, const int);
bool remove_first(LinkedList*);
bool remove_last(LinkedList*);

#endif // LINKED_LIST_H_INCLUDED
