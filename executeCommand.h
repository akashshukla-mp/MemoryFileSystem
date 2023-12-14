
#include <bits/stdc++.h>
#include "module.h"
using namespace std;

// // Function to execute a command based on the provided FileSystemNode, current working directory, and command string.
void executeCommand(FileSystemNode *root, FileSystemNode *&pwd, const string &cmd)
{
    list<string> args = split(cmd, ' ');
    FileSystemNode *temp_pwd;
    
    // Handling different commands using if else statements
    if (cmd == "help")
        printInstructions();
    else if (args.front() == "ls")
    {
        if (args.size() == 1)
            print_ls(pwd->child);
        else
            while (args.size() != 1)
            {
                args.pop_front();
                cout << args.front() << ":" << endl;
                temp_pwd = cd(root, pwd, args.front());
                if (temp_pwd != NULL)
                    print_ls(temp_pwd->child);
            }
    }
    else if (args.front() == "tree")
    {
        if (args.size() == 1)
            print_tree(pwd->child, "");
        else
            while (args.size() != 1)
            {
                args.pop_front();
                cout << args.front() << ":\n.\n";
                temp_pwd = cd(root, pwd, args.front());
                if (temp_pwd != NULL)
                    print_tree(temp_pwd->child, "");
            }
    }
    else if (cmd == "pwd")
        cout << pwd_str(root, pwd) << endl;
    else if (args.front() == "cd")
    {
        if (args.size() == 1)
            pwd = root;
        else
        {
            args.pop_front();
            temp_pwd = cd(root, pwd, args.front());
            if (temp_pwd != NULL)
                pwd = temp_pwd;
        }
    }
    else if (args.front() == "find")
    {
        if (args.size() == 1)
            cout << "find: missing operand" << endl;
        else
            while (args.size() != 1)
            {
                args.pop_front();
                list<string> res;
                if (args.front()[0] == '/')
                    res = find_names(root, root, args.front());
                else
                    res = find_names(pwd, pwd, args.front());
                if (res.size() == 0)
                    cout << "find: '" << args.front() << "': no such file or directory" << endl;
                else
                    for (list<string>::iterator it = res.begin(); it != res.end(); it++)
                        cout << *it << endl;
            }
    }
    else if (args.front() == "stat")
    {
        if (args.size() == 1)
            cout << "stat: missing operand" << endl;
        else
            while (args.size() != 1)
            {
                args.pop_front();
                print_stat(root, pwd, args.front());
            }
    }
    else if (args.front() == "mkdir")
    {
        if (args.size() == 1)
            cout << "mkdir: missing operand" << endl;
        else
            while (args.size() != 1)
            {
                args.pop_front();
                create(root, pwd, args.front(), 'd');
            }
    }
    else if (args.front() == "touch")
    {
        if (args.size() == 1)
            cout << "touch: missing operand" << endl;
        else
            while (args.size() != 1)
            {
                args.pop_front();
                create(root, pwd, args.front(), '-');
            }
    }
    else if (args.front() == "rm" || args.front() == "rmdir")
    {
        if (args.size() == 1)
            cout << args.front() << ": missing operand" << endl;
        else
            while (args.size() != 1)
            {
                args.pop_front();
                remove(root, pwd, args.front());
            }
    }
    else if (args.front() == "cp" || args.front() == "mv")
    {
        if (args.size() != 3)
            cout << args.front() << ": missing operand" << endl;
        else
        {
            int keep;
            if (args.front() == "cp")
                keep = 1;
            else
                keep = 0;
            args.pop_front();
            string src = args.front();
            args.pop_front();
            string dst = args.front();
            args.pop_front();
            dupl(root, pwd, src, dst, keep);
        }
    }
    else if (args.front() == "edit")
    {
        if (args.size() == 1)
            cout << "edit: missing operand" << endl;
        else
        {
            args.pop_front();
            edit(root, pwd, args.front());
        }
    }
    else if (args.front() == "cat")
    {
        if (args.size() == 1)
            cout << "cat: missing operand" << endl;
        else
        {
            args.pop_front();
            cat(root, pwd, args.front());
        }
    }
    else if (args.front() == "chmod")
    {
        if (args.size() < 3)
            cout << "chmod: missing operand" << endl;
        else
        {
            args.pop_front();
            string perm = args.front();
            args.pop_front();
            chmod(root, pwd, args.front(), perm);
        }
    }
    else if (cmd == "exit")
        exit(0);
    else
        cout << "Unknown command" << endl;
}