#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "btree.h"

int array_searchhigh_key(int size, const struct data_t *array, uint64_t key) {
	int low  = -1;
	int high = size;
	int mid  = 0;

	//Do regular binary search over array
	while (low + 1 < high) {
		mid = (low + high) / 2;
		if (array[mid].key == key)
			return mid;
		else if (array[mid].key < key)
			low = mid;
		else
			high = mid;
	}

	return high;
}

btree btree_create(void) {
	btree b = (btree) malloc(sizeof(*b));

	b->is_leaf = 1;
	b->size = 0;

	return b;
}

void btree_destroy(btree b) {
	int i;

	//Recursive tree destruction
	if (!b->is_leaf)
		for (i = 0; i < b->size + 1; i++)
			btree_destroy(b->children[i]);

	free (b);
}

//Returns -1 if element was not found
uint64_t btree_search(btree b, uint64_t key) {
	if (b->size == 0)
		return -1;

	//Recursive tree search over arrays
	int pos = array_searchhigh_key(b->size, b->data, key);

	if (pos < b->size && b->data[pos].key == key)
		return b->data[pos].value;

	if (b->is_leaf)
		return -1;

	return btree_search(b->children[pos], key);
}


void btree_delete(btree b, uint64_t key) {
	struct data_t elem;
	elem.key = key; elem.value = -1;
	btree_insert(b, elem);
}
