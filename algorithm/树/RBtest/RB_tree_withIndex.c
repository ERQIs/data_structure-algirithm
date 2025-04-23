# include <stdio.h>
# include <stdlib.h>
# include <time.h>

typedef enum coloer {Red, Black} COLOR;

typedef struct treeNode {
    struct treeNode* parent;
    struct treeNode* left;
    struct treeNode* right;
    int val;
    int tree_size;          /*different*/
    COLOR color;
}   *RBT_NODE;

typedef struct RBTree {
    RBT_NODE nil;
    RBT_NODE root;
}   *RBT;

RBT_NODE RBT_NODE_creat(int v)
{
    RBT_NODE ret = malloc (sizeof(struct treeNode));
    ret-> val = v;
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

RBT_NODE RBT_search(RBT tree, int target)
{
    RBT_NODE cur = tree->root;
    while (cur != tree->nil){
        if (cur->val == target){
            return cur;
        } else if (target < cur->val){
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }
    return NULL;
}

void RBT_insert(RBT tree, RBT_NODE new)
{
    RBT_NODE parent = tree->nil, cur = tree->root;
    while (cur != tree->nil){
        parent = cur;
        if (new->val > cur->val){
            cur = cur->right;
        } else {
            cur = cur->left;
        }

    }
    if (parent == tree->nil){
        tree->root = new;
    } else if (new->val > parent->val){
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
    if (root == tree->nil)
        return tree->nil;
    while (root->right != tree->nil){
        root = root->right;
    }
    return root;
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

void show_front(RBT tree, RBT_NODE now)
{
    if (now == tree->nil){
        return;
    }

    printf("%d size: %d   ", now->val, now->tree_size);
    show_front(tree, now->left);
    show_front(tree, now->right);    
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
int RBT_get_index (RBT tree, int target)
{
    RBT_NODE cur = tree->root;
    int idx = 0;
    while (cur != tree->nil){
        if (cur->val == target && RBT_forerunner(tree, cur)->val != target){   /*attention! this is buggy!*/
            idx += cur->left->tree_size;                                       /*forerunner may not exist! (nil returned)*/
            return idx;
        } else if (target <= cur->val){
            cur = cur->left;
        } else {
            idx += cur->left->tree_size + 1;
            cur = cur->right;
        }
    }
    return 0x80000000;
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

// int main()
// {
//     RBT tree = RBT_creat();
//     int n;
//     scanf("%d", &n);
//     for (int i = 0; i < n; i ++){
//         int k;
//         scanf("%d", &k);
//         RBT_NODE new = RBT_NODE_creat(k);
//         RBT_insert(tree, new);
//     }
//     show_front(tree, tree->root);
//     scanf("%d", &n);
//     for (int i = 0; i < n; i ++){
//         int k;
//         scanf("%d", &k);
//         RBT_NODE del = RBT_search(tree, k);

//     //    printf("left %d right %d\n", del->left->val, del->right->val);

//         if (del != tree->nil){
//             // RBT_transplant(tree, del, del->right);
//             RBT_delete(tree, del);
//             show_front(tree, tree->root);
//         }
//     }
//     return 0;
// }

int cmp (const void* a, const void* b){
    return * (int*) a > * (int*) b ? 1 : -1;
}

RBT_NODE bug;

int* test_set;
int* unordered;

int main()
{
    // int n;
    // scanf("%d", &n);
    // for (int i = 0; i < n; i ++){
    //     int k;
    //     scanf("%d", &k);
    //     RBT_NODE new = RBT_NODE_creat(k);
    //     RBT_insert(tree, new);
    // }
    // show_front(tree, tree->root);
    // scanf("%d", &n);
    // for (int i = 0; i < n; i ++){
    //     int k;
    //     scanf("%d", &k);
    //     int idx = RBT_get_index(tree, k);
    //     printf("%d\n", idx);
    // }


    int set_n = 1000;
    int tree_size = 4000;
    int max_elem = 1000;

    test_set = (int*) malloc (sizeof(int) * tree_size);
    unordered = (int*) malloc (sizeof(int) * tree_size);

    srand((unsigned) time(NULL));
    for (int set = 0; set < set_n; set ++){

        int flag = 1;

        RBT tree = RBT_creat();
        for (int i = 0; i < tree_size; i ++){
            test_set[i] = rand() % max_elem;
            unordered[i] = test_set[i];
            RBT_NODE new = RBT_NODE_creat(test_set[i]);
            RBT_insert(tree, new);
        }

        qsort(test_set, tree_size, sizeof(int), cmp);

        int delete_seg = tree_size/2;
        for (int i = 0; i < delete_seg; i ++){
            RBT_NODE del = RBT_search(tree, test_set[i]);
            RBT_delete(tree, del);
        }

        for (int i = delete_seg; i < tree_size; i ++){
            if (RBT_get_index(tree, test_set[i]) != i - delete_seg && test_set[i] != test_set[i - 1]){
                printf("error occured %d %d\n", test_set[i], test_set[i + 1]);
                printf("%d %d\n", RBT_get_index(tree, test_set[i]), RBT_get_index(tree, test_set[i + 1]));
                // for (int j = 0; j < tree_size; j ++){
                //     printf("%d, ", test_set[j]);
                // }
                // putchar('\n');
                // for (int j = 0; j < tree_size; j ++){
                //     printf("%d, ", unordered[j]);
                // }
                // putchar('\n');
                flag = 0;
                break;
            }
            // printf("%d ", RBT_get_index(tree, test_set[i]));
        }

        if (flag){
            printf("set %d completed successfully\n", set);
        } else {
            break;
        }
        // putchar('\n');
        RBT_free(tree);
    }


//     int test_set[8] = {1, 1, 1, 4, 4, 4, 4, 5};
//     RBT tree = RBT_creat();
//     for (int i = 0; i < 8; i ++){
//         RBT_NODE new = RBT_NODE_creat(test_set[i]);
//         RBT_insert(tree, new);
//     }

//     int delete_list[2] = {1, 4};
//     for (int i = 0; i < 2; i ++){
//         RBT_NODE del = RBT_search(tree, delete_list[i]);
//         RBT_delete(tree, del);
//     }

//     int left_list[6] = {1, 1, 4, 4, 4, 5};
//     for (int i = 0; i < 6; i ++){
//         printf("%d ", RBT_get_index(tree, left_list[i]));
//     }
//     putchar('\n');
//     show_front(tree, tree->root);
// //   printf("%d %d\n", RBT_search(tree, 3)->left->val, RBT_search(tree, 3)->right->val);
//     putchar('\n');
//     RBT_free(tree);

    return 0;
}