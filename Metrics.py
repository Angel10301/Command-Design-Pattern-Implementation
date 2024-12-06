class MetricsTracker: # Define the MetricsTracker class
    def __init__(self):
        self.metrics = {
            "patient_admissions": 0,
            "patient_discharges": 0,
            "wait_times": []
        }

    def log_admission(self):
        self.metrics["patient_admissions"] += 1

    def log_discharge(self):
        self.metrics["patient_discharges"] += 1

    def log_wait_time(self, wait_time):
        self.metrics["wait_times"].append(wait_time)

    def get_average_wait_time(self):
        if not self.metrics["wait_times"]:
            return 0
        return sum(self.metrics["wait_times"]) / len(self.metrics["wait_times"])

    def generate_report(self):
        report = (
            f"Patient Admissions: {self.metrics['patient_admissions']}\n"
            f"Patient Discharges: {self.metrics['patient_discharges']}\n"
            f"Average Wait Time: {self.get_average_wait_time():.2f} minutes"
        )
        return report

if __name__ == "__main__": # Example Usage
    metrics_tracker = MetricsTracker() # Create a metrics tracker

    # Log some hospital operations
    metrics_tracker.log_admission()
    metrics_tracker.log_admission()
    metrics_tracker.log_discharge()
    metrics_tracker.log_wait_time(15)
    metrics_tracker.log_wait_time(20)
    metrics_tracker.log_wait_time(10)

    # Generate a performance report
    print("Hospital Metrics Report:")
    print(metrics_tracker.generate_report())