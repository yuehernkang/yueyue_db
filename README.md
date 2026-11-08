# Introduction
This is my implementation of a row-oriented database from scratch where we read the raw bytes from a file and translate it into a tuple

## Overall Architecture

### DiskManager
DiskManager is the main class that interact with the filesystem to read and write bytes to the file

### File
The file extension is .yueherndb, it does not really matter. You pass in a page_id to DiskManager, and it will read the raw bytes from the file. PAGE_SIZE is 4096, so given a page_id, we will do PAGE_SIZE * 4096 to get to the correct offset of a page.

### Page
== PAGE HEADER == SLOT 0 (offset, length) == SLOT 1 (offset, length) == SLOT 2 (offset, length)
........................... (this represents empty space)
== TUPLE 1 == TUPLE 2 == TUPLE 3 ==

This is called a Heap Page, a physical 4KB block of storage, has nothing to do with the Heap data structure, a Heap File just means a sequence of Heap Pages chained together on disk.

#### Tuples on the page
How to retrieve tuples on the page? The offset is stored in the slotted array. Offset stored is counted from the FRONT of the page, and we just go to the offset, add the length and get the bytes from there.

## File Level
What to do with the file? 
We need to know what are the offsets for each tuple
Need a CATALOG file defining what are the offsets to determine 1 tuple


## CATALOG file
WORK IN PROGRESS.....
When user create a table, CATALOG file is created.

CATALOG file contains, for each tuple, what are the sizes of each column

Questions to ask:
