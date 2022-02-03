#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"

Processor& System::Cpu() {
    return cpu_;
}

std::vector<Process>& System::Processes() {
    return processes_;
}

float System::MemoryUtilization() {
    return 0.0;
}

long int System::UpTime() {
    return 0;
}

int System::TotalProcesses() {
    return 0;
}

int System::RunningProcesses() {
    return 0;
}

std::string System::Kernel() {
    return std::string();
}

std::string System::OperatingSystem() {
    return std::string();
}