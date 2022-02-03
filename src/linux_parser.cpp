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

}

std::string LinuxParser::Kernel() {

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
