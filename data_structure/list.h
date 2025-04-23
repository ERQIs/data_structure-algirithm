/*

    ---- DOUBLE LINKED LIST ----

This header defines a simple basic double linked list.


    ---- USAGE ----

To use this double linked list, you should define a str-
ucture that is to be put in the list. Make sure the struc-
ture you defined contains a member of type 'listNode':

    struct myNode {
        ...
        listNode node;
        ...
    }

Every structure must be initialized first:

    struct myNode* new = make_new_node();
    list_init(new);

There is no specific head node for a list, nor any kind of
abstraction for the whole list. A node (myNode) is the en-
try to the list.

followings are the interfaces that you should use (try not 
to use other functions):


    ---- INTERFACES ----

    typedef struct myNode {
        ...
        listNode node;
        ...
    }   myNode;

These interfaces are defined as macrons. It may need some
special arguments:
    type -- the name of the structure you defined (myNode)
    listNode -- the name of the member of type listNode (node)      


void list_init(myNode* node, listNode)
    -- initialization.

myNode* list_rear(myNode* node, type, listNode)
    -- get the element right behind `node`.

myNode* list_pre(myNode* node, type, listNode)
    -- get the element right before `node`.

void list_append(myNode* ptr_behind, myNode* ptr_new, listNode) 
    -- insert a new element (ptr_new) right before an 
        element (ptr_behind).

void list_add(myNode* ptr_before, myNode* ptr_new, listNode) 
    -- insert a new element (ptr_new) right behind an 
        element (ptr_before). 

void list_delete(ptr_to_be_delete, listNode)  
    -- delete an element from a list (where it's in).

*/

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h> 
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

typedef struct listNode {
    struct listNode* pre;
    struct listNode* rear;
}   listNode;

void __list_node_init(listNode* node) {
    node->pre = node;
    node->rear = node;
}

/*
insert a new node in behind of some node
*/
void __list_node_add(listNode* front, listNode* new) {
    new->pre = front;
    new->rear = front->rear;
    front->rear = new;
    new->rear->pre = new;
}

/*
insert a new node in front of some node
*/
void __list_node_append(listNode* behind, listNode* new) {
    new->rear = behind;
    new->pre = behind->pre;
    behind->pre = new;
    new->pre->rear = new;
}

void __list_node_delete(listNode* node) {
    node->pre->rear = node->rear;
    node->rear->pre = node->pre;
    __list_node_init(node);
}

#define list_init(ptr, listNode) (  \
    __list_node_init(&(ptr)->listNode) )

#define list_rear(ptr, type, listNode) (        \
    container_of((ptr)->listNode.rear, type, listNode))

#define list_pre(ptr, type, listNode) (         \
    container_of((ptr)->listNode.pre, type, listNode) )

#define list_append(ptr_behind, ptr_new, listNode) ( \
    __list_node_append(&(ptr_behind)->listNode, &(ptr_new)->listNode) )

#define list_add(ptr_front, ptr_new, listNode) (    \
    __list_node_add(&(ptr_front)->listNode, &(ptr_new)->listNode) )

#define list_delete(ptr_to_be_delete, listNode) ( \
    __list_node_delete(&(ptr_to_be_delete)->listNode) )

#define list_single(ptr_some_node, listNode) ( \
    (ptr_some_node)->listNode.rear == &(ptr_some_node)->listNode)