#pragma once
template <typename T>
class BinaryTree
{
	template <typename T>
	struct Node
	{
		T value;
		Node<T>* parent{};
		Node<T>* left{};
		Node<T>* right{};
	};

	Node<T>* root;
	int count;
public:
	BinaryTree();
	~BinaryTree();

	Node<T>* Root() const;
	int Count() const;

	Node<T>* CreateNode(Node<T>* parent, T value);

	void InsertLoop(T value);
	void InsertReq(T value);

	Node<T>* Find(T value);

	void Remove(Node<T>* node);
	void RemoveBranch(Node<T>* node);

	Node<T>* Min(Node<T>* node = nullptr);
	Node<T>* Max(Node<T>* node = nullptr);

	void PrintBranch(Node<T>* node);
	void Print();
};

template<typename T>
inline BinaryTree<T>::BinaryTree() : root{}, count{} {}

template<typename T>
inline BinaryTree<T>::~BinaryTree()
{
	RemoveBranch(root);
}

template<typename T>
inline BinaryTree<T>::Node<T>* BinaryTree<T>::Root() const
{
	return root;
}

template<typename T>
inline int BinaryTree<T>::Count() const
{
	return count;
}

template<typename T>
inline BinaryTree<T>::Node<T>* BinaryTree<T>::CreateNode(Node<T>* parent, T value)
{
	Node<T>* node = new Node<T>;
	node->parent = parent;
	node->value = value;

	return node;
}

template<typename T>
void BinaryTree<T>::InsertLoop(T value)
{
	if (!root)
	{
		root = CreateNode(nullptr, value);
		count = 1;
		return;
	}

	Node<T>* nodeCurrent = root;
	Node<T>* nodeParent = nullptr;

	while (nodeCurrent)
	{
		nodeParent = nodeCurrent;
		if (value < nodeCurrent->value)
			nodeCurrent = nodeCurrent->left;
		else
			nodeCurrent = nodeCurrent->right;
	}

	nodeCurrent = CreateNode(nodeParent, value);
	if (value < nodeParent->value)
		nodeParent->left = nodeCurrent;
	else
		nodeParent->right = nodeCurrent;

	count++;
}

template<typename T>
void BinaryTree<T>::RemoveBranch(Node<T>* node)
{
	if (node->left)
		RemoveBranch(node->left);
	if(node->right)
		RemoveBranch(node->right);


	if (node->parent->left == node)
		node->parent->left = nullptr;
	else
		node->parent->right = nullptr;

	delete node;
	count--;
}

template<typename T>
void BinaryTree<T>::PrintBranch(Node<T>* node)
{
	if (node)
	{
		PrintBranch(node->left);
		std::cout << node->value << " ";
		PrintBranch(node->right);
	}
}

template<typename T>
void BinaryTree<T>::Print()
{
	PrintBranch(root);
}
