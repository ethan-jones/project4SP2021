#include <string>
#include <fstream>
#include "QueType.h"
typedef int ItemType;
struct TreeNode;
#include "QueType.cpp"
enum OrderType {PRE_ORDER, IN_ORDER, POST_ORDER};
class TreeType
{
public:
  TreeType();                     // constructor
  ~TreeType();                    // destructor
  TreeType(const TreeType& originalTree); 
  void operator=(const TreeType& originalTree); // copy constructor
  void MakeEmpty();
  bool IsEmpty() const;
  bool IsFull() const;
  int GetLength() const; 
  ItemType GetItem(ItemType item, bool& found);
  void PutItem(ItemType item);
  void DeleteItem(ItemType item);
  void ResetTree(OrderType order); 
  void GetNextItem(OrderType order, bool& finished);
  void Print() const;
  void inOrderTraverse(TreeNode* tree);
  void LevelOrderPrint();
  void PrintAncestors(int value);
  void GetSuccessor(TreeNode* tree, ItemType& data);
  void mirrorImage(TreeType& t);
  void PostOrderPrint() const;
  void PreOrderPrint() const;
  void Level(TreeNode* tree);
  void CopyTree(TreeNode*& copy, const TreeNode* originalTree);
  void PostOrder(TreeNode* tree, QueType<ItemType>& postQue);
  int CountNodes(TreeNode* tree);
  void Retrieve(TreeNode* tree, ItemType& item, bool& found);
  void Insert(TreeNode*& tree, ItemType item);
  void Delete(TreeNode*& tree, ItemType item);
  void PreOrder(TreeNode* tree, QueType<ItemType>*& preQue);
private:
  TreeNode* root;
  QueType<ItemType> preQue;
  QueType<ItemType> inQue;
  QueType<ItemType> postQue;
  TreeNode* PtrToSuccessor(TreeNode* tree);
};
