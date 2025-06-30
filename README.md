# s21_string+

## Project Overview
A custom C library implementing core string manipulation functions from `string.h` standard library with additional functionality inspired by C# String class. 

## Functionality

- Memory operations: memcpy, memcmp, memset
- String manipulation: strncpy, strncat, strtok
- Search/comparison: strstr, strchr, strcmp
- Case conversion (to_upper, to_lower)
- String insertion/trimming
- Unicode-safe operations


## Usage Example
```c
#include "s21_string.h"

int main() {
    char dest[100];
    s21_sprintf(dest, "Hello %s!", "world");
    printf("%s\n", dest);  // Hello world!
    return 0;
}
```

## Build Instructions
```bash
make all       # Build static library
make test      # Run unit tests
make gcov_report  # Generate coverage report
make clean #remove builded files
```

