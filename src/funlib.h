#pragma once
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define b8 char
#define BIT(x) 1 << (x)
#define KB(x) ((unsigned long long)1024 * x)
#define MB(x) ((unsigned long long)1024 * KB(x))
#define GB(x) ((unsigned long long)1024 * MB(x))
#ifdef _WIN32
#define DEBUG_BREAK() __debugbreak()
#define EXPORT_FN __declspec(dllexport)
#elif __linux__
#define DEBUG_BREAK() __builtin_trap()
#define EXPORT_FN
#elif __APPLE__
#define DEBUG_BREAK() __builtin_trap()
#define EXPORT_FN
#endif

// #############################################################################
//                           Logging
// #############################################################################
enum TextColor {
  TEXT_COLOR_BLACK,
  TEXT_COLOR_RED,
  TEXT_COLOR_GREEN,
  TEXT_COLOR_YELLOW,
  TEXT_COLOR_BLUE,
  TEXT_COLOR_MAGENTA,
  TEXT_COLOR_CYAN,
  TEXT_COLOR_WHITE,
  TEXT_COLOR_BRIGHT_BLACK,
  TEXT_COLOR_BRIGHT_RED,
  TEXT_COLOR_BRIGHT_GREEN,
  TEXT_COLOR_BRIGHT_YELLOW,
  TEXT_COLOR_BRIGHT_BLUE,
  TEXT_COLOR_BRIGHT_MAGENTA,
  TEXT_COLOR_BRIGHT_CYAN,
  TEXT_COLOR_BRIGHT_WHITE,
  TEXT_COLOR_COUNT
};

template <typename... Args>
void _log(char *prefix, char *msg, TextColor textColor, Args... args) {
  static char *TextColorTable[TEXT_COLOR_COUNT] = {
      "\x1b[30m", // TEXT_COLOR_BLACK
      "\x1b[31m", // TEXT_COLOR_RED
      "\x1b[32m", // TEXT_COLOR_GREEN
      "\x1b[33m", // TEXT_COLOR_YELLOW
      "\x1b[34m", // TEXT_COLOR_BLUE
      "\x1b[35m", // TEXT_COLOR_MAGENTA
      "\x1b[36m", // TEXT_COLOR_CYAN
      "\x1b[37m", // TEXT_COLOR_WHITE
      "\x1b[90m", // TEXT_COLOR_BRIGHT_BLACK
      "\x1b[91m", // TEXT_COLOR_BRIGHT_RED
      "\x1b[92m", // TEXT_COLOR_BRIGHT_GREEN
      "\x1b[93m", // TEXT_COLOR_BRIGHT_YELLOW
      "\x1b[94m", // TEXT_COLOR_BRIGHT_BLUE
      "\x1b[95m", // TEXT_COLOR_BRIGHT_MAGENTA
      "\x1b[96m", // TEXT_COLOR_BRIGHT_CYAN
      "\x1b[97m", // TEXT_COLOR_BRIGHT_WHITE
  };

  char formatBuffer[8192] = {};
  sprintf(formatBuffer, "%s %s %s \033[0m", TextColorTable[textColor], prefix,
          msg);

  char textBuffer[8912] = {};
  sprintf(textBuffer, formatBuffer, args...);

  puts(textBuffer);
}

#define LOG_TRACE(msg, ...)                                                    \
  _log("TRACE: ", msg, TEXT_COLOR_GREEN, ##__VA_ARGS__);
#define LOG_WARN(msg, ...)                                                     \
  _log("WARN: ", msg, TEXT_COLOR_YELLOW, ##__VA_ARGS__);
#define LOG_ERROR(msg, ...) _log("ERROR: ", msg, TEXT_COLOR_RED, ##__VA_ARGS__);

#define FN_ASSERT(x, msg, ...)                                                 \
  {                                                                            \
    if (!(x)) {                                                                \
      LOG_ERROR(msg, ##__VA_ARGS__);                                           \
      DEBUG_BREAK();                                                           \
      LOG_ERROR("Assertion HIT!")                                              \
    }                                                                          \
  }

// #############################################################################
//                           Bump Allocator
// #############################################################################
struct BumpAllocator {
  size_t capacity;
  size_t used;
  char *memory;
};

BumpAllocator Make_Bump_Allocator(size_t size);

char *Bump_Alloc(BumpAllocator *bumpAllocator, size_t size);

// #############################################################################
//                           File I/O
// #############################################################################
long long get_timestamp(const char *file);

bool file_exists(const char *filePath);

long get_file_size(const char *filePath);
/*
 * Reads a file into a supplied buffer. We manage our own
 * memory and therefore want more control over where it
 * is allocated
 */
char *read_file(const char *filePath, int *fileSize, char *buffer);
char *read_file(const char *filePath, int *fileSize,
                BumpAllocator *bumpAllocator);

void write_file(const char *filePath, char *buffer, int size);

bool copy_file(const char *fileName, const char *outputName, char *buffer);

bool copy_file(const char *fileName, const char *outputName,
               BumpAllocator *bumpAllocator);

// #############################################################################
//                           Math Stuff
// #############################################################################
struct Vec2 {
  float x, y;

  Vec2 operator/(float scalar) { return {x / scalar, y / scalar}; }

  Vec2 operator-(Vec2 other) { return {x - other.x, y - other.y}; }
};
struct IVec2 {
  int x, y;
};

Vec2 vec_2(IVec2 v);
struct Vec4 {
  union {
    float values[4];
    struct {
      float x;
      float y;
      float z;
      float w;
    };

    struct {
      float r;
      float g;
      float b;
      float a;
    };
  };

  float &operator[](int idx) { return values[idx]; }

  bool operator==(Vec4 other) {
    return x == other.x && y == other.y && z == other.z && w == other.w;
  }
};

struct Mat4 {
  union {
    Vec4 values[4];
    struct {
      float ax;
      float bx;
      float cx;
      float dx;

      float ay;
      float by;
      float cy;
      float dy;

      float az;
      float bz;
      float cz;
      float dz;

      float aw;
      float bw;
      float cw;
      float dw;
    };
  };

  Vec4 &operator[](int col) { return values[col]; }
};

Mat4 orthographic_projection(float left, float right, float top, float bottom);
