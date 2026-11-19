#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <string>

using namespace std;

struct Student {
    int roll;
    string name;
    double marks;
};

// Helper function for std::transform (adds 5 bonus marks, capped at 100)
Student addBonus(Student s) {
    s.marks += 5.0;
    if (s.marks > 100.0) {
        s.marks = 100.0;
    }
    return s;
}

// Helper function for std::sort (descending order of marks)
bool compareMarks(const Student& a, const Student& b) {
    return a.marks > b.marks;
}

// Helper function for std::find_if (checks for distinction >= 90)
bool isDistinction(const Student& s) {
    return s.marks >= 90.0;
}

char getGrade(double marks) {
    if (marks >= 85.0) return 'A';
    if (marks >= 70.0) return 'B';
    if (marks >= 50.0) return 'C';
    return 'F';
}

int main() {
    // 1. std::vector to store student dataset
    vector<Student> students = {
        {101, "Aarav", 78.0},
        {102, "Diya", 88.0},
        {103, "Rohan", 45.0},
        {104, "Sneha", 82.0}
    };

    // 2. std::transform to apply bonus marks
    transform(students.begin(), students.end(), students.begin(), addBonus);

    // 3. std::sort to rank students by marks (highest first)
    sort(students.begin(), students.end(), compareMarks);

    cout << "--- Ranked Student List (After +5 Bonus) ---" << endl;
    for (size_t i = 0; i < students.size(); i++) {
        cout << "Roll: " << students[i].roll
             << " | Name: " << students[i].name
             << " | Marks: " << students[i].marks
             << " | Grade: " << getGrade(students[i].marks) << endl;
    }

    // 4. std::find_if to find first student with >= 90 marks
    auto it = find_if(students.begin(), students.end(), isDistinction);
    if (it != students.end()) {
        cout << "\nFirst Distinction Student: " << it->name
             << " (" << it->marks << " marks)" << endl;
    }

    // 5. std::unordered_map for fast O(1) lookup by Roll Number
    unordered_map<int, Student> studentDirectory;
    for (size_t i = 0; i < students.size(); i++) {
        studentDirectory[students[i].roll] = students[i];
    }

    int searchRoll = 104;
    if (studentDirectory.find(searchRoll) != studentDirectory.end()) {
        cout << "Search Result for Roll " << searchRoll << ": "
             << studentDirectory[searchRoll].name << " - "
             << studentDirectory[searchRoll].marks << " marks" << endl;
    }

    // 6. std::map to store grade frequency in sorted order
    map<char, int> gradeCount;
    for (size_t i = 0; i < students.size(); i++) {
        char g = getGrade(students[i].marks);
        gradeCount[g]++;
    }

    cout << "\n--- Grade Summary (std::map) ---" << endl;
    for (auto gIt = gradeCount.begin(); gIt != gradeCount.end(); ++gIt) {
        cout << "Grade " << gIt->first << ": " << gIt->second << " student(s)" << endl;
    }

    return 0;
}
