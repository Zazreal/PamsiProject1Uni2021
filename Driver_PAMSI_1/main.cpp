#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "Stack.h"
#include "Packet.h"
#include <sstream>
#include <time.h>
//#include <thread>
//#include <chrono>

//Ta funkcja cos szwankowala, wiec ten kod jest w main
//Stack<Packet> Send_Message(const std::string message);

//To jest funkcja "otrzymymwania" wiadomosci, po prostu segreguje stack
//i go wyswietla w odpowiedniej kolejnosci
void Receive_Message(Stack<Packet>& Packets);

// W tej funkcji jest mnostwo zakomentowanego debugowania
// Do czego sluzy, nazwa mowi za siebie
void shuffle(Stack<Packet>& Packet_Array);

//To jest funkcja ktorej uzywalem do debugowania.
//Po prostu wyswietla co jest w calym stacku, bardzo pomogla
void PrintStack(Stack<Packet>& Packet_Array);

int main() 
{

	std::string default_message = "This is a default message used for testing!\0";
	std::string message = "";
	std::string tempstr = " ";
	char separator = ' ';
	int order = 0;
	Stack<Packet> Packet_Array(0);
	char YN = ' ';
	bool cont = true;
	std::stringstream ss(default_message);
	while (std::getline(ss, tempstr, separator))
	{
		Packet newpacket(tempstr, order);
		Packet_Array.push(newpacket);
		++order;
	}
	std::cout << "Start the driver? Y/N\n";
	while (cont){
		std::cin >> YN;
		if (YN == 'Y')
		{
			Packet driverhelp("thing", order++);
			std::cout << "\nStack.GetSize(): ";
			std::cout << Packet_Array.GetSize();
			std::cout << "\nStack.IsEmpty(): ";
			std::cout << Packet_Array.IsEmpty();
			std::cout << "\nStack.top(): ";
			Packet temp = Packet_Array.top();
			std::cout << temp << " Size: " << Packet_Array.GetSize();
			std::cout << "\nStack.push(): ";
			Packet_Array.push(driverhelp);
			temp = Packet_Array.top();
			std::cout << temp << " new Size: " << Packet_Array.GetSize();
			std::cout << "\nStack.pop(): ";
			temp = Packet_Array.pop();
			std::cout << temp << " new Size: " << Packet_Array.GetSize();
			std::cout << "\nStack operator[const int index] (tutaj 0): ";
			std::cout << Packet_Array[0];
			std::cout << "\nPacket.GeWord(): ";
			std::cout << driverhelp.GetWord();
			std::cout << "\nPacket.GetOrder(): ";
			std::cout << driverhelp.GetOrder();
			std::cout << "\nPacket operator<<(std::ostream& stream, const Packet& PT): ";
			std::cout << driverhelp;
			std::cout << "\nPacket operator=(const int& a) (tutaj -1) : ";
			driverhelp = -1;
			std::cout << driverhelp;
			std::cout << "\nPrintStack function: ";
			PrintStack(Packet_Array);
			std::cout << "\nshuffle function: ";
			shuffle(Packet_Array);
			std::cout << "\nReceive_Message function: ";
			Receive_Message(Packet_Array);
			cont = false;
		}
		else if (YN == 'N')
		{
			std::cout << "Exiting..." << std::endl;
			cont = false;
		}
		else {
			std::cout<<"Wrong input, try again" << std::endl;
		}
	}
	//getchar();
	return EXIT_SUCCESS;
}

//To jest funkcja ktorej uzywalem do debugowania.
//Po prostu wyswietla co jest w calym stacku, bardzo pomogla
void PrintStack(Stack<Packet>& Packet_Array)
{
	std::cout << std::endl;
	for (int i = 0; i < Packet_Array.GetSize(); i++)
	{
		std::cout << "Packet " << i << ": " << Packet_Array[i].GetWord() << ", Order: " << Packet_Array[i].GetOrder() << "\n";
	}
}

//Ta funkcja cos szwankowala, wiec ten kod jest w main
/*
Stack<Packet> Send_Message(const std::string default_message)
{
	std::stringstream ss(default_message);
	std::string tempstr = " ";
	char separator = ' ';
	int order = 0;
	Stack<Packet> Packet_Array(1);
	std::cout << "Getline start\n";
	while(std::getline(ss, tempstr, separator))
	{
		Packet newpacket(tempstr, order);
		Packet_Array.push(newpacket);
	}
	std::cout << "Getline end\n";
	return Packet_Array;
}
*/


// W tej funkcji jest mnostwo zakomentowanego debugowania
void shuffle(Stack<Packet>& Packet_Array)
{
	//to jest ten standardowy RNG z srandem i time(NULL)
	srand(time(NULL) + Packet_Array.GetSize());
	int first = 0;
	int second = 0;
	int PA = Packet_Array.GetSize();
	//std::cout << Packet_Array.GetSize();// / 2;
	for (int i = 0; i < PA; i++) {
		first = rand() % Packet_Array.GetSize();
		second = rand() % Packet_Array.GetSize();
		std::swap(Packet_Array[first], Packet_Array[second]);

		//std::cout << "i: " << i << std::endl;
		//std::cout << "first: " << first << std::endl;
		//std::cout << "second: " << second << std::endl;
		//std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	PrintStack(Packet_Array);
}

void Receive_Message(Stack<Packet>& Packets)
{
	//To jest bubble sort bo jest latwy do implementacji, mimo tego ze wolny
	std::string message_received = "";
	int size = Packets.GetSize();
	for (int i = 0; i < Packets.GetSize() - 1; ++i)
	{
		for (int j = 0; j < Packets.GetSize()-i-1; ++j)
		{
			if (Packets[j].GetOrder() < Packets[j + 1].GetOrder()) std::swap(Packets[j], Packets[j + 1]);
		}
	}
	//tutaj pop'uje caly stack do wiadomosci
	for (int i = 0; i < size; ++i)
	{
		message_received += Packets.pop().GetWord() + " ";
	}
	std::cout << "\nMessage displayed: \n";
	std::cout << message_received;

	//for (int i = 0; i < Packets.GetSize(); i++) std::cout << Packets[i].GetWord() << " ";
}