#include "assem.h"

int main()	//int main(int argc, char *argv[])
{
    printf("Assembling in progress..\n");

    FILE* user_code = fopen("user_code[for user].txt", "rb");	// fopen(argv[1], "rb");
    assert(user_code);

    Text text_class(user_code, true);

    Code code_class(&text_class, true);

    Bytecode byte_class(&code_class, true);

    printf("DONE!!\n");
    fclose(user_code);

    return 0;
}
