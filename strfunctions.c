#include "shell.h"



int mystrlen(char *str) {
	int i = 0;

	while (str[i] != '\0')
		i++;
	return (i);
}


int mystrcmp(char *str1, char *str2) {
	int i = 0;

	while (str1[i] != '\0' && str2[i] != '\0') {
		if (str1[i] != str2[i])
			return (-1);
		i++;
	}
	return (0);
}


int mycuststrncmp(char *str1, char *str2, int n) {
	int i = 0;

	while (str1[i] != '\0' && str2[i] != '\0' && i < n) {
		if (str1[i] != str2[i])
			return (-1);
		i++;
	}
	if (i == n)
		return (0);
	return (-1);
}


char *mystrdup(char *str) {
	int i = 0;
	char *dup = NULL;

	if (str == NULL)
		return (NULL);
	dup = malloc(sizeof(char) * (mystrlen(str) + 1));
	if (dup == NULL)
		return (NULL);
	while (str[i] != '\0') {
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}


char *concatpaths(char *dest, char *src) {
	int i = 0, j = 0;
	char *concat = NULL;

	concat = malloc(sizeof(char) * (mystrlen(dest) + mystrlen(src) + 1));
	if (concat == NULL)
		return (NULL);
	while (dest[i] != '\0') {
		concat[i] = dest[i];
		i++;
	}
	while (src[j] != '\0') {
		concat[i] = src[j];
		i++;
		j++;
	}
	concat[i] = '\0';
	return (concat);
}

char *mystrcpy(char *dest, char *src) {
	int i = 0;

	while (src[i] != '\0') {
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char *_strcat(char *dest, char *src) {
	int i, j;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;

	while (src[j] != '\0') {
		dest[i] = src[j];
		j++;
		i++;
	}

	dest[i] = '\0';

	return (dest);
}


char *_strchr(char *s, char c) {
	int i = 0;

	while (s[i] != '\0') {
		if (s[i] == c)
			break;
		i++;
	}

	if (s[i] == c)
		return (s + i);
	else
		return (NULL);
}

char *_strtok(char *str, char *delim) {
	static char *token;
	static char *next;
	char *delim_ptr;

	if (str != NULL)
		next = str;
	if (next == NULL)
		return (NULL);
	token = next;
	delim_ptr = _strchr(token, *delim);

	if (delim_ptr != NULL) {
		*delim_ptr = '\0';
		next = delim_ptr + 1;
	}
	else
		next = NULL;
	return (token);
}

char *splitstr(char *str) {
	int i = 0;

	while (str[i] != '\0') {
		if (str[i] == '#') {
			str[i] = '\0';
			break;
		}
		i++;
	}
	return (str);
}

int constcharlength(const char *str) {
	int i = 0;

	while (str[i] != '\0')
		i++;
	return (i);
}
