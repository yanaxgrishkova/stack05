#include "stack.hpp"
#include <thread>
#include <chrono>
#include <thread>

void producer(stack<int>& _stack)
{	
	unsigned int i = 0;
	for (;;)
	{
		_stack.push(i);
		++i;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

void consumer(stack<int>& _stack)
{
	for (;;)
	{
		try
		{
			_stack.pop();
		}
		catch (...)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}



int main()
{
	stack<int> s1;
	std::thread prod(producer, std::ref(s1));
	std::thread cons(consumer, std::ref(s1));

	prod.join();
	cons.join();

	return 0;
}
