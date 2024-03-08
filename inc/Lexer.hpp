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


    TokenType getGTLTToken(TokenType type);
    TokenType getAndOrToken(TokenType type);
    TokenType getArrowToken(TokenType type);

    TokenType Lexer::getWithEqual(TokenType type);
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

bool inline isValidHex(char c){
    return ( c >= '0' && c <= '9' 
        || c>='a' && c <= 'f' || c >= 'A' && c <= 'F');
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







TokenType inline getColonToken(char c){
    switch (c)
    {
    case ':': return TokenType::COLON_COLON;
    default : return TokenType::COLON; 
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