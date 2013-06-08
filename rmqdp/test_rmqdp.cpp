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

/*
 *  Range Minimum/Maximum Query search using DP
 *  O(nlogn) construction, O(1) query
 */

#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

const int  SIZE = 50000;
const int LOGSIZE = 20;

int n[SIZE]; 

int m[SIZE][LOGSIZE]; /* min value in a range */
int M[SIZE][LOGSIZE]; /* max value in a range */

int main() {
    /* number of elements in sequence */
    int N;

    /* number of queries */
    int  Q;

    cout << "Insert the number of values in the sequence: ";
    cin >> N;

    cout << "Insert the number of queries: ";
    cin >> Q;

    cout << "Insert " << N << " values:  " << endl;
    for (int i = 0; i < N; i++)
	cin >> n[i];

    for (int i = 0; i < N; i++)
	m[i][0] = M[i][0] = n[i];

    for (int i = 1;(1 << i) <= N; i++) {
	for (int j = 0; j + (1 << i) - 1 < N; j++) {
	    m[j][i] = min(m[j][i - 1], m[j + (1 << (i - 1))][i - 1]);
	    M[j][i] = max(M[j][i - 1], M[j + (1 << (i - 1))][i - 1]);
	}
    }

    cout << "Insert " << Q << " queries (one based interval):" << endl;
    for (int k = 0;k < Q; k++) {
	int i, j, t, p;
	cin >> i >> j;
	i--; j--;
	t = (int)(log(j - i + 1) / log(2)); 
	p = 1 << t;
	cout << "max: " << max(M[i][t], M[j - p + 1][t]) << "  min: " << min(m[i][t], m[j - p + 1][t]) << endl << endl;
    }
    return 0;
}
