#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

int Process::Pid() {
    return 0;
}

std::string Process::User() {
    return std::string();
}

std::string Process::Command() {
    return std::string();
}

float Process::CpuUtilization() {
    return 0.0;
}

std::string Process::Ram() {
    return std::string();
}

long int Process::UpTime() {
    return 0;
}

bool Process::operator<(Process const& a) const {
    return true;
}