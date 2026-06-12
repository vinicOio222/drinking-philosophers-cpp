#pragma once

#include <iostream>
#include <fstream>
#include <mutex>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <string>


/**
* @brief A thread-safe logger class for logging messages to both console and file.
* Provides timestamped logging with mutex protection to ensure thread safety.
*/
class Logger {
    private:
        static std::mutex mtx; // Mutex to protect concurrent access to logging resources
        static std::ofstream fileStream; // File stream for logging to a file

        /**
         * @brief Generates a timestamp string in the format HH:MM:SS.mmm.
         * @return A string representing the current timestamp.
         */
        static std::string timestamp() {
            auto now = std::chrono::system_clock::now();
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                now.time_since_epoch()
            ) % 1000;
            auto t = std::chrono::system_clock::to_time_t(now);
            std::tm tm{};

#ifdef _WIN32
            localtime_s(&tm, &t);
#else
            localtime_r(&t, &tm);
#endif
            std::ostringstream oss; // Format the timestamp as HH:MM:SS.mmm
            oss << std::put_time(&tm, "%H:%M:%S")
                << '.' << std::setfill('0')
                << std::setw(3) << ms.count();
            return oss.str();
        }

    public:
        /**
         * @brief Initializes the logger by opening the specified file for writing.
         * @param filename The name of the file to open.
         */
        static void init(const std::string& filename) {
            std::lock_guard<std::mutex> lock(mtx);
            fileStream.open(filename, std::ios::out | std::ios::trunc);
        }

        /**
         * @brief Logs a message with a timestamp to both console and file.
         * @param message The message to log.
         */
        static void log(const std::string& message) {
            std::lock_guard<std::mutex> lock(mtx);
            std::string line = "[" + timestamp() + "] " + message;
            std::cout << line << std::endl;
            if (fileStream.is_open()) {
                fileStream << line << "\n";
                fileStream.flush();
            }
        }
        
        /**
         * @brief Writes text to both console and file without a timestamp.
         * @param text The text to write.
         */
        static void write(const std::string& text) {
            std::lock_guard<std::mutex> lock(mtx);
            std::cout << text;
            if (fileStream.is_open()) {
                fileStream << text;
                fileStream.flush();
            }
        }
        
        /**
         * @brief Closes the log file stream if it is open.
         */
        static void close() {
            std::lock_guard<std::mutex> lock(mtx);
            if (fileStream.is_open()) {
                fileStream.close();
            }
        }
};


inline std::mutex Logger::mtx; // Definition of the static mutex member
inline std::ofstream Logger::fileStream; // Definition of the static file stream member