#include <condition_variable>
#include <mutex>
#include <queue>


template <typename T>
class Threadsafe_Priority_Queue
{
private:
	mutable std::mutex m_mutex;
	std::priority_queue<T> m_priority_queue;
	std::condition_variable m_condition_variable;

public:
	Threadsafe_Priority_Queue() = default;

	Threadsafe_Priority_Queue(const Threadsafe_Priority_Queue &other)
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		m_priority_queue = other.m_priority_queue;
	}

	Threadsafe_Priority_Queue &operator=(const Threadsafe_Priority_Queue &other)
	{
		std::scoped_lock lock(m_mutex, other.m_mutex);
		other.m_priority_queue = m_priority_queue;
	}

	bool empty()
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		return m_priority_queue.empty();
	}
};

int main(int argc, char const *argv[])
{
	std::priority_queue<int> q;
	q.empty();
	q.push();
	q.size();
	return 0;
}