#include "Lexer.hpp"


Lexer::Lexer(std::vector<char> contents)
{
    this->fileContents = contents;
}

char Lexer::next(){
    this->currentIndex++;
    return (this->currentIndex < this->fileContents.size())? 
            fileContents[this->currentIndex] :
            EOF;
}

char Lexer::peek(){
    return (this->currentIndex+1 < this->fileContents.size())?
        fileContents[this->currentIndex+1]:
        EOF;
}

char Lexer::current(){
    return fileContents[this->currentIndex];
}

bool inline isBlank(char c){
    return (
        c == ' ' || c == '\t' || c == '\r' || c == '\n'
    );
}

void Lexer::skipBlank() {

    char c; //if index is out of bounds of array char returned will be EOF
    while(  this->current() != EOF && isBlank(this->current())){

        if(this->current() == '\\' && this->peek() == '\\') { //single line comment
            while(this->next() != '\n' && this->current() != EOF);
        }
        else if(this->current() == '\\' && this->peek() == '*'){ //multi line comment
            while(this->next() != '*' && this->current() != EOF){
                if(this->peek() == '\\') break;
            }
        }
        else if(this->current() == EOF){
            return;
        }
        this->next();
    }
}

std::string Lexer::getIdentifier(){
    std::string ident = "";
    do{
        ident += this->current();
    }while (isIdentifier(this->next()));
    return ident; 
}

std::string Lexer::getHexNumber(){
    std::string str = "";

    char c;
    while ( (c = this->current() ) >= '0' && c <= '9' 
        || c>='a' && c <= 'f' || c >= 'A' && c <= 'F'){

        str += c; 
        this->next();
    }
    return str;
}

std::string Lexer::getBinaryNumber(){
    std::string str = "";

    char c;
    while ( (c = this->current() ) == '0' || c == '1'){
        str += c; 
        this->next();
    }
    return str;
}

std::string Lexer::getDecimalNumber(){
    std::string str = "";

    char c;
    while( (c=this->current())=='.' || c>= '0' && c <= '9' ){
        str += c;
        this->next();
    }
    return str;
}


TokenType Lexer::checkDecimalNumber(std::string str, int base){

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

std::string Lexer::getStringLiteral(){
    std::string str;
    str += this->current();
    char c;
    while(true){

        while( (c = this->current()) != '"' &&
                c != '\\' && c!= EOF
            ){
                str += c;
        }

        if(c =='\\') 
            str += this->next();
        else if(c == EOF){
            this->currentIndex--;
            break;
        }
        else {
            str += c;
            break;
        }
    }
    return str;
} 


Token * Lexer::nextToken(){
    skipBlank();

    NumberBase base = NumberBase::NONE;
    TokenType type; 
    std::string lexeme;
    size_t lineNumber = this->lineNumber,
           start = this->currentIndex;
           
    char c;
    if(isIdentifierStart( this->current() )){
        lexeme = getIdentifier();
        type = TokenType::IDENTIFIER; 
    }
    else if(isNumberStart(this->current())){
        if(this->current() == '0'){
            
            lexeme = "0";

            switch (this->next())
            {
            case 'x': 
                lexeme += 'x' + getHexNumber();
                base = NumberBase::HEX;
                type = checkDecimalNumber(lexeme, (int)base);
            break;
            case 'b': 
                base = NumberBase::BIN;
                lexeme += 'b' + getBinaryNumber();
                type = checkDecimalNumber(lexeme, (int)base); 
            break;
            default:
                base = NumberBase::DEC;
                lexeme += this->current() + getDecimalNumber();
                type = checkDecimalNumber(lexeme, (int)base);
            break;
            }
        }

    }
    else if(this->current() == '"'){
        lexeme = this->getStringLiteral();
        type = (peek()==EOF)? TokenType::UNDEFINED : TokenType::STRING;
    }
    else if(this->current() == '\''){

    }
    else {

        TokenType type = TokenType::UNDEFINED; 

        switch (this->current())
        {
        case '.': type = TokenType::DOT; break;
        case ',': type = TokenType::COMMA; break;
        case ';': type = TokenType::SEMICOLON; break;
        case '(': type = TokenType::LEFT_PAREN; break;
        case ')': type = TokenType::RIGHT_PAREN; break;
        case '[': type = TokenType::LEFT_BRACKET; break;
        case ']': type = TokenType::RIGHT_BRACKET; break;
        case '{': type = TokenType::LEFT_BRACE; break;
        case '}': type = TokenType::RIGHT_BRACE; break;
        default:
            break;
        }
    }








    auto token = new Token(type, lexeme, lineNumber, start, this->currentIndex);
    
    switch (type)
    {
    case TokenType::INTEGER: token->literal.integer =  std::stoll(lexeme,nullptr, (int)base) ; break;
    case TokenType::REAL: token->literal.Real =  std::stold(lexeme) ; break;
    default:break;
    }

    return token;
}

