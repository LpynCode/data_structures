#include <iostream>
#include <string>

class TNode {
 public:
  TNode(int key) : Key(key) {}

  int Key;
  TNode *Right = nullptr;
  TNode *Left = nullptr;
};

class TTree {
 public:
  TTree() {}

  void Insert(int key);
  void Erace(int key);

  TNode *Find(int key);
  TNode *Min(TNode *node);
  TNode *Max(TNode *node);
  void Print(TNode *node);

  ~TTree() { DestroyNode(Root); }
  TNode *Root = nullptr;

 private:
  static void DestroyNode(TNode *node) {
    if (node) {
      DestroyNode(node->Left);
      DestroyNode(node->Right);
      delete node;
    }
  }
};

void TTree ::Insert(int key) {
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

TNode *TTree::Find(int key) {
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

TNode *TTree::Min(TNode *node) {
  if (!node->Left) return node;

  return Min(node->Left);
}

TNode *TTree::Max(TNode *node) {
  if (!node->Right) return node;
  return Max(node->Right);
}

void TTree::Print(TNode *node) {
  if (!node) node = Root;

  if (!node) return;
  Print(node->Left);
  std::cout << node->Key << " ";
  Print(node->Right);
}

void TTree::Erace(int key) {
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
  TTree *tree = new TTree();
  tree->Insert(2);
  tree->Insert(3);
  tree->Insert(5);
  tree->Insert(6);
  tree->Insert(1);

  tree->Erace(2);

  tree->Print(tree->Root);
}