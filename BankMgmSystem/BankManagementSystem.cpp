#include <iostream>
#include <string>
#include <limits>
#include <conio.h>
#include <sstream> // Required for std::ostringstream
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_RESET "\033[0m"
#define COLOR_RED "\033[31m"
#define font_bold "\033[1m"
using namespace std;
void wait_for_keypress() {
    cout << "Press Enter to continue...";
    getch();
    system("cls");
}
int getValidInputForInt() {
    int input;
    while (!(cin >> input)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << COLOR_RED << "Invalid input. Please enter a number: " << COLOR_RESET;
    }
    return input;
}
double getValidInputForDouble() {
    double input;
    while (!(cin >> input)) {
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        cout << COLOR_RED << "Invalid input. Please enter a numeric value: " << COLOR_RESET;
    }
    return input;
}
struct Admin {
    string username;
    string password;
    string accessLevel;
};
const Admin ADMINS[] = {
    {"admin1", "admin123", "full-access"},
    {"admin2", "admin456", "read-only"}
};
const int NUM_ADMINS = 2;
bool authenticateAdmin(string& accessLevel) {
    string username, password;
    cout << "Enter Admin Username: ";
    cin >> username;
    cout << "Enter Admin Password: ";
    password = "";
    char ch;
    while ((ch = getch()) != '\r') { // Mask password input
        if (ch == '\b' && !password.empty()) { // Handle backspace
            password.erase(password.length() - 1); // Remove the last character
            cout << "\b \b"; // Move cursor back and erase the character
        } else if (ch != '\b') {
            password.push_back(ch); // Add the character to the password
            cout << '*'; // Display '*' for each character
        }
    }
    cout << endl;
    for (int i = 0; i < NUM_ADMINS; i++) {
        if (username == ADMINS[i].username && password == ADMINS[i].password) {
            accessLevel = ADMINS[i].accessLevel;
            cout << COLOR_GREEN << "Admin login successful!\n" << COLOR_RESET;
            wait_for_keypress();
            return true;
        }
    }
    cout << COLOR_RED << "Invalid admin credentials. Access denied!\n" << COLOR_RESET;
    wait_for_keypress();
    return false;
}
#define MAX_ACCOUNTS 100
class Bank {
private:
    string password, pin, recoveryCode;
    bool frozen;
    double loanAmount;
    int failedLoginAttempts;
public:
    string name, account_no;
    double balance;
    Bank() {
        name = "";
        account_no = "";
        balance = 0.0;
        password = "";
        pin = "";
        recoveryCode = "";
        loanAmount = 0.0;
        frozen = false;
        failedLoginAttempts = 0;
    }
    bool isValidName(string name) {
        bool hasUpper = false, hasLower = false;
        for (int i = 0; i < name.length(); i++) {
            char ch = name[i];
            if (!isalpha(ch) && ch != ' ') return false;
            if (isupper(ch)) hasUpper = true;
            if (islower(ch)) hasLower = true;
        }
        return hasUpper && hasLower;
    }

    string accNo() {
        static int accCounter = 100000;
        accCounter++;
        std::ostringstream oss;
        oss << accCounter;
        return oss.str();
    }

    bool isAccountUnique(Bank accounts[], int totalAccounts, string accNo) {
        for (int i = 0; i < totalAccounts; i++) {
            if (accounts[i].account_no == accNo) {
                return false;
            }
        }
        return true;
    }

    // Function to set a masked password/PIN/recovery code
    string setMaskedInputForPass(string prompt, int minLength , int maxLength) {
        string input;
        cout << prompt;
        input = "";
        char ch;
        while ((ch = getch()) != '\r') { // Mask input
            if (ch == '\b' && !input.empty()) { // Handle backspace
                input.erase(input.length() - 1); // Remove the last character
                cout << "\b \b"; // Move cursor back and erase the character
            } else if (ch != '\b') {
                input.push_back(ch); // Add the character to the input
                cout << '*'; // Display '*' for each character
            }
        }
        cout << endl;
        while (input.length() < minLength||input.length()>maxLength ||input.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ") == -1 ||
       input.find_first_of("abcdefghijklmnopqrstuvwxyz") == -1 ||
       input.find_first_of("0123456789") == -1 ||
       input.find_first_of("!@#$%^&*()-_=+[]{}|;:'\",.<>?/`~") == -1) {
        cout << COLOR_RED;
    
        if (input.length() < minLength || input.length() > maxLength) 
            cout << "Error: Password must be between " << minLength << " and " << maxLength << " characters long!\n";
            
        if (input.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ") == -1)
            cout << "Error: Password must contain at least one uppercase letter!\n";
    
        if (input.find_first_of("abcdefghijklmnopqrstuvwxyz") == -1)
            cout << "Error: Password must contain at least one lowercase letter!\n";
    
        if (input.find_first_of("0123456789") == -1)
            cout << "Error: Password must contain at least one digit!\n";
    
        if (input.find_first_of("!@#$%^&*()-_=+[]{}|;:'\",.<>?/`~") == -1)
            cout << "Error: Password must contain at least one special character!\n";
    
        cout << COLOR_RESET;
            cout << prompt;
            input = "";
            while ((ch = getch()) != '\r') {
                if (ch == '\b' && !input.empty()) {
                    input.erase(input.length() - 1); // Remove the last character
                    cout << "\b \b"; // Move cursor back and erase the character
                } else if (ch != '\b') {
                    input.push_back(ch); // Add the character to the input
                    cout << '*'; // Display '*' for each character
                }
            }
            cout << endl;
        }
        return input;
 {
            cout << COLOR_RED << "Input must be at least " << minLength << " characters long!\n" << COLOR_RESET;
            cout << prompt;
            input = "";
            while ((ch = getch()) != '\r') {
                if (ch == '\b' && !input.empty()) {
                    input.erase(input.length() - 1); // Remove the last character
                    cout << "\b \b"; // Move cursor back and erase the character
                } else if (ch != '\b') {
                    input.push_back(ch); // Add the character to the input
                    cout << '*'; // Display '*' for each character
                }
            }
            cout << endl;
        }
    }
    string setMaskedInput(string prompt, int minLength) {
        string input;
        cout << prompt;
        input = "";
        char ch;
        while ((ch = getch()) != '\r') { // Mask input
            if (ch == '\b' && !input.empty()) { // Handle backspace
                input.erase(input.length() - 1); // Remove the last character
                cout << "\b \b"; // Move cursor back and erase the character
            } else if (ch != '\b') {
                input.push_back(ch); // Add the character to the input
                cout << '*'; // Display '*' for each character
            }
        }
        cout << endl;
        while (input.length() != minLength || input.find_first_not_of("0123456789") != -1){
            cout << COLOR_RED;
    if (input.length() != minLength)
        cout << "Error: Input must be exactly " << minLength << " digits long!\n";
    if (input.find_first_not_of("0123456789") != -1)
        cout << "Error: Input must contain only numeric digits (0-9)!\n";
    cout << COLOR_RESET;
            cout << prompt;
            input = "";
            while ((ch = getch()) != '\r') {
                if (ch == '\b' && !input.empty()) {
                    input.erase(input.length() - 1); // Remove the last character
                    cout << "\b \b"; // Move cursor back and erase the character
                } else if (ch != '\b') {
                    input.push_back(ch); // Add the character to the input
                    cout << '*'; // Display '*' for each character
                }
            }
            cout << endl;
        }
        return input;
    }

    void createAccount(Bank accounts[], int totalAccounts) {
        cout << "Enter Name: ";
        cin.ignore(); // Clear input buffer
        getline(cin, name);
    
        while (!isValidName(name)) {
            cout << COLOR_RED << "Invalid Name! Name should contain at least one uppercase and one lowercase letter and it cannot contain numbers.\n" << COLOR_RESET;
            cout << "Enter Name: ";
            getline(cin, name);
        }
        string newAccNo;
        do {
            newAccNo = "B-"+ accNo() +"-2025";
        } while (!isAccountUnique(accounts, totalAccounts, newAccNo));
        account_no = newAccNo;
        cout << "Your Account Number is " << account_no << endl;
    
        cout << "Enter Initial Deposit: ";
        balance = getValidInputForDouble();
    
        while (balance <= 0) {
            cout << COLOR_RED << "Invalid Amount! Initial Deposit must be a positive number.\n" << COLOR_RESET;
            cout << "Enter Initial Deposit: ";
            balance = getValidInputForDouble();
        }
    
        password = setMaskedInputForPass("Set Account Password (at least 8 characters): ", 8,16);
        pin = setMaskedInput("Set 4-digit Numeric PIN: ", 4);
        recoveryCode = setMaskedInput("Set Account Recovery Code (at least 6 characters): ", 6);
    
        cout << COLOR_GREEN << "Account Created Successfully!\n" << COLOR_RESET;
        wait_for_keypress();
    }

    void showAccount() {
        if (name == "") {
            cout << COLOR_RED << "No account exists!\n" << COLOR_RESET;
            wait_for_keypress();
            return;
        }
        cout << font_bold << COLOR_YELLOW << "\n===== ACCOUNT DETAILS =====" << COLOR_RESET << endl;
        cout << "Name: " << name << endl;
        cout << "Account No: " << account_no << endl;
        cout << "Balance: $" << balance << endl;
        cout << "Loan Amount: $" << loanAmount << endl;
        cout << "Status: " << (frozen ? "Frozen" : "Active") << endl; // Display status
        cout << "-------------------------\n";
        wait_for_keypress();
    }

    bool verifyPIN() {
        if (frozen) {
            cout << COLOR_RED << "Account is frozen! Recover it first.\n" << COLOR_RESET;
            wait_for_keypress();
            return false;
        }
    
        string inputPIN = setMaskedInput("Enter 4-digit PIN: ", 4);
    
        if (inputPIN.length() != 4) {
            cout << COLOR_RED << "PIN must be 4 digits!\n" << COLOR_RESET;
            wait_for_keypress();
            return false;
        }
    
        if (inputPIN == pin) {
            failedLoginAttempts = 0;
            return true;
        } else {
            failedLoginAttempts++;
            if (failedLoginAttempts >= 3) {
                frozen = true;
                cout << COLOR_RED << "Too many failed attempts! Account frozen.\n" << COLOR_RESET;
            } else {
                cout << COLOR_RED << "Incorrect PIN!\n" << COLOR_RESET;
            }
            wait_for_keypress();
            return false;
        }
    }

    void deposit(double amount) {
        if (amount <= 0) {
            cout << COLOR_RED << "Invalid Amount! Amount must be a positive number.\n" << COLOR_RESET;
            wait_for_keypress();
            return;
        }

        if (!verifyPIN()) return;
        balance += amount;
        cout << COLOR_GREEN << "Amount Deposited Successfully. New Balance: $" << balance << COLOR_RESET << endl;
        wait_for_keypress();
    }

    void withdraw(double amount) {
        if (amount <= 0) {
            cout << COLOR_RED << "Invalid Amount! Amount must be a positive number.\n" << COLOR_RESET;
            wait_for_keypress();
            return;
        }

        if (!verifyPIN()) return;
        if (amount > balance) {
            cout << COLOR_RED << "Insufficient Balance!\n" << COLOR_RESET;
            wait_for_keypress();
        } else {
            balance -= amount;
            cout << COLOR_GREEN << "Amount Withdrawn Successfully. New Balance: $" << balance << COLOR_RESET << endl;
            wait_for_keypress();
        }
    }

    void transfer(Bank accounts[], int totalAccounts, double amount) {
        if (amount <= 0) {
            cout << COLOR_RED << "Invalid Amount! Amount must be a positive number.\n" << COLOR_RESET;
            wait_for_keypress();
            return;
        }
    
        if (!verifyPIN()) return;
        if (amount > balance) {
            cout << COLOR_RED << "Insufficient Balance!\n" << COLOR_RESET;
            wait_for_keypress();
            return;
        }
    
        string recipientAccNo;
        cout << "Enter Recipient Account No: ";
        cin >> recipientAccNo;
    
        bool recipientFound = false;
        for (int i = 0; i < totalAccounts; i++) {
            if (accounts[i].account_no == recipientAccNo) {
                if (accounts[i].frozen) {
                    cout << COLOR_RED << "Recipient account is frozen!\n" << COLOR_RESET;
                    wait_for_keypress();
                    return;
                }
                balance -= amount;
                accounts[i].balance += amount;
                cout << COLOR_GREEN << "Amount Transferred Successfully. New Balance: $" << balance << COLOR_RESET << endl;
                wait_for_keypress();
                recipientFound = true;
                break;
            }
        }
    
        if (!recipientFound) {
            cout << COLOR_RED << "Recipient Account Not Found!\n" << COLOR_RESET;
            wait_for_keypress();
        }
    }

    void checkBalance() {
        if (!verifyPIN()) return;
        cout << "Current Balance: $" << balance << endl;
        wait_for_keypress();
    }

    void recoverAccount() {
        if (!frozen) {
            cout << COLOR_YELLOW << "Your account is already active.\n" << COLOR_RESET;
            wait_for_keypress();
            return;
        }
        string inputCode = setMaskedInput("Enter Recovery Code: ", 6);

        if (inputCode == recoveryCode) {
            frozen = false;
            failedLoginAttempts = 0; // Reset failed attempts on recovery
            cout << COLOR_GREEN << "Account has been recovered successfully!\n" << COLOR_RESET;
            wait_for_keypress();
        } else {
            cout << COLOR_RED << "Incorrect Recovery Code! Account remains frozen.\n" << COLOR_RESET;
            wait_for_keypress();
        }
    }

    void resetPassword() {
        password = setMaskedInput("Enter New Password (at least 6 characters): ", 6);
        cout << COLOR_GREEN << "Password Updated Successfully!\n" << COLOR_RESET;
        wait_for_keypress();
    }

    void updateAccountInfo() {
        cout << "Enter New Name: ";
        cin.ignore();
        getline(cin, name);

        while (!isValidName(name)) {
            cout << COLOR_RED << "Invalid Name! Name should contain at least one uppercase and one lowercase letter and It cannot contain numbers.\n" << COLOR_RESET;
            cout << "Enter New Name: ";
            getline(cin, name);
        }

        resetPassword();
        cout << COLOR_GREEN << "Account Information Updated Successfully!\n" << COLOR_RESET;
        wait_for_keypress();
    }

    void closeAccount() {
        if (!verifyPIN()) return;
        string inputCode = setMaskedInput("Enter Recovery Code: ", 6);
    
        if (inputCode == recoveryCode) {
            name = "";
            account_no = "";
            balance = 0.0;
            password = "";
            pin = "";
            recoveryCode = "";
            loanAmount = 0.0; 
            frozen = false;
            cout << COLOR_GREEN << "Account Closed Successfully!\n" << COLOR_RESET;
            wait_for_keypress();
        } else {
            cout << COLOR_RED << "Incorrect Recovery Code! Account closure failed.\n" << COLOR_RESET;
            wait_for_keypress();
        }
    }

    void applyLoan(double amount) {
        if (amount <= 0) {
            cout << COLOR_RED << "Invalid Amount! Loan amount must be a positive number.\n" << COLOR_RESET;
            wait_for_keypress();
            return;
        }

        if (!verifyPIN()) return;
        loanAmount += amount;
        balance += amount;
        cout << COLOR_GREEN << "Loan Approved! Amount: $" << amount << " added to your balance.\n" << COLOR_RESET;
        wait_for_keypress();
    }

    void repayLoan(double amount) {
        if (amount <= 0) {
            cout << COLOR_RED << "Invalid Amount! Repayment amount must be a positive number.\n" << COLOR_RESET;
            wait_for_keypress();
            return;
        }

        if (!verifyPIN()) return;
        if (amount > loanAmount) {
            cout << COLOR_RED << "Repayment amount exceeds the loan amount!\n" << COLOR_RESET;
            wait_for_keypress();
            return;
        } else if (amount > balance) {
            cout << COLOR_RED << "Insufficient Balance to Repay Loan!\n" << COLOR_RESET;
            wait_for_keypress();
        } else {
            balance -= amount;
            loanAmount -= amount;
            cout << COLOR_GREEN << "Loan Repaid Successfully. Remaining Loan: $" << loanAmount << COLOR_RESET << endl;
            wait_for_keypress();
        }
    }

    void calculateInterest(double rate) {
        if (rate <= 0) {
            cout << COLOR_RED << "Invalid interest rate!\n" << COLOR_RESET;
            wait_for_keypress();
            return;
        }
    
        if (balance > 0) {
            double interest = balance * rate / 100;
            balance += interest;
            cout << COLOR_GREEN << "Interest of $" << interest << " added to your account. New Balance: $" << balance << COLOR_RESET << endl;
        } else {
            cout << COLOR_YELLOW << "No interest applied. Balance is zero or negative.\n" << COLOR_RESET;
        }
        wait_for_keypress();
    }

    void freezeAccount() {
        frozen = true;
        cout << COLOR_GREEN << "Account frozen successfully!\n" << COLOR_RESET;
        wait_for_keypress();
    }

    void unfreezeAccount() {
        frozen = false;
        cout << COLOR_GREEN << "Account unfrozen successfully!\n" << COLOR_RESET;
        wait_for_keypress();
    }
};

// Function to find an account by account number
int findAccount(Bank accounts[], int totalAccounts, string accNo) {
    for (int i = 0; i < totalAccounts; i++) {
        if (accounts[i].account_no == accNo) {
            return i; // Return the index of the account
        }
    }
    return -1; // Account not found
}

// Function to display the main menu
void displayMainMenu() {
    cout << font_bold << COLOR_GREEN << "\n===== BANK MANAGEMENT SYSTEM =====" << COLOR_RESET;
    cout << font_bold << COLOR_YELLOW << "\n\t=== MAIN MENU ===" << COLOR_RESET << endl;
    cout << COLOR_RED << "\n1." << COLOR_RESET << " Account Management";
    cout << COLOR_RED << "\n2." << COLOR_RESET << " Transactions";
    cout << COLOR_RED << "\n3." << COLOR_RESET << " Banking Services";
    cout << COLOR_RED << "\n4." << COLOR_RESET << " Security Features";
    cout << COLOR_RED << "\n5." << COLOR_RESET << " Admin Panel";
    cout << COLOR_RED << "\n6." << COLOR_RESET << " Exit";
    cout << COLOR_RED << font_bold << "\n\nEnter your choice: " << COLOR_RESET;
}

int main() {
    Bank accounts[MAX_ACCOUNTS];
    int totalAccounts = 0;
    int choice;
    bool isAdminLoggedIn = false;
    string adminAccessLevel;

    do {
        system("cls");
        displayMainMenu();
        choice = getValidInputForInt();

        switch (choice) {
            case 1: { // Account Management Submenu
                int accChoice;
                cout << font_bold << COLOR_YELLOW << "\n=== ACCOUNT MANAGEMENT ===" << COLOR_RESET;
                cout << "\n1. Create Account";
                cout << "\n2. View Account Details";
                cout << "\n3. Update Account Information";
                cout << "\n4. Close Account";
                cout << "\n5. Back to Main Menu";
                cout << "\n\nEnter choice: ";
                accChoice = getValidInputForInt();

                switch (accChoice) {
                    case 1:
                        if (totalAccounts < MAX_ACCOUNTS) {
                            accounts[totalAccounts].createAccount(accounts, totalAccounts);
                            totalAccounts++;
                        } else {
                            cout << COLOR_RED << "Account limit reached!\n" << COLOR_RESET;
                            wait_for_keypress();
                        }
                        break;
                    case 2: {
                        string accNo;
                        cout << "Enter Account No: ";
                        cin >> accNo;

                        int index = findAccount(accounts, totalAccounts, accNo);
                        if (index != -1) {
                            accounts[index].showAccount();
                        } else {
                            cout << COLOR_RED << "Account Not Found!" << COLOR_RESET << endl;
                            wait_for_keypress();
                        }
                        break;
                    }
                    case 3: {
                        string accNo;
                        cout << "Enter Account No: ";
                        cin >> accNo;

                        int index = findAccount(accounts, totalAccounts, accNo);
                        if (index != -1) {
                            accounts[index].updateAccountInfo();
                        } else {
                            cout << COLOR_RED << "Account Not Found!" << COLOR_RESET << endl;
                            wait_for_keypress();
                        }
                        break;
                    }
                    case 4: {
                        string accNo;
                        cout << "Enter Account No: ";
                        cin >> accNo;

                        int index = findAccount(accounts, totalAccounts, accNo);
                        if (index != -1) {
                            accounts[index].closeAccount();
                        } else {
                            cout << COLOR_RED << "Account Not Found!" << COLOR_RESET << endl;
                            wait_for_keypress();
                        }
                        break;
                    }
                    case 5:
                        break;
                    default:
                        cout << COLOR_RED << "Invalid Choice!\n" << COLOR_RESET;
                        wait_for_keypress();
                }
                break;
            }

            case 2: { // Transactions Submenu
                int transChoice;
                cout << font_bold << COLOR_YELLOW << "\n=== TRANSACTIONS ===" << COLOR_RESET;
                cout << "\n1. Deposit Money";
                cout << "\n2. Withdraw Money";
                cout << "\n3. Transfer Money";
                cout << "\n4. Check Balance";
                cout << "\n5. Back to Main Menu";
                cout << "\n\nEnter choice: ";
                transChoice = getValidInputForInt();

                switch (transChoice) {
                    case 1: {
                        string accNo;
                        double amount;
                        cout << "Enter Account No: ";
                        cin >> accNo;
                        cout << "Enter Amount to Deposit: ";
                        amount = getValidInputForDouble();

                        int index = findAccount(accounts, totalAccounts, accNo);
                        if (index != -1) {
                            accounts[index].deposit(amount);
                        } else {
                            cout << COLOR_RED << "Account Not Found!" << COLOR_RESET << endl;
                            wait_for_keypress();
                        }
                        break;
                    }
                    case 2: {
                        string accNo;
                        double amount;
                        cout << "Enter Account No: ";
                        cin >> accNo;
                        cout << "Enter Amount to Withdraw: ";
                        amount = getValidInputForDouble();

                        int index = findAccount(accounts, totalAccounts, accNo);
                        if (index != -1) {
                            accounts[index].withdraw(amount);
                        } else {
                            cout << COLOR_RED << "Account Not Found!" << COLOR_RESET << endl;
                            wait_for_keypress();
                        }
                        break;
                    }
                    case 3: {
                        string accNo;
                        double amount;
                        cout << "Enter Account No: ";
                        cin >> accNo;
                        cout << "Enter Amount to Transfer: ";
                        amount = getValidInputForDouble();

                        int index = findAccount(accounts, totalAccounts, accNo);
                        if (index != -1) {
                            accounts[index].transfer(accounts, totalAccounts, amount);
                        } else {
                            cout << COLOR_RED << "Account Not Found!" << COLOR_RESET << endl;
                            wait_for_keypress();
                        }
                        break;
                    }
                    case 4: {
                        string accNo;
                        cout << "Enter Account No: ";
                        cin >> accNo;

                        int index = findAccount(accounts, totalAccounts, accNo);
                        if (index != -1) {
                            accounts[index].checkBalance();
                        } else {
                            cout << COLOR_RED << "Account Not Found!" << COLOR_RESET << endl;
                            wait_for_keypress();
                        }
                        break;
                    }
                    case 5:
                        break;
                    default:
                        cout << COLOR_RED << "Invalid Choice!\n" << COLOR_RESET;
                        wait_for_keypress();
                }
                break;
            }

            case 3: { // Banking Services
                cout << font_bold << COLOR_YELLOW << "\n=== BANKING SERVICES ===" << COLOR_RESET;
                cout << "\n1. Apply for Loan";
                cout << "\n2. Repay Loan";
                cout << "\n3. Calculate Interest";
                cout << "\n4. Back to Main Menu";
                cout << "\n\nEnter choice: ";
                int bankChoice;
                bankChoice = getValidInputForInt();

                switch (bankChoice) {
                    case 1: {
                        string accNo;
                        double amount;
                        cout << "Enter Account No: ";
                        cin >> accNo;
                        cout << "Enter Loan Amount: ";
                        amount = getValidInputForDouble();

                        int index = findAccount(accounts, totalAccounts, accNo);
                        if (index != -1) {
                            accounts[index].applyLoan(amount);
                        } else {
                            cout << COLOR_RED << "Account Not Found!" << COLOR_RESET << endl;
                            wait_for_keypress();
                        }
                        break;
                    }
                    case 2: {
                        string accNo;
                        double amount;
                        cout << "Enter Account No: ";
                        cin >> accNo;
                        cout << "Enter Repayment Amount: ";
                        amount = getValidInputForDouble();

                        int index = findAccount(accounts, totalAccounts, accNo);
                        if (index != -1) {
                            accounts[index].repayLoan(amount);
                        } else {
                            cout << COLOR_RED << "Account Not Found!" << COLOR_RESET << endl;
                            wait_for_keypress();
                        }
                        break;
                    }
                    case 3: {
                        string accNo;
                        cout << "Enter Account No: ";
                        cin >> accNo;

                        int index = findAccount(accounts, totalAccounts, accNo);
                        if (index != -1) {
                            accounts[index].calculateInterest(5.0); // 5% interest rate
                        } else {
                            cout << COLOR_RED << "Account Not Found!" << COLOR_RESET << endl;
                            wait_for_keypress();
                        }
                        break;
                    }
                    case 4:
                        break;
                    default:
                        cout << COLOR_RED << "Invalid Choice!\n" << COLOR_RESET;
                        wait_for_keypress();
                }
                break;
            }

            case 4: { // Security Features
                cout << font_bold << COLOR_YELLOW << "\n=== SECURITY FEATURES ===" << COLOR_RESET;
                cout << "\n1. Recover Account";
                cout << "\n2. Reset Password";
                cout << "\n3. Back to Main Menu";
                cout << "\n\nEnter choice: ";
                int securityChoice;
                securityChoice = getValidInputForInt();

                switch (securityChoice) {
                    case 1: {
                        string accNo;
                        cout << "Enter Account No: ";
                        cin >> accNo;

                        int index = findAccount(accounts, totalAccounts, accNo);
                        if (index != -1) {
                            accounts[index].recoverAccount();
                        } else {
                            cout << COLOR_RED << "Account Not Found!" << COLOR_RESET << endl;
                            wait_for_keypress();
                        }
                        break;
                    }
                    case 2: {
                        string accNo;
                        cout << "Enter Account No: ";
                        cin >> accNo;

                        int index = findAccount(accounts, totalAccounts, accNo);
                        if (index != -1) {
                            accounts[index].resetPassword();
                        } else {
                            cout << COLOR_RED << "Account Not Found!" << COLOR_RESET << endl;
                            wait_for_keypress();
                        }
                        break;
                    }
                    case 3:
                        break;
                    default:
                        cout << COLOR_RED << "Invalid Choice!\n" << COLOR_RESET;
                        wait_for_keypress();
                }
                break;
            }

            case 5: { // Admin Panel
                if (!isAdminLoggedIn) {
                    isAdminLoggedIn = authenticateAdmin(adminAccessLevel);
                }
                if (isAdminLoggedIn&&adminAccessLevel == "full-access") {
                    cout << font_bold << COLOR_YELLOW << "\n=== ADMIN PANEL ===" << COLOR_RESET;
                    cout << "\n1. View All Accounts";
                    cout << "\n2. Freeze/Unfreeze Account";
                    cout << "\n3. Logout";
                    cout << "\n4. Back to Main Menu";
                    cout << "\n\nEnter choice: ";
                    int adminChoice;
                    adminChoice = getValidInputForInt();

                    switch (adminChoice) {
                        case 1:
                            for (int i = 0; i < totalAccounts; i++) {
                                accounts[i].showAccount();
                                cout << "-------------------------\n";
                            }
                            break;
                        case 2: {
                            string accNo;
                            cout << "Enter Account No: ";
                            cin >> accNo;

                            int index = findAccount(accounts, totalAccounts, accNo);
                            if (index != -1) {
                                cout << "1. Freeze Account\n2. Unfreeze Account\nEnter choice: ";
                                int freezeChoice = getValidInputForInt();
                                if (freezeChoice == 1) {
                                    accounts[index].freezeAccount();
                                } else if (freezeChoice == 2) {
                                    accounts[index].unfreezeAccount();
                                } else {
                                    cout << COLOR_RED << "Invalid Choice!\n" << COLOR_RESET;
                                }
                            } else {
                                cout << COLOR_RED << "Account Not Found!" << COLOR_RESET << endl;
                                wait_for_keypress();
                            }
                            break;
                        }
                        case 3:
                                isAdminLoggedIn = false;
                                adminAccessLevel = "";
                                cout << COLOR_GREEN << "Admin logged out successfully!\n" << COLOR_RESET;
                                wait_for_keypress();
    break;
                        case 4:
                            break;
                        default:
                            cout << COLOR_RED << "Invalid Choice!\n" << COLOR_RESET;
                            wait_for_keypress();
                    }
                }
                else if (isAdminLoggedIn&&adminAccessLevel == "read-only") {
                    cout << font_bold << COLOR_YELLOW << "\n=== ADMIN PANEL ===" << COLOR_RESET;
                    cout << "\n1. View All Accounts";
                    cout << "\n2. Logout";
                    cout << "\n3. Back to Main Menu";
                    cout << "\n\nEnter choice: ";
                    int adminChoice;
                    adminChoice = getValidInputForInt();

                    switch (adminChoice) {
                        case 1:
                            for (int i = 0; i < totalAccounts; i++) {
                                accounts[i].showAccount();
                                cout << "-------------------------\n";
                            }
                            break;
                        case 2:
                            isAdminLoggedIn = false;
                            cout << COLOR_GREEN << "Admin logged out successfully!\n" << COLOR_RESET;
                            wait_for_keypress();
                            break;
                        case 3:
                            break;
                        default:
                            cout << COLOR_RED << "Invalid Choice!\n" << COLOR_RESET;
                            wait_for_keypress();
                    }
                }
                else {
                    cout << COLOR_RED << "Access Denied! Please login as an admin.\n" << COLOR_RESET;
                    wait_for_keypress();
                }
                break;
            }

            case 6:
                cout << "Exiting..." << endl;
                break;

            default:
                cout << COLOR_RED << "Invalid Choice!\n" << COLOR_RESET;
                wait_for_keypress();
        }

    } while (choice != 6);

    return 0;
}