
#include <bits/stdc++.h>
using namespace std;

string time_now();

// Class definition for FileSystemNode representing a node in the file system tree.
class FileSystemNode{

public:
    // Member variables for file or directory attributes.
    string name;
    list<string> content;
    char type;
    string cdate;
    string mdate;
    int perm;
    FileSystemNode* link;
    FileSystemNode* parent;
    FileSystemNode* child;

    // Constructor 
    FileSystemNode(FileSystemNode* pwd, string n)
    {
        name = n;
        cdate = mdate = time_now();
        perm = 6;
        link = NULL;
        child = NULL;
        parent = pwd;
    }
    
  // Member function to convert permission integer to a string representation.
    string get_perm()
    {
        string res;
        if (perm == 0) res = "---";
        else if (perm == 1) res = "--x";
        else if (perm == 2) res = "-w-";
        else if (perm == 3) res = "-wx";
        else if (perm == 4) res = "r--";
        else if (perm == 5) res = "r-x";
        else if (perm == 6) res = "rw-";
        else if (perm == 7) res = "rwx";

        return res;
    }
};


 // Function definition to get the current time in a formatted string.
string time_now()
{
    string res = "", temp;
    time_t now = time(0);
    tm *ltm = localtime(&now);

    res += to_string(ltm->tm_mday) + " ";

   // Mapping numerical month to corresponding three-letter abbreviation.

    int month = ltm->tm_mon + 1;
    if (month == 1) res += "Jan ";
    else if (month == 2) res += "Feb ";
    else if (month == 3) res += "Mar ";
    else if (month == 4) res += "Apr ";
    else if (month == 5) res += "May ";
    else if (month == 6) res += "Jun ";
    else if (month == 7) res += "Jul ";
    else if (month == 8) res += "Aug ";
    else if (month == 9) res += "Sep ";
    else if (month == 10) res += "Oct ";
    else if (month == 11) res += "Nov ";
    else if (month == 12) res += "Dec ";

    if (to_string(ltm->tm_hour).size() == 1) res += "0";
    res += to_string(ltm->tm_hour) + ":";
    if (to_string(ltm->tm_min).size() == 1) res += "0";
    res += to_string(ltm->tm_min);

    return res;
}