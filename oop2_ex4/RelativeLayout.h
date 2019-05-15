#pragma once
//---- include section ------
#include <string>
#include <vector>
#include "ViewGroup.h"

//---- using section --------
using std::string;
using std::vector;

namespace GUI {
/*
 * RelativeLayout class
 */
template <class ViewType = GUI::View>
class RelativeLayout :
	public ViewGroup<ViewType>
{
public:
	// constructor
	explicit RelativeLayout(sf::RenderWindow& window) : ViewGroup<ViewType>(window) { }
	// add view
	virtual void addView(const std::shared_ptr<ViewType>& view, const sf::FloatRect& relativeBounds);
	// remove view
	virtual void removeView(int index) override;
	// convert to string
	virtual string toString() const override;
protected:
	// update components
	virtual void updateComponents() override;
	// remove all views
	virtual void removeAllViews() override;
private:
	// relative bounds of children
	vector<sf::FloatRect> m_relativeBounds;
	// check relative bounds
	bool checkRelativeBounds(const sf::FloatRect& relativeBounds) const;
	// check if number between 0-1
	bool checkBoundNumOK(float num) const;
	// update view bounds
	void updateViewBounds(int index);
};
}

template <class ViewType>
void GUI::RelativeLayout<ViewType>::addView(const std::shared_ptr<ViewType>& view, const sf::FloatRect& relativeBounds)
{
	if (!checkRelativeBounds(relativeBounds))
		throw std::invalid_argument("Relative bounds must be numbers between 0-1");

	ViewGroup<ViewType>::addView(view);
	m_relativeBounds.push_back(relativeBounds);
	updateViewBounds(this->getNumOfViews()-1);
}

template <class ViewType>
void GUI::RelativeLayout<ViewType>::removeView(int index)
{
	ViewGroup<ViewType>::removeView(index);
	m_relativeBounds.erase(m_relativeBounds.begin() + index);
	updateComponents();
}

template <class ViewType>
string GUI::RelativeLayout<ViewType>::toString() const
{
	return "RelativeLayout: { " + ViewGroup<ViewType>::toString() + " }";
}

template <class ViewType>
void GUI::RelativeLayout<ViewType>::updateComponents()
{	
	ViewGroup<ViewType>::updateComponents();

	if (this->isNoSet())
		return;

	if (this->getNumOfViews() > 0) {
		for (int i = 0; i < this->getNumOfViews(); i++) {
			updateViewBounds(i);
		}
	}
}

template<class ViewType>
void GUI::RelativeLayout<ViewType>::removeAllViews()
{
	ViewGroup<ViewType>::removeAllViews();
	m_relativeBounds.clear();
}

template <class ViewType>
bool GUI::RelativeLayout<ViewType>::checkRelativeBounds(const sf::FloatRect& relativeBounds) const
{
	return checkBoundNumOK(relativeBounds.left) && checkBoundNumOK(relativeBounds.top) &&
		checkBoundNumOK(relativeBounds.width) && checkBoundNumOK(relativeBounds.height);
}

template <class ViewType>
bool GUI::RelativeLayout<ViewType>::checkBoundNumOK(float num) const
{
	return (num >= 0) && (num <= 1);
}

template<class ViewType>
void GUI::RelativeLayout<ViewType>::updateViewBounds(int index)
{
	sf::FloatRect& relativeCBounds = m_relativeBounds[index];
	sf::FloatRect childBounds(this->getPosition().x + this->getWidth()*relativeCBounds.left, this->getPosition().y + this->getHeight()*relativeCBounds.top,
		this->getWidth()*relativeCBounds.width, this->getHeight()*relativeCBounds.height);
	const std::shared_ptr<ViewType>& childView = this->getView(index);
	childView->setBound(childBounds);
}

