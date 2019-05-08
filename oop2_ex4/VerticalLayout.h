#pragma once
//---- include section ------
#include <string>
#include "ViewGroup.h"

//---- using section --------
using std::string;

namespace GUI {
/*
 * VerticalLayout class
 */
template <class ViewType = GUI::View>
class VerticalLayout :
	public GUI::ViewGroup<ViewType>
{
public:
	// constructor
	explicit VerticalLayout(sf::RenderWindow& window) : ViewGroup<ViewType>(window) { }
	// add view with default height
	virtual void addView(const std::shared_ptr<ViewType>& view) override;
	// add view
	virtual void addView(const std::shared_ptr<ViewType>& view, float relativeHeight);
	// remove view
	virtual void removeView(int index) override;
	// get relative height of child
	float getChildRelativeHeight(int index) const;
	// convert to string
	virtual string toString() const override;
protected:
	// update components
	virtual void updateComponents() override;
	// arrange childrens with same heights
	void arrangeChildrens();
	// remove all views
	virtual void removeAllViews() override;
private:
	// my view relative heights
	vector<float> m_relativeHeights;
	// check relative height
	bool checkRelativeHeight(float relativeHeight) const;
};
}

template <class ViewType>
string GUI::VerticalLayout<ViewType>::toString() const
{
	return "VerticalLayout: { view=" + ViewGroup<ViewType>::toString() + " }";
}

template <class ViewType>
void GUI::VerticalLayout<ViewType>::addView(const std::shared_ptr<ViewType>& view)
{
	float relativeHeight = (float)1 / (this->getNumOfViews() + 1);
	addView(view, relativeHeight);
	arrangeChildrens();
}

template <class ViewType>
void GUI::VerticalLayout<ViewType>::addView(const std::shared_ptr<ViewType>& view, float relativeHeight)
{
	ViewGroup<ViewType>::addView(view);
	if (!checkRelativeHeight(relativeHeight))
		throw std::invalid_argument("Can't set relative height " + std::to_string(relativeHeight));
	m_relativeHeights.push_back(relativeHeight);
	updateComponents();
}

template <class ViewType>
void GUI::VerticalLayout<ViewType>::removeView(int index)
{
	ViewGroup<ViewType>::removeView(index);
	m_relativeHeights.erase(m_relativeHeights.begin() + index);
	updateComponents();
}

template <class ViewType>
void GUI::VerticalLayout<ViewType>::arrangeChildrens()
{
	if (this->getNumOfViews() > 0) {
		float relativeHeight = (float)1 / this->getNumOfViews();
		for (size_t i = 0; i < m_relativeHeights.size(); i++)
			m_relativeHeights[i] = relativeHeight;
		updateComponents();
	}
}

template<class ViewType>
void GUI::VerticalLayout<ViewType>::removeAllViews()
{
	ViewGroup<ViewType>::removeAllViews();
	m_relativeHeights.clear();
}

template <class ViewType>
float GUI::VerticalLayout<ViewType>::getChildRelativeHeight(int index) const
{
	if (!this->haveViewAt(index))
		throw std::invalid_argument("No found view at " + std::to_string(index) + " index");
	return m_relativeHeights[index];
}

template <class ViewType>
void GUI::VerticalLayout<ViewType>::updateComponents()
{
	ViewGroup<ViewType>::updateComponents();

	if (this->isNoSet())
		return;

	if (this->getNumOfViews() > 0) {
		int childWidth = this->getWidth();
		int childY = 0;
		for (int i = 0; i < this->getNumOfViews(); i++) {
			int childHeight = (int)(m_relativeHeights[i] * this->getHeight());
			sf::Vector2f childPosition(this->getPosition().x, this->getPosition().y + childY);
			const std::shared_ptr<ViewType>& view = this->getView(i);
			view->setBound(childPosition, childWidth, childHeight);

			childY += childHeight;
		}
	}
}

template <class ViewType>
bool GUI::VerticalLayout<ViewType>::checkRelativeHeight(float relativeHeight) const
{
	return ((relativeHeight >= 0) && (relativeHeight <= 1));
}