#include "PlayerBase.h"

PlayerBase::PlayerBase()
{ }

string PlayerBase::toString() const
{
	return "PlayerBase: { name=" + m_name + " }";
}