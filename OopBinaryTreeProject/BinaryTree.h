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
	void InsertReq(T value, Node<T>* node = nullptr);

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
inline void BinaryTree<T>::InsertReq(T value, Node<T>* node)
{
	if (!root)
	{
		root = CreateNode(nullptr, value);
		count = 1;
		return;
	}

	if (!node)
		node = root;

	if (value < node->value)
	{
		if (node->left)
			InsertReq(value, node->left);
		else
			node->left = CreateNode(node, value);
	}
	else
	{
		if (node->right)
			InsertReq(value, node->right);
		else
			node->right = CreateNode(node, value);
	}
	
	count++;
}

template<typename T>
inline BinaryTree<T>::Node<T>* BinaryTree<T>::Find(T value)
{
	Node<T>* node{ root };

	while (node)
	{
		if (value == node->value)
			break;
		else
		{
			if (value < node->value)
				node = node->left;
			else
				node = node->right;
		}
	}

	return node;
}

template<typename T>
inline void BinaryTree<T>::Remove(Node<T>* node) v
{
	// delete leaf
	if (!node->left && !node->right)
	{
		if (node == root)
			root = nullptr;
		else
		{
			if (node->parent->left == node)
				node->parent->left = nullptr;
			else
				node->parent->right = nullptr;
		}

		delete node;
		count--;
		return;
	}

	// delete node with one child
	if ((bool)node->left ^ (bool)node->right)
	{
		Node<T>* child;

		child = (node->left) ? node->left : node->right;
		
		if (node == root)
			root = child;
		else
		{
			if (node->parent->left == node)
				node->parent->left = child;
			else
				node->parent->right = child;
		}

		delete node;
		count--;
		return;
	}

	// node with two children
	Node<T>* minRightNode = Min(node->right);
	node->value = minRightNode->value;
	Remove(minRightNode);
}

template<typename T>
void BinaryTree<T>::RemoveBranch(Node<T>* node)
{
	if (node->left)
		RemoveBranch(node->left);
	if(node->right)
		RemoveBranch(node->right);

	if (node->parent)
	{
		if (node->parent->left == node)
			node->parent->left = nullptr;
		else
			node->parent->right = nullptr;
	}

	delete node;
	count--;
}

template<typename T>
inline BinaryTree<T>::Node<T>* BinaryTree<T>::Min(Node<T>* node)
{
	if (!node)
		node = root;
	while (node->left)
		node = node->left;
	return node;
}

template<typename T>
inline BinaryTree<T>::Node<T>* BinaryTree<T>::Max(Node<T>* node)
{
	if (!node)
		node = root;
	while (node->right)
		node = node->right;
	return node;
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
