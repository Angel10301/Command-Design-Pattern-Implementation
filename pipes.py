class Pipe: # Define a basic Pipe and Filter framework
    def __init__(self):
        self.filters = []
    
    def add_filter(self, filter_func):
        self.filters.append(filter_func)
    
    def process(self, data):
        for filter_func in self.filters:
            data = filter_func(data)
        return data

# Define filters
def validate_data(patient_data):
    if "name" in patient_data and "age" in patient_data:
        return patient_data
    raise ValueError("Invalid data: Missing fields")

def transform_data(patient_data):
    patient_data["DOB"] = patient_data.pop("DOB").replace("/", "-")  # Change
    return patient_data

def anonymize_data(patient_data):
    patient_data.pop("name", None)  # Remove PII
    return patient_data

def analyze_risk(patient_data):
    # Example: Simple risk score based on age
    patient_data["risk_score"] = "High" if patient_data["age"] > 60 else "Low"
    return patient_data

pipeline = Pipe() # Create the pipeline
pipeline.add_filter(validate_data)
pipeline.add_filter(transform_data)
pipeline.add_filter(anonymize_data)
pipeline.add_filter(analyze_risk)

patient_data = { # Example patient data
    "name": "John Doe",
    "age": 65,
    "medical_history": ["diabetes"],
    "DOB": "01/01/1958"
}

# Process the data through the pipeline
processed_data = pipeline.process(patient_data)
print(processed_data)