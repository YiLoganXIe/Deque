#ifndef DEQUE_H
#define DEQUE_H

#include <cstddef>
#include <memory>

template<typename T>
class Deque {
 public:
  //
  // @@@ The class's public API below should _not_ be modified @@@
  //

  // Constructor
  Deque();
  // Destructor
  ~Deque();


  //
  // Capacity
  //

  // Return true if empty, false otherwise
  // Complexity: O(1)
  bool Empty () const noexcept;
  // Return number of items in deque
  // Complexity: O(1)
  size_t Size () const noexcept;
  // Resize internal data structure to fit precisely the number of items and
  // free unused memory
  // Complexity: O(N)
  void ShrinkToFit();

  // Element access
  //

  // Return item at pos @pos
  // Complexity: O(1)
  T& operator[](size_t pos);
  // Return item at front of deque
  // Complexity: O(1)
  T& Front();
  // Return item at back of deque
  // Complexity: O(1)
  T& Back();


  //
  // Modifiers
  //

  // Clear contents of deque (make it empty)
  // Complexity: O(1)
  void Clear(void) noexcept;
  // Push item @value at front of deque
  // Complexity: O(1) amortized
  void PushFront(const T &value);
  // Push item @value at back of deque
  // Complexity: O(1) amortized
  void PushBack(const T &value);
  // Remove item at front of deque
  // Complexity: O(1) amortized
  void PopFront();
  // Remove item at back of deque
  void PopBack();
  // Complexity: O(1) amortized

 private:
  //
  // @@@ The class's internal members below can be modified @@@
  //

  // Private member variables
  // ...To be completed...
  std::unique_ptr<T[]> my_array = std::unique_ptr<T[]>(new T[0]);
  int my_size;
  int usr_size;
  int head;
  int tail;

  // Private constants
  // ...To be completed (if any)...

  // Private methods
  // ...To be completed (if any)...
  void Resize();

  bool AtEnd(int index);

  bool AtBegin(int index);

  bool HeadToTail();

  void InBoundCheck(int pos);

  void InBoundCheck();
};

//
// Your implementation of the class should be located below
//

// ...To be completed...

#endif  // DEQUE_H

template<typename T>
Deque<T>::Deque() : my_size(0), usr_size(0), head(0), tail(0) {};

template<typename T>
Deque<T>::~Deque() {
  head = 0;
  tail = 0;
  my_size = 0;
  usr_size = 0;
}

template<typename T>
bool Deque<T>::Empty() const noexcept {
  return usr_size == 0 && head == 0 && tail == 0;
}

template<typename T>
size_t Deque<T>::Size() const noexcept {
  return size_t(usr_size);
}

template<typename T>
void Deque<T>::ShrinkToFit() {
  std::unique_ptr <T[]> new_array = std::unique_ptr<T[]>(new T[usr_size]);
  if(HeadToTail()) {
    int count = 0;
    for (int i = head; i <= tail; i++, count++)
      new_array[count] = my_array[i];
  } else {
    int count = 0;
    for(int i = head; i < usr_size; i++, count++)
      new_array[count]=my_array[i];
    for(int i = 0; i <= tail; i++, count++)
      new_array[count]=my_array[i];
    head = 0;
    tail = usr_size - 1;
  }
  std::swap(new_array,my_array);
  my_size = usr_size;
}
template<typename T>
void Deque<T>::PushBack(const T &value) {
  usr_size++;
  if(usr_size > my_size ){
    Resize();
 }
  if (AtEnd(tail)) {
    my_array[0] = value;
    tail = 0;
  } else {
    my_array[tail + 1] = value;
    tail += 1;
  }
}

template<typename T>
void Deque<T>::PushFront(const T &value) {
  usr_size++;
  if(usr_size > my_size ){
    Resize();
  }
  if (AtBegin(head)) {
    my_array[my_size-1] = value;
    head = my_size-1;
  } else {
    my_array[head - 1] = value;
    head -= 1;
  }
}

template<typename T>
bool Deque<T>::AtEnd(int index) {
  return index == my_size-1;
}

template<typename T>
bool Deque<T>::AtBegin(int index) {
  return index == 0;
}

template<typename T>
bool Deque<T>::HeadToTail() {
  return head <= tail;
}

template<typename T>
void Deque<T>::Resize() {
  std::unique_ptr <T[]> new_array = std::unique_ptr<T[]>(new T[usr_size*2]);
  if(HeadToTail()) {
    for (int i = 0; i < my_size; i++)
      new_array[i] = my_array[i];
  } else {
    int count = 0;
    for(int i = head; i < my_size; i++, count++)
      new_array[count]=my_array[i];
    for(int i = 0; i <= tail; i++, count++)
      new_array[count]=my_array[i];
  }
  head = 0;
  tail = my_size-1;
  std::swap(new_array,my_array);
  my_size = usr_size;
}

template<typename T>
void Deque<T>::PopFront() {
  InBoundCheck();
  if (AtEnd(head))
    head = 0;
  else
    head += 1;
  usr_size -= 1;
}

template<typename T>
void Deque<T>::PopBack() {
  InBoundCheck();
  if (AtBegin(tail))
    tail = usr_size - 1;
  else
    tail -= 1;
  usr_size -= 1;
}

template<typename T>
T &Deque<T>::Front() {
  return my_array[head];
}
template<typename T>
T &Deque<T>::Back() {
  return my_array[tail];
}

template<typename T>
T &Deque<T>::operator[](size_t pos) {
  InBoundCheck(pos);
  if(HeadToTail() or head + int(pos) < my_size)
    return my_array[head + int(pos)];
  else
    return my_array[int(pos) + head - my_size];
}

template<typename T>
void Deque<T>::Clear(void) noexcept {
  if(!Empty()){
    head = 0;
    tail = 0;
    usr_size = 0;
  }
}

template<typename T>
void Deque<T>::InBoundCheck(int pos) {
  if(pos < 0 || pos >= usr_size)
    throw std::out_of_range("Deque Out Of Bound");
}

template<typename T>
void Deque<T>::InBoundCheck() {
  if(Empty())
    throw std::out_of_range("The Deque is Empty");
}

