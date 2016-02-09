#include "rbtree.h"
// relations
struct rbtree_node *grandparent(struct rbtree_node *n);
struct rbtree_node *sibling(struct rbtree_node *n);
struct rbtree_node *uncle(struct rbtree_node *n);
// node actions
struct rbtree_node *new_node(void *data, enum rbtree_color color);
void free_node(struct rbtree_node *node, bool free_data);
struct rbtree_node *lookup_node(struct rbtree *t, void *data);
void range_count(struct rbtree *t, struct rbtree_node *n, void *data_min, void *data_max, uint64_t *count);
void rotate_left(struct rbtree *t, struct rbtree_node *n);
void rotate_right(struct rbtree *t, struct rbtree_node *n);
struct rbtree_node *previous_node(struct rbtree_node *root);
void replace_node(struct rbtree *t, struct rbtree_node *oldn, struct rbtree_node *newn);
enum rbtree_color node_color(struct rbtree_node *n);
// balancing
void insert_case1(struct rbtree *t, struct rbtree_node *n);
void insert_case2(struct rbtree *t, struct rbtree_node *n);
void insert_case3(struct rbtree *t, struct rbtree_node *n);
void insert_case4(struct rbtree *t, struct rbtree_node *n);
void insert_case5(struct rbtree *t, struct rbtree_node *n);
void delete_case1(struct rbtree *t, struct rbtree_node *n);
void delete_case2(struct rbtree *t, struct rbtree_node *n);
void delete_case3(struct rbtree *t, struct rbtree_node *n);
void delete_case4(struct rbtree *t, struct rbtree_node *n);
void delete_case5(struct rbtree *t, struct rbtree_node *n);
void delete_case6(struct rbtree *t, struct rbtree_node *n);

// create tree
struct rbtree *rbtree__create(compare_func compare)
{
    assert(compare);

    struct rbtree *t = malloc(sizeof(struct rbtree));
    t->root = NULL;
    t->compare = compare;
    t->count = 0;
    return t;
}

// destroy tree
void rbtree__destroy(struct rbtree *t, bool free_data)
{
    assert(t);
    free_node(t->root, free_data);
}

// lookup node
void *rbtree__lookup(struct rbtree *t, void *data)
{
    struct rbtree_node *n = lookup_node(t, data);
    return n == NULL ? NULL : n->data;
}

// insert node, returns pointer to newly inserted data or pointer to existing data in case of data exists
void *rbtree__insert(struct rbtree *t, void* data, bool *exist)
{
    assert(t);
    assert(t->compare);
    assert(data);

    // clear result
    struct rbtree_node *ptr = NULL;
    if (exist)
        *exist = false;

    // if no root create it
    if (!t->root)
        t->root = ptr = new_node(data, RED);
    else
    {
        // search insert point
        struct rbtree_node *n = t->root;
        while (true)
        {
            int comp_result = t->compare(data, n->data);
            if (comp_result == 0)
            {
                // update node, raise data exists flag
                if (exist)
                    *exist = true;
                // update node data and return pointer to existing data
                void *ptr = n->data;
                n->data = data;
                return ptr;
            }
            else if (comp_result < 0)
            {
                // search in left subtree
                if (n->left == NULL)
                {
                    n->left = ptr = new_node(data, RED);
                    break;
                }
                else
                    n = n->left;
            }
            else
            {
                // search in right subtree
                if (n->right == NULL)
                {
                    n->right = ptr = new_node(data, RED);
                    break;
                }
                else
                    n = n->right;
            }
        }

        assert(ptr);
        ptr->parent = n;
    }

    // update items count
    t->count++;

    // balance tree
    insert_case1(t, ptr);

    return (ptr->data);
}

// delete tree node, returns pointer to data of deleted node
void *rbtree__delete(struct rbtree *t, void *data)
{
    assert(t);

    void *res = NULL;

    // lookup node, return if not found
    struct rbtree_node *n = lookup_node(t, data);
    if (n == NULL)
        return NULL;

    // save data
    res = n->data;

    // if there are two children, search previous in-order data node, copy data and delete it instead
    if (n->left && n->right)
    {
        struct rbtree_node *max = previous_node(n->left);
        assert(max);
        n->data = max->data;
        n = max;
    }

    // one (or both) of children should be a leaf
    assert(!n->left || !n->right);

    // get any non-leaf child
    struct rbtree_node *child = n->right == NULL ? n->left : n->right;

    // balance
    if (node_color(n) == BLACK)
    {
        n->color = node_color(child);
        delete_case1(t, n);
    }

    // replace deleting node with its non-leaf child
    replace_node(t, n, child);

    // root should be black
    if (n->parent == NULL && child != NULL)
        child->color = BLACK;

    // free rbtree_node and update items count
    free(n);
    t->count--;

    return res;
}

// get tree items count
uint64_t rbtree__count(struct rbtree *t)
{
    assert(t);
    return t->count;
}

// get count of nodes in data range
uint64_t rbtree__range_count(struct rbtree *t, void *data_min, void *data_max)
{
    assert(t);
    assert(t->compare);
    assert(data_min);
    assert(data_max);

    uint64_t res = 0;
    range_count(t, t->root, data_min, data_max, &res);

    return res;
}

// get grandparent node
struct rbtree_node *grandparent(struct rbtree_node *n)
{
    assert(n);
    assert(n->parent);
    assert(n->parent->parent);
    return n->parent->parent;
}

// get uncle node
struct rbtree_node *uncle(struct rbtree_node *n)
{
    assert(n);
    assert(n->parent);
    assert(n->parent->parent);
    return sibling(n->parent);
}

// get sibling node
struct rbtree_node *sibling(struct rbtree_node *n)
{
    assert(n);
    assert(n->parent);
    if (n == n->parent->left)
        return n->parent->right;
    else
        return n->parent->left;
}

// create a new node
struct rbtree_node *new_node(void *data, enum rbtree_color color)
{
    struct rbtree_node *result = malloc(sizeof(struct rbtree_node));
    result->data = data;
    result->color = color;
    result->left = NULL;
    result->right = NULL;
    result->parent = NULL;
    return result;
}

// free node
void free_node(struct rbtree_node *node, bool free_data)
{
    if (!node)
        return;

    free_node(node->left, free_data);
    node->left = NULL;

    free_node(node->right, free_data);
    node->right = NULL;

    free(node->data);
    node->data = NULL;

    node->parent = NULL;
    free(node);
}

// lookup node
struct rbtree_node *lookup_node(struct rbtree *t, void *data)
{
    assert(t);
    assert(t->compare);
    assert(data);

    struct rbtree_node *n = t->root;
    while (n)
    {
        int comp_result = t->compare(data, n->data);
        if (comp_result == 0)
            return n;
        else if (comp_result < 0)
            n = n->left;
        else
            n = n->right;
    }
    return n;
}

// get count of nodes in data range
void range_count(struct rbtree *t, struct rbtree_node *n, void *data_min, void *data_max, uint64_t *count)
{
    // go through tree, lookup range
    if (!n)
        return;

    int comp_min = t->compare(n->data, data_min);
    int comp_max = t->compare(n->data, data_max);

    // if data < min search in the left subtree
    if (comp_min > 0)
        range_count(t, n->left, data_min, data_max, count);

    // if data in range add it to iterator list
    if (comp_min >= 0 && comp_max <= 0)
        (*count)++;

    // if data > max search in the right subtree
    if (comp_max < 0)
        range_count(t, n->right, data_min, data_max, count);
}

// rotate node left
void rotate_left(struct rbtree *t, struct rbtree_node *n)
{
    assert(n);

    struct rbtree_node *r = n->right;
    replace_node(t, n, r);
    n->right = r->left;

    if (r->left)
        r->left->parent = n;

    r->left = n;
    n->parent = r;
}

// rotate node right
void rotate_right(struct rbtree *t, struct rbtree_node *n)
{
    assert(n);

    struct rbtree_node *l = n->left;
    replace_node(t, n, l);
    n->left = l->right;

    if (l->right)
        l->right->parent = n;

    l->right = n;
    n->parent = l;
}

// get previous order-in node
struct rbtree_node *previous_node(struct rbtree_node *n)
{
    assert(n);
    while (n->right)
        n = n->right;
    return n;
}

// replace node
void replace_node(struct rbtree *t, struct rbtree_node *old_node, struct rbtree_node *new_node)
{
    assert(t);
    assert(old_node);

    // update old node parent's child pointer
    if (!old_node->parent)
        t->root = new_node;
    else
    {
        if (old_node == old_node->parent->left)
            old_node->parent->left = new_node;
        else
            old_node->parent->right = new_node;
    }

    // update new node parent
    if (new_node)
        new_node->parent = old_node->parent;
}

// get color of node
enum rbtree_color node_color(struct rbtree_node *n)
{
    return n == NULL ? BLACK : n->color;
}

// insert case 1
void insert_case1(struct rbtree *t, struct rbtree_node *n)
{
    assert(n);
    if (n->parent == NULL)
        n->color = BLACK;
    else
        insert_case2(t, n);
}

// insert case 2
void insert_case2(struct rbtree *t, struct rbtree_node *n)
{
    assert(n);
    if (node_color(n->parent) == BLACK)
        return;
    else
        insert_case3(t, n);
}

// insert case 3
void insert_case3(struct rbtree *t, struct rbtree_node *n)
{
    assert(n);
    if (node_color(uncle(n)) == RED)
    {
        n->parent->color = BLACK;
        uncle(n)->color = BLACK;
        grandparent(n)->color = RED;
        insert_case1(t, grandparent(n));
    }
    else
        insert_case4(t, n);
}

// insert case 4
void insert_case4(struct rbtree *t, struct rbtree_node *n)
{
    assert(n);
    assert(n->parent);

    if (n == n->parent->right && n->parent == grandparent(n)->left)
    {
        rotate_left(t, n->parent);
        n = n->left;
    }
    else if (n == n->parent->left && n->parent == grandparent(n)->right)
    {
        rotate_right(t, n->parent);
        n = n->right;
    }
    insert_case5(t, n);
}

// insert case 5
void insert_case5(struct rbtree *t, struct rbtree_node *n)
{
    assert(n);
    assert(n->parent);

    n->parent->color = BLACK;
    grandparent(n)->color = RED;
    if (n == n->parent->left && n->parent == grandparent(n)->left)
        rotate_right(t, grandparent(n));
    else
    {
        assert(n == n->parent->right && n->parent == grandparent(n)->right);
        rotate_left(t, grandparent(n));
    }
}

// delete case 1
void delete_case1(struct rbtree *t, struct rbtree_node *n)
{
    assert(n);

    if (n->parent == NULL)
        return;
    else
        delete_case2(t, n);
}

// delete case 2
void delete_case2(struct rbtree *t, struct rbtree_node *n)
{
    assert(n);

    if (node_color(sibling(n)) == RED)
    {
        n->parent->color = RED;
        sibling(n)->color = BLACK;
        if (n == n->parent->left)
            rotate_left(t, n->parent);
        else
            rotate_right(t, n->parent);
    }
    delete_case3(t, n);
}

// delete case 3
void delete_case3(struct rbtree *t, struct rbtree_node *n)
{
    assert(n);

    if (node_color(n->parent) == BLACK && node_color(sibling(n)) == BLACK && node_color(sibling(n)->left) == BLACK && node_color(sibling(n)->right) == BLACK)
    {
        sibling(n)->color = RED;
        delete_case1(t, n->parent);
    }
    else
        delete_case4(t, n);
}

// delete case 4
void delete_case4(struct rbtree *t, struct rbtree_node *n)
{
    assert(n);

    if (node_color(n->parent) == RED && node_color(sibling(n)) == BLACK && node_color(sibling(n)->left) == BLACK && node_color(sibling(n)->right) == BLACK)
    {
        sibling(n)->color = RED;
        n->parent->color = BLACK;
    }
    else
        delete_case5(t, n);
}

// delete case 5
void delete_case5(struct rbtree *t, struct rbtree_node *n)
{
    assert(n);
    assert(n->parent);

    if (n == n->parent->left && node_color(sibling(n)) == BLACK && node_color(sibling(n)->left) == RED && node_color(sibling(n)->right) == BLACK)
    {
        sibling(n)->color = RED;
        sibling(n)->left->color = BLACK;
        rotate_right(t, sibling(n));
    }
    else if (n == n->parent->right && node_color(sibling(n)) == BLACK && node_color(sibling(n)->right) == RED && node_color(sibling(n)->left) == BLACK)
    {
        sibling(n)->color = RED;
        sibling(n)->right->color = BLACK;
        rotate_left(t, sibling(n));
    }
    delete_case6(t, n);
}

// deletecase 6
void delete_case6(struct rbtree *t, struct rbtree_node *n)
{
    assert(n);
    assert(n->parent);

    sibling(n)->color = node_color(n->parent);
    n->parent->color = BLACK;
    if (n == n->parent->left)
    {
        assert(node_color(sibling(n)->right) == RED);
        sibling(n)->right->color = BLACK;
        rotate_left(t, n->parent);
    }
    else
    {
        assert(node_color(sibling(n)->left) == RED);
        sibling(n)->left->color = BLACK;
        rotate_right(t, n->parent);
    }
}
