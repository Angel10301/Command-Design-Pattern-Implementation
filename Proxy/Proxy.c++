#include <iostream>

class Actuator { // Base class for steering and brake actuators
public:
    virtual void applySteeringAngle(double angle) = 0;
    virtual void applyBrakingForce(double force) = 0;
};

class SteeringActuator : public Actuator { // Steering actuator implementation
public:
    void applySteeringAngle(double angle) override {
        std::cout << "Steering angle applied: " << angle << std::endl;
    }
    void applyBrakingForce(double force) override { // Not applicable for steering actuator
    }
};
class BrakeActuator : public Actuator { // Brake actuator implementation
public:
    void applySteeringAngle(double angle) override {
        // Not applicable for brake actuator
    }

    void applyBrakingForce(double force) override {
        std::cout << "Braking force applied: " << force << std::endl;
    }
};
class SteeringWheelProxy { // Proxy class for steering wheel
public:
    SteeringWheelProxy(Actuator* actuator, std::string mode) : actuator_(actuator), mode_(mode) {} // Constructor initializes the actuator and mode

    void processSteeringInput(double angle) { // Processes steering input based on the current mode
        if (mode_ == "manual") {
            actuator_->applySteeringAngle(angle);
        } else if (mode_ == "autonomous") {
            std::cout << "Ignoring steering input in autonomous mode." << std::endl;
        }
    }

    void setMode(std::string mode) { // Sets the operating mode (manual or autonomous)
        mode_ = mode;
        std::cout << "Steering mode set to: " << mode_ << std::endl;
    }

private:
    Actuator* actuator_; // Pointer to the underlying actuator
    std::string mode_; // Current operating mode
};

class BrakePedalProxy { // Proxy class for brake pedal
public:

    BrakePedalProxy(Actuator* actuator, std::string mode) : actuator_(actuator), mode_(mode) {} // Constructor initializes the actuator and mode

    void processBrakeInput(double force) { // Processes brake input based on the current mode
        if (mode_ == "manual") {
            actuator_->applyBrakingForce(force);
        } else if (mode_ == "autonomous") {
            double adjustedForce = std::max(force, 50.0); // Enforce a minimum braking force in autonomous mode
            actuator_->applyBrakingForce(adjustedForce);
            std::cout << "Braking input adjusted for autonomous safety to " << adjustedForce << std::endl;
        }
    }

    void setMode(std::string mode) { // Sets the operating mode (manual or autonomous)
        mode_ = mode;
        std::cout << "Braking mode set to: " << mode_ << std::endl;
    }

private:
    Actuator* actuator_; // Pointer to the underlying actuator
    std::string mode_; // Current operating mode
};

int main() {
    SteeringActuator* steeringActuator = new SteeringActuator();// Create instances of steering and brake actuators
    BrakeActuator* brakeActuator = new BrakeActuator();
   
    SteeringWheelProxy* steeringProxy = new SteeringWheelProxy(steeringActuator, "manual"); // Create proxy objects for steering and brake
    BrakePedalProxy* brakeProxy = new BrakePedalProxy(brakeActuator, "manual");

    std::cout << "Manual mode:" << std::endl; // Simulate manual mode
    steeringProxy->processSteeringInput(30); // Normal steering
    brakeProxy->processBrakeInput(20); // Normal braking

    std::cout << "Switching to autonomous mode:" << std::endl; // Switch to autonomous mode
    steeringProxy->setMode("autonomous");
    brakeProxy->setMode("autonomous");

    steeringProxy->processSteeringInput(30); // Should ignore driver input
    brakeProxy->processBrakeInput(20); // Overrides for safety

    delete steeringActuator; // Clean up memory
    delete brakeActuator;
    delete steeringProxy;
    delete brakeProxy;

    return 0;
}
