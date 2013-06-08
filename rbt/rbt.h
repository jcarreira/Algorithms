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

#ifndef _RBT_H_
#define _RBT_H_

typedef struct rbtnode* Rbtlink;
typedef struct rbt* Rbt_tree_link;

/*  Creates a new RBT.
 *  Returns a link to the new RBT.
 *  For each to this function, there must be a call to rbt_destroy.
 */
Rbt_tree_link rbt_create( );

/*  Gets the item from a link to a node of the RBT.
 *  Returns the item.
 */
Rbtitem rbt_item( Rbtlink );

/*  Checks if the RBT has a given item.
 *  Returns a link to the node where the item was found, NULL_RBT_ITEM otherwise.
 */
Rbtlink rbt_search( Rbt_tree_link, Rbtitem );

/*  Finds the node which has the minimum item .
 *  Returns a link to the found item, NULL_RBT_ITEM otherwise.
 */
Rbtlink rbt_minimum( Rbt_tree_link );

/*  Finds the node which has the maximum item .
 *  Returns a link to the found item, NULL_RBT_ITEM otherwise.
 */
Rbtlink rbt_maximum( Rbt_tree_link );

/*  Deletes a given item from the RBT.
 */
void rbt_delete( Rbt_tree_link, Rbtitem );

/*  Inserts an item in the given RBT.
 *  The RBT can't hold repeated items.
 */
void rbt_insert( Rbt_tree_link, Rbtitem );

/*  Destroys the given RBT
 *  This must be called for each created RBT.
 */
void rbt_destroy( Rbt_tree_link );

/*  Gets the size of the given RBT.
 *  Returns the size of the given RBT.
 */
int rbt_size( Rbt_tree_link );

/*  Traverses the RBT in inorder and apply each link of the RBT to the passed function.
 *  This function traverses the elements of the RBT in increasing order.
 */
void rbt_inorder( Rbt_tree_link, void (*)(Rbtlink) );

/*  Traverses the RBT in preorder and apply each link of the RBT to the passed function.
 */
void rbt_preorder( Rbt_tree_link, void (*)(Rbtlink) );

/*  Traverses the RBT in postorder and apply each link of the RBT to the passed function.
 */
void rbt_postorder( Rbt_tree_link, void (*)(Rbtlink) );

/*  Gives the next link, in increasing order.
 *  Returns a link to the sucessor, in the RBT, of the passed link.
 */
Rbtlink rbt_sucessor( Rbtlink );

/*  Gives the previous link, in increasing order.
 *  Returns a link to the predecessor, in the RBT, of the passed link.
 */
Rbtlink rbt_predecessor( Rbtlink );

/*  Get the height of the tree.
 *  Returns the height of the tree.
 */
int rbt_height( Rbt_tree_link );

/* Checks if the RBT is a well structured Red-Black Tree.
 * Just for debugging purposes.
 */
int rbt_assert( Rbt_tree_link);

#endif
