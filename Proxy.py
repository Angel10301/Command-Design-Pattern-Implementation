# Real subjects: Steering and Brake Actuators
class SteeringActuator:
    def apply_steering_angle(self, angle):
        print(f"Steering actuator set to {angle} degrees.")

class BrakeActuator:
    def apply_braking_force(self, force):
        print(f"Brake actuator applying {force} units of force.")

# Proxy classes
class SteeringWheelProxy:
    def __init__(self, actuator, mode="manual"):
        self.actuator = actuator
        self.mode = mode    # 'manual' or 'autonomous'
    
    def process_steering_input(self, angle):
        if self.mode == "manual":
            self.actuator.apply_steering_angle(angle)
        elif self.mode == "autonomous":
            print("Ignoring steering input in autonomous mode.")
    
    def set_mode(self, mode):
        self.mode = mode
        print(f"Steering mode set to: {self.mode}")

class BrakePedalProxy:
    def __init__(self, actuator, mode="manual"):
        self.actuator = actuator
        self.mode = mode    # 'manual' or 'autonomous'
    
    def process_brake_input(self, force):
        if self.mode == "manual":
            self.actuator.apply_braking_force(force)
        elif self.mode == "autonomous":
            # Example of safety override
            adjusted_force = max(force, 50)  # Ensure minimum braking force for safety
            self.actuator.apply_braking_force(adjusted_force)
            print(f"Braking input adjusted for autonomous safety to {adjusted_force}")
    
    def set_mode(self, mode):
        self.mode = mode
        print(f"Braking mode set to: {self.mode}")

# Client code
if __name__ == "__main__":
    # Instantiate actuators
    steering_actuator = SteeringActuator()
    brake_actuator = BrakeActuator()
    
    # Create proxies for actuators
    steering_proxy = SteeringWheelProxy(steering_actuator)
    brake_proxy = BrakePedalProxy(brake_actuator)
        
    print("Manual mode:") # Driver controls in manual mode
    steering_proxy.process_steering_input(30)    # Normal steering
    brake_proxy.process_brake_input(20)        # Normal braking
        
    print("\nSwitching to autonomous mode:") # Switch to autonomous mode
    steering_proxy.set_mode("autonomous")
    brake_proxy.set_mode("autonomous")
    
    # Try to control the car in autonomous mode
    steering_proxy.process_steering_input(30)    # Should ignore driver input
    brake_proxy.process_brake_input(20)        # Overrides for safety
