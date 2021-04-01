#include "assem.h"

int main()	//int main(int argc, char *argv[])
{
    printf("Assembling in progress..\n");

    FILE* user_code = fopen("user_code[for user].asm", "rb");	// fopen(argv[1], "rb");
    assert(user_code);

    Text text_c(user_code);

    Code code_c(&text_c);

    Bytecode byte_c(&code_c);

    printf("DONE!!\n");
    fclose(user_code);

    return 0;
}
