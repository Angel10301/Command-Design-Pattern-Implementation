class Billing: # High Cohesion: The Billing class focuses only on billing-related tasks
    def __init__(self):
        self.transactions = []
    
    def generate_invoice(self, patient_name, service, amount):
        invoice = f"Invoice for {patient_name}: Service - {service}, Amount - ${amount}"
        self.transactions.append({"patient": patient_name, "service": service, "amount": amount})
        return invoice
    
    def calculate_total(self):
        return sum(transaction["amount"] for transaction in self.transactions)
    
    def print_transactions(self):
        return "\n".join(
            [f"Patient: {t['patient']}, Service: {t['service']}, Amount: ${t['amount']}"
            for t in self.transactions]
        )

if __name__ == "__main__": # Example Usage    
    billing = Billing() # Create a billing system
    
    # Generate invoices
    print(billing.generate_invoice("Alice", "Outpatient Consultation", 200))
    print(billing.generate_invoice("Bob", "Inpatient Surgery", 5000))
    print(billing.generate_invoice("Charlie", "Emergency Treatment", 1200))
        
    print(f"\nTotal Revenue: ${billing.calculate_total()}") # Calculate total revenue
    
    # Print all transactions
    print("\nTransactions:")
    print(billing.print_transactions())