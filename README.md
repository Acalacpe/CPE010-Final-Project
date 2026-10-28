# Student Enrollment & Grade Record System

A C++ console application planned to support student enrollment, subject selection, and final grade recording for a school registrar.

> **Status:** Documentation and design are in progress. Implementation has not started.

## Overview

This project applies arrays, a stack, a queue, linear search, and insertion sort to a student enrollment and grade recording process. The design focuses on a small, single-user console program with clear operations and input validation.

## Planned Features

- Add an enrollment request with student details and selected subjects.
- Process enrollment requests in first-in, first-out order.
- Enter or update one final grade per enrolled subject.
- Search for a student by student number.
- Display enrolled students alphabetically by name.
- Undo the latest grade change.

## Data Structures and Algorithms

| Topic | Planned Application |
| --- | --- |
| Arrays | Store student details, selected subjects, and grades |
| Stack | Restore the previous grade when undoing a change |
| Queue | Process enrollment requests in arrival order |
| Linear search | Find a student by student number |
| Insertion sort | Arrange student records alphabetically |

## System Rules

| Item | Planned Behavior |
| --- | --- |
| Student numbers | Entered manually; duplicates are rejected |
| Available subjects | English, Mathematics, and Science |
| Subject selection | One or more available subjects per student |
| Grade entry | One final grade per enrolled subject |
| Grade range | 0–100 |
| Passing grade | 75 |
| Unassigned grades | Displayed as **Not yet graded** |
| Users | One registrar user |
| Data storage | In memory for the current session |

Records are cleared when the program closes.

## Development Plan

1. Complete the theoretical documentation and system design.
2. Implement student records and the main menu.
3. Implement enrollment processing with a queue.
4. Implement grade entry and stack-based undo.
5. Implement searching, sorting, and input validation.
6. Test the program and capture actual outputs.
7. Measure performance and complete the documentation.

## Performance Analysis

The project will examine the best, average, and worst-case time complexity and the space complexity of its main operations. Experimental measurements will be collected after implementation and compared with the theoretical analysis.

## Build and Run

Build and run instructions will be added after implementation.
