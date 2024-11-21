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
        std::cout << "Content: " << state << std::endl;
    }

    std::string getState() const { return state; }

    Memento saveState() const { //saves the current into memento
        return Memento(state);
    }
    void restoreState(const Memento& memento){ //restore the editor's state
        state = memento.getState();
        std::cout << "Content: " << state << std::endl;
    }
};

class Caretaker { //caretaker class
private:
    std::vector<Memento> history;

public:
    void save(const Memento& memento) { // Save state to history
        history.push_back(memento);
    }

    Memento undo() {
        if (history.empty()) {
            throw std::out_of_range("No states to undo!");
        }
        Memento memento = history.back();
        history.pop_back();
        return memento;
    }
};

int main() {
    TextEditor editor;
    Caretaker caretaker;

    editor.setState("Hello, world!");
    caretaker.save(editor.saveState());

    editor.setState("Hello, world! This is the Memento pattern.");
    caretaker.save(editor.saveState());

    editor.setState("Final version of the text.");

    editor.restoreState(caretaker.undo()); //undo to "Hello, world! This is the Memento pattern."
    editor.restoreState(caretaker.undo()); //undo to "Hello, world!"

    return 0;
}
