#include <vector>
#include <string>
#include <iostream>
using namespace std;

#ifndef FEEDBACK_H
#define FEEDBACK_H

class Feedback {
    static int counter;
    int feedbackid;
    int accountid;
    int rating;
    string message;
    vector<Feedback> feedbacks;

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
        int id;
        cout << "\n-Enter the feedback id: ";
        cin >> id;

        if (id <= 0 || id > feedbacks.size()) {
            cout << "\nInvalid feedback ID!\n";
            return;
        }
        cout << "============================= Feedback #" << id << " =============================\n";
        cout << "Account ID: " << feedbacks[id-1].accountid << endl;
        cout << "Rating of the trip: " << feedbacks[id-1].rating << endl;
        cout << "Message of the feedback:\n\" " << feedbacks[id-1].message << " \"" << endl;
    }
};

int Feedback::counter = 0;

void Consleui() {
    Feedback feedback;
    int choice=0;
    while (true) {
        system("cls");
        cout << "****************************** Feedback Page ********************************\n\n";
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

#endif // FEEDBACK_H

int main() {
    Consleui();
    return 0;
}
