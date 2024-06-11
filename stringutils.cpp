#include "./stringutils.h"

vector<string> splitInWords(string const &str, char delimiter)
{
  vector<string> words;
  string word = "";
  for (auto x : str)
  {
    if (x == delimiter)
    {
      words.push_back(word);
      word = "";
    }
    else
    {
      word = word + x;
    }
  }
  words.push_back(word);
  return words;
}

// (one (two three) four) (five six)") -> ["one (two three) four", "five six"]
vector<string> splitInParenthesesGroups(string const &str)
{
  vector<string> tokens;
  string token;
  int level = 0;
  for (char c : str)
  {
    if (c == '(')
    {
      if (level > 0)
        token += c;
      level++;
    }
    else if (c == ')')
    {
      level--;
      if (level > 0)
        token += c;
      else if (level == 0)
      {
        tokens.push_back(token);
        token.clear();
      }
    }
    else if (level > 0)
    {
      token += c;
    }
  }
  return tokens;
}

ostream &operator<<(ostream &os, const vector<string> &arr)
{
  os << "[ ";
  for (auto x : arr)
  {
    os << x << ", ";
  }
  os << "]";
  return os;
}
