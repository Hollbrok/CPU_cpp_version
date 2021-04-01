#ifndef CPU_INFO_H_INCLUDED
#define CPU_INFO_H_INCLUDED

constexpr int START_SIZE    = 100;
constexpr int size_time     = 40;
constexpr double epsilon    = 1e-8;
constexpr double absEpsilon = 1e-12;

constexpr int SIZEX         = 300;
constexpr int SIZEY         = 300;
constexpr int OP_SIZE       = 3 * SIZEX * SIZEY;

class Stack;
struct Rix;

class Bytecode
{
private:

	double* data_                = nullptr;
    int     unknown_command_     = -666;
    int     bytecode_capacity_   = 0;
	int 	error_state_ 	     = 0;
	bool 	find_hlt_ = 0;

//!PRIVATE MAIN

	determine_status(Stack* stk);
	cmd_push_exe(int command, int i, Stack* stk, Rix* rix_struct, char* OP);
	cmd_pop_exe(int command, int i, Stack *stk, Rix *rix_struct, char *OP);
	cmd_compair_exe(int command, Stack* stk, int *i);
	draw_circ(char* OP, Stack* stk);

public:

	Bytecode(FILE* text);
	~Bytecode();

//!PUBLIC GETTERS



//!PUBLIC MAIN
	CPU();

};

struct Rix
{
    double rax = NAN;
    double rbx = NAN;
    double rcx = NAN;
    double rdx = NAN;
};

namespace memes_names
{
    enum Commands
    {
		DED_CODESTYLE 	 = 0,
		DED_ILAB_CLASSIC = 1,
		CAT              = 2,
		BOMONKA			 = 3,
		DED_HOHLOV		 = 4,
		CODING_BUGS		 = 5
	};
}

#endif // CPU_INFO_H_INCLUDED
