#pragma once
//---- include section ------
#include <queue>
#include <string>
#include <mutex>  // for std::unique_lock
#include <shared_mutex>

//---- using section --------
using std::string;

/*
 * RequestsQueue class.
 * this is synchronized class - can used from many threads
 */
template <class T = std::string>
class RequestsQueue {
public:
	// constructor
	RequestsQueue() = default;
	// get size of requests
	size_t size() const;
	// push new request
	void push(const T& t);
	// try pop request. if succeeding - return the pointer to request, otherwise return nullptr
	std::unique_ptr<T> tryPop();
	// check if queue is empty
	bool isEmpty() const;
	// clear all requests
	void clear();
private:
	// mutex
	mutable std::shared_mutex m_mutex;
	// queue
	std::queue<T> m_queue;
};

template<class T>
size_t RequestsQueue<T>::size() const
{
	std::shared_lock<std::shared_mutex> lock(m_mutex);
	return m_queue.size();
}

template<class T>
void RequestsQueue<T>::push(const T& t)
{
	std::unique_lock<std::shared_mutex> lock(m_mutex);
	m_queue.push(t);
}

template<class T>
std::unique_ptr<T> RequestsQueue<T>::tryPop()
{
	std::unique_lock<std::shared_mutex> lock(m_mutex);
	if (m_queue.empty())
		return nullptr;
	std::unique_ptr<T> request = std::make_unique<T>(m_queue.front());
	m_queue.pop();
	return request; // move unique_ptr to result
}

template<class T>
bool RequestsQueue<T>::isEmpty() const
{
	std::shared_lock<std::shared_mutex> lock(m_mutex);
	return m_queue.empty();
}

template<class T>
void RequestsQueue<T>::clear()
{
	std::unique_lock<std::shared_mutex> lock(m_mutex);
	while (!m_queue.empty())
		m_queue.pop();
}
