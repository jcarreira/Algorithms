/***************************************************************************
 *   Copyright (C) 2007 by Joao Carreira
 *
 *  This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#ifdef DEBUG
#include <stdio.h>
#endif

#include <assert.h>
#include <stdlib.h>
#include "rbt_item.h"
#include "rbt.h"

#define SENTINEL &dummy
#define max(a,b) ((a)>(b)?(a):(b))

static void left_rotate( Rbt_tree_link, Rbtlink );
static void right_rotate( Rbt_tree_link, Rbtlink );
static void rbt_delete_fixup( Rbt_tree_link, Rbtlink );
static void rbt_insert_fixup( Rbt_tree_link, Rbtlink );
static void rbt_destroy_link( Rbtlink );
static Rbtlink rbt_minimum_link( Rbtlink );
static Rbtlink rbt_maximum_link( Rbtlink );
static Rbtlink new_rbt_node( Rbtitem );
static void free_rbt_node( Rbtlink );
static void rbt_inorder_link( Rbtlink, void (*)(Rbtlink) );
static void rbt_preorder_link( Rbtlink, void (*)(Rbtlink) );
static void rbt_postorder_link( Rbtlink, void (*)(Rbtlink) );
static int assert_link( Rbtlink, int* );
static int rbt_height_link( Rbtlink );

typedef enum color { BLACK = 1,RED } Color;

typedef struct rbtnode{
    Rbtlink l,r,p;
    Color color;
    Rbtitem item;
}Rbtnode;

typedef struct rbt {
    int count_elements;
    Rbtlink root;
}Rbt;

static Rbtnode dummy = {0,0,0, BLACK};

#ifdef DEBUG
int num_allocs = 0;
#endif

int rbt_size(Rbt_tree_link rbt) {
    return rbt->count_elements;
}

Rbt_tree_link rbt_create() {
    Rbt_tree_link new_rbt = (Rbt_tree_link) malloc(sizeof(struct rbt));
    assert(new_rbt);

    new_rbt->count_elements = 0;
    new_rbt->root = SENTINEL;
    return new_rbt;
}

static Rbtlink new_rbt_node(Rbtitem item) {
    Rbtlink new = (Rbtlink) malloc(sizeof(struct rbtnode));
    assert(new);
    assign(&(new->item), item);
    new->p = new->l = new->r = SENTINEL;
#ifdef DEBUG
    num_allocs++;
#endif
    return new;
}

Rbtitem rbt_item(Rbtlink rbt) {
    return rbt->item;
}

int rbt_height(Rbt_tree_link rbt) {
    return rbt_height_link(rbt->root);
}

    static int rbt_height_link(Rbtlink link) {
	if(link == SENTINEL)
	    return 0;
	else return max(rbt_height_link(link->l), rbt_height_link(link->r)) + 1;
    }

Rbtlink rbt_minimum(Rbt_tree_link rbt) {
    return rbt_minimum_link(rbt->root);
}

static Rbtlink rbt_minimum_link(Rbtlink link) {
    Rbtlink p = SENTINEL;
    while(link != SENTINEL) {
	p = link;
	link = link->l;
    }	
    return p;
}

Rbtlink rbt_maximum( Rbt_tree_link rbt ) {
    return rbt_maximum_link(rbt->root);
}

static Rbtlink rbt_maximum_link( Rbtlink link ) {
    Rbtlink p = SENTINEL;
    while(link != SENTINEL) {
	p = link;
	link = link->r;
    }	
    return p;
}

void rbt_delete(Rbt_tree_link rbt, Rbtitem item) {
    Rbtlink z = rbt_search(rbt, item);
    Rbtlink y, x;

    if(z == NULL_RBT_ITEM)
	return;

    if(z->l == SENTINEL || z->r == SENTINEL)
	y = z;
    else y = rbt_sucessor(z);

    if(y->l != SENTINEL)
	x = y->l;
    else x = y->r;

    x->p = y->p;

    if(y->p == SENTINEL)
	rbt->root = x;
    else if(y == y->p->l)
	y->p->l = x;
    else y->p->r = x;

    Color old_color = y->color; 
    if(y != z) { 
	assign(&(z->item), y->item);
	free_rbt_node(y);
    } else free_rbt_node(z);

    if(old_color == BLACK) rbt_delete_fixup(rbt, x);

    rbt->count_elements--;  /*  number of elements has decreased   */
}

void rbt_insert(Rbt_tree_link rbt, Rbtitem item) {
    Rbtlink z;
    Rbtlink link = rbt->root, p = SENTINEL;

    while(link != SENTINEL) {
	p = link;
	if(cmp(item, link->item) < 0)
	    link = link->l;
	else if(cmp(item, link->item) > 0)
	    link = link->r;
	else return;
    }

    z = new_rbt_node(item);
    z->p = p;
    z->color = RED;
    z->l = z->r = SENTINEL;

    if(p == SENTINEL) {
	rbt->root = z;
	z->color = BLACK;
    } else {
	if(cmp(item, p->item) < 0)
	    p->l = z;
	else p->r = z;
    }

    rbt_insert_fixup(rbt, z);
    rbt->count_elements++;   /*   number of elements has increased   */
}

void rbt_inorder(Rbt_tree_link rbt, void (*func)(Rbtlink a)) {
    rbt_inorder_link(rbt->root, func);
}

static void rbt_inorder_link(Rbtlink link, void (*func)(Rbtlink a)) {
    if(link != SENTINEL) {
	rbt_inorder_link(link->l, func);
	func(link);
	rbt_inorder_link(link->r,func);
    }
}

void rbt_preorder(Rbt_tree_link rbt, void (*func)(Rbtlink a)) {
    rbt_preorder_link(rbt->root, func);
}

static void rbt_preorder_link(Rbtlink link, void (*func)(Rbtlink a)) {
    if(link != SENTINEL) {
	func(link);
	rbt_preorder_link(link->l, func);
	rbt_preorder_link(link->r,func);
    }
}

void rbt_postorder(Rbt_tree_link rbt, void (*func)(Rbtlink a)) {
    rbt_postorder_link(rbt->root, func);
}

static void rbt_postorder_link(Rbtlink link, void (*func)(Rbtlink a)) {
    if(link != SENTINEL) {
	rbt_postorder_link(link->l, func);
	rbt_postorder_link(link->r,func);
	func(link);
    }
}

Rbtlink rbt_search(Rbt_tree_link rbt, Rbtitem item) {
    Rbtlink root = rbt->root;
    while(root != SENTINEL) {
	if(cmp(root->item, item) < 0)
	    root = root->r;
	else if(cmp(root->item,item) > 0)
	    root = root->l;
	else return root;
    }
    return NULL_RBT_ITEM;
}

void rbt_destroy(Rbt_tree_link rbt) {
    rbt_destroy_link(rbt->root);
    free(rbt);
#ifdef DEBUG
    printf("%d\n",num_allocs);
#endif
}

static void rbt_destroy_link(Rbtlink link) {
    if(link != SENTINEL) {
	rbt_destroy_link(link->l);
	rbt_destroy_link(link->r);
	free_rbt_node(link);
    }
}

static void free_rbt_node(Rbtlink link) {
    assert(link);
    free_rbt_item(link->item);
    free(link);
#ifdef DEBUG
    num_allocs--;
#endif
}

static void left_rotate(Rbt_tree_link rbt, Rbtlink x) {
    Rbtnode sent = *rbt->root->p;

    Rbtlink y = x->r;

    x->r = y->l;
    y->l->p = x;
    y->p = x->p;
    if(x->p == SENTINEL) {
	rbt->root = y;
    }
    else if(x == x->p->l)
	x->p->l = y;
    else x->p->r = y;

    y->l = x;
    x->p = y;

    *rbt->root->p = sent;
}

static void right_rotate(Rbt_tree_link rbt, Rbtlink y) {
    Rbtnode sent = *rbt->root->p;

    Rbtlink x = y->l;

    y->l = x->r;
    x->r->p = y;
    x->p = y->p;
    if(y->p == SENTINEL)
	rbt->root = x;
    else if(y == y->p->l)
	y->p->l = x;
    else y->p->r = x;

    x->r = y;
    y->p = x;

    *rbt->root->p = sent;
}

Rbtlink rbt_sucessor(Rbtlink x) {
    Rbtlink y;
    if(x ->r != SENTINEL)
	return rbt_minimum_link(x->r);
    y = x->p;
    while(y != SENTINEL && x == y->r) {
	x = y;
	y = y->p;
    }
    return y;
}

Rbtlink rbt_predecessor(Rbtlink x) {
    Rbtlink y;
    if(x->l != SENTINEL)
	return rbt_maximum_link(x->l);

    y = x->p;
    while(y != SENTINEL && x == y->l) {
	x = y;
	y = y->p;
    }
    return y;
}

static void rbt_insert_fixup(Rbt_tree_link rbt,Rbtlink x) {
    Rbtlink y;

    while(x->p->color == RED) {
	if(x->p == x->p->p->l){
	    y = x->p->p->r;
	    if(y->color == RED) {
		x->p->color = BLACK;
		y->color = BLACK;
		x->p->p->color = RED;
		x=x->p->p;
	    }
	    else {
		if(x == x->p->r) {
		    x = x->p;
		    left_rotate(rbt, x);
		}
		x->p->color = BLACK;
		x->p->p->color = RED;
		right_rotate(rbt, x->p->p);
	    }
	}else {
	    y = x->p->p->l;
	    if(y->color == RED) {
		x->p->color = BLACK;
		y->color = BLACK;
		x->p->p->color = RED;
		x = x->p->p;
	    }else {
		if(x == x->p->l) {
		    x = x->p;
		    right_rotate(rbt, x);
		}
		x->p->color = BLACK;
		x->p->p->color = RED;
		left_rotate(rbt, x->p->p);
	    }
	}
    }
    rbt->root->color = BLACK;
}

static void rbt_delete_fixup(Rbt_tree_link rbt, Rbtlink x) {
    Rbtlink w;
    assert(x);
    while(x != rbt->root && x->color == BLACK) {
	if(x == x->p->l) {
	    w = x->p->r;
	    if(w->color == RED) {
		w->color = BLACK;
		x->p->color = RED;
		left_rotate(rbt, x->p);
		w = x->p->r;
	    }
	    if(w->l->color == BLACK && w->r->color == BLACK) {
		w->color = RED;
		x = x->p;
	    }else {
		if(w->r->color == BLACK) {
		    w->l->color = BLACK;
		    w->color = RED;
		    right_rotate(rbt,w);
		    w = x->p->r;
		}
		w->color = x->p->color;
		x->p->color = BLACK;
		w->r->color = BLACK;
		left_rotate(rbt,x->p);
		x = rbt->root;
	    }
	}
	else {
	    w = x->p->l;
	    if(w->color == RED){
		w->color = BLACK;
		x->p->color = RED;
		right_rotate(rbt, x->p);
		w = x->p->l;
	    }
	    if(w->r->color == BLACK && w->l->color == BLACK) {
		w->color = RED;
		x = x->p;
	    }else {
		if(w->l->color == BLACK) {
		    w->r->color = BLACK;
		    w->color = RED;
		    left_rotate(rbt, w);
		    w = x->p->l;
		}
		w->color = x->p->color;
		x->p->color = BLACK;
		w->l->color = BLACK;
		right_rotate(rbt, x->p);
		x = rbt->root;
	    }
	}
    }
    x->color = BLACK;
}

int rbt_assert(Rbt_tree_link rbt) {
    int count = 0;
    assert(rbt->root->p == SENTINEL);
    assert(dummy.l == 0 && dummy.r ==0);
    assert(assert_link(rbt->root, &count));
    assert(count == rbt_size(rbt));
#ifdef DEBUG
    printf("count: %d  size: %d\n", count, rbt_size(rbt));
#endif
    return 0;
}

static int assert_link(Rbtlink tree, int *count){
    Rbtlink l, r;
    int lh, rh;

    if(tree == SENTINEL)
	return 1;

    (*count)++;

    l = tree->l;
    r = tree->r;

    if(tree->color == RED && (l->color == RED || r->color == RED)) {
	/* Two REDs in a row */
	assert(0);
    }

    lh = assert_link(l, count);
    rh = assert_link(r, count);

    if (( l != SENTINEL && cmp(l->item, tree->item) > 0) || ( r != SENTINEL && cmp(r->item, tree->item) < 0)) {
	/* Binary tree violation */
	assert(0);
    }

    if (lh != 0 && rh != 0 && lh != rh) {
	/* Black violation */
	assert(0);
    }

    if (lh != 0 && rh != 0)
	return tree->color == RED ? lh : lh + 1;
    else return 0;
}
