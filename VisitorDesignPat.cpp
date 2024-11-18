#include <iostream>
#include <vector>
#include <memory>

class File; //forward declaration of classes
class Folder;

class Visitor { //visitor interface that visits File and Folder
public:
    virtual void visitFile(File* file) = 0; 
    virtual void visitFolder(Folder* folder)= 0;
};

class FileSysItem{ //abstract element interface
public:
    virtual void accept(Visitor* visitor) = 0; //accepts visitors 
    virtual ~FileSysItem() = default; //virtual destructor
};

class File : public FileSysItem{ //represents a file in the file system
    std::string name;
    int size; 
public:
    File(const std::string& n, int s) : name(n), size(s){}

    std::string getName() const { return name; } //retrieve file information
    int getSize() const { return size; }

    void accept(Visitor* visitor) override { //accept visitor and allow it to perform operations
            visitor->visitFile(this);
    }
};

class Folder : public FileSysItem{ //represents a folder that can contain other files/folder
    std:: string name;
    std::vector<FileSysItem*> items;
public:
    Folder(const std::string& n) : name(n){}

    void addItem(FileSysItem* item){ //add file or folder to this folder
        items.push_back(item);
    }
    const std::vector<FileSysItem*>& getItems() const{
    return items;
    }

    void accept(Visitor* visitor) override{ //accept visitor & allow operations
        visitor->visitFolder(this);
    }

    ~Folder(){
        for(auto* item : items) {
            delete item; //free memory of contained items
        }
    }
};

class SizeCalc : public Visitor{
    int totalSize = 0; //accumulte size of all files visited
public:
    void visitFile(File* file) override {
        std::cout << "Visiting file: " << file->getName()
        << " (Size:" << file->getSize() << "KB)\n";
        totalSize += file-> getSize(); //add size of file to total
    }
    void visitFolder(Folder* folder) override {
        std::cout << "visiting folder: " << folder->getItems().size() << " item inside\n";
        for (auto* item : folder->getItems()) {
            item->accept(this); //'accept" to visit each contained item
        }

    }

    int getTotalSize() const { // get total size of visited files
        return totalSize;
    }

};

int main(){ //creating the folder structure

    Folder* root = new Folder("root"); 
    root->addItem(new File("file1.txt", 100));//adding .txt files to root
    root->addItem(new File("file2.txt", 200));

    Folder* subFolder = new Folder("subfolder"); //creating subfolder
    subFolder->addItem(new File("file3.txt", 300));//adding to subfolder
    root->addItem(subFolder);

    SizeCalc calculator; //creating visitor
    root->accept(&calculator);
    std::cout << "Total size of files: " << calculator.getTotalSize()<< " KB\n";//display total size of all files

    delete root; //deletes all files and subfolders in structure
    return 0;
}