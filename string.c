#include "shell.h"

/**
 * _strlen - Returns the length of a string
 * @s: String whose length to check
 *
 * Return: integer length of string
 */
int _strlen(const char *s)
{
	int length = 0;

	if (!s)
		return (0);

	while (s[length])
		length++;

	return (length);
}

/**
 * _strcmp - Performs a comparison of two strings
 * @s1: First string
 * @s2: Second string
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	if (*s1 == *s2)
		return (0);
	else
		return ((*s1 < *s2) ? -1 : 1);
}

/**
 * starts_with - Check if needle starts with haystack
 * @haystack: String to search
 * @needle: Substring to find
 *
 * Return: Address of next character of haystack or NULL
 */
const char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
	{
		if (*needle != *haystack)
			return (NULL);

		needle++;
		haystack++;
	}

	return (haystack);
}

/**
 * _strcat - Concatenates two strings
 * @dest: Destination buffer
 * @src: Source buffer
 *
 * Return: Pointer to destination buffer
 */
char *_strcat(char *dest, const char *src)
{
	char *c = dest;

	while (*dest)
		dest++;

	while (*src)
		*dest++ = *src++;

	*dest = '\0';
	return (c);
}
