# C++ Design Patterns

A multitude of design patterns implemented in modern C++. Structs are used in many places instead of classes to avoid
dealing with private/public members and just focus on the pattern itself.
Currently contains:
 - Overview and examples of **SOLID** principles:
 	1. **Single-responsibility principle** - A class should only have a single responsibility, that is, only changes to one part of the software's specification should be able to affect the specification of the class.
	2. **Open-closed principle** - "Software entities ... should be open for extension, but closed for modification."
	3. **Liskov substitution principle** - "Objects in a program should be replaceable with instances of their subtypes without altering the correctness of that program."
	4. **Interface segregation principle** - "Many client-specific interfaces are better than one general-purpose interface."
	5. **Dependency inversion principle** - One should "depend upon abstractions, [not] concretions."
 - The **Maybe** monad
 - **Creational** patterns:
 	- **Builder (Classic, Fluent, Groovy Style, Facets)** - When piecewise object construction is complicated, provide and API for doing it succinctly.
	- **Factory (Factory Method, Inner Factory, Abstract Factory, Functional Factory)** - A separate component solely responsible for wholesale (not piecewise) creation of objects.
	- **Prototype (Classic Prototype, Prototype Factory, Boost.Serialization use-case)** - A partially or fully initialized object that you copy (clone) and make use of.
	- **Singleton (Naive Singleton, Meyers Singleton)** - A component which is instantiated only once.
 - **Structural** patterns:
	- **Adapter (std::stack, Classig, Caching Adapter)** - A construct which adapts an existing interface X to conform to the required interface Y.
	- **Bridge (Classic, PImpl)** - A mechanism that decouples an interface (hierarchy) from an implementation (hierarchy).
	- **Composite (Composite Pattern, use-cases)** - A mechanism for treating individual (scalar) objects and compositions of objects in a uniform manner.
	- **Decorator (Function, Wrapping, Mixin Inheritance)** - Allows adding behavior to individual objects without affecting the behavior of other objects of the same class.
	- **Facade (Facade Pattern use-case)** - Provides a simple, easy to use/understand interface over a large and sophisticated body of code.
	- **Flyweight (Classic, Boost.Flyweight)** - A space optimization technique that lets us use less memory by externally storing the data associated with similar objects.
	- **Null Object** - A no-op object that satisfies the requirements of some other object.
	- **Proxy** - A class that functions as an interface to a particular resource. That resource may be remote, expensive to construct, may require logging or some other functionality.
 - **Behavioral** patterns:
 	- **Chain of Responsibility (Pointer Chain, Centralized Broker)** - A chain of components who all get a chance to process a command or query, optionally having a default processing implementation and an ability to terminate the processing chain.
	- **Command (Classic, Undo/Redo, Composite)** - An object which represents an instruction to perform a particular action. Contains all information necessary for the action to be taken.
	- **Interpreter** - A component that processes structured (text) data. It does so by turning it into separate lexical tokens (lexing) and then interpreting sequences of said tokens (parsing).
	- **Iterator (STL iterators, Iterator, Boost.IteratorFacade)** - An object that facilitates the traversal of a data structure.
	- **Memento (Classic, Undo/Redo)** - A token/handle representing the system state. Lets us roll back to the state when the token was generated. May or may not directly expose state information.

