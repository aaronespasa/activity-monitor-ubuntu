#include <curses.h>
#include <chrono>
#include <string>
#include <thread>
#include <vector>

#include "format.h"
#include "ncurses_display.h"
#include "system.h"

std::string NCursesDisplay::ProgressBar(float percent) {
    // 50 bars uniformly displayed from 0% - 100% (2% is one bar(|))
    std::string result("0%");
    int size = 50;
    float bars{percent * size};

    for(int i = 0; i < size; ++i) {
        result += i <= bars ? '|' : ' ';
    }

    std::string display = std::to_string(percent * 100).substr(0, 4);

    if(percent < 0.1 || percent == 1.0)
        display = " " + std::to_string(percent * 100).substr(0, 3);
    
    return result + " " + display + "/100%";
}

void NCursesDisplay::DisplaySystem(System& system, WINDOW* window) {
    /**
     * Display the usage of the CPU, the Memory and information about the processes.
     */
    int row = 0;
    int const FIRST_COLUMN = 2;
    int const SECOND_COLUMN = 10;

    mvwprintw(window, ++row, FIRST_COLUMN, ("OS: " + system.OperatingSystem()).c_str());
    mvwprintw(window, ++row, FIRST_COLUMN, ("Kernel: " + system.Kernel()).c_str());
    
    // Display CPU usage:
    mvwprintw(window, ++row, FIRST_COLUMN, "CPU: ");
    wattron(window, COLOR_PAIR(1));
    mvwprintw(window, row, SECOND_COLUMN, "");
    wprintw(window, ProgressBar(system.Cpu().Utilization()).c_str());
    wattroff(window, COLOR_PAIR(1));

    // Display Memory usage:
    mvwprintw(window, ++row, FIRST_COLUMN, "Memory: ");
    wattron(window, COLOR_PAIR(1));
    mvwprintw(window, row, SECOND_COLUMN, "");
    wprintw(window, ProgressBar(system.MemoryUtilization()).c_str());
    wattroff(window, COLOR_PAIR(1));

    mvwprintw(window, ++row, FIRST_COLUMN,
             ("Total Processes: " + std::to_string(system.RunningProcesses())).c_str());

    mvwprintw(window, ++row, FIRST_COLUMN,
              ("Running Processes: " + std::to_string(system.RunningProcesses())).c_str());

    mvwprintw(window, ++row, FIRST_COLUMN,
              ("Up Time: " + Format::ElapsedTime(system.UpTime())).c_str());

    wrefresh(window);
}

void NCursesDisplay::DisplayProcesses(std::vector<Process>& processes, WINDOW* window, int n) {
    /**
     * Display the processes and their properties (like the PID, User, ...)
     */
    int row = 0;
    int const PID_COLUMN = 2;
    int const USER_COLUMN = 9;
    int const CPU_COLUMN = 16;
    int const RAM_COLUMN = 26;
    int const TIME_COLUMN = 35;
    int const COMMAND_COLUMN = 46;

    wattron(window, COLOR_PAIR(2));
    mvwprintw(window, ++row, PID_COLUMN, "PID");
    mvwprintw(window, row, USER_COLUMN, "USER");
    mvwprintw(window, ++row, CPU_COLUMN, "CPU[%%]");
    mvwprintw(window, ++row, RAM_COLUMN, "RAM[MB]");
    mvwprintw(window, ++row, TIME_COLUMN, "TIME+");
    mvwprintw(window, ++row, COMMAND_COLUMN, "COMMAND");
    wattroff(window, COLOR_PAIR(2));

    for(int i = 0; i < n; ++i) {
        // window->_max outputs the max. num. of columns of the window
        mvwprintw(window, ++row, PID_COLUMN,
                  (std::string(window->_maxx-2, ' ')).c_str());
        
        Process process = processes[i];
        float cpu = process.CpuUtilization() * 100;

        // Print the PID of the process
        mvwprintw(window, row, PID_COLUMN, std::to_string(process.Pid()).c_str());
        
        // Print the User of the process
        mvwprintw(window, row, USER_COLUMN, process.User().c_str());

        // Print the CPU usage of the process
        mvwprintw(window, row, CPU_COLUMN, std::to_string(cpu).substr(0, 4).c_str());

        // Print the RAM usage of the process
        mvwprintw(window, row, RAM_COLUMN, process.Ram().c_str());

        // Print the time the process has been up
        mvwprintw(window, row, TIME_COLUMN,
                  Format::ElapsedTime(process.UpTime()).c_str());
        
        mvwprintw(window, row, PID_COLUMN,
                  process.Command().substr(0, window->_maxx - 46).c_str());
    }
}

void NCursesDisplay::Display(System& system, int n) {
    /**
     * Display the Ubuntu processes activity through terminal.
     * @param int n: number of processes (10 by default);
     */
    initscr();          // start ncurses
    noecho();           // do not print input values
    cbreak();           // terminate ncurses on CTRL + C
    start_color();      // enable color

    int x_max = getmaxx(stdscr);    // stdscr is the default window

    // newwin(int nlines, int ncols, int begin_y, int begin_x) <- pointer to a new window
    WINDOW* system_window = newwin(9, x_max-1, 0, 0);
    WINDOW* process_window = newwin(3 + n, x_max - 1, system_window->_maxy + 1, 0);

    while(1) {
        // initialize the colors
        init_pair(1, COLOR_BLUE, COLOR_BLACK);
        init_pair(2, COLOR_GREEN, COLOR_BLACK);

        // Draw border around windows
        box(system_window, 0, 0);
        box(process_window, 0, 0);

        // Display the System and the Processes
        DisplaySystem(system, system_window);
        DisplayProcesses(system.Processes(), process_window, n);

        wrefresh(system_window);
        wrefresh(process_window);
        refresh();

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    endwin();           // stop ncurses
}