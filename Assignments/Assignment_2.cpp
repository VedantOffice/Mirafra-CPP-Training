#include<iostream>
#include<vector>
using namespace std;
class Items 
{
    public:
        int itemId;
        string name;
        int quantity;
        double price;
    public:
        Items() 
        {
            itemId = 0;
            name = "";
            quantity = 0;
            price = 0.0;
        }
        Items(int itemId, string name, int quantity, double price) 
        {
            this->itemId = itemId;
            this->name = name;
            this->quantity = quantity;
            this->price = price;
        }
        int getQuantity()
        {
            return quantity;
        }
        friend ostream& operator<<(ostream& os, const Items& item);
};
class Inventory 
{
    private:
        Items item;
        vector<vector<vector<Items>>> inventory;
        int locationX;
        int locationY;
        int locationZ;
    public:
        Inventory() 
        {

        }
        Inventory(int locationX, int locationY, int locationZ) 
        {
            this->locationX = locationX;
            this->locationY = locationY;
            this->locationZ = locationZ;
            for (int i = 0; i <= locationX; i++) 
            {
                vector<vector<Items>> layer;
                for (int j = 0; j <= locationY; j++) 
                {
                    vector<Items> row;
                    for (int k = 0; k <= locationZ; k++) 
                    {
                        row.push_back(Items());
                    }
                    layer.push_back(row);
                }
                inventory.push_back(layer);
            }
        }
        void addItem(int x, int y, int z, Items item) 
        {
            if (item.quantity != 0) 
            {
                inventory[x][y][z] = item;
            }
            else 
            {
                cout << "Item quantity is zero. Not adding to inventory." << endl;
            }
        }
        void disply() 
        {
            for (int i = 0; i < inventory.size(); i++) 
            {
                for (int j = 0; j < inventory[i].size(); j++) 
                {
                    for (int k = 0; k < inventory[i][j].size(); k++) 
                    {
                        if (inventory[i][j][k].name != "" || inventory[i][j][k].quantity > 0 ) 
                        {
                            cout<<"Location : "<<"("<<i<<","<<j<<","<<k<<")"<<endl;
                            cout << inventory[i][j][k] << endl;
                        }
                    }
                    cout << endl;
                }
                cout << endl;
            }
        }
        Items* findItem(int id)
        {
            for(int i = 0; i<inventory.size(); i++)
            {
                for(int j = 0; j<inventory[i].size(); j++)
                {
                    for(int k = 0; k<inventory[i][j].size(); k++)
                    {
                        if(inventory[i][j][k].itemId == id)
                        {
                            return &inventory[i][j][k];
                        }
                    }
                }
            }
            return nullptr;
        }
        void removeItem(const string& itemName)
        {
            bool isRemoved;
            for(int i = 0; i<inventory.size(); i++)
            {
                for(int j = 0; j<inventory[i].size(); j++)
                {
                    for(int k = 0; k<inventory[i][j].size(); k++)
                    {
                        if(inventory[i][j][k].name == itemName)
                        {
                            inventory[i][j][k] = Items();
                            isRemoved = true;
                        }
                    }
                }
            }
            if(isRemoved)
            {
                cout<<"Item removed successfully";
            }
            else
            {
                cout<<"Item not found";
            }
        }
        void transferItem(int X1, int Y1, int Z1, int X2, int Y2, int Z2, int q)
        {
            Items& fromItem = inventory[X1][Y1][Z1];
        
            if (q > fromItem.getQuantity()) 
            {
                cout << "Not enough quantity to transfer";
                return;
            }
            Items& toItem = inventory[X2][Y2][Z2];
            if (fromItem.quantity == 0) 
            {
                toItem = fromItem;
                toItem.quantity = q;
            }
            else
            {
                toItem.quantity = toItem.quantity + q;
                toItem.name = fromItem.name;
                toItem.price = fromItem.price;
                toItem.itemId = fromItem.itemId;
            }
            fromItem.quantity = fromItem.getQuantity() - q; 
            cout<<"Item transferred successfully"<<endl;
        }
        int checkStocks(int x, int y, int z)
        {
            return inventory[x][y][z].quantity;
        }
        void lowStocksAlert(int id)
        {
            for(int i = 0; i<inventory.size(); i++)
            {
                for(int j = 0; j<inventory[i].size(); j++)
                {
                    for(int k = 0; k<inventory[i][j].size(); k++)
                    {
                        if(inventory[i][j][k].itemId == id)
                        {
                            if(inventory[i][j][k].quantity<5)
                            {
                                cout<<"Low Stock Alert"<<endl;
                            }
                            else
                            {
                                cout<<"Not Low quantity"<<endl;
                                return;
                            }
                        }
                    }
                }
            }
        }
};
ostream& operator<<(ostream& os, const Items& item) 
{
    os << "Item ID: " << item.itemId << "\nName: " << item.name << "\nQuantity: " << item.quantity << "\nPrice: " << item.price << "\n";
    return os;
}
int main() 
{
    Inventory I(3, 3, 3);
    int choice;
    do 
    {
        cout << "\n--- Inventory Menu ---\n";
        cout << "1. Add Item\n";
        cout << "2. Display Inventory\n";
        cout << "3. Find Item\n";
        cout << "4. Remove Item\n";
        cout << "5. Transfer Item\n";
        cout << "6. Check Stock of Item\n";
        cout << "7. Low Stock Alert\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) 
        {
            case 1: 
            {
                int x, y, z, id, quantity;
                string name;
                double price;
                cout << "Enter item location (x, y, z): ";
                cin >> x >> y >> z;
                cout << "Enter item ID: ";
                cin >> id;
                cout << "Enter item name: ";
                cin >> name;
                cout << "Enter item quantity: ";
                cin >> quantity;
                cout << "Enter item price: ";
                cin >> price;
                I.addItem(x, y, z, Items(id, name, quantity, price));
                break;
            }
            case 2:
                I.disply();
                break;
            case 3: 
            {
                int id;
                cout << "Enter item ID to find: ";
                cin >> id;
                Items* item = I.findItem(id);
                if (item) {
                    cout << *item;
                } else {
                    cout << "Item not found\n";
                }
                break;
            }
            case 4: 
            {
                string name;
                cout << "Enter item name to remove: ";
                cin >> name;
                I.removeItem(name);
                break;
            }
            case 5: 
            {
                int X1, Y1, Z1, X2, Y2, Z2;
                cout << "Enter source location (X1, Y1, Z1): ";
                cin >> X1 >> Y1 >> Z1;
                cout << "Enter destination location (X2, Y2, Z2): ";
                cin >> X2 >> Y2 >> Z2;
                int q;
                cout<<"Enter the quantity to transfer : ";
                cin>>q;
                I.transferItem(X1, Y1, Z1, X2, Y2, Z2, q);
                break;
            }
            case 6: 
            {
                int x, y, z;
                cout << "Enter location (x, y, z) to check stock: ";
                cin >> x >> y >> z;
                cout << "Stock at location (" << x << "," << y << "," << z << "): " << I.checkStocks(x, y, z) << endl;
                break;
            }
            case 7: 
            {
                int id;
                cout << "Enter item ID for low stock alert: ";
                cin >> id;
                I.lowStocksAlert(id);
                break;
            }
            case 8:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 8);
    return 0;
}