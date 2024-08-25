#include "compiler.h"

int compile_file(const char* filename, const char* out_filename, int flags)
{
    struct compile_process* process = compile_process_create(filename, out_filename, flags);
    if(!process)
        return COMPILER_FAILED_WITH_ERRORS;
    
    //词法分析
    //解析产生抽象语法
    //树代码生成
    return COMPILER_FILE_COMPILED_OK;
}