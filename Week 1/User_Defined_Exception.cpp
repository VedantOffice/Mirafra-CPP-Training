#include<iostream>
using namespace std;
class MyException: public exception
{
    private:
        string message;
    public:
        MyException(const string msg)
        {
            message = msg;
        }
        const string what()
        {
            return message;
        }
};
int main()
{
    try
    {
        int a;
        cin>>a;
        if(a==0)
        {
            throw MyException("Number is zero");
        }
        else{
            cout<<a;

        }
    }
    catch(MyException& e)
    {
        cout<< e.what() << '\n';
    }
    
    return 0;
}