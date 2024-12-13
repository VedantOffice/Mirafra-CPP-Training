#include<iostream>
#include<vector>
using namespace std;
class Products
{
    protected:
        int p_id;
        string name;
        double price;
        double quantity;
    public:
        Products(int p_id, string name, double price, double quantity)
        {
            this->p_id = p_id;
            this->name = name;
            this->price = price;
            this->quantity = quantity;
        }
        virtual void displayProduct()
        {
            cout<<"Product ID = "<<p_id<<endl;
            cout<<"Product name = "<<name<<endl;
            cout<<"Price = "<<price<<endl;
            cout<<"Quantity = "<<quantity<<endl;
        }
        virtual double getPrice()
        {
            return price;
        }
        virtual double getQuantity()
        {
            return quantity;
        }
        virtual string getName()
        {
            return name;
        }
        virtual int getProdId()
        {
            return p_id;
        }
};
class Electronics: public Products
{
    private:
        double warranty;
    public:
        void displayProduct()
        {
            cout<<"Electronics Products"<<endl;
            cout<<"Product ID = "<<p_id<<endl;
            cout<<"Product name = "<<name<<endl;
            cout<<"Price = "<<price<<endl;
            cout<<"Quantity = "<<quantity<<endl;
            cout<<"Warranty = "<<warranty<<endl;
        }
        Electronics(int p_id, string name, double price, double quantity, double warranty):Products(p_id, name, price, quantity)
        {
            this->warranty = warranty;
        }
};
class Clothing: public Products
{
    private:
        double size;
    public:
        void displayProduct()
        {
            cout<<"Clothing Products"<<endl;
            cout<<"Product ID = "<<p_id<<endl;
            cout<<"Product name = "<<name<<endl;
            cout<<"Price = "<<price<<endl;
            cout<<"Quantity = "<<quantity<<endl;
            cout<<"Size = "<<size<<endl;
        }
        Clothing(int p_id, string name, double price, double quantity, double size):Products(p_id, name, price, quantity)
        {
            this->size = size;
        }
};
class Food: public Products
{
    private:
        string type;
    public:
        void displayProduct()
        {
            cout<<"Food Products"<<endl;
            cout<<"Product ID = "<<p_id<<endl;
            cout<<"Product name = "<<name<<endl;
            cout<<"Price = "<<price<<endl;
            cout<<"Quantity = "<<quantity<<endl;
            cout<<"Type = "<<type<<endl;
        }
        Food(int p_id, string name, double price, double quantity, string type):Products(p_id, name, price, quantity)
        {
            this->type = type;
        }
};
class Customer
{
    private:
        double c_id;
        string name;
        string address;
        string mobile_number;
    public:
        Customer()
        {

        }
        Customer(double c_id, string name, string address, string mobile_number)
        {
            this->c_id = c_id;
            this->name = name;
            this->address = address;
            this->mobile_number = mobile_number;
        }
        void showCustomer()
        {
            cout<<"Customer details as follows : "<<endl;
            cout<<"Customer ID = "<<c_id<<endl;
            cout<<"Customer name = "<<name<<endl;
            cout<<"Address = "<<address<<endl;
            cout<<"Mobile Number = "<<mobile_number<<endl;
        }
        double getCId()
        {
            return c_id;
        }
};
class Order
{
    private:
        int o_id;
        vector<Products> products;
        Customer c;
        double total;
        bool isPlaced;
    public:
        Order(int o_id, Customer& cust)
        {
            this->o_id = o_id;
            this->total = 0;
            c = cust;
        }
        void addProduct(Products p)
        {
            products.push_back(p);
            total = total + (p.getPrice()*p.getQuantity());
            cout<<"Order placed successfully by Customer with customer ID "<<c.getCId()<<endl;
        }
        void getOrderDetails()
        {
            cout<<"Order ID = "<<o_id<<endl;
            cout<<"Product Details are as follows = "<<endl;
            for(Products& prod: products)
            {
                cout<<"Product Name = "<<prod.getName()<<"\t"<<"Price = "<<prod.getPrice()<<endl;
            }
        }
        void placeOrder() 
        {
            isPlaced = true;
            cout << "Order placed successfully. No further changes allowed." << endl;
        }
        void removeProduct(int productid) {
        if (isPlaced) {
            cout << "Cannot remove product. Order is already placed." << endl;
            return;
        }
        for (auto it = products.begin(); it != products.end(); it++) {
            if (it->getProdId() == productid) {
                total -= it->getPrice();
                products.erase(it);
                cout << "Product removed successfully from Order" << endl;
                return;
            }
        }
        cout << "Product not found in the order" << endl;
    }
};
class Cart
{
    private:
        //vector<Products> prod;
        double carttotal;
    public:
        vector<Products> prod;
        void addProduct(Products p)
        {
            prod.push_back(p);
            carttotal = carttotal + (p.getPrice()*p.getQuantity());
            cout<<"Product added in cart successfully"<<endl;
        }
        void removeProduct(int productid)
        {
            for(auto it = prod.begin(); it!=prod.end(); it++)
            {
                if(it->getProdId()==productid)
                {
                    prod.erase(it);
                    carttotal = carttotal - it->getPrice();
                    cout<<"Product Removed successfully from cart"<<endl;
                }
            }
        }
        void getCartDetails()
        {
            cout<<"Cart Details as folllows "<<endl;
            for(Products p1: prod)
            {
                cout<<"Product Name = "<<p1.getName()<<"\t"<<"Product Price = "<<p1.getPrice();
            }
        }
};
int main()
{
    Products* p1 = new Electronics(1000,"Laptop", 20000, 1, 3);
    Products* p2 = new Clothing(2000,"TShirt", 200, 1, 29);
    Products* p3 = new Food(3000,"Apple", 20, 1, "Fruit");
    Customer c1(1001, "Vedant Kulkarni", "Pune, Maharashtra", "+917378637930");
    Order o1(100, c1);
    Cart cart1;
    int choice;
    do {
        cout << "\nShopping Cart Menu\n";
        cout << "1. View Products\n";
        cout << "2. Add Product to Cart\n";
        cout << "3. Remove Product from Cart\n";
        cout << "4. View Cart Details\n";
        cout << "5. Place an Order\n";
        cout << "6. Remove Product from Cart\n";
        cout << "7. View Order Details\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "\nAvailable Products:\n";
                p1->displayProduct();
                p2->displayProduct();
                p3->displayProduct();
                break;
            }
            case 2: {
                int productChoice;
                cout << "Select product to add to cart: \n";
                cout << "1. Laptop\n";
                cout << "2. T-Shirt\n";
                cout << "3. Apple\n";
                cout << "Enter your choice: ";
                cin >> productChoice;

                if (productChoice == 1) {
                    cart1.addProduct(*p1);
                } else if (productChoice == 2) {
                    cart1.addProduct(*p2);
                } else if (productChoice == 3) {
                    cart1.addProduct(*p3);
                } else {
                    cout << "Invalid choice.\n";
                }
                break;
            }
            case 3: {
                int productId;
                cout << "Enter product ID to remove from cart: ";
                cin >> productId;
                cart1.removeProduct(productId);
                break;
            }
            case 4: {
                cart1.getCartDetails();
                break;
            }
            case 5: {
            for (Products& prod : cart1.prod) 
            {
                o1.addProduct(prod); 
            }
                break;
            }
            case 6: {
                int productId;
                cout << "Enter product ID to remove from order: ";
                cin >> productId;
                o1.removeProduct(productId);
                break;
            }
            case 7: {
                o1.getOrderDetails();
                break;
            }
            case 8: {
                cout << "Thank you for shopping!\n";
                break;
            }
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 8);

    delete p1;
    delete p2;
    delete p3;
    return 0;
} 