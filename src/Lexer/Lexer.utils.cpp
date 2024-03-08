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

    do{
        str += this->current();
    }while(isValidHex(this->next()));

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


TokenType Lexer::getGTLTToken(TokenType type){

    if(this->current() == this->next()){ //means is shift
        if(this->next() == '='){
            this->next();
            return (TokenType)(((int)type)+3);
        }
        else return (TokenType)(((int)type)+1);
    }
    else if(this->current() == '='){
        this->next();
        return (TokenType)(((int)type)+2);
    }
    else return type;

}

TokenType Lexer::getAndOrToken(TokenType type){
    
    if(this->current() == this->next()){
        this->next();
        return (TokenType)(((int)type)+1);
    }
    else if(this->current() == '='){
        this->next();
        return (TokenType)(((int)type)+2);
    }
    else return type;
}

TokenType Lexer::getWithEqual(TokenType type){
    if(this->next() == '='){
        this->next();
        return (TokenType)(((int)type)+1);
    }
    else return type; 
}

TokenType Lexer::getArrowToken(TokenType type){
    if(this->next() == '='){
        this->next();
        return (TokenType)(((int)type)+1);
    }
    else if(this->current() == '>'){
        this->next();
        return (TokenType)(((int)type)+2);
    }
    else return type;
}
