//首先我们定义的二元查找树 节点的数据结构如下：
struct BSTreeNode
{
  int m_nValue; // value of node
  BSTreeNode *m_pLeft; // left child of node
  BSTreeNode *m_pRight; // right child of node
};


//引用 245 楼 tree_star 的回复
#include <stdio.h>
#include <iostream.h>

struct BSTreeNode
{
    int m_nValue; // value of node
    BSTreeNode *m_pLeft; // left child of node
    BSTreeNode *m_pRight; // right child of node
};


typedef struct BSTreeNode DoubleList;;
DoubleList * pHead;
DoubleList * pListIndex;

void convertToDoubleList(BSTreeNode * pCurrent);
// 创建二元查找树
void addBSTreeNode(BSTreeNode * & pCurrent, int value)
{
    if (NULL == pCurrent)
    {
        BSTreeNode * pBSTree = new BSTreeNode();
        pBSTree->m_pLeft = NULL;
        pBSTree->m_pRight = NULL;
        pBSTree->m_nValue = value;
        pCurrent = pBSTree;

    }
    else 
    {
        if ((pCurrent->m_nValue) > value)
        {
            addBSTreeNode(pCurrent->m_pLeft, value);
        }
        else if ((pCurrent->m_nValue) < value)
        {
            addBSTreeNode(pCurrent->m_pRight, value);
        }
        else
        {
            //cout<<"重复加入节点"<<endl;
        }
    }
}

// 遍历二元查找树  中序
void ergodicBSTree(BSTreeNode * pCurrent)
{
    if (NULL == pCurrent)
    {       
        return;
    }
    if (NULL != pCurrent->m_pLeft)
    {
        ergodicBSTree(pCurrent->m_pLeft);   
    }

    // 节点接到链表尾部
    convertToDoubleList(pCurrent);
    // 右子树为空
    if (NULL != pCurrent->m_pRight)
    {
        ergodicBSTree(pCurrent->m_pRight);
    }
}

// 二叉树转换成list
void  convertToDoubleList(BSTreeNode * pCurrent)
{

    pCurrent->m_pLeft = pListIndex;
    if (NULL != pListIndex)
    {
        pListIndex->m_pRight = pCurrent;
    }
    else
    {
        pHead = pCurrent;
    }   
    pListIndex = pCurrent;
    cout<<pCurrent->m_nValue<<endl;
}

int main()
{
    BSTreeNode * pRoot = NULL;
    pListIndex = NULL;
    pHead = NULL;
    addBSTreeNode(pRoot, 10);
    addBSTreeNode(pRoot, 4);
    addBSTreeNode(pRoot, 6);
    addBSTreeNode(pRoot, 8);
    addBSTreeNode(pRoot, 12);
    addBSTreeNode(pRoot, 14);
    addBSTreeNode(pRoot, 15);
    addBSTreeNode(pRoot, 16);
    ergodicBSTree(pRoot);
    return 0;
}