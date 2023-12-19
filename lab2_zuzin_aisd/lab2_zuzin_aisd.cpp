#include <iostream>
#include <cstdlib>

using namespace::std;

template <class T>
struct Node {
    T value;
    Node* next;
};

template <typename T>
class LinkedList {
private:
    Node<T>* head;
    int size;

public:
    LinkedList() : head(nullptr), size(0) {}

    LinkedList(const LinkedList<T>& other) {
        head = nullptr;
        size = 0;
        Node<T>* temp = other.head;
        while (temp != other.head) {
            push_tail(temp->value);
            temp = temp->next;
        }
    }

    LinkedList(int count) : head(nullptr), size(0) {
        for (int i = 0; i < count; i++) {
            push_tail(rand() % 100);
        }
    }

    Node<T>* get_head() {
        return head;
    }

    int get_size() {
        return size;
    }

    ~LinkedList() {
        while (head != nullptr) {
            pop_head();
        }
    }

    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {
            while (head != nullptr) {
                pop_head();
            }
            Node<T>* temp = other.head;
            while (temp != other.head) {
                push_tail(temp->value);
                temp = temp->next;
            }
        }
        return *this;
    }

    void push_tail(T value) {
        Node<T>* newNode = new Node<T>{ value, nullptr };
        if (head == nullptr) {
            head = newNode;
            head->next = head;
        }
        else {
            Node<T>* temp = head;
            while (temp->next != head) {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->next = head;
        }
        size++;
    }

    void push_tail(LinkedList<T>& other) {
        Node<T>* temp = other.get_head();
        do {
            push_tail(temp->value);
            temp = temp->next;
            size++;
        } while (temp != other.get_head());
        temp = get_head();
    }

    void push_head(T value) {
        Node<T>* newNode = new Node<T>{ value, nullptr };
        if (head == nullptr) {
            head = newNode;
            head->next = head;
        }
        else {
            newNode->next = head;
            Node<T>* temp = head;
            while (temp->next != head) {
                temp = temp->next;
            }
            temp->next = newNode;
            head = newNode;
        }
        size++;
    }

    void push_head(LinkedList<T>& other) {
        Node<T>* temp = other.head;
        do {
            push_head(temp->value);
            temp = temp->next;
            size++;
        } while (temp != other.get_head());
        temp = get_head();
    }

    void pop_head() {
        if (head == nullptr) {
            return;
        }
        if (head->next == head) {
            delete head;
            head = nullptr;
        }
        else {
            Node<T>* temp = head;
            while (temp->next != head) {
                temp = temp->next;
            }
            temp->next = head->next;
            delete head;
            head = temp->next;
        }
        size--;
    }

    void pop_tail() {
        if (head == nullptr) {
            return;
        }
        if (head->next == head) {
            delete head;
            head = nullptr;
        }
        else {
            Node<T>* temp1 = head;
            Node<T>* temp2 = nullptr;
            while (temp1->next != head) {
                temp2 = temp1;
                temp1 = temp1->next;
            }
            delete temp1;
            temp2->next = head;
        }
        size--;
    }

    void delete_node(T val) {
        Node<T>* current = head;
        Node<T>* temp = nullptr;

        while (current != nullptr && current->value == val) {
            pop_head();
            current = head;
            size--;
        }

        while (current != nullptr) {
            while (current != nullptr && current->value != val) {
                temp = current;
                current = current->next;
                if (current == head) return;
            }
            if (current == nullptr) return;
            temp->next = current->next;

            delete current;

            current = temp->next;
        }
    }

    T& operator[](int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        Node<T>* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }

    T& operator[](int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        Node<T>* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->value;
    }

    void split_students(LinkedList<T>& juniors, LinkedList<T>& seniors) {
        if (head == nullptr) throw logic_error("list is empty");
        else {
            Node<T>* current = head;
            do {
                if ((current->value == 1 || current->value == 2) && current->value >= 1) {
                    juniors.push_tail(current->value);
                    current = current->next;
                }
                else if ((current->value == 3 || current->value == 4 || current->value == 5) && current->value <= 5) {
                    seniors.push_tail(current->value);
                    current = current->next;
                }
                else throw logic_error("input the normal course-number");
            } while (current != head);
        }
    }

    friend std::ostream& operator<<(std::ostream& os, LinkedList<T>& lst) {
        Node<T>* current = lst.get_head();
        if (current->next == nullptr) throw runtime_error("list is empty");
        do {
            os << current->value << " ";
            current = current->next;
        } while (current != lst.get_head());
        return os;
    }
};

template <typename T>
class Student {
    T course;
public:
    Student(T c) : course(c) {};

    int get_course() {
        return course;
    }

    bool operator==(T val) {
        if (course == val) return true;
        return false;
    }

    bool operator!=(T val) {
        if (course != val) return true;
        return false;
    }

    bool operator!=(Student<T> val) {
        if (course != val.get_course()) return true;
        return false;
    }

    bool operator==(Student<T> val) {
        if (course == val.get_course()) return true;
        return false;
    }

    bool operator>=(T val) {
        if (course >= val) return true;
        return false;
    }

    bool operator<=(T val) {
        if (course <= val) return true;
        return false;
    }

    friend std::ostream& operator<<(std::ostream& os, const Student& student) {
        os << student.course << "c "; // like course
        return os;
    }
};

int main() {
    Student<int> st1(1), st2(2), st3(3), st4(4), st5(5), std10(10);
    LinkedList<Student<int>> students, juniors, seniors;
    students.push_head(std10);
    cout << "get 0th el: " << students[0] << endl;
    students[0] = st1;
    cout << "rename 0th el as 1: " << students << endl;
    students.push_tail(st2);
    students.push_tail(st3);
    students.push_tail(st4);
    students.push_tail(st2);
    students.push_tail(st4);
    students.push_tail(st5);
    students.push_tail(st2);
    cout << students << endl;
    students.split_students(juniors, seniors);
    cout << "1-2th course: " << juniors << endl << "3-5th course: " << seniors << endl;
    cout << "start list: " << students << endl;
    students.pop_tail();
    cout << "delete last element: " << students << endl;
    students.pop_head();
    cout << "delete first element: " << students << endl;

    students.delete_node(3);
    cout << "delete all 3: " << students << endl;

    students.push_tail(juniors);
    cout << "append juniors to full list in tail 1-2th course: " << students << endl;
    students.push_head(seniors);
    cout << "append seniors to full list in head 3-5th course: " << students << endl;
    

}
