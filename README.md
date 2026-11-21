# Object-Oriented Bank & Currency Management System

[![C++ Version](https://img.shields.io/badge/C%2B%2B-17%2F20-blue.svg?style=flat-square&logo=c%2B%2B)](https://en.cppreference.com/)
[![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey.svg?style=flat-square&logo=windows)](https://microsoft.com/)
[![IDE](https://img.shields.io/badge/IDE-Visual%20Studio%202022-purple.svg?style=flat-square&logo=visual-studio)](https://visualstudio.microsoft.com/)

A console banking application written in **C++** with a fully object-oriented design: clients, users, transactions and currency exchange are modeled as classes over file-based storage.

**Timeline:** Jun 2026 · **Stack:** C++17 · OOP · File I/O · Visual Studio

---

## 🏗️ Architecture

```
bank-system/
├── Core/        Domain classes: clsBankClient, clsUser, clsPerson, clsCurrency, clsTransactionLog
├── Screens/     One screen class per feature (login, clients, transactions, users, currency)
└── Utils/       clsDate, clsString, clsInputValidate, clsUtil
```

Every screen inherits from a shared `clsScreen` base; business objects live in `Core/`, independent of the UI.

## 🔑 Features

- **Client management (CRUD):** add, update, delete, find and list clients
- **Transactions:** deposits, withdrawals and inter-account transfers with real-time balance checks
- **Transfer log:** every transfer recorded with time, accounts, amount and operator username
- **User management:** bitwise permission flags (9 distinct permissions: list clients, add user, manage currencies, ...)
- **Login register:** every sign-in logged with date and time
- **Currency exchange:** currency list, rate management and a conversion calculator
- **Stored passwords encrypted** (Caesar cipher)

## 🛠️ Technologies

C++17 · Object-Oriented Programming · File-based persistence (text files) · Visual Studio
