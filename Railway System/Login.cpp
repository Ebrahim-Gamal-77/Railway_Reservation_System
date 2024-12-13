#include <iostream>
#include <vector>

using namespace std;

enum class UserStatus
{
    ADMIN, PASSENGER
};

// to print the user status as a string
string userStatusToString(UserStatus status)
{
    switch (status)
    {
    case UserStatus::ADMIN:
        return "Admin";
    case UserStatus::PASSENGER:
        return "Passenger";
    default:
        return "Unknown";
    }
}

class UserAccount
{
private:
    static int counter;
    int accountID;
    string username;
    string email;
    string password;
    UserStatus status; // admin or passenger

public:
    UserAccount(string username, string email, string password, UserStatus status)
        : username(username), email(email), password(password), status(status)
    {
        accountID = ++counter;
    }

    bool isLogedIn(string email, string password)
    {
        if (this->email == email && this->password == password)
            return true;
        else
            return false;
    }

    void updateProfile()
    {
        cout << "What do You Want to Update?\n";
        cout << "1. Username\n";
        cout << "2. Email\n";
        cout << "3. Password\n";
        int n;
        cin >> n;
        switch (n)
        {
        case 1:
        {
            cout << "Enter New Username : ";
            string newUsername;
            cin >> newUsername;
            this->username = newUsername;
            break;
        }
        case 2:
        {
            cout << "Enter New Email : ";
            string newEmail;
            cin >> newEmail;
            this->email = newEmail;
            break;
        }
        case 3:
        {
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

    void displayDetails()
    {
        cout << "************Account Details************\n";
        cout << " Account ID : " << getAccountID() << endl;
        cout << " Username : " << getUsername() << endl;
        cout << " Email : " << getEmail() << endl;
        cout << " Password : " << getPassword() << endl;
        cout << " Account Status : " << userStatusToString(getStatus()) << endl;
    }
};

int UserAccount::counter = 0;


class Admin
{
private:
    UserAccount adminAccount;

public:
    Admin(string username, string email, string password)
        : adminAccount(username, email, password, UserStatus::ADMIN) {}

    void addTrain()
    {
        cout << "Train added by admin: " << adminAccount.getUsername() << endl;
    }

    void updateRoute()
    {
        cout << "Route updated by admin: " << adminAccount.getUsername() << endl;
    }

    void removeTrain()
    {
        cout << "Train removed by admin: " << adminAccount.getUsername() << endl;
    }

    void updateDetails()
    {
        adminAccount.updateProfile();
        cout << "Admin account details updated to : \n";
        adminAccount.displayDetails();
    }
    //getAccount() provides access to the adminAccount throw the Admin object.
    UserAccount& getAccount()
    {
        return adminAccount;
    }
};

class Passenger
{
private:
    static int counter;
    int seatNumber;
    UserAccount passengerAccount;

public:
    Passenger(string username, string email, string password)
        : passengerAccount(username, email, password, UserStatus::PASSENGER)
    {
        seatNumber = counter++;
    }

    void bookTicket()
    {
        cout << "Ticket booked by passenger: " << passengerAccount.getUsername() << endl;
    }

    void cancelTicket() {
        cout << "Ticket canceled by passenger: " << passengerAccount.getUsername() << endl;
    }

    void updateDetails()
    {
        passengerAccount.updateProfile();
        cout << "Passenger account details updated to : \n";
        passengerAccount.displayDetails();
    }

    UserAccount& getAccount()
    {
        return passengerAccount;
    }
};

int Passenger::counter = 1001;


class TheSystem {
private:
    vector<Admin> admins;
    vector<Passenger> passengers;
    Admin* currentAdmin = NULL; // to Know which admin is loged in
    Passenger* currentPassenger = NULL; // to Know which passenger is loged in

public:
    // adding admin
    void registAdmin(const Admin& admin)
    {
        admins.push_back(admin);
        currentAdmin = &admins.back(); // point to the last element in the vector of admins
    }

    // adding passenger
    void registPassenger(const Passenger& passenger)
    {
        passengers.push_back(passenger);
        currentPassenger = &passengers.back(); // point to the last element in the vector of passengers
    }

    UserStatus login(const string& email, const string& password)
    {
        for (auto& admin : admins)
        {
            if (admin.getAccount().isLogedIn(email, password))
            {
                currentAdmin = &admin;
                cout << "Welcome, Admin: " << admin.getAccount().getUsername() << endl;
                return UserStatus::ADMIN;
            }
        }

        for (auto& passenger : passengers)
        {
            if (passenger.getAccount().isLogedIn(email, password))
            {
                currentPassenger = &passenger;
                cout << "Welcome, Passenger: " << passenger.getAccount().getUsername() << endl;
                return UserStatus::PASSENGER;
            }
        }

        cout << "Invalid account. Please try again." << endl;
    }

    // to check if the email is already used by another account => in registration proccess
    bool isEmailAvailable(const string& email)
    {
        for (auto& admin : admins)
        {
            if (admin.getAccount().getEmail() == email)
            {
                return false;
            }
        }

        for (auto& passenger : passengers)
        {
            if (passenger.getAccount().getEmail() == email)
            {
                return false;
            }
        }

        return true;
    }

    void displayAdmins()
    {
        int num = 1;
        for (auto& admin : admins)
        {
            cout << num << ". " << admin.getAccount().getUsername() << endl;
            num++;
        }
    }

    void displayPassengers()
    {
        int num = 1;
        for (auto& passenger : passengers)
        {
            cout << num << ". " << passenger.getAccount().getUsername() << endl;
            num++;
        }
    }

    // to know who is loged in know (which account)
    Admin* getCurrentAdmin()
    {
        return currentAdmin;
    }

    Passenger* getCurrentPassenger()
    {
        return currentPassenger;
    }
};


void adminPermissions(TheSystem& mySystem)
{
    int choice = 0;
    do
    {
        cout << "[1] Add Train\n";
        cout << "[2] Remove Train\n";
        cout << "[3] Update Route\n";
        cout << "[4] Update your Details\n";
        cout << "[5] Display Passengers\n";
        cout << "[6] Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;

        switch (choice)
        {
        case 1: {
            mySystem.getCurrentAdmin()->addTrain();
            system("pause");
            break;
        }

        case 2: {
            mySystem.getCurrentAdmin()->removeTrain();
            system("pause");
            break;
        }

        case 3: {
            mySystem.getCurrentAdmin()->updateRoute();
            system("pause");
            break;
        }

        case 4: {
            mySystem.getCurrentAdmin()->updateDetails();
            system("pause");
            break;
        }

        case 5: {
            mySystem.displayPassengers();
            system("pause");
            break;
        }

        case 6:
            return;
        }
    } while (true);
}

void passengerPermissions(TheSystem& mySystem)
{
    int choice = 0;
    do
    {
        cout << "[1] Book Ticket\n";
        cout << "[2] Cancel Ticket\n";
        cout << "[3] Update your Details\n";
        cout << "[4] Display Admins\n";
        cout << "[5] Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;

        switch (choice)
        {
        case 1: {
            mySystem.getCurrentPassenger()->bookTicket();
            system("pause");
            break;
        }

        case 2: {
            mySystem.getCurrentPassenger()->cancelTicket();
            system("pause");
            break;
        }

        case 3: {
            mySystem.getCurrentPassenger()->updateDetails();
            system("pause");
            break;
        }

        case 4: {
            mySystem.displayAdmins();
            system("pause");
            break;
        }

        case 5:
            return;
        }
    } while (true);
}


void consoleUI()
{
    TheSystem mySystem;

    while (true) {
        system("cls"); // clear screen for better UI
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
            }
            else if (status == UserStatus::PASSENGER) {
                passengerPermissions(mySystem);
            }
            else {
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
                }
                else {
                    mySystem.registAdmin(Admin(username, email, password));
                    cout << "Admin registered successfully!" << endl;
                    adminPermissions(mySystem);
                }
            }
            else {
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

    // old main
    /*
    TheSystem system;

    // Add Admins
    system.registAdmin(Admin("admin1", "admin1@example.com", "password123"));
    system.registAdmin(Admin("admin2", "admin2@example.com", "password456"));

    // Add Passengers
    system.registPassenger(Passenger("passenger1", "passenger1@example.com", "pass123"));
    system.registPassenger(Passenger("passenger2", "passenger2@example.com", "pass456"));

    // Simulate login
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    system.login(username, password);

    return 0;
    */
}
