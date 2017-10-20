#include "String_Functions.h"
String_Functions::String_Functions()
{
}
String_Functions::~String_Functions()
{
}


int String_FunctionsProxy::str_length(const char* string) {
	int i = 0, length = 0;
	for (i = 0; string[i] != '\0'; i++)
	{
		length++;
	}
	return length;
}
char* String_FunctionsProxy::str_cpy(char* dest, const char* src) {
	int i = 0;
	for (i = 0; src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}
	dest[i] = ' ';
	dest[i + 1] = '\0';
	return dest;
}
char* String_FunctionsProxy::str_cat(char* dest, const char* src) {
	int i, j;
	for (i = 0; dest[i] != '\0'; ++i);
	for (j = 0; src[j] != '\0'; ++j, ++i)
	{
		dest[i] = src[j];
	}
	dest[i] = ' ';
	dest[i + 1] = '\0';
	return dest;
}