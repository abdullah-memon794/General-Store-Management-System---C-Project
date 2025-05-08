#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
using namespace std;

struct Product {
    string name;
    int id;
    double price;
    int quantity;
};

class SalesManagementSystem {
private:
    vector<Product> products;

public:
    
	void loadFromFile() {
        ifstream file("products.txt");
        string line;
        
        while (getline(file, line)) {
            stringstream ss(line);
            Product product;
            string token;
            
            getline(ss, product.name, ',');
            getline(ss, token, ',');
            stringstream(token) >> product.id;  
            getline(ss, token, ',');
            stringstream(token) >> product.price;  
            getline(ss, token, ',');
            stringstream(token) >> product.quantity; 
            
            products.push_back(product);
        }
        file.close();
    }


    void addProduct() {
        do {
            Product product;
            cout << "Enter Product Name: ";
            cin >> product.name;
            cout << "Enter Product ID: ";
            cin >> product.id;
            cout << "Enter Product Price: ";
            cin >> product.price;
            cout << "Enter Product Quantity: ";
            cin >> product.quantity;
            cout << endl;
            
            products.push_back(product);
            saveToFile();

            char choice;
            cout << "Do you want to add more products? (y/n): ";
            cin >> choice;
            cout << endl;
            
            if (choice != 'y') break;

        } while (true);
    }


    void purchaseProduct() {
        if (products.empty()) {
            cout << "No products available for purchase.\n" << endl;
            return;
        }

        double totalAmount = 0.0;  
        vector< pair<string, double> > purchasedItems;  
        vector<int> purchasedQuantities; 

        do {
            cout << "\n\n\t\t\t*** AVAILABLE PRODUCTS ***\n";
            cout << "--------------------------------------------------"
                 << "---------------------------------------------------" << endl;
            cout << "ID" << setw(25) << "Name" << setw(25) << "Price"
                 << setw(25) << "Quantity" << endl;
            cout << "--------------------------------------------------"
                 << "---------------------------------------------------" << endl << endl;

			for (size_t i = 0; i < products.size(); ++i) {
                cout << products[i].id << setw(25) << products[i].name
                     << setw(25) << products[i].price << setw(25) << products[i].quantity << "\n";
            	cout << endl;
			}


            int id;
            cout << "Enter Product ID to purchase: ";
            cin >> id;
            cout << endl;

            bool found = false;
            
            for (size_t i = 0; i < products.size(); ++i) {
                if (products[i].id == id) {
                    int quantity;
                    cout << "Enter Quantity to purchase: ";
                    cin >> quantity;
                    cout << endl;
                    
                    if (quantity <= products[i].quantity) {
                        products[i].quantity -= quantity; 

                        double totalPrice = products[i].price * quantity;
                        totalAmount += totalPrice;

                        purchasedItems.push_back(make_pair(products[i].name, products[i].price));
						purchasedQuantities.push_back(quantity);

                        cout << "Purchased " << quantity << " of " << products[i].name
                             << " for " << totalPrice << "." << endl << endl;
                    } else {
                        cout << "Insufficient quantity available.\n" << endl << endl;
                    }
                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "Product not found.\n" << endl << endl;
            }

            char choice;
            cout << "Do you want to purchase more products? (y/n): ";
            cin >> choice;
            cout << endl;
            
            if (choice != 'y') break;
        
        } while (true);

        cout << "\n\n\t\t\t*** PURCHASE BILL ***\n";
        cout << "--------------------------------------------------"
                 << "---------------------------------------------------" << endl;
        cout << "Product Name" << setw(25) << "Quantity" << setw(25) << "Price per unit" << setw(25) << "Total\n";
        cout << "--------------------------------------------------"
                 << "---------------------------------------------------" << endl;

        for (size_t i = 0; i < purchasedItems.size(); ++i) {
            cout << purchasedItems[i].first 
				<< setw(25) << purchasedQuantities[i] 
                 << setw(25) << purchasedItems[i].second 
                 << setw(25) << purchasedQuantities[i] * purchasedItems[i].second << "\n";
        }

        cout << "--------------------------------------------------"
                 << "---------------------------------------------------" << endl;
        cout << "\t\t TOTAL AMOUNT: " << totalAmount << endl;
        cout << "--------------------------------------------------"
                 << "---------------------------------------------------" << endl << endl;

        saveToFile();  
    }

    void saveToFile() {
        ofstream file("products.txt", ios::trunc);  
        for (size_t i = 0; i < products.size(); ++i) {
            file << products[i].name << "," << products[i].id << "," << products[i].price
                 << "," << products[i].quantity << "\n";
        }
        file.close();
    }

    void run() {
        loadFromFile();  
        
        int option;
        do {
            cout << "1. Add Product\n2. Purchase Product\n0. Exit\n";
            cout << "Select an option: ";
            cin >> option;
            cout << endl;
            
            switch (option) {
                case 1:
                    addProduct();
                    break;
                case 2:
                    purchaseProduct();
                    break;
                case 0:
                    cout << "Exiting program.\n" << endl;
                    break;
                default:
                    cout << "Invalid option. Please try again.\n" << endl;
            }
        } while (option != 0);
    }
};

int main() {
    cout << "\t\t* * * * * * * * * * * * * * * * * * * * * * * * *\n";
    cout << "\t\t*                                               *\n";
    cout << "\t\t*                                               *\n";
    cout << "\t\t*       -----------------------------           *\n";
    cout << "\t\t*          Sales  Mangement  System             *\n";
    cout << "\t\t*       -----------------------------           *\n";
    cout << "\t\t*                                               *\n";
    cout << "\t\t*                                               *\n";
    cout << "\t\t*                                               *\n";
    cout << "\t\t*  Made By:- Abdullah Memon					 *\n";
    cout << "\t\t*                                               *\n";
    cout << "\t\t* * * * * * * * * * * * * * * * * * * * * * * * *\n\n";

    SalesManagementSystem sms;
    sms.run();
    return 0;
}
