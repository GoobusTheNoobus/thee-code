#pragma once

#include "misc.hpp"
#include <string>
#include <vector>
#include <memory>
#include <initializer_list>

namespace TheeCode {

    enum class ASTNodeType {
        NumberLiteral,
        StringLiteral,

        Identifier,

        BinaryExpr,

        VarDeclaration,
        Log,

        Root,
        EndOfFile,
    };

    enum class BinaryOperator {
        Plus,
        Minus,
        Star,
        Slash,
    };

    struct ASTNode {
        ASTNodeType node_type;

        // Since every inheritance of a generic ASTNode will have differing
        // sizes in bytes, we make sure every ASTNode inheritance have 
        // their own compiler generated destructor so the entire thing gets deleted
        virtual ~ASTNode() = default;
    };

    using ASTReference = std::unique_ptr<ASTNode>;

    struct NumberLiteralNode : ASTNode {

        bool is_float;
        std::string data;

        NumberLiteralNode(std::string d) {
            node_type = ASTNodeType::NumberLiteral;

            data = d;

            // If '.' is in the data, then it is a float
            is_float = data.find('.') != std::string::npos;
        }
    };

    struct StringLiteralNode : ASTNode{

        std::string data;

        StringLiteralNode(std::string d) {
            node_type = ASTNodeType::StringLiteral;

            data = d;
        }
    };

    struct IdentifierNode : ASTNode{

        std::string data;

        IdentifierNode(std::string d) {
            node_type = ASTNodeType::Identifier;

            data = d;
        }
    };

    struct BinaryExprNode : ASTNode{

        BinaryOperator op;
        ASTReference left, right;
         
        BinaryExprNode(BinaryOperator op, ASTReference left, ASTReference right) {
            node_type = ASTNodeType::BinaryExpr;

            this->op    = op;
            this->left  = std::move(left);
            this->right = std::move(right);
        }
    };

    struct VarDeclarationNode : ASTNode{

        IdentifierNode left;
        ASTReference right;
         
        VarDeclarationNode(std::string identifier_name, ASTReference right) : left(IdentifierNode(identifier_name)) {
            node_type = ASTNodeType::VarDeclaration;

            this->right = std::move(right);
        }
    };

    struct LogStatementNode : ASTNode{

        std::vector<ASTReference> params;
         
        LogStatementNode() {
            node_type = ASTNodeType::Log;

            this->params = std::vector<ASTReference>();
        }
    };

    struct RootNode : ASTNode {
        std::vector<ASTReference> children;

        RootNode() {
            node_type = ASTNodeType::Root;
        }
    };
}