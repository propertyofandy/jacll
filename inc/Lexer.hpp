#ifndef LEXER_HPP_
#define LEXER_HPP_

#include "Token.hpp"
#include <vector>

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

    void skipBlank();
    char next();
    char peek();
    char current();
    std::size_t getIndex();

    std::string getIdentifier();
    std::string getHexNumber();
    std::string getBinaryNumber();
    std::string getDecimalNumber();
    TokenType checkDecimalNumber(std::string str, int base);
    std::string Lexer::getStringLiteral();
};

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

#endif