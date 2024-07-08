//---------------------------------------------------------------------------

#ifndef tokenizeH
#define tokenizeH
//---------------------------------------------------------------------------

#if defined(__BORLANDC__) && defined(__clang__) && defined(_WIN32) && !defined(_WIN64)
#include <string.h>    
#include <stdlib.h>  
#include <cctype>  // Include the cctype header  
#include <sstream>
#define AnsiString std::string 
#define Length length
#else 
#include <vcl.h>
#endif


#define DEFINE_NULL    0
#define DEFINE_SPACES  1
#define CHAR_TYPE      2
#define SEPARATORS     3
#define NEWLINE_CHAR   4

#define HASH_DIRECTIVE 5
#define OPERATOR_TYPE  6
#define HEX_TYPE       7
#define DIGITS_TYPE    8
#define FUNCTION_TYPE  9
#define STRING_TYPE    10
#define LANG_KEYWORD   11
#define COMMON_TYPE    12
#define MULTI_COMMENT  13
#define SINGLE_COMMENT 14


void colorize_it(const char* input_file, const char* output_file);


#endif

