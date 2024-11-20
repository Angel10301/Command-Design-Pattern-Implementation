#include <iostream>
#include <vector>
#include <string>

class Memento{ //creating the Memento class that will store the state
private:
    std::string state;

public:
    Memento(const std::string& state) : state(state){} //stores the state as a string
    std::string getState() const { return state; } //getState() method provides access to the saved state
};

class TextEditor{ //creating the originator class
private:
    std::string state;

public:
    void setState(const std::string& newState){
        state = newState;
        std::cout << "State changed to: " << state << std::endl;
    }

    std::string getState() const { return state; }

    Memento saveState() const { //saves the current into memento
        return Memento(state);
    }
    void restoreState(const Memento& memento){ //restore the editor's state
        state = memento.getState();
        std::cout << "State restored to: " << state << std::endl;
    }
};

class Caretaker { //caretaker class
private:
    std::vector<Memento> histroy;

public:
    void save(const Memento& menmento) {
        histroy.push_back(menmento);
    }

    Memento get(int index) const {
        if (index >= 0 && index < histroy.size()) {
            return histroy[index];
        }
        throw std::out_of_range("Invalid Index");
    }
};

int main() {
    TextEditor originator;
    Caretaker caretaker;

    originator.setState("State1");
    caretaker.save(originator.saveState());

    originator.setState("State2");
    caretaker.save(originator.saveState());

    originator.setState("State3");

    originator.restoreState(caretaker.get(0)); // Undo to State1

    return 0;
}