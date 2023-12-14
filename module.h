#include <bits/stdc++.h>
#include "FileSystemNode.h"

// Function Declaration of all the functions

void fileSystemTree(FileSystemNode* root);
void printInstructions();
void print_tree(FileSystemNode* root, string prev);
void print_ls(FileSystemNode* pwd);
void print_stat(FileSystemNode* root, FileSystemNode* pwd, string path);
string pwd_str(FileSystemNode* root, FileSystemNode* pwd);
list<string> find_names(FileSystemNode* root, FileSystemNode* pwd, string name);
FileSystemNode* find_node(FileSystemNode* root, FileSystemNode* pwd, string path);
FileSystemNode* find_on_pwd(FileSystemNode* pwd, string name);
list<string> split(string str, char delim);
string join(list<string> str, char delim);
string* split_name(string str);
FileSystemNode* cd(FileSystemNode* root, FileSystemNode* pwd, string path);
FileSystemNode* create(FileSystemNode* root, FileSystemNode* pwd, string path, char type);
void remove(FileSystemNode* root, FileSystemNode* pwd, string path);
void dupl(FileSystemNode* root, FileSystemNode* pwd, string src, string dst, int keep);
void edit(FileSystemNode* root, FileSystemNode* pwd, string path);
void cat(FileSystemNode* root, FileSystemNode* pwd, string path);
void chmod(FileSystemNode* root, FileSystemNode* pwd, string path, string new_modes);

// Prints a set of instructions resembling Linux shell commands for the user.
void printInstructions()
{
    cout << "*** Follows the syntax of linux shell commands ***" << endl << endl;
    cout << "\thelp - print following message" << endl;
    cout << "\tls - list directory" << endl;
    cout << "\tcd - change directory" << endl;
    cout << "\ttree - display the files/directory in tree view" << endl;
    cout << "\tpwd - print working directory" << endl;
    cout << "\tfind - find file/directory path by name" << endl;
    cout << "\tstat - display file/directory information" << endl;
    cout << "\tcp - copy file" << endl;
    cout << "\tmv - move file" << endl;
    cout << "\tmkdir - make directory" << endl;
    cout << "\trmdir - remove directory" << endl;
    cout << "\ttouch - create file" << endl;
    cout << "\trm - remove file" << endl;
    cout << "\tcat - Display file content" << endl;
    cout << "\tedit - edit file" << endl;
    cout << "\tchmod - change file permission" << endl;
    cout << "\texit - exit program" << endl;
}

//Recursively prints the file system tree in a tree-view format, starting from the given root.
void print_tree(FileSystemNode* root, string prev)
{
    if (root != NULL)
    {
        string next, branch, branch_next;

        if (root->link == NULL)
        {
            branch = "`";
            branch_next = " ";
        }
        else
        {
            branch = "|";
            branch_next = "|";
        }
        if (prev == "")
        {
            cout << prev + branch << "-- " << root->name;
            next = prev + branch_next;
        }
        else
        {
            cout << prev + "   " + branch << "-- " << root->name;
            next = prev + "   " + branch_next;
        }
        
        if (root->type == 'd')
            cout << "/";
        cout << endl;

        print_tree(root->child, next);
        print_tree(root->link, prev);
    }
}

// Prints the contents of the current directory, including file types, permissions, modification dates, and names.
void print_ls(FileSystemNode* pwd)
{
    if (pwd != NULL)
    {
        cout << pwd->type << pwd->get_perm() << " " << pwd->mdate << " " << pwd->name;
        if (pwd->type == 'd') cout << "/";
        cout << endl;

        print_ls(pwd->link);
    }
}


//Displays information about a specified file or directory, such as name, type, access, modification, and creation dates.
void print_stat(FileSystemNode* root, FileSystemNode* pwd, string path)
{
    FileSystemNode* node = find_node(root, pwd, path);
    cout << "File: " << node->name;
    if (node->type == 'd') cout << "/";
    cout << endl;
    cout << "Access: " << node->type << node->get_perm() << endl;
    cout << "Modified: " << node->mdate << endl;
    cout << "Created: " << node->cdate << endl;
}

// Returns the current working directory as a string.
string pwd_str(FileSystemNode* root, FileSystemNode* pwd)
{
    string res = "";
    if (pwd == root)
        return "/";
    while (pwd != root)
    {
        res = "/" + pwd->name + res;
        pwd = pwd->parent;
    }
    return res;
}

// Finds and returns a list of file or directory paths that match the given name in the current working directory.
list<string> find_names(FileSystemNode* root, FileSystemNode* pwd, string name)
{
    static list<string> res;
    if (root == pwd)
        res.clear();
    if (pwd != NULL)
    {
        string path = pwd_str(root, pwd);
        if (path.find(name.c_str()) != string::npos)
        {
            res.push_back(path);
        }
        find_names(root, pwd->child, name);
        find_names(root, pwd->link, name);
    }
    return res;
}

// Finds and returns the node corresponding to the specified file or directory path.
FileSystemNode* find_node(FileSystemNode* root, FileSystemNode* pwd, string path)
{
    string parent_path = split_name(path)[0];
    string name = split_name(path)[1];
    pwd = cd(root, pwd, parent_path);
    if (pwd == NULL)
    {
       return NULL;
    }
    return find_on_pwd(pwd, name);
}

// Finds and returns the node with the specified name within the current working directory.
FileSystemNode* find_on_pwd(FileSystemNode* pwd, string name)
{
    pwd = pwd->child;
    while (pwd != NULL)
    {
        if (pwd->name == name)
        {
            return pwd;
        }
        pwd = pwd->link;
    }
    return NULL;
}

// Splits a string into a list of substrings based on the specified delimiter.

list<string> split(string str, char delim)
{
    list<string> res;
    string temp = "";
    for (int i = 0; i < (int)str.size(); i++)
    {
        if (str[i] != delim)
            temp += str[i];
        else
        {
            res.push_back(temp);
            temp = "";
        }
    }
    if (temp != "")
        res.push_back(temp);
    return res;
}

//  Joins a list of strings into a single string, using the specified delimiter.
string join(list<string> str, char delim)
{
    string res = "";
    for (list<string>::iterator it = str.begin(); it != str.end(); ++it)
    {
        res += *it;
        if (it != --str.end())
            res += delim;
    }
    return res;
}

// Splits a file or directory path into its parent path and name components.

string* split_name(string str)
{
    string* res = new string[2];

    list<string> temp = split(str, '/');
    res[1] = temp.back();
    temp.pop_back();
    res[0] = join(temp, '/');

    return res;
}

// Changes the current working directory based on the provided path.

FileSystemNode* cd(FileSystemNode* root, FileSystemNode* pwd, string path)
{
    list<string> path_list = split(path, '/');
    list<string>::iterator it = path_list.begin();
    FileSystemNode* temp;

    if (path[0] == '/')
    {
        temp = root;
        it++;
    }
    else if (path_list.front() == ".")
    {
        if (path_list.size() == 1)
            return pwd;
        else
        {
            temp = pwd;
            it++;
        }
    }
    else if (path_list.front() == "..")
    {
        if (path_list.size() == 1)
            return pwd->parent;
        else
        {
            temp = pwd->parent;
            it++;
        }
    }
    else
    {
        temp = pwd;
    }
    
    for (; it != path_list.end(); it++)
    {
        temp = find_on_pwd(temp, *it);
        if (temp == NULL || temp->type != 'd')
        {
            cout << "the directory '" << path << "' does not exist" << endl;
            return NULL;
        }
    }
    return temp;
}

// Creates a new file or directory at the specified path and returns its node.

FileSystemNode* create(FileSystemNode* root, FileSystemNode* pwd, string path, char type)
{
    string parent_path = split_name(path)[0];
    string name = split_name(path)[1];

    FileSystemNode* new_pwd = cd(root, pwd, parent_path);
    if (new_pwd == NULL)
    {
        cout << "the directory '" << parent_path << "' does not exist" << endl;
        return NULL;
    }

    FileSystemNode* temp = find_on_pwd(new_pwd, name);
    string choice = "";
    if (temp != NULL)
    {
        cout << "the file or directory '" << path << "' already exists" << endl;
        cout << "overwrite? (y/n) ";
        cin >> choice;
        if (choice != "y" && choice != "Y" && choice != "yes" && choice != "Yes")
            return NULL;
        remove(root, new_pwd, name);
    }

    temp = new FileSystemNode(new_pwd, name);
    temp->type = type;
    temp->parent = new_pwd;

    if (new_pwd->child == NULL)
    {
        new_pwd->child = temp;
        return temp;
    }
    FileSystemNode* prev = new_pwd->child;
    while (prev->link != NULL)
        prev = prev->link;
    prev->link = temp;

    return temp;
}

// Removes the file or directory at the specified path.

void remove(FileSystemNode* root, FileSystemNode* pwd, string path)
{
    FileSystemNode* temp = find_node(root, pwd, path);
    if (temp == NULL)
    {
        cout << "the file or directory '" << path << "' does not exist" << endl;
        return;
    }
    string choice = "";
    if (temp->type == 'd' && temp->child != NULL)
    {
        cout << "the directory '" << path << "' is not empty" << endl;
        cout << "proceed? (y/n) ";
        cin >> choice;
        if (choice != "y" && choice != "Y" && choice != "yes" && choice != "Yes")
            return;
    }

    if (temp->parent->child == temp)
    {
        temp->parent->child = temp->link;
        return;
    }
    FileSystemNode* prev = temp->parent->child;
    while (prev->link != temp)
        prev = prev->link;
    prev->link = temp->link;
}

// Duplicates a file or directory from the source to the destination, with an option to keep the original.

void dupl(FileSystemNode* root, FileSystemNode* pwd, string src, string dst, int keep)
{
    FileSystemNode* src_node = find_node(root, pwd, src);
    if (src_node == NULL)
    {
        cout << "the file or directory '" << src << "' does not exist" << endl;
        return;
    }
    string src_cdate = src_node->cdate;
    int src_perm = src_node->perm;
    list<string> src_content = src_node->content;

    FileSystemNode* dst_node = find_node(root, pwd, dst);
    if (dst_node != NULL && dst_node->type == 'd')
    {
        dst += "/" + src_node->name;
    }

    FileSystemNode* new_node = create(root, pwd, dst, src_node->type);
    if (new_node != NULL)
    {
        new_node->cdate = src_cdate;
        new_node->perm = src_perm;
        new_node->content = src_content;
    }
    else
        return;

    if (keep == 0)
    {
        remove(root, pwd, src);
    }

    return;
}

// Displays the content of a file at the specified path.

void cat(FileSystemNode* root, FileSystemNode* pwd, string path)
{
    FileSystemNode* temp = find_node(root, pwd, path);
    if (temp == NULL)
    {
        cout << "the file '" << path << "' does not exist" << endl;
        return;
    }
    if (temp->type != '-')
    {
        cout << "'" << path << "' is not a file" << endl;
        return;
    }
    if (temp->perm < 4)
    {
        cout << "you don't have permission to read '" << path << "'" << endl;
        return;
    }
    for (list<string>::iterator it = temp->content.begin(); it != temp->content.end(); it++)
        cout << *it << endl;
}


// Edits the content of a file at the specified path.

void edit(FileSystemNode* root, FileSystemNode* pwd, string path)
{
    FileSystemNode* temp = find_node(root, pwd, path);
    if (temp == NULL)
    {
        cout << "the file '" << path << "' does not exist" << endl;
        string choice = "";
        cout << "create it? (y/n) ";
        cin >> choice;
        if (choice != "y" && choice != "Y" && choice != "yes" && choice != "Yes")
            return;
        temp = create(root, pwd, path, '-');
    }
    if (temp->type != '-')
    {
        cout << "'" << path << "' is not a file" << endl;
        return;
    }

    if (!temp->content.empty())
    {
        if (temp->perm < 4)
        {
            cout << "you don't have permission to read '" << path << "'" << endl;
        }
        else
        {
            list<string> old_content = temp->content;
            cout << "content: " << endl;
            for (list<string>::iterator it = old_content.begin(); it != old_content.end(); it++)
                cout << *it << endl;
        }

        if (temp->perm < 2 || temp->perm == 4 || temp->perm == 5)
        {
            cout << "you don't have permission to write '" << path << "'" << endl;
            return;
        }
        
        string choice = "";
        cout << endl << "overwrite? (y/n) ";
        cin >> choice;
        if (choice != "y" && choice != "Y" && choice != "yes" && choice != "Yes")
            return;
    }

    temp->content.clear();
    cout << endl << temp->name << " : (enter \\n to save)" << endl;
    string line;
    while (1)
    {
        getline(cin, line);
        if (line == "\\n")
            break;
        temp->content.push_back(line);
    }
}

// Changes the permissions of a file or directory at the specified path.

void chmod(FileSystemNode* root, FileSystemNode* pwd, string path, string new_modes)
{
    FileSystemNode* temp = find_node(root, pwd, path);
    if (temp == NULL)
    {
        cout << "the file or directory '" << path << "' does not exist" << endl;
        return;
    }

    string perm_str = temp->get_perm();
    if (new_modes[0] == '+')
    {
        for (int i = 1; i < new_modes.size(); i++)
        {
            if (new_modes[i] == 'r' && perm_str.find('r') == string::npos)
                temp->perm += 4;
            else if (new_modes[i] == 'w' && perm_str.find('w') == string::npos)
                temp->perm += 2;
            else if (new_modes[i] == 'x' && perm_str.find('x') == string::npos)
                temp->perm += 1;
            else
                cout << "chmod: permission '" << new_modes[i] << "' already present or invalid\n";
        }
    }
    else if (new_modes[0] == '-')
    {
        for (int i = 1; i < new_modes.size(); i++)
        {
            if (new_modes[i] == 'r' && perm_str.find('r') != string::npos)
                temp->perm -= 4;
            else if (new_modes[i] == 'w' && perm_str.find('w') != string::npos)
                temp->perm -= 2;
            else if (new_modes[i] == 'x' && perm_str.find('x') != string::npos)
                temp->perm -= 1;
            else
                cout << "chmod: permission '" << new_modes[i] << "' already present or invalid\n";
        }
    }
    else if (new_modes.size() == 1 && new_modes[0] >= 48 && new_modes[0] <= 55)
    {
        temp->perm = new_modes[0]-48;
    }
    else
    {
        cout << "chmod: invalid permissions '" << new_modes << "'\n";
    }

}

// Builds a sample file system tree structure with predefined directories and files.

void fileSystemTree(FileSystemNode* root)
{
    vector<string> Dirs{"bin", "etc", "etc/systemd", "etc/systemd/system", "etc/systemd/user", 
        "home", "home/user", "home/user/Desktop", "home/user/Documents", "home/user/Downloads", 
        "home/user/Pictures", "tmp"};
    vector<string> Files{"bin/bash", "bin/cd", "bin/gcc", "bin/ls", "bin/python", 
        "etc/systemd/system/display-manager.service", "etc/systemd/system.conf", "etc/systemd/user.conf", 
        "etc/hosts", "etc/passwd", "etc/profile", "home/user/.bashrc"};

    for (string d : Dirs)
    {
        create(root, root, d, 'd');
    }
    for (string f : Files)
    {
        create(root, root, f, '-');
    }
}