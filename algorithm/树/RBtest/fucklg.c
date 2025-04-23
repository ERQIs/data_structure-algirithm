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

// void show_front(RBT tree, RBT_NODE now)
// {
//     if (now == tree->nil){
//         return;
//     }

//     printf("%d size: %d   ", now->val, now->tree_size);
//     show_front(tree, now->left);
//     show_front(tree, now->right);    
// }

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

// void show_name_iter(RBT tree, RBT_NODE root)
// {
//     if (root == tree->nil){
//         return;
//     }
//     show_name_iter(tree, root->left);
//     printf("%s\n", (char*)(root->val_p));
//     show_name_iter(tree, root->right);
// }

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

int main()
{
    int n, m, q;
    scanf("%d", &n);

    RBT tree = RBT_creat();

    char* newBook = (char*) malloc (sizeof(char) * 11);
    scanf("%s", newBook);
    RBT_NODE newNode = RBT_NODE_creat( (void*)newBook );
    tree->root = newNode;
    newNode->left = newNode->right = newNode->parent  = tree->nil;
    newNode->color = Black;

    for (int i = 1; i < n; i ++){

        char* newBook = (char*) malloc (sizeof(char) * 11);
        scanf("%s", newBook);
        RBT_NODE newNode = RBT_NODE_creat( (void*)newBook );

        RBT_NODE max = RBT_maximun(tree, tree->root);
        RBT_insert_after(tree, max, newNode);

    }

    scanf("%d", &m);

    for (int i = 0; i < m; i ++){

        int idx;
        char* newBook = (char*) malloc (sizeof(char) * 11);
        scanf("%s", newBook);
        RBT_NODE newNode = RBT_NODE_creat( (void*)newBook );
        scanf("%d", &idx);
        RBT_NODE refer = RBT_search_index (tree, idx);
        if (refer == tree->nil) {
            RBT_insert_after(tree, RBT_maximun(tree, tree->root), newNode);
        } else {
            RBT_insert_before(tree, refer, newNode);
        }
    }

    scanf("%d", &q);

    for (int i = 0; i < q; i ++){
        int idx;
        scanf("%d", &idx);
        printf("%s\n", (char*)(RBT_search_index(tree, idx)->val_p));
    }
    return 0;
}