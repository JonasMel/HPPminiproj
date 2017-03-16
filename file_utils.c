#include "file_utils.h"
#include <stdio.h>

int get_file_size(const char* fileName) {
  FILE* f = fopen(fileName, "rb");
  if(!f) {
    printf("Error in get_file_size(): fopen() failed for fileName '%s'.\n", fileName);
    return -1;
  }
  fseek(f, 0L, SEEK_END);
  size_t fileSize = ftell(f);
  fclose(f);
  return (int)fileSize;
}

int read_file_into_buffer(const char* fileName, unsigned char* buf, int bufSz) {
  int fileSize = get_file_size(fileName);
  if(fileSize > bufSz) {
    printf("Error in read_file_into_buffer: (fileSize > bufSz)\n");
    return -1;
  }
  FILE* f = fopen(fileName, "rb");
  if(!f) {
    printf("Error in read_file_into_buffer(): fopen() failed for fileName '%s'.\n", fileName);
    return -1;
  }
  size_t noOfItemsRead = fread(buf, sizeof(unsigned char), fileSize, f);
  if(noOfItemsRead != fileSize) {
    printf("Error in read_file_into_buffer: (noOfItemsRead != fileSize).\n");
    return -1;
  }
  fclose(f);
  // Return 0 to indicate success
  return 0;
}

int write_buffer_to_file(const char* fileName, const unsigned char* buf, int bufSz) {
  FILE* f = fopen(fileName, "wb");
  if(!f) {
    printf("Error in write_buffer_to_file(): failed to open file '%s' for writing.\n", fileName);
    return -1;
  }
  size_t noOfItemsWritten = fwrite(buf, sizeof(unsigned char), bufSz, f);
  if(noOfItemsWritten != bufSz) {
    printf("Error in write_buffer_to_file(): failed to write to file '%s'.\n", fileName);
    return -1;
  }
  fclose(f);
  // Return 0 to indicate success
  return 0;
}
