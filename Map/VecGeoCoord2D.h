//Copyright 2023 Lauryl Escoubas
//
//This file is part of Discover.
//
//Discover is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//Discover is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//You should have received a copy of the GNU General Public License along with Foobar. If not, see <https://www.gnu.org/licenses/>.

#ifndef VECGEOCOORD2D_H
#define VECGEOCOORD2D_H

#include <QGeoCoordinate>

class VecGeoCoord2D
{
public:
    VecGeoCoord2D();
    VecGeoCoord2D(double _x, double _y);
    VecGeoCoord2D(const QGeoCoordinate& _coord);

    VecGeoCoord2D operator+(const VecGeoCoord2D& _other) const;
    VecGeoCoord2D operator-(const VecGeoCoord2D& _other) const;
    VecGeoCoord2D operator*(double _factor) const;
    VecGeoCoord2D operator/(double _factor) const;
    VecGeoCoord2D& operator+=(const VecGeoCoord2D& _other);
    VecGeoCoord2D& operator-=(const VecGeoCoord2D& _other);
    VecGeoCoord2D& operator*=(double _factor);
    VecGeoCoord2D& operator/=(double _factor);
    VecGeoCoord2D& operator=(const VecGeoCoord2D& _other);
    bool operator==(const VecGeoCoord2D& _other) const;
    bool operator!=(const VecGeoCoord2D& _other) const;

    double length() const;
    double lenghtSquared() const;
    void normalize();
    VecGeoCoord2D normalized() const;
    float dot(const VecGeoCoord2D& _other) const;

    double x() const {return m_x;}
    double y() const {return m_y;}

private:
    double m_x{0.0};
    double m_y{0.0};
};

QDebug operator<<(QDebug dbg, const VecGeoCoord2D& _vec);

#endif // VECGEOCOORD2D_H
