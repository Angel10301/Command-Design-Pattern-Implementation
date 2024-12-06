#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <functional>
#include <algorithm> 

using namespace std;


typedef function<map<string, string>(map<string, string>)> FilterFunction; // Define a filter function type

class Pipe { // Define a Pipe class
public:
    void add_filter(FilterFunction filter) {
        filters.push_back(filter);
    }

    map<string, string> process(map<string, string> data) { // Process the data through the pipeline
        for (auto& filter : filters) {
            data = filter(data);
        }
        return data;
    }

private:
    vector<FilterFunction> filters;
};

// Define filter functions
map<string, string> validate_data(map<string, string> patient_data) { // Validate data, check for required fields
    if (patient_data.count("name") == 0 || patient_data.count("age") == 0) {
        throw invalid_argument("Invalid data: Missing fields");
    }
    return patient_data;
}


map<string, string> transform_data(map<string, string> patient_data) { // Transform data, modify data format
    string dob = patient_data["DOB"];
    replace(dob.begin(), dob.end(), '/', '-'); 
    patient_data["DOB"] = dob;                // Update DOB to the new format
    return patient_data;
}

map<string, string> anonymize_data(map<string, string> patient_data) { // Anonymize data, remove sensitive information
    patient_data.erase("name"); // Remove the name field for anonymization
    return patient_data;
}

map<string, string> analyze_risk(map<string, string> patient_data) { // Analyze risk, add risk score based on age
    try {
        int age = stoi(patient_data["age"]); // Convert the age string to an integer
        patient_data["risk_score"] = age > 60 ? "High" : "Low"; // Add a risk score based on the age
    } catch (const invalid_argument& e) {
        throw invalid_argument("Invalid age: " + patient_data["age"]);
    }
    return patient_data;
}

int main() {
    map<string, string> patient_data = {
        {"name", "John Doe"},
        {"age", "65"},
        {"medical_history", "diabetes"},
        {"DOB", "01/01/1958"}
    };

    Pipe pipeline; // Create a pipeline and add filters
    pipeline.add_filter(validate_data);   // Add the validation filter
    pipeline.add_filter(transform_data);  // Add the transformation filter
    pipeline.add_filter(anonymize_data);  // Add the anonymization filter
    pipeline.add_filter(analyze_risk);    // Add the risk analysis filter

    try {
        auto processed_data = pipeline.process(patient_data); // Process the data through the pipeline

        for (auto& [key, value] : processed_data) {
            cout << key << ": " << value << endl; // Output the processed data
        }
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl; // Handle exceptions gracefully
    }

    return 0;
}
