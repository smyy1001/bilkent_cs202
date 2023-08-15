/*
---------------------------------------------------------------------
~ Algorithm Analysis
    !: log(n) < n < n*log(n) < n^2 < 2^n < n!
    * Asymptotic Notations Overview:
        * Worst Case (upper bound) analysis: Big Oh -> O(f(n))
            ^T(n) = O(f(n)) if 0 ≤ T(n) ≤ cf(n), where n >= n0
        * Average Case analysis: Θ(f(n))
        * Best Case (lower bound) analysis: Ω(f(n))

---------------------------------------------------------------------
~ Searching & Sorting

    * Sequential Search
    int sequentialSearch( const int a[], int item, int n){
        for (int i = 0; i < n && a[i]!= item; i++);
        if (i == n)
            return –1;
        return i;
    }

    * Binary Search
    int binarySearch( int a[], int size, int x) {
        int low =0;
        int high = size –1;
        int mid;   // mid will be the index of

        // target when it’s found.
        while (low <= high) {
            mid = (low + high)/2;
            if (a[mid] < x)
                low = mid + 1;
            else if (a[mid] > x)
            high  = mid – 1;
            else
            return mid;
        }

        return –1;
    }

    ! Search        Best    Average     Worst
     Sequential     O(1)     O(n)        O(n)
     Binary         O(1)   O(log(n))   O(log(n))


    ! Mode: the element with highest frequency
    ! Median: middle element


    ? Selection Sort: find the greatest and move it to the end of the array
        void selectionSort( DataType theArray[], int n) {
            for (int last = n-1; last >= 1; --last) {
                int largest = indexOfLargest(theArray, last+1);
                swap(theArray[largest], theArray[last]);
            }
        }

        int indexOfLargest(const DataType theArray[], int size) {
            int indexSoFar = 0;
            for (int currentIndex=1; currentIndex<size;++currentIndex) {
                if (theArray[currentIndex] > theArray[indexSoFar])
                    indexSoFar = currentIndex;
            }
            return indexSoFar;
        }

        ! Best, average, worst -> O(n^2)



    ? Insertion Sort: take the first element as sorted and insert next element to its place
        void insertionSort(DataType theArray[], int n) {
            for (int unsorted = 1; unsorted < n; ++unsorted) {
                DataType nextItem = theArray[unsorted];
                int loc = unsorted;
                for ( ;(loc > 0) && (theArray[loc-1] > nextItem); --loc) {
                    theArray[loc] = theArray[loc-1];
                }
                theArray[loc] = nextItem;
            }
        }

        ! Best -> O(n)
        ! Average, worst -> O(n^2)



    ? Bubble Sort
        void bubbleSort( DataType theArray[], int n) {
            bool sorted = false;
            for (int pass = 1; (pass < n) && !sorted; ++pass) {
                sorted = true;
                for (int index = 0; index < n-pass; ++index) {
                    int nextIndex = index + 1;
                    if (theArray[index] > theArray[nextIndex]) {
                        swap(theArray[index], theArray[nextIndex]);
                        sorted = false; // signal exchange
                    }
                }
            }
        }

        ! Best -> O(n)
        ! Average, worst -> O(n^2)




    ? Merge Sort: divide into 2 groups'till you reach base case, then merge the halves
        void mergesort( DataType theArray[], int first, int last) {
            if (first < last) {
                int mid = (first + last)/2; // index of midpoint
                mergesort(theArray, first, mid);
                mergesort(theArray, mid+1, last);
                merge(theArray, first, mid, last);
            }
        }

        void merge( DataType theArray[], int first, int mid, int last) {

            DataType tempArray[MAX_SIZE]; // temporary array

            int first1 = first; // beginning of first subarray
            int last1 = mid;  // end of first subarray
            int first2 = mid + 1; // beginning of second subarray
            int last2 = last;  // end of second subarray
            int index = first1; // next available location in tempArray

            for ( ; (first1 <= last1) && (first2 <= last2); ++index) {
                if (theArray[first1] < theArray[first2]) {
                    tempArray[index] = theArray[first1];
                    ++first1;
                }
                else {
                    tempArray[index] = theArray[first2];
                    ++first2;
                }
            }

            // finish off the first subarray, if necessary
            for (; first1 <= last1; ++first1, ++index)
                tempArray[index] = theArray[first1];

            // finish off the second subarray, if necessary
            for (; first2 <= last2; ++first2, ++index)
                tempArray[index] = theArray[first2];

            // copy the result back into the original array
            for (index = first; index <= last; ++index)
                theArray[index] = tempArray[index];
        }

        ! Best, average -> O (n * logn )
        ! Worst -> O (n * logn )



    ? Quick Sort: chose a pivot, two sub groups inside the array will form, than combine'em

        void quicksort(DataType theArray[], int first, int last) {
            // Precondition: theArray[first..last] is an array.
            // Postcondition: theArray[first..last] is sorted.
            int pivotIndex;
            if (first < last) {
                // create the partition: S1, pivot, S2
                partition(theArray, first, last, pivotIndex);
                // sort regions S1 and S2
                quicksort(theArray, first, pivotIndex-1);
                quicksort(theArray, pivotIndex+1, last);
            }
        }

        void partition(DataType theArray[], int first, int last, int &pivotIndex) {
            // Precondition: theArray[first..last] is an array; first <= last.
            // Postcondition: Partitions theArray[first..last] such that:
            //   S1 = theArray[first..pivotIndex-1] < pivot
            //   theArray[pivotIndex] == pivot
            //   S2 = theArray[pivotIndex+1..last] >= pivot

            // place pivot in theArray[first]
            choosePivot(theArray, first, last);
            DataType pivot = theArray[first]; // copy pivot

            // initially, everything but pivot is in unknown
            int lastS1 = first;           // index of last item in S1
            int firstUnknown = first + 1; // index of first item in unknown

            // move one item at a time until unknown region is empty
            for ( ; firstUnknown <= last; ++firstUnknown) {
                // Invariant: theArray[first+1..lastS1] < pivot
                //            theArray[lastS1+1..firstUnknown-1] >= pivot
                // move item from unknown to proper region
                if (theArray[firstUnknown] < pivot) {  // belongs to S1
                    ++lastS1;
                    swap(theArray[firstUnknown], theArray[lastS1]);
                } // else belongs to S2
            }
            // place pivot in proper position and mark its location
            swap(theArray[first], theArray[lastS1]);
            pivotIndex = lastS1;
        }

        ! Best, average -> O(n * log2n)
        ! Worst -> O(n^2)

---------------------------------------------------------------------
~ Trees

    * The minimum height of a binary tree with n nodes is ceiling(log2(n+1))
    * Number of nodes at level h: s^(h-1)
    * Total number of nodes until level h (h included): 2^h -1

&Default constructor
    BinaryTree::BinaryTree() : root(NULL) {}

&Protected constructor
    BinaryTree::BinaryTree(TreeNode *nodePtr) : root(nodePtr) {}

&Constructor
    BinaryTree::BinaryTree(const TreeItemType& rootItem) {
    root = new TreeNode(rootItem, NULL, NULL);
    }

&Constructor
    BinaryTree::BinaryTree(const TreeItemType& rootItem,
        BinaryTree& leftTree, BinaryTree& rightTree) {
        root = new TreeNode(rootItem, NULL, NULL);
        attachLeftSubtree(leftTree);
        attachRightSubtree(rightTree);
    }

&attachLeftSubtree
    void BinaryTree::attachLeftSubtree(BinaryTree& leftTree) {
        if (!isEmpty() && (root->leftChildPtr == NULL)) {
            root->leftChildPtr = leftTree.root;
            leftTree.root = NULL
        }
    }

&attachRightSubtree
    void BinaryTree::attachRightSubtree(BinaryTree& rightTree) {
        if(!isEmpty() && (root->rightChildPtr == NULL)) {
            root->rightChildPtr = rightTree.root;
            rightTree.root = NULL;
        }
    }

&Copy constructor
    BinaryTree::BinaryTree(const BinaryTree& tree) {
        copyTree(tree.root, root);
    }

Uses preorder traversal for the copy operation
(Visits first the node and then the left and right children)
    void BinaryTree::copyTree(TreeNode *treePtr, TreeNode *& newTreePtr) const {
        if (treePtr != NULL) {  // copy node
            newTreePtr = new TreeNode(treePtr->item, NULL, NULL);
            copyTree(treePtr->leftChildPtr, newTreePtr->leftChildPtr);
            copyTree(treePtr->rightChildPtr, newTreePtr->rightChildPtr);
        }
        else
            newTreePtr = NULL; // copy empty tree
        }

&Destructor
    BinaryTree::~BinaryTree() {
        destroyTree(root);
    }

Uses postorder traversal for the destroy operation
(Visits first the left and right children and then the node)
    void BinaryTree::destroyTree(TreeNode *& treePtr) {
        if (treePtr != NULL){
            destroyTree(treePtr->leftChildPtr);
            destroyTree(treePtr->rightChildPtr);
            delete treePtr;
            treePtr = NULL;
        }
    }


? Traversals
    ~ Preorder Traversal
        The node is visited before its left and right subtrees,
    ~ Postorder Traversal
        The node is visited after both subtrees.
    ~ Inorder Traversal
        Visit left subtree, visit the node, and visit the right subtree.

    ? PreOrder
    void BinaryTree::preorder(TreeNode *treePtr, FunctionType visit) {
        if (treePtr != NULL) {
            visit(treePtr->item);
            preorder(treePtr->leftChildPtr, visit);
            preorder(treePtr->rightChildPtr, visit);
        }
    }

    ? InOrder
    void BinaryTree::inorder(TreeNode *treePtr, FunctionType visit) {
        if (treePtr != NULL) {
            inorder(treePtr->leftChildPtr, visit);
            visit(treePtr->item);
            inorder(treePtr->rightChildPtr, visit);
        }
    }

    ? PostOrder
    void BinaryTree::postorder(TreeNode *treePtr, FunctionType visit) {
        if (treePtr != NULL) {
            postorder(treePtr->leftChildPtr, visit);
            postorder(treePtr->rightChildPtr, visit);
            visit(treePtr->item);
        }
    }


    ^ BST (Binary Search Tree)
        ! A binary Tree is also a BST if: left node's data < root node's data < right node's data

    ^ Search in BST
    void BinarySearchTree::searchTreeRetrieve(KeyType searchKey,
                            TreeItemType& treeItem) const throw(TreeException) {
        retrieveItem(root, searchKey, treeItem);
    }

    void BinarySearchTree::retrieveItem(TreeNode *treePtr, KeyType searchKey,
                            TreeItemType& treeItem) const throw(TreeException) {
        if (treePtr == NULL)
            throw TreeException("TreeException: searchKey not found");
        else if (searchKey == treePtr->item.getKey())
            treeItem = treePtr->item;
        else if (searchKey < treePtr->item.getKey())
            retrieveItem(treePtr->leftChildPtr, searchKey, treeItem);
        else
            retrieveItem(treePtr->rightChildPtr, searchKey, treeItem);
    }

    ^ Insert a node
    void BinarySearchTree::searchTreeInsert(const TreeItemType& newItem) {
        insertItem(root, newItem);
    }
    void BinarySearchTree::insertItem(TreeNode *& treePtr,
                            const TreeItemType& newItem) throw(TreeException) {
        // Position of insertion found; insert after leaf
        if (treePtr == NULL) {
            treePtr = new TreeNode(newItem, NULL, NULL);
            if (treePtr == NULL)
                throw TreeException("TreeException: insert failed");
            }
        // Else search for the insertion position
        else if (newItem.getKey() < treePtr->item.getKey())
            insertItem(treePtr->leftChildPtr, newItem);
        else
            insertItem(treePtr->rightChildPtr, newItem);
    }


    ^ Delete a node
    void BinarySearchTree::searchTreeDelete(KeyType searchKey) throw(TreeException) {
        deleteItem(root, searchKey);
    }

    void BinarySearchTree::deleteItem(TreeNode * &treePtr, KeyType searchKey) throw(TreeException) {
        if (treePtr == NULL) // Empty tree
            throw TreeException("Delete failed");

        // Position of deletion found
        else if (searchKey == treePtr->item.getKey())
            deleteNodeItem(treePtr);

        // Else search for the deletion position
        else if (searchKey < treePtr->item.getKey())
            deleteItem(treePtr->leftChildPtr, searchKey);

        else
            deleteItem(treePtr->rightChildPtr, searchKey);
    }

    void BinarySearchTree::deleteNodeItem(TreeNode * &nodePtr) {
        TreeNode *delPtr;
        TreeItemType replacementItem;

        // (1)  Test for a leaf
        if ( (nodePtr->leftChildPtr == NULL) &&
            (nodePtr->rightChildPtr == NULL) ) {
            delete nodePtr;
            nodePtr = NULL;
        }

        // (2)  Test for no left child
        else if (nodePtr->leftChildPtr == NULL){
            delPtr = nodePtr;
            nodePtr = nodePtr->rightChildPtr;
            delPtr->rightChildPtr = NULL;
            delete delPtr;
        }

        // (3)  Test for no right child
        else if (nodePtr->rightChildPtr == NULL) {
            delPtr = nodePtr;
            nodePtr = nodePtr->leftChildPtr;
            delPtr->leftChildPtr = NULL;
            delete delPtr;
        }

        // (4)  There are two children:
        // Retrieve and delete the inOrder successor
        else {
            processLeftmost(nodePtr->rightChildPtr, replacementItem);
            nodePtr->item = replacementItem;
        }
    }

    void BinarySearchTree::processLeftmost(TreeNode *&nodePtr, TreeItemType& treeItem){
        if (nodePtr->leftChildPtr == NULL) {
            treeItem = nodePtr->item;
            TreeNode *delPtr = nodePtr;
            nodePtr = nodePtr->rightChildPtr; → update the nodePtr
            delPtr->rightChildPtr = NULL; // defense (not really important)
            delete delPtr; // deallocate →free the memory!
        }
        else
            processLeftmost(nodePtr->leftChildPtr, treeItem);
    }


    // Builds a minimum-height binary search tree from n sorted
    // values in a file. treePtr will point to the tree’s root.
    readTree(out treePtr:TreeNodePtr, in n:integer)
        if (n>0) {

            treePtr = pointer to new node with NULL child pointers

            // construct the left subtree
            readTree(treePtr->leftChildPtr, n/2)

            // get the root
            Read item from file into treePtr->item

            // construct the right subtree
            readTree(treePtr->rightChildPtr, (n-1)/2)
        }
    }


     ! Operations on BST
     * Operation        Average Case         Worst Case
     * Retrieval         O(log(n))              O(n)
     * Insertion         O(log(n))              O(n)
     * Deletion          O(log(n))              O(n)
     * Traversal           O(n)                 O(n)

     ! Tree Sort        O(n*log(n))             O(n)
---------------------------------------------------------------------
~ Heaps
    & A heap (maxheap) is a complete binary tree such that
        – It is empty, or
        – Its root contains a search key greater than or equal to the search
        key in each of its children, and each of its children is also a heap.

    ! always COMPLETE binary tree
    ! The last ceiling(n/2) nodes of a heap are all leaves (array implementation)

    & deletion operation --> O(log(n))
    Void Heap::heapDelete(HeapItemType&rootItem) throw(HeapException) {
        if (heapIsEmpty())
            throwHeapException("HeapException: Heap empty");

        else {
            rootItem = items[0];
            items[0] = items[--size];
            heapRebuild(0);
        }
    }


    & insertion operation --> O(log(n))
    void Heap::heapInsert(constHeapItemType&newItem) throw(HeapException) {
        if (size >= MAX_HEAP)
            throw HeapException("HeapException: Heap full");

        // Place the new item at the end of the heap
        items[size] = newItem;

        // Trickle new item up to its proper position
        int place = size;
        int parent = (place - 1)/2;

        while ( (place > 0) && (items[place].getKey() > items[parent].getKey()) ) {
            HeapItemType temp = items[parent];
            items[parent] = items[place];
            items[place] = temp;
            place = parent;
            parent = (place - 1)/2;
        }

        ++size;
    }


    & rebuild operation
    voidHeap::heapRebuild(int root) {
        int child = 2 * root + 1; // index of root's left child, if any
        if ( child < size ) {
            // root is not a leaf so that it has a left child
            int rightChild = child + 1; // index of a right child, if any

            // If root has right child, find larger child
            if ( (rightChild < size) && (items[rightChild].getKey() >items[child].getKey()) )
                child = rightChild; // index of larger child

            // If root’s item is smaller than larger child, swap values
            if ( items[root].getKey() < items[child].getKey() ) {
                HeapItemType temp = items[root];
                items[root] = items[child];
                items[child] = temp;
                // transform the new subtree into a heap
                heapRebuild(child);
            }
    }


    & heap sort (both average and worst)--> O(n*log(n))
    heapSort(inout anArray:ArrayType, in n:integer) {

        // build an initial heap
        for (index = (n/2) – 1 ;  index >= 0 ;  index--)
            heapRebuild(anArray, index, n)

        for (last = n-1 ;  last >0 ;  last--) {
            // invariant: anArray[0..last] is a heap,
            // anArray[last+1..n-1] is sorted and
            // contains the largest items of anArray.

            swap anArray[0] and anArray[last]

            // make the heap region a heap again
            heapRebuild(anArray, 0, last)
        }
    }

---------------------------------------------------------------------
~ AVL Trees
    ^ An AVL tree is a binary search tree such that for any node
    ^  the height of the left and right subtrees can differ by at most 1

    ! insertion, deletion, retrieval (worst case)  -> O(log2N)
    ! when deleting a node frm-om the tree, use in order successor

    ^ (outside): left subtree of left child  OR  right subtree of right child -> single rotation
    ^ (inside): right subtree of left child  OR  left subtree of right child -> double rotation

    & Rotation types
        & R (parent becomes right child)
        & L (parent becomes left child)
        & LR (first L, then R)
        & Rl (first R, then L)
---------------------------------------------------------------------
~ 2 - 3 Trees
    ^ A tree in which each internal node has either two or three children
    ^ all leaves are at the same level

    ! A 2-3 tree with N nodes never has height greater than ceiling( log(N+1) )
    ! A 2-3 tree of height h always has at least 2h-1 nodes
    ! Searching a 2-3 tree is O(log N)
    ! insertion, deletion, retrieval based on key -> guaranteed O(log N)

    & 2 - 3 Tree's Node
    int smallItem, largeItem;
    23TreeNode *left, *mid, *right;

    ! insertion:
        • first put it to where it fits the best
        • then split the node if it has no place 
        • push the middle one up ↑

    ! deletion:
        • there are many cases:
            – Delete empty root
            – Merge nodes
            – Redistribute values

---------------------------------------------------------------------
~ 2 - 3 - 4 Trees
    ^ Allows 4-nodes (four children and three data items) too

    ! 2-3-4 tree more efficient insertion-deletion but greater storage requirements
    
    & 2 - 3 - 4 Tree's Node
    int smallItem, middleItem, largeItem;
    234TreeNode *left, *lMid, *rMid, *right;

    ! insertion:
        • We split each 4-node as soon as we encounter it during our search 
            from the root to a leaf

    ! deletion:
        • We transform each 2-node into either 3-node or 4-node 
            as soon as it is encountered on the way from the root to a leaf


        Case – 1: If either of the siblings of the current node is a 3 or 4 node.
            - Perform a rotation with that sibling.
            - The key having the closest value to this node moves up to the parent
                that overlooks the current node and
                the parent is added to the current node to make it a 3 node.
            - The node that was the originally rotated sibling’s child
                is now the child of the current node.


        Case – 2: If the parent is a 2 node and the sibling is also a 2 node
            - In this case the parent is root.
            - merge the three 2 nodes to form a 4 node. then remove the required value


        Case – 3: If the siblings are 2 nodes but the parent is a 3 node or 4 nodes:
            - Merge the siblings (2 nodes) and the parent key overlooking the siblings
            - Form a 4 node
            - The child of the siblings is brought to this node.

---------------------------------------------------------------------
~ Red - Black Trees
    ^ It is a special binary search tree
    ^ Can be used to represent 2-3-4 trees
    ^ so that we can retain advantages of a 2-3-4 tree without storage overhead

    ^ 3-node and 4-nodes are represented by a binary tree
    ^ To distinguish the original 2-nodes from generated ones we use red & black pointers
    ^ All original pointers are black pointers 
    ^ 2-nodes that result from the split of 3-nodes and 4-nodes are red pointers

    ! Root is always a black node.
    ! The children of a red node (pointed by a red pointer) are always    
        black nodes (pointed by a black pointer)
    ! All external nodes (leaves and nodes with a single child) should have 
        the same number of black pointers on the path from the root to that 
        external node.


    & red-black Tree Node
        enum Color {RED, BLACK};
        classTreeNode {
            private:
            int Item;
            redBlackTreeNode *left, *right;
            Color     leftColor, rightColor;
        }

    !!!!!!!!
todo  LEARN THE SPLITTING IN A RED-BLACK TREE
    !!!!!!!!

---------------------------------------------------------------------
~ Hash Table
    ^ A hash function tells us where to place an item in array called a hash table

    ^ Design a Hash Function
        1. Selecting digits: Select certain digits and combine to create the address
        2. Folding: selecting all digits and adding them
            We can select a group of digits and add the digits in this group as well
        3. Modular Arithmetic: h(x) = x  mod  tableSize -> simple and effective!
        ↓
        or a combination of all
    

    ! Collision Resolution:
        ^ Open Addressing: each entry 1 item
            = Probes some empty location whn collision occurs using:
                ^1- Linear Probing:
                    -> i, i+1, i+2, i+3, ...
                    Efficiency!!! important to prevent table from filling up
                ^2- Quadratic Probing:
                    -> i, i+1^2, i+2^2, i+3^2, i+4^2, ...
                ^3- Double Hashing: using a second hash function h2
                    -> h1(key), h1(key) + h2(key), h1(key) + 2*h2(key), ...


            Retrieval 
                Probe the locations until desired item or empty location
            Deletion
                Need three kinds of locations: Occupied, Empty, Deleted
                A deleted one is treated as an occupied location during retrieval


        ^4- Separate Chaining: each entry more than 1 item
            = Sol 1: Buckets
                each location is an array called "Bucket"
            = Sol 2: Separate-Chaining
                each entry is a pointer to a linked list (the chain)


        ? Efficiency: S. Chaining > Quadratic + D. Hashing > Linear


    ! load factor a = (current number of items) / tableSize
        • measures how full a hash table is
        • should not be too loaded
    

    ! Separate Chaining Analysis
        Successful search: 1+(a/2)
        Unsuccessful search: a
        • It is the most efficient collision resolution scheme
        • But it requires more storage (needs storage for pointers)
        • It easily performs the deletion operation



    & String hashing examples
        & example 1
        // if the table size is large, the function does not 
        // distribute the keys well

        int hash( const string &key, int tableSize ) {
            int hasVal = 0; 
            
            for (int i = 0; i < key.length(); i++)
                hashVal += key[i]; 

            // the insertion index
            return hashVal % tableSize; 
        }

    & example 2
    // Examine only the first 3 characters of the key

    int hash (const string &key, int tableSize) {
        return (key[0]+27 * key[1] + 729*key[2]) % tableSize; 
    }

    * Hash Tables VS Search Trees
        • In most operations, H. table performs better than s. tree
        • !However! traversing in a sorted order is difficult in h. table


    ? Performance (Chaining & Open Addressing)
    –  Search - O(1) expected, O(n) worst case
    –  Insert - O(1) expected, O(n) worst case
    –  Delete - O(1) expected, O(n) worst case
    -  Min, Max, Predecessor, Successor - O(n+m) expected + worst 


    !! Hash Tables ar mostly the best BUT the worst-case time is unpredictable
    !! The best worst-case bounds come from balanced binary trees

---------------------------------------------------------------------
~ Graphs
    ^ G = (V, E) 
    ^ Vertices: nodes, edges: arcs

    ! Simple path passes through a vertex only once
    ! Cycle is a path that begins and ends at the same vertex
    ! Simple cycle does not pass through other vertices more than once
    ! Connected graph has a path between each pair of distinct vertices
    ! Complete graph has an edge between each pair of distinct vertices
    
    ! If a directed graph is not strongly connected, but the underlying graph
        (without direction to arcs) is connected then the graph is weakly connected

    ! directed acyclic graph (DAG) is a directed graph with no cycles
    
    ! Vertex w is adjacent to v iff:
        There is a direct edge from  v to w

    ! If the edges are labelled with numeric values: Weighted Graph


    * Implementation
        - Adjacency Matrix
            • A two dimensional array
            • matrix[i][j] is weight that labels edge from vertex i to vertex j instead of 1, 
            • matrix[i][j] equals to "infinity" instead of 0 when there is no edge from vertex i to j
        – Adjacency List
            • For each vertex we keep a list of adjacent vertices    
            • for a graph with n vertices consists of n linked lists.
            • The ith linked list has a node for vertex j iff 
            the graph contains an edge from vertex i to vertex j

    ~ 2 common operations
        1. Determine whether there is an edge from vertex i to vertex j
            -> Adjacent Matrix more efficient
        2. Find all vertices adjacent to a given vertex i
            -> Adjacent List more efficient


    ! Matrix VS List
        – Adjacency matrix is better if the graph is dense (too many edges)
        – Adjacency list is better if the graph is sparse (few edges)
        ! Lists are better for most problems

    
    ~ Traversals (must mark vertexes when visited otherwise: infinite loops!)
        ? Depth First T.
            Visit a vertex, then visit one of the adjacent vertexes
            If there is no unvisited adjacent, back up to the previous step

            & Recursive DFT
            dft(in v:Vertex) {
                // Traverses a graph beginning at vertex v 
                // by using depth-first strategy
                // Recursive Version
                Mark v as visited;
                for (each unvisited vertex u adjacent to v)
                dft(u)
            }

            & Iterative DFT
            dft(in v:Vertex) {
                // Traverses a graph beginning at vertex v 
                // by using depth-first strategy: Iterative Version
                s.createStack();

                // push v into the stack and mark it
                s.push(v);
                
                Mark v as visited; 

                while (!s.isEmpty()) {
                    if (no unvisited vertices are adjacent to the vertex on the top of stack)
                        s.pop();  // backtrack
                    else {
                        Select an unvisited (u) adjacent to the vertex on the top of the stack;
                        s.push(u);
                        Mark u as visited;
                    }
                }
            }


        ? Breadth First T.
            visits every vertex adjacent to the one in hand

            & Iterative BFT
            bft(in v:Vertex) {
                // Traverses a graph beginning at vertex v 
                // by using breadth-first strategy: Iterative Version
                q.createQueue();

                // add v to the queue and mark it
                Mark v as visited; 
                q.enqueue(v);

                while (!q.isEmpty()) {
                    q.dequeue(w);
                    for (each unvisited vertex u adjacent to w) {
                        Mark u as visited;
                        q.enqueue(u);
                    }    
                }
            }


    ^ Topological Sort (Topological Order: Linear Order)
        • Arranging vertices into topological order is topological sorting
        
        • Order of visiting in a directed graph without cycles
        • So that we can visit vertex v after we visit its predecessors

        !For a given graph, there may be more than one topological order.

        & Simple Topological Sorting algo1
        topSort1(in theGraph:Graph, out aList:List) {
            // Arranges the vertices in graph theGraph into a
            // topological order and places them in list aList
            n = number of vertices in theGraph;

            for (step=1 through n) {
                select a vertex v that has no successors;
                aList.insert(1,v);
                Delete from theGraph vertex v and its edges;
            }
        }


        & DFS Topological Sorting algo2
        topSort2(in theGraph:Graph, out aList:List) {
            // Arranges the vertices in graph theGraph into a topological order and 
            // places them in list aList
            s.createStack();

            for (all vertices v in the graph) {
                if (v has no predecessors) {
                    s.push(v);
                    Mark v as visited;
                }
            }

            while (!s.isEmpty()) {
                if (all adjacent are visited) {
                    s.pop(v);
                    aList.insert(1,v);
                }
                else {
                    Select an unvisited vertex u adjacent to the vertex on 
                    the top of the stack;
                    s.push(u);
                    Mark u as visited;
                }
            } 
        }


    * Spanning Trees (of a connected undirected graph G)
        A sub-graph of G that contains all of G’s vertices
            and enough of its edges to form a tree


    & DFT Spanning Tree
    dfsTree(in v:vertex) {
        // Forms a spanning tree for a connected undirected graph
        // beginning at vertex v by using depth-first search;
        // Recursive Version
        Mark v as visited;
        for (each unvisited vertex u adjacent to v) {
            Mark the edge from u tu v; // different form normal DFT 
            dfsTree(u);
        }
    }


    & BFT Spanning Tree
    bfsTree(in v:vertex) {
        // Forms a spanning tree for a connected undirected graph
        // beginning at vertex v by using breadth-first search;
        // Iterative Version
        q.createQueue();
        q.enqueue(v);
        Mark v as visited;

        while (!q.isEmpty()) {
            q.dequeue(w);

            for (each unvisited vertex u adjacent to w) {
                Mark u as visited;
                Mark edge between w and u; // different form normal BFT 
                q.enqueue(u);
            }
        }
    }

    * Minimum Spanning Tree
        ! has a minimal edge-weight sum


    ^ Prim's Algorithm
        • finds a minimum spanning tree that begins any vertex
        • Initially, the tree contains only the starting vertex
        • At each stage, the algorithm selects a least-cost edge from those 
        beginning with a vertex in the tree and end with a vertex not in the tree
        • The selected vertex and least-cost edge are added to the tree


        & Prim's Algo
        primsAlgorithm(in v:Vertex) {
            // Determines a minimum spanning tree for a weighted, 
            // connected, undirected graph whose weights are 
            // nonnegative, beginning with any vertex.
            Mark vertex v as visited and add to minimum spanning tree;
            while (there are unvisited vertices) {
                Find least-cost edge from visited v to unvisited u;
                Mark u as visited;
                Add vertex u and edge (v,u) to minimum spanning tree;
            }
        }

    ^ Shortest Path
        ! Dijkstra’s shortest-path algorithm finds the shortest paths between 
        vertex 0 (the given vertex) and all other vertices

        & Dijkstra's Algo
        shortestPath(in theGraph, in weight:WeightArray) {
            // Finds the minimum-cost paths between an origin vertex (vertex 0)
            // and all other vertices in a weighted directed graph theGraph;
            // theGraph’s weights are nonnegative
            Create a set vertexSet that contains only vertex 0;
            n = number of vertices in the Graph;

            // Step 1
            for (v=0 through n-1) {
                weight[v] = matrix[0][v];
            }

            // Steps 2 through n
            for (v=2 through n) {
                Find the smallest weight[v] such that v is not in vertexSet;
                Add v to vertexSet;

                for (all vertices u adjacent to v but not in vertexSet) {
                    if (weight[u] > weight[v]+matrix[v][u]) {
                        weight[u] = weight[v]+matrix[v][u];
                    }
                }
            }
        }

*/
