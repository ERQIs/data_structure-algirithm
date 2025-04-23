#include <stddef.h>

 /**
  * container_of - cast a member of a structure out to the containing structure
  * @ptr:    the pointer to the member.
  * @type:   the type of the container struct this is embedded in.
  * @member: the name of the member within the struct.
  *
  * WARNING: any const qualifier of @ptr is lost.
  */
 #define container_of(ptr, type, member) ({              \
     void *__mptr = (void *)(ptr);                   \
     ((type *)(__mptr - offsetof(type, member))); })

typedef struct DSU_node {
    struct DSU_node *p;
    int rank;
}   DSU_node;

void DSU_init(DSU_node* node) {
    node->rank = 0;
    node->p = node;
}

void DSU_link(DSU_node* x, DSU_node* y) {
    if (x->rank > y->rank) {
        y->p = x;
    } else {
        x->p = y;
        if (x->rank == y->rank){
            y->rank ++;
        }
    }
}

DSU_node* DSU_find_set(DSU_node* x) {
    if (x->p != x){
        x->p = DSU_find_set(x->p);
    }
    return x->p;
}

void DSU_union(DSU_node* x, DSU_node* y) {
    DSU_link(DSU_find_set(x), DSU_find_set(y));
} 

#include <stdlib.h>
#include <stdio.h>

int main() {
    int n, m, p, q, i, x, y;
    scanf("%d%d%d%d", &n, &m, &p, &q);

    DSU_node* A = (DSU_node*) malloc (sizeof(struct DSU_node) * n);
    for (i = 0; i < n; i ++){
        DSU_init(&A[i]);
    }
    DSU_node* B = (DSU_node*) malloc (sizeof(struct DSU_node) * m);
    for (i = 0; i < m; i ++){
        DSU_init(&B[i]);
    }

    for (i = 0; i < p; i ++) {
        scanf("%d%d", &x, &y);
        DSU_union(&A[x - 1], &A[y - 1]);
    }

    for (i = 0; i < q; i ++){
        scanf("%d%d", &x, &y);
        DSU_union(&B[-x - 1], &B[-y - 1]);
    }

    int males = 0, females = 0;
    for (int i = 0; i < n; i ++) {
        if (DSU_find_set(&A[0]) == DSU_find_set(&A[i])) {
            males ++;
        }
    }
    for (int i = 0; i < m; i ++) {
        if (DSU_find_set(&B[0]) == DSU_find_set(&B[i])) {
            females ++;
        }
    }

    printf("%d\n", males < females ? males : females);
    return 0;
}


