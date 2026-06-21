#include "parser.hpp"

namespace TheeCode {
    ASTReference Parser::parse() {
        auto root = std::make_unique<RootNode>();

        while (!end()) {
            root->children.push_back(parse_statement());
        }

        return root;
    }

    ASTReference Parser::parse_statement() {
        auto token = current();

        // Handle log and let
        if (token.type == Token::TokenType::Keyword) {
            if (token.data == "let")
                return parse_variable_decl();

            if (token.data == "log")
                return parse_log_statement();

            raise_error(ErrorType::SyntaxError, "Invalid keyword statement");
        }

        raise_error(ErrorType::UnimplementedError, "This type of statement is either just wrong or unimplemented");

        // This code will never be reached, it's just to disable warning
        return nullptr;
    }

    ASTReference Parser::parse_variable_decl() {
        // Consume 'let'
        next();
        
        // Identifier
        auto name = next();

        if (next().data != "=") {
            raise_error(ErrorType::SyntaxError, "Expected '='");
        }

        auto value = parse_expression();

        return std::make_unique<VarDeclarationNode>(name.data, std::move(value));
    }

    ASTReference Parser::parse_log_statement() {
        // Consume 'log'
        next();

        auto node = std::make_unique<LogStatementNode>();

        while (!end()) {
            Token& token = current();

            if (token.type == Token::TokenType::SemiColon) {
                break;
            }

            node->params.push_back(parse_statement());
        }

        return node;
    }

    ASTReference Parser::parse_expression() {
        // TO-DO: Make it do something
        return nullptr;
    }
}