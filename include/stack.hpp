#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <utility>
#include <new>
#include <thread>
#include <mutex>
#include <condition_variable>

template <typename T> /*thread-safe*/
class stack
{
private:
	void swap(stack<T> &);

public:
	stack();
	stack(stack<T> const &);
	stack<T>& operator = (stack<T> const &);
	size_t count() const;
	void push(T const &);
	auto try_pop() -> std::shared_ptr<T>;
  	auto wait_and_pop() -> std::shared_ptr<T>;
	bool empty() const;

private:
	mutable std::mutex mutex_;
	std::condition_variable cond_;
	T* array_;
	size_t array_size_;
	size_t count_;
};

template <typename T>
stack<T>::stack() : count_(0), array_size_(0), array_(nullptr)
{}

template <typename T>
size_t stack<T>::count() const
{
	std::lock_guard<std::mutex> lock(mutex_);
	return count_;
}

template <typename T>
stack<T>::stack(stack<T> const& copy)
{
	std::lock_guard<std::mutex> lock(copy.mutex_);
	T* temp = new T[copy.array_size_];
	array_size_ = copy.array_size_;
	count_ = copy.count_;
	array_ = temp;
	try
	{
		std::copy(copy.array_, copy.array_ + count_, array_);
	}
	catch (...)
	{
		delete[] array_;
		throw;
	}
}

template <typename T>
stack<T>& stack<T>::operator=(stack<T> const& other)
{
	if (this != &other)
	{
		stack<T> temp(other);
		swap(temp);
	}

	return *this;
}

template <typename T>
void stack<T>::swap(stack<T>& other)
{
	std::lock(mutex_, other.mutex_);
	std::swap(array_, other.array_);
	std::swap(array_size_, other.array_size_);
	std::swap(count_, other.count_);
	mutex_.unlock();
	other.mutex_.unlock();
}

template <typename T>
void stack<T>::push(T const& value)
{
	std::lock_guard<std::mutex> lock(mutex_);
	if (array_size_ == count_)
	{
		size_t size = array_size_;
		size == 0 ? 1 : array_size_ * 2;

		T* temp = new T[size];
		
		try
		{
			std::copy(array_, array_ + count_, temp);	
		}
		
		catch ( ... )
		{
			delete[] temp;
			throw;
		}

		array_size_ = size;
		delete[] array_;
		array_ = temp;
	}
	
	array_[count_] = value;
	++count_;
	cond_.notify_all();
}

template <typename T>
auto stack<T>::wait_and_pop() -> std::shared_ptr<T>
{
	std::unique_lock<std::mutex> lock(mutex_);

	if (empty())
	{
		cond_.wait(lock);
	}
	else
	{
		--count_;
	}	
	auto pop = std::make_shared<T>(array_[count_]);
	return pop;
}

template <typename T>
auto stack<T>::try_pop() -> std::shared_ptr<T>
{
	std::lock_guard<std::mutex> lock(mutex_);
	
	if (empty())
	{
		return nullptr;
	}
	else
	{
		--count_;
	}
	auto pop = std::make_shared<T>(array_[count_]);
	return pop;
}

template <typename T>
bool stack<T>::empty() const
{
	std::lock_guard<std::mutex> lock(mutex_);
	return (count_ == 0);	
}
