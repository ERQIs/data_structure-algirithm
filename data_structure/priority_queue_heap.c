# include <stdio.h>
# include <stdlib.h>

/*
                            PRQ PRIORITY QUEUE

      This is a priority queue based on heap.
      PRQ organizes elements by organizing a list of pointers that points
    to the elements. Inside, all the pointers got a (void*) type.
    To define the order of prioricy, you have to define a function:

        int (*cmp)(void* prior, void* subseq)
        {
            returns 1 if prior is more prior than subseq, 0 oterwise.
            (prior and subseq are pointers to the elements)
        }
    
      When pushing an element into the PRQ, push a pointer to that element.
      When poping an element pointer from PRQ, remember to convert it from
    the (void*) type.



PRQ supports following functions:


        PRQ PRQ_create (int max_size):

            Creates a priority queue that maintains at most max_size elements.

        void* PRQ_top (PRQ Q):

            Gets the top of PRQ without extracting the top element.
        

        void* PRQ_pop (PRQ Q, int (*cmp)(void* prior, void* subseq)):

            Gets the top of PRQ extracting the top element.


        void PRQ_push (PRQ Q, void* new, int (*cmp)(void* prior, void* subseq)):

            Inserts an element into priority queue.

        
        int PRQ_is_empty (PRQ Q):

            returns 1 if Q is empty, 0 otherwise.


        int PRQ_is_full (PRQ Q):

            returns 1 if Q is full, 0 otherwise.


        int PRQ_get_size (PRQ Q)

            returns the size of Q.

        void PRQ_free (PRQ Q)

            frees the PRQ.



PRQ inside functions (not recomended to call directly)


    PRQ_left(n)
    PRQ_right(n)
    PRQ_parent(n)
    void PRQ_swap (void** _a, void** _b)
    void PRQ_heapify (PRQ Q, int n, int (*cmp)(void* prior, void* subseq))

*/



# define PRQ_left(n) ( (((n) + 1) << 1) - 1 )
# define PRQ_right(n) ( ((n) + 1) << 1 )
# define PRQ_parent(n) ( (((n) + 1) >> 1) - 1 )


typedef struct priority_queue {
    int size;
    int max_size;
    void** data;
}   *PRQ;

PRQ PRQ_create (int max_size)
{
    if (max_size <= 0){
        printf("invalid max_size to create PRQ.\n");
        return NULL;
    }
    void** data = (void**) malloc (sizeof(void*) * max_size);
    PRQ ret = (PRQ) malloc (sizeof(struct priority_queue));
    if (data == NULL || ret == NULL){
        printf("unable to allocate PRQ.\n");
        return NULL;
    }
    ret->data = data;
    ret->max_size = max_size;
    ret->size = 0;
    return ret;
}

void PRQ_swap (void** _a, void** _b)
{
    void* tmp = *_a;
    *_a = *_b;
    *_b = tmp;
}

void PRQ_heapify (PRQ Q, int n, int (*cmp)(void* prior, void* subseq))
{
    void** data = Q->data;
    int size = Q->size;
    int left = PRQ_left(n);
    int right = PRQ_right(n);
    int prior = n;

    if (right < size){
        prior = cmp(data[right], data[prior]) ? right : prior;
    }
    if (left < size){
        prior = cmp(data[left], data[prior]) ? left : prior;
    }
    if (prior != n){
        PRQ_swap(data + prior, data + n);
        PRQ_heapify(Q, prior, cmp);
    }
}

void* PRQ_top (PRQ Q)
{
    if (Q->size == 0){
        printf("PRQ empty.\n");
        return NULL;
    }
    return (Q->data)[0];
}

void* PRQ_pop (PRQ Q, int (*cmp)(void* prior, void* subseq))
{
    if (Q->size == 0){
        printf("PRQ underflow.\n");
        return NULL;
    }
    void* ret = (Q->data)[0];
    (Q->data)[0] = (Q->data)[Q->size - 1];
    Q->size --;
    PRQ_heapify(Q, 0, cmp);
    return ret;
}

void PRQ_push (PRQ Q, void* new, int (*cmp)(void* prior, void* subseq))
{
    if (Q->max_size == Q->size){
        printf("PRQ overflow.\n");
        return;
    }
    int now_idx = Q->size;
    int p_idx = PRQ_parent(now_idx);
    void** data = Q->data;

    data[ (Q->size) ++] = new;
    while (now_idx != 0 && cmp(data[now_idx], data[p_idx])){
        PRQ_swap(data + now_idx, data + p_idx);
        now_idx = p_idx;
        p_idx = PRQ_parent(now_idx);
    }
}

int PRQ_is_empty (PRQ Q)
{
    return Q->size == 0;
}

int PRQ_is_full (PRQ Q)
{
    return Q->size == Q->max_size;
}

int PRQ_get_size (PRQ Q)
{
    return Q->size;
}

void PRQ_free (PRQ Q)
{
    free(Q->data);
    free(Q);
}

int cmp (void* a, void* b)
{
    return *(int*)a > *(int*)b;
}



/*
  The first viersion of priority queue doesn't support to change
any object (except for the top) that is "in the queue". The reason
is that we can't easily find the queue element pointing at the changed
object to maintain the priority queue.

  The second version of priority queue allows to change the objects.
which means when we change the object, we can find the queue element
from the priority queue and maintain it.

  To meet this, the OBJECT (which is a structure) must contain a member
( int handler ) to be managed by this version of priority queue.
  This member is initialized and updated by PRQ functions, so we don't 
have to initialize it, just give it a space.

  THE HANDLER MEMBER MUST BE THE FIRST MEMBER IN THE OBJECT!

    exmp:
        struct edge{
            int prq_handler;
            int start;
            int end;
            int weight;
        }
*/


#include <stdio.h>
#include <stdlib.h>
#define PRQ_left(n) ( (((n) + 1) << 1) - 1 )
#define PRQ_right(n) ( ((n) + 1) << 1 )
#define PRQ_parent(n) ( (((n) + 1) >> 1) - 1 )

typedef struct priority_queue {
    int size;
    int max_size;
    void** data;
}   *PRQ;

PRQ PRQ_create (int max_size)
{
    if (max_size <= 0){
        printf("invalid max_size to create PRQ.\n");
        return NULL;
    }
    void** data = (void**) malloc (sizeof(void*) * max_size);
    PRQ ret = (PRQ) malloc (sizeof(struct priority_queue));
    if (data == NULL || ret == NULL){
        printf("unable to allocate PRQ.\n");
        return NULL;
    }
    ret->data = data;
    ret->max_size = max_size;
    ret->size = 0;
    return ret;
}

void PRQ_swap (void** _a, void** _b)
{
    int h_tmp = **(int**) _a;
    **(int**) _a = **(int**) _b;
    **(int**) _b = h_tmp;      //   swaping the handler here. 

    void* tmp = *_a;
    *_a = *_b;
    *_b = tmp;
}

void PRQ_heapify (PRQ Q, int n, int (*cmp)(void* prior, void* subseq))
{
    void** data = Q->data;
    int size = Q->size;
    int left = PRQ_left(n);
    int right = PRQ_right(n);
    int prior = n;

    if (right < size){
        prior = cmp(data[right], data[prior]) ? right : prior;
    }
    if (left < size){
        prior = cmp(data[left], data[prior]) ? left : prior;
    }
    if (prior != n){
        PRQ_swap(data + prior, data + n);
        PRQ_heapify(Q, prior, cmp);
    }
}

void* PRQ_top (PRQ Q)
{
    if (Q->size == 0){
        printf("PRQ empty.\n");
        return NULL;
    }
    return (Q->data)[0];
}

void* PRQ_pop (PRQ Q, int (*cmp)(void* prior, void* subseq))
{
    if (Q->size == 0){
        printf("PRQ underflow.\n");
        return NULL;
    }
    void* ret = (Q->data)[0];
    (Q->data)[0] = (Q->data)[Q->size - 1];
    Q->size --;
    PRQ_heapify(Q, 0, cmp);
    return ret;
}

void PRQ_push (PRQ Q, void* new, int (*cmp)(void* prior, void* subseq))
{
    if (Q->max_size == Q->size){
        printf("PRQ overflow.\n");
        return;
    }
    int now_idx = Q->size;
    int p_idx = PRQ_parent(now_idx);
    void** data = Q->data;

    data[ (Q->size) ++] = new;
    *(int*) new = now_idx;            // initializing handler.


    while (now_idx != 0 && cmp(data[now_idx], data[p_idx])){
        PRQ_swap(data + now_idx, data + p_idx);
        now_idx = p_idx;
        p_idx = PRQ_parent(now_idx);
    }
}

void PRQ_change_ele_maintain(PRQ Q, void* to_handle, int (*cmp)(void* prior, void* subseq))
{
    int idx = *(int*) to_handle;
    void** data = Q->data;
    int parent = PRQ_parent(idx);
    while (idx != 0) {
        if ( cmp(data[idx], data[parent]) ){
            PRQ_swap(data + parent, data + idx);
            idx = parent;
            parent = PRQ_parent(idx);
        } else {
            break;
        }
    }
    PRQ_heapify(Q, idx, cmp);
}

int PRQ_is_empty (PRQ Q)
{
    return Q->size == 0;
}

int PRQ_is_full (PRQ Q)
{
    return Q->size == Q->max_size;
}

int PRQ_get_size (PRQ Q)
{
    return Q->size;
}

void PRQ_free (PRQ Q)
{
    free(Q->data);
    free(Q);
}