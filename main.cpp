#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <windows.h>
#include <sstream>
#include <chrono>
#include <ctime>

using namespace std;

void clearScreen()
{
    system("cls");
}

vector<string> dataArray;
vector<string> cartData;
vector<string> receiptsArray;

class BasicFunctionality
{
public:
    // Code Below reads the file
    void readFile(const string &filename)
    {
        ifstream inputFile(filename);
        if (!inputFile)
        {
            cout << "Failed to open the file." << endl;
            return;
        }

        string line;
        while (getline(inputFile, line))
        {
            dataArray.push_back(line);
        }

        inputFile.close();
    }

    // Code Below will login the user using the data in the users.txt file
    bool login(const string &username, const string &password)
    {
        ifstream usersFile("users.txt");

        if (!usersFile)
        {
            cout << "Failed to open the users file." << endl;
            return false;
        }

        string line; // Sameer:abc
        // This if condition will check line by line if the user exists
        // When ever a user is found it will return true and login process completes
        while (getline(usersFile, line))
        {
            if (line == username + ":" + password) // Sameer:abc
            {
                usersFile.close();
                return true;
            }
        }

        // Incase no user is found then false is returned

        usersFile.close();
        return false; // Login failed
    }

    // Code below creates a user and saves the data inside the users.txt file
    bool signup(const string &username, const string &password)
    {

        ofstream usersFile("users.txt", ios::app);
        if (!usersFile)
        {
            cout << "Failed to open the users file." << endl;
            return false;
        }

        readFile("users.txt");
        // Check if username already exists
        for (const auto &data : dataArray)
        {

            // Fahad:1233

            if (data.substr(0, data.find(':')) == username)
            {
                cout << "Username already exists." << endl;
                usersFile.close();
                return false;
            }
        }

        // if no username exists then add a new user
        usersFile << username << ":" << password << endl;
        usersFile.close();
        return true;
    }
};

class cartFunctions
{

public:
    // Function to open the file and save its data in the cartData vector
    void openFile(const string &username)
    {
        ifstream file("carts/" + username + ".txt"); // Opening the file with .txt extension
        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                cartData.push_back(line); // Saving each line in the vector
            }
            file.close();
        }
    }

    // Function to add item to cart
    void addItem(const string &username)
    {
        cout << "\n\nHow many items do you want to add in cart = ";

        int qty;

        cin >> qty;

        for (int i = 1; i <= qty; i++)
        {
            string index;
            string quantity;

            cout << "Enter Product index number = ";
            cin >> index;
            cout << "Enter Quantity = ";
            cin >> quantity;

            fstream outputFile(("carts/" + username + ".txt"), ios::app);

            for (const auto &element : dataArray)
            {
                string firstFourDigits = element.substr(0, element.find(":"));

                if (firstFourDigits == index)
                {
                    outputFile << element << ":" << quantity << endl;
                }
                else
                {
                    cout << "Item doesnt exists";
                }
            }
        }
    }

    // Function to return the length of the cartData vector
    int getCartDataLength() const
    {
        return cartData.size();
    }
};

string dateGenerator()
{
    auto now = std::chrono::system_clock::now();

    // Convert system time to time_t
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    // Convert time_t to tm struct for local time
    std::tm *localTime = std::localtime(&currentTime);

    // Extract date components
    int year = localTime->tm_year + 1900; // years since 1900
    int month = localTime->tm_mon + 1;    // months since January [0, 11]
    int day = localTime->tm_mday;         // day of the month [1, 31]

    // Print current date
    string s = to_string(year) + ":" + to_string(month) + ":" + to_string(day);

    return s;
}

class RenderUI
{
public:
    void initialPage(const string &username)
    {
        clearScreen();

        cartFunctions cartManager;
        cartManager.openFile(username);

        int choice;

        cout << "\n\n\t\t\t|------WELCOME TO BEE-SHOP------|\n\n";
        cout << "Hi! "
             << username << endl;
        cout << "You have " << cartManager.getCartDataLength() << " items in cart\n\n";

        cout << "What to do (Choose a option from below)\n";
        cout << "1. View Products\n";
        cout << "2. View your Cart\n";
        cout << "3. View your Previous Receipts\n";
        cout << "To exit Enter any number except 1,2,3\n\n";
        cout << "Enter Your choice = ";

        cin >> choice;

        switch (choice)
        {
        case 1:
            productPage(username);

        case 2:
            cartPage(username);

        case 3:
            receiptsPage(username);

        default:
            break;
        }
    }

    void productPage(const string &username)
    {

        clearScreen();

        cartFunctions cartManager;
        cartManager.openFile(username);

        int choice;

        cout << "Hi! \n"
             << username;
        cout << "\n\n\t\t\t|------WELCOME TO BEE-SHOP------|\n\n";
        cout << "You have" << cartManager.getCartDataLength() << "items in cart\n\n";

        cout << "What do you want to buy today\n";

        BasicFunctionality reader;
        reader.readFile("items.txt");

        // Before we print the items to console first we want to separate all data by colons in them
        // This could be done by iterating overall the items and then splitting it

        cout << "Index"
             << "\t"
             << "Category"
             << "\t\t\t\t"
             << "Name"
             << "\t\t\t"
             << "Price"
             << endl;

        for (const string &line : dataArray)
        {
            stringstream ss(line);
            string token;
            vector<string> tokenArr; // [0001, name, pri.....]

            // Split the line by ":"
            while (getline(ss, token, ':'))
            {
                tokenArr.push_back(token);
            }

            // Print the 1st, 2nd, and last element
            cout << tokenArr[0] << "\t" << tokenArr.back() << "\t\t\t\t" << tokenArr[1] << "\t\t\t" << tokenArr[2] << endl;
        }

        cout << "\n\n\nWhat to do (Choose a option from below)\n";
        cout << "1. Add items to cart\n";
        cout << "2. Return to main menu\n";
        cout << "To exit Enter any number except 1,2,3\n\n";
        cout << "Enter Your choice = ";

        cin >> choice;

        switch (choice)
        {
        case 1:
            cartManager.addItem(username);
        case 2:
            initialPage(username);

        default:
            break;
        }
    }

    void cartPage(const string &username)
    {
        clearScreen();
        cout << "\n\n\t\t\t|------BEE-SHOP------|\n\n";

        cout << "Your Cart items are listed below\n\n";

        cartFunctions cart;

        cart.openFile(username);

        int totalCost = 0.0;

        cout << "Name"
             << "\t\t"
             << "Price"
             << "\t\t"
             << "Quantity"
             << "\t\t"
             << "Total Price"
             << "\t\t" << endl;

        for (const string &line : cartData)
        {
            stringstream ss(line);
            string token;
            vector<string> tokens;

            // Split the line by ":"
            while (getline(ss, token, ':'))
            {
                tokens.push_back(token);
            }

            cout << tokens[1] << "\t\t" << tokens[2] << "\t\t" << tokens.back() << "\t\t" << (stoi(tokens[2].substr(1)) * stoi(tokens.back())) << endl;

            totalCost = totalCost + (stoi(tokens[2].substr(1)) * stoi(tokens.back()));
        }

        cout << "\n\n\nTotal cost = $" << totalCost;

        int choice;

        cout << "\n\n\nWhat to do (Choose a option from below)\n";
        cout << "1. Pay the Bill\n";
        cout << "2. Return to main menu\n";
        cout << "To exit Enter any number except 1,2,3\n\n";
        cout << "Enter Your choice = ";

        cin >> choice;

        switch (choice)
        {
        case 1:
            billingPage(username, totalCost);
        case 2:
            initialPage(username);

        default:
            break;
        }
    }

    void billingPage(const string &username, const int &totalcost)
    {
        clearScreen();
        cout << "\n\n\t\t\t|------BEE-SHOP------|\n\n";
        cout << "\nThankyou for shopping";
        cout << "Here is your Total Bill = $" << totalcost;

        fstream outputFile(("bills/" + username + ".txt"), ios::app);

        outputFile << dateGenerator << "\t" << totalcost;

        cout << "\n\n\nWhat to do (Choose a option from below)\n";
        cout << "1. Return to main menu\n";
        cout << "To exit Enter any number except 1,2,3\n\n";
        cout << "Enter Your choice = ";

        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
            initialPage(username);

        default:
            break;
        }
    }

    void receiptsPage(const string &username)
    {
        clearScreen();

        fstream outputFile(("bills/" + username + ".txt"), ios::app);

        ifstream inputFile("bills/" + username + ".txt");

        string line;
        while (getline(inputFile, line))
        {
            receiptsArray.push_back(line);
        }

        for (const auto &data : receiptsArray)
        {
            cout << data << endl;
        }

        inputFile.close();

        cout << "\n\n\nWhat to do (Choose a option from below)\n";
        cout << "1. Return to main menu\n";
        cout << "To exit Enter any number except 1,2,3\n\n";
        cout << "Enter Your choice = ";

        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
            initialPage(username);

        default:
            break;
        }
    }
};

int main()
{

    BasicFunctionality reader;

    bool authenticated = false;

    while (!authenticated)
    {
        clearScreen();

        int choice;
        cout << "\t\t|------WELCOME TO BEE-SHOP------|\n";
        cout << "Before we continue please chose a option from below\n";
        cout << "1. Login\n";
        cout << "2. Signup\n";
        cout << "3. Exit\n";
        cout << "\nWhat to do Enter option = ";
        cin >> choice;

        string username, password;

        switch (choice)

        {
        case 1:
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;

            authenticated = reader.login(username, password);
            break;

        case 2:
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;

            authenticated = reader.signup(username, password);
            break;

        case 3:
            cout << "Exiting";
            break;

        default:
            cout << "Invalid Choice try again until then good bye";

            break;
        }

        if (authenticated)
        {
            clearScreen();
            cout << "Logged in successfuly\n";

            RenderUI renderer;

            renderer.initialPage(username);
        }
        else
        {
            cout << "Login failed. Would you like to try again? (Y/N): ";
            char choice;
            cin >> choice;
            if (choice != 'Y' && choice != 'y')
            {
                cout << "Exiting..." << endl;
                break;
            }
        }
    }
}