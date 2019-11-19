#include "mergesort.h"

/*
 * Function: split
 * ----------------------------
 * Splits a singly linked list into two halves. If the list has an odd number of
 * nodes, the extra node goes in the first half.
 *
 *	list: pointer to list to split
 *
 * returns a pointer to the second (back) half of the list. The list itself has
 * the linkage broken at the halfway point.
 *
 */
LinkedList* split(LinkedList* list) {
	// Get size of list
	int size = list_size(list);

	// If list size is -1 (bad list) or 0 (list is empty) return NULL because it
	// can't be split
	if (size <= 0)
    {
        return NULL;
    }

    LinkedList* back = create_list();
    Node* half;

	// If list size is 1, then the back half of the list should be an empty list
    if (size == 1)
    {
        half = list->first;
        back = NULL;
    }
	// If the list size is greater than 1 then get the node that is halfway
	// through the list. Call this node half.
	if (size > 1)
    {
        half = get_n(list, (size / 2)); // get_n doesn't return the node
    }
	// Create a linked list called back and set back->first = half->next
	back->first = half->next;
	// Set half->next = NULL, this breaks the first half of the list
	half->next = NULL;
	// Return back
	return back;
}

/*
 * Function: merge
 * ----------------------------
 * Main workhorse function for merging two sorted lists
 *
 *	a: node in first list, will be NULL if all nodes from first list are merged
 *  b: node in second list, will be NULL if all nodes from second list are merged
 *  compare: comparator
 *
 *  returns the next node in the merged list
 *
 */
Node* merge(Node* a, Node* b, int (*compare)(void*, void*)) {
	// If a or b are NULL then we just return the other node
	if (a == NULL)
    {
        return b;
    }
    if (b == NULL)
    {
        return a;
    }

	// If a->data <= b->data then
	//		result = a
	//		result->next = merge(a->next, b)
	//		return result
	//
	// else
	//		result = b
	//		result->next = merge(a, b->next)
	//		return result
	Node* result;
	if (compare(a->data, b->data) <= 0)
    {
        Node* result = a;
        result->next = merge(a->next, b, compare);
        return result;
    } else
    {
        result = b;
        result->next = merge(a, b->next, compare);
        return result;
    }

	return NULL;
}

/*
 * Function: merge_lists
 * ----------------------------
 * Merges two sorted linked lists into a single, sorted whole
 *
 *	a: first list, will contain the sorted whole when done
 *  b: second list
 *  compare: comparator
 *
 */
void merge_lists(LinkedList* a, LinkedList* b, int (*compare)(void*, void*)) {
	a->first = merge(a->first, b->first, compare);
}

/*
 * Function: merge_sort
 * ----------------------------
 * Sorts a linked list using the merge sort algorithm
 *
 *	list: list to sort
 *  compare: comparator
 *
 */
void merge_sort(LinkedList* list, int (*compare) (void*, void*)) {
	// Use split and merge_lists here to do merge sort
	LinkedList* splitList = split(list);
	while (splitList != NULL)
    {
        merge_lists(list, splitList, compare);
        splitList = split(splitList);
    }

	return;
}
