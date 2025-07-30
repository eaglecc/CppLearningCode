#include <thread>
#include <iostream>
#include <shared_mutex>
#include <chrono>

std::shared_timed_mutex stmux;



void ThreadRead(int i)
{
	for (;;)
	{
		stmux.lock_shared();
		std::cout << i;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		stmux.unlock_shared();
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

int main(int argc, char* argv[])
{
    
}