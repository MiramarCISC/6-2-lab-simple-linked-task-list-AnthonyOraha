#include "task_list.hpp"
#include <iostream>

using namespace std;

bool isValidPriority(int priority) {
    // TODO: Return true when priority is from 1 to 5.
    if(priority >= 1 && priority <= 5) return true;
    else return false;
}

Task createTask(string description, int priority) {
    Task task;

    // TODO:
    // Store the description.
    // Store the priority if valid; otherwise store 1.
    // New tasks should start as not completed.
    task.description = description;
    if(isValidPriority(priority)) {
        task.priority = priority;
    }
    else {
        task.priority = 1;
    }
    task.completed = false;
    return task;
}

void insertFront(TaskNode*& head, Task task) {
    // TODO:
    // Dynamically allocate a new TaskNode.
    // Store task in the node.
    // Point the new node to the old head.
    // Update head.
    TaskNode* newNode = new TaskNode;
    newNode->data = task;
    newNode->next = head;
    head = newNode;
}

int countTasks(const TaskNode* head) {
    // TODO: Traverse the list and count nodes.
    const TaskNode* current = head;
    int ctr = 0;
    while(current != nullptr) {
        ctr++;
        current = current->next;
    }
    return ctr;
}

TaskNode* findTask(TaskNode* head, string description) {
    // TODO:
    // Traverse the list.
    // Return the first node whose task description matches.
    // Return nullptr if not found.
    TaskNode* current = head;
    while(current != nullptr) {
        if(current->data.description == description) return current;
        current = current->next;
    }
    return nullptr;
}

bool markTaskComplete(TaskNode* head, string description) {
    // TODO:
    // Find the task.
    // If found, set completed to true and return true.
    // Otherwise return false.
    TaskNode* task = findTask(head, description);
    if(task != nullptr) {
        task->data.completed = true;
        return true;
    }
    return false;
}

int removeCompletedTasks(TaskNode*& head) {
    // TODO:
    // Remove all completed tasks.
    // Return the number of removed nodes.
    // Be sure to handle completed tasks at the head of the list.
    int ctr = 0;
    TaskNode* current = head;
    while(head != nullptr && current->data.completed == true) {
        head = current->next;
        delete current;
        current = head;
        ctr++;
    }
    if(current == nullptr) return ctr;
    TaskNode* after = current->next;
    while(after != nullptr) {
        if(after->data.completed == true) {
            current->next = after->next;
            delete after;    
            ctr++;
            after = current->next;
        } else {
            current = current->next;
            after = current->next;
        }
    }
    
    return ctr;
}

void clearTasks(TaskNode*& head) {
    // TODO:
    // Delete every node in the list.
    // Set head to nullptr.
    TaskNode* current = head;
    while(current != nullptr) {    
        TaskNode* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = nullptr;
}

void printTask(const Task& task) {
    cout << task.description
         << " | priority " << task.priority
         << " | " << (task.completed ? "complete" : "not complete")
         << endl;
}

void printTasks(const TaskNode* head) {
    if (head == nullptr) {
        cout << "No tasks." << endl;
        return;
    }

    const TaskNode* current = head;

    while (current != nullptr) {
        printTask(current->data);
        current = current->next;
    }
}
