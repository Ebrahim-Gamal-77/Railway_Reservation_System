#include <iostream>
#include <string>
#include <unordered_map>
#include <iomanip> // For formatting
#include <ctime> // For time handling
using namespace std;

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
    // Constructor
    Ticket(): ticketID(1), trainID(1){
    }

    Ticket(int id, string name, int train, string seat, double price, const string& date)
        : ticketID(id), passengerName(name), trainID(train), seatNumber(seat), fare(price), status(true), bookingDate(date) {}

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
        if (true == status) {
            status = false;
            cout << "Ticket " << ticketID << " has been cancelled.\n";
        } else {
            cout << "Ticket " << ticketID << " is already cancelled.\n";
        }
    }

    // Update Ticket Details
    void updateDetails(const string &newSeat, double newFare) {
        if (true == status) {
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

class Reservation {
private:
    unordered_map<int, Ticket> tickets;
    int nextTicketID;

    // Helper function to get current date
    string getCurrentDate() const {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        char date[11];
        strftime(date, sizeof(date), "%Y-%m-%d", ltm);
        return string(date);
    }

public:
    // Constructor
    Reservation() : nextTicketID(1) {}

    // Book a Ticket
    void bookTicket(const string &passengerName, int trainID, const string &seatNumber, double fare) {
        string date = getCurrentDate();
        Ticket newTicket(nextTicketID, passengerName, trainID, seatNumber, fare, date);
        tickets[nextTicketID] = newTicket;
        cout << "Ticket booked successfully. Ticket ID: " << nextTicketID << "\n";
        nextTicketID++;
    }

    // Cancel a Ticket
    void cancelTicket(int ticketID) {
        auto it = tickets.find(ticketID);
        if (it != tickets.end()) {
            it->second.cancelTicket();
        } else {
            cout << "Ticket ID " << ticketID << " not found.\n";
        }
    }

    // Update Ticket
    void updateTicket(int ticketID, const string &newSeat, double newFare) {
        auto it = tickets.find(ticketID);
        if (it != tickets.end()) {
            it->second.updateDetails(newSeat, newFare);
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
        for (const auto &pair : tickets) {
            pair.second.displayTicket();
        }
    }

    // Display Tickets by Passenger Name
    void searchTicketsByPassenger(const string &name) const {
        bool found = false;
        for (const auto &pair : tickets) {
            if (pair.second.getPassengerName() == name) {
                pair.second.displayTicket();
                found = true;
            }
        }
        if (!found) {
            cout << "No tickets found for passenger: " << name << "\n";
        }
    }
};

void consoleUI() {
    Reservation reservationSystem;
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
                int ticketID;
                cout << "Enter Ticket ID to Cancel: ";
                cin >> ticketID;
                reservationSystem.cancelTicket(ticketID);
                break;
            }
            case 3: {
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
            case 4:
                reservationSystem.displayAllTickets();
                break;
            case 5: {
                string name;
                cout << "Enter Passenger Name to Search: ";
                cin >> ws;
                getline(cin, name);
                reservationSystem.searchTicketsByPassenger(name);
                break;
            }
            case 6:
                cout << "Exiting the system. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

}

int main() {
    consoleUI();
    return 0;
}