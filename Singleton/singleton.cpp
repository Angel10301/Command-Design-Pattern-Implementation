// C++ Singleton Pattern
#include <iostream>

class Singleton {
	private:
		static Singleton* instance;
		Singleton() { // Private constructor
		}

	public:
		static Singleton* getInstance() {
			if (instance == nullptr) { // If no instance exists, create one
				instance = new Singleton();
			}
			return instance;
		}

		void doSomething() {
			std::cout << "Doing something in the Singleton." << std::endl;
		}

	private:
		// Disable copy and assignment
		Singleton(const Singleton&) = delete;
		Singleton& operator=(const Singleton&) = delete;
};

Singleton* Singleton::instance = nullptr; // Initialize the static instance pointer to nullptr

int main() {
    // Exaample Singleton usage
    Singleton* singleton1 = Singleton::getInstance();
    singleton1->doSomething();

    Singleton* singleton2 = Singleton::getInstance();
    std::cout << "Singleton1 == Singleton2? " << (singleton1 == singleton2) << std::endl; // 1=>true

    return 0;
}