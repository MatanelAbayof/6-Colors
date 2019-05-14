#include "PlayerBase.h"

PlayerBase::PlayerBase()
	: m_gameScreen(nullptr)
{ }

string PlayerBase::toString() const
{
	return "PlayerBase: { name=" + m_name + " }";
}