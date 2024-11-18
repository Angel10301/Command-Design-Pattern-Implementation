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
    void knock(){std::cout << "Door knocked." << std::endl;}
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

class DoorControl{ //invoker
    Command* command;
public:
    void setCommand(Command* cmd) { command = cmd;} //sets the current command to be executed
    void pressButton() { command->execute();} //executes when command is pressed
};

int main(){
    Door door; //create Door object aka receiver
    DoorBell doorbell; //create Door object aka receiver
    OpenDoor openCommand(&door); //command to open door, assoicated with Door object
    CloseDoor closeCommand(&door); //command to close, associated with Door object
    KnockDoor knockCommand(&door); //command to knock, associated with Door object
    RingDoor ringCommand(&doorbell); //command to knock, associated with DoorBell object

    DoorControl control; //invoker that executes the commands

    control.setCommand(&knockCommand);
    control.pressButton();
    
    control.setCommand(&ringCommand);
    control.pressButton();
    
    control.setCommand(&openCommand); //sets command to "OpenDoor"
    control.pressButton(); //"open" command, outputs: "Door is open"

    control.setCommand(&closeCommand);
    control.pressButton();

    return 0;
}
