#include <chrono>
#include <condition_variable>
#include <iostream>
#include <thread>
#include <future>
#include <mutex>
#include <type_traits>

#ifndef COUNT
#define COUNT 500
#endif


std::mutex m;
std::condition_variable c;

bool is_ping = false;


template <bool ping>
void pingpong()
{	
	auto counter = 0;
	while(counter++ < COUNT)
	{
		std::unique_lock<std::mutex> lock(m);
		c.wait(lock, [] { return (ping ? !is_ping : is_ping); });
		std::cout << (ping ? "ping" : "pong") << std::endl;
		is_ping = ping;
		c.notify_one();
	}
}


int main(int argc, char const *argv[])
{
	std::thread th1(pingpong<1>);
	std::thread th2(pingpong<0>);

	th1.join();
	th2.join();

	return 0;
}