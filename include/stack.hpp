#ifndef STACK_HPP 
#define STACK_HPP

template <typename T>
class stack
{
public:
    using size_type = std::size_t;
    
    stack();
    bool empty() const;
private:
    T * buffer_;
    size_type buffer_size_;
    size_type count_;
};

template <typename T>
stack<T>::stack() : buffer_{ nullptr }, buffer_size_ { 0UL }, count_{ 0UL }
{
}

template <typename T>
bool stack<T>::empty() const
{
    return count_ == 0;    
}

#endif
