#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <assert.h>
#include <sstream>
using namespace std;

class Coach {
	long long id;

	array<bool, 30>Seats { };//Initially false(zero)

	int Reserved_Seats{ }; //Initially zero

	int Available_Seats{ 30 }; // Initially 30.
public:
	Coach() :id(0) {}

	Coach(long long ID, int num_of_Available_Seat, int num_of_Reserved_Seat);

	int Reserved_Seats_num();

	int Available_Seats_num();

	bool Check_Availability();

	void Reserve_Seat();

	void Set_id(long long Id);

	friend ostream& operator << (ostream& output, const Coach& c);// Output all the content of Coach

};

Coach::Coach(long long ID, int num_of_Available_Seat, int num_of_Reserved_Seat)
	:id(ID), Available_Seats(num_of_Available_Seat), Reserved_Seats(num_of_Reserved_Seat) {}

void Coach::Set_id(long long Id)
{
	id = Id;
}

ostream& operator << (ostream& output, const Coach& obj)
{
	output << "\n\nID: " << obj.id << "\t\t" << "Num of reserved seats: " << obj.Reserved_Seats

		<< "\t\t" << "Num of available seat: " << obj.Available_Seats << "\t\n\n";

	return output;
}

int Coach::Reserved_Seats_num()
{
	return Reserved_Seats;
}

int Coach::Available_Seats_num()
{
	return Available_Seats;
}

bool Coach::Check_Availability()
{
	return Available_Seats; // if the value > 0,it will return true...if not will return false (0)
}

void Coach::Reserve_Seat()
{
	if (Reserved_Seats_num() == 30)

		cout << "\nFully Reserved.";

	else
	{	
		int seat_num ;
		do
		{
			cout << "\n\nEnter the propere seat (1 : 30): ";
			cin >> seat_num;

		} while (seat_num > 30 || seat_num < 1);

		if (Seats[seat_num - 1])
		{
			cout << "\nSeat already booked. Please choose another seat.\n";
			Reserve_Seat(); // Recursive call.
		}
		else
		{

			Seats[seat_num - 1] = true;

			Available_Seats--;
			Reserved_Seats++;

			cout << "\nReservation done.\n";
		}
	}
}

class Train
{
	long long Id;

	vector<Coach>Coachs_of_train; // Composition: train has a 10 coach.

public:
	Train():Coachs_of_train(10) {}

	Train(long long ID) : Id(ID) {}

	void Class_Levels();
};

void Train::Class_Levels()
{
	cout << "\n\t\t1A:First Class air conditioned.\t 2A:Second Class air conditioned.\n\n\n"

		<< "\t\t3A:Third Class air conditioned.\t CC:AC Chair Car.\n\n\n";

	string type("");

	do
	{
		cout << "Enter the type (1A,2A,3A,CC) : ";
		cin >> type;

	} while (type != "1A" && type != "1a" && type != "2A" && type != "2a" &&
		type != "3a" && type != "3A" && type != "CC" && type != "cc" && type != "Cc");

	if (type == "1A" || type == "1a")
	{
		Coachs_of_train[0].Set_id(301);
		cout << Coachs_of_train[0];
		Coachs_of_train[0].Reserve_Seat();
	}
	else if (type == "2A" || type == "2a")
	{
		Coachs_of_train[1].Set_id(302);
		cout << Coachs_of_train[1];
		Coachs_of_train[1].Reserve_Seat();
	}
	else if (type == "3A" || type == "3a")
	{
		Coachs_of_train[2].Set_id(303);
		cout << Coachs_of_train[2];
		Coachs_of_train[2].Reserve_Seat();
	}
	else
	{
		Coachs_of_train[3].Set_id(304);
		cout << Coachs_of_train[3];
		Coachs_of_train[3].Reserve_Seat();
	}
}

struct Train_node
{
	Train_node* next{ };
	Train data{ };
	Train_node() {} //Default Constructor.
};


class admin
{
	int Platform{ };
	string Depart, Destination;
	Train_node* head { }; // points to nullptr.
	int Num_of_stops{ };
	string Train_Status;// Delayed_Canceled_Ontime.
public:
	void Consol();

};
void admin::Consol()
{
	cout << "\t\t_______________ Egypt Railways ________________\n\n";

	cout << "Departing from: ";
	cin >> Depart;
	cout << "Going to: ";
	cin >> Destination;

	cout << "\n\n1:High speed train\t\t 2:Diesel train\t\t 3:Electric train \t\t 4:Monorail \n\n";

	int option;
	do
	{
		cout << "Choose option from 1 to 4:";
		cin >> option;

	} while (option < 1 || option>4);

	head->data.Class_Levels();
}


int main()
{
	admin a;
	a.Consol();
}