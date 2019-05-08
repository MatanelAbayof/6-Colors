#pragma once
//---- include section ------
#include <string>
#include "ViewGroup.h"

//---- using section --------
using std::string;

namespace GUI {
	/*
	 * HorizontalLayout class
	 */
	template <class ViewType = GUI::View>
	class HorizontalLayout :
		public GUI::ViewGroup<ViewType>
	{
	public:
		// constructor
		explicit HorizontalLayout(sf::RenderWindow& window) : ViewGroup<ViewType>(window) { }
		// add view with default width
		virtual void addView(const std::shared_ptr<ViewType>& view) override;
		// add view with custom width
		virtual void addView(const std::shared_ptr<ViewType>& view, float relativeWidth);
		// remove view
		virtual void removeView(int index) override;
		// convert to string
		virtual string toString() const override;
	protected:
		// update components
		virtual void updateComponents() override;
		// arrange all childrens with same widths
		void arrangeChildrens();
		// remove all views
		virtual void removeAllViews() override;
	private:
		// childrens relative widths
		vector<float> m_relativeWidths;
		// check if relative width in [0, 1]
		bool checkRelativeWidth(float relativeWidth) const;
	};
}

template <class ViewType>
void GUI::HorizontalLayout<ViewType>::addView(const std::shared_ptr<ViewType>& view)
{
	float relativeWidth = (float)1 / (this->getNumOfViews() + 1);
	addView(view, relativeWidth);
	arrangeChildrens();
}

template <class ViewType>
void GUI::HorizontalLayout<ViewType>::addView(const std::shared_ptr<ViewType>& view, float relativeWidth)
{
	ViewGroup<ViewType>::addView(view);
	if (!checkRelativeWidth(relativeWidth))
		throw std::invalid_argument("Can't set relative width " + std::to_string(relativeWidth));
	m_relativeWidths.push_back(relativeWidth);
	updateComponents();
}

template <class ViewType>
void GUI::HorizontalLayout<ViewType>::removeView(int index)
{
	ViewGroup<ViewType>::removeView(index);
	m_relativeWidths.erase(m_relativeWidths.begin() + index);
	updateComponents();
}

template <class ViewType>
void GUI::HorizontalLayout<ViewType>::arrangeChildrens()
{
	if (this->getNumOfViews() > 0) {
		float relativeWidth = (float)1 / this->getNumOfViews();
		for (size_t i = 0; i < m_relativeWidths.size(); i++)
			m_relativeWidths[i] = relativeWidth;
		updateComponents();
	}
}

template<class ViewType>
void GUI::HorizontalLayout<ViewType>::removeAllViews()
{
	ViewGroup<ViewType>::removeAllViews();
	m_relativeWidths.clear();
}

template <class ViewType>
string GUI::HorizontalLayout<ViewType>::toString() const
{
	return "HorizontalLayout: { view=" + ViewGroup<ViewType>::toString() + " }";
}

template <class ViewType>
void GUI::HorizontalLayout<ViewType>::updateComponents()
{
	ViewGroup<ViewType>::updateComponents();

	if (this->isNoSet())
		return;

	if (this->getNumOfViews() > 0) {
		int childX = 0;
		int childHeight = this->getHeight();

		for (int i = 0; i < this->getNumOfViews(); i++) {
			int childWidth = (int)(m_relativeWidths[i] * this->getWidth());
			sf::Vector2f childPosition(this->getPosition().x + childX, this->getPosition().y);
			const std::shared_ptr<ViewType>& view = this->getView(i);
			view->setBound(childPosition, childWidth, childHeight);

			childX += childWidth;
		}
	}
}

template <class ViewType>
bool GUI::HorizontalLayout<ViewType>::checkRelativeWidth(float relativeWidth) const
{
	return ((relativeWidth >= 0) && (relativeWidth <= 1));
}
