#ifndef VECTORBINARYTREE_H
#define VECTORBINARYTREE_H

#include <vector>
#include <iostream>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include"vectornode.h"

using namespace std;

template<typename T>
class vectorBinaryTree
{
public:
    vectorBinaryTree(unsigned int s=500);
    ~vectorBinaryTree();


    void insert(T data,int c=1);
    int findParent(unsigned int i);
    int findRightChild(unsigned int i);
    int findLeftChild(unsigned int i);
    bool RightChildNull(unsigned int i);
    bool LeftChildNull(unsigned int i);
    void Swap(VectorNode<T>*a,VectorNode<T> *b);
    T returnData(unsigned i);
    void display();
    int maxHeight(int i);
    int max(int a, int b);

    void saveArray(vector<VectorNode<T>*> &vTemp,unsigned int i);
    void reBalance();
    bool isBalance(unsigned int i);

private:
    vector<VectorNode<T>*> vArray;
    VectorNode<T> *vNode;
    int totalNode;
    int lastLocation;
    void nukem(unsigned i);


    void insert(T data, int c,int location);
    void saveArray(vector<VectorNode<T>*> &vTemp,unsigned int i,unsigned int j);
    void reBalance(unsigned int i);
    void makeSpace(unsigned int i,bool &isLeft);
    void pushUp(unsigned int i, bool isLeft);

};


template<typename T>
vectorBinaryTree<T>::vectorBinaryTree(unsigned int s)
{
    vArray.reserve(s);
    for(int i=0;i<s;i++)
    {
        vArray[i]=NULL;
    }
    totalNode=0;
}

template<typename T>
vectorBinaryTree<T>::~vectorBinaryTree()
{

}
template<typename T>
void vectorBinaryTree<T>::nukem(unsigned i)
{
    vArray[i]=NULL;
}


template<typename T>
void vectorBinaryTree<T>::insert(T data, int c)
{
    totalNode++;
    if(vArray[0]==NULL)
    {
        VectorNode<T> *newNode=new VectorNode<T>(data,c);
        vArray[0]=newNode;
        lastLocation=0;
        cout<<"1vArray[0]="<<data<<endl;
    }
    else
    {
        insert(data,c,0);
    }
//    reBalance();

}

template<typename T>
int vectorBinaryTree<T>::findParent(unsigned int i)
{
    if(i==0)
    {
        cout<<"is the root data, no parent"<<endl;
    }
    else
    {
        return (i-1)/2;
    }
}

template<typename T>
int vectorBinaryTree<T>::findLeftChild(unsigned int i)
{
    return (i*2)+1;
}

template<typename T>
int vectorBinaryTree<T>::findRightChild(unsigned int i)
{
    return (i*2)+2;
}

template<typename T>
bool vectorBinaryTree<T>::LeftChildNull(unsigned int i)
{
    if(vArray[findLeftChild(i)]==NULL)
        return true;
    else
        return false;
}

template<typename T>
bool vectorBinaryTree<T>::RightChildNull(unsigned int i)
{
    if(vArray[findRightChild(i)]==NULL)
        return true;
    else
        return false;
}

template<typename T>
void vectorBinaryTree<T>::Swap(VectorNode<T> *a, VectorNode<T> *b)
{
    VectorNode<T> *newNode=a;
    a=b;
    b=newNode;
}

template<typename T>
void vectorBinaryTree<T>::insert(T data, int c, int location)
{

    if(!vArray[location])
    {
        cout<<"2vArray["<<location<<"]="<<data<<endl;
        VectorNode<T> *newNode = new VectorNode<T>(data,c);
        vArray[location] = newNode;
        if(location>lastLocation)
            lastLocation=location;
    }
    else
    {
        VectorNode<T> *temp;
        temp=vArray[location];

        if(data< temp->data)
        {
            insert(data,c,findLeftChild(location));
        }
        else if(data> temp->data)
        {
            insert(data,c,findRightChild(location));
        }
        else if(data== temp->data)
        {
            temp->count+=c;
        }
        else
        {
            cout<<"super error"<<endl;
        }
    }
//    reBalance();
}

template<typename T>
T vectorBinaryTree<T>::returnData(unsigned i)
{
    if(vArray[i]==NULL)
    {
        cout<<"null data ";
        return NULL;
    }
    else
    {
        VectorNode<T> * temp;
        temp=vArray[i];
        return temp->data;
    }
}

template<typename T>
void vectorBinaryTree<T>::display()
{
    cout<<"display tree last location= "<<lastLocation<<endl;
    for(int i=0;i<lastLocation+1;i++)
    {
        if(vArray[i]!=NULL)
        {
            VectorNode<T> * tempNode;
            tempNode=vArray[i];
//            cout<<"tempNode["<<i<<"]="<<tempNode->data<<" #)"<<tempNode->count<<endl;
            cout<<"tempNode["<<i<<"]="<<tempNode->data<<" leftH="<<maxHeight(findLeftChild(i))<<", rightH="<<maxHeight(findRightChild(i))<<endl;
        }



    }
}

template<typename T>
int vectorBinaryTree<T>::maxHeight(int i)
{
    int height=0;
    if(vArray[i]!=NULL)
    {
        int Left_Height=maxHeight(findLeftChild(i));
        int Right_Height=maxHeight(findRightChild(i));
        height=max(Left_Height,Right_Height)+1;
    }
    return height;
}

template<typename T>
int vectorBinaryTree<T>::max(int a, int b)
{
    return (a >= b)? a: b;
}


template<typename T>
void vectorBinaryTree<T>::saveArray(vector<VectorNode<T> *> &vTemp, unsigned int i, unsigned int j)
{
    vTemp[j]=vArray[i];
    if(vArray[findLeftChild(i)]!=NULL)
    {
        saveArray(vTemp,findLeftChild(i),findLeftChild(j));
    }
    if(vArray[findRightChild(i)]!=NULL)
    {
        saveArray(vTemp,findRightChild(i),findRightChild(j));
    }
}

template<typename T>
void vectorBinaryTree<T>::saveArray(vector<VectorNode<T> *> &vTemp, unsigned int i)
{
    vTemp=saveArray(vTemp,i,0);
}

template<typename T>
void vectorBinaryTree<T>::reBalance()
{
    if(vArray[0]==NULL)
    {
        cout<<"No data:reBalance()"<<endl;
    }
    else
    {
        for(int i=0;i<lastLocation;i++)
        {
            reBalance(i);
        }

    }

}

template<typename T>
void vectorBinaryTree<T>::reBalance(unsigned int i)
{
    int depthLeft = maxHeight(findLeftChild(i)),
        depthRight = maxHeight(findRightChild(i)),
        diff = depthLeft - depthRight;

    if(abs(diff) > 1)//left side is heavy
    {
        VectorNode<T> *temp;
        temp=vArray[i];
        cout<<"unblance ->"<<i<<")= "<<temp->data<<" Left="<<depthLeft<<" right="<<depthRight<<endl;
        bool direction;
        //make space on right side
        makeSpace(i,direction);//move all data one space down to the lighest branch
        //move the heavyest branch up one
        cout<<"after makespace"<<endl;
        pushUp(i,direction);

    }
}


template<typename T>
bool vectorBinaryTree<T>::isBalance(unsigned int i)
{
    int leftH;//hight for left subtree
    int rightH;//hight for right subtree

    if(vArray[0]==NULL)
    {
        return true;
    }
    leftH=maxHeight(findLeftChild(i));
    rightH=maxHeight(findRightChild(i));
    if(abs(leftH-rightH)<1 && isBlanced(findLeftChild(i)) && isBlanced(findRightChild(i)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

//this will move the lighest branch one down, leaving i to be null;
//return 1, if pushing the node down left, return 0 if right
template<typename T>
void vectorBinaryTree<T>::makeSpace(unsigned int i, bool &isLeft)
{
    VectorNode<T> *newNode;
    swap(newNode,vArray[i]);
    bool endLoop=false;
    if(maxHeight(findLeftChild(i))>maxHeight(findRightChild(i)))
        isLeft=false;
    else
        isLeft=true;


    do
    {
        int depthLeft = maxHeight(findLeftChild(i)),
            depthRight = maxHeight(findRightChild(i));


        if(depthLeft>depthRight)//move right side down
        {
            i=findRightChild(i);
            if(vArray[i]==NULL)
                endLoop=true;
            swap(newNode,vArray[i]);
        }
        else if(depthLeft<=depthRight)//move left side down
        {
            i=findLeftChild(i);
            if(vArray[i]==NULL)
                endLoop=true;
            swap(newNode,vArray[i]);
        }


    }while(endLoop!=true);

}
//
//i is the orginal insert location, j is the source of the data
template<typename T>
void vectorBinaryTree<T>::pushUp(unsigned int i, bool isLeft)//false=left up, true=right up
{
        if(isLeft)
        {
            swap(vArray[i],vArray[findRightChild(i)]);
            i=findRightChild(i);
        }
        else
        {
            swap(vArray[i],vArray[findLeftChild(i)]);
            i=findRightChild(i);
        }

        bool endLoop=false;

        do
        {
            int depthLeft = maxHeight(findLeftChild(i)),
                depthRight = maxHeight(findRightChild(i));


            if(depthLeft>depthRight)//move right side down
            {
                if(vArray[findLeftChild(i)]!=NULL)
                {
                    endLoop=true;
                    swap(vArray[findLeftChild(i)],vArray[i]);
                    i=findLeftChild(i);
                }
                else
                    endLoop=true;
            }
            else if(depthLeft<=depthRight)//move left side down
            {
                if(vArray[findRightChild(i)]!=NULL)
                {
                    endLoop=true;
                    swap(vArray[findRightChild(i)],vArray[i]);
                    i=findRightChild(i);
                }
                else
                    endLoop=true;
            }


        }while(endLoop!=true);


}

#endif // VECTORBINARYTREE_H
