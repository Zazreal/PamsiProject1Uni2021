
#include "Stack.h"
#include "Packet.h"
//#include "Timer.h"
#include <iostream>
#include <string>
#include <sstream>
#include <time.h>

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
	
	//std::string default_message = "This is a default message used for testing!\0";
	/*
	std::string benchmarking = "";
	for (int i = 0; i < 5000; i++)
		benchmarking += "a ";
	Timer timer;
	*/
	
	std::string message = "";
	std::cout << "Please, input the message" << std::endl;
	std::getline(std::cin, message); //getline bo cin the akceptuje calych zdan
	
	//rozpoczecie operacji rozbierania zdania na wyrazy
	std::stringstream ss(message);
	std::string tempstr = " ";
	char separator = ' ';
	char sep = 32;
	int order = 0;
	Stack<Packet> Packet_Array(0);
	//std::cout << "Getline start\n";
	while (std::getline(ss, tempstr, sep))
	{
		Packet newpacket(tempstr, order);
		Packet_Array.push(newpacket);
		++order;
	}
	//tutaj sie konczy
	//std::cout << "Getline end\n";
	//std::cout << "Packet array complete" << std::endl;

	//PrintStack(Packet_Array);

	//tutaj mieszam losowo wyrazy w stacku tak jakby mialy dotrzec w losowej kolejnosci
	shuffle(Packet_Array);
	//PrintStack(Packet_Array);
	
	std::cout << "Message received: \n";
	for (int i = 0; i < Packet_Array.GetSize(); i++) std::cout << Packet_Array[i].GetWord() << " ";
	std::cout << std::endl;
	
	//PrintStack(Packet_Array);

	//Tutaj "odbieram" wiadomosc i uzywam algorytmu sortowania
	Receive_Message(Packet_Array);

	//PrintStack(Packet_Array);

	//getchar();
	//__debugbreak();
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
}

void Receive_Message(Stack<Packet>& Packets)
{
	//To jest bubble sort bo jest latwy do implementacji, mimo tego ze wolny
	std::string message_received = "";
	int size = Packets.GetSize();
	//std::cout << "\entering bubble sort\n";
	for (int i = 0; i < Packets.GetSize() - 1; ++i)
	{
		//std::cout << "\ni: " << i << "\n";
		for (int j = 0; j < Packets.GetSize()-i-1; ++j)
		{
			if (Packets[j].GetOrder() < Packets[j + 1].GetOrder()) std::swap(Packets[j], Packets[j + 1]);
		}
	}
	//std::cout << "\exiting bubble sort\n";
	//tutaj pop'uje caly stack do wiadomosci
	for (int i = 0; i < size; ++i)
	{
		message_received += Packets.pop().GetWord() + " ";
	}
	std::cout << "Message displayed: \n";
	std::cout << message_received;
	for (int i = 0; i < Packets.GetSize(); i++) std::cout << Packets[i].GetWord() << " ";
}