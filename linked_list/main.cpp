#include <iostream>

class Node {
 public:
  Node(int key) { this->Key = key; }
  int Key;
  Node *Next = nullptr;
};

class LinkedList {
 public:
  Node *Root = nullptr;

  LinkedList() {}
  ~LinkedList() { DestroyList(this->Root); }

  void Insert(int key);
  void Shift();
  void Pop();
  void Erace(int key);
  void Print(Node *node);

  Node *Find(int key);

 private:
  static void DestroyList(Node *node) {
    if (node) {
      DestroyList(node->Next);
      delete node;
    }
  }
};

void LinkedList::Insert(int key) {
  Node *cur = Root;
  Node *newNode = new Node(key);

  if (!cur) {
    this->Root = newNode;
  }
  while (cur) {
    if (!cur->Next) {
      cur->Next = newNode;
      return;
    }
    cur = cur->Next;
  }
}

void LinkedList::Shift() {
  Node *tmp = Root;
  Root = Root->Next;
  delete tmp;
}

void LinkedList::Pop() {
  Node *cur = Root;
  while (cur->Next->Next) {
    cur = cur->Next;
  }
  delete cur->Next;
  cur->Next = nullptr;
}

void LinkedList::Erace(int key) {
  Node *cur = Root;
  if (cur->Key == key) {
    Shift();
  }
  while (cur->Next) {
    if (cur->Next->Key == key) {
      Node *tmp = cur->Next;
      cur->Next = tmp->Next;
      delete tmp;
      return;
    }
    cur = cur->Next;
  }
}

Node *LinkedList::Find(int key) {
  Node *cur = Root;
  while (cur) {
    if (cur->Key == key) {
      return cur;
    }
    cur = cur->Next;
  }

  return nullptr;
}

void LinkedList::Print(Node *node) {
  if (!node) return;
  std::cout << node->Key << " ";
  Print(node->Next);
}

int main() {
  LinkedList *list = new LinkedList();
  list->Insert(1);
  list->Insert(5);
  list->Insert(2);

  list->Erace(5);
  list->Print(list->Root);
}