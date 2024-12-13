#include<iostream>
using namespace std;
class BankAccount
{
    private:
        int accNumber;
        string accName;
        double balance;
    public:
        BankAccount(int accNumber, double balance, const string& str)
        {
            this->accNumber = accNumber;
            this->accName = str;
            this->balance = balance;
        }
        BankAccount(BankAccount& b)
        {
            this->accNumber = b.accNumber;
            this->accName = b.accName;
            this->balance = b.balance;
        }
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
            cout<<"Account Number = "<<accNumber<<endl;
            cout<<"Account Holder name = "<<accName<<endl;
            cout<<"Balance = "<<balance<<endl;
        }
};
int main()
{
    BankAccount b1(101, 25000, "Vedant Kulkarni");

    BankAccount b2 = b1;
    b2.displayinfo();
    return 0;
}
