# include <stdio.h>
# include <stdlib.h>
# include <time.h>      // this header is used for testing code (to initialize srand())

/*

                                    RED & BLACK TREE

This is the red black tree data structure that built to show convinience to my own programming.

This version of RB_tree allows to search an elements's index or find an element by its index 
(starts from 0) from the ordered list.
This attribute is realized by maintaining information of tree size in each node (size of each 
sub-tree is recorded in the root of the sub-tree). Maintaining such attribute results in a size 
cost and time cost (O(logn) when inserting and deleting).



*************    DATA STRUCTURES (TYPES)    *************

****  RBT_NODE   (struct treeNode *)

    type of the node in red black tree.

    attributes:
        parent, left, right : Other adjacent nodes.
        val_p : this is the pointer to the element that 
                correspoeds to the node. got type (void*).
        tree_size : size of the sub tree that rooted in 
                    current node. vital to compute INDEXES.
        color : red or black.

---------------------------------------------------------

****  RBT   (struct RBT *)
    
    abstraction of the whole red and black tree

    attributes:
        nil: null, difined the same as in "Introducion to Algorithms"
        root: root of the tree. also same.


*********************************************************


****************        FUNCTIONS        ****************

FUNCTIONS FOR USER:
------------------

RBT RBT_creat()


    argument:
        (none)

    return:
        a new RBT

    function:
        creates an brand new red and black tree.

---------------------------------------------------------

RBT_NODE RBT_NODE_creat(void* v_p)


    argument:
        a pointer to some element that to be stay in 
        node. (with type void*)

    return:
        a new RBT_NODE with something you want inside it.

    function:
        creates an brand new red and black tree node with.

    how to use ?
        to use this function (which always need to), first 
        you got to innitialize an entity in the memory (something 
        that you want to manage with this RB tree), and then call
        this function with the pointer to that entity.

        example 1:

        struct student {
            char* name;
            int age;
        } erqi = {"erqi", 21};

        RBT_NODE new_node = RBT_NODE_creat( (void*)(&erqi) );

        example 2:

        int list[20];
        RBT_NODE new_node = RBT_NODE_creat( (void*)(list + 2) );

        !!!! attention !!!!
        in this case you should never change anything in list[20] 
        if you don't want to change what's inside the tree.

---------------------------------------------------------

RBT_NODE RBT_search(RBT tree, void* target_p, int (*cmp)(const void* smaller, const void* bigger))


    argument:
        tree : the tree you are going to search from.
        target_p : this is a pointer to some structure that 
                   coresponds to the node that you are going to search.
                   the structure stays in the same position with the 
                   wanted node under the full order defined by fucntion cmp.
        cmp : a function that defines a full order of all the element that 
              can be in the tree.

    return:
        some node that matches the target_value (if there are many corresponding
        nodes, it returns one randomly), if such node doesn't exist, it returns
        tree->nil. 

    function:
        This function enables to get some certain node form certain tree.

---------------------------------------------------------

void RBT_insert(RBT tree, RBT_NODE new, int (*cmp)(const void* smaller, const void* bigger))


    argument:
        tree : the tree to be inserted
        new : the new node that is going to be inserted in the tree.
        cmp : a function that defines a full order of all the element 
              that can be in the tree.

    return:
        (none)
    
    function:
        inserts a new node to the right position in the tree. Right position 
        is defined by the function cmp.
        Of courese it requires the tree to be initially ordered under cmp. 
        This function has a time cost of O(logn).

---------------------------------------------------------

int RBT_get_index (RBT tree, void* target_p, int (*cmp)(const void* smaller, const void* bigger))


    argument:
        tree : the tree to be requested.
        target_p : this is a pointer to some structure that 
                   coresponds to the node that you are going to request.
                   the structure stays in the same position with the 
                   wanted node under the full order defined by fucntion cmp.
        cmp : the function that defines a list ordering.

    return:
        the index (starts from 0) of the coresponding node if it exists.
        -1 if it doesn't exist.
    function:
        if the tree is ordered under cmp, this function can return the index 
        of the first node that corresponds to target_p. Otherwise (when there 
        is no corresponding node), it returns -1.

---------------------------------------------------------

RBT_NODE RBT_minium(RBT tree, RBT_NODE root)
RBT_NODE RBT_maximun(RBT tree, RBT_NODE root)


    argument:
        tree: the tree where you use this function.
        root: some node in the tree, the function will return the maximum
              or minimun element of the subtree that rooted in this node.

    return:
        a node which contains the largest element of the subtree.

    function:
        This function enables to inquiry the maximun or minimum node of
        the certain SUB tree.

        Specifically, to get the maximun (same when it's minimun) node
        of the hole tree, use :

            RBT_NODE max = RBT_maximun (tree, tree->root);

---------------------------------------------------------

void RBT_delete(RBT tree, RBT_NODE del)


    argument:
        tree: the tree where you want to delete something.
        del: the node that you want to delete.
            !!! MAKE SURE THIS NODE IS IN THE TREE !!!
    
    return:
        (none)
    
    function:
        deletes a node from a tree.

    !!!
        !!! MAKE SURE THIS NODE IS IN THE TREE !!!
        to get the node, you should get it FROM THE TREE.

---------------------------------------------------------

RBT_NODE RBT_successor(RBT tree, RBT_NODE node)
RBT_NODE RBT_forerunner(RBT tree, RBT_NODE node)


    argument:
        tree: the tree where the request happens.
        node: let's say this is node x.
    
    return:
        the forerunner/successor of node x. tree->nil if x doesn't have orerunner/successor node.

---------------------------------------------------------

void RBT_free (RBT tree)


    argument:
        tree: thr tree you are going to free.
    
    return:
        (none)

    function:
        frees a tree.


*/


/******************************/


typedef int *MY_TYPE;

int RBT_cmp (const void* smaller, const void* bigger)
{
    return *((MY_TYPE)smaller) <= *((MY_TYPE)bigger) ? 1 : 0;
}
/*this function should define a partially order, returns 1 when t1 <=(par) t2, 0 otherwise*/

/*****************************/

# include <stdio.h>
# include <stdlib.h>

typedef enum coloer {Red, Black} COLOR;

typedef struct treeNode {
    struct treeNode* parent;
    struct treeNode* left;
    struct treeNode* right;
    void* val_p;
    int tree_size;          /*different*/
    COLOR color;
}   *RBT_NODE;

typedef struct RBTree {
    RBT_NODE nil;
    RBT_NODE root;
}   *RBT;

RBT_NODE RBT_NODE_creat(void* v_p)
{
    RBT_NODE ret = malloc (sizeof(struct treeNode));
    ret-> val_p = v_p;
    ret->parent = NULL;
    ret->left = NULL;
    ret->right = NULL;
    ret->color = Red;
    ret->tree_size = 1;        /*different*/
    return ret;
}

RBT RBT_creat()
{
    RBT ret = malloc (sizeof(struct RBTree));

    RBT_NODE nil = malloc (sizeof(struct treeNode));
    nil->left = nil->right = nil->parent = nil;
    nil->color = Black;
    nil->tree_size = 0;    /*different*/

    ret->nil = nil;
    ret->root = nil;
    return ret;
}


/*added function*/
void RBT_size_fix(RBT tree, RBT_NODE leaf)
{
    if (leaf == tree->nil){
        return;
    }
    RBT_NODE iter = leaf->parent;
    while (iter != tree->nil){
        iter->tree_size = iter->left->tree_size + iter->right->tree_size + 1;
        iter = iter->parent;
    }
}

void RBT_transplant(RBT tree, RBT_NODE hole, RBT_NODE target)
{
    if (hole->parent == tree->nil){
        tree->root = target;
        target->parent = tree->nil;   // this is what I added
    } else if (hole == hole->parent->right){
        hole->parent->right = target;
    } else {
        hole->parent->left = target;
    }
    target->parent = hole->parent;
    if (hole->parent != tree-> nil){
        hole->parent->tree_size = hole->parent->left->tree_size + hole->parent->right->tree_size + 1;
    }
    RBT_size_fix(tree, hole->parent);         /*different*/
}

void RBT_left_rotate(RBT tree, RBT_NODE axis)
{
    RBT_NODE new_axis = axis->right;

    new_axis->tree_size += axis->left->tree_size + 1;     /*different*/
    axis->tree_size -= new_axis->right->tree_size + 1;    /*different*/

    axis->right = new_axis->left;
    if (axis->right != tree->nil){
        axis->right->parent = axis;
    }

    new_axis->parent = axis->parent;
    if (new_axis->parent == tree->nil){
        tree->root = new_axis;
    } else if (axis == axis->parent->left){
        axis->parent->left = new_axis;
    } else {
        axis->parent->right = new_axis;
    }

    new_axis->left = axis;
    axis->parent = new_axis;
}

void RBT_right_rotate(RBT tree, RBT_NODE axis)
{
    RBT_NODE new_axis = axis->left;

    new_axis->tree_size += axis->right->tree_size + 1;     /*different*/
    axis->tree_size -= new_axis->left->tree_size + 1;      /*different*/

    axis->left = new_axis->right;
    if (axis->left != tree->nil){
        axis->left->parent = axis;
    }

    new_axis->parent = axis->parent;
    if (axis->parent == tree->nil){
        tree->root = new_axis;
    } else if (axis == axis->parent->left){
        axis->parent->left = new_axis;
    } else {
        axis->parent->right = new_axis;
    }

    new_axis->right = axis;
    axis->parent = new_axis;
}

void RBT_insert_fixup(RBT tree, RBT_NODE prob)
{
    while (prob->parent->color == Red){

        if (prob->parent == prob->parent->parent->left){
            RBT_NODE uncle = prob->parent->parent->right;
            if (uncle->color == Red){
                prob->parent->color = uncle->color = Black;
                uncle->parent->color = Red;
                prob = uncle->parent;
            } else {
                if (prob == prob->parent->right){
                    prob = prob->parent;
                    RBT_left_rotate(tree, prob);
                }
                prob->parent->color = Black;
                prob->parent->parent->color = Red;
                RBT_right_rotate(tree, prob->parent->parent);
            }

        } else {

            RBT_NODE uncle = prob->parent->parent->left;
            if (uncle->color == Red){
                prob->parent->color = uncle->color = Black;
                uncle->parent->color = Red;
                prob = uncle->parent;
            } else {
                if (prob == prob->parent->left){
                    prob = prob->parent;
                    RBT_right_rotate(tree, prob);
                }
                prob->parent->color = Black;
                prob->parent->parent->color = Red;
                RBT_left_rotate(tree, prob->parent->parent);
            }

        }

    }
    tree->root->color = Black;
}

RBT_NODE RBT_search(RBT tree, void* target_p, int (*cmp)(const void* smaller, const void* bigger))
{
    RBT_NODE cur = tree->root;
    while (cur != tree->nil){
        int cur_val_le_tar_val = cmp(cur->val_p, target_p);
        int tar_val_le_cur_val = cmp(target_p, cur->val_p);
        if (cur_val_le_tar_val == 1 && tar_val_le_cur_val == 1){    
            return cur;
        } else if (tar_val_le_cur_val == 1){
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }
    return tree->nil;
}

void RBT_insert(RBT tree, RBT_NODE new, int (*cmp)(const void* smaller, const void* bigger))
{
    RBT_NODE parent = tree->nil, cur = tree->root;
    while (cur != tree->nil){
        parent = cur;
        if (cmp(cur->val_p, new->val_p) == 1){
            cur = cur->right;
        } else {
            cur = cur->left;
        }

    }
    if (parent == tree->nil){
        tree->root = new;
    } else if (cmp(parent->val_p, new->val_p) == 1){
        parent->right = new;
    } else {
        parent->left = new;
    }

    new->parent = parent;
    new->left = tree->nil;
    new->right = tree->nil;
    new->color = Red;

    RBT_size_fix(tree, new);     /*different*/
    RBT_insert_fixup(tree, new);
}

RBT_NODE RBT_minium(RBT tree, RBT_NODE root)
{
    if (root == tree->nil)
        return tree->nil;
    while (root->left != tree->nil){
        root = root->left;
    }
    return root;
}
RBT_NODE RBT_maximun(RBT tree, RBT_NODE root)
{
    register RBT_NODE p = root;
    register RBT_NODE nil = tree->nil;
    if (p == nil)
        return nil;

    register RBT_NODE right = p->right;
    while (right != nil){
        p = right;
        right = p->right;
    }
    
    return p;
}

void RBT_delete_fixup(RBT tree, RBT_NODE BB/* it means double black*/)
{
    while (BB != tree->root && BB->color == Black){
        if (BB == BB->parent->left){
            RBT_NODE brother = BB->parent->right;
            if (brother->color == Red){
                brother->color = Black;
                BB->parent->color = Red;
                RBT_left_rotate(tree, BB->parent);
                brother = BB->parent->right;
            }
            if (brother->left->color == Black && brother->right->color == Black){
                brother->color = Red;
                BB = BB->parent;
            } else {
                if (brother->right->color == Black){
                    brother->left->color = Black;
                    brother->color = Red;
                    RBT_right_rotate(tree, brother);
                    brother = BB->parent->right;
                }
                brother->color = BB->parent->color;
                BB->parent->color = Black;
                brother->right->color = Black;
                RBT_left_rotate(tree, BB->parent);
                BB = tree->root;
            }
        } else {
            RBT_NODE brother = BB->parent->left;
            if (brother->color == Red){
                brother->color = Black;
                BB->parent->color = Red;
                RBT_right_rotate(tree, BB->parent);
                brother = BB->parent->left;
            }
            if (brother->right->color == Black && brother->left->color == Black){
                brother->color = Red;
                BB = BB->parent;
            } else {
                if (brother->left->color == Black){
                    brother->right->color = Red;
                    RBT_left_rotate(tree, brother);
                    brother = BB->parent->left;
                }
                brother->color = BB->parent->color;
                BB->parent->color = Black;
                brother->left->color = Black;
                RBT_right_rotate(tree, BB->parent);
                BB = tree->root;
            }
        }
    }
    BB->color = Black;
}

void RBT_delete(RBT tree, RBT_NODE del)    //buggy! (now it seems fine)
{
    RBT_NODE dis = del;   // some node that disapeared from where it used to be
    RBT_NODE rpr;         // some node that is going to replace dis (replacer)
    COLOR dis_color = dis->color;
    if (del->left == tree->nil){
        rpr = del->right;
        RBT_transplant(tree, del, del->right);
    } else if (del->right == tree->nil){
        rpr = del->left;
        RBT_transplant(tree, del, del->left);
    } else {
        dis = RBT_minium(tree, del->right);    //here once was a bug

        dis_color = dis->color;
        rpr = dis->right;
        if (dis->parent == del){
            rpr->parent = dis;
        } else {
            RBT_transplant(tree, dis, dis->right);
            dis->right = del->right;
            dis->right->parent = dis;
            
            del->right->tree_size = del->right->right->tree_size + del->right->left->tree_size + 1;   /*different*/
            dis->tree_size = dis->left->tree_size + dis->right->tree_size + 1;       /*different*/

        }
        RBT_transplant(tree, del, dis);
        dis->left = del->left;  
        dis->left->parent = dis;
        dis->tree_size = dis->left->tree_size + dis->right->tree_size + 1;   /*different*/
        dis->color = del->color;
    }

    if (del->parent != tree->nil) {      /*different*/
        del->parent->tree_size = del->parent->left->tree_size + del->parent->right->tree_size + 1;        /*bug fixed*/
        RBT_size_fix(tree, del->parent);    
    }                 /*different*/

    if (dis_color == Black){
        RBT_delete_fixup(tree, rpr);
    }
    free(del);
}

RBT_NODE RBT_successor(RBT tree, RBT_NODE node)
{
    if (node->right != tree->nil){
        return RBT_minium(tree, node->right);
    }
    RBT_NODE p = node->parent;
    while (p != tree->nil && node == p->right){
        node = p;
        p = node->parent;
    }
    return p;
}

RBT_NODE RBT_forerunner(RBT tree, RBT_NODE node)
{
    if (node->left != tree->nil){
        return RBT_maximun(tree, node->left);
    }
    RBT_NODE p = node->parent;
    while (p != tree->nil && node == p->left){
        node = p;
        p = node->parent;
    }
    return p;
}


/*different function*/
int RBT_get_index (RBT tree, void* target_p, int (*cmp)(const void* smaller, const void* bigger))
{
    RBT_NODE cur = tree->root;
    int idx = 0;
    while (cur != tree->nil){
        int cur_val_le_tar_val = cmp(cur->val_p, target_p);
        int tar_val_le_cur_val = cmp(target_p, cur->val_p);
             
        RBT_NODE fore = RBT_forerunner(tree, cur);
        if (cur_val_le_tar_val && tar_val_le_cur_val &&       // current node value equal to target
            !(fore != tree->nil && cmp(fore->val_p, target_p) && cmp(target_p, fore->val_p))){
                    idx += cur->left->tree_size; // except for current node has a forerunner f and f's value equal to target
                    return idx;                  // this is to return index of the first value when there are same values in the tree
        } else if (tar_val_le_cur_val){
            cur = cur->left;
        } else {
            idx += cur->left->tree_size + 1;
            cur = cur->right;
        }
    }
    return -1;
}

void RBT_free_tree_iter(RBT_NODE now, RBT_NODE nil){
    if (now == nil){
        return;
    }
    if (now->left != nil){
        RBT_free_tree_iter(now->left, nil);
    }
    if (now->right != nil){
        RBT_free_tree_iter(now->right, nil);
    }
    if (now->parent != nil){
        if (now == now->parent->left){
            now->parent->left = nil;
        } else {
            now->parent->right = nil;
        }
    }
    free(now);
}

void RBT_free (RBT tree){
    RBT_free_tree_iter(tree->root, tree->nil);
    free(tree->nil);
    free(tree);
}

RBT_NODE RBT_search_index (RBT tree, int i)
{
    RBT_NODE now_node = tree->root;
    if (now_node == tree->nil || tree->root->tree_size <= i){
        return tree->nil;
    }
    int now_idx = now_node->left->tree_size;
    while (now_idx != i){
        if (i < now_idx){
            now_idx -= now_node->left->right->tree_size + 1;
            now_node = now_node->left;
        } else {
            now_idx += now_node->right->left->tree_size + 1;
            now_node = now_node->right;
        }
    }
    return now_node;
}

void RBT_insert_before (RBT tree, RBT_NODE refer, RBT_NODE new)
{
    new->left = new->right = tree->nil;
    if (refer->left == tree->nil){
        refer->left = new;
        new->parent = refer;
    } else {
        RBT_NODE pos = RBT_maximun(tree, refer->left);
        pos->right = new;
        new->parent = pos;
    }
    RBT_size_fix(tree, new);
    RBT_insert_fixup(tree, new);
}

void RBT_insert_after (RBT tree, RBT_NODE refer, RBT_NODE new)
{
    new->left = new->right = tree->nil;
    if (refer->right == tree->nil){
        refer->right = new;
        new->parent = refer;
    } else {
        RBT_NODE pos = RBT_minium(tree, refer->right);
        pos->left = new;
        new->parent = pos;
    }
    RBT_size_fix(tree, new);
    RBT_insert_fixup(tree, new);
}