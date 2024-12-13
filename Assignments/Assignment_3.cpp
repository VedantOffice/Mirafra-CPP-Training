#include<iostream>
#include<vector>
using namespace std;
class FoodItem
{
    private:
        string name;
        int id;
        double price;
        string category;
    public:
        FoodItem(string name, int id, double price, string category)
        {
            this->name = name;
            this->id = id;
            this->price = price;
            this->category = category;
        }
        void display()
        {
            cout<<"Food Item name : "<<name
            <<"Food Item Price : "<<price
            <<"Food Item category : "<<category;
        }
        double getPrice()
        {
            return price;
        }
        int getId()
        {
            return id;
        }
};
class MenuNode
{
    public:
        FoodItem* f1;
        MenuNode* next;
        MenuNode(FoodItem* f)
        {
            f1 = f;
            next = nullptr;
        }
};
class Menu
{
    public:
        MenuNode* head;
    public:
        Menu()
        {
            head = nullptr;
        }
        void addFoodItem(FoodItem& f)
        {
            FoodItem* f1 = new FoodItem(f);
            MenuNode* newnode = new MenuNode(f1);
            if(head == nullptr)
            {
                head = newnode;
                return;
            }
            MenuNode* current = head;
            while(current->next != nullptr)
            {
                current = current->next;
            }
            current->next = newnode;
        }
        void displayMenu()
        {
            MenuNode* current = head;
            while(current != nullptr)
            {
                current->f1->display();
                cout<<endl;
                current = current->next;
            }
            cout<<endl;
        }
        void removeFoodItem(FoodItem& f1) 
        {
            if (head == nullptr) 
            {
                cout << "Menu is empty!" << endl;
                return;
            }
            if (head->f1 == &f1) 
            {
                MenuNode* temp = head;
                head = head->next;
                delete temp;
                cout << "Food Item deleted successfully from the Menu" << endl;
                return;
            }
            MenuNode* prev = head;
            MenuNode* current = head->next;
            while (current != nullptr) 
            {
                if (current->f1 == &f1) 
                {
                    prev->next = current->next;
                    delete current;
                    cout << "Food Item deleted successfully from the Menu" << endl;
                    return;
                }
                prev = current;
                current = current->next;
            }
            cout << "Food Item not found!" << endl;
        }
        MenuNode* getHead() 
        {
            return head;
        }
};
class Order
{
    private:
        int orderId;
        vector<FoodItem*> foodItems;
        double totalPrice;
    public:
        void addFoodItem(FoodItem* f)
        {
            foodItems.push_back(f);
            totalPrice = totalPrice + f->getPrice();
            cout<<"Food Item added successfully"<<endl;
        }
        void displayOrder()
        {
            cout<<"Order ID : "<<orderId<<endl;
            for(FoodItem* f: foodItems)
            {
                f->display();
            }
            cout<<"total Price = "<<totalPrice<<endl;
        }
};
class Restaurant
{
    private:
        string name;
        int restaurantID;
        Menu m;
    public:
        Restaurant(string name, int r)
        {
            this->name = name;
            restaurantID = r;
        }
        void addFoodToMenu(FoodItem& f)
        {
            m.addFoodItem(f);
        }
        void removeFoodFromMenu(FoodItem& f)
        {
            m.removeFoodItem(f);
        }
        void displayMenu()
        {
            cout<<"Displaying menu for Restaurant Name = "<<name<<endl;
            m.displayMenu();
        }
        string getName()
        {
            return name;
        }
        Menu& getMenu()
        {
            return m;
        }
        int getID()
        {
            return restaurantID;
        }
};
class Customer
{
    private:
        int customerID;
        string name;
    public:
        Customer(int c, string n)
        {
            customerID = c;
            name = n;
        }
        void placeOrder(Restaurant& r, vector<FoodItem*>& f)
        {
            Order o;
            for(FoodItem* f1 : f)
            {
                o.addFoodItem(f1);
            }
            cout<<"Order placed successfully at restaurant "<<r.getName();
        }
        void viewMenu(Restaurant& r) 
        {
            cout << "Viewing menu for restaurant: " << r.getName() << endl;
            r.displayMenu();
        }
};
class Admin 
{
    public:
        void createRestaurant(vector<Restaurant*>& restaurants) 
        {
            string name;
            int id;
            cout << "Enter Restaurant Name: ";
            cin >> name;
            cout << "Enter Restaurant ID: ";
            cin >> id;

            Restaurant* newRestaurant = new Restaurant(name, id);
            restaurants.push_back(newRestaurant);
            cout << "Restaurant created successfully!" << endl;
        }
};
class HotelManager 
{
    public:
        void addFoodToMenu(Restaurant& r) 
        {
            string foodName, category;
            int foodId;
            double foodPrice;
            cout << "Enter food name: ";
            cin >> foodName;
            cout << "Enter food ID: ";
            cin >> foodId;
            cout << "Enter food price: ";
            cin >> foodPrice;
            cout << "Enter food category: ";
            cin >> category;
            FoodItem newFood(foodName, foodId, foodPrice, category);
            r.addFoodToMenu(newFood);
        }
        void removeFoodFromMenu(Restaurant& r) 
        {
            int foodId;
            cout << "Enter food ID to remove: ";
            cin >> foodId;
            Menu& menu = r.getMenu();
            MenuNode* current = menu.getHead();
            FoodItem* foodToRemove = nullptr;
            while (current != nullptr) 
            {
                if (current->f1->getId() == foodId) 
                {
                    foodToRemove = current->f1;
                    break;
                }
                current = current->next;
            }
            if (foodToRemove != nullptr) 
            {
                r.removeFoodFromMenu(*foodToRemove);
            } 
            else 
            {
                cout << "Food Item not found!" << endl;
            }
        }
};
int main()
{
    vector<Restaurant*> restaurants;
    Admin admin;
    HotelManager hotelManager;
    Customer customer1(1, "Vedant");

    int roleChoice;
    int menuChoice;

    while (true) 
    {
        cout << "\n-------- MAIN MENU --------\n";
        cout << "1. Admin\n";
        cout << "2. Hotel Manager\n";
        cout << "3. Customer\n";
        cout << "4. Exit\n";
        cout << "Enter your role choice: ";
        cin >> roleChoice;
        if (roleChoice == 1) 
        { 
            int password;
            cout<<"Enter Password\n";
            cin>>password;
            if(password==1000)
            {
                cout << "Admin Menu:\n";
                cout << "1. Create Restaurant\n";
                cout << "2. Exit\n";
                cin >> menuChoice;
                if (menuChoice == 1) 
                {
                    admin.createRestaurant(restaurants);
                } 
                else if (menuChoice == 2) 
                {
                    break;
                }
            }
            else
            {
                cout<<"You are not Admin";
            }
        }
        else if (roleChoice == 2) 
        { 
            int restaurantId;
            cout << "Enter Restaurant ID to manage: ";
            cin >> restaurantId;
            Restaurant* restaurant = nullptr;
            for (auto& r : restaurants) 
            {
                if (r->getID() == restaurantId) 
                {
                    restaurant = r;
                    break;
                }
            }
            if (restaurant == nullptr) 
            {
                cout << "Restaurant not found!" << endl;
                continue;
            }
            cout << "Hotel Manager Menu:\n";
            cout << "1. Add Food to Menu\n";
            cout << "2. Remove Food from Menu\n";
            cout << "3. View Menu\n";
            cout << "4. Exit\n";
            cin >> menuChoice;
            if (menuChoice == 1) 
            {
                hotelManager.addFoodToMenu(*restaurant);
            } 
            else if (menuChoice == 2) 
            {
                hotelManager.removeFoodFromMenu(*restaurant);
            } 
            else if (menuChoice == 3) 
            {
                restaurant->displayMenu();
            } 
            else if (menuChoice == 4)
            {
                break;
            }
        }
        else if (roleChoice == 3) 
        {
            if (restaurants.empty()) 
            {
                cout << "No restaurants available!\n";
                continue;
            }
            cout << "Enter Restaurant ID to order from: ";
            int restaurantId;
            cin >> restaurantId;
            Restaurant* restaurant = nullptr;
            for (auto& r : restaurants) 
            {
                if (r->getID() == restaurantId) 
                {
                    restaurant = r;
                    break;
                }
            }
            if (restaurant == nullptr) 
            {
                cout << "Restaurant not found!" << endl;
                continue;
            }
            cout << "Customer Menu:\n";
            cout << "1. View Menu\n";
            cout << "2. Place Order\n";
            cout << "3. Exit\n";
            cin >> menuChoice;
            if (menuChoice == 1) 
            {
                customer1.viewMenu(*restaurant);
            } 
            else if (menuChoice == 2) 
            {
                int numItems;
                cout << "Enter number of items to order: ";
                cin >> numItems;
                vector<FoodItem*> orderItems;
                for (int i = 0; i < numItems; ++i) 
                {
                    int foodId;
                    cout << "Enter food ID to add to order: ";
                    cin >> foodId;
                    Menu& menu = restaurant->getMenu();
                    MenuNode* current = menu.getHead();
                    FoodItem* selectedFood = nullptr;
                    while (current != nullptr) 
                    {
                        if (current->f1->getId() == foodId) 
                        {
                            selectedFood = current->f1;
                            break;
                        }
                        current = current->next;
                    }
                    if (selectedFood != nullptr) 
                    {
                        orderItems.push_back(selectedFood);
                    } 
                    else 
                    {
                        cout << "Food Item with ID " << foodId << " not found!" << endl;
                    }
                }
                customer1.placeOrder(*restaurant, orderItems);
            } 
            else if (menuChoice == 3)
            {
                break;
            }
        }
        else if (roleChoice == 4) 
        { 
            cout << "Exiting program...\n";
            break;
        }
    }    
    return 0;
}