#pragma once
//---- include section ------
#include <string>
#include <vector>
#include <memory>
#include "View.h"

//---- using section --------
using std::string;
using std::vector;

namespace GUI {
/*
 * ViewGroup abstract class
 * Note: the views can't be on each other.
 */
template <class ViewType = GUI::View>
class ViewGroup :
	public GUI::View
{
public:
	// get view by index
	virtual const std::shared_ptr<ViewType>& getView(int index) const;
	// get number of views
	virtual int getNumOfViews() const;
	// draw
	virtual void draw() override;
	// handle click event
	virtual bool handleClickEvent(float mouseX, float mouseY) override;
	// handle enter event
	virtual bool handleEnterEvent(float mouseX, float mouseY) override;
	// handle leave event
	virtual bool handleLeaveEvent(float mouseX, float mouseY) override;
	// handle key down event
	virtual void handleKeyDownEvent(sf::Keyboard::Key keyCode) override;
	// handle key released event
	virtual void handleKeyReleasedEvent(sf::Keyboard::Key keyCode) override;
	// convert to string
	virtual string toString() const override;
protected:
	// constructor
	explicit ViewGroup(sf::RenderWindow& window);
	// check if have view in index
	bool haveViewAt(int index) const;
	// remove view
	virtual void removeView(int index);
	// add view
	virtual void addView(const std::shared_ptr<ViewType>& view);
	// remove all views
	virtual void removeAllViews() { m_views.clear(); }
private:
	// my childrens
	std::vector<std::shared_ptr<ViewType>> m_views;
};
}

template <class ViewType>
GUI::ViewGroup<ViewType>::ViewGroup(sf::RenderWindow& window)
	: View(window)
{ }

template <class ViewType>
void GUI::ViewGroup<ViewType>::addView(const std::shared_ptr<ViewType>& view)
{
	// add self as parent view 
	view->setParent(*this);
	// add view
	m_views.push_back(view);
}

template <class ViewType>
const std::shared_ptr<ViewType>& GUI::ViewGroup<ViewType>::getView(int index) const
{
	if (!haveViewAt(index))
		throw std::invalid_argument("No found view at " + std::to_string(index) + " index");
	return m_views[index];
}

template <class ViewType>
void GUI::ViewGroup<ViewType>::removeView(int index)
{
	if (!haveViewAt(index))
		throw std::invalid_argument("No found view at " + std::to_string(index) + " index");
	m_views.erase(m_views.begin() + index);
}

template <class ViewType>
int GUI::ViewGroup<ViewType>::getNumOfViews() const
{
	return static_cast<int>(m_views.size());
}

template <class ViewType>
void GUI::ViewGroup<ViewType>::draw()
{
	View::draw();

	if (isShow()) {
		// draw children
		for (const auto& view : m_views)
			view->draw();
	}
}

template <class ViewType>
string GUI::ViewGroup<ViewType>::toString() const
{
	string str = "ViewGroup: { view=" + View::toString() + ", childs={\n";
	for (const auto& view : m_views)
		str += "v=" + view->toString() + "\n";
	str += "} }";
	return str;
}

template <class ViewType>
bool GUI::ViewGroup<ViewType>::handleClickEvent(float mouseX, float mouseY)
{
	bool clicked = View::handleClickEvent(mouseX, mouseY);

	if (isEnable()) {
		// handle children
		for (const auto& view : m_views)
			view->handleClickEvent(mouseX, mouseY);
	}

	return clicked;
}

template <class ViewType>
bool GUI::ViewGroup<ViewType>::handleEnterEvent(float mouseX, float mouseY)
{
	bool enterd = View::handleEnterEvent(mouseX, mouseY);

	if (isEnable()) {
		// handle children
		for (const auto& view : m_views) {
			if (view->handleEnterEvent(mouseX, mouseY))
				break;
		}
	}

	return enterd;
}

template <class ViewType>
bool GUI::ViewGroup<ViewType>::handleLeaveEvent(float mouseX, float mouseY)
{
	bool leaved = View::handleLeaveEvent(mouseX, mouseY);

	if (isEnable()) {
		// handle children
		for (const auto& view : m_views) {
			if (view->handleLeaveEvent(mouseX, mouseY))
				break;
		}
	}

	return leaved;
}

template <class ViewType>
void GUI::ViewGroup<ViewType>::handleKeyDownEvent(sf::Keyboard::Key keyCode)
{
	View::handleKeyDownEvent(keyCode);

	if (isEnable()) {
		// handle children
		for (const auto& view : m_views)
			view->handleKeyDownEvent(keyCode);
	}
}

template <class ViewType>
void GUI::ViewGroup<ViewType>::handleKeyReleasedEvent(sf::Keyboard::Key keyCode)
{
	View::handleKeyReleasedEvent(keyCode);

	if (isEnable()) {
		// handle children
		for (const auto& view : m_views)
			view->handleKeyReleasedEvent(keyCode);
	}
}

template <class ViewType>
bool GUI::ViewGroup<ViewType>::haveViewAt(int index) const
{
	return (index >= 0) && (index < getNumOfViews());
}
