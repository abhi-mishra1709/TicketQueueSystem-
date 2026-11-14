// Ticket Queue System
// Data structure used: Queue (FIFO), implemented from scratch with a singly linked list.

#include <iostream>
#include <string>
#include <limits>
#include <ctime>
using namespace std;

// ---------- Node of the linked list (one ticket) ----------
struct Ticket
{
    int number;
    string name;
    string service;
    time_t issuedAt;
    Ticket *next;

    Ticket(int n, const string &nm, const string &sv)
        : number(n), name(nm), service(sv), issuedAt(time(nullptr)), next(nullptr) {}
};

// ---------- Queue implemented with front and rear pointers ----------
class TicketQueue
{
private:
    Ticket *front;
    Ticket *rear;
    int count;

public:
    TicketQueue() : front(nullptr), rear(nullptr), count(0) {}

    ~TicketQueue()
    {
        while (!isEmpty())
        {
            Ticket *t = dequeue();
            delete t;
        }
    }

    bool isEmpty() const { return front == nullptr; }
    int size() const { return count; }

    // Add a ticket at the rear: O(1)
    void enqueue(Ticket *t)
    {
        if (isEmpty())
        {
            front = rear = t;
        }
        else
        {
            rear->next = t;
            rear = t;
        }
        count++;
    }

    // Remove and return the ticket at the front: O(1)
    Ticket *dequeue()
    {
        if (isEmpty())
            return nullptr;
        Ticket *t = front;
        front = front->next;
        if (front == nullptr)
            rear = nullptr;
        t->next = nullptr;
        count--;
        return t;
    }

    // Look at the front ticket without removing it: O(1)
    const Ticket *peek() const { return front; }

    // Position of a ticket in the queue (1 = next to be served), -1 if absent: O(n)
    int positionOf(int number) const
    {
        int pos = 1;
        for (Ticket *cur = front; cur != nullptr; cur = cur->next, pos++)
            if (cur->number == number)
                return pos;
        return -1;
    }

    // Remove a ticket from anywhere in the queue: O(n)
    bool cancel(int number)
    {
        Ticket *prev = nullptr;
        Ticket *cur = front;
        while (cur != nullptr && cur->number != number)
        {
            prev = cur;
            cur = cur->next;
        }
        if (cur == nullptr)
            return false;

        if (prev == nullptr)
            front = cur->next; // removing the first node
        else
            prev->next = cur->next;
        if (cur == rear)
            rear = prev; // removing the last node
        delete cur;
        count--;
        return true;
    }

    void display() const
    {
        if (isEmpty())
        {
            cout << "  The queue is empty.\n";
            return;
        }
        cout << "  Pos | Ticket | Name            | Service\n";
        cout << "  ----+--------+-----------------+----------------\n";
        int pos = 1;
        for (Ticket *cur = front; cur != nullptr; cur = cur->next, pos++)
        {
            cout << "  " << pos << "   | #" << cur->number << "    | " << cur->name;
            for (size_t i = cur->name.size(); i < 15; i++)
                cout << ' ';
            cout << " | " << cur->service << "\n";
        }
    }
};

// ---------- Helpers ----------
int readInt(const string &prompt)
{
    int x;
    while (true)
    {
        cout << prompt;
        if (cin >> x)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return x;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  Please enter a number.\n";
    }
}

string readLine(const string &prompt)
{
    string s;
    cout << prompt;
    getline(cin, s);
    return s;
}

string chooseService()
{
    cout << "  Services: 1) Billing  2) Support  3) New Account  4) Other\n";
    int c = readInt("  Choose service (1-4): ");
    switch (c)
    {
    case 1:
        return "Billing";
    case 2:
        return "Support";
    case 3:
        return "New Account";
    default:
        return "Other";
    }
}

void printMenu()
{
    cout << "\n========== TICKET QUEUE SYSTEM ==========\n";
    cout << " 1. Issue a new ticket\n";
    cout << " 2. Serve next customer\n";
    cout << " 3. View next in line\n";
    cout << " 4. Display full queue\n";
    cout << " 5. Check my position\n";
    cout << " 6. Cancel a ticket\n";
    cout << " 7. Show summary\n";
    cout << " 0. Exit\n";
    cout << "=========================================\n";
}

int main()
{
    TicketQueue queue;
    int nextTicketNo = 1;
    int servedCount = 0;

    while (true)
    {
        printMenu();
        int choice = readInt("Enter your choice: ");

        switch (choice)
        {
        case 1:
        {
            string name = readLine("  Customer name: ");
            if (name.empty())
                name = "Guest";
            string service = chooseService();
            Ticket *t = new Ticket(nextTicketNo++, name, service);
            queue.enqueue(t);
            cout << "  Ticket #" << t->number << " issued to " << t->name
                 << ". People ahead of you: " << queue.size() - 1 << "\n";
            break;
        }
        case 2:
        {
            Ticket *t = queue.dequeue();
            if (t == nullptr)
            {
                cout << "  No customers waiting.\n";
            }
            else
            {
                cout << "  Now serving ticket #" << t->number << " - " << t->name
                     << " (" << t->service << ")\n";
                delete t;
                servedCount++;
            }
            break;
        }
        case 3:
        {
            const Ticket *t = queue.peek();
            if (t == nullptr)
                cout << "  No customers waiting.\n";
            else
                cout << "  Next in line: ticket #" << t->number << " - " << t->name
                     << " (" << t->service << ")\n";
            break;
        }
        case 4:
            queue.display();
            break;
        case 5:
        {
            int no = readInt("  Enter ticket number: ");
            int pos = queue.positionOf(no);
            if (pos == -1)
                cout << "  Ticket #" << no << " is not in the queue.\n";
            else
                cout << "  Ticket #" << no << " is at position " << pos
                     << " (" << pos - 1 << " ahead of you).\n";
            break;
        }
        case 6:
        {
            int no = readInt("  Enter ticket number to cancel: ");
            if (queue.cancel(no))
                cout << "  Ticket #" << no << " cancelled.\n";
            else
                cout << "  Ticket #" << no << " not found.\n";
            break;
        }
        case 7:
            cout << "  Tickets issued : " << nextTicketNo - 1 << "\n";
            cout << "  Customers served: " << servedCount << "\n";
            cout << "  Waiting now     : " << queue.size() << "\n";
            break;
        case 0:
            cout << "Goodbye!\n";
            return 0;
        default:
            cout << "  Invalid choice, try again.\n";
        }
    }
}