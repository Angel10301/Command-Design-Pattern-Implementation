#include <iostream>
#include <string>
using namespace std;


class Handler { // Abstract Handler
protected:
    Handler* nextHandler = nullptr; // Pointer to the next handler in the chain

public:
    virtual ~Handler() {}
    void setNextHandler(Handler* handler) { // Method to set the next handler in the chain
        nextHandler = handler;
    }
    virtual void handleRequest(const string& severity) { // Virtual method to handle requests, overridden by concrete handlers
        if (nextHandler) {
            nextHandler->handleRequest(severity);
        }
    }
};


class Nurse : public Handler { // Concrete Handler Nurse
public:
    void handleRequest(const string& severity) override {
        if (severity == "mild") { // Nurse handles mild severity cases
            cout << "Nurse: Handling mild case, administering basic care." << endl;
        } else {
            cout << "Nurse: Severity too high, passing to Doctor." << endl;
            Handler::handleRequest(severity);
        }
    }
};

class Doctor : public Handler { // Concrete handler Doctor
public:
    void handleRequest(const string& severity) override { 
        if (severity == "moderate") { // Doctor handles moderate severity cases
            cout << "Doctor: Handling moderate case, providing medical treatment." << endl;
        } else {
            cout << "Doctor: Severity too high, passing to Specialist." << endl;
            Handler::handleRequest(severity);
        }
    }
};

class Specialist : public Handler { // Concrete Handler Specialist
public:
    void handleRequest(const string& severity) override {
        if (severity == "severe") {
            cout << "Specialist: Handling severe case, performing advanced medical care." << endl;
        } else {
            cout << "Specialist: Unable to handle, please review request severity." << endl;
        }
    }
};

int main() {
    Nurse nurse; // Create handlers
    Doctor doctor;
    Specialist specialist;

    nurse.setNextHandler(&doctor); // Set up chain of responsibility
    doctor.setNextHandler(&specialist);
    
    cout << "Request for a mild case:" << endl; // Test different severity levels
    nurse.handleRequest("mild");

    cout << "\nRequest for a moderate case:" << endl;
    nurse.handleRequest("moderate");

    cout << "\nRequest for a severe case:" << endl;
    nurse.handleRequest("severe");

    return 0;
}
