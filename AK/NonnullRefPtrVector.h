#pragma once

#include <AK/NonnullRefPtr.h>
#include <AK/Vector.h>

namespace AK {

template<typename T, int inline_capacity = 0>
class NonnullRefPtrVector : public Vector<NonnullRefPtr<T>, inline_capacity> {
    typedef Vector<NonnullRefPtr<T>> Base;

public:
    NonnullRefPtrVector(Vector<NonnullRefPtr<T>>&& other)
        : Base(static_cast<Base&&>(other))
    {
    }
    NonnullRefPtrVector(const Vector<NonnullRefPtr<T>>& other)
        : Base(static_cast<const Base&>(other))
    {
    }

    using Base::size;
    T& at(int index) { return *Base::at(index); }
    const T& at(int index) const { return *Base::at(index); }
    T& operator[](int index) { return at(index); }
    const T& operator[](int index) const { return at(index); }
    T& first() { return at(0); }
    const T& first() const { return at(0); }
    T& last() { return at(size() - 1); }
    const T& last() const { return at(size() - 1); }
};

}

using AK::NonnullRefPtrVector;