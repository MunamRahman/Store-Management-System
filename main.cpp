#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "StackType.cpp"
#include "quetype.cpp"
#include "BST.cpp"
#include "storeType.h"
#include <queue>
#include <tuple>
#include <cstdlib>
#include <windows.h>


using namespace std;

const int SHOP_CAPACITY = 50;
const string FINAL_SHOP_FILE = "final_shop.txt";

void clearScreen();
void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}




class Storeditem
{

    void readItemsFromFile(const string& filename, BST<storeItem>& inventory)
    {
        ifstream file(filename);
        if (!file.is_open())
        {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string name;
            char openBracket, closeBracket;
            int availability;

            ss >> name >> openBracket >> availability >> closeBracket;
            if (ss.fail() || openBracket != '(' || closeBracket != ')')
            {
                cerr << "Error parsing line: " << line << endl;
                continue;
            }

            storeItem item(name, availability);
            inventory.InsertItem(item);
        }

        file.close();
    }


    void displayMenu(BST<storeItem>& inventory)
    {
        string choice;
        string itemName;

        do
        {
            cout << "\nMenu:\n";
            cout << "1. Search for an item\n";
            cout << "2. Show all items\n";
            cout << "3. Exit\n";
            cout << "Enter your choice: ";

            cin.clear();
            cin >> choice;

            if (choice == "1")
            {
                clearScreen();
                cout << "Enter the name of the item to search for: ";
                cin >> itemName;
                inventory.SearchItem(itemName);
            }
            else if (choice == "2")
            {
                clearScreen();
                inventory.PrintInventory();
            }
            else if (choice == "3")
            {

                cout << "Exiting program.\n";
                Sleep(2000);
                clearScreen();

            }
            else
            {
                cout << "Invalid choice. Please try again.\n";
            }
        }
        while (choice != "3");
    }

public :
    void bstMain(BST<storeItem>& inventory)
    {
        readItemsFromFile("final_shop.txt", inventory);
        displayMenu(inventory);
    }
};







class CustomerOrder
{
private:
    QueType<string> cart;
    string customerName, name ;
    int priority, pr;

public:
    CustomerOrder() {}

    void setCustomerInfo(const string& name, int pr)
    {
        customerName = name;
        priority = pr;
    }

    void displayMenu()
    {
        Sleep(14000);
        clearScreen();
        cout << "--------------------" << endl;
        cout << " Shopping Cart Menu " << endl;
        cout << "--------------------" << endl<<endl;
        cout << "1. Add item to cart" << endl;
        cout << "2. Remove item from cart" << endl;
        cout << "3. Display Cart and Exit" <<endl << endl ;
        cout << "Enter your choice: ";
    }

    void addItemToCart(const string& filePath)
    {
        string itemName;
        int quantity;

        cout << "Enter the item to add to the cart: ";
        getline(cin, itemName);
        cout << "Enter the quantity: ";
        cin >> quantity;

        ifstream inFile(filePath);
        if (!inFile)
        {
            cerr << "Error: Unable to open file for reading." << endl;
            return;
        }

        bool found = false;
        string line;
        while (getline(inFile, line))
        {
            if (line.find(itemName) != string::npos)
            {
                int pos = line.find('(');
                int endPos = line.find(')');
                if (pos != string::npos && endPos != string::npos)
                {
                    int availableQuantity = stoi(line.substr(pos + 1, endPos - pos - 1));
                    if (quantity <= availableQuantity)
                    {
                        found = true;
                        string item = itemName + " (Quantity: " + to_string(quantity) + ")";
                        cart.Enqueue(item);
                        cout << "Item added to the cart." << endl;
                    }
                    else
                    {
                        cout << "Sorry, the required quantity of " << itemName << " is not available." << endl;
                    }
                    break;
                }
            }
        }

        if (!found)
        {
            cout << "Sorry, " << itemName << " is not available." << endl;
        }

        inFile.close();
    }

    void removeItemFromCart()
    {
        if (cart.IsEmpty())
        {
            cout << "The cart is empty. Cannot remove items." << endl;
            return;
        }

        string itemToRemove;
        cout << "Enter the item to remove from the cart: ";
        getline(cin, itemToRemove);

        int removeQuantity;
        cout << "Enter the quantity to remove: ";
        cin >> removeQuantity;

        QueType<string> tempCart;
        string currentItem;
        bool itemFound = false;

        while (!cart.IsEmpty())
        {
            cart.Dequeue(currentItem);
            if (currentItem.find(itemToRemove) != string::npos && !itemFound)
            {
                itemFound = true;
                int pos = currentItem.find("(Quantity:");
                if (pos != string::npos)
                {
                    int currentQuantity = stoi(currentItem.substr(pos + 11));
                    currentQuantity -= removeQuantity;
                    if (currentQuantity <= 0)
                    {
                        continue;
                    }
                    else
                    {
                        currentItem = currentItem.substr(0, pos + 11) + to_string(currentQuantity) + ")";
                    }
                }
            }
            tempCart.Enqueue(currentItem);
        }

        if (!itemFound)
        {
            cout << "Item not found in the cart." << endl;
        }
        else
        {
            cout << "Removed " << removeQuantity << " of " << itemToRemove << " from the cart." << endl;
        }

        while (!tempCart.IsEmpty())
        {
            tempCart.Dequeue(currentItem);
            cart.Enqueue(currentItem);
        }
    }

    void displayCart(bool writeToFile = false)
    {
        if (cart.IsEmpty())
        {
            cout << "The cart is empty." << endl;
            return;
        }

        QueType<string> tempCart = cart;
        string item;
        ofstream outFile;

        if (writeToFile)
        {
            outFile.open("cart.txt", ios::app);
            if (!outFile)
            {
                cerr << "Unable to open file for writing." << endl;
                return;
            }
            outFile << "Customer: " << customerName << " (Priority: " << priority << ")" << endl;
            outFile << "Items in the cart:" << endl;
        }

        cout << endl << endl ;
        cout << "Customer: " << customerName << " (Priority: " << priority << ")" << endl;
        cout << "---------------------" << endl;
        cout << "Items in the cart:" << endl;
        cout << "---------------------" << endl << endl ;

        while (!tempCart.IsEmpty())
        {
            tempCart.Dequeue(item);
            cout << item << endl;
            if (writeToFile)
            {
                outFile << item << endl;
            }
        }

        Sleep(2000);

        if (writeToFile)
        {
            outFile << endl;
            outFile.close();
        }
    }



    void processOrder()
    {
        int choice;

        do
        {
            displayMenu();
            cin >> choice;
            cin.ignore();

            if (choice == 1)
            {
                addItemToCart("final_shop.txt");
            }
            else if (choice == 2)
            {
                removeItemFromCart();
            }
            else if (choice == 3)
            {
                displayCart(true);

                cout << endl;
                cout << "Thanks for using." << endl;
                cout << "Please proceed to the counter." << endl << endl;
            }
            else
            {
                cout << "Invalid choice, please try again." << endl;
            }
        }
        while (choice != 3);
    }


    void cstm ( )
    {
        CustomerOrder customer;

        string name;
        int pr;

        Sleep(1000);
        clearScreen();

        cout << "----------------------" << endl;
        cout << " Customer Infomation " << endl;
        cout << "----------------------" << endl<<endl;

        cout << "Enter name: ";
        cin >> name;

        cout << "Enter priority: ";
        cin >> pr;
        cout << endl;


        cin.ignore();

        customer.setCustomerInfo(name, pr);
        customer.processOrder();
    }
};







class ManagerEntry
{
private:
    StackType<string> historyStack;
    string shop[SHOP_CAPACITY];
    int quantities[SHOP_CAPACITY] = {0};
    int shopSize = 0;

public:
    void performAddAction(const string& itemName, int quantity)
    {
        int index = -1;
        for (int i = 0; i < shopSize; ++i)
        {
            if (shop[i] == itemName)
            {
                index = i;
                break;
            }
        }

        if (shopSize < SHOP_CAPACITY)
        {
            if (index != -1)
            {
                quantities[index] += quantity;
            }
            else
            {
                shop[shopSize] = itemName;
                quantities[shopSize] = quantity;
                shopSize++;
            }
            string action = "Added: " + itemName + " (" + to_string(quantity) + ")";
            try
            {
                historyStack.Push(action);
            }
            catch (FullStack&)
            {
                cout << "Error: History stack is full." << endl;
            }
        }
        else
        {
            cout << "Shop is full, cannot add more items." << endl;
        }
    }

    void performRemoveAction(const string& itemName, int quantity)
    {
        int index = -1;
        for (int i = 0; i < shopSize; ++i)
        {
            if (shop[i] == itemName)
            {
                index = i;
                break;
            }
        }

        if (index != -1 && quantities[index] >= quantity)
        {
            quantities[index] -= quantity;
            if (quantities[index] == 0)
            {
                for (int i = index; i < shopSize - 1; ++i)
                {
                    shop[i] = shop[i + 1];
                    quantities[i] = quantities[i + 1];
                }
                shopSize--;
            }
            string action = "Removed: " + itemName + " (" + to_string(quantity) + ")";
            try
            {
                historyStack.Push(action);
            }
            catch (FullStack&)
            {
                cout << "Error: History stack is full." << endl;
            }
        }
        else
        {
            cout << "Item not found in shop or insufficient quantity: " << itemName << endl;
        }
    }

    void showHistory()
    {
        StackType<string> tempStack = historyStack;
        cout << "----------------------------------------" << endl;
        cout << "User action history (most recent first):" << endl;
        cout << "----------------------------------------" << endl<<endl;
        while (!tempStack.IsEmpty())
        {
            try
            {
                string lastAction = tempStack.Top();
                cout << lastAction << endl<<endl;
                tempStack.Pop();
            }
            catch (EmptyStack&)
            {
                cout << "Error: History stack is empty." << endl;
            }
        }
    }

    void viewFinalShop()
    {
        if (shopSize == 0)
        {
            cout << "Shop is empty." << endl;
        }
        else
        {
            cout << "-----------------" << endl;
            cout << "Final shop items:" << endl;
            cout << "-----------------" << endl<<endl;
            for (int i = 0; i < shopSize; ++i)
            {
                cout << "Item " << i+1 <<endl;
                cout << "Name : " << shop[i] <<endl;
                cout << "Quantities : (" << quantities[i] << ")" << endl<<endl;
            }
        }
    }

    void save()
    {
        ofstream finalShopFile(FINAL_SHOP_FILE);
        if (finalShopFile.is_open())
        {
            if (shopSize == 0)
            {
                finalShopFile << "Shop is empty." << endl;
            }
            else
            {
                for (int i = 0; i < shopSize; ++i)
                {
                    finalShopFile << shop[i] << " (" << quantities[i] << ")" << endl;
                }
            }
            finalShopFile.close();
        }
        else
        {
            cout << "Unable to open final shop file." << endl;
        }
    }

    void action()
    {
        cout << "-----------------" << endl;
        cout << " Storing Product " << endl;
        cout << "-----------------" << endl<<endl;
        cout << "1: Add to Shop" << endl;
        cout << "2: Remove from Shop" << endl;
        cout << "3: Show History" << endl;
        cout << "4: View Final Shop" << endl;
        cout << "0: Exit and Save" << endl;
    }

    void menu()
    {
        string itemName;
        int actionChoice, quantity;

        action();
        while (true)
        {
            cout << "Choose action (0 to exit and save): ";
            cin >> actionChoice;

            if (actionChoice == 0) break;

            if (actionChoice == 3)
            {
                clearScreen();
                showHistory();
                action();
                continue;
            }

            if (actionChoice == 4)
            {
                clearScreen();
                viewFinalShop();
                action();
                continue;
            }


            cout << "Enter item name: ";
            cin.ignore();
            getline(cin, itemName);
            cout << "Enter quantity: ";
            cin >> quantity;
            cout <<endl<<endl;

            switch (actionChoice)
            {
            case 1:
                performAddAction(itemName, quantity);
                break;
            case 2:
                performRemoveAction(itemName, quantity);
                break;
            default:
                cout << "Invalid action choice!" << endl;
                continue;
            }
        }

        save();
        cout << "Exiting... Final shop contents saved to " << FINAL_SHOP_FILE << endl;
        Sleep(2000);
        clearScreen();

    }
};


int main()
{
    int choice;

    while (true)
    {
        cout << "---------------------------------------------------------------" << endl;
        cout << "           GenZ Medicine Shop" << endl;
        cout << "---------------------------------------------------------------" << endl;
        cout << "1: Manager Entry" << endl;
        cout << "2: Customer Order" << endl;
        cout << "3: Sign Out" << endl;
        cout << endl;
        cout << "Choose option: ";
        cin >> choice;

        if (choice == 3)
        {
            clearScreen();
            cout << "Signing out..." << endl;
            Sleep(2000);
            break;
        }
        else if (choice == 2)
        {
            CustomerOrder cst;
            cst.cstm();
        }
        else if (choice == 1)
        {
            clearScreen();
            int managerChoice;
            cout << "-----------------" << endl;
            cout << "  Manager Entry  " << endl;
            cout << "-----------------" << endl << endl;
            cout << "1: Storing Product" << endl;
            cout << "2: Check Stored Product" << endl;
            cout << "Choose option: ";
            cin >> managerChoice;

            if (managerChoice == 1)
            {
                clearScreen();
                ManagerEntry manager;
                manager.menu();
            }
            else if (managerChoice == 2)
            {
                clearScreen();
                BST<storeItem> inventory;
                Storeditem Bst;
                Bst.bstMain(inventory);
            }
            else
            {
                cout << "Invalid choice, please try again." << endl;
            }
        }
        else
        {
            cout << "Invalid choice, please try again." << endl;
        }
    }

    return 0;
}




