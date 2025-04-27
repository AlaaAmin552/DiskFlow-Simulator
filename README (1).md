
# Disk Scheduling Simulator

## Introduction
This project is a disk scheduling simulator that implements three disk scheduling algorithms: FCFS (First-Come, First-Served), SCAN, and C-SCAN (Circular SCAN). It calculates the total head movement (seek time) and displays the order of cylinder visits for a given set of requests, initial head position, and number of cylinders, all provided by the user at runtime.

## Project Idea
The idea of this project is to simulate how a disk scheduling algorithm manages disk I/O requests efficiently. Disk scheduling is a critical component of operating systems to optimize the movement of the disk head, reducing seek time and improving performance. This simulator allows users to input their own disk requests, choose the scheduling algorithm, and observe the head movement and total seek time.

## Description
The program is written in C and provides an interactive interface for users to:

- Specify the number of cylinders (disk size, e.g., 100, 200, or 5000).
- Enter the number of requests (queue size).
- Input the cylinder requests (queue) and the initial head position.
- Choose one of the three algorithms (FCFS, SCAN, or C-SCAN) to run.

The program then calculates the total head movement (in cylinders) and prints the order of cylinder visits for the selected algorithm.

### The algorithms implemented are:

- **FCFS**: Services requests in the order they are received.
- **SCAN**: Moves the head toward higher cylinders until the maximum cylinder, then reverses to 0 to service remaining requests.
- **C-SCAN**: Moves the head toward higher cylinders until the maximum cylinder, jumps to 0 (without counting this movement), and services remaining requests from 0 upward.

## How It Works

### User Input:

- The user specifies the number of cylinders (e.g., 200 for a disk with cylinders 0 to 199).
- The user enters the number of requests (queue size).
- The user inputs the cylinder requests (e.g., 98, 183, 37, etc.) and the initial head position (e.g., 53).
- The user selects the algorithm to run (1 for FCFS, 2 for SCAN, 3 for C-SCAN).

### Processing:

- The program validates all inputs to ensure they are within the valid range (e.g., requests and head position must be between 0 and max_cylinders - 1).
- Based on the chosen algorithm, the program calculates the head movement:
  - **FCFS**: Processes requests in the order they are entered.
  - **SCAN**: Sorts requests, moves the head toward higher cylinders up to the maximum, then reverses to 0 to service remaining requests.
  - **C-SCAN**: Sorts requests, moves the head toward higher cylinders up to the maximum, jumps to 0, and services remaining requests from 0 upward.

### Output:

- The program prints the requests, initial head position, and maximum cylinder.
- It displays the order of cylinder visits (e.g., 53 → 65 → 67 → ...).
- It shows the total head movement (seek time) in cylinders.

## How to Run the Program

### Compile the Code:
```bash
gcc -o disk_scheduling disk_scheduling.c
```

### Run the Program:
```bash
./disk_scheduling
```

### Provide Inputs:

- Enter the number of cylinders (e.g., 200).
- Enter the number of requests (e.g., 8).
- Enter the initial head position (e.g., 53).
- Enter the requests (e.g., 98 183 37 122 14 124 65 67).
- Choose the algorithm (1 for FCFS, 2 for SCAN, 3 for C-SCAN).

### View the Output:

- The program will display the order of cylinder visits and the total head movement.

## Example

**Input:**
```
Enter the number of cylinders: 200
Enter the number of requests (queue size): 8
Enter the initial head position (0 to 199): 53
Enter the 8 requests (each between 0 and 199):
98 183 37 122 14 124 65 67
Choose the algorithm to run:
1. FCFS
2. SCAN
3. C-SCAN
Enter your choice (1-3): 3
```

**Output:**
```
Requests: 98 183 37 122 14 124 65 67
Initial head position: 53
Max cylinder: 199 (range 0 to 199)

Calculating head movements...
C-SCAN Order: 53 -> 65 -> 67 -> 98 -> 122 -> 124 -> 183 -> 199 -> 0 -> 14 -> 37

Total Head Movement (C-SCAN): 229 cylinders

Press Enter to exit...
```

## Requirements

- A C compiler (e.g., GCC) to compile and run the program.
- The program runs on any operating system that supports C (Windows, Linux, macOS).

## Notes

- The program includes input validation to ensure all values are within the valid range.
- The total head movement is calculated as the sum of absolute differences between consecutive head positions.
- The SCAN and C-SCAN algorithms sort the requests to optimize head movement.

## Team Members

This project was developed by:

- [Your Name] (Student) - Responsible for coding, testing, and documentation.
