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
int TreeType::CountNodes(TreeNode* tree) const
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

void TreeType::Retrieve(TreeNode* tree, 
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
void TreeType::Insert(TreeNode*& tree, ItemType item)
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


void TreeType::DeleteNode(TreeNode*&  tree) {
  // Deletes the node pointed to by tree.
  // Post: The user's data in the node pointed to by tree is no 
  //       longer in the tree.  If tree is a leaf node or has only 
  //       non-NULL child pointer the node pointed to by tree is 
  //       deleted; otherwise, the user's data is replaced by its 
  //       logical predecessor and the predecessor's node is deleted.
  ItemType data;
  TreeNode* tempPtr;

  tempPtr = tree;
  if (tree->left == NULL)
    {
      tree = tree->right;
      delete tempPtr;
    }
  else if (tree->right == NULL)
    {
      tree = tree->left;
      delete tempPtr;
    }
  else
    {
      GetPredecessor(tree->left, data);
      tree->info = data;
      Delete(tree->left, data);  // Delete predecessor node.
    }
}

  void TreeType::Delete(TreeNode*& tree, ItemType item)
{
  if (item < tree->info)
    Delete(tree->left, item);
  else if (item > tree->info)
    Delete(tree->right, item);
  else
    DeleteNode(tree);  // Node foundif (item < tree->info)
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
void TreeType::GetPredecessor(TreeNode* tree, ItemType& data)
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
void TreeType::inOrderTraverse(TreeNode* tree) const
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
TreeType::~TreeType()
// Calls recursive function Destroy to destroy the tree.
{
  Destroy(root);
}

////
void TreeType::Destroy(TreeNode*& tree)
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
// into root
{
  if (&originalTree == this)
    return;             // Ignore assigning self to self
  Destroy(root);      // Deallocate existing tree nodes
  CopyTree(root, originalTree.root);
}

//Helper method that finds a node with the value
TreeNode* findNode(TreeNode* root, int item) {
  bool done = false;
  TreeNode* tree = root;
  while (done == false) {
    if (tree == NULL) {
      done = true;
      return tree;
    } else if (tree->info == item) {
      done = true;
      return tree;
    } else if (tree->info > item) {
      tree = tree->left;
    } else {
      tree = tree->right;
    }
  }
  return tree;
}

////
void TreeType::CopyTree(TreeNode*& copy, const TreeNode* originalTree)
  // Post: copy is the root of a tree that is a duplicate
	// of originalTree.
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

void TreeType::PostOrderTraverse(TreeNode* tree) const {
  if (tree != NULL) {
    PostOrderTraverse(tree->left);
    PostOrderTraverse(tree->right);
    cout << tree->info << " ";
  }
}

void TreeType::PostOrderPrint() const
{
  PostOrderTraverse(root);
  cout << endl;
}


////
void GetNextItem(string whichone, bool& finished)
// Returns the next item in the desired order.
// Post: For the desired order, item is the next item in the queue.
//       If item is the last one in the queue, finished is true; 
//       otherwise finished is false.
{
  std::cout << "This method has been called" << std::endl;
}

void TreeType::PreOrderTraverse(TreeNode* tree) const {
  if (tree != NULL) {
    cout << tree->info << " ";
    PreOrderTraverse(tree->left);
    PreOrderTraverse(tree->right);
  }
}

////
void TreeType::PreOrderPrint() const
// traverses and prints tree in preorder
{
  PreOrderTraverse(root);
  cout << endl;
}

////
void TreeType::LevelOrderPrint() const{
  Level(root);
}

////
void TreeType::Level(TreeNode* tree) const{
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
TreeNode* TreeType::PtrToSuccessor(TreeNode* tree)
// returns a pointer to a successor node
{
  TreeNode* location = tree;
  if (location->right == NULL) {
    return location;
  }
  location = location->right;
  while (location->left!=NULL)
    {
      location = location->left;
    }
  return location;
}

void findAncestors (TreeNode* tree, int value) {
  while (tree->info != value) {
    cout << tree->info << " ";
    if (tree->info > value) {
      tree = tree->left;
    } else {
      tree = tree->right;
    }
  }
  cout << endl;
}

////
void TreeType::PrintAncestors(int value)
{
  bool found = false;
  GetItem(value, found);
  if (found) {
    if (root->info == value) {
      cout << value << " is the root value, No ancestors" << endl;
    } else {
      findAncestors(root, value);
    }
  } else {
    cout << value << " is not in the tree" << endl;
  }
}

////
void TreeType::mirrorImage(TreeType& t) { 
  Mirror(t.root, root);
}

////
void TreeType::Mirror(TreeNode*& copy, const TreeNode* originalTree){
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

int TreeType::GetSuccessor(int item){
  bool found = false;
  Retrieve(root, item, found);
  bool done = false;
  if (found) {
    TreeNode* location = findNode(root, item);
    if (location->left == NULL) {
      cout << "NULL" << endl;
      return -99999;
    }
    location = PtrToSuccessor(location);
    return location->info;
  } else {
    cout << "Item not found in tree" << endl;
    return -99999;
  }
}

