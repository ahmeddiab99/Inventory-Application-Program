/*
CSC-237 Project4 : Inventory Application Program 
Student : Ahmed Diab
Due Date : December 12, 2020.
Description :
    This program involves designing and creating a C++ program that read inventory items data from files, 
    then printing out this data sequentially to the user in a nice format. The program also allows the user to specify an item, 
    then add or remove units from this items. The Program also allows the user to create a new item and add it to the list, 
    and also allow the user to output all the data to a file whose name has been entered by the user.

*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "InventoryItem.h"

void helpMenu();
void inputFile(string inputFileName, std::ifstream& fp, int units, double cost, InventoryItem item[100], int &counter, int records);
void printFileData(int counter, InventoryItem item[100]);
void addParts(InventoryItem item[100]);
void removeParts(InventoryItem item[100]);
void addNewInventoryItem(int &counter, InventoryItem item[100]);
void outputFile(std::ofstream& myFile, string outputFileName, int counter, InventoryItem item[100]);

int main() {

	const int array_size = 100; 
	InventoryItem item[array_size]; // array of items.
    string inputFileName;   // name of the input file
    string outputFileName;  // name of the output file
    ifstream fp;
    ofstream myFile;
    string temp;
    int counter = 0; // counter that counts inside the input file.
    int records = 0; // holds how many records loaded from each file to the array.
    int units = 0;
    double cost = 0;
    char command;

    cout << "Command: ";
    cin >> command;

    // keep asking the user for a new command as long as the command he/she entered != q
    while (command != 'q') {
        
        switch (command) {

        case 'i':
        {
            // calling the function that inputs inventory data from a file.
            inputFile(inputFileName, fp, units, cost, item, counter, records);
        }
        

        case 'p':
        {
            // calling the function that prints inventory items list.
            printFileData(counter, item);
        }
        break;

        case 'a':
        {    
            // calling the function that add units to a specified item.
            addParts(item);
        }
        break;

        case 'r':
        {
            // calling the function that remove units from a specified item.
            removeParts(item);
        }
        break;

        case 'n':
        {
            // calling the function that create a new inventory item and add it to the array of items.
            addNewInventoryItem(counter, item);
        }
        break;

        case 'o':
        {
            // calling the function that output the inventory data to a file.
            outputFile(myFile, outputFileName, counter, item);
        }
        break;

        case 'h':
        {
            // calling function that prints the help menu.
            helpMenu();
        }
        break;



        default:
        {
            // if the user entered a wrong input, print this error message.
            cout << "wrong input, please try again or press h for help menu" << endl;
        }
     }
      
        cout << "Command: ";
        cin >> command;
    }

    cout << "Exit.";



	return 0;
}


// function that prints the help menu.
void helpMenu()
{
    cout << "Supported commands:" << endl;
    cout << "\t\ta\t\tAdd parts." << endl;
    cout << "\t\th\t\tprint Help text." << endl;
    cout << "\t\ti\t\tInput inventory data from a file." << endl;
    cout << "\t\tp\t\tPrint inventory list." << endl;
    cout << "\t\tn\t\tNew inventory item." << endl;
    cout << "\t\to\t\tOutput inventory data to a file." << endl;
    cout << "\t\tq\t\tquit (end the program)." << endl;
    cout << "\t\tr\t\tRemove parts." << endl;

}

// function that inputs inventory data from a file.
void inputFile(string inputFileName, std::ifstream& fp, int units, double cost, InventoryItem item[100], int &counter, int records)
{
    std::string line;
    string itemNum, unit, description, Cost;

    cout << "Enter name of input file: ";
    cin >> inputFileName;

    fp.open(inputFileName); // open the input file.
    if (fp.is_open()) {
        while (getline(fp, line)) {

            stringstream linestream(line);

            // split each line in the file into separate fields, then store these fields in strings.
            getline(linestream, itemNum, '|'); // store the field before the first delimiter '|'  in itemNum.
            getline(linestream, description, '|'); // store the field before the second delimiter '|'  in description.
            getline(linestream, Cost, '|');  // store the field before the third delimiter '|'  in Cost.
            getline(linestream, unit);  // store the remainder of the line in unit.

            units = stoi(unit); // convert string unit into integer
            cost = stod(Cost); // convert string Cost into double.

            // set the description, cost, and unit for each item.
            item[counter].setDescription(description);
            item[counter].setCost(cost);
            item[counter].setUnits(units);

            counter++;  // increment counter
            records++;  // increment records
        }

        cout << records << " records loaded to array" << endl;

        fp.close(); // close the file.

        records = 0;  // initialize records to zero.
    }
}

// function that prints inventory items list.
void printFileData(int counter, InventoryItem item[100])
{
    cout << left << setw(10) << "Item Num" << left << setw(45) << "Description" << left << setw(20) << "Cost" << left << setw(16) << "Quantity" << endl;
    cout << left << setw(10) << "_________" << left << setw(45) << "____________" << left << setw(20) << "______" << left << setw(16) << "___________" << endl;

    // printing inventory items list.
    for (int i = 0; i < counter; i++) {

        cout << setw(10) << i << left << setw(45) << item[i].getDescription() << left << setw(20) << item[i].getCost() << left << setw(16) << item[i].getUnits() << endl;
    }

    cout << counter << " records." << endl;
}

// function that add units to a specified item.
void addParts(InventoryItem item[100])
{
    int itemNumAdd, partsToAdd;

    // asking the user to choose the item that he/she wants to add units to, then enter how many units to add.
    cout << endl << "Choose an Item Number: ";
    cin >> itemNumAdd;
    cout << "How many parts to add? ";
    cin >> partsToAdd;

    // add the new units the user entered to the units of the specified item. 
    item[itemNumAdd].setUnits(item[itemNumAdd].getUnits() + partsToAdd);
}

// function that remove units from a specified item.
void removeParts(InventoryItem item[100])
{
    int itemNumRemove, partsToRemove;

    // asking the user to choose the item that he/she wants to remove units from, then enter how many parts to remove.
    cout << endl << "Choose an Item Number: ";
    cin >> itemNumRemove;
    cout << "How many parts to remove? ";
    cin >> partsToRemove;

    // if the user enters number of units to remove more than the current number of units, print this error message.
    if (partsToRemove > item[itemNumRemove].getUnits()) {
        cout << "Error: You are attempting to remove more parts than the Item currently holds." << endl;
    }
    else {
        // remove the new units the user entered from the units of the specified item.
        item[itemNumRemove].setUnits(item[itemNumRemove].getUnits() - partsToRemove);
    }
}

// function that create a new inventory item and add it to the array of items.
void addNewInventoryItem(int &counter, InventoryItem item[100])
{
    string newDescription;
    double newCost;
    int newQuantity;

    // get the information of the new item from the user.
    cout << "Enter description for new Item: ";
    cin.ignore(100, '\n');
    getline(cin, newDescription);
    cout << "Enter unit cost for new Item: ";
    cin >> newCost;
    cout << "Enter initial quantity for the new Item: ";
    cin >> newQuantity;

    // if the user enters number of units < 0 or > 30, print this error message, then allows him to enter the number of units again.
    if (newQuantity < 0 || newQuantity > 30) {
        cout << "Error: initial quantity must be >= zero and <= 30." << endl;
        cout << "Enter initial quantity for the new Item: ";
        cin >> newQuantity;
    }
    counter += 1;
    // set the description, cost, and unit for the new item.
    item[counter - 1].setDescription(newDescription);
    item[counter - 1].setCost(newCost);
    item[counter - 1].setUnits(newQuantity);


    cout << "Announcing a new inventory Item: " << newDescription << endl;
    cout << "We now have " << counter << " different inventory Items in stock!" << endl;
}

// function that output the inventory data to a file.
void outputFile(std::ofstream& myFile, string outputFileName, int counter, InventoryItem item[100])
{
    // get the name of the output file from the user.
    cout << "Enter the name of the output file: ";
    cin >> outputFileName;
    myFile.open(outputFileName); // open the output file

    // output the inventory data to the file.
    for (int i = 0; i < counter; i++) {

        myFile << i << "|" << item[i].getDescription() << "|" << item[i].getCost() << "|" << item[i].getUnits() << endl;
    }

    cout << counter << " records written to file." << endl;

    myFile.close(); // close the output file.
}