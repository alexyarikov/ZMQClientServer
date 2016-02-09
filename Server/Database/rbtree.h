#ifndef RBTREE_H_
#define RBTREE_H_

#include "../main.h"

// color enum
enum rbtree_color
{
    RED, BLACK
};

// compare function
typedef int(*compare_func)(void* left, void* right);

// tree node
struct rbtree_node
{
    void *data;
    struct rbtree_node *left;
    struct rbtree_node *right;
    struct rbtree_node *parent;
    enum rbtree_color color;
};

// tree
struct rbtree
{
    struct rbtree_node *root;
    uint64_t count;
    compare_func compare;
};

// functions
struct rbtree *rbtree__create(compare_func compare);
void rbtree__destroy(struct rbtree *t, bool free_data);
void *rbtree__lookup(struct rbtree *t, void *data);
void *rbtree__insert(struct rbtree *t, void *data, bool *exist);
void *rbtree__delete(struct rbtree *t, void *data);
uint64_t rbtree__count(struct rbtree *t);
uint64_t rbtree__range_count(struct rbtree *t, void *data_min, void *data_max);

#endif /* RBTREE_H */
