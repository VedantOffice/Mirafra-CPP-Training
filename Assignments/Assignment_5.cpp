#include<iostream>
#include<vector>
using namespace std;
class Patient
{
    private:
        int patientID;
        string name;
    public:
        Patient(int patientID, string name)
        {
            this->patientID = patientID;
            this->name = name;
        }
        int getPatientId()
        {
            return patientID;
        }
        string getPatientName()
        {
            return name;
        }
};
class ThreadedPatientBST
{
    private:
        Patient* patient;
        ThreadedPatientBST* left;
        ThreadedPatientBST* right;
        bool leftThreaded;
        bool rightThreaded;
    public:
        ThreadedPatientBST(Patient* newPatient)
        {
            patient = newPatient;
            left = nullptr;
            right = nullptr;
            leftThreaded = false;
            rightThreaded = false;
        }
        void insertPatient(Patient* newPatient) 
        {
            ThreadedPatientBST* current = this;
            ThreadedPatientBST* parent = nullptr;
            
            while (current != nullptr) 
            {
                parent = current;
                if (newPatient->getPatientId() < current->patient->getPatientId()) 
                {
                    current = current->left;
                } 
                else 
                {
                    current = current->right;
                }
            }

            if (newPatient->getPatientId() < parent->patient->getPatientId()) 
            {
                parent->left = new ThreadedPatientBST(newPatient);
            } 
            else 
            {
                parent->right = new ThreadedPatientBST(newPatient);
            }

            if (parent->left == nullptr) 
            {
                parent->left = parent->right;
                parent->leftThreaded = true;
            }

            if (parent->right == nullptr) 
            {
                parent->right = parent->left;
                parent->rightThreaded = true;
            }
        }
        void inorderTraversal() 
        {
            ThreadedPatientBST* current = this;

            while (current != nullptr) 
            {
                while (current->left != nullptr && !current->leftThreaded) 
                {
                    current = current->left;
                }

                cout<<"Patient ID: "<<current->patient->getPatientId()<<", Name: "<<current->patient->getPatientName()<<endl;

                if (current->rightThreaded) 
                {
                    current = current->right;
                } 

                else 
                {
                    current = current->right;
                }
            }
        }
        void removePatient(int patientID)
        {
            ThreadedPatientBST* parent = nullptr;
            ThreadedPatientBST* temp = this;
            while(temp != nullptr && temp->patient->getPatientId() != patientID)
            {
                parent = temp;
                if (patientID < temp->patient->getPatientId())
                {
                    temp = temp->left;
                }
                else
                {
                    temp = temp->right;
                }
            }
            if (temp == nullptr)
            {
                cout<<"Patient ID "<<patientID<<" not found." << endl;
                return;
            }
            if (temp->left == nullptr && temp->right == nullptr)
            {
                if (parent != nullptr)
                {
                    if (parent->left == temp)
                    {
                        parent->left = nullptr;
                    }
                    else
                    {
                        parent->right = nullptr;
                    }
                }
                delete temp;
                return;
            }
            if (temp->left == nullptr || temp->right == nullptr)
            {
                ThreadedPatientBST* child;
                if(temp->left != nullptr)
                {
                    child = temp->left;
                }
                else
                {
                    child = temp->right;
                }
                if (parent != nullptr)
                {
                    if (parent->left == temp)
                    {
                        parent->left = child;
                    }
                    else
                    {
                        parent->right = child;
                    }
                }
                delete temp;
                return;
            }
            ThreadedPatientBST* successor = temp->right;
            ThreadedPatientBST* successorParent = temp;

            while (successor->left != nullptr)
            {
                successorParent = successor;
                successor = successor->left;
            }

            temp->patient = successor->patient;

            if (successorParent->left == successor)
            {
                successorParent->left = successor->right;
            }
            else
            {
                successorParent->right = successor->right;
            }
            delete successor;
        }
};
class Department
{
    private:
        string deptName;
        ThreadedPatientBST* p;
        Department* left;
        Department* right;
    public:
        Department(string name)
        {
            deptName = name;
            p = nullptr;
            left = nullptr;
            right = nullptr;
        }
        void addPatient(Patient* patient)
        {
            if(p == nullptr)
            {
                p = new ThreadedPatientBST(patient);
                return;
            }
            else
            {
                p->insertPatient(patient);
            }
        }
        void removePatientFromDepartment(int patientID)
        {
            if (p != nullptr)
            {
                p->removePatient(patientID);
            }
            else
            {
                cout << "No patients found in the department to remove." << endl;
            }
        }
        void showPatients()
        {
            if(p!=nullptr)
            {
                cout<<"Patints in the department : "<<deptName<<endl;
                p->inorderTraversal();
            }
            else
            {
                cout<<"No patients are currently present in the department "<<deptName;
            }
        }
        void showDept()
        {
            cout<<"Department Name = "<<deptName<<endl;
            if(left != nullptr)
            {
                left->showDept();
            }
            if(right != nullptr)
            {
                right->showDept();
            }
        }  
        string getDeptName()
        {
            return deptName;
        }
        Department* getLeft()
        {
            return left;
        }
        Department* getRight()
        {
            return right;
        }
        void setLeft(Department* d)
        {
            left = d;
        }
        void setRight(Department* d)
        {
            right = d;
        }
};
int main() 
{
    vector<Department*> departments;
    int choice;
    while (true) {
        cout<<"\n--- Hospital Management System ---\n";
        cout<<"1. Add a new department\n";
        cout<<"2. Add a patient to a department\n";
        cout<<"3. Remove a patient from a department\n";
        cout<<"4. Show a department and its patients\n";
        cout<<"5. Show all departments and their patients\n";
        cout<<"6. Exit\n";
        cout<<"Enter your choice: ";
        cin>>choice;

        switch (choice) 
        {
            case 1: 
            {
                string deptName;
                cout<<"Enter the name of the new department: ";
                cin>>deptName;
                Department* newDept = new Department(deptName);
                departments.push_back(newDept);
                cout << "Department '" << deptName << "' added successfully.\n";
                break;
            }
            case 2: 
            {
                string deptName, patientName;
                int patientID;
                cout << "Enter the department name: ";
                cin >> deptName;
                cout << "Enter patient ID: ";
                cin >> patientID;
                cout << "Enter patient name: ";
                cin >> patientName;

                bool found = false;
                for (Department* d : departments) 
                {
                    if (d->getDeptName() == deptName) 
                    {
                        d->addPatient(new Patient(patientID, patientName));
                        cout<<"Patient added successfully to "<<deptName<<".\n";
                        found = true;
                        break;
                    }
                }
                if (!found) 
                {
                    cout<<"Department not found.\n";
                }
                break;
            }
            case 3: 
            {
                string deptName;
                int patientID;
                cout<<"Enter the department name: ";
                cin>>deptName;
                cout<<"Enter patient ID to remove: ";
                cin>>patientID;

                bool found = false;
                for (Department* d : departments) 
                {
                    if (d->getDeptName() == deptName) 
                    {
                        d->removePatientFromDepartment(patientID);
                        found = true;
                        break;
                    }
                }
                if (!found) 
                {
                    cout<<"Department not found.\n";
                }
                break;
            }
            case 4: 
            {
                string deptName;
                cout<<"Enter the department name to display: ";
                cin >> deptName;

                bool found = false;
                for (Department* d : departments) 
                {
                    if (d->getDeptName() == deptName) 
                    {
                        d->showPatients();
                        found = true;
                        break;
                    }
                }
                if (!found) 
                {
                    cout<<"Department not found.\n";
                }
                break;
            }
            case 5: 
            {
                cout<<"\n--- Departments and their patients ---\n";
                for (Department* d : departments) 
                {
                    d->showPatients();
                }
                break;
            }
            case 6: 
            {
                cout<<"Exiting the program. Goodbye!\n";
                return 0;
            }
            default:
                cout<<"Invalid choice. Please try again.\n";
        }
    }
}