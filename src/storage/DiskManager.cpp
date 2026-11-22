#include "storage/DiskManager.hpp"

#include <fcntl.h>
#include <unistd.h>

#include <cstring>
#include <ios>
#include <stdexcept>

#include "common/constants.hpp"
// DiskManager implementation
// C++ Constructor. constructor in C++ always share the exact same name as the class and has no
// return type
// file_path_ and file_descriptor_ is the member initializer list
// Instead of assigning values inside the constructor curly braces, the initializer list sets your
// member variables before the constrctor body even runs
DiskManager::DiskManager(const std::string& db_file) : file_path_(db_file), file_descriptor_(-1) {
    // Open the database file with read/write access, create if it doesn't exist
    file_descriptor_ = open(file_path_.c_str(), O_RDWR | O_CREAT, 0644);
    if (file_descriptor_ < 0) {
        throw std::runtime_error("Failed to open database file: " + file_path_);
    }
}

DiskManager::~DiskManager() {
    if (file_descriptor_ >= 0) {
        close(file_descriptor_);
    }
}

/*
    For reading a whole page, put into the char page_buffer
*/
void DiskManager::ReadPage(int32_t page_id, char* page_buffer) {
    // To read the file, we are given the page_id, and the page_buffer.
    // We will multiply PAGE_SIZE * page_id to get the correct page
    // STEP 1 : PAGE_SIZE * page_id -> Get the starting byte offset
    // STEP 2 : we set the data to the page_buffer input parameter
    off_t offset = static_cast<off_t>(page_id) * PAGE_SIZE;
    ssize_t bytes_read = pread(file_descriptor_, page_buffer, PAGE_SIZE, offset);

    if (bytes_read < 0) {
        throw std::runtime_error("Failed to read page from disk" + std::string(strerror(errno)));
    }
    // It will put the read page bytes into the page_buffer
}

// Given a file_descriptor, we take the input page_buffer and write the bytes into the given page
void DiskManager::WritePage(int32_t page_id, const char* page_buffer) {
    // To write to the page, we need to get the offset again
    off_t offset = static_cast<off_t>(page_id) * PAGE_SIZE;
    ssize_t bytes_to_write = pwrite(file_descriptor_, page_buffer, PAGE_SIZE, offset);
    if (bytes_to_write == -1) {
        perror("Error using pwrite");
        close(file_descriptor_);
    }
}