#ifndef ASSEM_INFO_H_INCLUDED
#define ASSEM_INFO_H_INCLUDED

constexpr int size_time      = 40;
constexpr int MAX_LABELS     = 50;
constexpr int MAX_LABEL_SIZE = 20;

struct Line
{
    char *line  = nullptr;              // pointer to line
    long length = 0;                    // length of line
};


class Text
{
private:
    char* data_              = nullptr;  // pointer on buffer
    Line* lines_             = nullptr;  // pointer to the line struct
    int num_of_lines_        = 0;        // number of lines
    int length_file_         = 0;        // size of buffer
	FILE* user_code_		 = nullptr;

//! Private GETTERS (use in Text constructor)
   	get_num_of_lines_buffer_length_of_file();
   	get_lines_pointer(Line *lines);

public:
	Text(FILE *user_code, bool need_dump = false);
   ~Text();

//! GETTERS
int	get_length_file();
int get_num_of_lines();
int get_length(size_t number_of_line);
char get_char(size_t number_of_line, size_t number_of_char);
	dump();

};


class Code
{
private:

	char*   data_   	= nullptr;  // pointer to buffer of code
    int     length_ 	= 0;        // length of buffer
    int     terms_  	= 0;        // numbers of lexeme
	int  	cur_size_	= 0;		// cur code size need for lexeme reading

public:

	Code(Text* text_struct, bool need_dump = false);
   ~Code();

//! GETTERS

	dump();
int	get_terms();
int get_cur_size();
char get_char(size_t number);

//! SETTERS
	set_cur_size(size_t number);
};

class Bytecode
{
private:

	double* data_              = nullptr;
	char*   unknown_command_   = nullptr;
	int 	error_state_	   = 0;
    int     bytecode_capacity_ = 0;

public:

	Bytecode(Code *code_class, bool need_debug = false);
   ~Bytecode();

//! GETTERS

int get_error_state();
char* get_unknown_command();


//! SETTERS

	set_error_state(int number);
	set_unknown_command(char* command);
	set_int_to_data(size_t number, int digit);
	determine_status();

//! Other

	print_good(FILE* error);
	print_error(FILE* error, int error_bit);
};

struct Label
{
    char* name    = nullptr;
    size_t length = 0;
    int adress    = 0;
};


#endif // ASSEM_INFO_H_INCLUDED
