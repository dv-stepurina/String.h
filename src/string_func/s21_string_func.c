#include "../s21_string.h"

void *s21_insert(const char *src, const char *str, size_t start_index) {
  if (src == NULL || str == NULL) return S21_NULL;

  s21_size_t srclen = s21_strlen(src);
  s21_size_t strlen = s21_strlen(str);

  if (start_index > srclen) {
    return S21_NULL;
  }

  char *newStr = calloc((srclen + strlen + 1), sizeof(char));
  if (newStr != NULL) {
    s21_memcpy(newStr, src, start_index);
    s21_memcpy(newStr + start_index, str, strlen);
    s21_memcpy(newStr + start_index + strlen, src + start_index,
               srclen - start_index + 1);
  }

  return newStr;
}

void *s21_memchr(const void *str, int c, s21_size_t n) {
  const unsigned char *ptr = (const unsigned char *)str;
  unsigned char ch = (unsigned char)c;
  const unsigned char *result = S21_NULL;

  for (s21_size_t i = 0; i < n; i++) {
    if (ptr[i] == ch) {
      result = (ptr + i);
      break;
    }
  }
  return (void *)result;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const unsigned char *firstStr = (const unsigned char *)str1;
  const unsigned char *secStr = (const unsigned char *)str2;

  for (s21_size_t i = 0; i < n; i++) {
    if (firstStr[i] != secStr[i]) {
      return (int)(firstStr[i] - secStr[i]);
    }
  }

  return 0;
}


void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  for (int i = 0; i < (int)n; i++) {
    ((char *)dest)[i] = ((char *)src)[i];
  }
  return dest;
}


void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *ptr = (unsigned char *)str;
  unsigned char value = (unsigned char)c;

  for (size_t i = 0; i < n; i++) {
    ptr[i] = value;
  }

  return str;
}

s21_size_t s21_strlen(const char *str) {
  s21_size_t length = 0;
  while (*str) {
    length++;
    str++;
  }
  return length;
}

char *s21_strcpy(char *str1, const char *str2) {
  int i = 0;
  while (str2[i] != '\0') {
    str1[i] = str2[i];
    i++;
  }
  str1[i] = '\0';

  return str1;
}

void s21_strcat(char *str2, const char *str1) {
  int length = 0;
  while (str2[length] != '\0') {
    length++;
  }

  int i = 0;
  while (str1[i] != '\0') {
    str2[length + i] = str1[i];
    i++;
  }
  str2[length + i] = '\0';
}

void s21_reverse(char str[], int len) {
  int start, end;
  for (start = 0, end = len - 1; start < end; start++, end--) {
    char temp;
    temp = *(str + start);
    *(str + start) = *(str + end);
    *(str + end) = temp;
  }
}

char *s21_itoa(int num, char *str, int base) {
  int i = 0;
  int isNegative = 0;

  if (num == -2147483648) return "-2147483648";  // for handling INT_MIN

  if (num == 0) {
    str[i] = '0';
    str[i + 1] = '\0';
    return str;
  }

  if (num < 0 && base == 10) {
    isNegative = 1;
    num = -num;
  }

  while (num != 0) {
    int rem = num % base;
    str[i++] = (rem > 9) ? (rem - 10) + 'A' : rem + '0';
    num = num / base;
  }

  if (isNegative) {
    str[i++] = '-';
  }

  str[i] = '\0';

  s21_reverse(str, i);

  return str;
}

char *s21_itoa_int64(int64_t num, char *str, int base) {
  int i = 0;
  int isNegative = 0;

  if (num == 0) {
    str[i] = '0';
    str[i + 1] = '\0';
    return str;
  }

  if (num < 0 && base == 10) {
    isNegative = 1;
    num = -num;
  }

  while (num != 0) {
    int rem = num % base;
    str[i++] = (rem > 9) ? (rem - 10) + 'A' : rem + '0';
    num = num / base;
  }

  if (isNegative) {
    str[i++] = '-';
  }

  str[i] = '\0';

  s21_reverse(str, i);

  return str;
}

char *s21_ftoa(double num, char *buffer, int afterpoint) {
  // Handling negative numbers.
  if (num < 0) {
    buffer[0] = '-';
    num = -num;
  }

  // Integer part.
  int int_part = (int)num;
  double float_part = num - int_part;

  // Conversion of the integer part to a string.
  int i = 0;
  if (int_part == 0) {
    buffer[i++] = '0';
  } else {
    while (int_part) {
      buffer[i++] = (int_part % 10) + '0';
      int_part /= 10;
    }
  }
  s21_reverse(buffer, i);
  buffer[i] = '.';  // Adding a decimal point.
  i++;

  // Conversion of the fractional part to a string.
  for (int j = 0; j < afterpoint - 1; j++) {
    float_part *= 10;
    int fractional_part = (int)float_part;
    buffer[i++] = fractional_part + '0';
    float_part -= fractional_part;
  }

  int float_part_1 = (int)(float_part * 100) % 10;
  if (float_part_1 >= 5) {
    float_part = float_part * 10 + 1;
    int fractional_part = (int)(float_part);
    buffer[i++] = fractional_part + '0';

  } else {
    float_part = float_part * 10;
    int fractional_part = (int)float_part;
    buffer[i++] = fractional_part + '0';
  }

  buffer[i] = '\0';
  return buffer;
}

char *s21_itoa_uint64(uint64_t num, char *str, int base) {
  int i = 0;

  if (num == 0) {
    str[i] = '0';
    str[i + 1] = '\0';
    return str;
  }

  while (num != 0) {
    int rem = num % base;
    str[i++] = (rem > 9) ? (rem - 10) + 'A' : rem + '0';
    num = num / base;
  }

  str[i] = '\0';

  s21_reverse(str, i);

  return str;
}

char *s21_strchr(const char *str, int c) {
  char *i;
  for (i = (char *)str; *i != c && *i != '\0'; i += 1);
  return (*i == c ? i : S21_NULL);
}


s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t count = 0;
  int flag_stop = 0;
  for (const char *s1 = str1; *s1 != '\0'; s1++) {
    for (const char *s2 = str2; *s2 != '\0'; s2++) {
      if (*s1 == *s2) {
        flag_stop = 1;
      }
    }
    if (!flag_stop) {
      count++;
    }
  }
  return count;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  s21_size_t destLength = 0;
  while (dest[destLength] != '\0') destLength++;

  s21_size_t i;
  for (i = 0; i < n && src[i] != '\0'; i++) {
    dest[destLength + i] = src[i];
  }

  if (n > 0) {
    dest[destLength + i] = '\0';
  }

  return dest;
}

int s21_strncmp(const char *str1, const char *str2, size_t n) {
  for (size_t i = 0; i < n && (str1[i] != '\0' || str2[i] != '\0'); i++) {
    if (str1[i] != str2[i]) {
      return (unsigned char)str1[i] - (unsigned char)str2[i];
    }
  }
  return 0;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t i;
  for (i = 0; i < n && src[i] != '\0'; i++) {
    dest[i] = src[i];
  }

  if (n > 0) dest[i] = '\0';

  return dest;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  char *c = S21_NULL;
  for (int i = 0; str1[i] && c == S21_NULL; i++) {
    for (int j = 0; str2[j] && c == S21_NULL; j++) {
      if (str1[i] == str2[j]) {
        c = (char *)str1 + i;
      }
    }
  }
  return c;
}

char *s21_strrchr(const char *str, int c) {
  const char *result = S21_NULL;
  unsigned char ch = (unsigned char)c;

  while (*str != '\0') {
    if (*str == ch) {
      result = str;
    }
    str++;
  }

  if (*str == ch) {
    result = str;
  }

  return (char *)result;
}

char *s21_strstr(const char *haystack, const char *needle) {
  char *letterPointer = S21_NULL;

  for (int i = 0; haystack[i] != '\0'; i++) {
    if (haystack[i] == needle[0]) {
      int j = 0;
      while (needle[j] != '\0' && haystack[i + j] != '\0' &&
             haystack[i + j] == needle[j]) {
        j++;
      }
      if (needle[j] == '\0') {
        letterPointer = (char *)&haystack[i];
      }
    }
  }

  if (*needle == '\0') {
    letterPointer = (char *)haystack;
  }

  return letterPointer;
}

char *s21_strtok(char *str, const char *delim) {
  static char *next_token = S21_NULL;
  char *token_start = S21_NULL;
  if (str || next_token) {
    if (str == S21_NULL) str = next_token;
    while (*str && s21_strchr(delim, *str)) str++;
    if (*str != '\0') {
      token_start = str;
      while (*str && !s21_strchr(delim, *str)) str++;
      if (*str) {
        *str = '\0';
        next_token = str + 1;
      } else
        next_token = S21_NULL;
    } else
      next_token = S21_NULL;
  }
  return token_start;
}


void *s21_to_lower(const char *str) {
  char *dest = S21_NULL;
  if (str != S21_NULL) {
    const char *l = str;
    s21_size_t len = 0;
    while (*l != '\0') {
      len++;
      l++;
    }
    dest = (char *)malloc((len + 1) * sizeof(char));
    char *c = dest;
    while (*str != '\0') {
      if (*str >= 'A' && *str <= 'Z') {
        *c = *str + 32;
      } else {
        *c = *str;
      }
      c++;
      str++;
    }
    *c = '\0';
  }
  return (void *)dest;
}

void *s21_to_upper(const char *str) {
  char *dest = S21_NULL;
  if (str != S21_NULL) {
    const char *l = str;
    s21_size_t len = 0;
    while (*l != '\0') {
      len++;
      l++;
    }
    dest = (char *)malloc((len + 1) * sizeof(char));
    char *c = dest;
    while (*str != '\0') {
      if (*str >= 'a' && *str <= 'z') {
        *c = *str - 32;

      } else {
        *c = *str;
      }
      c++;
      str++;
    }

    *c = '\0';
  }
  return (void *)dest;
}

void *s21_trim(const char *src, const char *trim_chars) {
  if (src == NULL || trim_chars == NULL) return S21_NULL;

  const char *start = src;
  while (*start != '\0' && s21_strpbrk(start, trim_chars) == start) {
    start++;
  }

  const char *end = src + s21_strlen(src) - 1;
  while (end >= start && s21_strpbrk(end, trim_chars) == end) {
    end--;
  }
  s21_size_t trimLength = end - start + 1;
  char *trimStr = calloc(trimLength + 1, sizeof(char));
  int flag = 0;
  if (trimStr == NULL) {
    flag = 1;
  } else {
    s21_strncpy(trimStr, start, trimLength);
    trimStr[trimLength] = '\0';
  }
  return flag == 1 ? S21_NULL : trimStr;
}