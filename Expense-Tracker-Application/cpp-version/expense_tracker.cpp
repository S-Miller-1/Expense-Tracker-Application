#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <limits>
#include <map>
#include <regex>
#include <cctype>

using namespace std;

struct Expense {
    string date;
    double amount;
    string category;
    string description;
};

vector<Expense> expenses;

bool isValidDate(const string& date) {
    regex datePattern("^\\d{4}-\\d{2}-\\d{2}$");
    return regex_match(date, datePattern);
}

string getValidDate() {
    string date;

    while (true) {
        cout << "Enter date (YYYY-MM-DD): ";
        getline(cin, date);

        if (isValidDate(date)) {
            return date;
        }

        cout << "Invalid date format. Please use YYYY-MM-DD." << endl;
    }
}

double getValidAmount() {
    double amount;

    while (true) {
        cout << "Enter amount: $";
        cin >> amount;

        if (cin.fail() || amount <= 0) {
            cout << "Invalid amount. Please enter a valid number greater than 0." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return amount;
        }
    }
}

string toLowerCase(string text) {
    for (char& character : text) {
        character = static_cast<char>(tolower(character));
    }

    return text;
}

void printExpense(const Expense& expense, int index) {
    cout << index << ". Date: " << expense.date
         << " | Amount: $" << fixed << setprecision(2) << expense.amount
         << " | Category: " << expense.category
         << " | Description: " << expense.description
         << endl;
}

void addExpense() {
    cout << "\n--- Add Expense ---" << endl;

    Expense expense;

    expense.date = getValidDate();
    expense.amount = getValidAmount();

    cout << "Enter category: ";
    getline(cin, expense.category);

    cout << "Enter description: ";
    getline(cin, expense.description);

    expenses.push_back(expense);

    cout << "Expense added successfully." << endl;
}

void viewExpenses() {
    cout << "\n--- View All Expenses ---" << endl;

    if (expenses.empty()) {
        cout << "No expenses have been added." << endl;
        return;
    }

    for (size_t i = 0; i < expenses.size(); i++) {
        printExpense(expenses[i], static_cast<int>(i + 1));
    }
}

void filterByCategory() {
    cout << "\n--- Filter by Category ---" << endl;

    if (expenses.empty()) {
        cout << "No expenses have been added." << endl;
        return;
    }

    string category;

    cout << "Enter category to search: ";
    getline(cin, category);

    string searchCategory = toLowerCase(category);

    bool found = false;
    int count = 1;

    for (const Expense& expense : expenses) {
        if (toLowerCase(expense.category) == searchCategory) {
            printExpense(expense, count);
            count++;
            found = true;
        }
    }

    if (!found) {
        cout << "No expenses found for that category." << endl;
    }
}

void filterByDate() {
    cout << "\n--- Filter by Date ---" << endl;

    if (expenses.empty()) {
        cout << "No expenses have been added." << endl;
        return;
    }

    string date = getValidDate();

    bool found = false;
    int count = 1;

    for (const Expense& expense : expenses) {
        if (expense.date == date) {
            printExpense(expense, count);
            count++;
            found = true;
        }
    }

    if (!found) {
        cout << "No expenses found for that date." << endl;
    }
}

void viewSummary() {
    cout << "\n--- Expense Summary ---" << endl;

    if (expenses.empty()) {
        cout << "No expenses have been added." << endl;
        return;
    }

    double overallTotal = 0.0;
    map<string, double> categoryTotals;

    for (const Expense& expense : expenses) {
        overallTotal += expense.amount;
        categoryTotals[expense.category] += expense.amount;
    }

    cout << "Overall Total: $" << fixed << setprecision(2) << overallTotal << endl;
    cout << "\nTotals by Category:" << endl;

    for (const auto& pair : categoryTotals) {
        cout << pair.first << ": $" << fixed << setprecision(2) << pair.second << endl;
    }
}

void mainMenu() {
    int choice;

    while (true) {
        cout << "\n===== Expense Tracker Application - C++ Version =====" << endl;
        cout << "1. Add Expense" << endl;
        cout << "2. View All Expenses" << endl;
        cout << "3. Filter by Category" << endl;
        cout << "4. Filter by Date" << endl;
        cout << "5. View Expense Summary" << endl;
        cout << "6. Exit" << endl;
        cout << "Choose an option: ";

        cin >> choice;

        if (cin.fail()) {
            cout << "Invalid option. Please choose a number from 1 to 6." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                addExpense();
                break;
            case 2:
                viewExpenses();
                break;
            case 3:
                filterByCategory();
                break;
            case 4:
                filterByDate();
                break;
            case 5:
                viewSummary();
                break;
            case 6:
                cout << "Exiting Expense Tracker. Goodbye!" << endl;
                return;
            default:
                cout << "Invalid option. Please choose a number from 1 to 6." << endl;
        }
    }
}

int main() {
    mainMenu();
    return 0;
}