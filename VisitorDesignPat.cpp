#include <iostream>
#include <vector>
#include <memory>

class GeneralPatient; //forward declaartaions for Visitor interface
class EmergencyPatient;
class ICUPatient;

class MedicalStaffVisitor { //defines operations that visitors can perform on diffrent types of patients
public:
    virtual void visitGeneralPatient(GeneralPatient* patient) = 0; //general patients
    virtual void visitEmergencyPatient(EmergencyPatient* patient) = 0; //emergency patients 
    virtual void visitICUPatient(ICUPatient* patient) = 0; //icu patitents
    virtual ~MedicalStaffVisitor() = default;
};

class Patient { //representing a patient in the system, each can accept a visitor
public:
    virtual void accept(MedicalStaffVisitor* visitor) = 0;
    virtual ~Patient() = default;
};

class GeneralPatient : public Patient { //general patient 
public:
    void accept(MedicalStaffVisitor* visitor) override {
        visitor->visitGeneralPatient(this); //calling the visitor
    }
};

class EmergencyPatient : public Patient {
public:
    void accept(MedicalStaffVisitor* visitor) override {
        visitor->visitEmergencyPatient(this); //call the visitor's method for emergency patients
    }
};

class ICUPatient : public Patient {
public:
    void accept(MedicalStaffVisitor* visitor) override {
        visitor->visitICUPatient(this);
    }
};

class Nurse : public MedicalStaffVisitor { //nurse implements specific actions for each type of patient
public:
    void visitGeneralPatient(GeneralPatient* patient) override {
        std::cout << "Nurse checks the vitals of a general patient.\n";
    }
    void visitEmergencyPatient(EmergencyPatient* patient) override {
        std::cout << "Nurse assists emergency care for the patient.\n";
    }
    void visitICUPatient(ICUPatient* patient) override {
        std::cout << "Nurse monitors critical stats for the ICU patient.\n";
    }
};

class Doctor : public MedicalStaffVisitor { //doctor implements specific actions for each type of patient
public:
    void visitGeneralPatient(GeneralPatient* patient) override {
        std::cout << "Doctor reviews the general patient's symptoms and prescribes medication.\n";
    }
    void visitEmergencyPatient(EmergencyPatient* patient) override {
        std::cout << "Doctor performs urgent diagnostics for the emergency patient.\n";
    }
    void visitICUPatient(ICUPatient* patient) override {
        std::cout << "Doctor reviews and adjusts treatment plans for the ICU patient.\n";
    }
};

int main() {
    std::vector<std::unique_ptr<Patient>> patients; //cteating list of patients using pointers for memeory management
    patients.push_back(std::make_unique<GeneralPatient>());
    patients.push_back(std::make_unique<EmergencyPatient>());
    patients.push_back(std::make_unique<ICUPatient>());

    Nurse nurse; //creating visitors 
    Doctor doctor;

    std::cout << "Nurse's shift:\n"; //nurse visits all patients
    for (const auto& patient : patients) {
        patient->accept(&nurse);
    }

    std::cout << "\nDoctor's shift:\n"; //doctor visits patients
    for (const auto& patient : patients) {
        patient->accept(&doctor);
    }

    return 0;
}
