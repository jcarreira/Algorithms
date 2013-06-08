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

#include <vector>
#include <algorithm>
#include <utility>
#include <climits>
#include <cmath>
#include "Point.h"
#include "math_util.h"

static
inline bool equal(const double a, const double b) {
    return fabs(a-b) < EPS;
}

static
inline double dist(const Point &p1, const Point &p2) {
    double dx = p1.getX() - p2.getX(), dy = p1.getY() - p2.getY();
    return dx * dx + dy * dy;
}

static
double delta_m(const vp &ql, const vp &qr, const double delta) {
    int i, j = 0;
    double dm = delta;

    for (i = 0; i < (int)ql.size(); i++) {
	Point p = ql[i];

	while (j < (int)qr.size() && qr[j].getY() < p.getY() - delta)
	    j++;

	int k = j;
	while (k < (int)qr.size() && qr[k].getY() <= p.getY() + delta) {
	    dm = std::min(dm, dist(p, qr[k]));
	    k++;
	}
    }
    return dm;
}

static vp select_candidates(const vp &p, int l, int r, double delta, double midx) {
    vp n;
    for (int i = l;i <= r; i++) {
	if (fabs(p[i].getX() - midx) <= delta)
	    n.push_back(p[i]);
    }
    return n;
}

double closest_pair(vp &p, const int l, const int r) {
    if (r - l + 1 < 2) return INF;

    int mid = (l + r) / 2;
    double midx = p[mid].getX();
    double dl = closest_pair(p, l, mid);
    double dr = closest_pair(p, mid + 1, r);
    double delta = std::min(dl, dr);

    vp ql, qr;
    ql = select_candidates(p, l,mid, delta, midx);
    qr = select_candidates(p, mid + 1, r, delta, midx);

    double dm = delta_m(ql, qr, delta);
    vp res;
    merge(p.begin() + l, p.begin() + mid + 1, p.begin() + mid + 1, p.begin() + r + 1, back_inserter(res));
    copy(res.begin(), res.end(), p.begin() + l);
    return std::min(dm, std::min(dr, dm));
}

