/*
 * Include the provided hash table library.
 */
#include "hashtable.h"

/*
 * Include the header file.
 */
#include "philspel.h"

/*
 * Standard IO and file routines.
 */
#include <stdio.h>

/*
 * General utility routines (including malloc()).
 */
#include <stdlib.h>

/*
 * Character utility routines.
 */
#include <ctype.h>

/*
 * String utility routines.
 */
#include <string.h>

/*
 * This hash table stores the dictionary.
 */
HashTable *dictionary;

typedef struct string
{
  char *value;
  int size;
} string;

string *create_str(char *str)
{
  int len = strlen(str);
  string *s = (string *)malloc(sizeof(string));
  s->value = (char *)malloc(len + 1);
  s->size = len;
  s->value = strcpy(s->value, str);
  s->value[len] = '\0';
  return s;
}

void grow_string(string *str, int size)
{
  if (size < str->size)
  {
    return;
  }
  while (str->size < size)
  {
    str->size *= 2;
  }
  if (strlen(str->value) > str->size)
  {
    return;
  }
  str->value = (char *)realloc((void *)str->value, str->size);
}

void grow(string *str)
{
  if (str->size == 0)
  {
    str->size = 1;
  }
  grow_string(str, str->size * 2);
}

void appendc(string *str, char c)
{
  int len = strlen(str->value);
  if (len + 1 > str->size)
  {
    grow(str);
  }
  str->value[len] = c;
}

void append(string *str, char *s)
{
  if (str->size == 0)
  {
    str->size = 1;
  }
  int len = strlen(str->value);
  if (len + strlen(s) > str->size)
  {
    grow_string(str, len + strlen(s));
  }
  for (int i = 0; i < strlen(s); i++)
  {
    str->value[i + len] = s[i];
  }
  str->value[strlen(s) + len] = '\0';
}
/*
 * The MAIN routine.  You can safely print debugging information
 * to standard error (stderr) as shown and it will be ignored in
 * the grading process.
 */
int main(int argc, char **argv)
{
  if (argc != 2)
  {
    fprintf(stderr, "Specify a dictionary\n");
    return 0;
  }
  /*
   * Allocate a hash table to store the dictionary.
   */
  fprintf(stderr, "Creating hashtable\n");
  dictionary = createHashTable(2255, &stringHash, &stringEquals);

  fprintf(stderr, "Loading dictionary %s\n", argv[1]);
  readDictionary(argv[1]);
  fprintf(stderr, "Dictionary loaded\n");
  fprintf(stderr, "Processing stdin\n");
  processInput();

  /*
   * The MAIN function in C should always return 0 as a way of telling
   * whatever program invoked this that everything went OK.
   */
  return 0;
}

/*
 * This should hash a string to a bucket index.  Void *s can be safely cast
 * to a char * (null terminated string) and is already done for you here
 * for convenience.
 */
unsigned int stringHash(void *s)
{
  char *string = (char *)s;
  int count = 1;
  while (count < strlen(string))
  {
    count *= 2;
  }
  int hash = 0;
  int len = strlen(string);
  for (int i = 0; i < len; i++)
  {
    hash += string[i] * i;
    hash = hash ^ (hash << 3);
  }
  return (count - 1) & hash;
}

/*
 * This should return a nonzero value if the two strings are identical
 * (case sensitive comparison) and 0 otherwise.
 */
int stringEquals(void *s1, void *s2)
{
  if (s1 == NULL || s2 == NULL)
  {
    return 0;
  }
  char *string1 = (char *)s1;
  char *string2 = (char *)s2;
  if (strlen(string1) != strlen(string2))
  {
    return 0;
  }
  for (int i = 0; i < strlen(s1); i++)
  {
    if (string1[i] != string2[i])
    {
      return 0;
    }
  }
  return 1;
}

/*
 * This function should read in every word from the dictionary and
 * store it in the hash table.  You should first open the file specified,
 * then read the words one at a time and insert them into the dictionary.
 * Once the file is read in completely, return.  You will need to allocate
 * (using malloc()) space for each word.  As described in the spec, you
 * can initially assume that no word is longer than 60 characters.  However,
 * for the final 20% of your grade, you cannot assumed that words have a bounded
 * length.  You CANNOT assume that the specified file exists.  If the file does
 * NOT exist, you should print some message to standard error and call exit(1)
 * to cleanly exit the program.
 *
 * Since the format is one word at a time, with new lines in between,
 * you can safely use fscanf() to read in the strings until you want to handle
 * arbitrarily long dictionary chacaters.
 */
void readDictionary(char *dictName)
{
  FILE *fp = fopen(dictName, "r");
  if (!fp)
  {
    fprintf(stderr, "File: %s does not exist", dictName);
    exit(-1);
  }
  while (1)
  {
    string *word = create_str("");
    char c = fgetc(fp);
    while (c != '\n')
    {
      appendc(word, c);
      c = fgetc(fp);
      if (c == EOF)
      {
        return;
      }
    }
    insertData(dictionary, (void *)word->value, (void *)word->value);
  }
  fclose(fp);
}

char *toLowerCase(string *s)
{
  int len = strlen(s->value);
  char *ss = (char *)malloc(len + 1);
  for (int i = 0; i < len; i++)
  {
    ss[i] = tolower(s->value[i]);
  }
  ss[len] = '\0';
  return ss;
}

char *toLowerExpectFirst(string *str)
{
  int len = strlen(str->value);
  char *ss = (char *)malloc(len + 1);
  ss[0] = str->value[0];
  for (int i = 1; i < len; i++)
  {
    ss[i] = tolower(str->value[i]);
  }
  ss[len] = '\0';
  return ss;
}
/*
 * This should process standard input (stdin) and copy it to standard
 * output (stdout) as specified in the spec (e.g., if a standard
 * dictionary was used and the string "this is a taest of  this-proGram"
 * was given to stdin, the output to stdout should be
 * "this is a teast [sic] of  this-proGram").  All words should be checked
 * against the dictionary as they are input, then with all but the first
 * letter converted to lowercase, and finally with all letters converted
 * to lowercase.  Only if all 3 cases are not in the dictionary should it
 * be reported as not found by appending " [sic]" after the error.
 *
 * Since we care about preserving whitespace and pass through all non alphabet
 * characters untouched, scanf() is probably insufficent (since it only considers
 * whitespace as breaking strings), meaning you will probably have
 * to get characters from stdin one at a time.
 *
 * Do note that even under the initial assumption that no word is longer than 60
 * characters, you may still encounter strings of non-alphabetic characters (e.g.,
 * numbers and punctuation) which are longer than 60 characters. Again, for the
 * final 20% of your grade, you cannot assume words have a bounded length.
 */
void processInput()
{
  char c;
  string *word = create_str("");
  string *res = create_str("");
  int eof = 0;
  while (!eof)
  {
    c = fgetc(stdin);
    if (c == EOF)
    {
      eof = 1;
    }
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
    {
      appendc(word, c);
    }
    else if (word->size != 0)
    {
      char *lower = toLowerCase(word);
      char *lower2 = toLowerExpectFirst(word);
      if (findData(dictionary, (void *)word->value) == NULL && findData(dictionary, lower) == NULL && findData(dictionary, lower2) == NULL)
      {
        append(word, " [sic]");
      }

      append(res, word->value);

      free(word->value);
      if (c != EOF)
      {
        appendc(res, c);
      }
      word = create_str("");
    }
    else
    {
      appendc(res, c);
    }
  }
  fputs(res->value, stdout);
  free(res->value);
  free(res);
  free(word->value);
  free(word);
}
