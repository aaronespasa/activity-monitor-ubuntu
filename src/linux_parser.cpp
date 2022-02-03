#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"

/********************************************
 *                  SYSTEM                  *
 ********************************************/
float LinuxParser::MemoryUtilization() {

}

long LinuxParser::UpTime() {
    
}

std::vector<int> Pids() {
    // IDs of the process that are being executed
}

int LinuxParser::TotalProcesses() {

}

int LinuxParser::RunningProcesses() {

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

}

long LinuxParser::Jiffies() {

}

long LinuxParser::ActiveJiffies() {

}

long LinuxParser::ActiveJiffies(int pid) {

}

long LinuxParser::IdleJiffies() {

}

/********************************************
 *                  PROCESSES               *
 ********************************************/
std::string LinuxParser::Command(int pid) {

}

std::string LinuxParser::Ram(int pid) {

}

std::string LinuxParser::Uid(int pid) {

}

std::string LinuxParser::User(int pid) {

}

long int LinuxParser::UpTime(int pid) {

}
