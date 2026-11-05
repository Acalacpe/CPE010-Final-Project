# Regression Checks

Build and run the regression executable using the commands in the root README.
Keep assertions enabled when running these tests.

The checks cover:

- Sharing headers between separate source files.
- Stack overflow, underflow, and peek behavior.
- Rejecting a grade update when history is full.
- Global undo after sorting or editing different students.
- Distinguishing a grade of zero from an ungraded subject.
- Invalid student, subject, and grade values.
- Rejecting duplicate pending and enrolled student IDs.
- Circular queue wraparound and FIFO order.
- Keeping a request when student storage is full.
- Case-insensitive, stable sorting of complete records.
- Searching an independent array larger than the console program's capacity.
- Rejecting invalid menu input.
- Showing pending remarks when some enrolled subjects are ungraded.
