#ifndef TOKEN_HPP_
#define TOKEN_HPP_
#include <string>
#include <iostream>

 

enum class TokenType : char {
    // arithmatic     arithmetic assignments
    MINUS   ,   MINUS_EQUAL ,                       
    PLUS    ,   PLUS_EQUAL  ,                           
    STAR    ,   STAR_EQUAL  ,                            
    SLASH   ,   SLASH_EQUAL ,                            
    MOD     ,   MOD_EQUAL   ,                                     
    // boolean 
    BANG     , BANG_EQUAL    , LESS_EQUAL ,                                                        
    GREATER  , EQUAL_EQUAL   , AND        ,                                              
    LESS     , GREATER_EQUAL , OR         ,                                                                                                                                                                                                                          
    // enclosures
    LEFT_PAREN    , RIGHT_PAREN   ,  
    LEFT_BRACE    , RIGHT_BRACE   ,      
    LEFT_BRACKET  , RIGHT_BRACKET ,                                   
    // other
    EQUAL      ,  DOUBLE_COLON,                         
    COMMA      ,  THIN_ARROW  ,                                       
    DOT        ,  FAT_ARROW   ,                                         
    SEMICOLON  ,  HASH        ,                                  
    COLON      ,  HAT         ,                             
    // bit operations
    BIT_OR       , BIT_NOT       , BIT_XOR        ,
    BIT_XOR_EQUAL, BIT_AND       , BIT_AND_EQUAL  ,
    BIT_OR_EQUAL , BIT_LSHIFT    , BIT_RSHIFT     ,
    BIT_NOT_EQUAL, BIT_LSHIFT_SET, BIT_RSHIFT_SET ,
    // CONTROL FLOW 
    FOR, WHILE, DO, IF, ELSE, RETURN, 
    // type defanitions
    STRUCT, ENUM, MODULE, 
    //literals
    _NULL, STRING, CHAR, INTEGER, REAL,
    
    IDENTIFIER, UNDEFINED,
    _EOF = -1, 
};

class Token {
public: 
    TokenType type    ;
    std::string lexeme;
    size_t lineNumber ;
    size_t leftIndex  ;
    size_t rightIndex ;
    size_t weight     ;
    bool hasError     ;

    union literal
    {
        size_t integer;
        double Real; 
    }literal;
    
    std::string toString();
    Token(TokenType type, std::string lexeme, 
             size_t lineNumber, size_t leftIndex, 
             size_t rightIndex);
    
private:
    std::string tokenTypeToString();
    std::size_t getWeight();
};

#endif