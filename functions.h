#pragma once

// Save tasks to a file
void saveTasksToFile(const std::vector<Task>& tasks, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const Task& task : tasks) {
            file << task.serialize() << "\n";
        }
        file.close();
    }
}

// Load tasks from a file
std::vector<Task> loadTasksFromFile(const std::string& filename) {
    std::vector<Task> tasks;
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            Task task;
            task.deserialize(line);
            tasks.push_back(task);
        }
        file.close();
    }
    return tasks;
}


// Menu
void menu() {
    std::cout << "choose what you want to do" << std::endl;
    std::cout << "1. print todo List " << std::endl;
    std::cout << "2. add new task " << std::endl;
    std::cout << "3. update text of task " << std::endl;
    std::cout << "4. mark task as completed" << std::endl;
    std::cout << "5. delete todo list" << std::endl;
    std::cout << "6. clear command line" << std::endl;
    std::cout << "0. exit" << std::endl;
}