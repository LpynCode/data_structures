#include <iostream>
#include <string>

class TNode {
 public:
  TNode(int key) : Key(key) {}

  int Key;
  TNode *Right = nullptr;
  TNode *Left = nullptr;
};

class SplayTree {
 public:
  SplayTree() {}

  void Insert(int key);
  void Erace(int key);

  TNode *Find(int key);
  TNode *Min(TNode *node);
  TNode *Max(TNode *node);
  void Print(TNode *node);

  ~SplayTree() { DestroyNode(Root); }
  TNode *Root = nullptr;

 private:
  void Zig(TNode *node);

  static void DestroyNode(TNode *node) {
    if (node) {
      DestroyNode(node->Left);
      DestroyNode(node->Right);
      delete node;
    }
  }
};

void SplayTree ::Insert(int key) {
  TNode **cur = &Root;

  while (*cur) {
    TNode &node = **cur;
    if (key <= node.Key) {
      cur = &node.Left;
    } else {
      cur = &node.Right;
    }
  }
  *cur = new TNode(key);
}

TNode *SplayTree::Find(int key) {
  TNode *cur = Root;

  while (cur) {
    if (key == cur->Key) return cur;
    if (key <= cur->Key) {
      cur = cur->Left;
    } else {
      cur = cur->Right;
    }
  }

  return nullptr;
}

TNode *SplayTree::Min(TNode *node) {
  if (!node->Left) return node;

  return Min(node->Left);
}

TNode *SplayTree::Max(TNode *node) {
  if (!node->Right) return node;
  return Max(node->Right);
}

void SplayTree::Print(TNode *node) {
  if (!node) return;
  Print(node->Left);
  std::cout << node->Key << " ";
  Print(node->Right);
}

void SplayTree::Zig(TNode *node) {}

void SplayTree::Erace(int key) {
  TNode *cur = Root;
  TNode *parent = nullptr;

  while (cur && cur->Key != key) {
    parent = cur;
    if (cur->Key > key) {
      cur = cur->Left;
    } else {
      cur = cur->Right;
    }
  }

  if (!cur) return;

  if (!cur->Left) {
    if (parent->Left == cur) parent->Left = cur->Right;
    if (parent->Right == cur) parent->Right = cur->Right;
    delete cur;
    return;
  }

  if (!cur->Right) {
    if (parent->Right == cur) parent->Right = cur->Left;
    if (parent->Left == cur) parent->Left = cur->Left;
    delete cur;
    return;
  }

  TNode *min = Min(cur->Right);
  Erace(min->Key);
  cur->Key = min->Key;
}

int main() {
  SplayTree *tree = new SplayTree();
  tree->Insert(2);
  tree->Insert(3);
  tree->Insert(5);
  tree->Insert(6);
  tree->Insert(1);

  tree->Erace(2);

  tree->Print(tree->Root);
}