#include <gtest/gtest.h>
#include "Token.hpp"

TEST(Token, Token_To_String){

    for (size_t i = 0; i < 62; i++)
    {
        Token tok((TokenType)i, "1", 0, 0, 0);

        if(tok.toString().find("error at TokenTypeToString") != std::string::npos){
            EXPECT_TRUE(false) << "failled at "<< i << '\n' << tok.toString();
        }
    }

    SUCCEED();
    
}