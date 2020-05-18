#pragma once

#include "Vector.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <math.h>
using namespace std;

int string2int(string a, int i=0)
{
	int aLen=0;
	for (int i=0; a[i]!=0; i++)
		aLen++;
	if (i == aLen)
		return 0;
	int b = (a[i] - '0');
	for (unsigned int j = 0; j < aLen - i - 1;j++)
		b *= 10;
	b += string2int(a, i + 1);
	return b;
}
bool strCmp(string a, string b)
{
	unsigned int s = b.length();
	if (a.length() != s)
		return false;
	for (unsigned int i = 0; i < s; i++)
	{
		if (a[i] != b[i])
			return false;
	}
	return true;
}
bool operator==(string a, string b)
{
	return strCmp(a, b);
}
/*template <typename T>
T& operator<<(T& o, string p)
{
	for (int i = 0; i < p.length(); i++)
	{
		o<<p[i];
	}
	return o;
}*/
string int2str(int i)
{
	if (i < 10)
	{
		string a = "a";
		a[0] = static_cast<char>(i + '0');
		return a;
	}
	string a = "";
	a += int2str(i / 10);
	a += int2str(i % 10);
	return a;
}
char* str2CharArray(string a)
{
	char* b = new char[a.length() + 1];
	for (int i = 0; i < a.length(); i++)
	{
		b[i] = a[i];
	}
	b[a.length()] = 0;
	return b;
}
float string2float(string a)
{
	int i = 0;
	float num = 0, f = 0.1;
	for (i = 0; a[i] != '.';i++) {
		num = num * 10 + (a[i] - 48);
	}
	i++;
	for (int j = i; j < a.length();j++) {
		num += (a[j] - 48)*f;
		f = f*0.1;
	}
	return num;
}
string charArray2String(char* a, unsigned int size)
{
	string b = "";
	for (unsigned int i = 0; i < size; i++)
	{
		if (a[i] == 0)
			break;
		else
			b += a[i];
	}
	return b;
}
Vector<string> split(string line, const char* delim)
{
Vector<string> toks;
	char *token = strtok_s(str2CharArray(line), delim, new char*);
	while (token)
	{
		toks.addAtEnd(charArray2String(token,strlen(token)));
		token = strtok_s(NULL, delim,new char*);
	}
	return toks;
}
void split(char token, Vector<string>& tokens, string data)
{
	tokens.clear();
	string temp; bool quotes = false;
	for (unsigned int i = 0; i < data.length(); i++) {
		if (data[i] == '"') {
			if (quotes == true)
				quotes = false;
			else
				quotes = true;
			i++;
		}
		if (quotes == true)
			temp += data[i];
		else {
			if (data[i] != token)
				temp += data[i];
			else {
				string t = "";
				if (!strCmp(temp, t))
					tokens.addAtEnd(temp);
				temp = "";
			}
		}
	}
	tokens.addAtEnd(temp);
}
