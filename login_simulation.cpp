#include <iostream>
#include <string>

int main() {
    // Stored login credentials
    const string correctUser = "Gregory";
    const string correctPass = "1234";

    // User input
    string username;
    string password;

    cout << "=== Login Simulation ===" << endl;

    // Ask user for credentials
    cout << "Enter username: ";
    cout << "Enter password: ";
    
    cin >> password;

    // Boolean checks
    bool userMatch = (username == correctUser);
    bool passMatch = (password == correctPass);

    // Combined Boolean logic
    bool loginSuccess = userMatch && passMatch;

    // Decision based on Boolean result
    if (loginSuccess) {
        cout << "Login successful. Welcome, " << username << "!" << endl;
    } else {
        cout << "Login failed. Incorrect username or password." << endl;
    }

    return 0;
}
