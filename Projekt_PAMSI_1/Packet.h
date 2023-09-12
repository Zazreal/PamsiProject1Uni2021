#pragma once

#include <string>
#include <iostream>

class Packet
{
private:
	int m_order;
	std::string m_word; //probowalem char* array, ale sie poddalem
public:
	Packet();
	Packet(const std::string& word, int order); //przyjmuje wszystkie potrzebne dane
	Packet(const Packet& other); //copy constructor
	~Packet();
	std::string GetWord(); //zwraca string m_word
	int GetOrder(); // zwraca m_order
	Packet operator=(const int& a); // to jest uzywane do 2 rzeczy: przypisanie order i jesli a == -1 to m_word bedzie zamienione na pustke
	friend std::ostream& operator<<(std::ostream& stream, const Packet& PT) //wypisuje m_word do ekranu
	{
		stream << PT.m_word;
		return stream;
	}
};

