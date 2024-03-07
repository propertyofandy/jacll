
#include <iostream>

#include "Token.hpp"

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"




int main(){

    Token tok(TokenType::AND, "hello", 0, 0, 0);
    std::cout << tok.toString() << std::endl;
}

