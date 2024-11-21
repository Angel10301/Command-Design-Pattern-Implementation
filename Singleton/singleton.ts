// TypeScript Singleton Pattern
class Singleton {
    private static instance: Singleton;
    private constructor() { // Private constructor prevents direct construction calls with 'new'
    }

    public static getInstance(): Singleton {
        if (!Singleton.instance) { // If no instance exists, create one
            Singleton.instance = new Singleton();
        }
        return Singleton.instance;
    }

    public someBusinessLogic() {
        console.log("Executing business logic");
    }
}

// Example usage of singleton
const instance1 = Singleton.getInstance();
const instance2 = Singleton.getInstance();
console.log(instance1 === instance2); // Output: True, both are the same instance
