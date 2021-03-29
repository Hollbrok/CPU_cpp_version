#include "cpu.h"

int main()
{
    printf("CPU in progress..\n");

    FILE* text = fopen("[!]assembler_code.txt", "rb");


    struct Bytecode byte_struct = {};
    get_bytecode(text, &byte_struct);

    Stack stk("def_stack", 100);
    Stack stk_call("stack_call", 100);

    CPU(&byte_struct, &stk, &stk_call);

    bytecode_destruct(&byte_struct);

    //txMessageBox("������!");
    printf("DONE!!\n");

    return 0;
}
