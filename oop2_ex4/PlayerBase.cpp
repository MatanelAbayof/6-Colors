#include "PlayerBase.h"



const string & PlayerBase::getName() const
{
	return m_name;
}

void PlayerBase::setName(const string & name)
{
	m_name = name;
}

string PlayerBase::toString() const
{
	return "PlayerBase: { name =" + m_name + " } ";
}

PlayerBase::PlayerBase()
{
}


PlayerBase::~PlayerBase()
{
}
