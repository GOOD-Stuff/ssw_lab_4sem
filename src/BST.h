// Copyright by (c) Paykov

template<class Type>
class BST {
private:
  size_t size = 0;
  template<class Type>
  class BST_node {
  public:
    Type value{};
    bool initalize = false;
    BST_node<Type>* left = nullptr, * right = nullptr;
    BST_node() {
      initalize = false;
    }
    BST_node(const Type& x) {
      this->value = x;
      this->initalize = true;
    }
  };

  // Проверка узла на существование 
  template<class T>
  bool null_pointer(const BST_node<T>* node) const {
    return node == nullptr || !node->initalize;
  }

  void pop(BST_node<Type>* node, const Type& x) {
    // к сожалению, не хватило сил и терпения, чтобы это написать       :(
  }

  // Пушаем
  void push(BST_node<Type>* node, const Type& x) {
    if (null_pointer(node)) {
      BST_node<Type>* res = new BST_node<Type>(x);
      *node = *res;
      return;
    }
    if (node->value == x) {
      return;
    }
    if (x < node->value) {
      if (null_pointer(node->left)) {
        BST_node<Type>* res = new BST_node<Type>(x);
        node->left = res;
        size += 1;
      } else {
        push(node->left, x);
      }
    } else {
      if (null_pointer(node->right)) {
        BST_node<Type>* res = new BST_node<Type>(x);
        node->right = res;
        size += 1;
      } else {
        push(node->right, x);
      }
    }
  }

  // Находим
  std::pair<bool, BST_node<Type>*> find(BST_node<Type>* node, const Type& x) {
    if (null_pointer(node)) {
      return { false, nullptr };
    }
    if (node->value == x) {
      return { true, node };
    }
    return find((node->value > x ? node->left : node->right), x);
  }

  BST_node<Type>* general = new BST_node<Type>;
public:
  BST() = default;

  void pop(const Type& x) {
    pop(find(general, x).second, x);
  }
  void push(const Type& x) {
    push(general, x);
  }
  bool find(const Type& x) {
    return find(general, x).first;
  }
};


