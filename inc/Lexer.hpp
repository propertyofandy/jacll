#ifndef LEXER_HPP_
#define LEXER_HPP_

#include "Token.hpp"
#include <vector>

///////////////////////////////////////////////
// LEXER TYPE DEFENITIONS
//////////////////////////////////////////////

// used for defining base number system 
enum class NumberBase : char { 
    NONE = 0,
    HEX = 16, BIN =2, DEC = 10, 
};

class Lexer
{
public:
    Lexer(std::vector<char>);
    ~Lexer();
    Token * nextToken();

private:
    std::vector<char> fileContents;
    size_t lineNumber;
    size_t currentIndex;

    char next();
    char peek();
    char current();
    std::size_t getIndex();
    
    void skipBlank();
    std::string getIdentifier();
    std::string getHexNumber();
    std::string getBinaryNumber();
    std::string getDecimalNumber();
    std::string getStringLiteral();
    std::string getCharLiteral();
};


///////////////////////////////////////////////
// INLINE FUNCTION DEFENITIONS
//////////////////////////////////////////////

bool inline isIdentifierStart(char c) {
    return (c == '_' || c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z');
}

bool inline isIdentifier(char c) {

    return (c == '_' || c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c >= '0' && c <= '9');
}

bool inline isNumberStart(char c){
    return (c >= '0' && c <= '9');
}

bool inline isBlank(char c){
    return (
        c == ' ' || c == '\t' || c == '\r' || c == '\n' || c =='\\'
    );
}

TokenType inline getPlusToken(char c){
    if( c == '=' ){
        return TokenType::PLUS_EQUAL;
    }
    else{
        return TokenType::PLUS;
    }
}

TokenType inline getMinusToken(char c){
    switch (c)
    {
    case '=': return TokenType::MINUS_EQUAL; 
    case '>': return TokenType::THIN_ARROW; 
    default : return TokenType::MINUS;     
    }
}

TokenType inline checkDecimalNumber(std::string str, int base){

    try
    {
        std::stoll(str, nullptr, base);
        return TokenType::INTEGER;
    }
    catch(const std::exception& e)
    {
        try
        {
            std::stoull(str, nullptr, base);
            return TokenType::INTEGER;
        }
        catch(const std::exception& e)
        {
            try
            {
                std::stold(str);
                return TokenType::REAL;
            }
            catch(const std::exception& e)
            {
                return TokenType::UNDEFINED; 
            } 
        }
    } 
}


std::size_t inline getIntegerLiteral(std::string lexeme, int base){
    try
        {    //try getting unsigned long long
            return std::stoull(lexeme, nullptr, base);
        }
        catch(const std::exception& e)
        {   // if failed then number is negetive get long long and cast to unsigned
            return (std::size_t)std::stoll(lexeme, nullptr, base);
        }
}

std::size_t inline getCharValue(std::string lexeme){
    if(lexeme.size() == 3){
        return lexeme[1];  // return normal char
    }
    else if(lexeme == "\'n\'"){  // check for escape sequences
        return '\n'; 
    }
    else if(lexeme == "\'t\'"){
        return '\t';
    }
    else if(lexeme == "\'r\'"){
        return '\r';
    }
    else if(lexeme == "\'b\'"){
        return '\b';
    }
    else if(lexeme == "\'\'\'"){
        return '\'';
    }
    else if(lexeme == "\'\"\'"){
        return '\"';
    }
    else if(lexeme == "\'\\\'"){
        return '\\';
    }
    else if(lexeme == "\'\a\'"){
        return '\a';
    }
    else if(lexeme == "\'\f\'"){
        return '\f';
    }
    else if(lexeme == "\'\v\'"){
        return '\v';
    }
    else return (std::size_t)-1; // return max ull value
    
}

#endif