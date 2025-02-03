const readline = require('readline');

// Create an interface for user input and output
const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
});

class Entity {
  constructor(id, name, entity1, entity2) {
    this.id = id;
    this.name = name;
    this.entity1 = entity1;
    this.entity2 = entity2;
    this.sublist = new LinkedList();
  }
}

class Node {
  constructor(data) {
    this.data = data;
    this.next = null;
  }
}

class LinkedList {
  constructor() {
    this.head = null;
  }

  add(data) {
    const newNode = new Node(data);
    if (!this.head) {
      this.head = newNode;
    } else {
      let current = this.head;
      while (current.next) {
        current = current.next;
      }
      current.next = newNode;
    }
  }

  display() {
    let current = this.head;
    while (current) {
      console.log(`${current.data.id} ${current.data.name} ${current.data.entity1} ${current.data.entity2}`);
      current = current.next;
    }
  }

  findById(id) {
    let current = this.head;
    while (current) {
      if (current.data.id === id) {
        return current.data;
      }
      current = current.next;
    }
    return null;
  }
}

class CRM {
  constructor() {
    this.leads = new LinkedList();
    this.contacts = new LinkedList();
    this.leadId = 1;
    this.contactId = 101;
  }

  // Function to handle user input and call the respective CRM functions
  askQuestion(query) {
    return new Promise((resolve) => rl.question(query, resolve));
  }

  async addLead() {
    const name = await this.askQuestion("Enter Lead Name: ");
    const phone = await this.askQuestion("Enter Phone: ");
    const website = await this.askQuestion("Enter Website: ");
    const newLead = new Entity(this.leadId++, name, phone, website);
    this.leads.add(newLead);
    console.log("Lead added successfully.");
  }

  async displayLeads() {
    console.log("Lead List:");
    this.leads.display();
  }

  async addContact() {
    const name = await this.askQuestion("Enter Contact Name: ");
    const phone = await this.askQuestion("Enter Phone: ");
    const email = await this.askQuestion("Enter Email: ");
    const newContact = new Entity(this.contactId++, name, phone, email);
    this.contacts.add(newContact);

    const leadId = parseInt(await this.askQuestion("Enter Lead ID to assign contact: "));
    const lead = this.leads.findById(leadId);
    if (!lead) {
      console.log("Invalid Lead ID");
      return;
    }
    lead.sublist.add(newContact);
    console.log("Contact added successfully and assigned to lead.");
  }

  async displayContacts() {
    console.log("Contact List:");
    this.contacts.display();
  }

  async displayLeadsWithContacts() {
    let current = this.leads.head;
    while (current) {
      console.log(`Lead Info: ${current.data.id} ${current.data.name} ${current.data.entity1} ${current.data.entity2}`);
      console.log("Contacts:");
      current.data.sublist.display();
      current = current.next;
    }
  }

  async searchLead() {
    const id = parseInt(await this.askQuestion("Enter Lead ID: "));
    const lead = this.leads.findById(id);
    if (!lead) {
      console.log("Lead Not Found");
      return;
    }
    console.log(`${lead.id} ${lead.name} ${lead.entity1} ${lead.entity2}`);
  }

  async searchContact() {
    const id = parseInt(await this.askQuestion("Enter Contact ID: "));
    const contact = this.contacts.findById(id);
    if (!contact) {
      console.log("Contact Not Found");
      return;
    }
    console.log(`${contact.id} ${contact.name} ${contact.entity1} ${contact.entity2}`);
  }

  async updateLead() {
    const id = parseInt(await this.askQuestion("Enter Lead ID: "));
    const lead = this.leads.findById(id);
    if (!lead) {
      console.log("Lead Not Found");
      return;
    }
    lead.name = await this.askQuestion("Enter New Name: ");
    console.log("Lead Successfully Updated");
  }

  async updateContact() {
    const id = parseInt(await this.askQuestion("Enter Contact ID: "));
    const contact = this.contacts.findById(id);
    if (!contact) {
      console.log("Contact Not Found");
      return;
    }
    contact.name = await this.askQuestion("Enter New Name: ");
    console.log("Contact Successfully Updated");
  }
}

const manager = new CRM();

async function main() {
  while (true) {
    const choice = parseInt(await manager.askQuestion(
      "Enter your choice:\n1. Add Lead\n2. Add Contact\n3. Search Lead\n4. Search Contact\n5. Update Lead\n6. Update Contact\n7. Display Leads\n8. Display Contacts\n9. Display Leads with Contacts\n10. Exit\n"
    ));

    if (choice === 10) break;

    switch (choice) {
      case 1:
        await manager.addLead();
        break;
      case 2:
        await manager.addContact();
        break;
      case 3:
        await manager.searchLead();
        break;
      case 4:
        await manager.searchContact();
        break;
      case 5:
        await manager.updateLead();
        break;
      case 6:
        await manager.updateContact();
        break;
      case 7:
        await manager.displayLeads();
        break;
      case 8:
        await manager.displayContacts();
        break;
      case 9:
        await manager.displayLeadsWithContacts();
        break;
      default:
        console.log("Invalid Choice");
    }
  }

  rl.close();  // Close the readline interface when done
}

main();
