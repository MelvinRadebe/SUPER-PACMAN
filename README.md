Software Development SIDE Project (RUN the .exe or compile and ENJOY!!!)
👾 Super Pac-Man
A modern, scalable take on the classic Pac-Man game — built with maintainability and extensibility in mind.

🚀 Features
State-based Ghost AI
Ghost behavior is managed using a flexible state pattern. Each ghost can transition between:

ChaseState

ScatterState

FrightenedState
New states can easily be added in the future.

Polymorphic Behavior
An abstract GhostState class defines the shared interface, while child classes implement unique movement strategies. This promotes clean, modular, and testable code.

State Machine for Game Flow
A dedicated GameStateMachine class handles transitions between ghost states and overall game phases, enabling scalable logic and future expansion.

🛠️ Architecture Highlights
Object-oriented design using inheritance and polymorphism

Clean separation of concerns

Open to extension, closed to modification. 



