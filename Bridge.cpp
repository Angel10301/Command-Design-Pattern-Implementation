#include <iostream>
#include <string>

using namespace std;

// Define the PaymentMethod interface
class PaymentMethod {
public:
  virtual string process_payment(double amount) = 0;
};

// Concrete Implementations of PaymentMethod
class InsurancePayment : public PaymentMethod {
public:
  string process_payment(double amount) override {
    return "Processing insurance payment of $" + to_string(amount) + ".";
  }
};

class SelfPayPayment : public PaymentMethod {
public:
  string process_payment(double amount) override {
    return "Processing self-pay payment of $" + to_string(amount) + ".";
  }
};

// Define the HospitalService abstraction
class HospitalService {
public:
  HospitalService(PaymentMethod *payment_method) : payment_method(payment_method) {}
  virtual string provide_service(const string &patient_name,
                                   double amount) = 0;

protected:
  PaymentMethod *payment_method;
};

// Concrete implementations of HospitalService
class OutpatientService : public HospitalService {
public:
  OutpatientService(PaymentMethod *payment_method)
      : HospitalService(payment_method) {}

  string provide_service(const string &patient_name, double amount) override {
    string payment_info = payment_method->process_payment(amount);
    return "Outpatient service provided to " + patient_name + ". " +
           payment_info;
  }
};

class InpatientService : public HospitalService {
public:
  InpatientService(PaymentMethod *payment_method)
      : HospitalService(payment_method) {}

  string provide_service(const string &patient_name, double amount) override {
    string payment_info = payment_method->process_payment(amount);
    return "Inpatient service provided to " + patient_name + ". " +
           payment_info;
  }
};

int main() {
  // Define payment methods
  InsurancePayment *insurance = new InsurancePayment();
  SelfPayPayment *self_pay = new SelfPayPayment();

  // Define services with different payment methods
  OutpatientService *outpatient_with_insurance =
      new OutpatientService(insurance);
  OutpatientService *outpatient_with_selfpay = new OutpatientService(self_pay);
  InpatientService *inpatient_with_insurance = new InpatientService(insurance);

  // Use the services
  cout << outpatient_with_insurance->provide_service("Alice", 200) << endl;
  cout << outpatient_with_selfpay->provide_service("Bob", 150) << endl;
  cout << inpatient_with_insurance->provide_service("Charlie", 500) << endl;

  // Clean up memory (important in C++)
  delete insurance;
  delete self_pay;
  delete outpatient_with_insurance;
  delete outpatient_with_selfpay;
  delete inpatient_with_insurance;

  return 0;
}