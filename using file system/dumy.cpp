#include <bits/stdc++.h>
using namespace std;

template <typename T>
class _Entity
{
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

    T &_getsublist() { return _sublist; }

    void _setname(string name) { _name = name; }

    _Entity(int id, string name, string entity1, string entity2)
        : _id(id), _name(name), _entity1(entity1), _entity2(entity2) {}
};

template <typename T>
class _Node
{
private:
    T *_data;
    _Node *_next;

public:
    T *_getdata() { return _data; }
    _Node *_getnext() { return _next; }

    void _setnext(_Node *next) { _next = next; }
    _Node(T *data) : _data(data), _next(nullptr) {}
};

template <typename T>
class _Linkedlist
{
private:
    _Node<T> *_head;

public:
    _Node<T> *_get_head() { return _head; }
    _Linkedlist() : _head(nullptr) {}

    void add(T *data)
    {
        _Node<T> *newNode = new _Node<T>(data);
        if (_head == nullptr)
        {
            _head = newNode;
        }
        else
        {
            _Node<T> *curr = _head;
            while (curr->_getnext())
            {
                curr = curr->_getnext();
            }
            curr->_setnext(newNode);
        }
    }

    void display()
    {
        _Node<T> *curr = _head;
        while (curr)
        {
            cout << curr->_getdata()->_getid() << " "
                 << curr->_getdata()->_getname() << " "
                 << curr->_getdata()->_getentity1() << " "
                 << curr->_getdata()->_getentity2() << " " << endl;
            curr = curr->_getnext();
        }
    }

    T *findbyid(int x)
    {
        _Node<T> *curr = _head;
        while (curr)
        {
            if (curr->_getdata()->_getid() == x)
            {
                return curr->_getdata();
            }
            curr = curr->_getnext();
        }
        return nullptr;
    }

    void displayleadcontact()
    {
        _Node<T> *curr = _head;
        while (curr)
        {
            cout << "Lead info:" << endl;
            cout << curr->_getdata()->_getid() << " "
                 << curr->_getdata()->_getname() << " "
                 << curr->_getdata()->_getentity1() << " "
                 << curr->_getdata()->_getentity2() << " " << endl;

            cout << "Sub List:" << endl;
            auto &temp = curr->_getdata()->_getsublist();
            temp.display();

            curr = curr->_getnext();
        }
    }
};

class DataStorage
{
public:
    virtual void saveLeadsToFile(_Linkedlist<_Entity<_Linkedlist<_Entity<string>>>> &leadList) = 0;
    virtual void saveContactsToFile(_Linkedlist<_Entity<string>> &contactList, _Linkedlist<_Entity<_Linkedlist<_Entity<string>>>> &leadList) = 0;
    virtual void loadLeadsFromFile(_Linkedlist<_Entity<_Linkedlist<_Entity<string>>>> &leadList) = 0;
    virtual void loadContactsFromFile(_Linkedlist<_Entity<string>> &contactList, _Linkedlist<_Entity<_Linkedlist<_Entity<string>>>> &leadList) = 0;
    virtual ~DataStorage() = default;
};

class FileDataStorage : public DataStorage
{
public:
    void saveLeadsToFile(_Linkedlist<_Entity<_Linkedlist<_Entity<string>>>> &leadList) override
    {
        ofstream file("leads.txt");
        _Node<_Entity<_Linkedlist<_Entity<string>>>> *curr = leadList._get_head();
        while (curr)
        {
            auto *lead = curr->_getdata();
            file << lead->_getid() << "|" << lead->_getname() << "|"
                 << lead->_getentity1() << "|" << lead->_getentity2() << endl;
            curr = curr->_getnext();
        }
        file.close();
    }

    void saveContactsToFile(_Linkedlist<_Entity<string>> &contactList, _Linkedlist<_Entity<_Linkedlist<_Entity<string>>>> &leadList) override
    {
        ofstream file("contacts.txt");
        _Node<_Entity<_Linkedlist<_Entity<string>>>> *leadNode = leadList._get_head();
        while (leadNode)
        {
            _Entity<_Linkedlist<_Entity<string>>> *lead = leadNode->_getdata();
            int leadId = lead->_getid();
            _Node<_Entity<string>> *contactNode = lead->_getsublist()._get_head();
            while (contactNode)
            {
                _Entity<string> *contact = contactNode->_getdata();
                file << contact->_getid() << "|"
                     << contact->_getname() << "|"
                     << contact->_getentity1() << "|"
                     << contact->_getentity2() << "|"
                     << leadId << endl;
                contactNode = contactNode->_getnext();
            }
            leadNode = leadNode->_getnext();
        }
        file.close();
    }

    void loadLeadsFromFile(_Linkedlist<_Entity<_Linkedlist<_Entity<string>>>> &leadList) override
    {
        ifstream file("leads.txt");
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            int id;
            string name, phone, website;
            char delimiter;
            ss >> id >> delimiter;
            getline(ss, name, '|');
            getline(ss, phone, '|');
            getline(ss, website, '|');
            auto *lead = new _Entity<_Linkedlist<_Entity<string>>>(id, name, phone, website);
            leadList.add(lead);
        }
        file.close();
    }

    void loadContactsFromFile(_Linkedlist<_Entity<string>> &contactList, _Linkedlist<_Entity<_Linkedlist<_Entity<string>>>> &leadList) override
    {
        ifstream file("contacts.txt");
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            int id, leadId;
            string name, phone, email;
            char delimiter;
            ss >> id >> delimiter;
            getline(ss, name, '|');
            getline(ss, phone, '|');
            getline(ss, email, '|');
            ss >> leadId;
            auto *contact = new _Entity<string>(id, name, phone, email);
            contactList.add(contact);
            auto *lead = leadList.findbyid(leadId);
            if (lead)
            {
                lead->_getsublist().add(contact);
            }
        }
        file.close();
    }
};

class MemoryDataStorage : public DataStorage
{
private:
    map<int, _Entity<_Linkedlist<_Entity<string>>>> leadMemory;
    map<int, _Entity<string>> contactMemory;

public:
    void saveLeadsToFile(_Linkedlist<_Entity<_Linkedlist<_Entity<string>>>> &leadList) override
    {
        ofstream file("leads.txt");
        _Node<_Entity<_Linkedlist<_Entity<string>>>> *curr = leadList._get_head();
        while (curr)
        {
            auto *lead = curr->_getdata();
            leadMemory[lead->_getid()] = *lead;
            file << lead->_getid() << "|" << lead->_getname() << "|"
                 << lead->_getentity1() << "|" << lead->_getentity2() << endl;
            curr = curr->_getnext();
        }
        file.close();
    }

    void saveContactsToFile(_Linkedlist<_Entity<string>> &contactList, _Linkedlist<_Entity<_Linkedlist<_Entity<string>>>> &leadList) override
    {
        ofstream file("contacts.txt");
        _Node<_Entity<_Linkedlist<_Entity<string>>>> *leadNode = leadList._get_head();
        while (leadNode)
        {
            _Entity<_Linkedlist<_Entity<string>>> *lead = leadNode->_getdata();
            int leadId = lead->_getid();
            _Node<_Entity<string>> *contactNode = lead->_getsublist()._get_head();
            while (contactNode)
            {
                _Entity<string> *contact = contactNode->_getdata();
                contactMemory[contact->_getid()] = *contact;
                file << contact->_getid() << "|"
                     << contact->_getname() << "|"
                     << contact->_getentity1() << "|"
                     << contact->_getentity2() << "|"
                     << leadId << endl;
                contactNode = contactNode->_getnext();
            }
            leadNode = leadNode->_getnext();
        }
        file.close();
    }

    void loadLeadsFromFile(_Linkedlist<_Entity<_Linkedlist<_Entity<string>>>> &leadList) override
    {
        for (const auto &pair : leadMemory)
        {
            leadList.add(new _Entity<_Linkedlist<_Entity<string>>>(pair.second));
        }
    }

    void loadContactsFromFile(_Linkedlist<_Entity<string>> &contactList, _Linkedlist<_Entity<_Linkedlist<_Entity<string>>>> &leadList) override
    {
        for (const auto &pair : contactMemory)
        {
            contactList.add(new _Entity<string>(pair.second));
        }
    }
};

class _CRM
{
private:
    _Linkedlist<_Entity<_Linkedlist<_Entity<string>>>> leads;
    _Linkedlist<_Entity<string>> contacts;
    int _leadid = 0;
    int _contactid = 100;
    unique_ptr<DataStorage> dataStorage;

public:
    _CRM(bool useMemory)
    {
        if (useMemory)
        {
            dataStorage = make_unique<MemoryDataStorage>();
        }
        else
        {
            dataStorage = make_unique<FileDataStorage>();
        }

        dataStorage->loadLeadsFromFile(leads);
        dataStorage->loadContactsFromFile(contacts, leads);
    }

    ~_CRM()
    {
        dataStorage->saveLeadsToFile(leads);
        dataStorage->saveContactsToFile(contacts, leads);
    }

    void addLead()
    {
        string name, phone, website;
        cout << "Name:";
        cin >> name;
        cout << "Phone:";
        cin >> phone;
        cout << "Website:";
        cin >> website;
        auto *newNode = new _Entity<_Linkedlist<_Entity<string>>>(++_leadid, name, phone, website);
        leads.add(newNode);
    }

    void displayLeads()
    {
        cout << "Lead info:" << endl;
        leads.display();
    }

    void addContact()
    {
        string name, phone, gmail;
        cout << "Name:";
        cin >> name;
        cout << "Phone:";
        cin >> phone;
        cout << "gmail:";
        cin >> gmail;
        auto *newNode = new _Entity<string>(++_contactid, name, phone, gmail);
        contacts.add(newNode);

        cout << "Enter the Lead id you want to allocate:";
        int x;
        cin >> x;
        auto *lead = leads.findbyid(x);
        if (lead == nullptr)
        {
            cout << "Invalid Id" << endl;
            return;
        }
        lead->_getsublist().add(newNode);
    }

    void displayContacts()
    {
        cout << "Contacts info:" << endl;
        contacts.display();
    }

    void displayLeadsWithContacts()
    {
        leads.displayleadcontact();
    }
};

int main()
{
    _CRM manager(true); // Change to true for memory-based storage
    cout << "Enter 1 to add leads :" << endl;
    cout << "Enter 2 to add contacts :" << endl;
    cout << "Enter 3  to display leads :" << endl;
    cout << "Enter 4 to display contacts :" << endl;
    cout << "Enter 5 to display displayLeadsWithContacts:" << endl;
    cout << "Enter 6 to Exit :" << endl;
    int i = 0;
    while (i != 6)
    {
        int pos;
        cin >> pos;
        i = pos;
        switch (i)
        {
        case 1:
            manager.addLead();
            break;
        case 2:
            manager.addContact();
            break;
        case 3:
            manager.displayLeads();
            break;
        case 4:
            manager.displayContacts();
            break;
        case 5:
            manager.displayLeadsWithContacts();
            break;
        case 6:
            break;
        default:
            cout << "Invalid Code" << endl;
            break;
        }
    }
    return 0;
}
