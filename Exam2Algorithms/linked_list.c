#include "linked_list.h"

const int MAX_STRING_LENGTH = 1024;

/*
 * Function: create_node
 * ----------------------------
 * returns a pointer to a new node
 *
 *	data: data for node to hold
 *	data_size: size of data in bytes
 *
 */
Node* create_node(const void* data, const size_t data_size) {
	// Allocate space for the node
	Node* node = (Node*) malloc(sizeof(Node));

	// Copy data
	node->data = malloc(data_size);
	memcpy(node->data, data, data_size);

	// Neighbor is NULL initially
	node->next = NULL;

	return node;
}


/*
 * Function: create_list
 * ----------------------------
 * returns a pointer to a new linked_list. The head node is initialized to NULL
 *
 */
LinkedList* create_list() {
	LinkedList* list = (LinkedList*) malloc(sizeof(LinkedList));
	list->first = NULL;
	return list;
}

/*
 * Function: destroy
 * ----------------------------
 * frees the memory used to store a node's data as well as the node itself
 *
 *	node: the node to destroy
 *
 */
void destroy(Node* node) {
    free(node->data);
	free(node);
}

/*
 * Function: list_size
 * ----------------------------
 * returns the number of nodes in a linked_list
 *
 *	list: the linked_list
 *
 */
int list_size(const LinkedList* list) {
	if (list == NULL) {
		return -1;
	}

	size_t size = 0;
	Node* current = list->first;

	while (current != NULL) {
		size++;
		current = current->next;
	}

	return size;
}

/*
 * Function: get_string
 * ----------------------------
 * returns a char* representation of the list
 *
 *	list: the linked_list
 *  formatter: turns list data into strings
 *
 */
char* get_string(const LinkedList* list, char* (*formatter)(void*)) {
	char* buffer = (char*) malloc(MAX_STRING_LENGTH * sizeof(char));

	if (list == NULL) {
		strcpy(buffer,"NULL");
		return buffer;
	}

	strcpy(buffer, "[");
	Node* current = list->first;
	while (current != NULL) {
		sprintf(buffer, "%s%s", buffer, formatter(current->data));

		current = current->next;
		if (current != NULL) {
			sprintf(buffer, "%s, ", buffer);
		}
	}

	sprintf(buffer,"%s]", buffer);
	return buffer;
}

/*
 * Function: add_n
 * ----------------------------
 * adds an item to the list at index n
 *
 *	list: the linked_list
 *  n: add item at this position in list
 *	data: data to write to node
 *  data_size: size of data
 *
 */
bool add_n(LinkedList* list, const int n, const void* data,
         const size_t data_size) {

	// They passed a null for some reason
	if (list == NULL) {
		return false;
	}

	// negative n
	if (n < 0) {
		return false;
	}

	// n is larger than the size of the list
	const int SIZE = list_size(list);
	if (n > SIZE) {
		return false;
	}

	// List is empty
	if (list->first == NULL) {
		list->first = create_node(data, data_size);
		return true;
	}

	// At this point we know we can add the node so let's make it and hold on
	// to it for later
	Node* new_node = create_node(data, data_size);

	// Adding to beginning
	if (n == 0) {
		new_node->next = list->first;
		list->first = new_node;
		return true;
	}

	// Navigate to the spot in the list and add the node
	Node* current = list->first;
	Node* prev = NULL;
	for (int count = 0; count < n; count++) {
		prev = current;
		current = current->next;
	}

	new_node->next = current;
	prev->next = new_node;
	return true;
}

/*
 * Function: add_beginning
 * ----------------------------
 * adds an item to the beginning of the list
 *
 *	list: the linked_list
 *	data: data to write to node
 *  data_size: size of data
 *
 */
bool add_beginning(LinkedList* list, const void* data, const size_t data_size) {
	return add_n(list, 0, data, data_size);
}

/*
 * Function: add_end
 * ----------------------------
 * adds an item to the end of the list
 *
 *	list: the linked_list
 *	data: data to write to node
 *  data_size: size of data
 *
 */
bool add_end(LinkedList* list, const void* data, const size_t data_size) {
	return add_n(list, list_size(list), data, data_size);
}

/*
 * Function: get_n
 * ----------------------------
 * returns the data from the nth node in the list
 *
 *	list: the linked_list
 *  n: index of node whose data is to be returned
 *
 */
void* get_n(const LinkedList* list, const int n) {
	// They passed a null
	if (list == NULL) {
		return NULL;
	}

	// Negative n
	if (n < 0) {
		return NULL;
	}

	// List is empty
	if (list->first == NULL) {
		return NULL;
	}

	// n is larger than the size of the list
	const int SIZE = list_size(list);
	if (n > SIZE - 1) {
		return NULL;
	}

	Node* current = list->first;
	for (int i = 0; i < n; i++) {
		current = current->next;
	}

	return current; // changed from current->data to current
}

/*
 * Function: get_first
 * ----------------------------
 * returns the data from the first node in the list
 *
 *	list: the linked_list
 *
 */
void* get_first(const LinkedList* list) {
	return get_n(list, 0);
}

/*
 * Function: get_first
 * ----------------------------
 * returns the data from the last node in the list
 *
 *	list: the linked_list
 *
 */
void* get_last(const LinkedList* list) {
	return get_n(list, list_size(list) - 1);
}

/*
 * Function: remove_n
 * ----------------------------
 * removes the nth node in the list, adjusting pointers accordingly
 *
 *	list: the linked_list
 *  n: index of node whose data is to be returned
 *
 */
bool remove_n(LinkedList* list, const int n) {
	// They passed a null for some reason
	if (list == NULL) {
		return false;
	}

	if (n < 0) {
		return false;
	}

	// List is empty
	if (list->first == NULL) {
		return false;
	}

	// n is larger than the size of the list
	const int SIZE = list_size(list);
	if (n > SIZE - 1) {
		return false;
	}

	// Removing first node
	if (n == 0) {
		Node* node = list->first;
		list->first = node->next;
		destroy(node);
		return true;
	}

	Node* current = list->first;
	Node* prev = list->first;
	for (int count = 0; count < n; count++) {
		prev = current;
		current = current->next;
	}

	prev->next = current->next;
	destroy(current);
	return true;
}

/*
 * Function: remove_first
 * ----------------------------
 * removes the first node in the list, adjusting pointers accordingly
 *
 *	list: the linked_list
 *
 */
bool remove_first(LinkedList* list) {
	return remove_n(list, 0);
}

/*
 * Function: remove_last
 * ----------------------------
 * removes the last node in the list, adjusting pointers accordingly
 *
 *	list: the linked_list
 *
 */
bool remove_last(LinkedList* list) {
	return remove_n(list, list_size(list) - 1);
}
