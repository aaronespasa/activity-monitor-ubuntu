#include <filesystem>
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"

namespace fs = std::filesystem;

/********************************************
 *                  SYSTEM                  *
 ********************************************/
float LinuxParser::MemoryUtilization() {
    return 0.0;
}

long LinuxParser::UpTime() {
    return 0;
}

std::vector<int> LinuxParser::Pids() {
    // IDs of the process that are being executed
    std::vector<int> pids;
    std::string proc_str, pid_str;

    for(const auto &entry : fs::directory_iterator(kProcDirectory)) {
        std::string entry_str = entry.path();
        std::replace(entry_str.begin(), entry_str.end(), '/', ' ');

        std::istringstream linestream(entry_str);

        linestream >> proc_str >> pid_str;
        int pid = stoi(pid_str);
        pids.push_back(pid);
    }
}

int LinuxParser::TotalProcesses() {
    std::string key, value;
    int total_processes;

    std::string line;
    std::ifstream stream(kProcDirectory + kVersionFilename);

    if(stream.is_open()) {
        while(std::getline(stream, line)) {
            std::istringstream linestream(line);

            while(linestream >> key >> value) {
                if(key == "processes") {
                    total_processes = stoi(value);
                    return total_processes;
                }
            }
        }
    }

    return total_processes;
}

int LinuxParser::RunningProcesses() {
    std::string key, value;
    int running_processes;

    std::string line;
    std::ifstream stream(kProcDirectory + kVersionFilename);

    if(stream.is_open()) {
        while(std::getline(stream, line)) {
            std::istringstream linestream(line);

            while(linestream >> key >> value) {
                if(key == "procs_running") {
                    running_processes = stoi(value);
                    return running_processes;
                }
            }
        }
    }

    return running_processes;
}

std::string LinuxParser::OperatingSystem() {
    std::string line;
    std::string key;
    std::string value;
    std::ifstream filestream(kOSPath);

    if(filestream.is_open()) {
        while(std::getline(filestream, line)) {
            // PRETTY_NAME="Ubuntu 20.04" -> PRETTY_NAME Ubuntu 20.04
            std::replace(line.begin(), line.end(), ' ', '_');
            std::replace(line.begin(), line.end(), '=', ' ');
            std::replace(line.begin(), line.end(), '"', ' ');

            std::istringstream linestream(line);
            while(linestream >> key >> value) {
                if(key == "PRETTY_NAME") {
                    std::replace(value.begin(), value.end(), '_', ' ');
                    return value;
                }
            }
        }
    }

    return value;
}

std::string LinuxParser::Kernel() {
    std::string os, kernel, version;

    std::ifstream stream(kProcDirectory + kVersionFilename);

    if(stream.is_open()) {
        std::string line;
        std::getline(stream, line);
        std::istringstream linestream(line);
        // stream until a white space is encountered
        linestream >> os >> version >> kernel;
    }

    return kernel;
}

/********************************************
 *                    CPU                   *
 ********************************************/
std::vector<std::string> LinuxParser::CpuUtilization() {
    return {};
}

long LinuxParser::Jiffies() {
    return 0;
}

long LinuxParser::ActiveJiffies() {
    return 0;
}

long LinuxParser::ActiveJiffies(int pid) {
    return 0;
}

long LinuxParser::IdleJiffies() {
    return 0;
}

/********************************************
 *                  PROCESSES               *
 ********************************************/
std::string LinuxParser::Command(int pid) {
    return std::string();
}

std::string LinuxParser::Ram(int pid) {
    return std::string();
}

std::string LinuxParser::Uid(int pid) {
    return std::string();
}

std::string LinuxParser::User(int pid) {
    return std::string();
}

long int LinuxParser::UpTime(int pid) {
    return 0;
}
