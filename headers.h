int shrill_execute(char ** str, int * proc_list, char ** proc_name, int *proc_count);
char **shrill_split_cmd(char *line);
char **shrill_split_line(char *line);
char *shrill_read_line(void);
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

