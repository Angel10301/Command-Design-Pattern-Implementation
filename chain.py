class Handler: # Define the handler interface
    def __init__(self):
        self.next_handler = None
    
    def set_next_handler(self, handler):
        self.next_handler = handler
    
    def handle_request(self, severity):
        if self.next_handler:
            self.next_handler.handle_request(severity)

# Concrete handler classes
class Nurse(Handler):
    def handle_request(self, severity):
        if severity == "mild":
            print("Nurse: Handling mild case, administering basic care.")
        else:
            print("Nurse: Severity too high, passing to Doctor.")
            super().handle_request(severity)

class Doctor(Handler):
    def handle_request(self, severity):
        if severity == "moderate":
            print("Doctor: Handling moderate case, providing medical treatment.")
        else:
            print("Doctor: Severity too high, passing to Specialist.")
            super().handle_request(severity)

class Specialist(Handler):
    def handle_request(self, severity):
        if severity == "severe":
            print("Specialist: Handling severe case, performing advanced medical")
        else:
            print("Specialist: Unable to handle, please review request severity.")

if __name__ == "__main__": # Client code
    # Create handlers
    nurse = Nurse()
    doctor = Doctor()
    specialist = Specialist()
    
    # Set up chain of responsibility
    nurse.set_next_handler(doctor)
    doctor.set_next_handler(specialist)
    
    # Test different severity levels
    print("Request for a mild case:")
    nurse.handle_request("mild")
    
    print("\nRequest for a moderate case:")
    nurse.handle_request("moderate")
    
    print("\nRequest for a severe case:")
    nurse.handle_request("severe")