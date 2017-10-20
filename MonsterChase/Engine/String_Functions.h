#pragma once
#pragma once
class String_Functions
{
public:
	String_Functions();
	~String_Functions();
	
};


namespace String_FunctionsProxy {
	char* str_cpy(char* dest, const char* src);
	char* str_cat(char* dest, const char* src);
	int str_length(const char* string);
}