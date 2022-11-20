#include <iostream>
#include <stack>
#include <vector>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////
// Class ArrayBTNode
////////////////////////////////////////////////////////////////////////////////////////

template <class DT>
class ArrayBTNode
{
protected:
	// Instance Variables
	DT *_info;
	int _left;
	int _right;

public:
	// Constructors and Destructor
	ArrayBTNode();
	ArrayBTNode(DT &info);
	~ArrayBTNode();

	// getter Methods
	DT *getinfo() const;
	int getleft() const;
	int getright() const;

	// setter Methods
	void setInfo(DT &info);
	void setInfoNull(); // Sets _info to Null
	void setLeft(int left);
	void setRight(int right);

	// Display Method
	// Outputs data in _info, _left, _right
	void display();

	// Overloaded Comparison Operators
	// Used for comparing _info field with other ArrayBTNodes
	bool operator<(const ArrayBTNode<DT> &x);
	bool operator>(const ArrayBTNode<DT> &x);
	bool operator==(const ArrayBTNode<DT> &x);
	bool operator>=(const ArrayBTNode<DT> &x);
	bool operator<=(const ArrayBTNode<DT> &x);
	bool operator!=(const ArrayBTNode<DT> &x);

	// TODO: Overloaded Ostream Operator - Uses display method to output ArrayBTNode contents
	friend ostream &operator<<(ostream &os, const ArrayBTNode<DT> &x)
	{
		return os << *x.getinfo();
	}
};

template <class DT>
ArrayBTNode<DT>::ArrayBTNode()
{
	_info = nullptr;
	_left = _right = -1;
}

template <class DT>
ArrayBTNode<DT>::ArrayBTNode(DT &info)
{
	*_info = info;
}

template <class DT>
ArrayBTNode<DT>::~ArrayBTNode()
{
	delete _info;
}

template <class DT>
DT *ArrayBTNode<DT>::getinfo() const
{
	return _info;
}

template <class DT>
int ArrayBTNode<DT>::getleft() const
{
	return _left;
}

template <class DT>
int ArrayBTNode<DT>::getright() const
{
	return _right;
}

template <class DT>
void ArrayBTNode<DT>::setInfo(DT &info)
{
	_info = new DT(info);
}

template <class DT>
void ArrayBTNode<DT>::setInfoNull()
{
	delete _info;
	_info = nullptr;
	_left = _right = -1;
}

template <class DT>
void ArrayBTNode<DT>::setLeft(int left)
{
	_left = left;
}

template <class DT>
void ArrayBTNode<DT>::setRight(int right)
{
	_right = right;
}

template <class DT>
void ArrayBTNode<DT>::display() {}

template <class DT>
bool ArrayBTNode<DT>::operator<(const ArrayBTNode<DT> &x)
{
	return *_info < *x.getinfo();
}

template <class DT>
bool ArrayBTNode<DT>::operator>(const ArrayBTNode<DT> &x)
{
	return *_info > *x.getinfo();
}

template <class DT>
bool ArrayBTNode<DT>::operator==(const ArrayBTNode<DT> &x)
{
	return *_info == *x.getinfo();
}

template <class DT>
bool ArrayBTNode<DT>::operator>=(const ArrayBTNode<DT> &x)
{
	return *_info >= *x.getinfo();
}

template <class DT>
bool ArrayBTNode<DT>::operator<=(const ArrayBTNode<DT> &x)
{
	return *_info <= *x.getinfo();
}

template <class DT>
bool ArrayBTNode<DT>::operator!=(const ArrayBTNode<DT> &x)
{
	return *_info != *x.getinfo();
}

// template <class DT>
// ostream& operator<<(ostream& os, const ArrayBTNode<DT> &x)
// {
// 	return os << *x.getinfo();
// }

// ArrayBTNode::

////////////////////////////////////////////////////////////////////////////////////////
// Class ArrayBST
////////////////////////////////////////////////////////////////////////////////////////

template <class DT>
class ArrayBST
{
protected:
	// Instance Variables
	vector<ArrayBTNode<DT>> _tree; // Vector of ArrayBTNodes used to create a tree
	int _rootIndex;				   // Index of the root node in _tree
	int _numNodes;				   // Number of nodes in the tree
	int _size;					   // Maximum size of the _tree array
	stack<int> _freeLocations;	   // Stack containing indexes of freeLocations in the _tree array

public:
	// Constructors and Destructor
	ArrayBST();
	ArrayBST(int k); // initialize the vector with NULL nodes and fill the stack
	~ArrayBST();

	// Accessor Methods
	bool isEmpty() const;
	int Height();
	int Size();
	int rootIndex();
	int maxSize();

	// Mutator Methods
	void setData(int index, DT &value);
	void setLeft(int index, int value);
	void setRight(int index, int value);

	// Display methods and traversals
	void display(ostream &os) const;
	void displayPreOrder(ostream &os) const;
	void displayInOrder(ostream &os) const;
	void printRaw(); // Display the array and all of its contents

	// BST Specific Methods
	void insert(DT &object);
	bool find(DT &object);
	int findIndex(DT &object);
	void remove(DT &object); // extra credit

	// TODO: Overridden ostream operator for ArrayBST - this will call the pre order and in order methods
	friend ostream &operator<<(ostream &os, const ArrayBST<DT> &x)
	{
		displayPreOrder(os);
		displayInOrder(os);
		return os;
	}
};

template <class DT>
ArrayBST<DT>::ArrayBST() {}

template <class DT>
ArrayBST<DT>::ArrayBST(int k)
{
	_size = k;
	_numNodes = 0;
	_rootIndex = -1;
	for (int i = 0; i < k; i++)
		_freeLocations.push(i);
	_tree.resize(k, ArrayBTNode<DT>());
}

template <class DT>
ArrayBST<DT>::~ArrayBST() {}

template <class DT>
bool ArrayBST<DT>::isEmpty() const
{
	return !_numNodes;
}

template <class DT>
int ArrayBST<DT>::Height()
{
	return 0;
}

template <class DT>
int ArrayBST<DT>::Size()
{
	return _numNodes;
}

template <class DT>
int ArrayBST<DT>::rootIndex()
{
	return _rootIndex;
}

template <class DT>
int ArrayBST<DT>::maxSize()
{
	return _size;
}

template <class DT>
void ArrayBST<DT>::setData(int index, DT &value)
{
	_tree[index].setInfo(value);
}

template <class DT>
void ArrayBST<DT>::setLeft(int index, int value)
{
	_tree[index].setLeft(value);
}

template <class DT>
void ArrayBST<DT>::setRight(int index, int value)
{
	_tree[index].setRight(value);
}

template <class DT>
void ArrayBST<DT>::display(ostream &os) const
{
	cout << "Information in Tree:" << endl;
	displayPreOrder(os);
	displayInOrder(os);
}

template <class DT>
void ArrayBST<DT>::displayPreOrder(ostream &os) const
{
	os << "Pre Order Traversal: " << endl;
	stack<DT> stk;
	int root = _rootIndex;
	while (root != -1 || stk.size())
	{
		while (root != -1)
		{
			os << _tree[root] << ' ';
			stk.push(root);
			root = _tree[root].getleft();
		}
		root = _tree[stk.top()].getright();
		stk.pop();
	}
	os << endl;
}

template <class DT>
void ArrayBST<DT>::displayInOrder(ostream &os) const
{
	cout << "In Order Traversal: " << endl;
	stack<DT> stk;
	int root = _rootIndex;
	while (root != -1 || stk.size())
	{
		while (root != -1)
		{
			stk.push(root);
			root = _tree[root].getleft();
		}
		os << _tree[stk.top()] << ' ';
		root = _tree[stk.top()].getright();
		stk.pop();
	}
	os << endl;
}

template <class DT>
void ArrayBST<DT>::printRaw()
{
	cout << "Raw Data: " << endl;
	for (int i = 0; i < _size; i++)
	{
		if (!_tree[i].getinfo())
			continue;
		cout << "Index " << i << ": ";
		cout << "Info: " << *_tree[i].getinfo() << ", ";
		cout << "Left: " << _tree[i].getleft() << ", ";
		cout << "Right: " << _tree[i].getright() << endl;
	}
	cout << "Free Indexes: " << endl;
	if (_freeLocations.empty())
		cout << "None" << endl;
	else
		for (int i = _size - _numNodes - 1; i >= 0; i--)
			if (!i)
				cout << i << endl;
			else
				cout << i << ", ";
}

template <class DT>
void ArrayBST<DT>::insert(DT &object)
{
	if (_freeLocations.empty())
	{
		cout << "Cannot insert data, BST Full." << endl;
		return;
	}

	int pos = _freeLocations.top();
	_freeLocations.pop();

	int cur = _rootIndex;
	if (!_numNodes)
		_rootIndex = _size - 1;
	_numNodes++;

	int last = -1, dir = 0;
	while (cur != -1 && _tree[cur].getinfo())
	{
		last = cur;
		if (*_tree[cur].getinfo() <= object)
		{
			cur = _tree[cur].getright();
			dir = 1;
		}
		else
		{
			cur = _tree[cur].getleft();
			dir = -1;
		}
	}

	if (last != -1)
		if (dir == -1)
			_tree[last].setLeft(pos);
	if (dir == 1)
		_tree[last].setRight(pos);
	_tree[pos].setInfo(object);
}

template <class DT>
bool ArrayBST<DT>::find(DT &object)
{
	if (isEmpty())
		return true;
	int cur = _rootIndex;
	while (cur != -1 && _tree[cur].getinfo() && *_tree[cur].getinfo() != object)
		if (*_tree[cur].getinfo() <= object)
			cur = _tree[cur].getright();
		else if (*_tree[cur].getinfo() > object)
			cur = _tree[cur].getleft();
	if (cur == -1 || !_tree[cur].getinfo())
		return false;
	return true;
}

template <class DT>
int ArrayBST<DT>::findIndex(DT &object)
{
	if (isEmpty())
		return -1;
	int cur = _rootIndex;

	while (cur != -1 && _tree[cur].getinfo() && *_tree[cur].getinfo() != object)
		if (*_tree[cur].getinfo() <= object)
			cur = _tree[cur].getright();
		else if (*_tree[cur].getinfo() > object)
			cur = _tree[cur].getleft();
	if (cur == -1 || !_tree[cur].getinfo())
		return -1;
	return cur;
}

template <class DT>
void ArrayBST<DT>::remove(DT &object)
{
	if (!find(object))
	{
		cout << "Object not found." << endl;
		return;
	}

	int cur = _rootIndex;
	int last = -1, dir = 0;
	while (cur != -1)
	{

		if (*_tree[cur].getinfo() < object)
		{
			last = cur;
			cur = _tree[cur].getright();
			dir = 1;
		}
		else if (*_tree[cur].getinfo() > object)
		{
			last = cur;
			cur = _tree[cur].getleft();
			dir = -1;
		}
		else
		{
			int L = _tree[cur].getleft();
			int R = _tree[cur].getright();
			if (L == -1 && R == -1)
			{
				if (last != -1 && dir == 1)
					_tree[last].setRight(-1);
				if (last != -1 && dir == -1)
					_tree[last].setLeft(-1);
				_freeLocations.push(cur);
				_tree[cur].setInfoNull();
				cur = last;
			}
			else if (L == -1 && R != -1) // left empty
			{
				_tree[cur].setLeft(_tree[R].getleft());
				_tree[cur].setRight(_tree[R].getright());
				_tree[cur].setInfo(*_tree[R].getinfo());
				_freeLocations.push(R);
				_tree[R].setInfoNull();
			}
			else if (L != -1 && R == -1) // right empty
			{
				_tree[cur].setLeft(_tree[L].getleft());
				_tree[cur].setRight(_tree[L].getright());
				_tree[cur].setInfo(*_tree[L].getinfo());
				_freeLocations.push(L);
				_tree[L].setInfoNull();
			}
			else
			{
				int p = _tree[cur].getright();
				int parent_p = cur;
				while (_tree[p].getleft() != -1)
				{
					parent_p = p;
					p = _tree[p].getleft();
				}

				if (cur == parent_p)
				{
					_tree[cur].setRight(_tree[p].getright());
					_tree[cur].setInfo(*_tree[p].getinfo());
					_freeLocations.push(p);
					_tree[p].setInfoNull();
				}
				else
				{
					_tree[parent_p].setLeft(_tree[p].getright());
					_tree[cur].setInfo(*_tree[p].getinfo());
					_freeLocations.push(p);
					_tree[p].setInfoNull();
				}
				// _freeLocations.push(cur);

				// cur = p;
			}
			_numNodes--;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////
// Main Method
////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	// Get input for the size of the tree
	int inputSize;
	cin >> inputSize;

	// Create a BST of the size inputSize
	ArrayBST<int> myBST = ArrayBST<int>(inputSize);

	// TODO: input loop for commands
	cout << "Number of maximum nodes: " << inputSize << endl;
	string option;
	int x;
	while (cin >> option)
	{
		cout << endl;
		if (option == "I")
		{
			cin >> x;
			cout << "Inserting " << x << endl;
			myBST.insert(x);
		}
		else if (option == "F")
		{
			cin >> x;
			cout << "Finding " << x << endl;
			int pos = myBST.findIndex(x);
			if (pos == -1)
				cout << "Number not found." << endl;
			else
				cout << "Number found at index " << pos << "." << endl;
		}
		else if (option == "O")
		{
			myBST.display(cout);
		}
		else if (option == "A")
		{
			myBST.printRaw();
		}
		else if (option == "R")
		{
			cin >> x;
			cout << "Removing " << x << endl;
			myBST.remove(x);
		}
	}

	return 0;
}