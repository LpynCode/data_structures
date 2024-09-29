#include <iostream>

class Node {
 public:
  Node *Left = nullptr;
  Node *Right = nullptr;
  int Key;
  size_t Height;
  Node(int key) : Key(key), Height(0) {};
};

class AVLTree {
 public:
  Node *Root = nullptr;
  AVLTree() {}
  ~AVLTree() { DestroyNode(this->Root); }
  void Print(Node *node);
  void Insert(int key);
  void Erace(int key);
  void RightRotate(Node *p);
  void FixHeight(Node *node);

  Node *Min(Node *node);

 private:
  Node *RecourciveInsert(Node *node, Node *newNode);
  void LeftRotate(Node *p);
  void Balance(Node *node);
  size_t GetHeight(Node *node);
  int GetDelta(Node *node);
  static void DestroyNode(Node *node) {
    if (!node) return;
    DestroyNode(node->Left);
    DestroyNode(node->Right);
    delete node;
  }
};

void AVLTree::Insert(int key) {
  Node *newNode = new Node(key);
  if (!this->Root) {
    this->Root = newNode;
    return;
  }
  RecourciveInsert(Root, newNode);
}

Node *AVLTree::RecourciveInsert(Node *node, Node *newNode) {
  if (!node) {
    return newNode;
  }

  if (newNode->Key < node->Key) {
    node->Left = RecourciveInsert(node->Left, newNode);
  } else {
    node->Right = RecourciveInsert(node->Right, newNode);
  }

  Balance(node);
  return node;
}

void AVLTree::Erace(int key) {
  Node *cur = this->Root;
  Node *prev = nullptr;

  while (cur && cur->Key != key) {
    prev = cur;
    if (key < cur->Key) {
      cur = cur->Left;
    } else {
      cur = cur->Right;
    }
  }

  if (!cur) return;

  if (!cur->Left) {
    if (prev->Left == cur) prev->Left = cur->Right;
    if (prev->Right == cur) prev->Right = cur->Right;
    delete cur;
    return;
  }

  if (!cur->Right) {
    if (prev->Right == cur) prev->Right = cur->Left;
    if (prev->Left == cur) prev->Left = cur->Left;
    delete cur;
    return;
  }

  Node *min = Min(cur->Right);
  Erace(min->Key);
  cur->Key = min->Key;
}

Node *AVLTree::Min(Node *node) {
  if (!node->Left) return node;
  return Min(node->Left);
}

void AVLTree::RightRotate(Node *p) {
  Node *cur = p->Left;
  p->Left = cur->Right;
  cur->Right = p;
  if (Root == p) {
    Root = cur;
  }

  FixHeight(p);
  FixHeight(cur);
}

void AVLTree::LeftRotate(Node *p) {
  Node *cur = p->Right;
  p->Right = cur->Left;
  cur->Left = p;
  if (Root == p) {
    Root = cur;
  }
  FixHeight(p);
  FixHeight(cur);
}

int AVLTree::GetDelta(Node *node) {
  return static_cast<int>(GetHeight(node->Right) - GetHeight(node->Left));
}

void AVLTree::FixHeight(Node *node) {
  if (!node->Left && !node->Right) {
    node->Height = 0;
    return;
  }
  size_t leftHeight = GetHeight(node->Left);
  size_t rightHeight = GetHeight(node->Right);
  node->Height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

size_t AVLTree::GetHeight(Node *node) { return node ? node->Height : 0; }

void AVLTree::Balance(Node *node) {
  FixHeight(node);

  int parentDelta = GetDelta(node);

  if (parentDelta >= -1 && parentDelta <= 1) return;

  if (parentDelta == 2) {
    if (GetDelta(node->Right) < 0) {
      RightRotate(node->Right);
    }
    return LeftRotate(node);
  }

  if (parentDelta == -2) {
    if (GetDelta(node->Left) > 0) {
      LeftRotate(node->Left);
    }
    return RightRotate(node);
  }
}

void AVLTree::Print(Node *node) {
  if (!node) return;
  Print(node->Left);
  std::cout << node->Key << std::endl;
  Print(node->Right);
}

int main() {
  AVLTree tree = AVLTree();
  tree.Insert(5);
  tree.Insert(4);
  tree.Insert(3);
  tree.Insert(2);
  tree.Insert(1);
  tree.Insert(0);
  tree.Print(tree.Root);
}