#include<bits/stdc++.h>
using namespace std;
class _Contact{
  private: int _id;
  private: string _name;
  private: string _address;
  private: string _email;

  public: int _getid(){ return _id; }
  public: string _getname(){ return _name; }
  public: string _getaddress(){ return _address; }
  public: string _getemail(){ return _email; }

  public: void _setid(int id) { _id=id;}
  public: void _setname(string name) { _name=name;}
  public: void _setaddress(string address) { _address=address;}
  public: void _setemail(string email) { _email=email;}

  _Contact(int id,string name,string address,string email)
  : _id(id),_name(name),_address(address),_email(email) {}
};

class _Contactnode{
  public: _Contact* _data;
  public: _Contactnode* next;

public: _Contactnode(_Contact* data): _data(data),next(nullptr) {}
};

class _Contactlinkedlist{
   private: _Contactnode* _head;

   public: _Contactlinkedlist() :_head(nullptr) {}

   void add(_Contact* data)
   {
       _Contactnode* newNode=new _Contactnode(data);
       if(_head==nullptr)
       {
           _head=newNode;
       }
       else
       {
           _Contactnode* curr=_head;
           while(curr->next)
           {
               curr=curr->next;
           }
           curr->next=newNode;
       }
   }
   vector<_Contact*> _getelement()
   {
       vector<_Contact*>element;
       _Contactnode* curr=_head;
       while(curr)
       {
           element.push_back(curr->_data);
           curr=curr->next;
       }
       return element;
   }
   _Contact* _find(string name)
   {
       _Contactnode* curr=_head;
       while(curr)
       {
           if(curr->_data->_getname()==name)
           {
               return curr->_data;
           }
           curr=curr->next;
       }
       return nullptr;
   }
};
class _Lead{
  private: int _id;
  private: string _name;
  private: string _address;
  private: string _website;
  private: _Contactlinkedlist _Leadtocontact;

  public: int _getid() {return _id;}
  public: string _getname() {return _name;}
  public: string _getaddress() {return _address;}
  public: string _getwebsite() {return _website;}

  public: void _setid(int id){ _id=id;}
  public: void _setname(string name){ _name=name;}
  public: void _setaddress(string address){ _address=address;}
  public: void _setwebsite(string website){ _website=website;}

  _Lead(int id,string name,string address,string website)
  : _id(id),_name(name),_address(address),_website(website){}

  void _addcontact(_Contact* contact)
  {
      _Leadtocontact.add(contact);
  }
  vector<_Contact*> _getcontact()
  {
      return _Leadtocontact._getelement();
  }

};

class _Leadnode{
  public: _Lead* _data;
  public: _Leadnode* next;

public:_Leadnode(_Lead* data):_data(data),next(nullptr){}
};

class _Leadlinkedlist{
   private: _Leadnode* _head;

  public: _Leadlinkedlist(): _head(nullptr){}
  void add(_Lead* data)
  {
      _Leadnode* newNode=new _Leadnode(data);
      if(_head==nullptr)
      {
          _head=newNode;
      }
      else
      {
          _Leadnode* temp=_head;
          while(temp->next)
          {
              temp=temp->next;
          }
          temp->next=newNode;
      }
  }

  vector<_Lead*> _getelement()
  {
      vector<_Lead*> element;
      _Leadnode* curr=_head;
      while(curr)
      {
          element.push_back(curr->_data);
          curr=curr->next;
      }
      return element;
  }
  _Lead* _findleadbyid(int leadId)
  {
      _Leadnode* curr=_head;
      while(curr)
      {
          if(curr->_data->_getid()==leadId)
          {
              return curr->_data;
          }
          curr=curr->next;
      }
      return nullptr;
  }
  _Lead* _find(string name)
  {
      _Leadnode* curr=_head;
      while(curr)
      {
          if(curr->_data->_getname()==name)
          {
              return curr->_data;
          }
          curr=curr->next;
      }
      return nullptr;
  }

};

class LeadContactManager{
    private: _Leadlinkedlist leads;
    private: _Contactlinkedlist contacts;
    private: int _Leadid=1;
    private: int _Contactid=101;
  public:

  void _addcontact(string name,string address,string email){
      _Contact* newNode=new _Contact(_Contactid++,name,address,email);
      contacts.add(newNode);
  }

  void _displaycontact(){
      vector<_Contact*> linklist=contacts._getelement();
      cout<<"Contact list :"<<endl;
      for(auto i: linklist)
      {
          cout<<i->_getid()<<" "<<i->_getname()<<" "
          <<i->_getaddress()<<" "<<i->_getemail()<<endl;
      }
  }

  void _addlead(string name,string address,string website){
      _Lead* newNode=new _Lead(_Leadid++,name,address,website);
      leads.add(newNode);
    }
    void _displaylead()
    {
        vector<_Lead*> linklist=leads._getelement();
        cout<<"Lead list :"<<endl;
        for(auto i:linklist)
        {
            cout<<i->_getid()<<"  "<<i->_getname()<<"  "
            <<i->_getaddress()<<"  "<<i->_getwebsite()<<endl;
        }
    }

    void _associateContactWithLead(int leadId,vector<int> contactIds){
        _Lead* tempLead=leads._findleadbyid(leadId);
        if(!tempLead)
        {
            cout<<"Lead Not Found"<<endl;
            return;
        }
        vector<_Contact*> linklist=contacts._getelement();
        for(auto input: contactIds)
        {
            for(auto con_id:linklist)
            {
                if(input==con_id->_getid())
                {
                    tempLead->_addcontact(con_id);
                }
            }
        }
    }


    void _displayLeadWithContacts(int leadId)
    {
        _Lead* tempLead=leads._findleadbyid(leadId);
        if(!tempLead)
        {
            cout<<"Not Found"<<endl;
            return;
        }
        cout<<"Lead info :"<<endl;
        cout<<tempLead->_getid()<<" "<<tempLead->_getname()<<endl;
        vector<_Contact*> linklist=tempLead->_getcontact();
        cout<<"Contact info :"<<endl;
        for(auto i: linklist)
        {
            cout<<i->_getid()<<" "<<i->_getname()<<
            " "<<i->_getaddress()<<" "<<i->_getemail()<<endl;
        }

    }
    void _searchlead(string name)
    {
        _Lead* tempLead=leads._find(name);
        if(tempLead)
        {
        cout<<tempLead->_getid()<<" "<<tempLead->_getname()<<" "<<endl;
        }
        else
        {
            cout<<"Not Found"<<endl;
        }
    }
    void _searchcontach(string name)
    {
        _Contact* tempLead=contacts._find(name);
        if(tempLead)
        {
        cout<<tempLead->_getid()<<" "<<tempLead->_getname()<<" "<<endl;
        }
        else
        {
            cout<<"Not Found"<<endl;
        }
    }
    void _updatelead(string name)
    {
         _Lead* tempLead=leads._find(name);
        if(tempLead)
        {
            cout<<"Enter new Name :"<<endl;
            string name1;cin>>name1;
           tempLead->_setname(name1);
           _displaylead();
        }
        else
        {
            cout<<"Not Found"<<endl;
        }
    }
    void _updatecontact(string name)
    {
        _Contact* tempLead=contacts._find(name);
        if(tempLead)
        {
       cout<<"Enter new Name :"<<endl;
            string name1;cin>>name1;
           tempLead->_setname(name1);
           _displaycontact();
        }
        else
        {
            cout<<"Not Found"<<endl;
        }
    }

};
int main()
{
    LeadContactManager manager;
    manager._addlead("karim","moghbazar",".com");
    manager._addlead("jarim","moghbazar",".com");
    manager._addlead("marim","moghbazar",".com");
    manager._addlead("tarim","moghbazar",".com");
    manager._addlead("aarim","moghbazar",".com");

    manager._displaylead();

    manager._addcontact("azim","palton","gamil");
    manager._addcontact("bzim","palton","gamil");
    manager._addcontact("czim","palton","gamil");
    manager._addcontact("dzim","palton","gamil");
    manager._addcontact("fzim","palton","gamil");
    manager._addcontact("gzim","palton","gamil");
    manager._addcontact("hzim","palton","gamil");

    manager._displaycontact();

    manager._associateContactWithLead(1, {101, 102, 103});
    manager._associateContactWithLead(2, {104, 105});
    manager._associateContactWithLead(3, {106});
     manager._associateContactWithLead(1, {107});

    manager._displayLeadWithContacts(1);
    manager._displayLeadWithContacts(2);
    manager._displayLeadWithContacts(3);

    cout<<"Enter 1 to search Leadinfo:"<<endl;
    cout<<"Enter 2 to search Contactinfo:"<<endl;
    cout<<"Enter 3 to update Leadinfo:"<<endl;
    cout<<"Enter 4 to update Contactinfo:"<<endl;
    int x;cin>>x;
    switch(x)
    {
        case 1:{
            cout<<"Enter the name you want to search:"<<endl;
            string name1;cin>>name1;
            manager._searchlead(name1);
            break;
        }
        case 2:{
            cout<<"Enter the name you want to search:"<<endl;
            string name1;cin>>name1;
            manager._searchcontach(name1);
            break;
        }
         case 3:{
            cout<<"Enter the name you want to update:"<<endl;
            string name1;cin>>name1;
            manager._updatelead(name1);
            break;
        }
         case 4:{
            cout<<"Enter the name you want to update:"<<endl;
            string name1;cin>>name1;
            manager._updatecontact(name1);
            break;
        }
        default:
          cout<<"Invalid!"<<endl;
          break;
    }


}
