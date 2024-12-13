#include<iostream>
#include<ctime>
#include<queue>
#include<vector>
#include<stack>
#include<chrono>
#include<thread>
using namespace std;
using namespace chrono;
class Vehicle
{
    private:
        string vehicle_number;
        string vehicle_name;
        string vehicle_type;
        time_t entryTime;
        time_t exitTime;
    public:
        Vehicle()
        {

        }
        Vehicle(string vehicle_number, string vehicle_type, string vehicle_name)
        {
            this->vehicle_number = vehicle_number;
            this->vehicle_type = vehicle_type;
            this->vehicle_name = vehicle_name;
            entryTime = time(0);
            exitTime = entryTime;
        }
        void setExitTime(time_t exitTime)
        {
            this->exitTime = exitTime;
        }
        double calculateParkingFee()
        {
            double duration = difftime(exitTime, entryTime);
            double durationInHours = duration/3600;
            if(durationInHours < 1)
            {
                durationInHours = 1;
            }
            double fee = 0;
            if (vehicle_type == "normal" && vehicle_name == "car") 
            {
                fee = durationInHours * 20;
            } 
            else if (vehicle_type == "normal" && vehicle_name == "bike") 
            {
                fee = durationInHours * 10;
            }
            else if (vehicle_type == "emergency") 
            {
                fee = durationInHours * 0;
            }
            return fee;
        }
        void displayVehicleDetails()
        {
            cout<<"Vehicle Number: "<< vehicle_number << endl;
            cout<<"Vehicle Type: "<<vehicle_type<<endl;
            cout<<"Vehicle Name: "<<vehicle_name<<endl;
            cout<<"Entry Time: "<<ctime(&entryTime);
        }
        string getVehicleNumber()
        {
            return vehicle_number;
        }
        string getVehicleType()
        {
            return vehicle_type;
        }
        bool operator<(const Vehicle& other)
        {
            return this->vehicle_type != "emergency" && other.vehicle_type == "emergency";
        }
        Vehicle(const Vehicle& other) 
        {
            vehicle_number = other.vehicle_number;
            vehicle_name = other.vehicle_name;
            vehicle_type = other.vehicle_type;
            entryTime = other.entryTime;
            exitTime = other.exitTime;
        }
};
class EmergencyVehicleComparator
{
    public:
        bool operator()(Vehicle &v1, Vehicle &v2)
        {
            if (v1.getVehicleType() == "emergency" && v2.getVehicleType() != "emergency")
                return false;
            if (v1.getVehicleType() != "emergency" && v2.getVehicleType() == "emergency")
                return true;
            return false;
        }
};
class ParkingSystem
{
    private:
        vector<Vehicle> parkingLot;
        queue<Vehicle> waitingQueue;
        stack<Vehicle> exitStack;
        priority_queue<Vehicle, vector<Vehicle>, EmergencyVehicleComparator> priorityQueue;
        double totalRevenue;
        int maxCapacity;
        int currentVehicles;
    public:
        ParkingSystem()
        {

        }
        ParkingSystem(int maxCapacity)
        {
            this->maxCapacity = maxCapacity;
            this->currentVehicles = 0;
            this->totalRevenue = 0.0;
        }
        void vehicleEntry(Vehicle& v)
        {
            if (currentVehicles < maxCapacity) 
            {
                parkingLot.push_back(v);
                currentVehicles++;
                cout<<"Vehicle " << v.getVehicleNumber()<<" has entered the parking lot.\n";
            }
            else 
            {
                if (v.getVehicleType() == "emergency") 
                {
                    priorityQueue.push(v);
                    cout<<"Emergency vehicle " << v.getVehicleNumber() << " is waiting.\n";
                }
                else
                {
                    waitingQueue.push(v);
                    cout<<"Parking lot is full. Vehicle "<< v.getVehicleNumber()<<" is waiting.\n";
                }
            }
        }
        void vehicleExit(const string& vehicleNumber) 
        {
            bool found = false;
            for (auto it = parkingLot.begin(); it != parkingLot.end(); ++it) 
            {
                if (it->getVehicleNumber() == vehicleNumber) 
                {
                    time_t exitTime = time(0);
                    it->setExitTime(exitTime);  // set exit time when vehicle exits

                    // Simulate parking time with a delay for 5 seconds
                    std::this_thread::sleep_for(std::chrono::seconds(5)); 

                    double fee = it->calculateParkingFee();  // Calculate the fee after sleep
                    totalRevenue += fee;

                    cout << "Vehicle " << vehicleNumber << " is exiting the parking lot.\n";
                    cout << "Parking Fee = " << fee << endl;

                    exitStack.push(*it);
                    parkingLot.erase(it);
                    currentVehicles--;

                    found = true;
                    break;
                }
            }

            if (!found) 
            {
                cout << "Vehicle " << vehicleNumber << " not found in the parking lot.\n";
                return;
            }

            // After a vehicle exits, check the waiting queue and priority queue for other vehicles
            if (!priorityQueue.empty()) 
            {
                Vehicle nextVehicle = priorityQueue.top();
                priorityQueue.pop();
                vehicleEntry(nextVehicle);
            } 
            else if (!waitingQueue.empty()) 
            {
                Vehicle nextVehicle = waitingQueue.front();
                waitingQueue.pop();
                vehicleEntry(nextVehicle);
            }
        }



        void displayParkingStatus()
        {
            cout<<"\nCurrent Vehicles in Parking Lot:\n";
            if (parkingLot.empty()) 
            {
                cout<<"The parking lot is empty.\n";
            } 
            else 
            {
                for (Vehicle& vehicle : parkingLot) 
                {
                    vehicle.displayVehicleDetails();
                    cout<<"-------------------------------------\n";
                }
            }

            cout<<"\nVehicles in Waiting Queue:\n";
            if (waitingQueue.empty()) 
            {
                cout<<"No vehicles waiting.\n";
            }
            else
            {
                queue<Vehicle> tempQueue = waitingQueue;
                while (!tempQueue.empty()) 
                {
                    Vehicle v = tempQueue.front();
                    tempQueue.pop();
                    cout<<"Vehicle Number = "<< v.getVehicleNumber()<<endl;
                }
            }

            cout<<"\nVehicles Exited:\n";
            if (exitStack.empty()) 
            {
                cout<<"No vehicles have exited yet.\n";
            } 
            else
            {
                stack<Vehicle> tempStack = exitStack;
                while (!tempStack.empty()) 
                {
                    Vehicle v = tempStack.top();
                    tempStack.pop();
                    v.displayVehicleDetails();
                    cout << "-------------------------------------\n";
                }
            }
        }
        void displayTotalRevenue()
        {
            cout << "\nTotal Revenue Generated: $" << totalRevenue << endl;
        }
};
int main()
{
    ParkingSystem system(5);

    // Create some vehicles
    Vehicle v1("ABC123", "normal", "car");
    Vehicle v2("LMN789", "normal", "bike");
    Vehicle v3("PQR111", "emergency", "ambulance");
    Vehicle v4("JKL222", "normal", "car");
    Vehicle v5("XYZ456", "normal", "car");

    // Vehicles enter the parking lot
    system.vehicleEntry(v1);
    system.vehicleEntry(v2);
    system.vehicleEntry(v3);
    system.vehicleEntry(v4);
    system.vehicleEntry(v5);

    system.displayParkingStatus();

    // Simulate some vehicles exiting after some time
    system.vehicleExit("PQR111");  // Emergency vehicle exits
    system.vehicleExit("ABC123");  // Normal car exits

    system.displayParkingStatus();
    system.displayTotalRevenue();  // Display total revenue

    // More vehicles entering
    Vehicle v6("XYZ999", "normal", "car");
    Vehicle v7("ABC888", "normal", "bike");
    system.vehicleEntry(v6);
    system.vehicleEntry(v7);

    system.displayParkingStatus();

    // Exit another vehicle
    system.vehicleExit("XYZ456");

    system.displayParkingStatus();
    system.displayTotalRevenue();  // Display total revenue

}