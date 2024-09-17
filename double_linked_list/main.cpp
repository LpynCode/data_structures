#include <iostream>

class Node {
 public:
  Node(int key) { this->Key = key; }

  int Key;
  Node *Next = nullptr;
  Node *Prev = nullptr;
};

class DoubleLinkedList {
 public:
  DoubleLinkedList() {}
  ~DoubleLinkedList() { DestroyList(this->Head); }
  void Append(int key);
  void Prepend(int key);
  Node *GetAt(size_t index);
  void Shift();
  void Pop();
  void Print(Node *node);

  Node *Head = nullptr, *Tail = nullptr;

 private:
  static void DestroyList(Node *node) {
    if (node) {
      DestroyList(node->Next);
      delete node;
    }
  }
};

void DoubleLinkedList::Append(int key) {
  Node *newNode = new Node(key);
  newNode->Prev = this->Tail;

  if (this->Tail != nullptr) this->Tail->Next = newNode;
  if (!this->Head) this->Head = newNode;

  this->Tail = newNode;
}

void DoubleLinkedList::Prepend(int key) {
  Node *newNode = new Node(key);
  newNode->Next = this->Head;

  if (this->Head != nullptr) this->Head->Prev = newNode;
  if (!this->Tail) this->Tail = newNode;

  this->Head = newNode;
}

void DoubleLinkedList::Shift() {
  if (!this->Head) return;

  Node *tmp = this->Head->Next;

  if (tmp != nullptr) {
    tmp->Prev = nullptr;
  } else {
    this->Tail = nullptr;
  }

  delete this->Head;
  this->Head = tmp;
}

void DoubleLinkedList::Pop() {
  if (!this->Tail) return;
  Node *tmp = this->Tail->Prev;

  if (tmp != nullptr) {
    tmp->Next = nullptr;
  } else {
    this->Head = nullptr;
  }

  delete this->Tail;
  this->Tail = tmp;
}

Node *DoubleLinkedList::GetAt(size_t index) {
  size_t i = 0;
  Node *cur = this->Head;
  while (cur) {
    if (i == index) return cur;

    cur = cur->Next;
    i++;
  }

  return nullptr;
}

void DoubleLinkedList::Print(Node *node) {
  if (!node) return;
  std::cout << node->Key << " ";
  Print(node->Next);
}

int main() {
  DoubleLinkedList *list = new DoubleLinkedList();
  list->Append(5);
  list->Append(6);
  list->Prepend(1);
  list->Shift();
  std::cout << list->GetAt(0)->Key << std::endl;

  list->Print(list->Head);
}