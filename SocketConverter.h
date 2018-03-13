#pragma once

#include <cstdio>
#include <cstring>

char *split(char *str, char ch = ',') {
	for (int i = 0; *(str + i) != '\0'; i++) {
		if (*(str + i) == ch) {
			*(str + i) = '\0';
			return str + i + 1;
		}
	}
	return nullptr;
}

inline char *toBuf(char *buf, int a) {
	return buf + sprintf(buf, "%d,", a);
}

inline char *toBuf(char *buf, char *b) {
	return buf + sprintf(buf, "%s,", b);
}

inline char *toBuf(char *buf, double c) {
	return buf + sprintf(buf, "%lf,", c);
}

char *fromBuf(char *buf, int &a) {
	char *next = split(buf);
	sscanf(buf, "%d", &a);
	return next;
}

char *fromBuf(char *buf, char *b) {
	char *next = split(buf);
	sscanf(buf, "%s", b);
	return next;
}

char *fromBuf(char *buf, double &c) {
	char *next = split(buf);
	sscanf(buf, "%lf", &c);
	return next;
}
