#pragma once


class Task {
public:
    Task() {}
    Task(const std::string& taskText, const std::string& deadlineStr)
    {
        m_text = taskText;
        m_completed = false;
        setDeadline(deadlineStr);
    }
    void setText(const std::string& taskText) {
        m_text = taskText;
    }
    std::string getText() {
        return m_text;
    }
    void setCompleted(bool state) {
        m_completed = state;
    }
    bool getCompleted() {
        return m_completed;
    }

    static bool isValidDateFormat(const std::string& dateStr) {
        std::regex dateRegex(R"(^\d{4}-\d{2}-\d{2}$)");
        return std::regex_match(dateStr, dateRegex);
    }
    bool setDeadline(const std::string& deadlineStr) {
        std::tm tm = {};
        if (sscanf_s(deadlineStr.c_str(), "%d-%d-%d", &tm.tm_year, &tm.tm_mon, &tm.tm_mday) == 3) {
            tm.tm_year -= 1900; // Adjust year
            tm.tm_mon -= 1;     // Adjust month

            m_deadline = std::chrono::system_clock::from_time_t(std::mktime(&tm));
            return true;
        }
        return false;
    }

    void display() const {
        std::cout << "Task: " << m_text << "\n";
        std::cout << "Status: " << (m_completed ? "completed" : "Not completed") << "\n";

        // Calculate time left
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        if (now < m_deadline) {
            std::chrono::duration<int> remainingTime = std::chrono::duration_cast<std::chrono::hours>(m_deadline - now);

            int remainingDays = remainingTime.count() / 24;
            int remainingHours = remainingTime.count() % 24;
            if (remainingDays < 1) {
                std::cout << "!! Warning: you have less than one day" << std::endl;
            }
            std::cout << "Time Left: " << remainingDays << " days and " << remainingHours << " hours\n";
        }
        else {
            std::cout << "deadline has passed.\n";
        }
    }
    std::string serialize() const {
        std::string status = m_completed ? "1" : "0";
        return m_text + ";" + status + ";" + std::to_string(std::chrono::duration_cast<std::chrono::seconds>(m_deadline.time_since_epoch()).count());
    }

    // Deserialize task from a string format
    void deserialize(const std::string& data) {
        size_t pos1 = data.find(';');
        size_t pos2 = data.find(';', pos1 + 1);

        m_text = data.substr(0, pos1);
        m_completed = (data[pos1 + 1] == '1');
        int epochSeconds = std::stoi(data.substr(pos2 + 1));
        m_deadline = std::chrono::system_clock::time_point(std::chrono::seconds(epochSeconds));
    }
private:
    std::string m_text;
    bool m_completed;
    std::chrono::system_clock::time_point m_deadline;
};
