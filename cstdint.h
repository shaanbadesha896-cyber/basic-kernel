#ifndef CSTDINT_H
#define CSTDINT_H

// --- Exact-width signed integer types ---
typedef signed char        int8_t;      // Exactly 1 byte
typedef short              int16_t;     // Exactly 2 bytes
typedef int                int32_t;     // Exactly 4 bytes
typedef long long          int64_t;     // Exactly 8 bytes

// --- Exact-width unsigned integer types ---
typedef unsigned char      uint8_t;     // Exactly 1 byte
typedef unsigned short     uint16_t;    // Exactly 2 bytes
typedef unsigned int       uint32_t;    // Exactly 4 bytes
typedef unsigned long long uint64_t;    // Exactly 8 bytes

// --- Pointer-width integer types (Crucial for page matching) ---
// In 32-bit mode, memory addresses are 32 bits wide.
typedef unsigned int       uintptr_t;
typedef int                intptr_t;

#endif // CSTDINT_H 