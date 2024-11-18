#include <iostream>

class Command { //command interface
public:
    virtual void execute() = 0; //implemented by concrete commands
    virtual ~Command() = default; //destructor to cleanup derived classes
};

class Door { //Receiver
public:
    void open(){std::cout<< "Door is open." << std::endl;}
    void close(){ std:: cout << "Door is closed." << std::endl;}
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

class DoorControl{ //invoker
    Command* command;
public:
    void setCommand(Command* cmd) { command = cmd;} //sets the current command to be executed
    void pressButton() { command->execute();} //executes when command is pressed
};

int main(){
    Door door; //create Door object aka receiver
    OpenDoor openCommand(&door); //command to open door, assoicated with Door object
    CloseDoor closeCommand(&door); //command to close, associated with Door object

    DoorControl control; //invoker that executes the commands

    control.setCommand(&openCommand); //sets command to "OpenDoor"
    control.pressButton(); //"open" command, outputs: "Door is open"

    control.setCommand(&closeCommand);
    control.pressButton();

    return 0;
}
