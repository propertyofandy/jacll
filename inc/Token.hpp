#ifndef TOKEN_HPP_
#define TOKEN_HPP_
#include <string>
#include <iostream>

 

enum class TokenType : char {

    // ops with only =
                  
    PLUS    , PLUS_EQUAL    ,                           
    STAR    , STAR_EQUAL    ,                            
    SLASH   , SLASH_EQUAL   ,                            
    MOD     , MOD_EQUAL     ,                                     
    BANG    , BANG_EQUAL    ,
    BIT_XOR , BIT_XOR_EQUAL ,
    BIT_NOT , BIT_NOT_EQUAL ,

    MINUS   , MINUS_EQUAL   ,  THIN_ARROW  ,    
    EQUAL   , EQUAL_EQUAL   ,  FAT_ARROW   , 

    BIT_AND , AND , BIT_AND_EQUAL,
    BIT_OR  , OR  , BIT_OR_EQUAL ,                                                      

    COLON   ,  COLON_COLON ,
    LESS    ,  BIT_LSHIFT  ,LESS_EQUAL     , BIT_LSHIFT_SET,
    GREATER ,  BIT_RSHIFT  ,GREATER_EQUAL  , BIT_RSHIFT_SET,                                

    LEFT_PAREN    , 
    RIGHT_PAREN   ,  
    LEFT_BRACE    , 
    RIGHT_BRACE   ,      
    LEFT_BRACKET  , 
    RIGHT_BRACKET ,                                               
    COMMA         ,                                        
    DOT           ,                                           
    SEMICOLON     ,  
    HASH          ,                                  
                             
 
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
             size_t rightIndex, int base);
    
private:
    std::string tokenTypeToString();
    std::size_t getWeight();
};




#endif