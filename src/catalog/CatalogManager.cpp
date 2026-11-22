#include "catalog/CatalogManager.hpp"

#include <iostream>

// Catalog files end with .yueherncatalog
// They are persistent on disk and store the table structure in this format inside each file
// <COLUMN_NAME>,<COLUMN_TYPE>,<SIZE>
CatalogManager::CatalogManager() { LoadAllTablesFromDisk(); }

// <TABLE_NAME>.yuehern.catalog
void CatalogManager::LoadAllTablesFromDisk() {
    std::cout << "Scanning and reading the catalog directory in app/catalog";
    /* How should we be able to access the catalog?
        Use which data structure?

        - We can store the catalog in a hash map
        - Estimated size of each table?
        - Size of data stored per row?
    */
}

void CatalogManager::LoadSampleTableInMemory() {}

bool CatalogManager::CreateTable(const std::string& table_name, const std::vector<Column>& columns,
                                 uint16_t root_page_id) {
    std::cout << "CreateTable()";
    for (const Column element : columns) {
    }

    // loop through the vector, and the type (ColumnDataType) and size of each
}