
#include "Schedule.h"
#ifndef STATION_H //MACRO to check for the header file
#define STATION_H
using namespace std;

class Station {
	int stationID;
	string stationName;
	string stationLocation;
	bool underMaintenance;
	string emergencyNumber;
	static list<Station*>stations;
	static list<pair<string, string>>reports_applied;


	static void show_stations_details();//this function display station name and its schedules (arrival and departure)
	static void announcement(string stationName);//as the admin saw the reports he will announce to the station there is a problem so we stopped this station for now

	static void add_station(int id, string stationName1, string stationLocation1, bool stat, string number);
	static void delete_station(string stationName1);

	void station_details();//used in show_stations_details 
	static void show_reports();//display the reports for the admin so he can take a decision 
	static void stop_station(int id);//admin could close the station cause of the report applied
public:
	Station() {}
	Station(int id, string stationname, string loct, bool Maintenance, string number) :stationID(id), stationName(stationname), stationLocation(loct), underMaintenance(Maintenance), emergencyNumber(number) {}

	static void emergency_report();//a user saw something wrong in the station and want to report it so an admin help in it (two trains crashed for example) so we shut that station and schedules.
	static void display_station_schedules(string stationName);//as user enter the station name so we display for him all schedules of that station

	static void manage_stations();// for admins only (i made an row vector ) thats not ideal ,later i will make it check by username if admin or not




};
list<Station*>Station::stations = {
	new Station(1,"Alexandria_station","Alexandria",1,"145"),// stationID==> 1      Name==>Alexandria_station            location====>Alexandria        status===> valid station no obsticals     if status ==>1 assign empty string.
	new Station(2,"Mansoura_station","Mansoura",1,"177"),
	new Station(3,"Benha_station","Benha",1,"199"),
	new Station(4,"Samannud_station","Samannud",1,"133"),
	new Station(5,"Damietta_station","Damietta",1,"144"),
	new Station(6,"Cairo_station","Cairo",1,"127"),
	new Station(7,"Tanta_station","Tanta",1,"191"),
	new Station(8,"Elmahalla_station","Elmahalla",1,"156")


};
list<pair<string, string>>Station::reports_applied;
void Station::show_stations_details()
{
	cout << "all stations and their schedules" << endl;
	cout << "==============================\n";
	for (auto it : stations) {
		it->station_details();
		schedule::search_for_schedule(it->stationName);

	}
}
void Station::announcement(string stationName)
{
	if (reports_applied.size() == 0) {
		cout << "No reports sent yet to announce anything" << endl;
		return;
	}
	cout << "Dear,customers based on on a report sent for us : " << endl;
	for (auto it : reports_applied) {
		if (stationName == it.first) {
			cout << "Station name:" << it.first << "and report :" << it.second << endl;
			cout << "We will stop this station for now to make it better for you and hope we match your expectations" << endl;
			return;
		}

	}
}
void Station::add_station(int id, string stationName1, string stationLocation1, bool stat, string number)
{
	for (auto it : stations) {
		if (it->stationID == id) {
			cout << "Be aware can\'t have two stations with the same id" << endl;
			return;
		}
	}
	Station* newStation = new Station(id, stationName1, stationLocation1, stat, number);
	stations.push_back(newStation);



}
void Station::delete_station(string stationName1)
{
	for (auto it : stations) {
		if (it->stationName == stationName1) {
			stations.remove(it);
			cout << "Done" << endl;
			return;
		}
	}
	cout << "No station with the name you provide" << endl;
	return;

}
void Station::emergency_report() {

	cout << "Hello sir, this is the central emergency number " << endl;
	cout << "===================================================\n";
	cout << "Enter the emergency number of the station here sir to switch you to it:" << endl;
	string stationNumber;
	cin >> stationNumber;
	bool isFound = 0;
	string station_name = "";
	for (auto it : stations) {
		if (it->emergencyNumber == stationNumber) {
			isFound = 1;
			station_name = it->stationName;
			break;
		}
	}
	if (isFound) {
		cout << "Hello sir this the emergency number of " << station_name << endl;
		cout << "please submit your report here sir:" << endl;
		string report;
		cin >> report;
		for (auto it : stations) {
			if (it->stationName == station_name) {
				reports_applied.push_back({ it->stationName,report });

				cout << "Thank you sir for helping us be better we will solve it no worries" << endl;
				return;
			}
		}
	}
	else {
		cout << "The number you entered is false sir please try again with the correct one" << endl;
	}

}

void Station::display_station_schedules(string name)
{
	for (auto it : stations) {
		if (it->stationName == name && it->underMaintenance == 1) {

			schedule::search_for_schedule(it->stationName);
			return;
		}
	}
	cout << "Invalid station name sir try again later " << endl;
	return;
}

void Station::manage_stations()
{
	cout << "====================Admains part=====================" << endl;
	cout << "A small test so you can enter to see the data " << endl;
	cout << "What is the missing value in this row vector" << endl;
	cout << "[123,789,192,900,?]" << endl;
	cout << "Submit your answer here:" << endl;
	string answer;
	cin >> answer;
	if (answer == "2005") {
		do {
#ifdef _WIN32  //a macro that hidden in the our code when executing a code i make sure that this code executes on windows
			system("cls");//windows clear screen command                                                             
#else
			system("clear");//linux clear screen command                     if we made the final code on a laptop uses linux                                                
#endif
			cout << "Welcome to the station management part" << endl;
			cout << "1]Display stations\n";
			cout << "2]Add station\n";
			cout << "3]Remove station\n";
			cout << "4]Show stopped schedules" << endl;
			cout << "5]Stop station" << endl;
			cout << "6]Announcement" << endl;
			cout << "7] Exit" << endl;
			cout << "Enter your choice from those operations " << endl;
			int option;
			cin >> option;
			switch (option) {
			case 1:
				Station::show_stations_details();
				break;
			case 2: {
				cout << "Enter the id of the station you want to add:" << endl;
				int stationId;
				cin >> stationId;
				cout << "Enter the station name that you want to add:" << endl;
				string stationName;
				cin >> stationName;
				cout << "Enter the Location of the station:" << endl;
				string location;
				cin >> location;
				cout << "Enter the status of the stataion (1 or 0):" << endl;
				bool status;
				cin >> status;
				cout << "Enter the emergency number of this station:" << endl;
				string number;
				cin >> number;
				Station::add_station(stationId, stationName, location, status, number);
				break;
			}
			case 3: {
				cout << "Enter the name of the station you want to delete from the system :" << endl;
				string stationName;
				cin >> stationName;
				Station::delete_station(stationName);
				break;
			}
			case 4:
				schedule::send_resolution();
				break;
			case 5: {
				cout << "Enter the name of the id of station you want to stop" << endl;
				int id;
				cin >> id;
				Station::stop_station(id);
				break;
			}
			case 6: {
				cout << "Enter the name of the station will display this announcement" << endl;
				string stationName1;
				cin >> stationName1;
				Station::announcement(stationName1);
				break;
			}
			case 7:
				cout << "Exiting....!" << endl;
				return;
			default:
				cout << "invalid operation" << endl;
				break;
			}
			cout << "\nPress Enter to continue...";
			cin.ignore();
			cin.get();
		} while (true);


	}
	else {
		cout << "Ops looks like you are not an admain" << endl;
	}

}

void Station::stop_station(int id)
{
	bool is_found = false;
	for (auto& it : stations) {
		if (id == it->stationID) {
			it->underMaintenance = 0;
			is_found = true;
			break;
		}
	}

	if (is_found) {
		if (!reports_applied.empty()) {  // Check if reports_applied is not empty
			for (auto& it : reports_applied) {
				reports_applied.remove(it);
			}
		}
		cout << "Done!" << endl;
	}
	else {
		cout << "No station with this name you entered" << endl;
	}
}



void Station::station_details()
{
	cout << "Station name:" << stationName << endl;
	cout << "Station location:" << stationLocation << endl;
	cout << "Emergency number:" << emergencyNumber << endl;
	cout << "station status:" << underMaintenance << endl;

}

void Station::show_reports()
{
	if (reports_applied.size() == 0) {
		cout << "No reports sent yet,all clear!" << endl;
		return;
	}
	cout << "The following are the reports of some customers:" << endl;
	for (auto it : reports_applied) {
		cout << "Station name:" << it.first << "report details" << it.second << endl;
		cout << "==================================\n";
	}
}
#endif //STATION_H


