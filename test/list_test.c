#include <stdio.h>
#include "double_list.h"

BOOL eval(DL_NODE *n1, DL_NODE *n2) {
	return *(int*)n1->object < *(int*)n2->object;
}

int main(int argc, char **argv) {
	int arr[] = {8, 10, 11, 3, 12, 18, 16, 9, 1, 17, 15, 7, 2, 6, 19, 4, 14, 5, 13, 20};
	DL_TABLE *table = dl_table_new();
	DL_NODE *tmp;
	int i;
	
	for(i = 0; i < 20; i++) {
		dl_add(table, &arr[i]);
	}
	
	dl_sort(table, eval);
	
	for(tmp = table->top; tmp != NULL; tmp = tmp->next) {
		printf("%d\n", *(int*)tmp->object);
	}

	dl_table_destroy(table);

	return 0;
}

