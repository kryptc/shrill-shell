#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define SHRILL_TOK_DELIM " \t\r\n\a"
#define SHRILL_CMD_DELIM ";"
#define SHRILL_PIP_DELIM "|"

char **shrill_split_pip(char *line)
{
  int i = 0;
  char **tokens = malloc(2000 * sizeof(char*));
  char *token;

  token = strtok(line, SHRILL_PIP_DELIM);
  while (token != NULL) 
  {
    tokens[i] = token;
    i++;
    token = strtok(NULL, SHRILL_PIP_DELIM);
  }
  tokens[i] = NULL;
  return tokens;
}

char **shrill_split_cmd(char *line)
{
  int i = 0;
  char **tokens = malloc(2000 * sizeof(char*));
  char *token;

  token = strtok(line, SHRILL_CMD_DELIM);
  while (token != NULL) 
  {
    tokens[i] = token;
    i++;
    token = strtok(NULL, SHRILL_CMD_DELIM);
  }
  tokens[i] = NULL;
  return tokens;
}

char **shrill_split_line(char *line)
{
  int i = 0;
  char **tokens = malloc(2000 * sizeof(char*));
  char *token;

  token = strtok(line, SHRILL_TOK_DELIM);
  while (token != NULL) 
  {
    tokens[i] = token;
    i++;
    token = strtok(NULL, SHRILL_TOK_DELIM);
  }
  tokens[i] = NULL;
  return tokens;
}


char *shrill_read_line(void)
{
  char *line = NULL;
  size_t bufsize = 0; // have getline allocate a buffer for us
  getline(&line, &bufsize, stdin);
  return line;
}

