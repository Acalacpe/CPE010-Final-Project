#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include "algorithms.h"
#include "enrollment.h"
#include "grades.h"
#include "helpers.h"
#include "student.h"

bool headersLinkInAnotherSource();

static void resetState() {
    studentCount = 0;
    qFront = 0;
    qCount = 0;
    gradeHistoryStack = GradeStack();
}

static Student makeStudent(const std::string& id, const std::string& name) {
    Student student;
    student.id = id;
    student.name = name;
    student.program = "CPE";
    student.year = 2;
    student.enrolled[0] = true;
    return student;
}

static void requestWithInput(const std::string& input) {
    std::istringstream source(input);
    std::streambuf* previous = std::cin.rdbuf(source.rdbuf());
    std::cin.clear();
    addRequest();
    std::cin.rdbuf(previous);
    std::cin.clear();
}

static void requestStudent(int id) {
    requestWithInput(std::to_string(id) + "\nStudent Name\nCPE\n2\ny\nn\nn\n");
}

int main() {
    std::ostringstream captured;
    std::streambuf* previousOutput = std::cout.rdbuf(captured.rdbuf());
    int checks = 0;

    assert(headersLinkInAnotherSource());
    checks++;

    GradeStack stack;
    GradeChange change = {"123", 0, NOT_GRADED, 80};
    GradeChange saved;
    assert(!stack.pop(saved) && !stack.peek(saved));
    for (int i = 0; i < MAX_STACK_SIZE; i++) assert(stack.push(change));
    assert(stack.isFull() && !stack.push(change));
    assert(stack.peek(saved) && saved.studentId == "123");
    for (int i = 0; i < MAX_STACK_SIZE; i++) assert(stack.pop(saved));
    assert(stack.isEmpty() && !stack.pop(saved));
    checks++;

    resetState();
    students[studentCount++] = makeStudent("123", "Student Name");
    for (int grade = 0; grade < MAX_STACK_SIZE; grade++) {
        assert(updateStudentGrade(0, 0, grade));
    }
    assert(!updateStudentGrade(0, 0, 50));
    assert(students[0].grades[0] == 49 && gradeHistoryStack.top == 49);
    assert(undoLatestGradeEdit() && students[0].grades[0] == 48);
    assert(updateStudentGrade(0, 0, 60));
    assert(undoLatestGradeEdit() && students[0].grades[0] == 48);
    checks++;

    resetState();
    students[studentCount++] = makeStudent("101", "Zulu");
    students[studentCount++] = makeStudent("202", "alpha");
    assert(updateStudentGrade(0, 0, 80));
    assert(updateStudentGrade(1, 0, 90));
    insertionSort();
    assert(students[0].id == "202");
    assert(undoLatestGradeEdit());
    assert(students[linearSearch("202")].grades[0] == NOT_GRADED);
    assert(students[linearSearch("101")].grades[0] == 80);
    assert(undoLatestGradeEdit());
    assert(students[linearSearch("101")].grades[0] == NOT_GRADED);
    assert(!undoLatestGradeEdit());
    checks++;

    resetState();
    students[studentCount++] = makeStudent("123", "Student Name");
    assert(updateStudentGrade(0, 0, 0));
    assert(gradeText(students[0], 0) == "0 (Failed)");
    assert(!updateStudentGrade(0, 0, 0) && gradeHistoryStack.top == 0);
    assert(undoLatestGradeEdit());
    assert(gradeText(students[0], 0) == "Not yet graded");
    assert(gradeText(students[0], 1) == "Not enrolled");
    checks++;

    assert(!updateStudentGrade(-1, 0, 80));
    assert(!updateStudentGrade(0, -1, 80));
    assert(!updateStudentGrade(0, NUM_SUBJECTS, 80));
    assert(!updateStudentGrade(0, 1, 80));
    assert(!updateStudentGrade(0, 0, -1));
    assert(!updateStudentGrade(0, 0, 101));
    assert(gradeHistoryStack.isEmpty() && students[0].grades[0] == NOT_GRADED);
    checks++;

    resetState();
    processNext();
    displayStudents();
    assert(studentCount == 0 && qCount == 0);
    requestStudent(123);
    requestWithInput("123\n");
    assert(qCount == 1);
    processNext();
    requestWithInput("123\n");
    assert(qCount == 0 && studentCount == 1 && students[0].id == "123");
    checks++;

    resetState();
    for (int id = 1; id <= MAX_REQUESTS; id++) requestStudent(id);
    requestWithInput("");
    assert(qCount == MAX_REQUESTS);
    for (int id = 1; id <= 25; id++) {
        processNext();
        assert(students[studentCount - 1].id == std::to_string(id));
    }
    for (int id = 51; id <= 75; id++) requestStudent(id);
    for (int id = 26; id <= 75; id++) {
        processNext();
        assert(students[studentCount - 1].id == std::to_string(id));
    }
    assert(studentCount == 75 && qCount == 0);
    checks++;

    resetState();
    studentCount = MAX_STUDENTS;
    requests[0] = makeStudent("101", "Waiting Student");
    qCount = 1;
    processNext();
    assert(studentCount == MAX_STUDENTS && qCount == 1 && qFront == 0);
    assert(requests[0].id == "101");
    checks++;

    Student records[5];
    records[0] = makeStudent("1", "Zulu");
    records[1] = makeStudent("2", "anna");
    records[2] = makeStudent("3", "Anna");
    records[3] = makeStudent("4", "Beta");
    records[4] = makeStudent("5", "alpha");
    records[0].enrolled[2] = true;
    records[0].grades[2] = 92;
    insertionSort(records, 5);
    assert(records[0].id == "5" && records[1].id == "2" && records[2].id == "3");
    assert(records[3].id == "4" && records[4].id == "1");
    assert(records[4].enrolled[2] && records[4].grades[2] == 92);
    assert(linearSearch(records, 5, "1") == 4);
    assert(linearSearch(records, 5, "missing") == -1);
    assert(linearSearch(records, 0, "1") == -1);
    checks++;

    Student* many = new Student[1000];
    for (int i = 0; i < 1000; i++) many[i].id = std::to_string(i);
    assert(linearSearch(many, 1000, "999") == 999);
    assert(linearSearch(many, 1000, "1000") == -1);
    delete[] many;
    checks++;

    std::istringstream menuInput("abc\n1.5\n6\n5\n");
    std::streambuf* previousInput = std::cin.rdbuf(menuInput.rdbuf());
    std::cin.clear();
    assert(askInt("Choice: ", 0, 5) == 5);
    std::cin.rdbuf(previousInput);
    std::cin.clear();
    checks++;

    resetState();
    students[studentCount++] = makeStudent("123", "Student Name");
    students[0].enrolled[1] = true;
    assert(updateStudentGrade(0, 0, 80));
    std::ostringstream report;
    std::streambuf* capturedOutput = std::cout.rdbuf(report.rdbuf());
    printGradeReportTable(0);
    std::cout.rdbuf(capturedOutput);
    assert(report.str().find("Not yet graded") != std::string::npos);
    assert(report.str().find("Overall remarks: Pending") != std::string::npos);
    assert(report.str().find("Overall remarks: PASSED") == std::string::npos);
    checks++;

    std::cout.rdbuf(previousOutput);
    std::cout << "All " << checks << " regression checks passed.\n";
    return 0;
}
