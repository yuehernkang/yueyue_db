#pragma once
#include <fstream>
#include <string>
// DiskManager interface
class DiskManager {
   private:
    int file_descriptor_;
    std::string file_path_;

   public:
    explicit DiskManager(const std::string& db_file);
    ~DiskManager();

    void ReadPage(int32_t page_id, char* page_buffer);
    void WritePage(int32_t page_id, const char* page_buffer);
};