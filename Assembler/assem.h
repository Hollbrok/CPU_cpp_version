#ifndef ASSEM_H_INCLUDED
#define ASSEM_H_INCLUDED

#include <Txlib.h>
#include <time.h>
#include "assem_info.h"

#include "Commands.h"

using number_of_labels = int;

#define cmd_check(name, command)   \
	else if (!strcmp(temp, #name)) \
		data_[i] = command;

#define rix_check(name, command)                  \
	else if (!strcmp(temp, #name))                \
	{                                             \
		data_[i] = command;           \
		specifiers[flags_size++] = S_REGIST_SPEC; \
		IS_LAST_COMMAND_PUSH = false;             \
	}

#define transition_check(name, command) \
	else if (!strcmp(temp, #name))      \
	{                                   \
		data_[i] = command; \
		IS_LAST_COMMAND_JMP = true;     \
	}

#define bracket_check(bracket)   \
	else if (temp[0] == bracket) \
		bracket_exe(bracket, temp, this, &flags_size, specifiers, i);


auto set_time(struct tm *time) -> char *;

auto define_date(void) -> char *;

auto error_process(int i, char *temp) -> int;

//auto get_byte(int digit, int number_of_bit) -> bool;

auto get_labels(Label *labels, Code *code_class) -> number_of_labels;

inline get_lexeme(int *j, Code *code_class, char *temp);

inline bracket_exe(char spec, char *temp, Bytecode *byte_class, int *flags_size, double *specifiers, int i);

auto define_specs(int *SPEC_NUMBER, int *SPEC_REGIST, char spec) -> int;

auto get_byte(int digit, int number_of_bit) -> bool;

#endif // ASSEM_H_INCLUDED
