#ifndef AR_ar_disjoint_set
#define AR_ar_disjoint_set
struct ar_disjoint_set_unit{
	struct ar_disjoint_set_unit *parent;
	int num;
	int rank;
};

struct ar_disjoint_set{
	int size;
	struct ar_disjoint_set_unit *element;
};

struct ar_disjoint_set_unit * ar_parent_disjoint_set_unit(struct ar_disjoint_set_unit *dj_sub_set);

void ar_init_disjoint_set(struct ar_disjoint_set *dj_set, int size);

void ar_destruct_disjoint_set(struct ar_disjoint_set *dj_set);

void ar_union_disjoint_set(
	struct ar_disjoint_set_unit *dj_sub_set1,
	struct ar_disjoint_set_unit *dj_sub_set2
);
#endif