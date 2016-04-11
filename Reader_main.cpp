#include<iostream>
#include<cstdlib> 
#include "Token.hpp"
#include "Reader.hpp"


Token readDependencyLine( Reader * reader )
{
    Token target = reader->getToken();
    if( target.isEOF() )
        return target;

    if( ! target.isName() ) {
        std::cout << "The first token of a dependency line should be a name-token.\n";
        exit(1);
    }
    std::cout << "Target is: " << target.getName() << std::endl;
    Token colon = reader->getToken();
    if( ! colon.isColon() ) {
        std::cout << "Missing colon character on the dependency line.\n";
        exit(1);
    }

    std::cout << "The following file-names depend on the above target.\n";
    Token token;
    do {
        token = reader->getToken();
        if( token.isName() ) 
            std::cout << token.getName() << std::endl;
    } while( token.isName() ) ;
    
    if( ! token.isEOL() ) {
        std::cout << "Dependency line contains a non-name token.\n";
        exit(1);
    }
    return token;
}

int main(int argc, const char *argv[])
{
    if( argc != 2 ) {
        std::cout << "usage: " << argv[0] << " name-of-input-make-file-to-tokenize.\n";
        return 1;
    }
    std::cout << "Using makefile, " << argv[1] << ".\n";
    Reader *reader = new Reader(argv[1]);

    while( true ) {
        Token token = readDependencyLine(reader);
        if( token.isEOF() )
            return 0;
        token = reader->getToken();
        if( ! token.isCommand() ) {
            std::cout << "No command found after dependency line.\n";
            exit(1);
        }
        std::cout << "The command is: " << token.getCommand() << std::endl;
    }
    return 0;
}
