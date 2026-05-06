#include <unistd.h>
#include <sys/wait.h>
#include <iostream>

int main() {
    pid_t pid = fork();
    if (pid == 0) {
        std::cout << "Child PID=" << getpid() << "\n";
        return 0;
    }

    waitpid(pid, nullptr, 0);
    std::cout << "Parent PID=" << getpid() << ", child finished\n";
    return 0;
}