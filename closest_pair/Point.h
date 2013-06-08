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

#ifndef _POINT_H_
#define _POINT_H_

# include <cmath>
# include "math_util.h"

const double EPS = 1e-8;

class Point {
public:
    Point(const double x = 0, const double y = 0) : _x(x), _y(y) {}

    void setX(const int x) { _x = x; }
    void setY(const int y) { _y = y; }

    double getX() const { return _x; }
    double getY() const { return _y; }

    bool operator<(const Point &a) const { return _y < a.getY() || (equal(_y, a.getY(), EPS) && _x < a.getX()); }

private:
    double _x, _y;
    bool equal(const double a, const double b, const double error) const { return fabs(a-b) < error; }
};

#endif //_POINT_H_
