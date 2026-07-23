#include "task_list.hpp"
#include <iostream>

using namespace std;

bool isValidPriority(int priority) {
    if (priority >= 1 && priority <= 5) {
        return true;
    }

    return false;
}

Task createTask(string description, int priority) {
    Task task;

    task.description = description;

    if (isValidPriority(priority)) {
        task.priority = priority;
    } else {
        task.priority = 1;
    }

    task.completed = false;

    return task;
}

// Creates a new node, points it to the old head, then makes it the new head
void insertFront(TaskNode*& head, Task task) {
    TaskNode* newNode = new TaskNode;

    newNode->data = task;
    newNode->next = head;
    head = newNode;
}

int countTasks(const TaskNode* head) {
    int count = 0;

    const TaskNode* current = head;

    while (current != nullptr) {
        count++;
        current = current->next;
    }

    return count;
}

TaskNode* findTask(TaskNode* head, string description) {
    TaskNode* current = head;

    while (current != nullptr) {
        if (current->data.description == description) {
            return current;
        }

        current = current->next;
    }

    return nullptr;
}

bool markTaskComplete(TaskNode* head, string description) {
    TaskNode* task = findTask(head, description);

    if (task != nullptr) {
        task->data.completed = true;
        return true;
    }

    return false;
}

// First removes completed tasks at the front, then walks the rest of the list
// connecting neighboring nodes before deleting each completed one
int removeCompletedTasks(TaskNode*& head) {
    int removed = 0;

    while (head != nullptr && head->data.completed) {
        TaskNode* temp = head;
        head = head->next;
        delete temp;
        removed++;
    }

    TaskNode* current = head;

    while (current != nullptr && current->next != nullptr) {
        if (current->next->data.completed) {
            TaskNode* temp = current->next;
            current->next = temp->next;
            delete temp;
            removed++;
        } else {
            current = current->next;
        }
    }

    return removed;
}

void clearTasks(TaskNode*& head) {
    while (head != nullptr) {
        TaskNode* temp = head;
        head = head->next;
        delete temp;
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