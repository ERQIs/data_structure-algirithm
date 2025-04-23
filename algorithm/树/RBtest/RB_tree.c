# include <stdio.h>
# include <stdlib.h>

typedef enum coloer {Red, Black} COLOR;

typedef struct treeNode {
    struct treeNode* parent;
    struct treeNode* left;
    struct treeNode* right;
    int val;
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
    return ret;
}

RBT RBT_creat()
{
    RBT ret = malloc (sizeof(struct RBTree));

    RBT_NODE nil = malloc (sizeof(struct treeNode));
    nil->parent = nil;
    nil->color = Black;

    ret->nil = nil;
    ret->root = nil;
    return ret;
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
}

void RBT_left_rotate(RBT tree, RBT_NODE axis)
{
    RBT_NODE new_axis = axis->right;

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

void RBT_delete(RBT tree, RBT_NODE del)    //buggy!
{
    RBT_NODE dis = del;   // some node that disapeared from where it used to be
    RBT_NODE rpr;         // some node that is going to replace dis (replacer)
    COLOR dis_color = dis->color;
    if (del->left == tree->nil){
        rpr = del->right;

        printf("flag");

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
        }
        RBT_transplant(tree, del, dis);
        dis->left = del->left;  
        dis->left->parent = dis;
        dis->color = del->color;
    }
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

   printf("%d%c ", now->val, now->color == Red ? 'r' : 'b');
    show_front(tree, now->left);
    show_front(tree, now->right);    
}

int main()
{
    RBT tree = RBT_creat();
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i ++){
        int k;
        scanf("%d", &k);
        RBT_NODE new = RBT_NODE_creat(k);
        RBT_insert(tree, new);
    }
    show_front(tree, tree->root);
    scanf("%d", &n);
    for (int i = 0; i < n; i ++){
        int k;
        scanf("%d", &k);
        RBT_NODE del = RBT_search(tree, k);

        printf("left %d right %d\n", del->left->val, del->right->val);

        if (del != tree->nil){
            // RBT_transplant(tree, del, del->right);
            RBT_delete(tree, del);
            show_front(tree, tree->root);
        }
    }
    return 0;
}

//7 1 2 3 9 8 7 5 buggy when delete 5

// 1b 2b 3b 5r 7r 8b 9r
// pre 2b 1b 7r 3b 5r 8b 9r
// post 1b 5r 3b 9r 8b 7r 2b