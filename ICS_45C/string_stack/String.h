#include <iostream>
#include <cassert>
using namespace std;

#define MAXLEN 128

class String
{
public:
    explicit String(const char *s = "")
    {
	assert(strlen(s) < MAXLEN);
	strcpy(buf, s);
    }

    String(const String & s)
    {
	assert(strlen(s.buf) < MAXLEN);
	strcpy(buf, s.buf);	
    }

    String operator = (const String & s)
    {
	strcpy(buf, s.buf);	
    }

    char & operator [] (int index)
    {
	if (! inBounds(index))
	{
	    cerr << "ERROR: index out of bounds" << endl;
	    index = 0;
	}
	return buf[index];
    }

    int size()
    {
	return strlen(buf);
    }

    String reverse()
    {
	char rev[MAXLEN];
	reverse_cpy(rev, buf);
	String temp(rev);
	return temp;
    }

    int indexOf(const char c)
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

    int indexOf(const String pattern)
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

    bool operator == (const String s)
    {
	return strcmp(buf, s.buf) == 0;
    }

    bool operator != (const String s)
    {
	return strcmp(buf, s.buf) != 0;
    }

    bool operator > (const String s)
    {
	return strcmp(buf, s.buf) > 0;
    }

    bool operator < (const String s)
    {
	return strcmp(buf, s.buf) < 0;
    }

    bool operator <= (const String s)
    {
	return strcmp(buf, s.buf) <= 0;
    }

    bool operator >= (const String s)
    {
	return strcmp(buf, s.buf) >= 0;
    }

    String operator + (const String s)
    {
	return String(strcat(buf, s.buf));
    }

    String operator += (const String s)
    {
	return String(strcat(buf, s.buf));
    }

    void print(ostream & out)
    {
	out << buf;
    }

    void read(istream & in)
    {
	in.getline(buf, MAXLEN);
    }

    ~String() {}


private:

    char buf[MAXLEN];

    bool inBounds(int i)
    {
	return i >= 0 && i < strlen(buf);
    }

    static int strlen(const char *s)
    {
	int len;
	for (len = 0; s[len] != '\0'; ++len)
	{}
	return len;
    }

    static char * strcpy(char *dest, const char *src)
    {
	int i;
	for (i = 0; src[i] != '\0' && i < MAXLEN - 1; ++i)
	    dest[i] = src[i];
	dest[i] = '\0';
	return dest;
    }

    static char * strcat(char *dest, const char *src)
    {
	strcpy(dest + strlen(dest), src);
	return dest;
    }

    static int strcmp(const char *left, const char *right)
    {
	for (int i = 0; left[i] != '\0' || right[i] != '\0'; ++i)
	{
	    if (left[i] != right[i])
		return left[i] - right[i];
	}
	return 0;
    }

    static int strncmp(const char *left, const char *right, int n)
    {
	for (int i = 0; (left[i] != '\0' || right[i] != '\0') && i < n; ++i)
	{
	    if (left[i] != right[i])
		return left[i] - right[i];
	}
	return 0;
    }

    static char * strchr(char *str, int c)
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

    static const char * strstr(const char *haystack, const char *needle)
    {
	return strstr((char *)haystack, needle);
    }

    static char * strstr(char *haystack, const char *needle)
    {
	for (int i = 0; haystack[i] != '\0'; ++i)
	{
	    if (needle[0] == haystack[i]
	    && strncmp(&haystack[i], needle, strlen(needle)) == 0)
		return &haystack[i];
	}
	return NULL;
    }

    static void reverse_cpy(char *dest, const char *src)
    {
	int dest_index = 0;
	for (int i = strlen(src) - 1; i >= 0; --i)
	{
	    dest[dest_index++] = src[i];
	}
	dest[dest_index] = '\0';
    }
};

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
