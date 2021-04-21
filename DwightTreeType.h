#include <string>
#include <fstream>
#include "QueType.h"

//typedef int ItemType;
template <class ItemType>
struct TreeNode;

enum OrderType {PRE_ORDER, IN_ORDER, POST_ORDER};

template <class ItemType>
class TreeType
{
public:
  TreeType();                     // constructor
  ~TreeType();                    // destructor
  TreeType(const TreeType<ItemType>& originalTree); 
  void operator=(const TreeType<ItemType>& originalTree); // copy constructor
  void MakeEmpty();
  bool IsEmpty() const;
  bool IsFull() const;
  int GetLength() const; 
  ItemType GetItem(ItemType item, bool& found);
  void PutItem(ItemType item);
  void DeleteItem(ItemType item);
  void ResetTree(OrderType order); 
  ItemType GetNextItem(OrderType order, bool& finished);
  void PreOrder(TreeNode<ItemType> * tree, QueType<ItemType> & que);
  void PostOrder(TreeNode<ItemType> * tree, QueType<ItemType> & que);
  void InOrder(TreeNode<ItemType> * tree, QueType<ItemType> & que);
  std::string Print() const;
  std::string PreOrderPrint();
  std::string PostOrderPrint();
  std::string InOrderPrint();
  void LevelOrderPrint();
  void PrintAncestors(ItemType value);
  void GetSuccessor(TreeNode<ItemType> * tree, ItemType& data);
  ItemType mirrorImage(TreeType& t);
private:
  TreeNode<ItemType> * root;
  QueType<ItemType> preQue;
  QueType<ItemType> inQue;
  QueType<ItemType> postQue;
  TreeNode<ItemType> * PtrToSuccessor(TreeNode<ItemType> * tree);
};
