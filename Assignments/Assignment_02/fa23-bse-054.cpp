
#include <iostream>
using namespace std;

class PatientNode
{
public:
  string name;
  int arrivalNo;
  string condition;
  int priority;
  PatientNode *next;

  PatientNode(string name, int arrivalNo, string condition, int priority)
  {
    this->name = name;
    this->arrivalNo = arrivalNo;
    this->condition = condition;
    this->priority = priority;
    next = NULL;
  }
};

class PatientList
{
public:
  PatientNode *head;
  PatientNode *tail;

  PatientList()
  {
    head = tail = NULL;
  }

  void addPatient(string name, int arrivalNo, string condition, int priority)
  {
    PatientNode *newPatient = new PatientNode(name, arrivalNo, condition, priority);

    // First patient
    if (head == NULL)
    {
      head = tail = newPatient;
      return;
    }

    // New highest priority
    if (priority < head->priority)
    {
      newPatient->next = head;
      head = newPatient;
      return;
    }

    PatientNode *current = head;
    PatientNode *previous = NULL;

    // Find correct position by priority
    while (current != NULL && current->priority <= priority)
    {
      previous = current;
      current = current->next;
    }

    previous->next = newPatient;
    newPatient->next = current;

    // New patient added at the end
    if (current == NULL)
    {
      tail = newPatient;
    }
  }

  void displayPatients()
  {
    cout << "\n Patient List \n";
    if (head == NULL)
    {
      cout << "No patients in the queue.\n";
      return;
    }

    PatientNode *current = head;
    while (current != NULL)
    {
      cout << "Name: " << current->name
           << " Arrival" << current->arrivalNo
           << " Condition:" << current->condition
           << " Priority: " << current->priority << "\n";
      current = current->next;
    }
    cout << "\n";
  }
};

int main()
{
  PatientList hospitalQueue;
  bool exitProgram = false;

  while (!exitProgram)
  {
    cout << "\n  Medical Emergency System \n";
    cout << "1. Register New Patient\n";
    cout << "2. View All Patients\n";
    cout << "3. Exit\n";
    cout << "\n";

    int choice;
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1)
    {
      cout << "\n Register New Patient n";
      string name;
      int arrivalNo;
      string condition;
      int priority;

      cout << "Enter Patient Name: ";
      cin >> name;

      cout << "Enter Arrival Number: ";
      cin >> arrivalNo;

      cout << "Enter Emergency Condition: ";
      cin.ignore();
      getline(cin, condition);

      if (condition == "Heart Attack" || condition == "Stroke")
        priority = 1;
      else if (condition == "Broken Leg" || condition == "Severe Burn" || condition == "Fractured Arm")
        priority = 2;
      else if (condition == "Fever" || condition == "Food Poisoning" || condition == "Migraine")
        priority = 3;
      else if (condition == "Mild Cold" || condition == "Small Cut")
        priority = 4;
      else
      {
        cout << "Invalid emergency condition entered. Please try again.\n";
        continue;
      }

      hospitalQueue.addPatient(name, arrivalNo, condition, priority);
      cout << "Patient added successfully!\n";
    }
    else if (choice == 2)
    {
      hospitalQueue.displayPatients();
    }
    else if (choice == 3)
    {
      cout << "Exiting the system. Stay safe!\n";
      exitProgram = true;
    }
    else
    {
      cout << "Invalid choice. Please select again.\n";
    }
  }

  return 0;
}
