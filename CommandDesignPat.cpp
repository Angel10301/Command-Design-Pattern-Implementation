//This program depicts the command design pattern, which is a behavioral design pattern. 
//Its purpose is to encapsulate a request as an object, allowing you to parameterize objects with different requests, 
//delay the execution of a request, or support undoable operations.
//The program was written in C++. This program is a simulation of a doorbell being rang, followed by a knock on the door, 
//till finally the door is opened, then ultimatly closed. It works in correlation to the figure in the slides,
//encapsulating how the invoker goes to the Command to execute, then to ConcreteCommand which sends an action to the receiver.
#include <iostream>

class Command { //command interface
public:
    virtual void execute() = 0; //implemented by concrete commands
    virtual ~Command() = default; //destructor to cleanup derived classes
};

class Interactible{
public:
    virtual void signalPresence() = 0;
};

class DoorBell : public Interactible{ //Receiver
    Interactible* inter;
public:
    void signalPresence() override {std::cout << "Doorbell rang." << std::endl;}
};

class Door : public Interactible{ //Receiver
    Interactible* inter;
public:
    void signalPresence() override {std::cout << "Door knocked." << std::endl;}
    void open(){std::cout<< "Door opened." << std::endl;}
    void close(){std::cout << "Door closed." << std::endl;}
};

class OpenDoor : public Command { //concrete Commands
    Door* door; //pointer to Door object (reciver)
public:
    OpenDoor(Door* d) : door(d){}
    void execute() override { door->open();}//open door
};

class CloseDoor : public Command { 
    Door* door;
public:
    CloseDoor(Door* d) : door(d) {}
    void execute() override { door->close();} //close door
};

class KnockDoor : public Command { 
    Door* door;
public:
    KnockDoor(Door* d) : door(d) {}
    void execute() override { door->signalPresence();} //knock door
};

class RingDoor : public Command { 
    DoorBell* doorbell;
public:
    RingDoor(DoorBell* d) : doorbell(d) {}
    void execute() override { doorbell->signalPresence();} //knock door
};

class Performer{ //invoker
    Command* command;
public:
    void setCommand(Command* cmd) { command = cmd;} //sets the current command to be executed
    void act() { command->execute();} //executes when command is pressed
};

int main(){
    Door door; //create Door object aka receiver
    DoorBell doorbell; //create Door object aka receiver
    OpenDoor openCommand(&door); //command to open door, assoicated with Door object
    CloseDoor closeCommand(&door); //command to close, associated with Door object
    KnockDoor knockCommand(&door); //command to knock, associated with Door object
    RingDoor ringCommand(&doorbell); //command to knock, associated with DoorBell object

    Performer perform; //invoker that executes the commands

    perform.setCommand(&knockCommand);
    perform.act();
    
    perform.setCommand(&ringCommand);
    perform.act();
    
    perform.setCommand(&openCommand); //sets command to "OpenDoor"
    perform.act(); //"open" command, outputs: "Door is open"

    perform.setCommand(&closeCommand);
    perform.act();

    return 0;
}
