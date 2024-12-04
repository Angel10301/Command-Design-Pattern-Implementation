# This code demonstrates the Interpreter Design Pattern by simulating a system that parses and executes instructions based on predefined actions and executes the corresponding behavior dynamically.

class Expression: # Abstract expression class
    def interpret(self, context):
        pass

class Medicate(Expression): # Terminal expression classes for diffrent actions
    def interpret(self, context):
        print(f"Administering medication for {context} ")

class Observe(Expression): # Terminal expression class for observing a specific parameter
    def interpret(self, context):
        print(f"Observing {context}")

class Rest(Expression):
    def interpret(self, context):
        print(f"Observing {context}") # Perform the observation with the given context

class InstructionInterpreter: # Interpreter class to parse instructions and execute them
    def __init__(self):
        self.actions = {
            "MEDICATE": Medicate(),
            "OBSERVE": Observe(),
            "REST": Rest()
        }
    def interpret(self, instruction):
        parts = instruction.split()
        action = parts[0]
        context = parts[1]

        if action in self.actions:
            self.actions[action].interpret(context)
        else:
            print(f"Unknown instruction: {instruction}")

if __name__ == "__main__": # Main execution to demonstrate the interpreter design Pattern
    interpreter = InstructionInterpreter()

    interpreter.interpret("MEDICATE Fever") # Test for various intructions
    interpreter.interpret("OBSERVE BloodPressure")
    interpreter.interpret("REST Patient")

