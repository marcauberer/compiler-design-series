#pragma once

#include <string>
#include <vector>

#include "../reader/Reader.h"

class ASTNode {
public:
  // Constructors
  ASTNode(ASTNode *parent, CodeLoc codeLoc)
      : parent(parent), codeLoc(std::move(codeLoc)) {}
  ASTNode(const ASTNode &) = delete;

  // Destructors
  virtual ~ASTNode() {
    for (const ASTNode *child : children)
      delete child;
  }

  // Public members
  ASTNode *parent;
  std::vector<ASTNode *> children;
  const CodeLoc codeLoc;
};

class ASTEntryNode : public ASTNode {
public:
  // Constructor
  using ASTNode::ASTNode;
};