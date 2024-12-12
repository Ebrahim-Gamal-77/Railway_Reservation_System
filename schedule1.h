#include<iostream>
#include<list>
#include<fstream>
#include<sstream>
#include<string>
using namespace std;
class schedule {
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
	static list<schedule*>schedules;//a list that stored schedules only aproved ones (note: i made it type schedule* as i want to put each object in heap cuz the size of each one is large) we show this list to the user to choose from it
	static list<schedule*>processed_schedules;//thats the list of schedules of unaproved ones (that we made the schedule and still under checking) 
	static void adding(int id, int num, string depTime, string depStation, string arriveTime, string arriveStation,bool stat);//thats the adding function contains two adding method one for adding in the aproved ones and method for adding in unaproved ones
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
	schedule() {}
	schedule(int id, int num, Time depTime, Time arriveTime, bool stat) :scheduleId(id), trainNumber(num), arrivalTime(arriveTime), departureTime(depTime), status(stat) {}
	static void display_schedules();// as we display all the schedules for the user to choice which one fits 
	static void Update_schedules();
	static void get_schedule(int trainNum);// a user want to know his schedule we want him to enter train number and get the schedule for him
	void schedule_details();



};
list<schedule*>schedule::schedules = {
	new schedule(1,1,{"7:45 Pm","Alexandria_station"},{"10:45 Pm","Benha_station"},1), //schedule 1, train 1  ,dep (7:45) station(alex) , arrival (9:00) and station (benha)             
	new schedule(2,2,{"3:45 pm","Alexandria_station"},{"6:45 pm","Benha_station"},1),
	new schedule(3,3,{"5:00 Am","Mansoura_station"},{"9:00 Am","Alexandria_station"},1),
	new schedule(4,4,{"9:00 Am","Benha_station"},{"11:00","Damietta_station"},1),
	new schedule(5,5,{"2:00 Pm","Samannud_station"},{"7:00 Pm","Alexandria_station"},1),//???? ????? 
	new schedule(6,6,{"4:30 Pm","Cairo_station"},{"7:30 Pm","Benha_station"},1),
	new schedule(7,7,{"3:00 Am","Damietta_station"},{"5:00 Am","mansoura_station"},1),
	new schedule(8,8,{"6:00 Am","Tanta_station"},{"8:30 Am","Elmahalla_station"},1),// ???? ?????

	
};
list<schedule*>schedule::processed_schedules;
void schedule::adding(int id, int num, string depTime, string depStation, string arriveTime, string arriveStation, bool status) {
	for (auto it : schedules) {
		if (num == it->trainNumber || id == it->scheduleId) {
			cout << "be aware we cant have two trains with the same schedule or the same schedule id\n";
			return;
		}
	}
	
	if (status == 1) {
		add_schedule_aproved(id, num, depTime, depStation, arriveTime, arriveStation, stat);
	}
	else if (status == 0) {
		add_to_processed_list(id, num, depTime, depStation, arriveTime, arriveStation, stat);
		cout << "we have it stand by when you want to approve it\n";
	}
	cout << "Done.." << endl;
}
void schedule::pop_schedule(int id) {
	
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
void schedule::schedule_details() {
	cout << "ScheduleNumber: " << scheduleId << "\n" << "TrainNumber: " << trainNumber << "\n" << "Departure time and station: " << "[" << departureTime.time << "," << departureTime.stationName << "]" << "\n";
	cout << "arrive time and station: " << "[" << arrivalTime.time << "," << arrivalTime.stationName << "]";
}
void schedule::get_schedule(int trainNum) {
	for (auto it : schedules) {
		if (trainNum == it->trainNumber) {
			cout << "found your schedule sir:\n";
			it->schedule_details();
			return;
		}
	}
}
void schedule::Update_schedules() {
	
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
					schedule::adding(scheduleID, trainNum, depTime, depStation, arriveTime, arriveStation, stat);
					
				}
				else if (order == 2) {
					cout << "Enter the id of the schedule you want to remove:" << endl;
					int scheduleID;
					cin >> scheduleID;
					schedule::pop_schedule(scheduleID);
				}
				else if (order == 3) {
					cout << "Enter the Id of the schedule you want:" << endl;
					int scheduleID;
					cin >> scheduleID;
					schedule::reset(scheduleID);
				}
				else if (order == 4) {
					cout << "Enter the id of the schedule you want to update" << endl;
					int scheduleID;
					cin >> scheduleID;
					schedule::update(scheduleID);
				}
				else if (order == 5) {
					cout << "all schedules here in the system approved and not approved\n";
					cout << "approved ones: \n";
					
				
					schedule::display_schedules();
					cout << "\nunapproved ones " << endl;
					if (processed_schedules.size() == 0) {
						cout << "nothing added to display\n";
					}
					else {
						schedule::display_processed_schedules();
						
						
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



void schedule::reset(int id) {
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
void schedule::update(int id) {
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
					cout << "Done" <<  endl;
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
void schedule::display_schedules() {
	

	for (auto it : schedules) {
		if (it->status == 1) {
			it->schedule_details();
			cout << "\n================================\n";
		}
	}
}





void schedule::add_schedule_aproved(int id, int num, string depTime, string depStation, string arriveTime, string arriveStation, bool stat) {
	

	Time dep(depTime, depStation);
	Time arrive(arriveTime, arriveStation);
	schedule* new_schedule = new schedule(id, num, dep, arrive, stat);

	schedules.push_back(new_schedule);
	//save_schedules_to_file(); // Save the updated schedules to the file
	cout << "Schedule added and saved !\n";
}
//void schedule::save_processed_schedules_to_file() {
//	ofstream file("D:\data structure project\processed.txt"); // Open the processed schedule file for writing
//
//	if (!file.is_open()) {
//		cout << "Could not open file for saving processed schedules\n";
//		return;
//	}
//
//	// Write each processed schedule to the file
//	for (auto it : processed_schedules) {
//		file << it->schedule_id << " "
//			<< it->train_number << " "
//			<< it->departure_time.time << " " << it->departure_time.station_name << " "
//			<< it->arrival_time.time << " " << it->arrival_time.station_name << " "
//			<< it->status << "\n";
//	}
//
//	file.close(); // Close the file
//}
//void schedule::load_processed_schedules_from_file() {
//	ifstream file("D:\data structure project\processed.txt"); // Open the processed schedule file for reading
//	string line;
//	if (!file.is_open()) {
//		
//		return;
//	}
//
//	// Clear current processed schedules before loading from file
//	processed_schedules.clear();
//
//	// Read the file and load processed schedules
//	while (getline(file, line)) {
//		stringstream ss(line);
//		int id, num, stat;
//		string dep_time, dep_station, arri_time, arri_station;
//
//		ss >> id >> num >> dep_time >> dep_station >> arri_time >> arri_station >> stat;
//		Time dep(dep_time, dep_station);
//		Time arri(arri_time, arri_station);
//		processed_schedules.push_back(new schedule(id, num, dep, arri, stat));
//	}
//
//	file.close(); // Close the file
//}
void schedule::display_processed_schedules() {
	//load_processed_schedules_from_file(); // Load processed schedules from the file

	for (auto it : processed_schedules) {
		
			it->schedule_details();
			cout << "\n================================\n";
		
	}
}
void schedule::add_to_processed_list(int id, int num, string depTime, string depStation, string arriveTime, string arriveStation, bool stat) {
	for (auto it : processed_schedules) {
		if (num == it->trainNumber || id == it->scheduleId) {
			cout << "Cannot have two trains with the same schedule or the same schedule ID in processed list\n";
			return;
		}
	}

	Time dep(depTime, depStation);
	Time arrive(arriveTime, arriveStation);
	schedule* new_schedule = new schedule(id, num, dep, arrive, stat);

	processed_schedules.push_back(new_schedule);
	
	cout << "Schedule added to processed !\n";
}




