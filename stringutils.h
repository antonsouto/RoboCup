#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <string>
#include <iostream>
#include <vector>

using namespace std;

/**
 * function that splits a string in parentheses ( ) groups. (one (two three) four) -> one (two three) four
 * @param str string to split
 * @return vector<string> with the groups
 * @example splitInParenthesesGroups("(one (two three) four)") -> ["one (two three) four"]
 * @example splitInParenthesesGroups("(one (two three) four) (five six)") -> ["one (two three) four", "five six"]
 */
vector<string> splitInParenthesesGroups(string const &str);

/**
 * function that splits a string in words. "one two three" -> one two three
 * @param str string to split
 * @param delimiter character to split the string by default is ' '
 * @return vector<string> with the words
 * @example splitInWords("one two three") -> ["one", "two", "three"]
 */
vector<string> splitInWords(string const &str, char delimiter = ' ');

/**
 * cout an array of strings
 * @param arr array of strings
 */
ostream &operator<<(ostream &os, const vector<string> &arr);

#endif // STRINGUTILS_H
