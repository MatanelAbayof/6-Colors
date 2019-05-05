#pragma once
//---- include section ------
#include <functional>
#include <vector>

//---- using section --------
using std::vector;

namespace GUI {
/*
 * IHandler interface
 */
template <class T>
class IHandler
{
public:
	// type of handler
	using Listener = std::function<void(T&)>;
	// remove listeners
	void removeListeners() { m_ListenerList.clear(); }
	// listen to event
	void addListener(Listener listener) { m_ListenerList.push_back(listener); }
	// call all listeners
	void callListeners(T& t);
private:
	// vector of functions that listen to event
	vector<Listener> m_ListenerList;
};

template<class T>
void IHandler<T>::callListeners(T& t)
{
	for (Listener &listener : m_ListenerList)
		listener(t);
}

}
