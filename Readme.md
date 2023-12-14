##Memory File System

1. Running the Program in a Linux Environment

Ensure that you have a C++ compiler installed on your Linux system.
Place all the provided files (main.cpp, executeCommand.h, module.h, FileSystemNode.h) in the same directory.
Open a terminal in the directory containing the files.

Compile the program using the following command:
g++ main.cpp -o file_system

Run the compiled program:
./file_system

The program will start, and you can begin interacting with the file system.

3. Project Structure:

Structure of FileSystemNode:

name: Name of the file or directory.
content: Content of the file (for files) or list of child nodes (for directories).
type: 'd' for directory, '-' for file.
cdate: Creation date.
mdate: Last modification date.
perm: Permission level (integer representation).
link: Pointer to the next node in the same directory.
parent: Pointer to the parent directory.
child: Pointer to the first child node (for directories).

4. Functionality and Usage 

help: Print instructions on how to use the shell commands.
ls [directory]: List files and directories in the current or specified directory.
tree [directory]: Display the directory tree structure.
pwd: Print the current working directory.
cd [path]: Change the current directory.
find [name]: Find files or directories by name.
stat [file/directory]: Display information about a file or directory.
cp [source] [destination]: Copy file or directory.
mv [source] [destination]: Move file or directory.
mkdir [directory]: Create a new directory.
touch [file]: Create a new file.
rm [file/directory]: Remove file or directory.
cat [file]: Display the contents of a file.
edit [file]: Edit the content of a file.
chmod [permissions] [file/directory]: Change file or directory permissions.
exit: Exit the program.


5. Data Structures

The primary data structure used in this file system implementation is a linked list. Each directory (FileSystemNode) is represented as a node with pointers to its child nodes (child) and the next node in the same directory level (link). The linked list structure creates a hierarchical representation similar to a tree, facilitating navigation through the file system. The implementation is designed for simplicity and educational purposes, utilizing linked lists to model the directory structure efficiently.

Time Efficiency: The time complexity of most operations is proportional to the depth of the directory tree or the length of the linked list for a specific directory.

Memory Efficiency: The program uses memory efficiently by dynamically allocating nodes only when needed, minimizing memory consumption.
Best Case Time Complexity = Omega(1)
Average Case Time Complexity = Theta(logN)
Worst Case Time Complexity = O(n)

6. Advantages over Other Implementations:
This implementation provides a basic file system shell with common commands, mimicking Linux shell commands.
It is a simple and lightweight file system representation. The program is self-contained, with a modular structure, making it easy to understand and extend.