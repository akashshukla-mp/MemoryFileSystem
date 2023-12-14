#include <bits/stdc++.h>
#include "executeCommand.h"

using namespace std;

int main()
{
    // Creating the root of the file system tree.
    FileSystemNode *root = new FileSystemNode(NULL, "");

    // Setting the root node as a directory.
    root->type = 'd';

    // Initializing the current working directory (pwd) to the root.
    FileSystemNode *pwd = root;

    // Populating the file system tree with predefined directories and files.
    fileSystemTree(root);

    // Printing initial instructions.
    printInstructions();

    string cmd;
    cout << endl
         << pwd_str(root, pwd) << ">> ";

    // Command input loop
    while (getline(cin >> ws, cmd))
    {
        // Function call to execute the entered command
        executeCommand(root, pwd, cmd);
        cout << endl
             << pwd_str(root, pwd) << ">> ";
    }

    cout << endl;
    return 0;
}