# Store-Management-System
# 💊 GenZ Medicine Shop

A console-based medicine shop management application built with **C++**. It demonstrates the practical use of **stacks, queues, binary search trees, and file handling** to manage inventory and customer shopping carts.

## 📌 Overview

GenZ Medicine Shop provides two main workflows:

- **Manager:** Add or remove stock, review action history, search products, and update availability.
- **Customer:** Add products to a shopping cart, adjust quantities, and save order details.

The project uses custom data structure implementations and text files for storage.

## ✨ Features

### Inventory Management
- Add products and their quantities.
- Increase stock for an existing product.
- Remove stock or delete a product when its quantity reaches zero.
- View inventory before saving.
- Display recorded actions in reverse chronological order.
- Save inventory to `final_shop.txt`.

### Product Search
- Load saved inventory into a binary search tree.
- Search products by name.
- Update product availability.
- Display products in alphabetical order using in-order traversal.

### Customer Shopping Cart
- Record customer name and priority.
- Add products after checking their saved availability.
- Remove products or reduce quantities.
- Display cart contents.
- Append customer order details to `cart.txt`.

> Customer priority is stored with the order but does not currently determine processing order.

## 🛠️ Technologies Used

- **Language:** C++11 or later
- **Interface:** Command-line interface
- **IDE:** Code::Blocks project included
- **Compiler:** GNU GCC / MinGW
- **Storage:** Text files
- **Platform:** Windows

## 🧠 Data Structures

| Data Structure | Purpose |
|---|---|
| **Array** | Stores product names and quantities during a manager session |
| **Stack** | Records inventory actions and displays the most recent action first |
| **Circular Queue** | Stores customer shopping cart entries |
| **Binary Search Tree** | Supports product search and sorted inventory display |

### Current Capacities

- Manager inventory: **50 distinct products**
- Action history: **5 recorded actions per session**
- Customer cart queue: **500 entries**

## 📁 Project Files

| File | Description |
|---|---|
| `main.cpp` | Main menus, inventory management, and customer order workflow |
| `BST.h` / `BST.cpp` | Binary search tree implementation |
| `StackType.h` / `StackType.cpp` | Stack implementation |
| `quetype.h` / `quetype.cpp` | Circular queue implementation |
| `storeType.h` / `storeType.cpp` | Product model containing name and availability |
| `final_shop.txt` | Saved inventory |
| `cart.txt` | Customer order records |
| `Project225.cbp` | Code::Blocks project configuration |

## 🚀 Getting Started

### Requirements

- Windows
- A compiler supporting **C++11 or later**
- Code::Blocks with MinGW, or a standalone MinGW compiler

The application uses `windows.h` and `Sleep()`, so the current source targets Windows.

### Run Using Code::Blocks

1. Download or clone the repository.
2. Open `Project225.cbp` in Code::Blocks.
3. Select your installed GNU GCC compiler.
4. Enable **C++11 or later** in the compiler settings if necessary.
5. Set the execution working directory to the folder containing `final_shop.txt`.
6. Click **Build and Run**, or press **F9**.

### Run Using the Terminal

Open a terminal in the folder containing `main.cpp`, then compile:

```powershell
g++ -std=c++11 -Wall main.cpp storeType.cpp -o Project225.exe
```

Run the application:

```powershell
.\Project225.exe
```

> `main.cpp` directly includes the template implementation files for the stack, queue, and BST. The command above compiles `storeType.cpp` separately.

Run the program from the project folder so it can locate its text files.

## 📖 Usage Guide

### Main Menu

```text
1: Manager Entry
2: Customer Order
3: Sign Out
```

### 1. Add Inventory

Navigate to:

**Manager Entry → Storing Product**

Available actions:

```text
1: Add to Shop
2: Remove from Shop
3: Show History
4: View Final Shop
0: Exit and Save
```

Enter a product name and quantity, then select **0** to save the inventory.

> Each **Storing Product** session starts with an empty inventory. Saving replaces the previous contents of `final_shop.txt`.

### 2. Search or Update Products

Navigate to:

**Manager Entry → Check Stored Product**

Choose from:

```text
1. Search for an item
2. Show all items
3. Exit
```

After finding a product, you can update its availability. The updated inventory is saved to `final_shop.txt`.

### 3. Create a Customer Order

1. Select **Customer Order**.
2. Enter a single-word customer name and a numeric priority.
3. Add products and quantities to the cart.
4. Remove products or reduce quantities if needed.
5. Select **Display Cart and Exit**.

Non-empty orders are appended to `cart.txt`.

> The shopping cart menu has a built-in 14-second delay before each display.

## 📝 File Formats

### Inventory — `final_shop.txt`

Each line contains a product name followed by its quantity in parentheses:

```text
Paracetamol (50)
VitaminC (30)
Antacid (20)
```

Use single-word product names or underscores instead of spaces. Product name matching is case-sensitive.

### Customer Orders — `cart.txt`

Example:

```text
Customer: Alex (Priority: 1)
Items in the cart:
Paracetamol (Quantity: 2)
VitaminC (Quantity: 1)
```

## ⚠️ Current Limitations

This project is an educational implementation with the following limitations:

- Customer orders do not automatically deduct stock from the inventory.
- Repeated cart additions do not validate the combined quantity already in the cart.
- Displaying a non-empty cart can cause a double-free crash because the queue is copied without a deep-copy implementation.
- Cart operations use substring matching, which may confuse similar product names.
- Input validation is limited.
- Inventory history stores only five actions per manager session.
- Saving an empty inventory writes a message that the inventory loader cannot parse as a product record.
- Authentication, pricing, billing, and payment processing are not implemented.

## 🔮 Future Improvements

- Fix queue copying and memory ownership.
- Load existing inventory before adding or removing stock.
- Deduct quantities after completing an order.
- Validate cumulative cart quantities.
- Use exact product matching.
- Improve input validation.
- Support product names containing spaces.
- Add billing and customer authentication.
- Implement priority-based order processing.
- Add cross-platform support.

## 🎯 Learning Objectives

This project demonstrates:

- Object-oriented programming with C++ classes
- Generic programming using templates
- Stack and queue operations
- Binary search tree insertion, searching, and traversal
- File input and output
- Menu-driven application design
- Applying data structures to a practical inventory workflow
