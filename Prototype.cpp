#include <iostream>
#include <string>

using namespace std;

class MedicalRecord {
public:
  // Constructor with default values
  MedicalRecord(string patient_name = "", int age = 0, string diagnosis = "", 
                string treatment = "") {
    this->patient_name = patient_name;
    this->age = age;
    this->diagnosis = diagnosis;
    this->treatment = treatment;
  }

  // Copy constructor for deep copying
  MedicalRecord(const MedicalRecord &other) {
    this->patient_name = other.patient_name;
    this->age = other.age;
    this->diagnosis = other.diagnosis;
    this->treatment = other.treatment;
  }

  // Overloading the assignment operator for deep copying
  MedicalRecord& operator=(const MedicalRecord &other) {
    if (this != &other) {
      this->patient_name = other.patient_name;
      this->age = other.age;
      this->diagnosis = other.diagnosis;
      this->treatment = other.treatment;
    }
    return *this;
  }

  // Getter methods for accessing private members
  string getPatientName() const { return patient_name; }
  int getAge() const { return age; }
  string getDiagnosis() const { return diagnosis; }
  string getTreatment() const { return treatment; }

  // Setter methods for modifying private members
  void setPatientName(const string &patientName) { patient_name = patientName; }
  void setAge(int age) { this->age = age; }
  void setDiagnosis(const string &diagnosis) { this->diagnosis = diagnosis; }
  void setTreatment(const string &treatment) { this->treatment = treatment; }

private:
  string patient_name;
  int age;
  string diagnosis;
  string treatment;
};

int main() {
  // Create a prototype medical record
  MedicalRecord prototype_record("Template", 0, "General Checkup", "Standard Protocol");

  // Clone the prototype for a new patient and customize
  MedicalRecord patient1_record = prototype_record; // Using the copy constructor
  patient1_record.setPatientName("Alice Smith");
  patient1_record.setAge(35);
  patient1_record.setDiagnosis("Hypertension");
  patient1_record.setTreatment("Blood Pressure Medication");

  // Another cloned and customized record
  MedicalRecord patient2_record;
  patient2_record = prototype_record; // Using the assignment operator
  patient2_record.setPatientName("John Doe");
  patient2_record.setAge(58);
  patient2_record.setDiagnosis("Diabetes");
  patient2_record.setTreatment("Insulin Therapy");

  // Display the records
  cout << "Patient 1 Record:" << endl;
  cout << "Patient Name: " << patient1_record.getPatientName() << endl;
  cout << "Age: " << patient1_record.getAge() << endl;
  cout << "Diagnosis: " << patient1_record.getDiagnosis() << endl;
  cout << "Treatment: " << patient1_record.getTreatment() << endl;

  cout << "\nPatient 2 Record:" << endl;
  cout << "Patient Name: " << patient2_record.getPatientName() << endl;
  cout << "Age: " << patient2_record.getAge() << endl;
  cout << "Diagnosis: " << patient2_record.getDiagnosis() << endl;
  cout << "Treatment: " << patient2_record.getTreatment() << endl;

  return 0;
}