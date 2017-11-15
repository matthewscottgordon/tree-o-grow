#ifndef VECTOR_H
#define VECTOR_H

#include <cassert>

template< size_t LENGTH, typename ElementType=double>
class Vector
{
public:
    template<typename... T>
    Vector( T... elements )
        : m_elements{elements...}
        {
        }


    ElementType operator[]( size_t i ) const
        {
            assert( i < LENGTH );
            return m_elements[i];
        }

    ElementType &operator[]( size_t i )
        {
            assert( i < LENGTH );
            return m_elements[i];
        }


    const ElementType *data() const
        {
            return m_elements.data();
        }

private:
    Vector()
        {
            m_elements.fill(0);
        }

    std::array<ElementType,LENGTH> m_elements;
};

#endif
