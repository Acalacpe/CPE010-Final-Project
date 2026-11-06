<div align="center">

<p><strong>CPE010 · DATA STRUCTURES AND ALGORITHMS</strong></p>

<h1>Student Enrollment<br>&amp; Grade Record System</h1>

<p>A C++ console application for student enrollment, subject selection,<br>and final grade recording for a school registrar.</p>

<p>
<img src="https://img.shields.io/badge/Language-C%2B%2B-00599C?style=for-the-badge" alt="Language: C++">
<img src="https://img.shields.io/badge/Interface-Console-334155?style=for-the-badge" alt="Interface: Console">
<img src="https://img.shields.io/badge/Stage-Testing-0F766E?style=for-the-badge" alt="Stage: Testing">
</p>

<p>
<a href="#overview">Overview</a> &nbsp;·&nbsp;
<a href="#features">Features</a> &nbsp;·&nbsp;
<a href="#data-structures-and-algorithms">Algorithms</a> &nbsp;·&nbsp;
<a href="#system-rules">System Rules</a> &nbsp;·&nbsp;
<a href="#development-plan">Development Plan</a>
</p>

</div>

---

> **Status:** Core features are implemented. Regression tests cover enrollment, grade history, and multi-file integration. Performance measurements and final documentation are pending.

## Overview

This project applies arrays, a stack, a queue, linear search, and insertion sort to a student enrollment and grade recording process. The design focuses on a small, single-user console program with clear operations and input validation.

## Features

| Feature | Behavior |
| :--- | :--- |
| **Enrollment** | Add an enrollment request with student details and selected subjects. |
| **Request Processing** | Process enrollment requests in first-in, first-out order. |
| **Grade Management** | Enter or update one final grade per enrolled subject. |
| **Student Search** | Search for a student by student number. |
| **Alphabetical Records** | Display enrolled students alphabetically by name. |
| **Grade Undo** | Undo the latest grade change across all students from the main menu. |

## Data Structures and Algorithms

| Topic | Application |
| :--- | :--- |
| **Arrays** | Store student details, selected subjects, and grades |
| **Stack** | Restore the previous grade when undoing a change |
| **Queue** | Process enrollment requests in arrival order |
| **Linear search** | Find a student by student number |
| **Insertion sort** | Arrange student records alphabetically |

## System Rules

| Item | Behavior |
| :--- | :--- |
| **Student numbers** | Entered manually, digits only; duplicates are rejected |
| **Available subjects** | English, Mathematics, and Science |
| **Subject selection** | One or more available subjects per student |
| **Grade entry** | One final grade per enrolled subject |
| **Grade range** | Whole numbers from **0–100** |
| **Passing grade** | **75** |
| **Unassigned grades** | Displayed as **Not yet graded** |
| **Users** | One registrar user |
| **Data storage** | In memory for the current session |
| **Application capacity** | 100 enrolled students and 50 pending requests |
| **Grade history capacity** | 50 changes; further updates are blocked until an undo frees space |

> Records are cleared when the program closes.

## Development Plan

| Phase | Work |
| :---: | :--- |
| **01** | Complete the theoretical documentation and system design. |
| **02** | Implement student records and the main menu. |
| **03** | Implement enrollment processing with a queue. |
| **04** | Implement grade entry and stack-based undo. |
| **05** | Implement searching, sorting, and input validation. |
| **06** | Test the program and capture actual outputs. |
| **07** | Measure performance and complete the documentation. |

## Performance Analysis

The project will examine the best, average, and worst-case time complexity and the space complexity of its main operations. Experimental measurements will be collected after implementation and compared with the theoretical analysis.

## Project Structure

| Location | Purpose |
| :--- | :--- |
| [`src/`](src/) | Application source files and main menu |
| [`benchmarks/`](benchmarks/) | Separate code for performance measurements |
| [`tests/`](tests/) | Test cases and sample inputs |
| [`docs/flowcharts/`](docs/flowcharts/) | System flowcharts |
| [`docs/screenshots/`](docs/screenshots/) | Actual program output screenshots |
| [`docs/performance/`](docs/performance/) | Measured results and performance graphs |

Source files are in `src/`, public headers are in `include/`, and regression checks are in `tests/`. Benchmark and output folders are reserved for measured results and actual screenshots.

## Main Menu

| Choice | Action |
| :---: | :--- |
| 1 | Add enrollment request |
| 2 | Process the next request |
| 3 | Display students alphabetically |
| 4 | Search a student, view a grade report, or enter/update/undo grades |
| 0 | Exit |
