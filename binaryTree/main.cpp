#include <QtCore>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "binarytree.h"
#include "vectorbinarytree.h"
#include <ctime>
#include <iomanip>
#include <vector>

#define MAXTREE 2

using namespace std;

int beta=1;

bool again();
template<typename T>
void menu(binaryTree<T> tree[],int &toUse);
template<typename T>
void perform(binaryTree<T> &myTree, char selection, int &touse);


int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);
  if(beta==0)
  {
      binaryTree<char> tree[MAXTREE];
      int touse=0;
      do
      {
//        menu(tree, touse);
      }while(again());
  }
  else if(beta==1)
  {
      binaryTree<int> tree[MAXTREE];
      cout<<"Unsorted numbers: "<<endl;
      int touse=0;
      int theRandNum;
      srand(time(NULL));
      for(int i = 0; i < 10; i++)
      {
          theRandNum = rand()% 100 + 1;
          cout<<i<<")insert "<<theRandNum<<endl;
          tree[touse].insert(theRandNum);
          cout<<tree[touse]<<endl;
      }
      cout<<tree[touse]<<endl;
      cout<<"display tree"<<endl;
//      for(int i=0;i<5;i++)
//      {
//          tree[touse].display(i);
//      }
      tree[touse].display(10);
      cout<<endl<<"**********remove node**********"<<endl;
      cout<<"0) endloop"<<endl;
      cout<<"1) remove data"<<endl;
      bool endLoop=false;
      int index,data;
      do
      {
          cout<<endl<<"index; ";
          cin>>index;
          if(index==0)
              endLoop=true;
          else
          {
              cout<<"data; ";
              cin>>data;
              if(tree[touse].remove(data)==true)
                  cout<<"remove is done"<<endl;
              else
                  cout<<"remove is error"<<endl;
              cout<<tree[touse]<<endl;
              tree[touse].display(10);
          }




      }while(endLoop!=true);

      cout<<endl<<"beta done"<<endl;
  }
  else if(beta==2)//binary vector tree
  {
      bool randInsert=true;
      vectorBinaryTree<int> vTree;
      cout<<"Unsorted numbers: "<<endl;
      if(randInsert==true)
      {
          int theRandNum;
          srand(time(NULL));
          for(int i = 0; i < 10; i++)
          {
              theRandNum = rand()% 100 + 1;
              cout<<i<<")insert "<<theRandNum<<endl;
              vTree.insert(theRandNum);
          }
      }
      else
      {
          vTree.insert(1);
          vTree.insert(2);
          vTree.insert(3);
      }



      cout<<"display tree beta 2"<<endl;
      vTree.display();
      cout<<"rebalance**************"<<endl;
      vTree.reBalance();
      vTree.display();
      cout<<endl<<"end of beta vector binary tree"<<endl;

  }
  else if(beta==3)
  {
      cout<<"vector test"<<endl;
      vector<int> v1;
      vector<int> v2;
      v1.reserve(50);
      v2.reserve(50);
      for(int i=0;i<50;i++)
      {
          v1[i]=NULL;
          v2[i]=NULL;
      }
      int theRandNum;
      srand(time(NULL));
      for(int i = 0; i < 10; i++)
      {
          theRandNum = rand()% 100 + 1;
          cout<<"v1["<<i<<"]= "<<theRandNum<<endl;
          v1[i]=theRandNum;
      }
      cout<<"v2 outcome"<<endl;
      v2=v1;
      for(int i = 0; i < 20; i++)
      {
          cout<<"v2["<<i<<"]= "<<v2[i]<<endl;
      }
  }

  return a.exec();
}

bool again()
{
   char ans;
   cout<<"Do you want to do this again? ";
   cin >> ans;
   return toupper(ans) == 'Y';
}

template<typename T>
void perform(binaryTree<T> tree[], char selection, int &touse)
{
   T value;
   int order;
   char name[30];
   switch(toupper(selection))
   {

     case '+' :
     case 'E' : cout<<"What value do you want to put into the tree? ";
                cin>> value;
                tree[touse].insert(value);
                break;

     case '-' :
     case 'D' : cout<<"What value do you want to see if it is in the tree? ";
                cin>> value;
//                if(tree[touse].remove(value))
                   cout<<value<<" removed successfully"<<endl;
//                else
//                   cout<<"Item not in tree -- therefore it was not removed."<<endl;
//                break;

     case 'P' : cout<<tree[touse]<<endl;
                break;

     case 'F' : cout<<"What value do you want to see if it is in the tree? ";
                cin>> value;
                if(tree[touse].find(value))
                     cout<<"The tree has this value in it"<<endl;
                else
                    cout<<"The tree does not have this value in it"<<endl;
                break;


     case 'C' : cout<<"There are "<<tree[touse].totalDataItems()<<" items in the tree "<<endl;
                break;

     case 'N' : cout<<"There were "<<tree[touse].totalDataItems()<<" items in the tree you just disposed"<<endl;
                tree[touse].clear();
                break;

     case 'S' : do
                {
                   cout<<"Enter 1 for a PREORDER, 2 for INORDER and 3 for POSTORDER ";
                   cin>>order;
                }while(order<1 || order > 3);
                switch(order)
                {
                    case 1: tree[touse].setTraversal(PRE_ORDER);
                            break;
                    case 2: tree[touse].setTraversal(IN_ORDER);
                            break;
                    case 3: tree[touse].setTraversal(POST_ORDER);
                            break;
                }
                break;

     case 'T' : do
                {
                   cout<<"Which tree do you want to use: ";
                   cin>>order;
                }while(order < 0 || order > MAXTREE);
                break;


     case 'W' : {
                  ofstream out;
                  cout<<"What is the name of the file you want to write to: ";
                  cin>>name;
                  out.open(name);
                  out<<tree[touse];
                  out.close();
                  break;
                }

     case 'R' : {
                  ifstream in;
                  cout<<"What is the name of the file you want to read from: ";
                  cin>>name;
                  in.open(name);
                  in>>tree[touse];
                  in.close();
                  break;
                }

     case 'Q' : cout<<"Goodbye"<<endl;
   }
}


void menu(binaryTree<char> tree[],int &toUse)
{
  char selection;
  do
  {
     cout<<endl;
     cout<<"Menu Selections for tree operations"<<endl
         <<" E. Enter data"<<endl
         <<" D. Delete data"<<endl
         <<" S. Select print order"<<endl
         <<" P. Print the tree"<<endl
         <<" F. Find if an item is in the tree"<<endl
         <<" T. Select tree to use"<<endl
         <<" R. Read from a file"<<endl
         <<" W. Write to a file"<<endl
         <<" C. Count how many items are in the tree"<<endl
         <<" N. Empty the tree"<<endl
         <<" Q. Quit"<<endl
         <<"What is your selection: ";
     cin>>selection;
     perform(tree, selection, toUse);
  }while(toupper(selection) != 'Q');
}
