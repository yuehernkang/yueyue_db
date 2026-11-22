#pragma once
#include <common/constants.hpp>
#include <cstdint>
#include <string>
#include <vector>
// Singleton Catalog Manager that will load once on startup
struct Column {
    std::string name;
    CatalogDataType type;
    uint32_t size;
};

// Represents the structure of a specific table
struct TableMetadata {
    std::string table_name;
    uint32_t table_id;
    std::vector<Column> columns;
};

// DiskManager interface
class CatalogManager {
   private:
    int file_descriptor_;
    std::string file_path_;
    void LoadAllTablesFromDisk();
    void LoadSampleTableInMemory();
    CatalogManager();
    ~CatalogManager() = default;

   public:
    static CatalogManager& GetInstance() {
        static CatalogManager instance;
        return instance;
    }
    // TABLE_NAME = CATALOG FILE NAME
    bool CreateTable(const std::string& table_name, const std::vector<Column>& columns,
                     uint16_t root_page_id);
};