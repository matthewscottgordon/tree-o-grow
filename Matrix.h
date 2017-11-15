#ifndef MATRIX_H
#define MATRIX_H

#include "Vector.h"

#include <cassert>
#include <cmath>

template< size_t ROWS, size_t COLUMNS, typename ElementType=double>
class Matrix
{
public:
    template<typename... T>
    Matrix( T... elements )
        : m_elements{elements...}
        {
        }

    static Matrix Identity()
        {
            Matrix result;
            for( int i=0; i<std::max(ROWS,COLUMNS); ++i )
                result(i,i) = 1;
        }


    ElementType operator()( size_t row, size_t column ) const
        {
            assert( row < ROWS && column < COLUMNS );
            return m_elements[row*ROWS+column];
        }

    ElementType &operator()( size_t row, size_t column )
        {
            assert( row < ROWS && column < COLUMNS );
            return m_elements[row*ROWS+column];
        }


    template< size_t OTHER_DIMENSION >
    Matrix<ROWS,OTHER_DIMENSION,ElementType>
    operator*( const Matrix<OTHER_DIMENSION,ROWS,ElementType> &other )
        {
            Matrix<ROWS,OTHER_DIMENSION,ElementType> result;
            for( size_t row; row<ROWS; ++row )
                for( size_t column; column<OTHER_DIMENSION; ++column )
                    for( size_t i=0; i<COLUMNS; ++i )
                        result(row,column) += (*this)(row,i) * other(column,row);
            return result;
        }


    const ElementType *data() const
        {
            return m_elements.data();
        }

private:
    Matrix()
        {
            m_elements.fill(0);
        }

    std::array<ElementType,ROWS*COLUMNS> m_elements;
};


template<typename ElementType>
Matrix<4,4,ElementType> makeRotationMatrix( const Vector<3,ElementType> &axis, ElementType radians )
{
    static_assert( std::is_floating_point<ElementType>::value,
                   "Rotation matrix must have float r double type." );

    const ElementType cosTheta = std::cos(radians);
    const ElementType sinTheta = std::sin(radians);
    return Matrix<4,4,ElementType>(
        cosTheta                       + axis[0]*axis[0]*(1.0-cosTheta),
        axis[1]*axis[0]*(1.0-cosTheta) + axis[2]*sinTheta,
        axis[2]*axis[0]*(1.0-cosTheta) - axis[1]*sinTheta,
        axis[0]*axis[1]*(1.0-cosTheta) - axis[2]*sinTheta,
        cosTheta                       + axis[1]*axis[1]*(1.0-cosTheta),
        axis[2]*axis[1]*(1.0-cosTheta) + axis[0]*sinTheta,
        axis[0]*axis[2]*(1.0-cosTheta) + axis[1]*sinTheta,
        axis[1]*axis[2]*(1.0-cosTheta) - axis[0]*sinTheta,
        cosTheta                       + axis[2]*axis[2]*(1.0-cosTheta) );
}

#endif
