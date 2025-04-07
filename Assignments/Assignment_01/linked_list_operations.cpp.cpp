#include <iostream>
#include <string>
using namespace std;

// Task Node structure
struct Task {
    int id; // Unique Task ID
    string description; // Task Description
    int priority; // Task Priority (Higher value = Higher priority)
    Task* next; // Pointer to next task
};

class TaskManager {
private:
    Task* head; // Head of the task list
public:
    TaskManager() { head = nullptr; }

    // Add a new task sorted by priority (higher priority first)
    void addTask(int id, string desc, int priority) {
        Task* newTask = new Task{id, desc, priority, nullptr};

        // If the list is empty or the new task has the highest priority, insert at head
        if (!head || head->priority < priority) {
            newTask->next = head;
            head = newTask;
            return;
        }

        // Traverse the list to find the correct position
        Task* temp = head;
        while (temp->next && temp->next->priority >= priority) {
            temp = temp->next;
        }
        newTask->next = temp->next;
        temp->next = newTask;
    }

    // Remove the highest priority task (head of the list)
    void removeHighestPriorityTask() {
        if (head == NULL) {
            cout << "No tasks available!" << endl;
            return;
        }
        Task* temp = head;
        head = head->next;
        delete temp;
        cout << "Highest priority task removed!" << endl;
    }

    // Remove a task by its ID
    void removeTaskById(int id) {
        if (!head) {
            cout << "No tasks available!" << endl;
            return;
        }

        // If the head task is the one to be removed
        if (head->id == id) {
            Task* temp = head;
            head = head->next;
            delete temp;
            cout << "Task removed!" << endl;
            return;
        }

        // Traverse the list to find the task
        Task* temp = head;
        while (temp->next && temp->next->id != id) {
            temp = temp->next;
        }

        // If task was not found
        if (!temp->next) {
            cout << "Task not found!" << endl;
            return;
        }

        // Remove the task
        Task* toDelete = temp->next;
        temp->next = temp->next->next;
        delete toDelete;
        cout << "Task removed!" << endl;
    }

    // Display all tasks in the list
    void viewTasks() {
        if (head == NULL) {
            cout << "No tasks available!" << endl;
            return;
        }
        Task* temp = head;
        while (temp) {
            cout << "ID: " << temp->id << " | Desc: " << temp->description << " | Priority: " << temp->priority << endl;
            temp = temp->next;
        }
    }
};

int main() {
    TaskManager tm;
    int choice, id, priority;
    string desc;

    while (true) {
        // Display menu options
        cout << "\nTask Management System" << endl;
        cout << "1. Add Task\n2. View Tasks\n3. Remove Highest Priority Task\n4. Remove Task by ID\n5. Exit\nChoose: ";
        cin >> choice;

        switch (choice) {
            case 1:
                // Input task details
                cout << "Enter Task ID: "; cin >> id;
                cin.ignore();
                cout << "Enter Task Description: "; getline(cin, desc);
                cout << "Enter Task Priority: "; cin >> priority;
                tm.addTask(id, desc, priority);
                break;
            case 2:
                // View all tasks
                tm.viewTasks();
                break;
            case 3:
                // Remove highest priority task
                tm.removeHighestPriorityTask();
                break;
            case 4:
                // Remove task by ID
                cout << "Enter Task ID to remove: "; cin >> id;
                tm.removeTaskById(id);
                break;
            case 5:
                // Exit program
                return 0;
            default:
                cout << "Invalid choice!" << endl;
        }
    }
}

