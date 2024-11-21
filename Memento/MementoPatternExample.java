// Java Memento Pattern
import java.util.Stack;

public class MementoPatternExample {
    public static void main(String[] args) {
        TextEditor editor = new TextEditor();
        UndoManager undoManager = new UndoManager();

        editor.write("Hello, world!"); // Write and save the first version
        System.out.println("Content: " + editor.getContent());    // Outputs: Hello, world!
        undoManager.save(editor.save());  // Save the state

        editor.write("Hello, world! This is the Memento pattern."); // Write and save the second version
        System.out.println("Content: " + editor.getContent());    // Outputs: Hello, world! This is the Memento pattern.
        undoManager.save(editor.save());  // Save the state

        editor.write("Final version of the text."); // Write and save the third version
        System.out.println("Content: " + editor.getContent());    // Outputs: Final version of the text.

        editor.restore(undoManager.undo()); // Undo the last action
        System.out.println("After undo: " + editor.getContent());  // Outputs: Hello, world! This is the Memento pattern.

        editor.restore(undoManager.undo()); // Undo again
        System.out.println("After second undo: " + editor.getContent());  // Outputs: Hello, world!
    }
}

class Memento { // Memento class
    private final String state;

    public Memento(String state) {
        this.state = state;
    }

    public String getState() {
        return state;
    }
}

class TextEditor { // Originator class
    private String content;

    public void write(String text) {
        content = text;
    }

    public String getContent() {
        return content;
    }

    public Memento save() { // Save the current state into a memento
        return new Memento(content);
    }

    public void restore(Memento memento) { // Restore the editor's state from a memento
        content = memento.getState();
    }
}

class UndoManager { // Caretaker class
    private Stack<Memento> history = new Stack<>();

    public void save(Memento memento) { // Save a memento to the history stack
        history.push(memento);
    }

    public Memento undo() { // Retrieve the most recent memento from the stack
        if (!history.isEmpty()) {
            return history.pop();
        }
        return null;
    }
}
