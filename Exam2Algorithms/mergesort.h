#ifndef MERGESORT_H_INCLUDED
#define MERGESORT_H_INCLUDED

#include "linked_list.h"

LinkedList* split(LinkedList*);
Node* merge(Node*, Node*, int (void*, void*));
void merge_lists(LinkedList*, LinkedList*, int (void*, void*));
void merge_sort(LinkedList*, int (void*, void*));

#endif
