# Python Adapter Pattern
class ElectricCar:
    def charge_battery(self):
        print("Battery is charging for the electric car.")

class GasCar:
    def fill_gas_tank(self):
        print("Gas tank is filling for the gas car.")

class GasCarAdapter: # Adapter that makes GasCar compatible with ElectricCar interface
    def __init__(self, gas_car):
        self.gas_car = gas_car
    
    def charge_battery(self):
        self.gas_car.fill_gas_tank() # Translate the charge_battery call to fill_gas_tank

def charge_car(car): # Client code that expects a car with a charge_battery method
    car.charge_battery()

# Example usage
electric_car = ElectricCar()
gas_car = GasCar()
gas_car_adapter = GasCarAdapter(gas_car)

print("Charging electric car:")
charge_car(electric_car)    # Works directly

print("\nCharging gas car using adapter:")
charge_car(gas_car_adapter) # Works through the adapter
