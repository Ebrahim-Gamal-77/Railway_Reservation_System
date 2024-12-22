#include<ratio>
#include<iostream>
#include<iomanip>
#include <chrono>
#include <ctime>
#include <array>
#include <vector>
#include <assert.h>
#include <climits>
#include <sstream>
#include <unordered_map>
#include "station1.h"

using namespace std;


class Feedback {
    static int counter;
    int feedbackid;
    int accountid;
    int rating;
    string message;
    static list<Feedback> feedbacks;

public:
    Feedback(int Accountid, string Message, int Rating) {
        feedbackid = ++counter;
        accountid = Accountid;
        message = Message;
        rating = Rating;
    }

    Feedback() {
        feedbackid = ++counter;
    }

    void sumbitfeedback() {
        Feedback newFeedback;
        cout << "-Enter your account id: ";
        cin >> newFeedback.accountid;
        cout << "\n-Rate your trip out of 5: ";
        do {
            cin >> newFeedback.rating;
            if (newFeedback.rating > 5) {
                cout << "\nEnter a valid rating! ";
            }
        } while (newFeedback.rating > 5);
        cout << "-Enter your Suggestions: ";
        cin.ignore();
        getline(cin, newFeedback.message);
        feedbacks.push_back(newFeedback);
        cout << "\nFeedback submitted successfully!\n";
    }

    void getFeedbackDetails() {
        /*int id;
        cout << "\n-Enter the feedback id: ";
        cin >> id;

        if (id <= 0 || id > static_cast<int> (feedbacks.size())) {
            cout << "\nInvalid feedback ID!\n";
            return;
        }*/


        cout << "Account ID: " << feedbackid << endl;
        cout << "Rating of the trip: " << rating << endl;
        cout << "Message of the feedback:\n\" " << message << " \"" << endl;
    }

    void displayfeedbacks() {
        if (feedbacks.size() == 0) {
            cout << "No feedbacks sent yet" << endl;
            return;
        }
        cout << "============================= Feedbacks # =============================\n";
        for (auto it: feedbacks) {
            it.getFeedbackDetails();
        }
    }
};

list<Feedback> Feedback::feedbacks = {};

int Feedback::counter = 0;

void Consleui() {
    Feedback feedback;
    int choice = 0;
    while (true) {
#ifdef _WIN32
        system("cls"); // clear screen for better UI
#else
        system("clear"); // clear screen for better UI
#endif
        cout << "********** Feedback Page ************\n\n";
        cout << "1) Submit feedback.\n";
        cout << "2) Feedback Details.\n";
        cout << "3) Exit.\n";
        cout << "-Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                feedback.sumbitfeedback();
                system("pause");
                break;
            }
            case 2: {
                feedback.getFeedbackDetails();
                system("pause");
                break;
            }
            case 3: {
                cout << "\nExit feedback !\n ";
                return;
            }
            default:
                cout << "Invalid choice. Try again!\n";
                system("pause");
        }
    }
}


class Ticket {
private:
    int ticketID;
    string passengerName;
    int trainID;
    string seatNumber;
    double fare;
    bool status; // "Booked" or "Cancelled"
    string bookingDate; // Date of booking

public:
    // Default constructor
    Ticket() : ticketID(1), trainID(1), status(true) {
    }

    // Parameterized constructor to initialize Ticket
    Ticket(int id, string name, int train, string seat, double price, const string &date)
        : ticketID(id), passengerName(name), trainID(train), seatNumber(seat), fare(price), status(true),
          bookingDate(date) {
    }

    // Getters
    int getTicketID() const { return ticketID; }
    string getPassengerName() const { return passengerName; }
    int getTrainID() const { return trainID; }
    string getSeatNumber() const { return seatNumber; }
    double getFare() const { return fare; }
    string getStatus() const { return status ? "Booked" : "Cancelled"; }
    string getBookingDate() const { return bookingDate; }

    // Cancel Ticket
    void cancelTicket() {
        if (status == true) {
            status = false;
            cout << "Ticket " << ticketID << " has been cancelled.\n";
        } else {
            cout << "Ticket " << ticketID << " is already cancelled.\n";
        }
    }

    // Update Ticket Details
    void updateDetails(const string &newSeat, double newFare) {
        if (status == true) {
            seatNumber = newSeat;
            fare = newFare;
            cout << "Ticket " << ticketID << " has been updated.\n";
        } else {
            cout << "Cannot update a cancelled ticket.\n";
        }
    }

    // Display Ticket Details
    void displayTicket() const {
        cout << "\nTicket ID: " << ticketID
                << "\nPassenger Name: " << passengerName
                << "\nTrain ID: " << trainID
                << "\nSeat Number: " << seatNumber
                << "\nFare: $" << fixed << setprecision(2) << fare
                << "\nStatus: " << (status ? "Booked" : "Cancelled")
                << "\nBooking Date: " << bookingDate << "\n";
    }
};

// Reservation class
class Reservation {
private:
    static unordered_map<int, Ticket> tickets; // Maps ticket ID to Ticket object
    int nextTicketID; // To track the next available ticket ID

    // Get current date in YYYY-MM-DD format
    string getCurrentDate() const {
        time_t now = time(0);
        tm local_tm;

#ifdef _WIN32
        localtime_s(&local_tm, &now);  // Windows-specific
#else
        localtime_r(&now, &local_tm); // POSIX-compliant
#endif

        char date[11];
        strftime(date, sizeof(date), "%Y-%m-%d", &local_tm);
        return string(date);
    }

public:
    // Constructor initializes nextTicketID to 1
    Reservation() : nextTicketID(1) {
    }

    // Book a Ticket
    void bookTicket(const string &passengerName, int trainID, const string &seatNumber, double fare) {
        string date = getCurrentDate(); // Get current date
        Ticket newTicket(nextTicketID, passengerName, trainID, seatNumber, fare, date); // Create new ticket
        tickets[nextTicketID] = newTicket; // Store ticket in unordered_map
        cout << "Ticket booked successfully. Ticket ID: " << nextTicketID << "\n";

        nextTicketID++; // Increment ticket ID for the next booking
    }

    // Cancel a Ticket
    void cancel_Ticket(int ticketID) {
        for (auto it: tickets) {
            if (it.first == ticketID) {
                it.second.cancelTicket();
                return;
            }
        }
        cout << "Ticket ID " << ticketID << " not found.\n";
    }

    // Update Ticket
    void updateTicket(int ticketID, const string &newSeat, double newFare) {
        auto it = tickets.find(ticketID); // Find ticket by ID
        if (it != tickets.end()) {
            // If ticket found
            it->second.updateDetails(newSeat, newFare); // Update ticket details
        } else {
            cout << "Ticket ID " << ticketID << " not found.\n";
        }
    }

    // Display All Tickets
    void displayAllTickets() const {
        if (tickets.empty()) {
            cout << "No tickets booked yet.\n";
            return;
        }

        cout << "\n--- All Tickets ---\n";
        for (const auto &pair: tickets) {
            pair.second.displayTicket(); // Display each ticket
        }
    }

    // Search Tickets by Passenger Name
    void searchTicketsByPassenger(const string &name) const {
        bool found = false;
        for (const auto &pair: tickets) {
            if (pair.second.getPassengerName() == name) {
                pair.second.displayTicket(); // Display ticket if passenger matches
                found = true;
            }
        }
        if (!found) {
            cout << "No tickets found for passenger: " << name << "\n";
        }
    }
};

unordered_map<int, Ticket> Reservation::tickets = {};
// Console UI function to interact with the user
void consoleUI1() {
    Reservation reservationSystem; // Create reservation system
    int choice;

    do {
        cout << "\n--- Ticket Reservation System ---\n";
        cout << "1. Book Ticket\n";
        cout << "2. Cancel Ticket\n";
        cout << "3. Update Ticket\n";
        cout << "4. Display All Tickets\n";
        cout << "5. Search Tickets by Passenger Name\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                // Book Ticket
                string name, seat;
                int trainID;
                double fare;

                cout << "Enter Passenger Name: ";
                cin >> ws; // To consume any leftover whitespace
                getline(cin, name);
                cout << "Enter Train ID: ";
                cin >> trainID;
                cout << "Enter Seat Number: ";
                cin >> ws;
                getline(cin, seat);
                cout << "Enter Fare: ";
                cin >> fare;

                reservationSystem.bookTicket(name, trainID, seat, fare);
                break;
            }
            case 2: {
                // Cancel Ticket
                int ticketID;
                cout << "Enter Ticket ID to Cancel: ";
                cin >> ticketID;
                reservationSystem.cancel_Ticket(ticketID);
                break;
            }
            case 3: {
                // Update Ticket
                int ticketID;
                string newSeat;
                double newFare;

                cout << "Enter Ticket ID to Update: ";
                cin >> ticketID;
                cout << "Enter New Seat Number: ";
                cin >> ws;
                getline(cin, newSeat);
                cout << "Enter New Fare: ";
                cin >> newFare;

                reservationSystem.updateTicket(ticketID, newSeat, newFare);
                break;
            }
            case 4: // Display All Tickets
                reservationSystem.displayAllTickets();
                break;
            case 5: {
                // Search Tickets by Passenger Name
                string name;
                cout << "Enter Passenger Name to Search: ";
                cin >> ws;
                getline(cin, name);
                reservationSystem.searchTicketsByPassenger(name);
                break;
            }
            case 6: // Exit
                cout << "Exiting the system. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);
}


class Coach {
    long long id;
    array<bool, 30> Seats{}; //Initially false(zero)

    int Reserved_Seats{}; //Initially zero

    int Available_Seats{30}; // Initially 30.
public:
    Coach() : id(0) {
    }

    Coach(long long ID, int num_of_Available_Seat, int num_of_Reserved_Seat);

    int Reserved_Seats_num();

    int Available_Seats_num();

    bool Check_Availability();

    void Reserve_Seat();

    void Set_id(long long Id);

    friend ostream &operator <<(ostream &output, const Coach &c); // Output all the content of Coach
};

Coach::Coach(long long ID, int num_of_Available_Seat, int num_of_Reserved_Seat)
    : id(ID), Available_Seats(num_of_Available_Seat), Reserved_Seats(num_of_Reserved_Seat) {
}

void Coach::Set_id(long long Id) {
    id = Id;
}

ostream &operator <<(ostream &output, const Coach &obj) {
    output << "\n\nID: " << obj.id << "\t\t" << "Num of reserved seats: " << obj.Reserved_Seats

            << "\t\t" << "Num of available seat: " << obj.Available_Seats << "\t\n\n";

    return output;
}

int Coach::Reserved_Seats_num() {
    return Reserved_Seats;
}

int Coach::Available_Seats_num() {
    return Available_Seats;
}

bool Coach::Check_Availability() {
    return Available_Seats; // if the value > 0,it will return true...if not will return false (0)
}

void Coach::Reserve_Seat() {
    if (Reserved_Seats_num() == 30)

        cout << "\nFully Reserved.";

    else {
        int seat_num;
        do {
            cout << "\n\nEnter the propere seat (1 : 30): ";
            cin >> seat_num;
        } while (seat_num > 30 || seat_num < 1);

        // 0 based index

        if (Seats[seat_num - 1]) // 1
        {
            cout << "\nSeat already booked. Please choose another seat.\n";
            Reserve_Seat(); // Recursive call.
        } else // 0
        {
            // 30
            Seats[seat_num - 1] = true;

            Available_Seats--;
            Reserved_Seats++;

            cout << "\nReservation done.\n";
        }
    }
}

class Train {
    long long Id;
    string trainName;

    vector<Coach> Coachs_of_train; // Composition: train has a 10 coach.
    static list<Train *> trains_insystem;
    //Coach Coachs_of_train[10];

public:
    Train() : Coachs_of_train(10) {
    } // Default const  train has a 10 coach.


    Train(long long ID, string name) : Id(ID), trainName(name), Coachs_of_train(10) {
    }

    void Class_Levels();

    long long GetId() const { return Id; };

    static void Add_Train() {
        long long trainId;
        cout << "Enter train ID: ";
        cin >> trainId;
        string name;
        cout << "Enter the name of the train sir: " << endl;
        cin >> name;
        for (auto it: trains_insystem) {
            if (it->Id == trainId || it->trainName == name) {
                cout << "Be ware sir cannot have two trains with the same name or id !" << endl;
                return;
            }
        }

        Train *newTrain = new Train(trainId, name);
        trains_insystem.push_back(newTrain);


        cout << "Train with ID " << trainId << " And name  " << name << " added successfully.\n";
    }

    // Method to display all trains
    static void Display_Trains() {
        for (auto it: trains_insystem) {
            cout << "TrainId: " << it->Id << " And train name: " << it->trainName << endl;
        }
    }
};

list<Train *> Train::trains_insystem = {
    new Train(1, "Alexandria_train"),
    new Train(2, "Mansoura_train"),
    new Train(3, "Benha_train"),
    new Train(4, "Samannud_train"),
    new Train(5, "Damietta_train"),
    new Train(6, "Cairo_train"),
    new Train(7, "Tanta_train"),
    new Train(8, "Elmahalla_train"),
};

void Train::Class_Levels() {
    cout << "\n\t\t1A:First Class air conditioned.\t 2A:Second Class air conditioned.\n\n\n"

            << "\t\t3A:Third Class air conditioned.\t CC:AC Chair Car.\n\n\n";

    string type("");

    do {
        cout << "Enter the type (1A,2A,3A,CC) : ";
        cin >> type;
    } while (type != "1A" && type != "1a" && type != "2A" && type != "2a" &&
             type != "3a" && type != "3A" && type != "CC" && type != "cc" && type != "Cc");

    //				=======

    if (type == "1A" || type == "1a") {
        Coachs_of_train[0].Set_id(301);
        cout << Coachs_of_train[0];
        Coachs_of_train[0].Reserve_Seat();
    } else if (type == "2A" || type == "2a") {
        Coachs_of_train[1].Set_id(302);
        cout << Coachs_of_train[1];
        Coachs_of_train[1].Reserve_Seat();
    } else if (type == "3A" || type == "3a") {
        Coachs_of_train[2].Set_id(303);
        cout << Coachs_of_train[2];
        Coachs_of_train[2].Reserve_Seat();
    } else {
        Coachs_of_train[3].Set_id(304);
        cout << Coachs_of_train[3];
        Coachs_of_train[3].Reserve_Seat();
    }
}

struct Train_node {
    Train_node *next{};
    Train data{};

    Train_node() {
    } //Default Constructor.
};

class admin {
    int Platfor{};
    string Depart, Destination;
    Train_node *head{}; // points to nullptr.
    int Num_of_stops{};
    string Train_Status; // Delayed_Canceled _ Ontime.


public:
    static void Consol();

    // Default constructor
    admin() {
        head = new Train_node;
    }

    // Destructor
    ~admin() {
        /* delete(head);*/
    }

    // Method to add a train


    // Admin options menu
    void admin_options() {
        cout << "\t\t______ Egypt Railways _______\n";
        cout << "\n1: Add a train\n2: Display trains\n";

        int option;
        do {
            cout << "Choose option (1-2): ";
            cin >> option;
        } while (option < 1 || option > 2);

        switch (option) {
            case 1:
                Train::Add_Train();
                break;
            case 2:
                Train::Display_Trains();
                break;
        }
    }
};

class Payment {
    double amount = 0.0;
    string method;
    string status;
    string date;

    static list<Payment> Receipts; // Static list to store all payment receipts
    static int payment_id_counter; // Counter for generating unique payment IDs

    int payment_id;

    string getCurrentDateTime() const {
        auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        tm local_tm;

#ifdef _WIN32
        localtime_s(&local_tm, &now);  // Windows-specific
#else
        localtime_r(&now, &local_tm); // POSIX-compliant (Linux, macOS, etc.)
#endif

        std::stringstream ss;
        ss << std::put_time(&local_tm, "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }

public:
    Payment(double amt)
        : amount(amt), payment_id(++payment_id_counter) {
        date = getCurrentDateTime();
    }


    void paymentMethod() {
        int choice;
        cout << "Choose a payment method from the following: \n"
                << "1) Credit/Debit Card\n"
                << "2) Digital Wallet\n";
        do {
            cin >> choice;
            if (choice < 1 || choice > 2) {
                cout << "Please enter a valid choice.\n";
            }
        } while (choice < 1 || choice > 2);

        method = (choice == 1) ? "Credit/Debit Card" : "Digital Wallet";
    }


    void processPayment(double fare) {
        string number;
        if (method == "Credit/Debit Card") {
            cout << "Please enter the Credit/Debit Card number: ";
            do {
                cin >> number;
                if (number.size() != 16)
                    cout << "Please enter a valid Credit/Debit Card number.\n";
            } while (number.size() != 16);
        } else {
            cout << "Please enter the Digital Wallet number: ";
            do {
                cin >> number;
                if (number.size() != 11)
                    cout << "Please enter a valid Digital Wallet number.\n";
            } while (number.size() != 11);
        }

        status = (amount == fare) ? "Successful" : "Unsuccessful";
    }


    void verifyPayment() const {
        cout << "The payment is " << status << ".\n";
    }


    void generateReceipt() {
        Receipts.push_back(*this);
        cout << "-----------------------Receipt#" << payment_id << "-----------------------\n"
                << "Payment ID: " << payment_id << "\n"
                << "Amount: " << amount << "\n"
                << "Method: " << method << "\n"
                << "Status: " << status << "\n"
                << "Date: " << date << "\n";
    }


    static void displayAllReceipts() {
        if (Receipts.size() == 0) {
            cout << "No receipts yet sir!" << endl;
            return;
        }
        cout << "---------- All Receipts ----------\n";
        for (const auto &receipt: Receipts) {
            cout << "Receipt#" << receipt.payment_id << " | Amount: " << receipt.amount
                    << " | Method: " << receipt.method << " | Status: " << receipt.status
                    << " | Date: " << receipt.date << "\n";
        }
    }
};

// Initialize static members
int Payment::payment_id_counter = 0;
list<Payment> Payment::Receipts;

enum class UserStatus {
    ADMIN, PASSENGER
};

// to print the user status as a string
string userStatusToString(UserStatus status) {
    switch (status) {
        case UserStatus::ADMIN:
            return "Admin";
        case UserStatus::PASSENGER:
            return "Passenger";
        default:
            return "Unknown";
    }
}

class UserAccount {
private:
    static int counter;
    int accountID;
    string username;
    string email;
    string password;
    UserStatus status; // admin or passenger

public:
    UserAccount(string username, string email, string password, UserStatus status)
        : username(username), email(email), password(password), status(status) {
        accountID = ++counter;
    }

    bool isLogedIn(string email, string password) {
        if (this->email == email && this->password == password)
            return true;
        else
            return false;
    }

    void updateProfile() {
        cout << "What do You Want to Update?\n";
        cout << "1. Username\n";
        cout << "2. Email\n";
        cout << "3. Password\n";
        int n;
        cin >> n;
        switch (n) {
            case 1: {
                cout << "Enter New Username : ";
                string newUsername;
                cin >> newUsername;
                this->username = newUsername;
                break;
            }
            case 2: {
                cout << "Enter New Email : ";
                string newEmail;
                cin >> newEmail;
                this->email = newEmail;
                break;
            }
            case 3: {
                cout << "Enter New Password : ";
                string newPassword;
                cin >> newPassword;
                this->password = newPassword;
                break;
            }
            default:
                cout << "Wrong Option";
                break;
        }
    }

    string getUsername() { return username; }

    string getEmail() { return email; }

    string getPassword() { return password; }

    UserStatus getStatus() { return status; }

    int getAccountID() { return accountID; }

    void displayDetails() {
        cout << "*****Account Details*****\n";
        cout << " Account ID : " << getAccountID() << endl;
        cout << " Username : " << getUsername() << endl;
        cout << " Email : " << getEmail() << endl;
        cout << " Password : " << getPassword() << endl;
        cout << " Account Status : " << userStatusToString(getStatus()) << endl;
    }
};

int UserAccount::counter = 0;


class Admin {
private:
    UserAccount adminAccount;

public:
    Admin(string username, string email, string password)
        : adminAccount(username, email, password, UserStatus::ADMIN) {
    }

    void addTrain() {
        cout << "Train added by admin: " << adminAccount.getUsername() << endl;
    }

    void updateRoute() {
        cout << "Route updated by admin: " << adminAccount.getUsername() << endl;
    }

    void removeTrain() {
        cout << "Train removed by admin: " << adminAccount.getUsername() << endl;
    }

    void updateDetails() {
        adminAccount.updateProfile();
        cout << "Admin account details updated to : \n";
        adminAccount.displayDetails();
    }

    //getAccount() provides access to the adminAccount throw the Admin object.
    UserAccount &getAccount() {
        return adminAccount;
    }
};

class Passenger {
private:
    static int counter;
    int seatNumber;
    UserAccount passengerAccount;

public:
    Passenger(string username, string email, string password)
        : passengerAccount(username, email, password, UserStatus::PASSENGER) {
        seatNumber = counter++;
    }

    void bookTicket() {
        cout << "Ticket booked by passenger: " << passengerAccount.getUsername() << endl;
    }

    void cancelTicket() {
        cout << "Ticket canceled by passenger: " << passengerAccount.getUsername() << endl;
    }

    void updateDetails() {
        passengerAccount.updateProfile();
        cout << "Passenger account details updated to : \n";
        passengerAccount.displayDetails();
    }

    UserAccount &getAccount() {
        return passengerAccount;
    }
};

int Passenger::counter = 1001;


class TheSystem {
private:
    vector<Admin> admins;
    vector<Passenger> passengers;
    Admin *currentAdmin = NULL; // to Know which admin is loged in
    Passenger *currentPassenger = NULL; // to Know which passenger is loged in

public:
    // adding admin
    void registAdmin(const Admin &admin) {
        admins.push_back(admin);
        currentAdmin = &admins.back(); // point to the last element in the vector of admins
    }

    // adding passenger
    void registPassenger(const Passenger &passenger) {
        passengers.push_back(passenger);
        currentPassenger = &passengers.back(); // point to the last element in the vector of passengers
    }

    UserStatus login(const string &email, const string &password) {
        for (auto &admin: admins) {
            if (admin.getAccount().isLogedIn(email, password)) {
                currentAdmin = &admin;
                cout << "Welcome, Admin: " << admin.getAccount().getUsername() << endl;
                return UserStatus::ADMIN;
            }
        }

        for (auto &passenger: passengers) {
            if (passenger.getAccount().isLogedIn(email, password)) {
                currentPassenger = &passenger;
                cout << "Welcome, Passenger: " << passenger.getAccount().getUsername() << endl;
                return UserStatus::PASSENGER;
            }
        }

        cout << "Invalid account. Please try again." << endl;
    }

    // to check if the email is already used by another account => in registration proccess
    bool isEmailAvailable(const string &email) {
        for (auto &admin: admins) {
            if (admin.getAccount().getEmail() == email) {
                return false;
            }
        }

        for (auto &passenger: passengers) {
            if (passenger.getAccount().getEmail() == email) {
                return false;
            }
        }

        return true;
    }

    void displayAdmins() {
        int num = 1;
        for (auto &admin: admins) {
            cout << num << ". " << admin.getAccount().getUsername() << endl;
            num++;
        }
    }

    void displayPassengers() {
        if (passengers.size() == 0) {
            cout << "Still no passengers Registered in the system!" << endl;
            return;
        }
        int num = 1;
        for (auto &passenger: passengers) {
            cout << num << ". " << passenger.getAccount().getUsername() << endl;
            num++;
        }
    }

    // to know who is loged in know (which account)
    Admin *getCurrentAdmin() {
        return currentAdmin;
    }

    Passenger *getCurrentPassenger() {
        return currentPassenger;
    }
};


void adminPermissions(TheSystem &mySystem) {
    int choice = 0;
    cout << "What you want to manage" << endl;
    do {
        cout << "[1] schedules\n";
        cout << "[2] stations\n";
        cout << "[3] tickets\n";
        cout << "[4] Trains\n";
        cout << "[5] Display Passengers\n";
        cout << "[6] display all Receipts\n";
        cout << "[7] see all feedbacks" << endl;
        cout << "[8] Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;

        switch (choice) {
            case 1: {
                schedule::Update_schedules();
                system("pause");
                break;
            }

            case 2: {
                Station::manage_stations();
                system("pause");
                break;
            }

            case 3: {
                consoleUI1();
                system("pause");
                break;
            }


            case 4: {
                admin train_features;
                train_features.admin_options();
                break;
            }
            case 5: {
                mySystem.displayPassengers();
                system("pause");
                break;
            }

            case 6:
                Payment::displayAllReceipts();
                break;
            case 7: {
                Feedback report;
                report.displayfeedbacks();
                break;
            }
            case 8:
                return;
        }
    } while (true);
}

void passengerPermissions(TheSystem &mySystem) {
    int choice = 0;
    do {
        cout << "[1] Book Ticket\n";
        cout << "[2] Cancel Ticket\n";
        cout << "[3] display available schedules\n";
        cout << "[4] report a problem in station\n";
        cout << "[5] Submit feedback\n";
        cout << "[6] Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;

        switch (choice) {
            case 1: {
                cout << "Enter your name here sir: " << endl;
                string name;
                cin >> name;
                cout << "Enter the id of the train you want to travel on: " << endl;
                int trainid;
                cin >> trainid;
                cout << "Enter the number of the seat you want to sit on sir: " << endl;
                string seatnum;
                cin >> seatnum;
                cout << "Enter the fare of the ticket sir: " << endl;
                double fare;
                cin >> fare;
                Reservation reser_system;
                reser_system.bookTicket(name, trainid, seatnum, fare);
                Payment p1(fare);
                cout << "Ticket booked but need to be confirmed " << endl;
                cout << "pay to confirm it sir: " << endl;
                p1.paymentMethod();
                p1.processPayment(fare);
                p1.generateReceipt();

                system("pause");
                break;
            }

            case 2: {
                int ticketID = 0;
                cout << "Enter Ticket ID to Cancel: ";
                cin.clear(); // Clear any error flags
                cin.ignore(INT_MAX, '\n'); // Ignore leftover input
                cin >> ticketID;

                if (cin.fail()) {
                    cout << "Invalid input. Please enter a valid ticket ID.\n";
                    cin.clear(); // Clear the fail state
                    cin.ignore(INT_MAX, '\n'); // Clear the buffer
                    break;
                }
                Reservation reser_system;
                reser_system.cancel_Ticket(ticketID);
                system("pause");
                break;
            }

            case 3: {
                Station::show_stations_details();
                system("pause");
                break;
            }

            case 4: {
                Station::emergency_report();
                system("pause");
                break;
            }
            case 5: {
                Feedback report;
                report.sumbitfeedback();
                break;
            }

            case 6:
                return;
        }
    } while (true);
}


void consoleUI() {
    TheSystem mySystem;

    while (true) {
#ifdef _WIN32
        system("cls"); // clear screen for better UI
#else
        system("clear"); // clear screen for better UI
#endif
        cout << "=========================== Welcome To Our Interface ===========================\n\n";
        cout << "[1] Login\n";
        cout << "[2] Register\n";
        cout << "[3] Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                string email, password;
                cout << "\n=========== Login ===========\n";
                cout << "Email: ";
                cin >> email;
                cout << "Password: ";
                cin >> password;

                UserStatus status = mySystem.login(email, password);
                if (status == UserStatus::ADMIN) {
                    adminPermissions(mySystem);
                } else if (status == UserStatus::PASSENGER) {
                    passengerPermissions(mySystem);
                } else {
                    cout << "Invalid credentials. Please try again." << endl;
                    system("pause");
                }
                break;
            }

            case 2: {
                cout << "\n=========== Register ===========\n";
                cout << "[1] Register as Passenger\n";
                cout << "[2] Register as Admin\n";
                cout << "Enter your choice: ";
                int registerChoice;
                cin >> registerChoice;

                if (registerChoice == 1 || registerChoice == 2) {
                    string username, email, password;
                    cout << "\nEnter Username: ";
                    cin >> username;
                    cout << "Enter Email: ";
                    cin >> email;

                    if (!mySystem.isEmailAvailable(email)) {
                        cout << "This email is already used. Please try another email." << endl;
                        system("pause");
                        break;
                    }

                    cout << "Enter Password: ";
                    cin >> password;

                    if (registerChoice == 1) {
                        mySystem.registPassenger(Passenger(username, email, password));
                        cout << "Passenger registered successfully!" << endl;
                        passengerPermissions(mySystem);
                    } else {
                        mySystem.registAdmin(Admin(username, email, password));
                        cout << "Admin registered successfully!" << endl;
                        adminPermissions(mySystem);
                    }
                } else {
                    cout << "Invalid choice. Returning to main menu." << endl;
                }
                system("pause");
                break;
            }

            case 3:
                cout << "Exiting the system. Thank you!" << endl;
                return;

            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
                system("pause");
        }
    }
}


int main() {
    consoleUI();
    return 0;
}