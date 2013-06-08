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

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>
#include "rbt_item.h"
#include "rbt.h"

#define N 1000000

int i,count=0;
int n[N];
int num[N];

void func(Rbtlink link) {
    n[count++] = rbt_item(link);
}

int main(){
    Rbt_tree_link a = rbt_create();
    Rbtlink it;
    srand(time(NULL));

    puts("Inserting...");
    for(i=0;i<N;i++) {
	num[i] = rand() % N;
	rbt_insert(a,num[i]);
    }
    
    printf("rbt_size: %d\n",rbt_size(a));

    printf("min value:%d   max value:%d\n",rbt_item(rbt_minimum(a)),rbt_item(rbt_maximum(a)));
    puts("Doing assert...");
    rbt_assert(a);
    puts("Traversing (inorder)...");
    rbt_inorder(a,func);

    for(i=0; i < N; i++)
	rbt_search(a, i);

    puts("Traversing (from max to min)...");
    it = rbt_maximum(a);
    for(i = rbt_size(a)-1; i >= 0; i--) {
	assert(n[i] == rbt_item(it));
	it = rbt_predecessor(it);
    }

    printf("rbt_size: %d\n",rbt_size(a));

    puts("Deleting all values...");
    int i = 0;
    for (i = 0; i < N; ++i) {
	printf("%d deleted\r", num[i]);
	rbt_delete(a, num[i]);
    }

    puts("\nDestroying rbt..");
    rbt_destroy(a);
    puts("OK!");
    return 0;
}
