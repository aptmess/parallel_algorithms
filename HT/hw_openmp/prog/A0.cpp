#include <iostream>

using namespace std;

int count_words(char* str)
{

   bool sep_flag = true;
   int word_counter = 0;

   while (*str)
   {
      if (*str == ' ' || *str == '\n' || *str == '\t')
      {
         sep_flag = true;
      }
      else if (sep_flag)
      {
         sep_flag = false;
         word_counter = word_counter + 1;
      }

      ++str;
   }

   return word_counter;
}

int main(int argc, char* argv[])
{
    if (argc > 1)
    {
        printf("input string `%s` has %d words\n", argv[1], count_words(argv[1]));
    }
    else
    {
        cout << "error:: no arguments given" << endl;
    }
    return 0;
}
