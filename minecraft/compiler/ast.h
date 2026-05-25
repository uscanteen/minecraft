#pragma once
#include <vector>
#include <string>
#include <memory>

class ASTNode {
public:
    virtual ~ASTNode() = default;
};

class BlockDeclarationNode : public ASTNode {
public:
    std::string blockName;
    int blockId;

    BlockDeclarationNode(std::string name, int id) 
        : blockName(name), blockId(id) {}
};


class ProgramNode : public ASTNode {
public:
    std::vector<std::unique_ptr<ASTNode>> statements;
};