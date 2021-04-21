#include <iostream>
#include <queue>
#include "TreeType.h"
using namespace std;

struct TreeNode
{
  ItemType info;
  TreeNode* left;
  TreeNode* right;
};

bool TreeType::IsFull() const
// Returns true if there is no room for another item 
//  on the free store; false otherwise.
{
  TreeNode* location;
  try
  {
    location = new TreeNode;
    delete location;
    return false;
  }
  catch(std::bad_alloc exception)
  {
    return true;
  }
}

bool TreeType::IsEmpty() const
// Returns true if the tree is empty; false otherwise.
{
  return root == NULL;
}

int TreeType::GetLength() const
// Calls recursive function CountNodes to count the 
// nodes in the tree.
{
  return CountNodes(root);
}

////
int CountNodes(TreeNode* tree)
// Post: returns the number of nodes in the tree.
{
  if (tree == NULL)
    return 0;
  else 
    return CountNodes(tree->left) + CountNodes(tree->right) + 1;
}

ItemType TreeType::GetItem(ItemType item, bool& found)
// Calls recursive function Retrieve to search the tree for item.
{
  Retrieve(root, item, found);
  return item;
}

void Retrieve(TreeNode* tree, 
     ItemType& item, bool& found)
// Recursively searches tree for item.
// Post: If there is an element someItem whose key matches item's,
//       found is true and item is set to a copy of someItem; 
//       otherwise found is false and item is unchanged.
{
  if (tree == NULL)
    found = false;                     // item is not found.
  else if (item < tree->info)      
    Retrieve(tree->left, item, found); // Search left subtree.
  else if (item > tree->info)
    Retrieve(tree->right, item, found);// Search right subtree.
  else
  {
    item = tree->info;                 // item is found.
    found = true;
   }
} 

void TreeType::PutItem(ItemType item)
// Calls recursive function Insert to insert item into tree.
{
  Insert(root, item);
}

// helper Function for PutItem
void Insert(TreeNode*& tree, ItemType item)
// Inserts item into tree.
// Post:  item is in tree; search property is maintained.
{
  if (tree == NULL){// Insertion place found.
    tree = new TreeNode;
    tree->right = NULL;
    tree->left = NULL;
    tree->info = item;
  }
  else if (item < tree->info)
    Insert(tree->left, item);    // Insert in left subtree.
  else
    Insert(tree->right, item);   // Insert in right subtree.
} 


void DeleteNode(TreeNode*&  tree) {

       ItemType data;
       TreeNode* tempPtr;

        tempPtr = tree;

        if ( tree->left == NULL) {
              tree = tree->right;
              delete tempPtr;
       } else if (tree->right == NULL){
              tree = tree->left;
              delete tempPtr;
       }else{
               GetSuccessor(tree->right,data);
               tree->info = data;
               Delete(tree->left, data);
        }
}

void Delete(TreeNode*& tree, ItemType item)
{
  if (item.ComparedTo(tree->info) == LESS)
     Delete(tree->left, item);
  else if (item.ComparedTo(tree->info) == GREATER)
     Delete(tree->right, item);
  else
     DeleteNode(tree);  // Node found
}


////
void TreeType::DeleteItem(ItemType item)// Calls recursive function Delete to delete item from tree.
{
	bool found = false;
	GetItem(item, found);
	if (found)
		Delete(root, item);
	else
		cout << item << "is not in tree\n";
}

////
void GetPredecessor(TreeNode* tree, & data)
// Sets data to the info member of the right-most node in tree.
{
  while (tree->right != NULL)
    tree = tree->right;
  data = tree->info;
}

////
string PrintTree(TreeNode* tree) 
// Prints info member of items in tree in sorted order on screen.
{
  string str = "";
  if (tree != NULL)
  {
    str += PrintTree(tree->left);   // Print left subtree.
    str += tree->info;
    str += "  ";
    str += PrintTree(tree->right);  // Print right subtree.
  }
  return str;
}

////
void TreeType::Print() const
// Calls recursive function inOrderTraverse to print items in the tree.
{
	inOrderTraverse(root);
}

////
void TreeType::inOrderTraverse(TreeNode* tree) 
// Prints info member of items in tree in sorted order on screen.
{
  if (tree != NULL)
  {
	inOrderTraverse(tree->left);   // Print left subtree.
    cout << tree->info<<"  ";
	inOrderTraverse(tree->right);  // Print right subtree.
  }
}


////
TreeType::TreeType()
{
  root = NULL;
}

////
void Destroy(TreeNode*& tree);

////
TreeType::~TreeType()
// Calls recursive function Destroy to destroy the tree.
{
  Destroy(root);
}

////
void Destroy(TreeNode*& tree)
// Post: tree is empty; nodes have been deallocated.
{
  if (tree != NULL)
  {
    Destroy(tree->left);
    Destroy(tree->right);
    delete tree;
  }
}

////
void TreeType::MakeEmpty()
// Makes the function empty
{
  Destroy(root);
  root = NULL;
}

////
TreeType::TreeType(const TreeType& originalTree)
// Calls recursive function CopyTree to copy originalTree 
//  into root.
{
  CopyTree(root, originalTree.root);
}

////
void TreeType::operator= (const TreeType& originalTree)
// Calls recursive function CopyTree to copy originalTree 
// into root.
{
  {
  if (&originalTree == this)
    return;             // Ignore assigning self to self
  Destroy(root);      // Deallocate existing tree nodes
  CopyTree(root, originalTree.root);
  }

}

////
void CopyTree(TreeNode*& copy, const TreeNode* originalTree)
// Post: copy is the root of a tree that is a duplicate 
//       of originalTree.
{
  if (originalTree == NULL)
    copy = NULL;
  else
  {
    copy = new TreeNode;
    copy->info = originalTree->info;
    CopyTree(copy->left, originalTree->left);
    CopyTree(copy->right, originalTree->right);
  }
}

void PostOrderPrint() const
{
  string str = "";
  PostOrder(root, postQue);
  ItemType item;
  while (!postQue.IsEmpty())
  {
    postQue.Dequeue(item);
    str += item;
    str += " ";
  }
  cout << str;
}


////
 TreeType::GetNextItem(OrderType order, bool& finished)
// Returns the next item in the desired order.
// Post: For the desired order, item is the next item in the queue.
//       If item is the last one in the queue, finished is true; 
//       otherwise finished is false.
{
  finished = false;
   item;
  switch (order)
  {
    case PRE_ORDER  : preQue.Dequeue(item);
                      if (preQue.IsEmpty())
                        finished = true;
                      break;
    case IN_ORDER   : inQue.Dequeue(item);
                      if (inQue.IsEmpty())
                        finished = true;
                      break;
    case  POST_ORDER: postQue.Dequeue(item);
                      if (postQue.IsEmpty())
                        finished = true;
                      break;
  }
  return item;
}

////
void PreOrderPrint()
// traverses and prints tree in preorder
{
  string str = "";
  PreOrder(root, preQue);
   item;
  while (!preQue.IsEmpty())
  {
    preQue.Dequeue(item);
    str += item;
    str += " ";
  }
  cout << str;
}

////
void TreeType::LevelOrderPrint(){
	Level(root);
}

////
void Level(TreeNode* tree){
	queue <TreeNode * > que1;
	if (tree == NULL){
		return;
	}
	que1.push(tree);
	while (true){
		int nodes = que1.size();
		if (nodes == 0){
			break;
		}
		while (nodes > 0){
			TreeNode * treeroot = que1.front();
			cout << treeroot->info << " ";
			que1.pop();
			if (treeroot->left != NULL){
				que1.push(treeroot->left);
			}
			if (treeroot->right != NULL){
				que1.push(treeroot->right);
			}
			nodes--;
		}
		cout << endl;
	}
}

////
TreeNode* PtrToSuccessor(TreeNode* tree)
// returns a pointer to a successor node
{
  TreeNode* location = tree->left;
  while (location->left!=NULL)
  {
    location = tree->left;
  }
  return location;
}

////
void TreeType::PrintAncestors(int value)
{
  string str = "";
  TreeNode * location = root;
  while (location->info != value || location != NULL)
  {
    if (location->info>value)
    {
      str += location->info;
      str+= " ";
      location = location->left;
    }
    else if (location->info<value)
    {
      str += location->info;
      str+= " ";
      location = location->right;
    }
    else if (location->info == value)
        break;
  }
  if (location==NULL)
    str = "This item is not in the tree";
  else if (str.length() == 0)
    str = "This item has no ancestors";
  cout << str;
}

////
void mirrorImage(TreeType& t)
{
    
  Mirror(t.root, root);
  return t;
}

////
void Mirror(TreeNode*& copy, const TreeNode* originalTree){
  if (originalTree == NULL){
  	copy = NULL;
  }
  else{
  	copy = new TreeNode;
  	copy->info = originalTree->info;
  	Mirror(copy->left, originalTree->right);
  	Mirror(copy->right, originalTree->left);
  }
}

void TreeType::GetSuccessor(TreeNode* tree, & data){
        while(tree->left != NULL)
                tree = tree->left;
        data= tree->info;
}

void PostOrder(TreeNode* tree, QueType<ItemType>& postQue)
// Post: postQue contains the tree items in postorder.
{
  if (tree != NULL)
  {
    PostOrder(tree->left, postQue);
    PostOrder(tree->right, postQue);
    postQue.Enqueue(tree->info);
  }
}

