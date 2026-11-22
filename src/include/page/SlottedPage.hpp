#include <cstring>

#include "common/constants.hpp"

#pragma once
// This is a single page, inside the .yueherndb file, there can be multiple pages
// Right now no limit to the amount of pages that can be stored in the .db file
// Inside each page, we use slotted array mechanism
// I thought we use array to store the slot???
// == PAGE_HEADER == SLOT 0 (offset, length) == SLOT 1 (offset, length)

// PAGE HEADER:
// From Andy Pavlo notes:
// Page header contains meta data about the page contents
// For example, page size, checksum, dbms version, transaction visibility
// Compression / Encoding, Schema information, Data summary
// free_space_pointer will point to where the free space (from the back) starts
#pragma pack(push, 1)
struct PageHeader {
    uint16_t slot_count;
    uint16_t free_space_pointer;
};

// For the Slotted Array
struct Slot {
    uint16_t offset;
    uint16_t length;
};
#pragma pack(pop)

// Page contains PageHeader, Slotted Array and tuples
// Also known as a Heap Page, this is a physical 4KB block of storage that holds actual data records
// (tuples)
class SlottedPage {
   public:
    // This is a member variable of SlottedPage, it contains all the raw bytes that gets written
    // into yue.db file
    char data_[PAGE_SIZE];
    PageHeader* GetHeader() { return reinterpret_cast<PageHeader*>(data_); };
    Slot* GetSlot(uint16_t slot_id) {
        // Given the slot ID, we need to get the offset and length of the data
        // 1. Get the Slot data (offset and length) offset based on the id given,
        // 2. Once we the get, we calculate the offset and length to get the actual data bytes out

        // 1. Find out where the slotted array starts
        char* slot_array_start = data_ + sizeof(PageHeader);
        // 2. Once we know where the slotted array starts, we can use reinterpret_cast,
        // to automatically count the bytes needed and get the data out!
        Slot* slot_array = reinterpret_cast<Slot*>(slot_array_start);
        //
        return slot_array + slot_id;
    };

    // This is to insert a tuple into the page
    // First we need to identify where to start the insert of our tuple
    // We will insert the tuple from the back
    // == <START>
    // == PAGE HEADER ==
    // == SLOTTED ARRAY 1,2,3,4,5,6..... ==
    // == EMPTY SPACE ==
    // == <NEW_TUPLE_HERE> ==
    // == <EXISTING_TUPLE> ==
    // == <END>
    // To calculate this, we need to know where to start, to find that, we need to know the where
    // the current tuple sizes?
    // Formula : sizeof(Header) + sizeof(total * sizeof(Slot)) + (no. of tuples * sizeof(tuple))
    bool InsertTuple(char* tuple_data, uint16_t tuple_size) {
        PageHeader* header = GetHeader();

        uint16_t no_of_slots = header->slot_count;
        // Calculate the bytes taken by the slots
        size_t header_slotted_array_size = sizeof(PageHeader) + (no_of_slots * sizeof(Slot));
        // At where, the byte offset, do we put this tuple?
        // == START ==
        // == <no_of_slots> bytes ==
        // == <insert_tuple_here> ==
        // == <existing_tuples> ==
        // == END ==
        // Update current free space pointer
        uint16_t curr_free_space_pointer = header->free_space_pointer;
        uint16_t new_free_space_pointer = curr_free_space_pointer - tuple_size;
        header->free_space_pointer = new_free_space_pointer;
        // Copy the raw bytes from the caller's buffer into the page_memory
        std::memcpy(data_ + new_free_space_pointer, tuple_data, tuple_size);
        return true;
    }
};