# Store-Management-System
GenZ Medicine Shop
A menu-driven medicine shop management application built with C++. The project demonstrates how stacks, queues, binary search trees, and file handling can support inventory management and customer shopping carts.
Features
Inventory management
- Add products and their quantities to the shop.
- Increase the quantity of an existing product or remove stock.
- View the current inventory before saving.
- Display recorded stock actions in reverse chronological order using a stack.
- Save inventory to final_shop.txt.
Inventory search
- Load saved products into a binary search tree (BST).
- Search for a product by its name.
- Update a product's availability and save the change.
- Display products in name order using in-order traversal.
Customer orders
- Record a customer's name and a numeric priority value.
- Add products to a queue-based shopping cart after checking the saved quantity.
- Remove an item or reduce its quantity in the cart.
- Display the cart and append the order details to cart.txt.
Customer priority is recorded with the order; it does not control order processing or sorting.

Technologies and Data Structures
Component	Purpose
C++11 or later	Application logic, classes, and templates
Arrays	Store up to 50 distinct products in the manager's inventory session
Stack	Store up to 5 inventory action records, displayed most recent first
Circular queue	Store customer cart entries in insertion order; default capacity is 500
Binary search tree	Search products and display saved inventory in name order
Text files	Store inventory and append customer order records
Windows API	Provide timed pauses through Sleep()
Code::Blocks	Included IDE project configuration


Project Files
File	Description
main.cpp	Main menus, inventory operations, and customer order workflow
BST.h, BST.cpp	Template-based binary search tree implementation
StackType.h, StackType.cpp	Fixed-capacity stack implementation
quetype.h, quetype.cpp	Circular queue implementation
storeType.h, storeType.cpp	Product name and availability model
final_shop.txt	Saved product quantities
cart.txt	Appended customer order records
Project225.cbp	Code::Blocks project file


Getting Started
Requirements
- Windows, because the source includes windows.h and uses Sleep().
- A C++ compiler supporting C++11 or later, such as MinGW GCC.
- Code::Blocks is optional.
Download or clone this repository, then open the folder containing main.cpp and Project225.cbp. If the repository contains a nested Project225 folder, use that folder for the following steps.
Option 1: Code::Blocks
1. Open Project225.cbp.
2. Select the GNU GCC compiler installed on your computer.
3. Enable C++11 or later in the project's compiler settings if necessary.
4. Set the execution working directory to the project folder containing the text files.
5. Select Build and Run (F9).
Option 2: Windows Terminal
With MinGW's g++ available on your PATH, run these commands from the project folder:
g++ -std=c++11 -Wall main.cpp storeType.cpp -o Project225.exe
.\Project225.exe
main.cpp directly includes BST.cpp, StackType.cpp, and quetype.cpp to make their template implementations available. The command above compiles storeType.cpp separately.
Keep the working directory set to the project folder: the application reads and writes its text files using relative paths.
How to Use
The main menu provides three options:
1: Manager Entry
2: Customer Order
3: Sign Out
Set up inventory
1. Choose Manager Entry → Storing Product.
2. Choose Add to Shop, then enter a product name and quantity.
3. Repeat for additional products.
4. Use Show History or View Final Shop to review the session.
5. Choose 0: Exit and Save to write the inventory file.
Each Storing Product session starts with an empty inventory. Saving replaces final_shop.txt; it does not load and extend the previous inventory. To change an existing saved product's quantity, use Check Stored Product → Search for an item instead.
Search saved products
Choose Manager Entry → Check Stored Product. Search by the exact product name, optionally update its availability, or select Show all items.
Create a customer order
1. Choose Customer Order.
2. Enter a single-word customer name and a numeric priority.
3. Add products using their saved names and positive quantities.
4. Remove products or reduce quantities as needed.
5. Choose Display Cart and Exit to display the order and append it to cart.txt.
The shopping cart menu includes a 14-second pause before each display.
Data Format
final_shop.txt stores one product per line:
Paracetamol (50)
VitaminC (30)
Antacid (20)
Use single-word product names, or underscores instead of spaces, because the inventory loader reads names as a single token. Name matching is case-sensitive.
An example order entry in cart.txt is:
Customer: Alex (Priority: 1)
Items in the cart:
Paracetamol (Quantity: 2)
VitaminC (Quantity: 1)
Current Limitations
This is an educational data structures project. The current implementation has several limitations:
- Customer orders do not deduct quantities from the saved inventory, and repeated cart additions are not checked against the combined quantity already in the cart.
- Cart display copies the queue without a deep-copy implementation. This can cause a double-free crash after displaying a non-empty cart.
- Cart matching uses substring searches, so similar product names can match unexpectedly.
- Input validation is limited; use valid menu numbers and positive quantities.
- The history stack records only five actions per manager session; additional actions can change stock without being recorded.
- Saving an empty inventory writes Shop is empty., which the inventory loader cannot parse as a product record.
- There is no login authentication, pricing, billing, payment processing, or database integration.
Possible Improvements
- Implement safe queue copying or display the cart without copying its owned storage.
- Load existing stock before starting a manager inventory session.
- Deduct purchased quantities and validate cumulative cart quantities.
- Add exact product matching and stronger input validation.
- Support product names containing spaces.
- Add billing, authentication, and actual priority-based order processing.
- Replace Windows-specific calls for cross-platform support.
