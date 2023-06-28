#include <iostream>

using namespace std;

class Person{
    public:
    Person* next;
    Person* prev;
    string name;
    Person(){
        next = nullptr;
        prev = nullptr;
        name = "";
    }
    Person( string _name){
        next = nullptr;
        prev = nullptr;
        name = _name;
    }
};

class Waitlist{
    public:
        Person* head;
        Waitlist(){
            head = nullptr;
        }
        Waitlist(Person*& address){
            head = address;
        }
        Person* findPerson(string _name){
            Person* ptr = head;
            Person* temp = nullptr; 
            while(ptr != nullptr){
                if(ptr->name == _name){
                    temp = ptr;
                }
                ptr = ptr->next;
            }
            
            return temp;
        }
        void addPerson(Person* person){
            if(head == nullptr){
                head = person;
                return;
            }
            if(findPerson(person->name) != nullptr){
                cout << "Person already on waitlist. Please enter a different or similar name." << endl;
                return;
            }
            Person* ptr = head;
            while(ptr->next != nullptr){
                ptr = ptr->next;
            }
            ptr->next = person;
            person->prev = ptr;
            cout << "Person added to waitlist." << endl;
        }
        void adjustPlaceForward(string name, int _num){
            if(head == nullptr){
                cout << "There is no one on the waitlist." << endl;
                return;
            }
            if(findPerson(name) == nullptr){
                cout << "There is no one on the waitlist with that name." << endl;
                return;
            }
            Person* ptr = findPerson(name);
            
            if(ptr->prev == nullptr){
                cout << "This person is already at the top of the list." << endl;
                return;
            }

            Person* temp = ptr->prev;

            for(int i = 0; i < _num; i++){
                if(temp->prev == nullptr){
                    head->next = ptr->next;
                    ptr->next->prev = head;
                    ptr->next = head;
                    ptr->prev = head->prev;
                    head->prev = ptr;
                    head = ptr;
                    break;
                }

                temp->next = ptr->next;
                ptr->next = temp;
                ptr->prev = temp->prev;
                temp->prev = ptr;

                if(ptr->prev != nullptr){
                    ptr->prev->next = ptr;
                }

                if(temp->next != nullptr){
                    temp->next->prev = temp;
                }

                temp = ptr->prev;

            }
        }

        void adjustPlaceBackwards(string name, int _num){
            if(head == nullptr){
                cout << "There is no one on the waitlist." << endl;
                return;
            }
            if(findPerson(name) == nullptr){
                cout << "There is no one on the waitlist with that name." << endl;
                return;
            }
            Person* ptr = findPerson(name);
            
            if(ptr->next == nullptr){
                cout << "This person is already at the bottom of the list." << endl;
                return;
            }

            Person* temp = ptr->next;

            for(int i = 0; i < _num; i++){
                if(ptr->next == nullptr){
                    break;
                }
                if(ptr->prev == nullptr){
                    head->next = temp->next;
                    head->next->prev = head;
                    temp->next = head;
                    temp->prev = head->prev;
                    head->prev = temp;
                    head = temp;
                }
                else{
                    ptr->next = temp->next;
                    temp->next = ptr;
                    temp->prev = ptr->prev;
                    ptr->prev = temp;
                    temp->prev->next = temp;
                }

                if(ptr->next != nullptr){
                    ptr->next->prev = ptr;
                }

                temp = ptr->next;
            }

        }

        void prependPerson(Person* person){
            head->prev = person;
            person->next = head;
            head = person;
            cout << "Added person to the front of the waitlist." << endl;
        }

        void prependExistingPerson(string name){
            if(head == nullptr){
                cout << "There is no one on the waitlist." << endl;
                return;
            }
            if(findPerson(name) == nullptr){
                cout << "There is no one on the waitlist with that name." << endl;
                return;
            }
            Person* ptr = findPerson(name);
            if(ptr->prev == nullptr){
                cout << "This person is already on the top of the list." << endl;
                return;
            }
            if(ptr->next == nullptr){
                ptr->prev->next = ptr->next;
                ptr->prev = head->prev;
                head->prev = ptr;
                ptr->next = head;
            }
            else{
                ptr->prev->next = ptr->next;
                ptr->next->prev = ptr->prev;
                ptr->next = head;
                ptr->prev = head->prev;
                head->prev = ptr;
            }

            head = ptr;

        }

        void insertPersonAfter(Person* person, string name){
            if(head == nullptr){
                cout << "Insert failed. There is no one on the list." << endl;
                return;
            }
            if(findPerson(person->name) != nullptr){
                cout << "Person already on waitlist. Please enter a different or similar name." << endl;
                return;
            }
            if(findPerson(name) == nullptr){
                cout << "There is no one on the waitlist with that name." << endl;
                return;
            }
            Person* ptr = findPerson(name);
            Person* nextPtr = ptr->next;

            if(nextPtr == nullptr){
                ptr->next = person;
                person->prev = ptr;
            }
            else{
                ptr->next = person;
                nextPtr->prev = person;
                person->next = nextPtr;
                person->prev = ptr;
            }

            cout << "Person inserted into waitlist." << endl;
            
        }

        void moveToBottom(string name){
            if(head == nullptr){
                cout << "There is no one on the waitlist." << endl;
                return;
            }
            if(findPerson(name) == nullptr){
                cout << "There is no one on the waitlist with that name." << endl;
                return;
            }
            Person* ptr = findPerson(name);
            Person* lastPerson = head;

            while(lastPerson->next != nullptr){
                lastPerson = lastPerson->next;
            }

            if(ptr->next == nullptr){
                cout << "Person is already at the bottom of the list." << endl;
                return;
            }
            if(ptr->prev == nullptr){
                ptr->next->prev = ptr->prev;
                head = ptr->next;
            }
            else{
                ptr->prev->next = ptr->next;
                ptr->next->prev = ptr->prev;
            }

            ptr->next = nullptr;
            ptr->prev = lastPerson;
            lastPerson->next = ptr;
        }

        void swapPlaces(string name1, string name2){
            if(head == nullptr){
                cout << "There is no one on the waitlist." << endl;
                return;
            }
            if(findPerson(name1) == nullptr || findPerson(name2) == nullptr){
                cout << "Unable to swap. One or both names are not on the list." << endl;
                return;
            }
            if(head->next == nullptr){
                cout << "Unable to swap. There is only one person on the waitlist." << endl;
            }
            Person* ptr1 = findPerson(name1);
            Person* ptr2 = findPerson(name2);
            string temp;

            temp = ptr1->name;
            ptr1->name = ptr2->name;
            ptr2->name = temp;

        }

        void deletePerson(string name){
            if(head == nullptr){
                cout << "There is no one on the waitlist." << endl;
                return;
            }
            if(findPerson(name) == nullptr){
                cout << "There is no one on the waitlist with that name." << endl;
                return;
            }
            if(head->next == nullptr){
                head = nullptr;
                return;
            }
            Person* ptr = findPerson(name);

            if(ptr->prev == nullptr){
                ptr->next->prev = ptr->prev;
                head = ptr->next;
            }
            else if(ptr->next == nullptr){
                ptr->prev->next = ptr->next;
            }
            else{
                ptr->prev->next = ptr->next;
                ptr->next->prev = ptr->prev;
            }
            ptr->next = nullptr;
            ptr->prev = nullptr;
        }

        void displayWaitlist(){
            if(head == nullptr){
                cout << "There is no one on the waitlist." << endl << "---" << endl;
                return;
            }
            Person* ptr = head;
            int count = 1;
            while(ptr != nullptr){
                cout << count << " - " << ptr->name << endl;
                ptr = ptr->next;
                count++;
            }
            cout << "---" << endl;
        }


};


int main(){
    Waitlist w;
    int option, num;
    string name, name1;

    do{
        cout << endl;
        w.displayWaitlist();
        cout << "Welcome to the waitlist. Please choose one of the following options:" << endl << "---" << endl;
        cout << "1 - Add new person to waitlist" << endl;
        cout << "2 - Add new person to the front of the list" << endl;
        cout << "3 - Insert a new person to the list" << endl;
        cout << "4 - Move person forward" << endl;
        cout << "5 - Move person backward" << endl;
        cout << "6 - Move person to the front of the list" << endl;
        cout << "7 - Move person to the bottom of the list" << endl;
        cout << "8 - Swap two people" << endl;
        cout << "9 - Remove person from waitlist" << endl;
        cout << "10 - Clear Screen" << endl;

        cin >> option;
        cin.ignore();
        Person* person = new Person();

        switch(option){
            case 0:
                break;
            case 1:
                cout << "Enter the person's name you want to add:" << endl;
                getline(cin, name);
                person->name = name;
                w.addPerson(person);
                break;
            case 2:
                cout << "Enter the person's name you want to add to the front of the list:" << endl;
                getline(cin, name);
                person->name = name;
                w.prependPerson(person);
                break;
            case 3:
                cout << "Enter the person's name you want to add:" << endl;
                getline(cin, name);
                person->name = name;
                cout << "Enter the name of person on the list you want to add new person after:" << endl;
                getline(cin, name1);
                w.insertPersonAfter(person, name1);
                break;
            case 4:
                cout << "What is the person's name?" << endl;
                getline(cin, name);
                cout << "How many places do you want to move up?" << endl;
                cin >> num;
                w.adjustPlaceForward(name, num);
                break;
            case 5:
                cout << "What is the person's name?" << endl;
                getline(cin, name);
                cout << "How many places do you want to move down?" << endl;
                cin >> num;
                w.adjustPlaceBackwards(name, num);
                break;
            case 6:
                cout << "Who do you want to move to the top of the list?" << endl;
                getline(cin, name);
                w.prependExistingPerson(name);
                break;
            case 7:
                cout << "Who do you want to move to the bottom of the list?" << endl;
                getline(cin, name);
                w.moveToBottom(name);
                break;
            case 8:
                cout << "Which two people would you like to swap?" << endl;
                getline(cin, name);
                getline(cin, name1);
                w.swapPlaces(name, name1);
                break;
            case 9:
                cout << "Which person would you like to remove from the waitlist?" << endl;
                getline(cin, name);
                w.deletePerson(name);
                break;
            case 10:
                system("cls");
                break;
            default:
                cout << "Enter a valid option." << endl;

        }


    }
    while(option != 0);

    return 0;
}