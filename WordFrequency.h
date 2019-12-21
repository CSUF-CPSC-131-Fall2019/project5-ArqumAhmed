#pragma once
#include <string>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <iterator>
#include "sanitize.h"

using std::string;
using namespace std;

class WordFrequency {
private:
     // TO BE COMPLETED
     int letter;
     int letter_count;
     string new_letter;
     std::unordered_map<std::string,int> total_letter;

public:
    WordFrequency(); // default constructor
    void readIn(const string & filename); // add words from file to hash table
    size_t numberOfWords(); // return the number of unique words
    size_t wordCount(const string & word); // return the number of occurrences of the given word
    string mostFrequentWord(); // return the most frequent word
    size_t maxBucketSize(); // return the size of the largest bucket in the hash table
    bool isEndPunctuation(const char letter1);
};

WordFrequency::WordFrequency()//default constructor
{
  new_letter = " ";
  letter = 0;
}

bool WordFrequency::isEndPunctuation(const char letter1)//return true if character ends with ?, !, '.'. else reaturns false
{
  if((letter1 == '?') || (letter1 == '!') || (letter1 == '.'))
  {
    return true;
  }
  else
  {
    return false;
  }
}


size_t WordFrequency::numberOfWords()
{
  return total_letter.size();//returns the number of total words
}

size_t WordFrequency:: wordCount( const string & word)//returns how many times a word would show up
{
  letter_count = total_letter[word];
  return letter_count;
}

void WordFrequency::readIn(const string & filename)//reads in the unordered map
{
  fstream myfile;
  string line;
  myfile.open(filename);

  while (myfile >> line)
  {
    sanitize(line);
    if(isEndPunctuation(line.at(line.size()-1)))
    {
      total_letter[line.substr(0,line.size()-1)]++;//increamenting using the substr function
    }
    else
    {
      total_letter[line]++;
    }
  }
  myfile.close();

  }

  string WordFrequency::mostFrequentWord()//returns the string that holds the maximum value.
  {
    int max = 0;
    string letter_2;
    for( auto i = total_letter.begin(); i != total_letter.end(); i++)//declaring an iterator using auto.
    {
      if((i -> second) >= max)
      {
        max = i -> second;
        letter_2 = i -> first;
      }
    }
    return letter_2;
  }

  size_t WordFrequency::maxBucketSize()//returns the maximum size buckect using the hash tables.
  {
    size_t max = 0;
    for(int i = 0; i < total_letter.bucket_count(); i++)
    {
      if(total_letter.bucket_size(i) >= max)//looking for the maximum bucket size
      {
        max = total_letter.bucket_size(i);
      }
    }
    return max;
  }
