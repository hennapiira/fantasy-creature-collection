# Fantasy Creature Collection

## 🐉 Project Description

This is a personal learning project in C++. The goal was to practice database handling, object-oriented programming, and building a simple command-line interface. The application lets you manage a collection of fantasy creatures and experiment with user authentication and PostgreSQL integration.

## ✨ Features

- **Add, remove and list creatures** in your collection
- **User authentication** with password handling
- **Database integration** using PostgreSQL
- **Simple text-based interface** for easy interaction

## 🛠 Technologies

- **C++** – Main programming language
- **PostgreSQL** – Database for storing creatures and user data
- **lipqxx** – C++ library for PostgreSQL integration

## 🚀 Installation

1. Clone the repository:

```
git clone <repository-url>
cd fantasy-creature-collection
```

Build the project:

```
g++ src/main.cpp src/db/dbConn.cpp src/db/dbMethods.cpp src/auth.cpp src/utils.cpp src/controller.cpp src/creature.cpp -lpqxx -lpq -o fcc
```

Run the program:

```
./fcc.exe
```
