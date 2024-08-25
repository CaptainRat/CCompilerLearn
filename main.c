#include <stdio.h>
#include "helpers/vector.h"
#include "compiler.h"
int main()
{
    int res = compile_file("./test.c", "./test", 0);
    if(res == COMPILER_FILE_COMPILED_OK)
    {
        printf("编译完成\n");
    }
    else if(res == COMPILER_FAILED_WITH_ERRORS)
    {
        printf("编译失败\n");
    }
    else
    {
        printf("编译未知响应\n");
    }
    return 0;
}