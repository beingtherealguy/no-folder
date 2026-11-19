#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main() {
    string filename = "students.csv";

    // 1. Write student records to CSV using fstream
    fstream file;
    file.open(filename, ios::out | ios::trunc);

    if (!file) {
        cout << "Error opening file for writing!" << endl;
        return 1;
    }

    file << "RollNo,Name,Marks,Status\n";
    file << "101,Aarav,85,PASS\n";

    // Save write pointer position before writing Roll 102's status
    file << "102,Meera,92,";
    streampos statusPos = file.tellp(); // tellp() gets current write position
    file << "HOLD\n";

    file << "103,Kabir,78,PASS\n";

    cout << "Total bytes written (tellp): " << file.tellp() << endl;

    // 2. Use seekp() to move write pointer back and update "HOLD" to "PASS"
    file.seekp(statusPos, ios::beg);
    file << "PASS";
    file.close();

    // 3. Read CSV records using fstream and demonstrate tellg() & seekg()
    file.open(filename, ios::in);
    if (!file) {
        cout << "Error opening file for reading!" << endl;
        return 1;
    }

    // Find total file size using seekg() and tellg()
    file.seekg(0, ios::end);
    streampos fileSize = file.tellg();
    cout << "Total file size (seekg + tellg): " << fileSize << " bytes\n" << endl;

    // Move read pointer back to the beginning of the file
    file.seekg(0, ios::beg);

    string line;
    streampos thirdRecordPos = 0;
    int lineNumber = 0;

    cout << "--- Reading All CSV Records ---" << endl;
    while (true) {
        streampos currentPos = file.tellg(); // tellg() gets current read offset
        if (!getline(file, line)) {
            break;
        }
        if (lineNumber == 3) {
            thirdRecordPos = currentPos; // Save byte offset of 3rd student (Kabir)
        }
        cout << "[Byte " << currentPos << "] " << line << endl;
        lineNumber++;
    }

    // 4. Jump directly to the 3rd student record using seekg()
    file.clear(); // Clear EOF flag before calling seekg()
    file.seekg(thirdRecordPos, ios::beg);

    getline(file, line);
    stringstream ss(line);
    string roll, name, marks, status;

    getline(ss, roll, ',');
    getline(ss, name, ',');
    getline(ss, marks, ',');
    getline(ss, status, ',');

    cout << "\n--- Direct Read Using seekg() ---" << endl;
    cout << "Roll: " << roll << " | Name: " << name
         << " | Marks: " << marks << " | Status: " << status << endl;

    file.close();
    return 0;
}
