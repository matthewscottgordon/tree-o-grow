#ifndef MATRIX_H
#define MATRIX_H

#include <cassert>

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

#endif
