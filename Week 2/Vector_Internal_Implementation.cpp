#include<iostream>
using namespace std;
template<typename T>
class MyVector
{
    private:
        T* data;
        size_t size; //size_t is a special unsigned integer type defined in the standard library
        size_t capacity;
        // Function to resize the array when the current capacity is reached
        void resize(size_t newcapacity)
        {
            T* newdata = new T[newcapacity];
            for(size_t i = 0; i<size; i++)
            {
                newdata[i] = data[i];
            }
            delete[] data;
            data = newdata;
            capacity = newcapacity;
        }
    public:
        MyVector()
        {
            data = nullptr;
            size = 0;
            capacity = 0;
        }
        // Function to add an element to the vector
        void push_back(const T& value)
        {
            if(size == capacity)
            {
                if(capacity == 0)
                {
                    resize(1);
                }
                else
                {
                    resize(capacity*2);
                }
            }
            data[size] = value;
            size++;
        }
        // Function to remove an element to the vector
        void pop_back()
        {
            if(size<=0)
            {
                cout<<"No element to pop"<<endl;
            }
            else
            {
                size--;
            }
        }
        // Function to access an element in the vector by its index
        T& operator[](size_t index)
        {
            if(index>=size)
            {
                throw out_of_range("Index out of range");
            }
            return data[index];
        }
        // Function to get the size of the vector
        size_t getSize()
        {
            return size;
        }
        // Function to get the capacity of the vector
        size_t getCapacity()
        {
            return capacity;
        }
        // Function to print all the elements of the vector
        void print()
        {
            for(size_t i =  0; i<size; i++)
            {
                cout<<data[i]<<"\t";
            }
        }
        // Function to clear all the elements of the vector
        void clear()
        {
            size = 0;
        }
        // Function to access an element in the vector by the at function
        T& at(size_t index)
        {
            if(index>=size)
            {
                throw out_of_range("Index out of range");
            }
            return data[index];
        }
        ~MyVector()
        {
            delete[] data;
        }
};
int main()
{
    MyVector<int> v1;
    v1.push_back(20);
    cout<<"Size = "<<v1.getSize()<<"\t"<<"Capacity = "<<v1.getCapacity()<<endl;
    v1.push_back(40);
    cout<<"Size = "<<v1.getSize()<<"\t"<<"Capacity = "<<v1.getCapacity()<<endl;
    v1.push_back(50);
    cout<<"Size = "<<v1.getSize()<<"\t"<<"Capacity = "<<v1.getCapacity()<<endl;

    v1.pop_back();
    cout<<"Size = "<<v1.getSize()<<"\t"<<"Capacity = "<<v1.getCapacity()<<endl;

    cout<<v1[1]<<endl;

    v1.print();
    cout<<endl;
    // v1.clear();
    // cout<<v1[0];

    cout<<v1.at(1);

    
    return 0;
}