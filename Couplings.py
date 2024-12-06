class Patient: # Define a Patient class
    def __init__(self, name, ailment):
        self.name = name
        self.ailment = ailment
    
    def get_details(self):
        return f"Patient: {self.name}, Ailment: {self.ailment}"

class Doctor: # Define a Doctor class
    def __init__(self, name, specialization):
        self.name = name
        self.specialization = specialization
    
    def get_details(self):
        return f"Doctor: {self.name}, Specialization: {self.specialization}"

class Scheduler: # Define a Scheduler class for decoupling
    def __init__(self):
        self.assignments = []
    
    def assign(self, doctor, patient):
        if doctor.specialization in patient.ailment:
            self.assignments.append((doctor, patient))
            print(f"Assigned {doctor.name} to {patient.name}")
        else:
            print(f"No match: {doctor.name} cannot treat {patient.name}'s condition")

    def show_assignments(self):
        print("\nCurrent Assignments:")
        for doctor, patient in self.assignments:
            print(f"{doctor.name} is treating {patient.name} for {patient.ailment}")

if __name__ == "__main__": # Example Usage
    # Create patients
    patient1 = Patient("Alice", "Cardiology")
    patient2 = Patient("Bob", "Orthopedics")
    
    # Create doctors
    doctor1 = Doctor("Dr. Smith", "Cardiology")
    doctor2 = Doctor("Dr. Johnson", "Orthopedics")
    
    # Use Scheduler to assign
    scheduler = Scheduler()
    scheduler.assign(doctor1, patient1)  # Matching specialization
    scheduler.assign(doctor2, patient2)  # Matching specialization
    scheduler.assign(doctor1, patient2)  # Non-matching specialization
        
    scheduler.show_assignments() # Show final assignments