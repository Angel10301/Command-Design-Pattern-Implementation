# Python Singleton Pattern
class Singleton:
    _instance = None  # class attribute to store the single instance

    def __new__(cls, *args, **kwargs):        
        if not cls._instance: # If no instance exists, create one and assign it to _instance
            cls._instance = super(Singleton, cls).__new__(cls, *args, **kwargs)
        return cls._instance

# Example usage
singleton1 = Singleton()
singleton2 = Singleton()

print(singleton1 is singleton2)  # Output: True, both are the same instance
