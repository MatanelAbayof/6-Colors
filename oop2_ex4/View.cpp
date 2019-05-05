//---- include section ------
#include "View.h"
#include "RectUtils.h"

// init default position
const sf::Vector2f GUI::View::DEFAULT_POSITION = { 0, 0 };

GUI::View::View(sf::RenderWindow& window)
	: m_window(window), m_show(true), m_clickable(true), m_width(MIN_WIDTH),
	  m_height(MIN_HEIGHT), m_position(DEFAULT_POSITION), m_parent(nullptr),
	  m_mouseIn(false), m_mouseOut(true), m_lastKeyDownCode(sf::Keyboard::Key::Unknown),
	  m_camera(nullptr), m_useCamera(false)
{
	// init texture
	updateComponents();
}

GUI::View::View(const View& otherView)
	: m_window(otherView.m_window), m_parent(otherView.m_parent), m_useCamera(otherView.m_useCamera),
	  m_background(otherView.m_background), m_border(otherView.m_border), m_width(otherView.m_width),
	  m_height(otherView.m_height), m_show(otherView.m_show), m_clickable(otherView.m_clickable),
	  m_position(otherView.m_position), m_mouseIn(otherView.m_mouseIn), m_mouseOut(otherView.m_mouseOut),
      m_lastKeyDownCode(sf::Keyboard::Key::Unknown)
{
	if (otherView.m_useCamera)
		m_camera = std::make_unique<sf::View>(*otherView.m_camera);
}

sf::RenderWindow& GUI::View::getWindow()
{
	return m_window;
}

bool GUI::View::isUseCamera() const
{
	return m_useCamera;
}

sf::View& GUI::View::getCamera()
{
	if (!m_useCamera)
		throw std::logic_error("This view not use camera (" + toString() + ")");
	return *m_camera;
}

void GUI::View::makeRootView(bool useCamera)
{
	m_useCamera = useCamera;
	m_parent = nullptr;	
	setBound(sf::Vector2f(0, 0), m_window.getSize().x, m_window.getSize().y);
	if (useCamera)
		m_camera = std::make_unique<sf::View>(sf::View(getBound()));
}

void GUI::View::sendDrawRequest(const sf::Drawable &drawable)
{
	if (isShow())
		m_window.draw(drawable);
}

void GUI::View::callOnClick()
{
	if (m_clickable)
		m_clickHandler.callListeners(*this);
}

void GUI::View::setClickListener(ClickHandler::Listener listener)
{
	m_clickHandler.removeListeners();
	m_clickHandler.addListener(listener);
}

void GUI::View::addClickListener(ClickHandler::Listener listener)
{
	m_clickHandler.addListener(listener);
}

void GUI::View::callOnEnter()
{
	if (m_clickable)
		m_enterHandler.callListeners(*this);
}

void GUI::View::addEnterListener(EnterHandler::Listener listener)
{
	m_enterHandler.addListener(listener);
}

void GUI::View::callOnLeave()
{
	if (m_clickable)
		m_leaveHandler.callListeners(*this);
}

void GUI::View::callOnKeyDown(sf::Keyboard::Key keyCode)
{
	if (m_clickable)
		m_keyDownHandler.callListeners(keyCode);
}

void GUI::View::addLeaveListener(LeaveHandler::Listener listener)
{
	m_leaveHandler.addListener(listener);
}

void GUI::View::addKeyDownListener(KeyDownHandler::Listener listener)
{
	m_keyDownHandler.addListener(listener);
}

void GUI::View::callOnKeyReleased(sf::Keyboard::Key keyCode)
{
	m_keyReleaseHandler.callListeners(keyCode);
}

void GUI::View::addKeyReleasedListener(KeyReleaseHandler::Listener listener)
{
	m_keyReleaseHandler.addListener(listener);
}

bool GUI::View::isPointInMyArea(float x, float y) const
{
	return isPointInMyArea(sf::Vector2f(x, y));
}

bool GUI::View::isPointInMyArea(const sf::Vector2f& point) const
{
	return getBound().contains(point);
}

bool GUI::View::handleEvent(const sf::Event& event)
{	
	// update camera if have
	if (m_useCamera)
		m_window.setView(*m_camera);
	else {
		// update my bounds
		m_window.setView(sf::View(getBound()));
	}

	// get mouse position relative to camera (or without that)
	sf::Vector2f mousePos = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));

	switch (event.type) {
		case sf::Event::MouseButtonPressed: {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				handleClickEvent(mousePos.x, mousePos.y);
			else
				return false; // cannot handle the event
		} break;
		case sf::Event::MouseEntered: {
			handleEnterEvent(mousePos.x, mousePos.y);
		} break;
		case sf::Event::MouseLeft: { // mouse left the screen
			handleLeaveEvent(-1, -1); // fake mouse coordinates
		} break;
		case sf::Event::MouseMoved: {
			handleEnterEvent(mousePos.x, mousePos.y);
			handleLeaveEvent(mousePos.x, mousePos.y);
		} break;
		case sf::Event::KeyPressed: {
			handleKeyDownEvent(event.key.code);
		} break;
		case sf::Event::KeyReleased: {
			handleKeyReleasedEvent(event.key.code);
		} break;
		case sf::Event::Resized: {
			// if is root view
			if (isRootView()&&!isUseCamera()) {
				// new bound
				sf::FloatRect newBound = RectUtils::createFloatRect(sf::Vector2f(0, 0), event.size.width, event.size.height);
				// disable SFML resize
				m_window.setView(sf::View(newBound));
				// resize view to maximum
				setBound(newBound);				
			}
		} break;
		default: // if cannot handle the event
			return false;
	}
	// come here if event has been handled
	return true;
}

const sf::Vector2f& GUI::View::getPosition() const
{
	return m_position;
}

sf::FloatRect GUI::View::getBound() const
{
	return sf::FloatRect(getPosition(), sf::Vector2f((float) m_width, (float) m_height));
}

int GUI::View::getWidth() const
{
	return m_width;
}

int GUI::View::getHeight() const
{
	return m_height;
}

sf::Vector2i GUI::View::getSize() const
{
	return sf::Vector2i(m_width, m_height);
}

void GUI::View::setSize(const sf::Vector2i& size)
{
	if (!checkBound(RectUtils::createFloatRect(getPosition(), size.x, size.y)))
		throw std::out_of_range(toString() + " is out of bounds!");
	m_width = size.x;
	m_height = size.y;
	updateComponents();
}

void GUI::View::setSize(int width, int height)
{
	setSize(sf::Vector2i(width, height));
}

sf::Vector2f GUI::View::getCenter() const
{
	return sf::Vector2f(m_position.x + m_width/2.f, m_position.y + m_height/2.f);
}

bool GUI::View::isShow() const
{
	return m_show;
}

void GUI::View::show()
{
	m_show = true;
	enable();
}

void GUI::View::hide()
{
	m_show = false;
	disable();
}

void GUI::View::enable()
{
	m_clickable = true;
}

void GUI::View::disable()
{
	m_clickable = false;
}

bool GUI::View::isEnable() const
{
	return m_clickable;
}

GUI::ImageTexture& GUI::View::getBackground()
{
	return m_background;
}

GUI::Border& GUI::View::getBorder()
{
	return m_border;
}

void GUI::View::draw()
{
	if (isShow()) {
		
		if (isRootView() & !m_useCamera) {
			// update my bounds
			m_window.setView(sf::View(getBound()));
		}

		// update camera if used
		if (m_useCamera)
			m_window.setView(*m_camera);

		sf::FloatRect bounds = getBound();
		// draw background
		m_background.draw(m_window);
		// draw border
		m_border.draw(m_window);
	}
}

string GUI::View::toString() const
{
	return "View: { position: {x=" + std::to_string(m_position.x) + ", y=" + std::to_string(m_position.y) +
			"}, size: {width = " + std::to_string(getWidth()) + ", height = " + std::to_string(getHeight()) +
			"}, background=" + m_background.toString() + ", " + m_border.toString() + " }";
}

void GUI::View::setWidth(int width)
{
	if (!checkBound(RectUtils::createFloatRect(getPosition(), width, getHeight())))
		throw std::out_of_range(toString() + " is out of bounds!");
	// set new width
	m_width = width;
	updateComponents();
}

void GUI::View::setHeight(int height)
{
	if (!checkBound(RectUtils::createFloatRect(getPosition(), getWidth(), height)))
		throw std::out_of_range(toString() + " is out of bounds!");
	// set new height
	m_height = height;
	updateComponents();
}

void GUI::View::setBound(const sf::FloatRect& bound)
{
	if (!checkBound(bound))
		throw std::out_of_range(toString() + " is out of bounds!");
	// add members
	m_position = sf::Vector2f(bound.left, bound.top);
	m_width = (int) bound.width;
	m_height = (int) bound.height;

	updateComponents();
}

void GUI::View::setBound(const sf::Vector2f& position, int width, int height)
{
	setBound(RectUtils::createFloatRect(position, width, height));
}

void GUI::View::setPosition(const sf::Vector2f& position)
{
	if (!checkBound(RectUtils::createFloatRect(position, getWidth(), getHeight())))
		throw std::out_of_range(toString() + " is out of bounds! (new position: x=" + std::to_string(position.x) + ", y=" + std::to_string(position.y));
	m_position = position;
	updateComponents();
}

void GUI::View::setPosition(float x, float y)
{
	sf::Vector2f pos(x, y);
	setPosition(pos);
}

void GUI::View::setParent(View& view)
{
	m_parent = &view;
}

GUI::View& GUI::View::getParent() const
{
	if (isRootView())
		throw std::logic_error("There are no parent view to " + toString());
	return *m_parent;
}

bool GUI::View::isRootView() const
{
	return (m_parent == nullptr);
}

void GUI::View::updateComponents()
{ 
	sf::FloatRect bounds = getBound();
	m_background.updateBounds(bounds);
	m_border.updateBounds(bounds);
}

bool GUI::View::isNoSet() const
{
	return ((getWidth() == MIN_WIDTH || getHeight() == MIN_HEIGHT));
}

bool GUI::View::checkBound(const sf::FloatRect& bound) const
{
	// if is no set
	if (isNoSet())
		return true;
	
	// check legal width
	if (!isLegalWidth((int) bound.width))
		return false;
	// check legal height
	if (!isLegalHeight((int) bound.height))
		return false;
	
	return true;
}

bool GUI::View::isLegalWidth(int width) const
{
	return width >= 0;
}

bool GUI::View::isLegalHeight(int height) const
{
	return height >= 0;
}

bool GUI::View::handleClickEvent(float mouseX, float mouseY)
{
	bool clicked = isPointInMyArea(mouseX, mouseY);
	if(clicked)
		callOnClick();
	return clicked;
}

bool GUI::View::handleEnterEvent(float mouseX, float mouseY)
{
	if (isPointInMyArea(mouseX, mouseY))
	{
		if (!m_mouseIn) {
			callOnEnter();
			m_mouseIn = true;
			m_mouseOut = false;
			return true;
		}	
	} else {
		m_mouseIn = false;
	}
	return false;
}

bool GUI::View::handleLeaveEvent(float mouseX, float mouseY)
{
	if (!isPointInMyArea(mouseX, mouseY))
	{
		if (!m_mouseOut) {
			callOnLeave();
			m_mouseOut = true;
			m_mouseIn = false;
			return true;
		}
	}
	else {
		m_mouseOut = false;
	}
	return false;
}

void GUI::View::handleKeyDownEvent(sf::Keyboard::Key keyCode)
{
	if (m_lastKeyDownCode != keyCode) {
		callOnKeyDown(keyCode);
		m_lastKeyDownCode = keyCode;
	}		
}

void GUI::View::handleKeyReleasedEvent(sf::Keyboard::Key keyCode)
{
	if (m_clickable) {
		callOnKeyReleased(keyCode);
		m_lastKeyDownCode = sf::Keyboard::Unknown; // reset key down
	}
}
