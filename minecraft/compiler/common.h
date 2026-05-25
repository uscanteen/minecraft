#pragma once
#include <string>

enum TokenType {
    TOKEN_EOF,
    TOKEN_KEYWORD,
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_ASSIGN,
    TOKEN_PLUS
}

struct Token {
    TokenType type;
    std::string value;
    int line;
};