#include <memory>
#include <iostream>

template <typename T>
class bstree;
template <typename T>
using bstree_ptr = std::shared_ptr<bstree<T>>;

template <typename T>
class bstree : public std::enable_shared_from_this<bstree<T>>
{
public:
  static bstree_ptr<T> make() { return nullptr; }
  static bstree_ptr<T> make(T value)
  {
    return bstree_ptr<T>(new bstree(std::move(value)));
  }

  T &value() { return value_; }
  const T &value() const { return value_; }

  bstree_ptr<T> left_child() const { return lchild_; }
  bstree_ptr<T> right_child() const { return rchild_; }

  static bool search(const T &x, bstree_ptr<T> root) 
  {
    if(root == nullptr)
      return false;
    
    if(root->value() == x)
      return true;

    if (bstree<T>::search(x,root->left_child()) == true)
      return true;

    if (bstree<T>::search(x,root->right_child()) == true)
      return true;

    return false;
  }

  static int height(bstree_ptr<T> root)
  {
    if (root == nullptr)
      return -1;

    return std::max(
        (root->lchild_ ? height(root->left_child()) + 1 : 0),
        (root->rchild_ ? height(root->right_child()) + 1 : 0));
  }

  friend std::ostream &operator<<(std::ostream &os, bstree_ptr<T> root)
  {
    if (root == nullptr)
      return os << "()";
    else
      return os << "(" << root->value()
                << root->left_child()
                << root->right_child() << ")";
  }

  static bstree_ptr<T> insert(T x, bstree_ptr<T> root)
  {
    if (bstree<T>::search(x,root) == true)
      return root;
    else
    {
      if (root == nullptr)
      {
        root = bstree::make(x);
        return root;
      }
      else if (x < root->value())
        root->lchild_ = insert(x, root->lchild_);
      else
        root->rchild_ = insert(x, root->rchild_);
    }
    return root;
  }

  static bstree_ptr<T> remove(T x, bstree_ptr<T> root)
  {
    if(root == nullptr)
      return root;
    if (bstree<T>::search(x,root) == false)
      return root;
    
    if(x < root->value())
      root->lchild_ = remove(x, root->lchild_);

    else if(x > root->value())
      root->rchild_ = remove(x, root->rchild_);

    else
    {
      if(!root->lchild_ && !root->rchild_)
        root = nullptr;
      
      else if(root->lchild_ && !root->rchild_)
      {
        root = root->lchild_;
      }

      else if(root->rchild_ && !root->lchild_)
      {
        root = root->rchild_;
      }

      else
      {
          bstree_ptr<T> find = root->rchild_;
          while(find->lchild_)
          {
            find = find->lchild_;
          }
          root->value_ = find->value_;
          root->rchild_ = bstree<T>::remove(root->value_,root->rchild_);
      }
    }
    return root;
  }

protected:
  bstree() = default;

  bstree(T value) : value_(std::move(value))
  {}

private:
  T value_;
  bstree_ptr<T> lchild_, rchild_;
};