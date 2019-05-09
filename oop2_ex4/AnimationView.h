#pragma once
//---- include section ------
#include "View.h"
#include "Timer.h"
#include "TextureInfo.h"

namespace GUI {
/*
 * AnimationView class
 */
class AnimationView :
	public GUI::View
{
public:
	// constructor
	explicit AnimationView(sf::RenderWindow& window);
	// copy constructor
	AnimationView(const AnimationView& anotherAnimView);
	// set animation
	void setAnimation(const string& animName);
	// clear animation images
	void clearAnimImages();
	// check if have animation
	bool isHaveAnimation() const { return m_textureInfo != nullptr; }
	// set animation frequency - get time in milliseconds to one frame
	void setAnimationFrequency(int frameMillis);
	// stop animation
	void stopAnimation() { m_timer.stop(); }
	// draw
	virtual void draw() override;
	// convert to string
	virtual string toString() const override;
protected:
	// update components
	virtual void updateComponents();
private:
	// current sprite
	sf::Sprite m_sprite;
	// current texture
	TextureInfo* m_textureInfo;
	// current image index
	int m_currentImageIndex;
	// timer for frames
	Timer m_timer;
	// set current image
	void setCurrentImage(int index);
	// update sprite
	void updateSprite();
};
}
