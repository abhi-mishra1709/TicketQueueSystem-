# Ticket Queue System

A console-based ticket queue (token) system written in C++, built to demonstrate the **Queue** data structure, implemented from scratch using a singly linked list.

## Objectives
- Show how a Queue (First In, First Out) works in a real-life scenario.
- Implement the queue manually with `front` and `rear` pointers instead of using the STL.
- Practise dynamic memory allocation and linked-list traversal.

## Features
- Issue a new ticket (customer name and service type)
- Serve the next customer (dequeue)
- View who is next in line (peek)
- Display the full queue with positions
- Check the position of any ticket
- Cancel a ticket from anywhere in the queue
- Summary of tickets issued, served and waiting

## Data Structure Used
**Queue (FIFO) using a singly linked list**

| Operation | Description | Time complexity |
|---|---|---|
| `enqueue` | Add a ticket at the rear | O(1) |
| `dequeue` | Remove the ticket at the front | O(1) |
| `peek` | View the front ticket | O(1) |
| `positionOf` | Find a ticket's position | O(n) |
| `cancel` | Remove a ticket from any position | O(n) |

Each ticket is a node holding the ticket number, customer name, service and a `next` pointer. The `rear` pointer makes insertion O(1) without traversing the list.

## Real-Life Applications
Bank and hospital token counters, customer-support call queues, printer job queues, and ticket booking counters.

## How to Run
```bash
g++ -std=c++17 -o ticket_queue main.cpp
./ticket_queue
```

## Sample Output
```
1. Issue a new ticket
Customer name: Aman
Ticket #1 issued to Aman. People ahead of you: 0

2. Serve next customer
Now serving ticket #1 - Aman (Billing)
```

## Project Structure
```
ticket-queue-system/
├── main.cpp
└── README.md
```

## Author
<Name - Abhishek Mishra>, <Enroll - 22314803125>