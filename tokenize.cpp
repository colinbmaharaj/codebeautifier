
//---------------------------------------------------------------------------

#pragma hdrstop

#include "tokenize.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

#if defined(__BORLANDC__) && defined(__clang__) && defined(_WIN32) && !defined(_WIN64)
void madd(const char *s)
{
	printf("%s", s);
}
#else 
void madd(const char *s);
#endif 	

char tmp[65536];

#include <stdio.h>

//---------------------------------------------------------------------------

int isThreeCharKeyword(const char *s)
{
    char t[4]={0};
    if (!strchr(".-<>",s[0])) return 0;
    t[0]=s[0]; t[1]=s[1];t[2]=s[2];
    const char* threeCharOperators[] = {
    "...",    "->>",   "<<=",   ">>="};
    int sizeofarray = 4;
    for (int i = 0; i < sizeofarray; i++)
    {
      if (!strcmp(t, threeCharOperators[i]))
      {
        return strlen(threeCharOperators[i]);
      }
    }
    return 0;
}


//--------------------------------------------------------------------

 int isTwoCharKeyword(const char *s)
 {
    char t[4]={0};
    if (!strchr("([><=!&|+-:?",s[0])) return 0;
    t[0]=s[0]; t[1]=s[1];
    const char* twoCharKeywords[] = {
    ">=",   "<=",   "==",   "!=",   "&&",
    "||",   "++",   "--",   "->",   "::",
    "?:",   "<<",   ">>",   "[]",   "()"};
    int sizeofarray = 15;
    for (int i = 0; i < sizeofarray; i++)
    {
      if (!strcmp(t, twoCharKeywords[i]))
      {
        return strlen(twoCharKeywords[i]);
      }
    }
    return 0;
 }

 //--------------------------------------------------------------------

int isletter(char c)
{
  if ((c>='a'&& c<='z') || (c>='A'&& c<='Z')) { return 1; }
  return 0;
}

//--------------------------------------------------------------------


int isascii2(char c)
{
  if (isletter(c)) { return 1; }
  if (isdigit(c)) { return 1; }
  if (c=='_') { return 1; }
  return 0;
}


//--------------------------------------------------------------------
// Stops at the length of t, so checks the length of the keyword 
// But if the char at the end of the keyword is azAZ09_ then return 
// a mismatch or 1 
//--------------------------------------------------------------------

 int strcmp2(const char *s, const char *keywd)
 {
   int strlen_keywd = strlen(keywd);
   for (int i = 0; i < strlen_keywd; i++)
   {
     if (s[i]!=keywd[i]) { return s[i]-keywd[i]; }
   }
   if (!isascii2(s[strlen_keywd])) { return 0; }
   return 1; 
 }

//--------------------------------------------------------------------

 int isCommonKw(const char *s, char *ret)
 {
    char t[12]={0}; strncpy(t,s,10);t[10]='\0';
    const char* commkw[] = {
    "cout"    , "strcpy" , "strncpy", "strcmp"  , "cin"     ,
    "strcat"  , "strncat", "cerr"   , "endl"    , "ifstream",
    "ofstream", "getline", "strtok" , "sprintf" , "isspace" , 
	"printf"  , "strlen" , "isdigit", };
    #define sizeofarray 18
    static int ckLength[sizeofarray]={0};
    if (ckLength[0]==0) // should happen once
    { // so length is not used all the time
      for (int i = 0; i < sizeofarray; i++)
      ckLength[i]=strlen(commkw[i]);
    }

    for (int i = 0; i < sizeofarray; i++)
    {
      if (!strcmp2(t, commkw[i]))
      {
        strcpy(ret,commkw[i]);
        return ckLength[i];
      }
    }
    return 0;
 }

//--------------------------------------------------------------------

 int isDirective(const char *s, char *ret)
 {
    char t[12]={0}; strncpy(t,s,10);t[10]='\0';
    const char* preprocessorDirectives[] = {
    "#warning", "!defined", "#include", "#define", "#pragma",
	"#undef"  , "#ifndef" , "#ifdef"  , "#endif" , "#error" ,
	"#elif"   , "#else"   , "#line"   ,  "#if" };
    #define sizeofarray1 14
    static int ppLength[sizeofarray1]={0};
    if (ppLength[0]==0) // should happen once
    { // so length is not used all the time
      for (int i = 0; i < sizeofarray1; i++)
      ppLength[i]=strlen(preprocessorDirectives[i]);
    }

    for (int i = 0; i < sizeofarray1; i++)
    {
      if (!strcmp2(t, preprocessorDirectives[i]))
      {
        strcpy(ret,preprocessorDirectives[i]);
        return ppLength[i];
      }
    }
    return 0;
}

//--------------------------------------------------------------------

 int isKeyword(const char *s, char *ret)
 {
	char t[24]={0}; strncpy(t,s,18);t[18]='\0';
    const char* keywords[] = {
    "reinterpret_cast", "static_assert", "dynamic_cast", "thread_local", "constexpr",
    "__fastcall"      , "static_cast"  , "namespace"   , "protected"   , "unsigned" , 
	"continue"        , "explicit"     , "template"    , "register"    , "volatile" , 
	"noexcept"        , "typename"     , "nullptr"     , "alignas"     , "private"  , 
	"wchar_t"         , "typedef"      , "alignof"     , "default"     , "mutable"  , 
	"virtual"         , "sizeof"       , "export"      , "extern"      , "bitand"   , 
	"delete"          , "struct"       , "not_eq"      , "public"      , "return"   , 
	"signed"          , "static"       , "typeid"      , "union"       , "false"    , 
	"xor_eq"          , "and_eq"       , "switch"      , "using"       , "bitor"    , 
	"inline"          , "double"       , "compl"       , "size_t"      , "throw"    , 
	"true"            , "float"        , "const"       , "while"       , "short"    , 
	"break"           , "char"         , "class"       , "goto"        , "else"     , 
	"long"            , "void"         , "enum"        , "case"        , "int"      , 
	"new"             , "for"          , "if"          , "do"};                        
                                                                       
    #define sizeofarray2 69
    static int kwLength[sizeofarray2]={0};
    if (kwLength[0]==0) // should happen once..
    { // ..so length is not used all the time
      for (int i = 0; i < sizeofarray2; i++)
      kwLength[i]=strlen(keywords[i]);
    }

    for (int i = 0; i < sizeofarray2; i++)
    {
      if (!strcmp2(t, keywords[i]))
      {
        strcpy(ret,keywords[i]);
        return kwLength[i];
      }
    }
    return 0;

 }


//----------------------------------------------------------------------
// returns TOKEN and TYPE of TOKEN which will determine how to color it
//----------------------------------------------------------------------

int  getToken(const char *s, int pos, int & incby, char *tok)
{
  incby=0;
  s += pos; int p=0; char d=0;

  // Deal with 3,2,1 operators ________________________________
  #define strcpy1(tok,c) tok[0]=c;tok[1]='\0';
  #define strcpy2(tok,c) tok[0]=c[0];tok[1]=c[1];tok[2]='\0';

  if (*s=='\r' || *s=='\n')
  {
    incby=1;strcpy1(tok,s[0]);
    if (*s=='\r' && *(s+1)=='\n')
    {
      incby=2;strcpy2(tok,s);
    }
    return NEWLINE_CHAR;
  }

  // Include and other directives______________________________
  if (*s=='#' || *s=='!')
  {
    incby=isDirective(s,tok);
	s+=incby;
    if (incby)
    {
      while (*s!='\n' && *s)
	  {
        tok[incby++]=*s++;
	  }
      tok[incby]='\0';
	  return HASH_DIRECTIVE;
    }
  }

  // Common keywords _________________________________________
  if (*s=='s'||*s=='c'||*s=='e'||*s=='i'||*s=='o'||*s=='p')
  {
    incby=isCommonKw(s,tok);
    s+=incby;
    if (incby)
    {
      tok[incby]='\0';
	  return COMMON_TYPE;
    }
  }


  // Clanguage Keyword________________________________________
  char firstlet[] = "abcdefgilmnprstuvwx";
  if (strchr(firstlet, *s))
  {
	incby=isKeyword(s,tok);
	s+=incby;
    if (incby)
    {
      tok[incby]='\0';
	  return LANG_KEYWORD;
    }
  }


  // just a bunch of white spaces______________________________
  if (isspace(*s) && *s)
  {
    char c = *s++; while (isspace(c) && c) { tok[incby++]=c; c = *s++; }
    tok[incby]='\0';
    return DEFINE_SPACES;
  }

  // single line comment_______________________________________
  if (*s=='/' && *(s+1)=='/')
  {
    char c=*s++;
    while (c!=10 && c)
    {
      tok[incby++]=c;
      c=*s++;
    }
    tok[incby]='\0';
    return SINGLE_COMMENT;
  }


  // Multi line comment_______________________________________
  if (*s=='/' && *(s+1)=='*')
  {
    int cond=1;
    char c=*s++;d=0;
    while (cond && c)
    {
      tok[incby++]=c;
      d=c; c=*s++;
      if (d=='*' && c=='/')
      {
        cond=0;
        tok[incby++]=c;
        tok[incby]='\0';
        return MULTI_COMMENT;
      }
    }
  }

  // Deal with 3,2,1 operators ________________________________
  const char OneCharKW[]="+-*/%<>&^|!~=?:.,;(){}[]";

  // Three and Two character keywords_________________________
  if (!isascii2(*s) && !isdigit(*s) && *s!='#' && *s)
  {
    if (isThreeCharKeyword(s))
    {
      incby=3;strncpy(tok,s,3);tok[3]='\0';
      return OPERATOR_TYPE;
    }

    if (isTwoCharKeyword(s))
    {
      incby=2;strncpy(tok,s,2);tok[2]='\0';
      return OPERATOR_TYPE;
    }

    if (strchr(OneCharKW, s[0]))
    {
      incby=1;strcpy1(tok,s[0]);
      return OPERATOR_TYPE;
    }
  }

  // We are going in a single quote string_____________________
  if (*s=='\'')
  {
    int strcond = 1;
    char c = *s++;
    char lastc=0, lastcc=0;
    tok[incby++]=c; // get the first single quote
    while (strcond && *s)
    {
      if (!isspace(c)&&c!=13 ) { lastcc=lastc; lastc = c; }
      c = *s++;
      tok[incby++]=c;
      if (c=='\'' && lastc=='\\' && lastcc!='\\') { continue; }
      if (c=='\'' && lastc=='\\' && lastcc=='\\') {strcond=0; tok[incby]='\0'; return CHAR_TYPE; }
      if (c=='\'' && lastc!='\\')                 {strcond=0; tok[incby]='\0'; return CHAR_TYPE; }
    }
  }

  // We are going in a double quote string_____________________
  if (*s=='\"')
  {
    int strcond = 1;
    char c = *s++;
    char lastc=0, lastcc=0;
    tok[incby++]=c; // get the first dbl quote
    while (strcond)
    {
      if (!isspace(c)&&c!=13 ) { lastcc=lastc; lastc = c; }
      c = *s++;
      tok[incby++]=c;
      if (c=='\"' && lastc=='\\' && lastcc!='\\') { continue; }
      if (c=='\"' && lastc=='\\' && lastcc=='\\') {strcond=0; tok[incby]='\0'; return STRING_TYPE; }
      if (c=='\"' && lastc!='\\')                 {strcond=0; tok[incby]='\0'; return STRING_TYPE; }
    }
  }

  // Deal with Hex digits______________________________________
  if (*s=='0' && *(s+1)=='x')
  {
     tok[incby++]=*s++;
     tok[incby++]=*s++;
     char c = *s++; while (isxdigit(c)) { tok[incby++]=c; c = *s++; }
     tok[incby]='\0';
     return HEX_TYPE;
  }

  // Deal with 0-9 digits______________________________________
  if (isdigit(*s))
  {
     while (isdigit(*s))
     {
       char c = *s++;
       tok[incby++]=c;
     }
     tok[incby]='\0';
     return DIGITS_TYPE;
  }

  // Ascii string______________________________________________
  if (isletter(*s) || *s=='_')
  {
	while (isascii2(*s))
     {
       char c = *s++;
       tok[incby++]=c;
     }
     tok[incby]='\0';
     return FUNCTION_TYPE;
  }

  char separators[] = "{}[]()<>;,:&=.~*!+-/|\\%";
  if  (strchr(separators, *s))
  {
	tok[incby++]=*s++;
	tok[incby]='\0';
	return SEPARATORS;
  }

  strncpy(tmp, s, 10); tmp[10]='\0';
  sprintf(tmp, "should never happen [%c] [%s] ", *s, tmp);
  madd(tmp);
  //Should never happen________________________________________
  return DEFINE_NULL;

}

//------------------------------------------------------------------------------
// Function to convert special characters to HTML entities
//------------------------------------------------------------------------------

void charHtml(const char *s, char *out)
{
    strcpy(out, ""); // Initialize the output string
    for (unsigned int i = 0; i < strlen(s); ++i)
    {
        char c = s[i];
        if (c == '&') {
            strcat(out, "&amp;");
        } else if (c == '\t') {
            strcat(out, "    ");
        } else if (c == '<') {
            strcat(out, "&lt;");
        } else if (c == '\r') {
            strcat(out, " ");
        } else if (c == '>') {
            strcat(out, "&gt;");
        } else if (c == '"') {
            strcat(out, "&quot;");
        } else if (c == '\'') {
            strcat(out, "&#39;"); // Alternatively, you can use &apos; for '
        } else if (c == '\n') {
            strcat(out, "\r\n");
        } else {
            strncat(out, &c, 1); // Append the character as-is if no conversion is needed
        }
    }
}

//------------------------------------------------------------------------------

AnsiString use_class(const char *s)
{
  AnsiString a = "<span class='"; a += s; a += "'>";
  return a;
}

//------------------------------------------------------------------------------

void colorize_it(const char* input_file, const char* output_file)
{
    FILE * file = fopen(input_file, "rb");
	if (!file)
	{
        printf("Error opening files!\n");
        return;
    }
	fseek(file, 0, SEEK_END); // go to the end and get the
	long size = ftell(file); // current file pointer position
	// allocate roundin up to the nearest 16th
	char *s = new char [((size/16)+1)*16];
	fseek(file, 0, SEEK_SET);
    // Read the file content into the char array
    fread(s, 1, size, file);
	s[size] = '\0'; // Null-terminate the string
	fclose(file);

	int pos = 0;
    int incby = 1;
    int oldtype = 0;
    char *tmp = new char [65536];
    char *tok = new char [65536];

    AnsiString a = "<!DOCTYPE html>\n<html>\n<head>";
    a += "<title>Syntax Highlighted Code</title>\n<style>\n";
    a += "  .pp { color: lightgreen; }\n";
    a += "  .ot { color: white; }\n";
    a += "  .pu { color: purple; }\n";
    a += "  .dt { color: red; }\n";
    a += "  .ft { color: aqua; }\n";
    a += "  .st { color: yellow; }\n";
    a += "  .lk { color: lightgreen; }\n";
    a += "  .ct { color: #ffbf00; }\n";
    a += "  .co { background-color: black; color: #D3D3D3; font-style: italic; padding: 2px; }\n";

    AnsiString b =  "  </style>\n</head>\n<body style='background-color: navy; ";
               b += "font-size: 20px; color: white;'>\n <pre>\n";

	int type=0;
    int didspan=0; 
	int newClass=0;
	int oldClass=99;
	enum { _pp=1,_ot,_pu,_dt,_ft,_st,_lk,_ct,_co }; 
	while (pos < size && incby!=0)
	{
      oldtype = type;
	  type = getToken(s, pos, incby, tok);
	  pos += incby;
      charHtml(tok, tmp);
      didspan=0;
      oldClass = newClass;
	  if (type != oldtype)
      {
        if (type == HASH_DIRECTIVE    )   { b += use_class("pp"); newClass=_pp; didspan=1; }
        if (type == OPERATOR_TYPE     )   { b += use_class("ot"); newClass=_ot; didspan=1; }
        if (type == HEX_TYPE          )   { b += use_class("pu"); newClass=_pu; didspan=1; }
        if (type == DIGITS_TYPE       )   { b += use_class("dt"); newClass=_dt; didspan=1; }
        if (type == FUNCTION_TYPE     )   { b += use_class("ft"); newClass=_ft; didspan=1; }
        if ((type== STRING_TYPE ||   
            type == CHAR_TYPE)        )   { b += use_class("st"); newClass=_st; didspan=1; }
        if (type == LANG_KEYWORD      )   { b += use_class("lk"); newClass=_lk; didspan=1; }
        if (type == COMMON_TYPE       )   { b += use_class("ct"); newClass=_ct; didspan=1; }
        if ((type== MULTI_COMMENT ||
            type == SINGLE_COMMENT)   )   { b += use_class("co"); newClass=_co; didspan=1; }
      }
      	  
      b += tmp;
      if (didspan==1)
      {
        b += "</span>";
      }
      else
      {
        int j=0; int k=0; int z=j+k;
      }
	}

    a = a + b;
	if (strlen(output_file))
	{
	  FILE *f = fopen(output_file, "w+b");
      fwrite(a.c_str(),1,a.Length(),f);	  
	  fclose(f);
	}
	else 
	{	
      madd(a.c_str());
	}

	delete []tok;
	delete []tmp;
	delete []s;

}

#if defined(__BORLANDC__) && defined(__clang__) && defined(_WIN32) && !defined(_WIN64)

// Main function with command-line parameters
int main(int argc, char* argv[]) {
    // Check if the correct number of arguments is provided
    if (argc < 2)
	{
        printf("Usage: %s <infile> [<outfile>]\n", argv[0]);
        return 1; // Return an error code
    }
	char outf[128]; strcpy(outf, "");
	if (argc > 2) strcpy(outf, argv[2]);
	colorize_it(argv[1], outf) ;

}

#endif 



