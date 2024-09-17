#include <iostream>

template <typename T>
class Vector {
 public:
  T operator[](size_t index) { return GetAt(index); }
  Vector() {}
  void Push(T value);
  void Unshift(T value);
  T GetAt(size_t index);
  void Print();
  ~Vector() { delete[] arr; }

 private:
  size_t Capacity = 1;
  size_t Length = 0;
  T *arr = new T[1];
  void Copy(T *arr, T *newArr);
};

template <typename T>
void Vector<T>::Push(T value) {
  if (this->Capacity == this->Length) {
    this->Capacity *= 2;
    T *newArr = new T[this->Capacity];
    this->Copy(arr, newArr);

    delete[] arr;
    this->arr = newArr;
  }

  this->arr[Length] = value;
  this->Length++;
}

template <typename T>
void Vector<T>::Unshift(T value) {
  if (this->Capacity <= this->Length + 1) {
    this->Capacity *= 2;
  }
  T *newArr = new T[this->Capacity];
  newArr[0] = value;
  for (size_t i = 1; i <= this->Length; i++) {
    newArr[i] = this->arr[i - 1];
  }
  delete[] arr;
  this->arr = newArr;
  this->Length++;
}

template <typename T>
void Vector<T>::Copy(T *arr, T *newArr) {
  for (size_t i = 0; i < this->Length; i++) {
    newArr[i] = arr[i];
  }
}

template <typename T>
T Vector<T>::GetAt(size_t index) {
  if (index < 0 || index > this->Length)
    throw std::invalid_argument("invalid index");
  return this->arr[index];
}

template <typename T>
void Vector<T>::Print() {
  for (size_t i = 0; i < this->Length; i++) {
    std::cout << this->arr[i] << std::endl;
  }
}
int main() {
  Vector<int> vector = {};
  vector.Push(1);
  vector.Push(3);
  vector.Unshift(5);

  std::cout << vector[2] << std::endl;

  vector.Print();
}