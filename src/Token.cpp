#include "Token.hpp"

Token::Token(TokenType type, std::string lexeme, 
             size_t lineNumber, size_t leftIndex, 
             size_t rightIndex):
             type{type}, 
             lexeme{lexeme}, 
             lineNumber{lineNumber}, 
             leftIndex{leftIndex},
             rightIndex{rightIndex},
             weight{getWeight()}
{

    switch (type)
    {
    case TokenType::INTEGER: this->literal.integer = std::atoll(lexeme.c_str()); break;
    case TokenType::REAL   : this->literal.Real    = std::stod(lexeme.c_str()) ;
    default:
        break;
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
    case TokenType::HAT            : return "^"         ;
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
    case TokenType::DOUBLE_COLON   : return "::"        ;
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
    
    case TokenType::COLON:  case   TokenType::DOUBLE_COLON: return 17;
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