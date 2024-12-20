#include<bits/stdc++.h>
using namespace std;

template <typename T>
class _Entity{
   private:
    int _id;
    string _name;
    string _entity1;
    string _entity2;
    T _sublist;
   public:
    int _getid() {return _id;}
    string _getname() {return _name;}
    string _getentity1() {return _entity1;}
    string _getentity2() {return _entity2;}

    T& _getsublist() {return _sublist;}

    void _setname(string name) {_name=name;}

    _Entity(int id,string name,string entity1,string entity2)
    : _id(id),_name(name),_entity1(entity1),_entity2(entity2){}
};

template <typename T>
class _Node{
  private:
    T* _data;
    _Node* _next;
  public:
    T* _getdata(){return _data;}
    _Node* _getnext(){return _next;}

    void _setnext(_Node* next) {_next=next;}
    _Node(T* data):_data(data),_next(nullptr) {}
};

template<typename T>
class _Linkedlist{
  private:
    _Node<T>* _head;
  public:
    _Linkedlist(): _head(nullptr) {}

    void add(T* data){
        _Node<T>* newNode=new _Node<T>(data);
        if(_head==nullptr)
        {
            _head=newNode;
        }
        else
        {
            _Node<T>* curr=_head;
            while(curr->_getnext())
            {
                curr=curr->_getnext();
            }
            curr->_setnext(newNode);
        }
    }
    void display(){
        _Node<T>* curr=_head;
        while(curr)
        {
            cout<<curr->_getdata()->_getid()<<" "<<
            curr->_getdata()->_getname()<<" "<<
            curr->_getdata()->_getentity1()<<" "<<
            curr->_getdata()->_getentity2()<<" "<<endl;
            curr=curr->_getnext();
        }
    }
    T* findbyid(int x){
        _Node<T>* curr=_head;
        while(curr)
        {
            if(curr->_getdata()->_getid()==x)
            {
                return curr->_getdata();
            }
            curr=curr->_getnext();
        }
        return nullptr;
    }
    void displayleadcontact(){
        _Node<T>* curr=_head;
        while(curr)
        {
            cout<<"Lead info:"<<endl;
    cout<<curr->_getdata()->_getid()<<" "<<
            curr->_getdata()->_getname()<<" "<<
            curr->_getdata()->_getentity1()<<" "<<
            curr->_getdata()->_getentity2()<<" "<<endl;

            cout<<"Sub List:"<<endl;
    auto& temp=curr->_getdata()->_getsublist();
   temp.display();

            curr=curr->_getnext();
        }
    }
};
class _CRM{
    private:
     _Linkedlist<_Entity<_Linkedlist<_Entity<string>>>>leads;
     _Linkedlist<_Entity<string>>contacts;
     int _leadid=0;
     int _contactid=100;
    public:
    void addLead(){
            string name,phone,website;
            cout<<"Name:";
            cin>>name;
            cout<<"Phone:";
            cin>>phone;
            cout<<"Website:";
            cin>>website;
  auto* newNode=new _Entity<_Linkedlist<_Entity<string>>>
               (++_leadid,name,phone,website);
             leads.add(newNode);
     }
    void displayLeads(){ cout<<"Lead info:"<<endl;
leads.display();}
    void addContact(){
         string name,phone,gmail;
         cout<<"Name:";
         cin>>name;
         cout<<"Phone:";
         cin>>phone;
         cout<<"gmail:";
         cin>>gmail;
         auto* newNode=new _Entity<string>(++_contactid,name,phone,gmail);
         contacts.add(newNode);

    cout<<"Enter the Lead id you want to allocated:";
    int x;cin>>x;
         auto* lead=leads.findbyid(x);
         if(lead==nullptr)
         {
             cout<<"Invalid Id"<<endl;
             return;
         }
         lead->_getsublist().add(newNode);

   }
    void displayContacts(){ cout<<"Contacts info:"<<endl;
                contacts.display();
          }
    void displayLeadsWithContacts() {
        leads.displayleadcontact();
    }
    void searchlead(){
        cout<<"Enter the Lead ID :";
        int id; cin>>id;
        auto* temp=leads.findbyid(id);
        if(temp==nullptr)
        {
            cout<<"NOT Available"<<endl;
            return;
        }
        else
        {
            cout<<temp->_getid()<<" "<<
            temp->_getname()<<" "<<temp->_getentity1()<<" "<<
            temp->_getentity2()<<endl;
        }
    }
    void searchcontact(){
        cout<<"Enter the Contact ID :";
        int id; cin>>id;
        auto* temp=contacts.findbyid(id);
        if(temp==nullptr)
        {
            cout<<"NOT Available"<<endl;
            return;
        }
        else
        {
            cout<<temp->_getid()<<" "<<
            temp->_getname()<<" "<<temp->_getentity1()<<" "<<
            temp->_getentity2()<<endl;
        }
    }
    void updatelead(){
        cout<<"Enter the Lead ID :";
        int ID; cin>>ID;
        auto* temp=leads.findbyid(ID);
        cout<<"Lead Info:";
        cout<<temp->_getid()<<" "<<
            temp->_getname()<<" "<<temp->_getentity1()<<" "<<
            temp->_getentity2()<<endl;
        cout<<"Enter New Name:";string name;cin>>name;
        temp->_setname(name);
        cout<<"Successfully Updated"<<endl;
    }
    void updatecontact(){
        cout<<"Enter the Contact ID :";
        int ID; cin>>ID;
        auto* temp=contacts.findbyid(ID);
        cout<<"Lead Info:";
        cout<<temp->_getid()<<" "<<
            temp->_getname()<<" "<<temp->_getentity1()<<" "<<
            temp->_getentity2()<<endl;
        cout<<"Enter New Name:";string name;cin>>name;
        temp->_setname(name);
        cout<<"Successfully Updated"<<endl;
    }
};
int main()
{
    _CRM manager;
     cout<<"Enter 1 to add leads :"<<endl;
    cout<<"Enter 2 to add contacts :"<<endl;
    cout<<"Enter 3 to search leads :"<<endl;
    cout<<"Enter 4 to search contacts :"<<endl;
    cout<<"Enter 5  to update leads :"<<endl;
    cout<<"Enter 6 to update contacts:"<<endl;
    cout<<"Enter 7  to display leads :"<<endl;
    cout<<"Enter 8 to display contacts :"<<endl;
    cout<<"Enter 9 to display displayLeadsWithContacts:"<<endl;
    cout<<"Enter 10 to Exit :"<<endl;
    int i=0;
     while(i!=10)
    {
        int pos;
        cin>>pos;
        i=pos;
        switch(i)
        {
        case 1:
        {
            manager.addLead();
            break;
        }
        case 2:
        {
            manager.addContact();
            break;
        }
        case 3:
        {
           manager.searchlead();
            break;
        }
        case 4:
        {
            manager.searchcontact();
            break;
        }
        case 5:
        {
            manager.updatelead();
            break;
        }
        case 6:
        {
           manager.updatecontact();
            break;
        }
        case 7:
        {
            manager.displayLeads();
            break;
        }
        case 8:
        {
           manager.displayContacts();
            break;
        }
        case 9:
        {
            manager.displayLeadsWithContacts();
            break;
        }
        case 10:
        {
            break;
        }
        default:
        {
            cout<<"Invalid Code"<<endl;
            break;
        }
        }
    }
    // cout<<endl;

}
