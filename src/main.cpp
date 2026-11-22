#include <cstring>
#include <iostream>
#include <vector>

#include "catalog/CatalogManager.hpp"
#include "common/constants.hpp"
#include "page/SlottedPage.hpp"
#include "storage/DiskManager.hpp"

void testFunctionToAddBytes(DiskManager& disk_m, const char* page_buffer) {
    disk_m.WritePage(0, page_buffer);
    // After ReadPage is done, it will put all 4096 bytes read into page_buffer
}

/*
    CURRENT OBJECTIVE: Implement a ReadTuple function
    Input: Record ID
    Output: Tuple Data

    Record ID -> DiskManager -> CatalogManager
*/

int main() {
    try {
        std::string db_filename = "data/db/yue.yueherndb";
        // Scan and Read catalog directory
        auto& catalog = CatalogManager::GetInstance();
        // Open or Create (if not exist)
        DiskManager disk_manager(db_filename);
        char page_buffer[PAGE_SIZE];
        // Given this page_buffer, write all 0, to the amount (PAGE_SIZE)
        std::memset(page_buffer, 0, PAGE_SIZE);
        testFunctionToAddBytes(disk_manager, page_buffer);
        disk_manager.ReadPage(0, page_buffer);

    } catch (const std::exception& e) {
        std::cerr << "Database Error " << e.what() << std::endl;
        return 1;
    }
}
