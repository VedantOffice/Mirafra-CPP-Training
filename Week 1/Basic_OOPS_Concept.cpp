#include<iostream>
using namespace std;
class BankAccount
{
    private:
        int accountNumber; // Unique account number
        string accountName; // Name of the account holder
        double balance; // Account balance
    public:
        // Constructor
        BankAccount(int accountNumber, string accountName, double balance)
        {
            this->accountNumber = accountNumber;
            this->accountName = accountName;
            this->balance = balance;
        }
        // Method to deposit money into the account
        void deposit(double amount)
        {
            if(amount<0)
            {
                cout<<"Deposit Amount must be positive"<<endl;
            }
            else
            {
                balance = balance + amount;
                cout<<"Deposited amount = "<<amount<<"\t"<<"Updated balance = "<<balance<<endl;
            }
        }
        // Method to withdraw money from the account
        void withdraw(double amount)
        {
            if(amount>balance)
            {
                cout<<"Insufficient balance"<<endl;
            }
            else if(amount<0)
            {
                cout<<"Amount must be positive"<<endl;
            }
            else
            {
                balance = balance - amount;
                cout<<"Withdrawn amount = "<<amount<<"\t"<<"Updated balance = "<<balance<<endl;
            }
        }
        // Method to display account information
        void displayinfo()
        {
            cout<<"Account Number = "<<accountNumber<<endl;
            cout<<"Account Holder name = "<<accountName<<endl;
            cout<<"Balance = "<<balance<<endl;
        }
};
int main()
{
    // Create a BankAccount object
    BankAccount b1(1000, "Vedant Kulkarni", 25000);
    // Perform transactions
    b1.deposit(285.89);
    b1.displayinfo(); // Display updated account details
    b1.withdraw(200.40);
    b1.withdraw(30000);   // Should fail due to insufficient funds  
    return 0;
}