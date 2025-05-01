#include <string.h>
#include <malloc.h>
#include "../inc/ar_disjoint_set.h"
void ar_init_disjoint_set(
	struct ar_disjoint_set * dj_set,
	int size
) {
	dj_set->size = size;
	dj_set->element = (struct ar_disjoint_set_unit *)malloc(size * sizeof(struct ar_disjoint_set_unit));
	for (int i = 0; i < size; i++) {
		dj_set->element[i].parent = &dj_set->element[i];
		dj_set->element[i].num = i;
		dj_set->element[i].rank = 1;
	}
}

void ar_destruct_disjoint_set(struct ar_disjoint_set * dj_set) {
	dj_set->size = 0; free(dj_set->element);
}

struct ar_disjoint_set_unit * ar_parent_disjoint_set_unit(struct ar_disjoint_set_unit *dj_sub_set) {
	if (dj_sub_set == dj_sub_set->parent) {
		return dj_sub_set;
	}
	dj_sub_set->parent = ar_parent_disjoint_set_unit(dj_sub_set->parent);
	return dj_sub_set->parent;
}

void ar_union_disjoint_set(struct ar_disjoint_set_unit *dj_sub_set1, struct ar_disjoint_set_unit *dj_sub_set2) {
	ar_parent_disjoint_set_unit(dj_sub_set1);
	ar_parent_disjoint_set_unit(dj_sub_set2);
	if (dj_sub_set1->parent == dj_sub_set2->parent) {return;}
	if (dj_sub_set1->parent->rank >= dj_sub_set2->parent->rank) {
		dj_sub_set1->parent->rank += dj_sub_set2->parent->rank;
		dj_sub_set2->parent->parent = dj_sub_set1->parent;
	} else {
		dj_sub_set2->parent->rank += dj_sub_set1->parent->rank;
		dj_sub_set1->parent->parent = dj_sub_set2->parent;
	}
}
