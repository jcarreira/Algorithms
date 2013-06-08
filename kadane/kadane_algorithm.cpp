/***************************************************************************
 *   Copyright (C) 2007 by João Carreira
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
 * maximum subarray sum in O(n^3)
 */

#include <iostream>
#include <climits>
#include <algorithm>

static const int SIZE = 100;

int n[SIZE+1][SIZE], c;

int calc_sum(int i, int j, int N) {
    int p[SIZE], max_value = INT_MIN, b = 0;

    for (int k = 0; k < N; k++) {
	p[k] = n[i][k] - n[j][k];
	b = p[k] + std::max(0, b);

	if (b > max_value)
	    max_value = b;
    }

    return max_value;
}

int main() {
    using namespace std;

    int N, max_value = INT_MIN;

    cin >> N;

    for (int i = 1; i <= N; i++) {
	for (int j = 0; j < N; j++) {
	    cin >> n[i][j];
	    n[i][j] += n[i - 1][j];
	}
    }

    for (int i = N; i > 0; i--) {
	for(int j = i - 1; j >= 0; j--) {
	    int sum = calc_sum(i, j, N);

	    if (sum > max_value)
		max_value = sum;
	}
    }
    cout << max_value << endl;
    return 0;
}
