#include <bits/stdc++.h>
using namespace std;

template <typename T>
class _Entity {
private:
    int _id;
    string _name;
    string _entity1;
    string _entity2;
    T _sublist;

public:
    int _getid() { return _id; }
    string _getname() { return _name; }
    string _getentity1() { return _entity1; }
    string _getentity2() { return _entity2; }

    T& _getsublist() { return _sublist; }

    void _setname(string name) { _name = name; }

    _Entity(int id, string name, string entity1, string entity2)
        : _id(id), _name(name), _entity1(entity1), _entity2(entity2) {}
};

template <typename T>
class _Node {
private:
    T* _data;
    _Node* _next;

public:
    T* _getdata() { return _data; }
    _Node* _getnext() { return _next; }

    void _setnext(_Node* next) { _next = next; }
    _Node(T* data) : _data(data), _next(nullptr) {}
};

template <typename T>
class _Linkedlist {
private:
    _Node<T>* _head;

public:
     _Node<T>* _get_head() {return _head;}
    _Linkedlist() : _head(nullptr) {}

    void add(T* data) {
        _Node<T>* newNode = new _Node<T>(data);
        if (_head == nullptr) {
            _head = newNode;
        } else {
            _Node<T>* curr = _head;
            while (curr->_getnext()) {
                curr = curr->_getnext();
            }
            curr->_setnext(newNode);
        }
    }
    void display() {
        _Node<T>* curr = _head;
        while (curr) {
            cout << curr->_getdata()->_getid() << " "
                 << curr->_getdata()->_getname() << " "
                 << curr->_getdata()->_getentity1() << " "
                 << curr->_getdata()->_getentity2() << " " << endl;
            curr = curr->_getnext();
        }
    }
    T* findbyid(int x) {
        _Node<T>* curr = _head;
        while (curr) {
            if (curr->_getdata()->_getid() == x) {
                return curr->_getdata();
            }
            curr = curr->_getnext();
        }
        return nullptr;
    }
    void displayleadcontact() {
        _Node<T>* curr = _head;
        while (curr) {
            cout << "Lead info:" << endl;
            cout << curr->_getdata()->_getid() << " "
                 << curr->_getdata()->_getname() << " "
                 << curr->_getdata()->_getentity1() << " "
                 << curr->_getdata()->_getentity2() << " " << endl;

            cout << "Sub List:" << endl;
            auto& temp = curr->_getdata()->_getsublist();
            temp.display();

            curr = curr->_getnext();
        }
    }
};
class DataStorage {
public:
    virtual void saveLeadsToFile(const List<Lead>& leadList) = 0;
    virtual void saveContactsToFile(const List<Contact>& contactList, const List<Lead>& leadList) = 0;
    virtual void loadLeadsFromFile(List<Lead>& leadList) = 0;
    virtual void loadContactsFromFile(List<Contact>& contactList, List<Lead>& leadList) = 0;
    virtual ~DataStorage() = default;
};

class _CRM {
private:
    _Linkedlist<_Entity<_Linkedlist<_Entity<string>>>> leads;
    _Linkedlist<_Entity<string>> contacts;
    int _leadid = 0;
    int _contactid = 100;

    void saveLeadsToFile() {
        ofstream file("leads.txt");
        _Node<_Entity<_Linkedlist<_Entity<string>>>>* curr = leads._get_head();
        while (curr) {
            auto* lead = curr->_getdata();
            file << lead->_getid() << "|" << lead->_getname() << "|"
                 << lead->_getentity1() << "|" << lead->_getentity2() << endl;
            curr = curr->_getnext();
        }
        file.close();
    }

void saveContactsToFile() {
    ofstream file("contacts.txt");
    if (!file.is_open()) {
        cerr << "Error: Unable to open contacts.txt for writing." << endl;
        return;
    }

    // Iterate over leads
    _Node<_Entity<_Linkedlist<_Entity<string>>>>* leadNode = leads._get_head();
    while (leadNode) {
        _Entity<_Linkedlist<_Entity<string>>>* lead = leadNode->_getdata();
        int leadId = lead->_getid();

        // Iterate over contacts in the lead's sublist
        _Node<_Entity<string>>* contactNode = lead->_getsublist()._get_head();
        while (contactNode) {
            _Entity<string>* contact = contactNode->_getdata();
            file << contact->_getid() << "|" 
                 << contact->_getname() << "|"
                 << contact->_getentity1() << "|"
                 << contact->_getentity2() << "|"
                 << leadId << endl; // Save associated lead ID
            contactNode = contactNode->_getnext();
        }

        leadNode = leadNode->_getnext();
    }

    file.close();
}




    void loadLeadsFromFile() {
        ifstream file("leads.txt");
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            int id;
            string name, phone, website;
            char delimiter;
            ss >> id >> delimiter;
            getline(ss, name, '|');
            getline(ss, phone, '|');
            getline(ss, website, '|');
            auto* lead = new _Entity<_Linkedlist<_Entity<string>>>(id, name, phone, website);
            leads.add(lead);
            _leadid = max(_leadid, id);
        }
        file.close();
    }

    void loadContactsFromFile() {
        ifstream file("contacts.txt");
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            int id, leadId;
            string name, phone, email;
            char delimiter;
            ss >> id >> delimiter;
            getline(ss, name, '|');
            getline(ss, phone, '|');
            getline(ss, email, '|');
            ss >> leadId;
            auto* contact = new _Entity<string>(id, name, phone, email);
            contacts.add(contact);
            auto* lead = leads.findbyid(leadId);
            if (lead) {
                lead->_getsublist().add(contact);
            }
            _contactid = max(_contactid, id);
        }
        file.close();
    }

public:
    _CRM() {
        loadLeadsFromFile();
        loadContactsFromFile();
    }

    ~_CRM() {
        saveLeadsToFile();
        saveContactsToFile();
    }

    void addLead() {
        string name, phone, website;
        cout << "Name:";
        cin >> name;
        cout << "Phone:";
        cin >> phone;
        cout << "Website:";
        cin >> website;
        auto* newNode = new _Entity<_Linkedlist<_Entity<string>>>(++_leadid, name, phone, website);
        leads.add(newNode);
    }

    void displayLeads() {
        cout << "Lead info:" << endl;
        leads.display();
    }

    void addContact() {
        string name, phone, gmail;
        cout << "Name:";
        cin >> name;
        cout << "Phone:";
        cin >> phone;
        cout << "gmail:";
        cin >> gmail;
        auto* newNode = new _Entity<string>(++_contactid, name, phone, gmail);
        contacts.add(newNode);

        cout << "Enter the Lead id you want to allocate:";
        int x;
        cin >> x;
        auto* lead = leads.findbyid(x);
        if (lead == nullptr) {
            cout << "Invalid Id" << endl;
            return;
        }
        lead->_getsublist().add(newNode);
    }

    void displayContacts() {
        cout << "Contacts info:" << endl;
        contacts.display();
    }

    void displayLeadsWithContacts() {
        leads.displayleadcontact();
    }

    // Other CRM methods unchanged...
};

int main() {
    _CRM manager;
    cout << "Enter 1 to add leads :" << endl;
    cout << "Enter 2 to add contacts :" << endl;
    cout << "Enter 3 to search leads :" << endl;
    cout << "Enter 4 to search contacts :" << endl;
    cout << "Enter 5  to update leads :" << endl;
    cout << "Enter 6 to update contacts:" << endl;
    cout << "Enter 7  to display leads :" << endl;
    cout << "Enter 8 to display contacts :" << endl;
    cout << "Enter 9 to display displayLeadsWithContacts:" << endl;
    cout << "Enter 10 to Exit :" << endl;
    int i = 0;
    while (i != 10) {
        int pos;
        cin >> pos;
        i = pos;
        switch (i) {
            case 1:
                manager.addLead();
                break;
            case 2:
                manager.addContact();
                break;
            case 3:
                //manager.searchlead();
                break;
            case 4:
               // manager.searchcontact();
                break;
            case 5:
               // manager.updatelead();
                break;
            case 6:
              //  manager.updatecontact();
                break;
            case 7:
                manager.displayLeads();
                break;
            case 8:
                manager.displayContacts();
                break;
            case 9:
                manager.displayLeadsWithContacts();
                break;
            case 10:
                break;
            default:
                cout << "Invalid Code" << endl;
                break;
        }
    }
    return 0;
}
