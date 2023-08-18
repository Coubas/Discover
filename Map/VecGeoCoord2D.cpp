#include "VecGeoCoord2D.h"

VecGeoCoord2D::VecGeoCoord2D()
    : m_x(0.0)
    , m_y(0.0)
{}

VecGeoCoord2D::VecGeoCoord2D(double _x, double _y)
    : m_x(_x)
    , m_y(_y)
{}

VecGeoCoord2D::VecGeoCoord2D(const QGeoCoordinate &_coord)
    : VecGeoCoord2D(_coord.latitude(), _coord.longitude())
{}

double VecGeoCoord2D::length() const
{
    return sqrt(lenghtSquared());
}

double VecGeoCoord2D::lenghtSquared() const
{
    return (m_x * m_x) + (m_y * m_y);
}

void VecGeoCoord2D::normalize()
{
    *this /= length();
}

VecGeoCoord2D VecGeoCoord2D::normalized() const
{
    return *this / length();
}

float VecGeoCoord2D::dot(const VecGeoCoord2D& _other) const
{
    return (m_x * _other.m_x) + (m_y * _other.m_y);
}

VecGeoCoord2D VecGeoCoord2D::operator+(const VecGeoCoord2D& _other) const
{
    return VecGeoCoord2D(m_x + _other.x(), m_y + _other.y());
}

VecGeoCoord2D VecGeoCoord2D::operator-(const VecGeoCoord2D& _other) const
{
    return VecGeoCoord2D(m_x - _other.x(), m_y - _other.y());
}

VecGeoCoord2D VecGeoCoord2D::operator*(double _factor) const
{
    return VecGeoCoord2D(m_x * _factor, m_y * _factor);
}

VecGeoCoord2D VecGeoCoord2D::operator/(double _factor) const
{
    return VecGeoCoord2D(m_x / _factor, m_y / _factor);
}

VecGeoCoord2D& VecGeoCoord2D::operator+=(const VecGeoCoord2D& _other)
{
    m_x += _other.m_x;
    m_y += _other.m_y;
    return *this;
}

VecGeoCoord2D& VecGeoCoord2D::operator-=(const VecGeoCoord2D& _other)
{
    m_x -= _other.m_x;
    m_y -= _other.m_y;
    return *this;
}

VecGeoCoord2D& VecGeoCoord2D::operator*=(double _factor)
{
    m_x *= _factor;
    m_y *= _factor;
    return *this;
}

VecGeoCoord2D& VecGeoCoord2D::operator/=(double _factor)
{
    m_x /= _factor;
    m_y /= _factor;
    return *this;
}

VecGeoCoord2D& VecGeoCoord2D::operator=(const VecGeoCoord2D& _other)
{
    m_x = _other.m_x;
    m_y = _other.m_y;
    return *this;
}

bool VecGeoCoord2D::operator==(const VecGeoCoord2D& _other) const
{
    return m_x == _other.m_x && m_y == _other.m_y;
}

bool VecGeoCoord2D::operator!=(const VecGeoCoord2D& _other) const
{
    return !operator==(_other);
}

QDebug operator<<(QDebug debug, const VecGeoCoord2D& _vec)
{
    debug.nospace() << "VecGeoCord2D(" << _vec.x() <<", "<<_vec.y()<< ")";
    return debug.maybeSpace();
}
