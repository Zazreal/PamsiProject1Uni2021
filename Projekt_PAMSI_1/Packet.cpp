
#include "Packet.h"
#include <string>

Packet::Packet()
{
}

Packet::Packet(const std::string& word, int order) : m_order{ order }, m_word{word}
{
}

Packet::Packet(const Packet& other): m_order(other.m_order), m_word{other.m_word}
{
}

Packet::~Packet()
{
}

std::string Packet::GetWord()
{
	return m_word;
}

int Packet::GetOrder()
{
	return m_order;
}

Packet Packet::operator=(const int& a)
{
	if (-1 == a) {
		m_order = -1;
		m_word = "";
	}
	this->m_order = a;
	return *this;
}