#pragma once

#include <cstdio>
#include <cstring>

inline char *split(char *str, char ch = ',') {
	for (int i = 0; *(str + i) != '\0'; i++) {
		if (*(str + i) == ch) {
			*(str + i) = '\0';
			return str + i + 1;
		}
	}
	return nullptr;
}

template<typename T>
inline char *toBuf(char *buf, T &a) {
	memcpy((void*)buf, (void*)&a, sizeof(a));
	return buf + sizeof(a);
}

template<typename T>
inline char *fromBuf(char *buf, T &a) {
	memcpy((void*)&a, (void*)buf, sizeof(a));
	return buf + sizeof(a);
}