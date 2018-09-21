int shrill_execute(char ** str);
char **shrill_split_cmd(char *line);
char **shrill_split_line(char *line);
// char *parse_line(char * str);
char *shrill_read_line(void);
char **shrill_split_pip(char *line);

int is_dir(const char* path) ;
char* permissions(char *file);
void print_longlist(char * filePath, char * fileName);
void ls(char ** str);
void cd(char ** str);
void echo_func(char ** str);
void pwd();
int remindme(char ** str);
void clock_func(char ** str);
void pinfo(int proc_id);
void jobs (char ** str);
void overkill();
void kjob(char ** str);
void fg (char ** str);
void bg (char ** str);
void setenv_func(char ** str);
void unsetenv_func(char ** str);







