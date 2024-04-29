# Operating Systems - Assignment 3: Threads Synchronization

## Overview

This project implements a multi-threaded simulation of a news broadcasting system in C to demonstrate the use of threads synchronization mechanisms.

## System Design

![System Design](https://raw.githubusercontent.com/noashachar/Producers-Consumers-with-Thread-Safe-Queue/main/assets/system-architecture.jpeg)

The system simulates the production, sorting, and display of news stories. Producers generate news stories which are passed to the Dispatcher. The Dispatcher sorts these into respective categories, which are then edited by Co-Editors before being displayed on the screen by the Screen Manager.

## Components

- **Producers**: Simulate news story creation.
- **Dispatcher**: Sorts stories by type.
- **Co-Editors**: Edit stories before public display.
- **Screen Manager**: Manages final story display output.

## Implementation

For synchronization, I implemented a `BoundedBuffer` and an `UnboundedBuffer`. Also, I used native semaphores.

For parallelism, I used `pthreads`.

## Configuration

The following format is expected (non-numeric chars are ignored):
```
PRODUCER ID: 1
number of products: [number]
queue size: [number]

PRODUCER ID: 2
number of products: [number]
queue size: [number]

…

PRODUCER ID: [n]
number of products: [number]
queue size: [number]

Co-Editor Queue Size: [number]
```

## How to Run

```bash
git clone https://github.com/noashachar/Producers-Consumers-with-Thread-Safe-Queue
cd Producers-Consumers-with-Thread-Safe-Queue
make
./main config.txt
```
