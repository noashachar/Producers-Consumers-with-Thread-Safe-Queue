# Operating Systems - Assignment 3: Threads Synchronization

## Overview

This project implements a multi-threaded simulation of a news broadcasting system in C to demonstrate the use of threads synchronization mechanisms.

## System Design

![System Design](attachment:system-architecture.jpeg)

The system simulates the production, sorting, and display of news stories. Producers generate news stories which are passed to the Dispatcher. The Dispatcher sorts these into respective categories, which are then edited by Co-Editors before being displayed on the screen by the Screen Manager.

## Components

- **Producers**: Simulate news story creation.
- **Dispatcher**: Sorts stories by type.
- **Co-Editors**: Edit stories before public display.
- **Screen Manager**: Manages final story display output.

## Synchronization

For synchronization, I implemented a `BoundedBuffer` and an `UnboundedBuffer`. Also, I used native semaphores.

## Configuration

Uses a configuration file to set up the number of producers, queue sizes, and the number of products.

## How to Run

```bash
make
./ex3.out config.txt
```
