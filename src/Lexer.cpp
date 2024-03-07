#include "Lexer.hpp"


Lexer::Lexer(std::vector<char> contents): fileContents{contents} {}

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
    return (this->currentIndex < this->fileContents.size())? 
            fileContents[this->currentIndex] :
            EOF;
}


void Lexer::skipBlank() {

    char c; //if index is out of bounds of array char returned will be EOF
    while(  this->current() != EOF && isBlank(this->current()) ){

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
    str += this->current();
    
    char c;
    while ( (c = this->next() ) >= '0' && c <= '9' 
        || c>='a' && c <= 'f' || c >= 'A' && c <= 'F'){

        str += c; 
    }
    return str;
}

std::string Lexer::getBinaryNumber(){
    std::string str = "";
    str += this->current();

    char c;
    while ( (c = this->next() ) == '0' || c == '1'){
        str += c; 
    }
    return str;
}


std::string Lexer::getDecimalNumber(){
    std::string str = "";
    str += this->current();

    char c;
    while( (c=this->next())=='.' || c>= '0' && c <= '9' ){
        str += c;
    }
    return str;
}

std::string Lexer::getStringLiteral(){
    std::string str;
    str += this->current();
    char c;
    while(true){

        while( (c = this->next()) != '"' &&
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

std::string Lexer::getCharLiteral(){
    std::string str = "";
    str += this->current();
    
    char c;
    while((c = this->next()) != '\'' && c != EOF){
        str += c;
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
                lexeme += getHexNumber();
                base = NumberBase::HEX;
                type = checkDecimalNumber(lexeme, (int)base);
            break;
            case 'b': 
                base = NumberBase::BIN;
                lexeme += getBinaryNumber();
                type = checkDecimalNumber(lexeme, (int)base); 
            break;
            default:
                base = NumberBase::DEC;
                lexeme += getDecimalNumber();
                type = checkDecimalNumber(lexeme, (int)base);
            break;
            }
        }
        else{
            base = NumberBase::DEC;
            lexeme = getDecimalNumber();
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

        TokenType type = TokenType::UNDEFINED; 

        switch (this->current())
        {
        case '.': type = TokenType::DOT;              break;
        case ',': type = TokenType::COMMA;            break;
        case ';': type = TokenType::SEMICOLON;        break;
        case '(': type = TokenType::LEFT_PAREN;       break;
        case ')': type = TokenType::RIGHT_PAREN;      break;
        case '[': type = TokenType::LEFT_BRACKET;     break;
        case ']': type = TokenType::RIGHT_BRACKET;    break;
        case '{': type = TokenType::LEFT_BRACE;       break;
        case '}': type = TokenType::RIGHT_BRACE;      break;
        case '+': type = getPlusToken(this->next());  break; 
        case '-': type = getMinusToken(this->next()); break;

        default:
            type = TokenType::UNDEFINED; 
            break;
        }
    }



    auto token = new Token(type, lexeme, lineNumber, start, this->currentIndex);
    
    switch (type) // add literal number values to union
    {
    case TokenType::INTEGER: token->literal.integer =  getIntegerLiteral(lexeme, (int)base) ; break;
    case TokenType::REAL: token->literal.Real =  std::stold(lexeme) ; break;
    case TokenType::CHAR: 
        token->literal.integer =  getCharValue(lexeme) ; 
        if(token->literal.integer == (std::size_t)-1){
            token->type = TokenType::UNDEFINED; 
        }
    break;
    default:break;
    }

    return token;
}

