#include "funlib.h"
#include <sys/stat.h>

BumpAllocator Make_Bump_Allocator(size_t size) {
  BumpAllocator ba = {};

  ba.memory = (char *)malloc(size);
  if (ba.memory) {
    ba.capacity = size;
    memset(ba.memory, 0, size); // Sets the memory to 0
  } else {
    FN_ASSERT(false, "Failed to allocate Memory!");
  }

  return ba;
}

char *Bump_Alloc(BumpAllocator *bumpAllocator, size_t size) {
  char *result = nullptr;

  size_t allignedSize =
      (size + 7) & ~7; // This makes sure the first 4 bits are 0
  if (bumpAllocator->used + allignedSize <= bumpAllocator->capacity) {
    result = bumpAllocator->memory + bumpAllocator->used;
    bumpAllocator->used += allignedSize;
  } else {
    FN_ASSERT(false, "BumpAllocator is full");
  }

  return result;
}

// #############################################################################
//                           File I/O
// #############################################################################
long long get_timestamp(const char *file) {
  struct stat file_stat = {};
  stat(file, &file_stat);
  return file_stat.st_mtime;
}

bool file_exists(const char *filePath) {
  FN_ASSERT(filePath, "No filePath supplied!");

  auto file = fopen(filePath, "rb");
  if (!file) {
    return false;
  }
  fclose(file);

  return true;
}

long get_file_size(const char *filePath) {
  FN_ASSERT(filePath, "No filePath supplied!");

  long fileSize = 0;
  auto file = fopen(filePath, "rb");
  if (!file) {
    LOG_ERROR("Failed opening File: %s", filePath);
    return 0;
  }

  fseek(file, 0, SEEK_END);
  fileSize = ftell(file);
  fseek(file, 0, SEEK_SET);
  fclose(file);

  return fileSize;
}

/*
 * Reads a file into a supplied buffer. We manage our own
 * memory and therefore want more control over where it
 * is allocated
 */
char *read_file(const char *filePath, int *fileSize, char *buffer) {
  FN_ASSERT(filePath, "No filePath supplied!");
  FN_ASSERT(fileSize, "No fileSize supplied!");
  FN_ASSERT(buffer, "No buffer supplied!");

  *fileSize = 0;
  auto file = fopen(filePath, "rb");
  if (!file) {
    LOG_ERROR("Failed opening File: %s", filePath);
    return nullptr;
  }

  fseek(file, 0, SEEK_END);
  *fileSize = ftell(file);
  fseek(file, 0, SEEK_SET);

  memset(buffer, 0, *fileSize + 1);
  fread(buffer, sizeof(char), *fileSize, file);

  fclose(file);

  return buffer;
}

char *read_file(const char *filePath, int *fileSize,
                BumpAllocator *bumpAllocator) {
  char *file = nullptr;
  long fileSize2 = get_file_size(filePath);

  if (fileSize2) {
    char *buffer = Bump_Alloc(bumpAllocator, fileSize2 + 1);

    file = read_file(filePath, fileSize, buffer);
  }

  return file;
}

void write_file(const char *filePath, char *buffer, int size) {
  FN_ASSERT(filePath, "No filePath supplied!");
  FN_ASSERT(buffer, "No buffer supplied!");
  auto file = fopen(filePath, "wb");
  if (!file) {
    LOG_ERROR("Failed opening File: %s", filePath);
    return;
  }

  fwrite(buffer, sizeof(char), size, file);
  fclose(file);
}

bool copy_file(const char *fileName, const char *outputName, char *buffer) {
  int fileSize = 0;
  char *data = read_file(fileName, &fileSize, buffer);

  auto outputFile = fopen(outputName, "wb");
  if (!outputFile) {
    LOG_ERROR("Failed opening File: %s", outputName);
    return false;
  }

  int result = fwrite(data, sizeof(char), fileSize, outputFile);
  if (!result) {
    LOG_ERROR("Failed opening File: %s", outputName);
    return false;
  }

  fclose(outputFile);

  return true;
}

bool copy_file(const char *fileName, const char *outputName,
               BumpAllocator *bumpAllocator) {
  char *file = 0;
  long fileSize2 = get_file_size(fileName);

  if (fileSize2) {
    char *buffer = Bump_Alloc(bumpAllocator, fileSize2 + 1);

    return copy_file(fileName, outputName, buffer);
  }

  return false;
}
