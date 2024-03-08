#include "Lexer.hpp"


Token * Lexer::nextToken(){
    skipBlank();

    NumberBase base = NumberBase::NONE;
    TokenType type; 
    std::string lexeme;
    size_t lineNumber = this->lineNumber,
           start = this->currentIndex;
           
    if(isIdentifierStart( this->current() )){
        lexeme = getSymbol(&isIdentifier);
        type = TokenType::IDENTIFIER; 
    }
    else if(isNumberStart(this->current())){
        if(this->current() == '0'){
            
            lexeme = "0";

            switch (this->next())
            {
            case 'x': 
                lexeme += getSymbol(&isValidHex);
                base = NumberBase::HEX;
                type = checkDecimalNumber(lexeme, (int)base);
            break;
            case 'b': 
                base = NumberBase::BIN;
                lexeme += getSymbol(&isValidBin);
                type = checkDecimalNumber(lexeme, (int)base); 
            break;
            default:
                base = NumberBase::DEC;
                lexeme += getSymbol(&isValidNumber);
                type = checkDecimalNumber(lexeme, (int)base);
            break;
            }
        }
        else{
            base = NumberBase::DEC;
            lexeme = getSymbol(&isValidNumber);
            type = checkDecimalNumber(lexeme, (int)base);
        }

    }
    else if(this->current() == '"'){
        lexeme = this->getStringLiteral();
        type = (peek()==EOF)? TokenType::UNDEFINED : TokenType::STRING;
    }
    else if(this->current() == '\''){
        lexeme = getCharLiteral();
        type = TokenType::CHAR; 
    }
    else {

        switch (this->current())
        {
        case '#': type = TokenType::HASH;                  break;
        case '.': type = TokenType::DOT;                   break;
        case ',': type = TokenType::COMMA;                 break;
        case ';': type = TokenType::SEMICOLON;             break;
        case '(': type = TokenType::LEFT_PAREN;            break;
        case ')': type = TokenType::RIGHT_PAREN;           break;
        case '[': type = TokenType::LEFT_BRACKET;          break;
        case ']': type = TokenType::RIGHT_BRACKET;         break;
        case '{': type = TokenType::LEFT_BRACE;            break;
        case '}': type = TokenType::RIGHT_BRACE;           break;
        case ':': type = getGTLTToken(TokenType::COLON);   break; 
        case '!': type = getWithEqual(TokenType::BANG);    break; 
        case '^': type = getWithEqual(TokenType::BIT_XOR); break; 
        case '~': type = getWithEqual(TokenType::BIT_NOT); break; 
        case '+': type = getWithEqual(TokenType::PLUS);    break; 
        case '-': type = getArrowToken(TokenType::MINUS);  break; 
        case '=': type = getArrowToken(TokenType::EQUAL);  break; 
        case '/': type = getWithEqual(TokenType::SLASH);   break;
        case '*': type = getWithEqual(TokenType::STAR);    break;
        case '%': type = getWithEqual(TokenType::MOD);     break;
        case '<': type = getGTLTToken(TokenType::LESS);    break;
        case '>': type = getGTLTToken(TokenType::GREATER); break;
        case '&': type = getAndOrToken(TokenType::BIT_AND);break;
        case '|': type = getAndOrToken(TokenType::BIT_OR); break;

        default : type = TokenType::UNDEFINED;             break;
        }
    }

    return new Token(type, lexeme, lineNumber, start, this->currentIndex, (int)base);
    
}
