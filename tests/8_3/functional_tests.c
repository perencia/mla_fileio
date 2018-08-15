#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "fileio.h"
#include "emulated_disk.h"

#define TEST_DRIVE DRV096

extern FILEIO_DRIVE_CONFIG EmulatedDisk;
extern struct EMULATED_DRIVE TEST_DRIVE;

bool TestSetup(void){
    const char name[] = "TestSetup";
    
    if(FILEIO_Initialize() != true) {printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_DriveMount ('A', &EmulatedDisk, (void*)&TEST_DRIVE) != FILEIO_ERROR_NONE){printf("TEST FAILED: %s\r\n", name); return false;}
    
    return true;
}

void TestTearDown(void){
    FILEIO_DriveUnmount ('A');
}

bool CreateFileInRoot(void){ 
    const char name[] = "CreateFileInRoot";
    FILEIO_OBJECT myFile;
    uint8_t buffer[4];
    
    if(FILEIO_Open(&myFile, "TEST.TXT", FILEIO_OPEN_WRITE | FILEIO_OPEN_CREATE | FILEIO_OPEN_TRUNCATE) != FILEIO_RESULT_SUCCESS){printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_Write("TEST", 1, 4, &myFile) != 4) {printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_Close(&myFile) != FILEIO_RESULT_SUCCESS) {printf("TEST FAILED: %s\r\n", name); return false;}    
    
    return true;
}

bool ReadFileInRoot(void){ 
    const char name[] = "ReadFileInRoot";
    FILEIO_OBJECT myFile;
    uint8_t buffer[4];
    
    if(FILEIO_Open(&myFile, "TEST.TXT", FILEIO_OPEN_WRITE | FILEIO_OPEN_CREATE | FILEIO_OPEN_TRUNCATE) != FILEIO_RESULT_SUCCESS){printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_Write("TEST", 1, 4, &myFile) != 4) {printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_Close(&myFile) != FILEIO_RESULT_SUCCESS) {printf("TEST FAILED: %s\r\n", name); return false;}    
    if(FILEIO_Open(&myFile, "TEST.TXT", FILEIO_OPEN_READ) != FILEIO_RESULT_SUCCESS){printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_Read (buffer, 1, 4, &myFile) != 4){printf("TEST FAILED: %s\r\n", name); return false;}
    if(memcmp(buffer, "TEST", 4) != 0){printf("TEST FAILED: %s\r\n", name); return false;}
    
    return true;
}

bool EndOfFile(void){ 
    const char name[] = "EndOfFile";
    FILEIO_OBJECT myFile;
    uint8_t buffer[4];
    
    if(FILEIO_Open(&myFile, "TEST.TXT", FILEIO_OPEN_WRITE | FILEIO_OPEN_CREATE | FILEIO_OPEN_TRUNCATE) != FILEIO_RESULT_SUCCESS){printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_Write("TEST", 1, 4, &myFile) != 4) {printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_Close(&myFile) != FILEIO_RESULT_SUCCESS) {printf("TEST FAILED: %s\r\n", name); return false;}    
    if(FILEIO_Open(&myFile, "TEST.TXT", FILEIO_OPEN_READ) != FILEIO_RESULT_SUCCESS){printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_Read (buffer, 1, 3, &myFile) != 3){printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_Eof(&myFile) == true){printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_Read (buffer, 1, 1, &myFile) != 1){printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_Eof(&myFile) != true){printf("TEST FAILED: %s\r\n", name); return false;}
    
    return true;
}

bool DirectoryRemoveAfterFolderDeletedButFileRemains(void){ 
    const char name[] = "DirectoryRemoveAfterFolderDeletedButFileRemains";
    FILEIO_OBJECT myFile;
    
    if(FILEIO_DirectoryMake("TEST") != FILEIO_RESULT_SUCCESS) {printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_DirectoryChange("TEST") != FILEIO_RESULT_SUCCESS) {printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_DirectoryMake("TEST2") != FILEIO_RESULT_SUCCESS) {printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_Open(&myFile, "TEST.TXT", FILEIO_OPEN_WRITE | FILEIO_OPEN_CREATE | FILEIO_OPEN_TRUNCATE) != FILEIO_RESULT_SUCCESS){printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_Write("TEST", 1, 4, &myFile) != 4) {printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_Close(&myFile) != FILEIO_RESULT_SUCCESS) {printf("TEST FAILED: %s\r\n", name); return false;} 
    if(FILEIO_DirectoryRemove("TEST2") != FILEIO_RESULT_SUCCESS) {printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_DirectoryChange("..") != FILEIO_RESULT_SUCCESS) {printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_DirectoryRemove("TEST") != FILEIO_RESULT_FAILURE) {printf("TEST FAILED: %s\r\n", name); return false;}
    
    return true;
}

bool DirectoryRemoveAfterFileDeleted(void){ 
    const char name[] = "DirectoryRemoveAfterFileDeleted";
    FILEIO_OBJECT myFile;
    
    if(FILEIO_DirectoryMake("TEST") != FILEIO_RESULT_SUCCESS) {printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_DirectoryChange("TEST") != FILEIO_RESULT_SUCCESS) {printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_Open(&myFile, "TEST.TXT", FILEIO_OPEN_WRITE | FILEIO_OPEN_CREATE | FILEIO_OPEN_TRUNCATE) != FILEIO_RESULT_SUCCESS){printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_Write("TEST", 1, 4, &myFile) != 4) {printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_Close(&myFile) != FILEIO_RESULT_SUCCESS) {printf("TEST FAILED: %s\r\n", name); return false;}    
    if(FILEIO_Remove("TEST.TXT") != FILEIO_RESULT_SUCCESS) {printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_DirectoryChange("..") != FILEIO_RESULT_SUCCESS) {printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_DirectoryRemove("TEST") != FILEIO_RESULT_SUCCESS) {printf("TEST FAILED: %s\r\n", name); return false;}
    
    return true;
}

bool DirectoryRemoveWhileNotEmpty(void){ 
    const char name[] = "DirectoryRemoveWhileNotEmpty";
    FILEIO_OBJECT myFile;
    
    if(FILEIO_DirectoryMake("TEST") != FILEIO_RESULT_SUCCESS) {printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_DirectoryChange("TEST") != FILEIO_RESULT_SUCCESS) {printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_Open(&myFile, "TEST.TXT", FILEIO_OPEN_WRITE | FILEIO_OPEN_CREATE | FILEIO_OPEN_TRUNCATE) != FILEIO_RESULT_SUCCESS){printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_Write("TEST", 1, 4, &myFile) != 4) {printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_Close(&myFile) != FILEIO_RESULT_SUCCESS) {printf("TEST FAILED: %s\r\n", name); return false;}    
    if(FILEIO_DirectoryChange("..") != FILEIO_RESULT_SUCCESS) {printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_DirectoryRemove("TEST") != FILEIO_RESULT_FAILURE) {printf("TEST FAILED: %s\r\n", name); return false;}
    
    return true;
}

bool SeekCurrent(void){ 
    const char name[] = "SeekCurrent";
    FILEIO_OBJECT myFile;
    
    if(FILEIO_Open(&myFile, "TEST.TXT", FILEIO_OPEN_WRITE | FILEIO_OPEN_READ | FILEIO_OPEN_CREATE | FILEIO_OPEN_TRUNCATE) != FILEIO_RESULT_SUCCESS){printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_Write("ABCDEFGHIJKLMNOPQRSTUVWXYZ", 1, 26, &myFile) != 26) {printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_Seek(&myFile, -1, FILEIO_SEEK_CUR) != FILEIO_RESULT_SUCCESS) {printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_GetChar(&myFile) != 'Z') {printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_Seek(&myFile, -26, FILEIO_SEEK_CUR) != FILEIO_RESULT_SUCCESS) {printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_GetChar(&myFile) != 'A') {printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_Seek(&myFile, 2, FILEIO_SEEK_CUR) != FILEIO_RESULT_SUCCESS) {printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_GetChar(&myFile) != 'D') {printf("TEST FAILED: %s\r\n", name); return false;}
    
    return true;
}

bool SeekSet(void){ 
    const char name[] = "SeekSet";
    FILEIO_OBJECT myFile;
    
    if(FILEIO_Open(&myFile, "TEST.TXT", FILEIO_OPEN_WRITE | FILEIO_OPEN_READ | FILEIO_OPEN_CREATE | FILEIO_OPEN_TRUNCATE) != FILEIO_RESULT_SUCCESS){printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_Write("ABCDEFGHIJKLMNOPQRSTUVWXYZ", 1, 26, &myFile) != 26) {printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_Seek(&myFile, 1, FILEIO_SEEK_SET) != FILEIO_RESULT_SUCCESS) {printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_GetChar(&myFile) != 'B') {printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_Seek(&myFile, 25, FILEIO_SEEK_SET) != FILEIO_RESULT_SUCCESS) {printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_GetChar(&myFile) != 'Z') {printf("TEST FAILED: %s\r\n", name); return false;}
    
    return true;
}

bool SeekEnd(void){ 
    const char name[] = "SeekEnd";
    FILEIO_OBJECT myFile;
    
    if(FILEIO_Open(&myFile, "TEST.TXT", FILEIO_OPEN_WRITE | FILEIO_OPEN_READ | FILEIO_OPEN_CREATE | FILEIO_OPEN_TRUNCATE) != FILEIO_RESULT_SUCCESS){printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_Write("ABCDEFGHIJKLMNOPQRSTUVWXYZ", 1, 26, &myFile) != 26) {printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_Seek(&myFile, 1, FILEIO_SEEK_END) != FILEIO_RESULT_SUCCESS) {printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_GetChar(&myFile) != 'Z') {printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_Seek(&myFile, 26, FILEIO_SEEK_END) != FILEIO_RESULT_SUCCESS) {printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_GetChar(&myFile) != 'A') {printf("TEST FAILED: %s\r\n", name); return false;}
    
    return true;
}

bool CreateMultipleDirectoriesAtOnce(void){ 
    const char name[] = "CreateMultipleDirectoriesAtOnce";
    
    if(FILEIO_DirectoryMake("TEST/TEST2/TEST3/TEST4") != FILEIO_RESULT_SUCCESS) {printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_DirectoryChange("TEST") != FILEIO_RESULT_SUCCESS) {printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_DirectoryChange("TEST2") != FILEIO_RESULT_SUCCESS) {printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_DirectoryChange("TEST3") != FILEIO_RESULT_SUCCESS) {printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_DirectoryChange("TEST4") != FILEIO_RESULT_SUCCESS) {printf("TEST FAILED: %s\r\n", name); return false;}
    
    return true;
}

bool Tell(void){ 
    const char name[] = "Tell";
    FILEIO_OBJECT myFile;
    
    if(FILEIO_Open(&myFile, "TEST.TXT", FILEIO_OPEN_WRITE | FILEIO_OPEN_READ | FILEIO_OPEN_CREATE | FILEIO_OPEN_TRUNCATE) != FILEIO_RESULT_SUCCESS){printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_Write("ABCDEFGHIJKLMNOPQRSTUVWXYZ", 1, 26, &myFile) != 26) {printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_Seek(&myFile, 1, FILEIO_SEEK_SET) != FILEIO_RESULT_SUCCESS) {printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_Tell(&myFile) != 1) {printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_GetChar(&myFile) != 'B') {printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_Tell(&myFile) != 2) {printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_Seek(&myFile, 25, FILEIO_SEEK_SET) != FILEIO_RESULT_SUCCESS) {printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_Tell(&myFile) != 25) {printf("TEST FAILED: %s\r\n", name); return false;}
    
    return true;
}

bool Rename(void){ 
    const char name[] = "Rename";
    FILEIO_OBJECT myFile;
    
    if(FILEIO_Open(&myFile, "TEST.TXT", FILEIO_OPEN_WRITE | FILEIO_OPEN_CREATE | FILEIO_OPEN_TRUNCATE) != FILEIO_RESULT_SUCCESS){printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_Write("TEST", 1, 4, &myFile) != 4) {printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_Close(&myFile) != FILEIO_RESULT_SUCCESS) {printf("TEST FAILED: %s\r\n", name); return false;} 
    if(FILEIO_Rename("TEST.TXT", "TEST2.TXT") != FILEIO_RESULT_SUCCESS) {printf("TEST FAILED: %s\r\n", name); return false;} 
    if(FILEIO_Open(&myFile, "TEST2.TXT", FILEIO_OPEN_READ) != FILEIO_RESULT_SUCCESS){printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_Close(&myFile) != FILEIO_RESULT_SUCCESS) {printf("TEST FAILED: %s\r\n", name); return false;} 
    if(FILEIO_Open(&myFile, "TEST.TXT", FILEIO_OPEN_READ) != FILEIO_RESULT_FAILURE){printf("TEST FAILED: %s\r\n", name); return false;}    
    
    return true;
}

bool FindFilesInRoot(void){ 
    const char name[] = "FindFilesInRoot";
    FILEIO_OBJECT myFile;
    FILEIO_SEARCH_RECORD searchRecord;
    
    if(FILEIO_Open(&myFile, "TEST.TXT", FILEIO_OPEN_WRITE | FILEIO_OPEN_CREATE | FILEIO_OPEN_TRUNCATE) != FILEIO_RESULT_SUCCESS){printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_Write("TEST", 1, 4, &myFile) != 4) {printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_Close(&myFile) != FILEIO_RESULT_SUCCESS) {printf("TEST FAILED: %s\r\n", name); return false;} 
    
    if(FILEIO_Open(&myFile, "TEST2.TXT", FILEIO_OPEN_WRITE | FILEIO_OPEN_CREATE | FILEIO_OPEN_TRUNCATE) != FILEIO_RESULT_SUCCESS){printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_Write("TEST2", 1, 5, &myFile) != 5) {printf("TEST FAILED: %s\r\n", name); return false;}
    if(FILEIO_Close(&myFile) != FILEIO_RESULT_SUCCESS) {printf("TEST FAILED: %s\r\n", name); return false;} 
    
    if(FILEIO_Find ("TEST*.TXT", FILEIO_ATTRIBUTE_MASK, &searchRecord, true) != FILEIO_RESULT_SUCCESS) {printf("TEST FAILED: %s\r\n", name); return false;} 
    if(FILEIO_Find ("TEST*.TXT", FILEIO_ATTRIBUTE_MASK, &searchRecord, false) != FILEIO_RESULT_SUCCESS) {printf("TEST FAILED: %s\r\n", name); return false;} 
    if(FILEIO_Find ("TEST*.TXT", FILEIO_ATTRIBUTE_MASK, &searchRecord, false) != FILEIO_RESULT_FAILURE) {printf("TEST FAILED: %s\r\n", name); return false;} 
    
    return true;
}

typedef bool (*TEST_FUNCTION)(void);
TEST_FUNCTION tests[]={
    &CreateFileInRoot,
    &ReadFileInRoot,
    &EndOfFile,
    &SeekCurrent,
    &SeekSet, 
    &SeekEnd, 
    &Tell,
    &Rename,
    &FindFilesInRoot,
    &DirectoryRemoveAfterFileDeleted,
    &DirectoryRemoveWhileNotEmpty,
    &DirectoryRemoveAfterFolderDeletedButFileRemains,
    &CreateMultipleDirectoriesAtOnce
};

void RunFunctionalTests(void){
    int test_index;
    uint32_t passed;
    const uint32_t test_count = (sizeof(tests)/sizeof(TEST_FUNCTION));
           
    passed = 0;
    for(test_index=0; test_index < (sizeof(tests)/sizeof(TEST_FUNCTION)); test_index++){
        if(TestSetup() == true){
            passed += tests[test_index]();
            TestTearDown();
        }
    }
    
    printf( "Functional tests: run: %i, passed: %i, failed: %i\r\n", test_count, passed, test_count-passed);
}
