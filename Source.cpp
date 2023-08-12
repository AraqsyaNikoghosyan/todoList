#include <string>
#include <chrono>
#include <regex>
#include <iostream>
#include <fstream>
#include "task.h"
#include  "functions.h"

int main() {
    std::vector<Task> todoList = loadTasksFromFile("todo.txt");
	int key{};
	int i{};
	std::string task_text;
	std::string deadlineStr;

	do {
		menu();
		std::cin >> key;
		switch (key) {
		case 1: {
			std::cout << "Todo List:\n";
			for (const Task& task : todoList) {
				std::cout <<"Index:" << i++ << std::endl;
				task.display();
				std::cout << "\n";
			}
			i = 0;
			break;
		}
		case 2: {
			std::cout << "Note: end input with '|' character" << std::endl;
			std::cout << "Enter task text: ";
			std::getline(std::cin, task_text, '|');

			do {
				std::cout << "Enter deadline (YYYY-MM-DD): ";
				std::getline(std::cin, deadlineStr);
			} while (!Task::isValidDateFormat(deadlineStr));

			Task newTask(task_text, deadlineStr);
			todoList.push_back(newTask);
			saveTasksToFile(todoList, "todo.txt");
			break;
		}
		case 3: {
			std::cout << "Note: end input with '|' character" << std::endl;
			std::cout << "Enter task index: ";
			std::cin >> i;
			std::cout << "Enter task text: ";
			std::getline(std::cin, task_text, '|');
			todoList[i].setText(task_text);
			saveTasksToFile(todoList, "todo.txt");
			break;
		}
		case 4: {
			std::cout << "Enter task index: ";
			std::cin >> i;
			todoList[i].setCompleted(true);
			saveTasksToFile(todoList, "todo.txt");
			break;
		}
		case 5: {
			todoList.clear();
			saveTasksToFile(todoList, "todo.txt");
			break;
		}
		

		case 6: {
			system("cls");
			break;
		}
		default:
			break;
		}
		if (key < 0 || key > 6) {
			std::cout << "no such command" << std::endl;
		}
	} while (key != 0);
	system("cls");

    return 0;
}