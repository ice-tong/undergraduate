#include "String.h"

int String:: num_allocations = 0;

String:: String(const char *s)
{
    buf = strdup(s);
}

String:: String(const String & s)
{
    buf = strdup(s.buf);
}

String String:: operator = (const String & s)
{
    delete_char_array(buf);
    buf = strdup(s.buf);
    return *this;
}

char & String:: operator [] (int index)
{
    if (! inBounds(index))
    {
	cerr << "ERROR: index out of bounds" << endl;
	index = 0;
    }
    return buf[index];
}

int String:: size()
{
    return strlen(buf);
}

String String:: reverse()
{
    char rev[size()+1];
    reverse_cpy(rev, buf);
    String temp(rev);
    return temp;
}

int String:: indexOf(const char c)
{
    char *s = strchr(buf, c);
    if (s == NULL)
	return -1;
    for (int i = 0; buf[i] != '\0'; ++i)
    {
	if (buf[i] == s[0])
	    return i;
    }
}

int String:: indexOf(const String pattern)
{
    char *s = strstr(buf, pattern.buf);
    if (s == NULL)
	return -1;
    for (int i = 0; buf[i] != '\0'; ++i)
    {
	if (strncmp(s, &buf[i], strlen(s)) == 0)
	    return i;
    }
}

bool String:: operator == (const String s)
{
    return strcmp(buf, s.buf) == 0;
}

bool String:: operator != (const String s)
{
    return strcmp(buf, s.buf) != 0;
}

bool String:: operator > (const String s)
{
    return strcmp(buf, s.buf) > 0;
}

bool String:: operator < (const String s)
{
    return strcmp(buf, s.buf) < 0;
}

bool String:: operator <= (const String s)
{
    return strcmp(buf, s.buf) <= 0;
}

bool String:: operator >= (const String s)
{
    return strcmp(buf, s.buf) >= 0;
}

String String:: operator + (const String s)
{
    char * cat = new_char_array(size()+strlen(s.buf)+1);
    strcpy(cat, buf);
    strcat(cat, s.buf);
    String result(cat);
    delete_char_array(cat);
    return result;
}

String String:: operator += (const String s)
{
    char * holder = buf;
    buf = new_char_array(size()+strlen(s.buf)+1);
    strcpy(buf, holder);
    strcat(buf, s.buf);
    delete_char_array(holder);
    return *this;
}

String:: ~String()
{
    delete_char_array(buf);
}

int String:: allocations()
{
    return num_allocations;
}


void String:: print(ostream & out)
{
    out << buf;
}

void String:: read(istream & in)
{
    char input[128];
    in.getline(input, 128);
    delete_char_array(buf);
    buf = strdup(input);
}




// Private

char * String:: new_char_array(int n_bytes)
{
    ++num_allocations;
    return new char[n_bytes];
}

void String:: delete_char_array(char *p)
{
    --num_allocations;
    delete[] p;
}

bool String:: inBounds(int i)
{
    return i >= 0 && i < strlen(buf);
}

int String:: strlen(const char *s)
{
    int len;
    for (len = 0; s[len] != '\0'; ++len)
    {}
    return len;
}

char * String:: strcpy(char *dest, const char *src)
{
    int i;
    for (i = 0; src[i] != '\0'; ++i)
	dest[i] = src[i];
    dest[i] = '\0';
    return dest;
}

char * String:: strdup(const char *src)
{
    char * dup = new_char_array(strlen(src)+1);;
    return strcpy(dup, src);
}

char * String:: strcat(char *dest, const char *src)
{
    strcpy(dest + strlen(dest), src);
    return dest;
}

int String:: strcmp(const char *left, const char *right)
{
    for (int i = 0; left[i] != '\0' || right[i] != '\0'; ++i)
    {
	if (left[i] != right[i])
	    return left[i] - right[i];
    }
    return 0;
}

int String:: strncmp(const char *left, const char *right, int n)
{
    for (int i = 0; (left[i] != '\0' || right[i] != '\0') && i < n; ++i)
    {
	if (left[i] != right[i])
	    return left[i] - right[i];
    }
    return 0;
}

char * String:: strchr(char *str, int c)
{
    int i;
    for (i = 0; str[i] != '\0'; i++)
    {
	if (str[i] == c)
	    return &str[i];
    }
    if (c == '\0')
	return &str[i];
    return NULL;
}

char * String:: strstr(char *haystack, const char *needle)
{
    for (int i = 0; haystack[i] != '\0'; ++i)
    {
	if (needle[0] == haystack[i]
	&& strncmp(&haystack[i], needle, strlen(needle)) == 0)
	    return &haystack[i];
    }
    return NULL;
}

void String:: reverse_cpy(char *dest, const char *src)
{
    int dest_index = 0;
    for (int i = strlen(src) - 1; i >= 0; --i)
	dest[dest_index++] = src[i];
    dest[dest_index] = '\0';
}



// <iostream>

ostream & operator << (ostream & out, String str)
{
    str.print(out);
    return out;
}

istream & operator >> (istream & in, String & str)
{
    str.read(in);
    return in;
}
