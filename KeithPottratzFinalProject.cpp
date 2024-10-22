/*
Keith Pottratz 10/20/2024
CS 300
Final Project
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

// Course structure to hold the course data
struct Course {
    std::string courseNumber;
    std::string courseName;
    std::vector<std::string> prerequisites;
};

// BST Node
struct Node {
    Course course;
    Node* left;
    Node* right;

    Node(Course c) : course(c), left(nullptr), right(nullptr) {}
};

// Binary Search Tree class
class BST {
private:
    Node* root;

    // In-order traversal to print courses in alphanumeric order
    void inOrder(Node* node) {
        if (node != nullptr) {
            inOrder(node->left);
            std::cout << "Course Number: " << node->course.courseNumber << ", "; 
            std::cout << "Course Name: " << node->course.courseName << "\n"; 
            if (!node->course.prerequisites.empty()) {
                std::cout << "Prerequisites: ";
                for (const auto& pre : node->course.prerequisites) { 
                    std::cout << pre << " ";
                }
                std::cout << "\n";
            }
            else {
                std::cout << "No prerequisites.\n";
            }
            inOrder(node->right);
        }
    }

    // Recursive insert
    Node* insert(Node* node, Course course) {
        if (node == nullptr) {
            return new Node(course);
        }
        if (course.courseNumber < node->course.courseNumber) {
            node->left = insert(node->left, course);
        }
        else {
            node->right = insert(node->right, course);
        }
        return node;
    }

    // Search for a course by its number
    Node* search(Node* node, const std::string& courseNumber) {
        if (node == nullptr || node->course.courseNumber == courseNumber) {
            return node;
        }
        if (courseNumber < node->course.courseNumber) {
            return search(node->left, courseNumber);
        }
        return search(node->right, courseNumber);
    }

public:
    BST() : root(nullptr) {}

    void insert(Course course) {
        root = insert(root, course); //Insert at the root
    }

	void printInOrder() { //Print the tree in order
        inOrder(root);
    }

    void searchCourse(const std::string& courseNumber) {  //searching the bst for the courseNumber
        Node* result = search(root, courseNumber);
        if (result != nullptr) {
            std::cout << "Course Number: " << result->course.courseNumber << "\n";
            std::cout << "Course Name: " << result->course.courseName << "\n";
            if (!result->course.prerequisites.empty()) {
                std::cout << "Prerequisites: ";
                for (const auto& pre : result->course.prerequisites) {
                    std::cout << pre << " ";
                }
                std::cout << "\n";
            }
            else {
                std::cout << "No prerequisites.\n";
            }
        }
        else {
            std::cout << "Course not found.\n";
        }
    }
};

// Load data from the CSV file into the BST
void loadData(const std::string& fileName, BST& bst) {
    std::ifstream file(fileName);
	if (!file.is_open()) {
		std::cout << "Error opening file" << std::endl;
		return;
	}
    std::string line;

    while (std::getline(file, line)) { 
        std::stringstream ss(line);
        std::string courseNumber, courseName, prerequisite;
        std::getline(ss, courseNumber, ',');
        std::getline(ss, courseName, ',');

        Course course;
        course.courseNumber = courseNumber;
        course.courseName = courseName;

        while (std::getline(ss, prerequisite, ',')) {
            course.prerequisites.push_back(prerequisite);
        }

        bst.insert(course);
    }

    file.close();

	std::cout << "Data loaded successfully.\n" << fileName << std::endl;
}

int main() {
    BST bst;
	bool dataLoaded = false; // Added to check if data is loaded
    // Load the course data
    loadData("../CS 300 ABCU_Advising_Program_Input.csv", bst);

    int choice = 0; // Menu choices. 
    while (choice != 9) {
        std::cout << "\nMenu:\n";
        std::cout << "1. Load course data from file\n";
        std::cout << "2. Print all courses (alphanumeric order)\n";
        std::cout << "3. Print a course and its prerequisites\n";
        std::cout << "9. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

		//The function below handles invalid input that is unexpected and clears cin and ignores the input.
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input. Please try again.\n";
            continue;
                    }

        if (choice == 1) {
			loadData("CS 300 ABCU_Advising_Program_Input.csv", bst); // Load the .csv file directly

            }
		else if (choice == 2) {
			std::cout << "\nCourses in alphanumeric order:\n";  //orders the bst in alphanumeric order
			bst.printInOrder();
		}
        else if (choice == 3) {
            std::string courseNumber;
			std::cout << "Enter course number: "; //Searches directly for what ever course number is entered if valid
            std::cin >> courseNumber;
            bst.searchCourse(courseNumber);
        }
        else if (choice != 9) {
			std::cout << "Invalid option. Please try again.\n"; // exits the program and produces an error if wrong input is entered
        }
    }

    std::cout << "Exiting program...\n";
    return 0;
}
