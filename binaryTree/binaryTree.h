#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include "node.h"

using namespace std;

enum ORDER {IN_ORDER, POST_ORDER, PRE_ORDER};

template<typename T>
class binaryTree
{
    public:
        binaryTree();
        binaryTree(T d, int c = 1);
        ~binaryTree();
        binaryTree(const binaryTree<T> &other);
        binaryTree<T>& operator=(const binaryTree<T> &other);

        void insert(T d, int c = 1);
        bool remove(T d);
        int find(T d);
        ORDER getTraversal();
        void setTraversal(ORDER traversal);
        int depth();//need remove
        int totalNodes();
        int totalDataItems();
        void rebalance();
        void clear();

        int maxHeight(node<T> *Leaf);//find max length of


        int rightWeight(node<T> *Leaf);
        int leftWeight(node<T> *Leaf);
        int WeightMeasure(node<T> *Leaf);
        int rightLength(node<T> *Leaf);
        bool isBlanced(node<T> *root);
        int height(node<T> *Leaf);
        int max(int a, int b);
        node<T>* Left_Rotation(node<T> *Leaf);
        node<T>* Right_Rotation(node<T> *Leaf);
        node<T>* Left_Right_Rotation(node<T> *Leaf);
        node<T>* Right_Left_Rotation(node<T> *Leaf);

        void display(node<T> *Leaf,int level);
        void display(int level);



        binaryTree<T>& operator<<(T d);

        template<typename U>
        friend
        ostream& operator<<(ostream& out, binaryTree<U> &n);

        template<typename U>
        friend
        istream& operator>>(istream& in, binaryTree<U> &n);

    private:
        node<T> *root;
        ORDER printOrder;
        int depth(node<T> *r);
        int totalNodes(node<T> *r);
        int totalDataItems(node<T> *r);
        void nukem(node<T>* &r);
        void copy(node<T> *r);
        void display(node<T> *r, ostream& out = cout);
        int find(T d, node<T> *r);
        node<T>* findParent(node<T> *r, T d);
        node<T>* insert(node<T> *branch, T data, int c);
        node<T>* findLeftMost(node<T> *r);
        node<T>* findRightMost(node<T> *r);
        node<T>* rebalance(node<T>* &r);
        void placeData(node<T>* leaf, node<T>* branch);
        node<T>* remove(node<T> *branch, T data, int c);
        node<T>* fallingNode(node<T> *branch);
        void dataSwap(node<T> *parent,node<T> *child);



};

template<typename T>
binaryTree<T>::binaryTree()
{
    root = NULL;
    printOrder = IN_ORDER;
}

template<typename T>
binaryTree<T>::binaryTree(T d, int c )
{
    root = new node<T>(d,c);
    printOrder = IN_ORDER;
}

template<typename T>
binaryTree<T>::~binaryTree()
{
    nukem(root);
}


template<typename T>
binaryTree<T>::binaryTree(const binaryTree<T> &other)
{
    copy(other.root);
}


template<typename T>
binaryTree<T>& binaryTree<T>::operator=(const binaryTree<T> &other)
{
    if(this != &other)
    {
        nukem(root);
        copy(other.root);
    }
    return *this;
}


template<typename T>
void binaryTree<T>::insert(T d, int c)
{
    root=insert(root,d,c);
}


template<typename T>
bool binaryTree<T>::remove(T d)
{
    if(remove(root,d,1)==NULL)
        return false;
    else
        return true;

}


template<typename T>
int binaryTree<T>::find(T d)
{
    return find(d,root);
}


template<typename T>
ORDER binaryTree<T>::getTraversal()
{
    return printOrder;
}


template<typename T>
void binaryTree<T>::setTraversal(ORDER traversal)
{
    printOrder = traversal;
}


template<typename T>
int binaryTree<T>::depth()
{
    return depth(root);
}


template<typename T>
int binaryTree<T>::totalNodes()
{
    return totalNodes(root);
}


template<typename T>
int binaryTree<T>::totalDataItems()
{
    return totalDataItems(root);
}


template<typename T>
void binaryTree<T>::clear()
{
    nukem(root);
}


template<typename T>
binaryTree<T>& binaryTree<T>::operator<<(T d)
{
    insert(d);
    return *this;
}


template<typename T>
int binaryTree<T>::depth(node<T> *r)
{
    return r ? 1 + max(depth(r->left), depth(r->right)) : 0;
}

template<typename T>
int binaryTree<T>::totalNodes(node<T> *r)
{
    return r ? 1 + totalNodes(r->left) + totalNodes(r->right) : 0;
}


template<typename T>
int binaryTree<T>::totalDataItems(node<T> *r)
{
    return r ? r->count + totalDataItems(r->left) + totalDataItems(r->right) : 0;
}

template<typename T>
void binaryTree<T>::nukem(node<T>* &r)
{
    if(r)
    {
        nukem(r->left);
        nukem(r->right);
        delete r;
        r = NULL;
    }
}


template<typename T>
void binaryTree<T>::copy(node<T> *r)
{
    if(r)
    {
        insert(r->data, r->count);
        copy(r->left);
        copy(r->right);
    }

}


template<typename T>
void binaryTree<T>::display(node<T> *r, ostream& out)
{
    if(!r)
        return;
    if(printOrder == PRE_ORDER)
        out<<r->data<<"["<<r->count<<"] ";
    if(r->left)
        display(r->left,out);
    if(printOrder == IN_ORDER)
        out<<r->data<<"["<<r->count<<"] ";
    if(r->right)
        display(r->right,out);
    if(printOrder == POST_ORDER)
        out<<r->data<<"["<<r->count<<"] ";

}


template<typename T>
int binaryTree<T>::find(T d, node<T> *r)
{
    return !r ? 0 :
                d == r->data ? r->count :
                d < r->data ? find(d, r->left) :
                              find(d, r->right);
}


template<typename T>
node<T>* binaryTree<T>::findParent(node<T> *r, T d)
{
    return !r ? NULL :
             r->left->data == d || r->right->data == d ? r
             :
             d < r->data ? findParent(r->left,d)
             : findParent(r->right,d);
}


template<typename T>
node<T>* binaryTree<T>::insert(node<T> *branch, T data, int c)
{

    if(!branch)
    {
        node<T> *newNode = new node<T>(data,c);
        branch = newNode;
    }
    else if(data< branch->data)
    {
        branch->left=insert(branch->left,data,c);
        branch=rebalance(branch);
    }
    else if(data> branch->data)
    {
        branch->right=insert(branch->right,data,c);
        branch=rebalance(branch);
    }
    else if(data== branch->data)
    {
        branch->count+=c;
    }
    else
    {
        cout<<"super error"<<endl;
    }

}


template<typename T>
node<T>* binaryTree<T>::findLeftMost(node<T> *r)
{
    return !r ? NULL :
            r->left == NULL ? r :
            findLeftMost(r->left);
}


template<typename T>
node<T>* binaryTree<T>::findRightMost(node<T> *r)
{
    return !r ? NULL :
            r->right == NULL ? r :
            findRightMost(r->right);
}



template<typename T>
node<T>* binaryTree<T>::rebalance(node<T>* &r)
{
    int depthLeft = maxHeight(r->left),
        depthRight = maxHeight(r->right),
        diff = depthLeft - depthRight;
//    if(abs(diff) <= 1)
//        return;
    if(diff > 1)//left side is heavy
    {
        //Left is out of wack
        if(depthLeft>0)
        {
            r=Left_Rotation(r);
            cout<<"Left_Rotation["<<r->data<<"]"<<endl;

        }
        else
        {
            r=Left_Right_Rotation(r);
            cout<<"Left_Right_Rotation["<<r->data<<"]"<<endl;
        }

    }
    else if(diff<-1)//right side is heavy
    {
        //Right is out of wack
        if(depthRight>0)
        {
            r=Right_Rotation(r);
            cout<<"Right_Rotation["<<r->data<<"]"<<endl;
        }

        else
        {
            r=Right_Left_Rotation(r);
            cout<<"Right_Rotation["<<r->data<<"]"<<endl;
        }
    }
    return r;
}

template<typename T>
void binaryTree<T>::rebalance()
{
    root=rebalance(root);
}

template<typename U>
ostream& operator<<(ostream& out, binaryTree<U> &n)
{
    if(out != cout)
        out<<"Print order was: "<<n.printOrder<<endl;
    n.display(n.root, out);
    return out;
}

template<typename U>
istream& operator>>(istream& in, binaryTree<U> &n)
{
    U data;
    int count, printOrder;
    char junk;
    string line;
    stringstream ss;
    ORDER order[3] = {IN_ORDER, PRE_ORDER, POST_ORDER};
    if(in != cin)
    {
        getline(in, line);
        ss<<line.substr(line.find(':')+1);
        ss>>printOrder;
        n.printOrder = order[printOrder];
    }
    while(in>>data>>junk>>count>>junk)
        n.insert(data,count);
    return in;
}


//find the max height, by finding the bottem and keep track of hte bottemest
template<typename T>
int binaryTree<T>::maxHeight(node<T> *Leaf)
{
    int height=0;
    if(Leaf!=NULL)
    {
        int Left_Height=maxHeight(Leaf->left);
        int Right_Height=maxHeight(Leaf->right);
        height=max(Left_Height,Right_Height)+1;
    }
    return height;
}



template<typename T>
node<T>* binaryTree<T>::Left_Rotation(node<T> *Leaf)
{
    node<T> *newRoot;
    newRoot=Leaf->left;
    Leaf->left=newRoot->right;
    newRoot->right=Leaf;
    return newRoot;
}


template<typename T>
node<T>* binaryTree<T>::Right_Rotation(node<T> *Leaf)
{
    node<T> *newRoot;
    newRoot=Leaf->right;
    Leaf->right=newRoot->left;
    newRoot->left=Leaf;
    return newRoot;
}


template<typename T>
node<T>* binaryTree<T>::Left_Right_Rotation(node<T> *Leaf)
{
    node<T> *newRoot;
    newRoot=Leaf->left;
    Leaf->left=Right_Rotation(newRoot);
    return Left_Rotation(Leaf);
}

template<typename T>
node<T>* binaryTree<T>::Right_Left_Rotation(node<T> *Leaf)
{
    node<T> *newRoot;
    newRoot=Leaf->right;
    Leaf->right=Left_Rotation(newRoot);
    return Right_Rotation(Leaf);
}



template<typename T>
void binaryTree<T>::display(node<T> *Leaf, int level)
{
    int i;
    if(Leaf!=NULL)
    {
        display(Leaf->right,level+1);
        printf("\n");
        if(Leaf==root)
            cout<<"->";
        for(i=0; i<level&&Leaf!=root;i++)
            cout<<"\t";
        cout<<Leaf->data;
        display(Leaf->left,level+1);
    }
}



template<typename T>
void binaryTree<T>::display(int level)
{
    display(root,level);
}










//branch is the parent it checking, leaf is the node to add
template<typename T>
void binaryTree<T>::placeData(node<T> *leaf, node<T> *branch)
{
    cout<<"leaf "<<leaf->data<<"\tbranch "<<branch->data<<endl;
    if(leaf->data> branch->data)
    {
        if(branch->right==NULL)
        {
            branch->right=leaf;
        }
        else
        {
            placeData(leaf,branch->right);
            branch=rebalance(branch);
        }
    }
    else if(leaf->data<branch->data)
    {
        if(branch->left==NULL)
        {
            branch->left=leaf;
        }
        else
        {
            placeData(leaf,branch->left);
            branch=rebalance(branch);
        }
    }
    else if(leaf->data==branch->data)
    {
        branch->count++;
    }
}

template<typename T>
int binaryTree<T>::rightWeight(node<T> *Leaf)
{
    if(Leaf->right==NULL)
        return 0;
    else
        return WeightMeasure(Leaf->right);

//    int size =1;//each node worth one point,
//    if(Leaf->right!=NULL)
//    {
//        Leaf=Leaf->right;
//        size +=rightWeight(Leaf);
//    }
//    if(Leaf->left!=NULL)
//    {
//        Leaf=Leaf->left;
//        size +=rightWeight(Leaf);
//    }
//    return size;
}

template<typename T>
int binaryTree<T>::leftWeight(node<T> *Leaf)
{
    if(Leaf->left==NULL)
    {
         return 0;
    }
    else
        return WeightMeasure(Leaf->left);
}
template<typename T>
int binaryTree<T>::WeightMeasure(node<T> *Leaf)
{
    int size=1;
    if(Leaf->left!=NULL)
    {
        Leaf=Leaf->left;
        size+=WeightMeasure(Leaf);
    }
    if(Leaf->right!=NULL)
    {
        Leaf=Leaf->right;
        size+=WeightMeasure(Leaf);
    }
    return size;
}

template<typename T>
bool binaryTree<T>::isBlanced(node<T> *root)
{
    int leftH;//hight for left subtree
    int rightH;//hight for right subtree

    if(root==NULL)
    {
        return true;
    }
    leftH=height(root->left);
    rightH=height(root->right);
    if(abs(leftH-rightH)<=1 && isBlanced(root->left) && isBlanced(root->right))
    {
        return true;
    }
    else
    {
        return false;
    }


}

template<typename T>
int binaryTree<T>::height(node<T> *Leaf)
{
    if(Leaf==NULL)
        return 0;
    else
    {
        return 1+max(height(Leaf->left),height(Leaf->right));
    }

}

template<typename T>
int binaryTree<T>::max(int a, int b)
{
    return (a >= b)? a: b;
}


//return null if the data do not exist,
template<typename T>
node<T>* binaryTree<T>::remove(node<T> *branch, T data, int c)
{
    if(!branch)
    {
        cout<<"did not find"<<endl;
        return NULL;
    }
    else if(data< branch->data)
    {
        branch=remove(branch->left,data,c);
    }
    else if(data> branch->data)
    {
        branch=remove(branch->right,data,c);
    }
    else if(data== branch->data)
    {
        if(branch->count-c>1)
        {
            branch->count -=c;
        }
        else
        {
            cout<<"start fallingNode"<<endl;
            branch=fallingNode(branch);
        }

    }
    else
    {
        cout<<"super error"<<endl;
    }
    return branch;
}

template<typename T>
node<T>* binaryTree<T>::fallingNode(node<T> *branch)
{
    if(branch->left==NULL && branch->right==NULL)
    {
        cout<<"single parent"<<endl;
        nukem(branch);
    }
    else if(maxHeight(branch->left)>maxHeight(branch->right))
    {
        cout<<" left swaping"<<endl;
        dataSwap(branch,branch->left);
        fallingNode(branch->left);
    }
    else if(maxHeight(branch->left) <= maxHeight(branch->right))
    {
        cout<<"right swaping"<<endl;
        dataSwap(branch,branch->right);
        fallingNode(branch->right);
    }
    return branch;
}

template<typename T>
void binaryTree<T>::dataSwap(node<T> *parent, node<T> *child)
{
    cout<<"data swap "<<parent->data<<" to "<<child->data<<endl;
    T tempData;
    int tempCount;

    tempData=parent->data;
    parent->data=child->data;
    child->data=tempData;

    tempCount=parent->count;
    parent->count=child->data;
    child->count=tempCount;

}




#endif // BINARYTREE_H
