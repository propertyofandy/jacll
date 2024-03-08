#include "Token.hpp"

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
    else return (std::size_t)-1; // return max ull value for undefined 
    
}



Token::Token(TokenType type, std::string lexeme, 
             size_t lineNumber, size_t leftIndex, 
             size_t rightIndex, int base):
             type{type}, 
             lexeme{lexeme}, 
             lineNumber{lineNumber}, 
             leftIndex{leftIndex},
             rightIndex{rightIndex},
             weight{getWeight()}
{

    switch (type)
    {
    case TokenType::INTEGER: this->literal.integer = getIntegerLiteral(lexeme, base); break;
    case TokenType::REAL   : this->literal.Real    = std::stold(lexeme)             ; break;
    case TokenType::CHAR   : this->literal.integer = getCharValue(lexeme)           ; break;
    default: break;
    }
}

std::string Token::toString(){
    return "Type: " + this->tokenTypeToString() + "\n" +
            "Lexeme: " + this->lexeme + "\n" + 
            "Line :" + std::to_string(this->lineNumber) + "\n" +
            "Length: " + std::to_string(this->rightIndex - this->rightIndex);
                      
}

std::string Token::tokenTypeToString(){

    switch (this->type)
    {
    case TokenType::STAR           : return "*"         ;
    case TokenType::SLASH          : return "/"         ;
    case TokenType::PLUS           : return "+"         ;
    case TokenType::MINUS          : return "-"         ;
    case TokenType::MOD            : return "%"         ;
    case TokenType::COLON          : return ":"         ;
    case TokenType::SEMICOLON      : return ";"         ;
    case TokenType::COMMA          : return ","         ;
    case TokenType::DOT            : return "."         ;
    case TokenType::BIT_OR         : return "|"         ;
    case TokenType::BANG           : return "!"         ;
    case TokenType::BIT_AND        : return "&"         ;
    case TokenType::BIT_NOT        : return "~"         ;
    case TokenType::LESS           : return "<"         ;
    case TokenType::GREATER        : return ">"         ;
    case TokenType::EQUAL          : return "="         ;
    case TokenType::LEFT_BRACE     : return "{"         ;
    case TokenType::RIGHT_BRACE    : return "}"         ;
    case TokenType::LEFT_PAREN     : return "("         ;
    case TokenType::RIGHT_PAREN    : return ")"         ;
    case TokenType::LEFT_BRACKET   : return "["         ;
    case TokenType::RIGHT_BRACKET  : return "]"         ;
    case TokenType::UNDEFINED      : return "undefined" ;
    case TokenType::IDENTIFIER     : return "identifier";
    case TokenType::CHAR           : return "char"      ;
    case TokenType::STRING         : return "string"    ;
    case TokenType::INTEGER        : return "integer"   ;
    case TokenType::REAL           : return "real"      ;
    case TokenType::DO             : return "do"        ;
    case TokenType::WHILE          : return "while"     ;
    case TokenType::FOR            : return "for"       ;
    case TokenType::IF             : return "if"        ;              
    case TokenType::ELSE           : return "else"      ;
    case TokenType::RETURN         : return "return"    ;
    case TokenType::ENUM           : return "enum"      ;                
    case TokenType::MODULE         : return "module"    ;
    case TokenType::STRUCT         : return "struct"    ;
    case TokenType::_NULL          : return "null"      ;  
    case TokenType::_EOF           : return "EOF"       ;                  
    case TokenType::BANG_EQUAL     : return "!="        ;
    case TokenType::BIT_AND_EQUAL  : return "&="        ;
    case TokenType::BIT_LSHIFT     : return "<<"        ;
    case TokenType::BIT_RSHIFT     : return ">>"        ;
    case TokenType::BIT_LSHIFT_SET : return "<<="       ;
    case TokenType::BIT_RSHIFT_SET : return ">>="       ;
    case TokenType::BIT_NOT_EQUAL  : return "~="        ;
    case TokenType::BIT_OR_EQUAL   : return "|="        ;
    case TokenType::BIT_XOR        : return "><"        ;
    case TokenType::BIT_XOR_EQUAL  : return "><="       ;
    case TokenType::COLON_COLON    : return "::"        ;
    case TokenType::EQUAL_EQUAL    : return "=="        ;
    case TokenType::FAT_ARROW      : return "=>"        ;
    case TokenType::GREATER_EQUAL  : return ">="        ;
    case TokenType::LESS_EQUAL     : return "<="        ;
    case TokenType::MINUS_EQUAL    : return "-="        ;
    case TokenType::MOD_EQUAL      : return "%="        ;
    case TokenType::PLUS_EQUAL     : return "+="        ;
    case TokenType::SLASH_EQUAL    : return "/="        ;
    case TokenType::STAR_EQUAL     : return "*="        ;
    case TokenType::THIN_ARROW     : return "->"        ;
    case TokenType::AND            : return "&&"        ;
    case TokenType::OR             : return "||"        ;
    case TokenType::HASH           : return "#"         ;
    
    default:
        return "error at TokenTypeToString";
    }
}

std::size_t Token::getWeight(){
    switch (this->type)
    {
    case TokenType::EQUAL: case TokenType::STAR_EQUAL: case TokenType::SLASH_EQUAL: 
    case TokenType::MOD_EQUAL: case TokenType::PLUS_EQUAL: case TokenType::MINUS_EQUAL:
    case TokenType::BIT_AND_EQUAL: case TokenType::BIT_OR_EQUAL: case TokenType::BIT_XOR_EQUAL: 
    case TokenType::BIT_LSHIFT_SET: case TokenType::BIT_RSHIFT_SET: case TokenType::BIT_NOT_EQUAL:
        return 18;
    
    case TokenType::COLON:  case   TokenType::COLON_COLON: return 17;
    case TokenType::COMMA:  return 16;
    case TokenType::THIN_ARROW: case TokenType::FAT_ARROW:  return 15;
    case TokenType::OR:     return 13;
    case TokenType::AND:    return 12;
    case TokenType::BIT_OR: return 11;
    case TokenType::BIT_XOR:return 10;
    case TokenType::BIT_AND:return  9;

    case TokenType::EQUAL_EQUAL:case TokenType::BANG_EQUAL: 
        return 8;

    case TokenType::LESS: case TokenType::LESS_EQUAL: case TokenType::GREATER: case TokenType::GREATER_EQUAL: 
        return 7;
    
    case TokenType::BIT_LSHIFT: case TokenType::BIT_RSHIFT: 
        return 6;

    case TokenType::PLUS: case TokenType::MINUS: 
        return 5;

    case TokenType::STAR: case TokenType::SLASH: case TokenType::MOD: 
        return 4;

    case TokenType::BANG: case TokenType::BIT_NOT: 
        return 3;

    case TokenType::LEFT_PAREN: case TokenType::RIGHT_PAREN: case TokenType::LEFT_BRACKET:
    case TokenType::RIGHT_BRACKET: case TokenType::DOT: 
        return 2;

    case TokenType::IDENTIFIER: case TokenType::INTEGER: 
    case TokenType::REAL: case TokenType::STRING:
    case TokenType::CHAR:
        return 1;

    default:
        return 0;
    }
     
}