//
// RingBuffer.hpp
//

#pragma once

template <typename T, size_t N>
class RingBuffer
{
private:
    T value_[N];
    size_t writeIndex_;
    size_t readIndex_;

public:
    RingBuffer<T, N>() : writeIndex_(0), readIndex_(0) {}
    void addLast(T value) { value_[writeIndex_] = value; ++writeIndex_; }
    T getFirst() { T result = value_[readIndex_]; ++readIndex_; return result; }
};

//
// End of File
//

