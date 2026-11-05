#ifndef GRADES_H
#define GRADES_H

void printGradeReportTable(int studentIndex);
bool updateStudentGrade(int studentIndex, int subjectIndex, int newGrade);
bool undoLatestGradeEdit();
void searchStudent();

#endif
