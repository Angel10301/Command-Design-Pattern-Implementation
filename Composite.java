//The composite design pattern uses composition to represent a tree structure
// It consists of TreeComponent a basic class, Leaf that represents individual leaves in the structure, and Branch that are branches that can contain other branches or leaves.

import java.util.ArrayList;
import java.util.List;

interface TreeComponent {// Abstract component
    void operation(); // Method to be implemented by all components
}
class Leaf implements TreeComponent { // Leaf class representing individual elements
    private String name;

    public Leaf(String name) {
        this.name = name;
    }

    @Override // Performing the operation specific to the leaf display
    public void operation() { 
        System.out.println("Leaf: " + name);
    }
}

class Branch implements TreeComponent { // Branch class representing composite elements
    private String name;
    private List<TreeComponent> children = new ArrayList<>(); // List to store children (branches or leaves)

    public Branch(String name) {
        this.name = name;
    }

    public void addChild(TreeComponent component) {
        children.add(component);
    }

    @Override // Performing operation specific to the branch
    public void operation() {
        System.out.println("Branch: " + name);
        for (TreeComponent child : children) {
            child.operation();
        }
    }
}

public class Main{
    public static void main(String[] args) { // Creating individual leaf nodes

        TreeComponent leaf1 = new Leaf("Leaf A"); // Create leaves
        TreeComponent leaf2 = new Leaf("Leaf B");
        TreeComponent leaf3 = new Leaf("Leaf C");

        Branch branch1 = new Branch("Branch 1"); // Create branch and add the children
        branch1.addChild(leaf1);
        branch1.addChild(leaf2);

        Branch branch2 = new Branch("Branch 2"); // Again Creating branch and adding the children
        branch2.addChild(leaf3);

        Branch mainTree = new Branch("Main Tree"); // Create main tree (root branch)
        mainTree.addChild(branch1);
        mainTree.addChild(branch2);

        mainTree.operation(); // Display the tree structure
    }
}

