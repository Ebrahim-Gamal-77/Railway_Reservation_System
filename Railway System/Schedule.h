#include<iostream>
#include<list>
#include<string>
#include<utility>

#ifndef SCHEDULE_H
#define SCHEDULE_H
using namespace std;

class Schedule {
	struct Time {

		string time;
		string stationName;
		Time() {}
		Time(string arrive, string station) {
			time = arrive;
			stationName = station;
		}
	};
	int scheduleId;
	int trainNumber;
	Time arrivalTime;
	Time departureTime;
	bool status;// 1 ===> aproved           0===>unaproved
	static list<Schedule*>schedules;//a list that stored schedules only aproved ones (note: i made it type schedule* as i want to put each object in heap cuz the size of each one is large) we show this list to the user to choose from it
	static list<Schedule*>processed_schedules;//thats the list of schedules of unaproved ones (that we made the schedule and still under checking) 
	static void adding(int id, int num, string depTime, string depStation, string arriveTime, string arriveStation, bool stat);//thats the adding function contains two adding method one for adding in the aproved ones and method for adding in unaproved ones
	static void pop_schedule(int id);//delete a schedule from the aproved schedules list (no pop method for the processed list as they still under checking no logic to delete them and we still check them)
	static void reset(int id);//an admin part that he can reset the schedule status (aproved or unaproved)
	static void add_schedule_aproved(int id, int num, string depTime, string depStation, string arriveTime, string arriveStation, bool stat);//thats the method in the adding method for adding an aproved schedule
	static void display_processed_schedules();//function  to display the un aproved list (part of update_schedules method) as only admins are allowed to see them not users
	static void add_to_processed_list(int id, int num, string depTime, string depStation, string arriveTime, string arriveStation, bool stat);//part of the Update_schedules method to allow admin to make a schedule and check on it later
	static void update(int id);//update a specific thing in the schedule
	/*static void load_schedules_from_file();
	static void save_schedules_to_file();
	static void save_processed_schedules_to_file();
	static void load_processed_schedules_from_file();*/  //some extra methods for file handling not finished yet (not important now)

	/*Some extra notes:
	adding method==> contain two methods in it add_schedule_aproved and add_to_processed_list
	Update_schedules==> contain every thing (adding ,reset,pop_schedule,display schedules,display_processed_schedules) as that function only for the admin that want to make a change from one of those options
	I made most of the methods in private as i want them hidden no one see it ever and deal with them with those methods in pubilc as i want
	Also i made a number code on Update_schedule method as if a user entered as an admin cant pass the test (some security to admins) and number is 717
	it ==> iterator i used this shortcut in every loop
	*/
public:
	Schedule() {}
	Schedule(int id, int num, Time depTime, Time arriveTime, bool stat) :scheduleId(id), trainNumber(num), arrivalTime(arriveTime), departureTime(depTime), status(stat) {}
	static void display_schedules();// as we display all the schedules for the user to choice which one fits 
	static void Update_schedules();
	static void get_schedule(int trainNum);// a user want to know his schedule we want him to enter train number and get the schedule for him
	void schedule_details();
	static void search_for_schedule(string stationName);//use it in station class as for each station name i use it to get its own schedules 
	static void send_resolution();//we send to the station our non aproved schedules so it could be hint if the station name in the resolution they close it



};
list<Schedule*>Schedule::schedules = {
	new Schedule(1,1,{"7:45 Pm","Alexandria_station"},{"10:45 Pm","Benha_station"},1), //schedule 1, train 1  ,dep (7:45) station(alex) , arrival (9:00) and station (benha)             
	new Schedule(2,2,{"3:45 pm","Alexandria_station"},{"6:45 pm","Benha_station"},1),
	new Schedule(3,3,{"5:00 Am","Mansoura_station"},{"9:00 Am","Alexandria_station"},1),
	new Schedule(4,4,{"9:00 Am","Benha_station"},{"11:00","Damietta_station"},1),
	new Schedule(5,5,{"2:00 Pm","Samannud_station"},{"7:00 Pm","Alexandria_station"},1),//???? ????? 
	new Schedule(6,6,{"4:30 Pm","Cairo_station"},{"7:30 Pm","Benha_station"},1),
	new Schedule(7,7,{"3:00 Am","Damietta_station"},{"5:00 Am","mansoura_station"},1),
	new Schedule(8,8,{"6:00 Am","Tanta_station"},{"8:30 Am","Elmahalla_station"},1),// ???? ?????


};
list<Schedule*>Schedule::processed_schedules;
void Schedule::adding(int id, int num, string depTime, string depStation, string arriveTime, string arriveStation, bool status) {
	for (auto it : schedules) {
		if (num == it->trainNumber || id == it->scheduleId) {
			cout << "be aware we cant have two trains with the same schedule or the same schedule id\n";
			return;
		}
	}

	if (status == true) {
		add_schedule_aproved(id, num, depTime, depStation, arriveTime, arriveStation, status);
	}
	else if (status == false) {
		add_to_processed_list(id, num, depTime, depStation, arriveTime, arriveStation, status);
		cout << "we have it stand by when you want to approve it\n";
	}
	cout << "Done.." << endl;
}
void Schedule::pop_schedule(int id) {

	for (auto it : schedules) {
		if (id == it->scheduleId) {
			if (it->status) {
				cout << "Thats an approved schedule are you sure you want to delete?:" << endl;
				string choice;
				cin >> choice;
				if (choice == "yes") {
					schedules.remove(it);
					cout << "Done.." << endl;
				}
				else {
					cout << "Ok saving it for now\n";
				}
				return;
			}

		}


	}

	for (auto it : processed_schedules) {
		if (id == it->scheduleId) {
			cout << "Deleting the unapproved schedule" << endl;
			processed_schedules.remove(it);
			cout << "Done." << endl;
			return;
		}
	}


	cout << "wrong Id not in our system here: " << endl;
}
void Schedule::schedule_details() {
	cout << "TrainNumber: " << trainNumber << "\n" << "Departure time and station: " << "[" << departureTime.time << "," << departureTime.stationName << "]" << "\n";
	cout << "arrive time and station: " << "[" << arrivalTime.time << "," << arrivalTime.stationName << "]";
	cout << "\n==============================\n";
}
void Schedule::get_schedule(int trainNum) {
	for (auto it : schedules) {
		if (trainNum == it->trainNumber) {
			cout << "found your schedule sir:\n";
			it->schedule_details();
			return;
		}
	}
}
void Schedule::Update_schedules() {

	cout << "\n===========Admins part===============\n";
	cout << "A small test that every admin knows to continue:\n what is the missing value in this row vector?: \n";
	cout << "[10,190,5060,4,?]\n";
	cout << "submit your answer here: ";
	int answer = 0;
	cin >> answer;
	if (answer != 717) {
		cout << "ops looks like you are not admin\n";
		return;
	}
	else {

		do {

#ifdef _WIN32  //a macro that hidden in the our code when executing a code i make sure that this code executes on windows
			system("cls");//windows clear screen command                                                             
#else
			system("clear");//linux clear screen command                     if we made the final code on a laptop uses linux                                                
#endif

			cout << "Welcome sir!\nwhat action you want to do: \n1]Add schedule  \n2]Remove schedule \n3]Reset schedule  \n4]Update schedule  \n5]Display \n6]Exit: \n";
			int order = 0;
			cin >> order;
			if (order == 1) {
				cout << "Enter data for the following requirement:" << endl;
				cout << "ScheduleId:";
				int scheduleID;
				cin >> scheduleID;
				cout << "TranNumber:";
				int trainNum;
				cin >> trainNum;
				cout << "Enter the departure time and station:";
				string depTime, depStation;
				cin >> depTime >> depStation;
				cout << "Enter the arrival time and station:";
				string arriveTime, arriveStation;
				cin >> arriveTime >> arriveStation;

				cout << "status of the schedule:" << endl;
				bool stat;
				cin >> stat;
				Schedule::adding(scheduleID, trainNum, depTime, depStation, arriveTime, arriveStation, stat);

			}
			else if (order == 2) {
				cout << "Enter the id of the schedule you want to remove:" << endl;
				int scheduleID;
				cin >> scheduleID;
				Schedule::pop_schedule(scheduleID);
			}
			else if (order == 3) {
				cout << "Enter the Id of the schedule you want:" << endl;
				int scheduleID;
				cin >> scheduleID;
				Schedule::reset(scheduleID);
			}
			else if (order == 4) {
				cout << "Enter the id of the schedule you want to update" << endl;
				int scheduleID;
				cin >> scheduleID;
				Schedule::update(scheduleID);
			}
			else if (order == 5) {
				cout << "all schedules here in the system approved and not approved\n";
				cout << "approved ones: \n";


				Schedule::display_schedules();
				cout << "\nunapproved ones " << endl;
				if (processed_schedules.size() == 0) {
					cout << "nothing added to display\n";
				}
				else {
					Schedule::display_processed_schedules();


				}

			}

			else if (order == 6) {
				cout << "Exiting...\n";
				break;
			}
			else {
				cout << "invalid operation" << endl;
			}

			cout << "\nPress Enter to continue...";
			cin.ignore();
			cin.get();
		} while (true);
	}
}



void Schedule::reset(int id) {
	cout << "you want to \n1]approve a schedule \n 2]decline one " << endl;
	int choice = 0;
	cin >> choice;
	if (choice == 1) {
		if (processed_schedules.size() == 0) {

			cout << "We dont have any unaproved schedules yet!" << endl;
			return;
		}
		for (auto it : processed_schedules) {
			if (id == it->scheduleId) {
				it->status = 1;
				processed_schedules.remove(it);
				schedules.push_back(it);
				cout << "Done the schedule is approved" << endl;
				return;
			}
		}
	}
	else if (choice == 2) {
		cout << "Great idea, you want to decline an \n1]approved one \n2] unapproved one" << endl;
		int option = 0;
		cin >> option;
		if (option == 1) {
			for (auto it : schedules) {
				if (id == it->scheduleId) {
					it->status = 0;
					schedules.remove(it);
					processed_schedules.push_back(it);
					cout << "Done" << endl;
					return;
				}
			}

		}
		else if (option == 2) {
			if (processed_schedules.size() == 0) {

				cout << "We dont have any unaproved schedules yet!" << endl;
				return;
			}
			for (auto it : processed_schedules) {
				if (id == it->scheduleId) {
					processed_schedules.remove(it);
					cout << "Done" << endl;
					return;
				}
			}
		}
		else {
			cout << "invalid operation\n";
		}
	}
	else {
		cout << "invalid operation\n";
	}

}
void Schedule::update(int id) {
	cout << "Updating\n 1] approved one \n2] unapproved" << endl;
	int choice = 0;
	cin >> choice;
	if (choice == 1) {
		cout << "you want to update\n1] arrive time  \n2] departure time" << endl;
		int option = 0;
		cin >> option;
		if (option == 1) {
			cout << "new changes enter time and station name";
			string arriveTime, arriveStation;
			cin >> arriveTime >> arriveStation;
			Time newTime(arriveTime, arriveStation);
			for (auto it : schedules) {
				if (id == it->scheduleId) {
					it->arrivalTime = newTime;
					cout << "Done" << endl;
					return;
				}
			}
		}
		else if (option == 2) {

			cout << "new changes enter time and station name";
			string depTime, depStation;
			cin >> depTime >> depStation;
			Time newTime(depTime, depStation);
			for (auto it : schedules) {
				if (id == it->scheduleId) {
					it->departureTime = newTime;
					cout << "Done" << endl;
					return;
				}
			}

		}
		else {
			cout << "invalid operation" << endl;
		}
	}
	else if (choice == 2) {
		if (processed_schedules.size() == 0) {
			cout << "Nothing in the unapproved list to update it\n";
			return;
		}
		cout << "you want to update\n1] arrive time  \n2] departure time" << endl;
		int option = 0;
		cin >> option;
		if (option == 1) {
			cout << "new changes enter time and station name";
			string arriveTime, arriveStation;
			cin >> arriveTime >> arriveStation;
			Time newTime(arriveTime, arriveStation);
			for (auto it : processed_schedules) {
				if (id == it->scheduleId) {
					it->arrivalTime = newTime;
					cout << "Done" << endl;
					return;
				}
			}
		}
		else if (option == 2) {
			cout << "new changes enter time and station name";
			string depTime, depStation;
			cin >> depTime >> depStation;
			Time newTime(depTime, depStation);
			for (auto it : processed_schedules) {
				if (id == it->scheduleId) {
					it->departureTime = newTime;
					cout << "Done";
					return;
				}
			}

		}
		else {
			cout << "invalid operation" << endl;
		}

	}
}
void Schedule::display_schedules() {


	for (auto it : schedules) {
		if (it->status == 1) {
			it->schedule_details();
			cout << "\n================================\n";
		}
	}
}
void Schedule::send_resolution()
{
	if (processed_schedules.size() == 0) {
		cout << "All clear no worries" << endl;
		return;
	}
	cout << "Hello station team we want to inform you that we have those schedules underaintenance" << endl;
	for (auto it : processed_schedules) {
		it->display_processed_schedules();
	}
	cout << "We are working hard on it to solve those problems we will inform you when finished,thank you" << endl;
}





void Schedule::add_schedule_aproved(int id, int num, string depTime, string depStation, string arriveTime, string arriveStation, bool stat) {


	Time dep(depTime, depStation);
	Time arrive(arriveTime, arriveStation);
	Schedule* new_schedule = new Schedule(id, num, dep, arrive, stat);

	schedules.push_back(new_schedule);

	cout << "Schedule added and saved !\n";
}


void Schedule::display_processed_schedules() {


	for (auto it : processed_schedules) {

		it->schedule_details();
		cout << "\n================================\n";

	}
}
void Schedule::add_to_processed_list(int id, int num, string depTime, string depStation, string arriveTime, string arriveStation, bool stat) {
	for (auto it : processed_schedules) {
		if (num == it->trainNumber || id == it->scheduleId) {
			cout << "Cannot have two trains with the same schedule or the same schedule ID in processed list\n";
			return;
		}
	}

	Time dep(depTime, depStation);
	Time arrive(arriveTime, arriveStation);
	Schedule* new_schedule = new Schedule(id, num, dep, arrive, stat);

	processed_schedules.push_back(new_schedule);

	cout << "Schedule added to processed !\n";
}
void Schedule::search_for_schedule(string stationName_) {
	cout << "station:" << stationName_ << ",schedules are : " << endl;
	for (auto it : schedules) {
		if (it->arrivalTime.stationName == stationName_ || it->departureTime.stationName == stationName_) {
			it->schedule_details();
		}
	}
}
#endif //SCHEDULE_H