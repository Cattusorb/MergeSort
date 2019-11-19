#include <time.h>
#include "mergesort.h"

/*
 * Function: int_formatter
 * ----------------------------
 * returns a char* representation of the integer stored at a given address
 *
 *	data: points to an integer
 *
 */
char* int_formatter(void* data) {
	char* buffer = (char*) malloc(12 * sizeof(char));
	sprintf(buffer, "%d", *((int*) data));
	return buffer;
}

/*
 * Function: compare_ints
 * ----------------------------
 * Compares the data stored at pointers a and b, assuming both addresses store
 * integers
 *
 *   a, b: void pointers to integers
 *
 * returns: ans < 0 if a < b, ans > 0 if a > b, ans = 0 if a == b
 *
 */
int compare_ints(void* a, void* b) {
	return *((int*) a) - *((int*) b);
}

int main() {
	srand(time(NULL));
	const int SIZE = 16;
	LinkedList* list = create_list();
	for (int i = 0; i < SIZE; i++) {
		int r = rand() % 100;
		add_end(list, &r, sizeof(int));
	}

	printf("Before: %s\n", get_string(list, int_formatter));
	merge_sort(list, compare_ints);
	printf("After: %s\n", get_string(list, int_formatter));
}
