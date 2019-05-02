#pragma once
//---- include section ------
#include <functional>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "IHandler.h"
#include "ImageTexture.h"
#include "Border.h"

//---- using section --------
using std::string;
using std::vector;

namespace GUI {
/*
 * View abstract class
 */
class View
{
public:
	// type of click handler
	typedef IHandler<View> ClickHandler;
	// type of enter handler
	typedef IHandler<View> EnterHandler;
	// type of leave handler
	typedef IHandler<View> LeaveHandler;
	// type of key release handler
	typedef IHandler<sf::Keyboard::Key> KeyReleaseHandler;
	// type of key down handler
	typedef IHandler<sf::Keyboard::Key> KeyDownHandler;
	// default position
	static const sf::Vector2f DEFAULT_POSITION;
	// default width
	static const int MIN_WIDTH = 0;
	// default height
	static const int MIN_HEIGHT = 0;
	// handle events - return false if cannot handle (use in root view)
	bool handleEvent(const sf::Event& event);
	// handle click event. return true if clicked
	virtual bool handleClickEvent(float mouseX, float mouseY);
	// handle enter event. return true if entered
	virtual bool handleEnterEvent(float mouseX, float mouseY);
	// handle leave event. return true if leaved
	virtual bool handleLeaveEvent(float mouseX, float mouseY);
	// handle key down event
	virtual void handleKeyDownEvent(sf::Keyboard::Key keyCode);
	// handle key released event
	virtual void handleKeyReleasedEvent(sf::Keyboard::Key keyCode);	
	// listen to click event (remove last listeners)
	void setClickListener(ClickHandler::Listener listener);
	// listen to click event
	void addClickListener(ClickHandler::Listener listener);
	// listen to enter event
	void addEnterListener(EnterHandler::Listener listener);	
	// listen to leave event
	void addLeaveListener(LeaveHandler::Listener listener);
	// listen to key down event
	void addKeyDownListener(KeyDownHandler::Listener listener);
	// listen to key release event
	void addKeyReleasedListener(KeyReleaseHandler::Listener listener);
	// if point in my area
	bool isPointInMyArea(float x, float y) const;
	bool isPointInMyArea(const sf::Vector2f& point) const;
	// get position
	const sf::Vector2f& getPosition() const;
	// get bound rectangle
	sf::FloatRect getBound() const;
	// get width
	int getWidth() const;
	// get height
	int getHeight() const;
	// get size (width and height)
	sf::Vector2i getSize() const;
	// set size (width and height)
	void setSize(const sf::Vector2i& size);
	void setSize(int width, int height);
	// get center
	sf::Vector2f getCenter() const;
	// is show
	bool isShow() const;
	// show
	virtual void show();
	// hide
	virtual void hide();
	// enable events
	virtual void enable();
	// disable events
	virtual void disable();
	// check if view is enable
	bool isEnable() const;
	// get background
	ImageTexture& getBackground();
	// get border
	Border& getBorder();
	// draw in window
	virtual void draw();
	// set width
	void setWidth(int width);
	// set height
	void setHeight(int height);
	// set area
	void setBound(const sf::FloatRect& bound);
	// set area
	void setBound(const sf::Vector2f& position, int width, int height);
	// set position
	void setPosition(const sf::Vector2f& position);
	void setPosition(float x, float y);
	// get parent view
	View& getParent() const;
	// check if has no parent view
	bool isRootView() const;
	// set parent view
	void setParent(View& view);
	// get window
	sf::RenderWindow& getWindow();
	// make this view as root view
	void makeRootView(bool useCamera = false);
	// check if use camera (only for root view)
	bool isUseCamera() const;
	// get camera (only for root view with camera)
	sf::View& getCamera();
	// convert to string
	virtual string toString() const;
protected:
	// constructor
	explicit View(sf::RenderWindow& window);
	// copy constructor (not copy listeners!)
	View(const View& otherView);
	// draw in view
	void sendDrawRequest(const sf::Drawable& drawable);
	// update components
	virtual void updateComponents();
	// check if view not set already
	virtual bool isNoSet() const;
private:
	// window
	sf::RenderWindow& m_window;
	// camera (for root view)
	std::unique_ptr<sf::View> m_camera;
	// parent view
	View* m_parent;
	// use camera (for root view)
	bool m_useCamera;
	// background object
	ImageTexture m_background;
	// border
	Border m_border;
	// size of view
	int m_width, m_height;
	// visibility
	bool m_show;
	// clickable - use for events
	bool m_clickable;
	// position of view
	sf::Vector2f m_position;
	// mouse in view (for enter handler)
	bool m_mouseIn;
	// mouse out of view (for leave handler)
	bool m_mouseOut;
	// click handler
	ClickHandler m_clickHandler;
	// enter handler
	EnterHandler m_enterHandler;
	// leave handler
	EnterHandler m_leaveHandler;
	// last key that down
	sf::Keyboard::Key m_lastKeyDownCode;
	// key down handler
	KeyDownHandler m_keyDownHandler;
	// key release handler
	KeyReleaseHandler m_keyReleaseHandler;
	// check if can set bound
	bool checkBound(const sf::FloatRect& bound) const;
	// check if width OK
	bool isLegalWidth(int width) const;
	// check if height OK
	bool isLegalHeight(int height) const;
	// call click event
	void callOnClick();
	// call enter event
	void callOnEnter();
	// call leave event
	void callOnLeave();
	// call key down event
	void callOnKeyDown(sf::Keyboard::Key keyCode);
	// call key release event
	void callOnKeyReleased(sf::Keyboard::Key keyCode);
};
}
