#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <iostream>

class Packet
{
private:
	int m_order;
	std::string m_word;
public:
	Packet();
	Packet(const std::string& word, int order);
	Packet(const Packet& other);
	~Packet();
	std::string GetWord();
	int GetOrder();
	Packet operator=(const int& a);
	friend std::ostream& operator<<(std::ostream& stream, const Packet& PT)
	{
		stream << PT.m_word;
		return stream;
	}
};

