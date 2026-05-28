from datetime import datetime

expenses = []


def get_valid_date():
    while True:
        date_text = input("Enter date (YYYY-MM-DD): ").strip()

        try:
            datetime.strptime(date_text, "%Y-%m-%d")
            return date_text
        except ValueError:
            print("Invalid date format. Please use YYYY-MM-DD.")


def get_valid_amount():
    while True:
        amount_text = input("Enter amount: $").strip()

        try:
            amount = float(amount_text)

            if amount <= 0:
                print("Amount must be greater than 0.")
            else:
                return amount

        except ValueError:
            print("Invalid amount. Please enter a valid number.")


def add_expense():
    print("\n--- Add Expense ---")

    date = get_valid_date()
    amount = get_valid_amount()
    category = input("Enter category: ").strip()
    description = input("Enter description: ").strip()

    expense = {
        "date": date,
        "amount": amount,
        "category": category,
        "description": description
    }

    expenses.append(expense)

    print("Expense added successfully.")


def view_expenses():
    print("\n--- View All Expenses ---")

    if not expenses:
        print("No expenses have been added.")
        return

    for index, expense in enumerate(expenses, start=1):
        print(
            f"{index}. Date: {expense['date']} | "
            f"Amount: ${expense['amount']:.2f} | "
            f"Category: {expense['category']} | "
            f"Description: {expense['description']}"
        )


def filter_by_category():
    print("\n--- Filter by Category ---")

    if not expenses:
        print("No expenses have been added.")
        return

    search_category = input("Enter category to search: ").strip().lower()

    filtered_expenses = [
        expense for expense in expenses
        if expense["category"].lower() == search_category
    ]

    if not filtered_expenses:
        print("No expenses found for that category.")
        return

    for index, expense in enumerate(filtered_expenses, start=1):
        print(
            f"{index}. Date: {expense['date']} | "
            f"Amount: ${expense['amount']:.2f} | "
            f"Category: {expense['category']} | "
            f"Description: {expense['description']}"
        )


def filter_by_date():
    print("\n--- Filter by Date ---")

    if not expenses:
        print("No expenses have been added.")
        return

    search_date = get_valid_date()

    filtered_expenses = [
        expense for expense in expenses
        if expense["date"] == search_date
    ]

    if not filtered_expenses:
        print("No expenses found for that date.")
        return

    for index, expense in enumerate(filtered_expenses, start=1):
        print(
            f"{index}. Date: {expense['date']} | "
            f"Amount: ${expense['amount']:.2f} | "
            f"Category: {expense['category']} | "
            f"Description: {expense['description']}"
        )


def view_summary():
    print("\n--- Expense Summary ---")

    if not expenses:
        print("No expenses have been added.")
        return

    overall_total = 0
    category_totals = {}

    for expense in expenses:
        overall_total += expense["amount"]
        category = expense["category"]

        if category in category_totals:
            category_totals[category] += expense["amount"]
        else:
            category_totals[category] = expense["amount"]

    print(f"Overall Total: ${overall_total:.2f}")
    print("\nTotals by Category:")

    for category, amount in category_totals.items():
        print(f"{category}: ${amount:.2f}")


def main_menu():
    while True:
        print("\n===== Expense Tracker Application - Python Version =====")
        print("1. Add Expense")
        print("2. View All Expenses")
        print("3. Filter by Category")
        print("4. Filter by Date")
        print("5. View Expense Summary")
        print("6. Exit")

        choice = input("Choose an option: ").strip()

        if choice == "1":
            add_expense()
        elif choice == "2":
            view_expenses()
        elif choice == "3":
            filter_by_category()
        elif choice == "4":
            filter_by_date()
        elif choice == "5":
            view_summary()
        elif choice == "6":
            print("Exiting Expense Tracker. Goodbye!")
            break
        else:
            print("Invalid option. Please choose a number from 1 to 6.")


if __name__ == "__main__":
    main_menu()