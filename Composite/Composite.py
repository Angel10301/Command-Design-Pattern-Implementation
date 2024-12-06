class TreeComponent: # Base class for both branches and leaves
    def show_details(self):
        pass
	
class Leaf(TreeComponent): # Leaf class representing an individual leaf
    def __init__(self, name):
        self.name = name
        
    def show_details(self):
        print(f"Leaf: {self.name}")
	
class Branch(TreeComponent): # Composite class representing a branch, which can hold leaves or other branches
    def __init__(self, name):
        self.name = name
        self.children = []
        
    def add_child(self, child):
        self.children.append(child)
        
    def show_details(self):
        print(f"Branch: {self.name}")
        for child in self.children:
            child.show_details()

if __name__ == "__main__": # Client code to create a tree structure
    # Create leaves
    leaf1 = Leaf("Leaf A")
    leaf2 = Leaf("Leaf B")
    leaf3 = Leaf("Leaf C")
    
    # Create branches
    branch1 = Branch("Branch 1")
    branch2 = Branch("Branch 2")
    
    # Add leaves to branches
    branch1.add_child(leaf1)
    branch1.add_child(leaf2)
    branch2.add_child(leaf3)
    
    # Create a main tree branch
    tree = Branch("Main Tree")
    tree.add_child(branch1)
    tree.add_child(branch2)
    
    # Display the whole tree
    tree.show_details()
