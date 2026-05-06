#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <cerrno>
#include <cstring>
#include <iostream>
#include <limits.h>

// Helper to check for errors and print them clearly
void check_error(int result, const char* syscall_name) {
    if (result < 0) {
        std::cerr << "Error in " << syscall_name << ": " << std::strerror(errno) << "\n";
        exit(EXIT_FAILURE);
    }
}

int main() {
    const char *dirname = "demo_dir";
    const char *filename = "example.txt";
    const char *renamed_file = "example_renamed.txt";
    const char *msg = "Hello from full syscall demo\n";

    // 1. mkdir: Create a directory with specific permissions
    check_error(mkdir(dirname, 0755), "mkdir");

    // 2. chdir: Change the working directory of the process
    check_error(chdir(dirname), "chdir");

    // 3. getcwd: Retrieve the current absolute path
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != nullptr) {
        std::cout << "[SYSCALL] getcwd: " << cwd << "\n";
    }

    // 4. open: Get a file descriptor (O_CREAT | O_EXCL ensures we create a fresh one)
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    check_error(fd, "open");

    // 5. write: Send data from user space to kernel buffer
    ssize_t bytes_written = write(fd, msg, std::strlen(msg));
    check_error(bytes_written, "write");
    std::cout << "[SYSCALL] write: " << bytes_written << " bytes written.\n";

    // 6. fsync: Force physical write to disk (optional but shows deep IO control)
    check_error(fsync(fd), "fsync");

    // 7. close: Release the file descriptor
    check_error(close(fd), "close");

    // 8. stat: Retrieve file metadata (size, permissions, timestamps)
    struct stat st;
    check_error(stat(filename, &st), "stat");
    std::cout << "[SYSCALL] stat: File size is " << st.st_size << " bytes.\n";

    // 9. rename: Atomic move/rename operation
    check_error(rename(filename, renamed_file), "rename");
    std::cout << "[SYSCALL] rename: Moved " << filename << " to " << renamed_file << "\n";

    // 10. unlink: Delete the name from the filesystem (deletes file if last link)
    check_error(unlink(renamed_file), "unlink");

    // 11. Cleanup: Leave the environment as we found it
    check_error(chdir(".."), "chdir (up)");
    check_error(rmdir(dirname), "rmdir");

    std::cout << "--- All syscalls executed successfully ---\n";
    return 0;
}