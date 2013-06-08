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

#include "Point.h"
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cfloat>
#include "closestpair.h"

#define INF_THRESHOLD 10000

typedef std::vector<Point> vp;

double dist(Point p1, Point p2) {
    double dx = p1.getX() - p2.getX(), dy = p1.getY() - p2.getY();
    return dx * dx + dy * dy;
}

double bruteforce(vp &p) {
    int i, j;
    double d = FLT_MAX;

    for (i = 0;i < (int)p.size(); i++)
	for (j = i + 1; j < (int)p.size(); j++)
	    d = std::min(d, dist(p[i], p[j]));
    return d;
}

int main() {
    int i, N, k;
    puts("Insert a value N, followed by N coordinates.");

    for (k = 0; scanf("%d", &N) == 1 && N; k++) {
	vp p;
	for (i = 0; i < N; i++) {
	    double n1, n2;
	    scanf("%lf %lf", &n1, &n2);
	    p.push_back(Point((int)n1, (int)n2));
	}

	sort(p.begin(), p.end());//sort by x-coordinate

	double dist1 = closest_pair(p, 0, N - 1);

	if (sqrt(dist1) >= INF_THRESHOLD)
	    printf(" %d  INFINITY\n", k);
	else printf("%d  %.4lf\n", k, sqrt(dist1));
    }
    return 0;
}
