```cpp
//
// Created by dyf on 19-5-11.
//
/*
 * 介绍一种时间复杂度为O(N) 额外空间复杂度为O(1)的二叉树的遍历方式，N为二叉树的节点个数
 *
 * 普通算法：
 * 为了从下级回到上级要有一个堆栈用来存储返回上级的信息  所以一般情况下空间复杂度为O(高度)
 *
 * Morris算法
 * 1）如果cur无左孩子 cur向右移动cur=cur->right
 * 2) 如果cur有左孩子 找到cur左子数上最右的节点，记为mostright：
 *          如果mostright的右指针为空,让其指向cur cur向左移动 cur=cur->left
 *          如果mostright的右指针指向cur 让其指向空 cur想右移动 cur=cur->right
 *
 *
 * 如果一个树有左子树  会到达该节点2次  没有左子树 会达到该节点1次 可以说两次重合
 * 第一次到达 前序遍历
 *
 * 递归排序是所有的节点都访问3次 选择第一次到达该节点时进行打印 前序遍历 第二次 中序遍历  第三次 后序遍历
 *
 * */
#include<iostream>
#include<math.h>
#include<vector>
#include<algorithm>
#include<queue>
 
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode*right;
    TreeNode(int x) :val(x), left(NULL), right(NULL) {}
};
 
class Solution {
public:
    void morrisIn(TreeNode*head){
        if(head==NULL)
            return;
        TreeNode*cur=head;
        TreeNode*mostRight=NULL;
        while(cur!=NULL){
            mostRight=cur->left;
            if(mostRight!=NULL){//如果有左子树执行
                while(mostRight->right!=NULL&&mostRight->right!=cur){
                    mostRight=mostRight->right;
                }
                if(mostRight->right==NULL){
                    mostRight->right=cur;
                    cur=cur->left;
                    continue;//相当于是cur将会有第二次访问的机会，所以这次不打印 并且左子树没有访问完 继续往下执行
                }else
                {
                    mostRight->right=NULL;
                }
            }
            std::cout<<cur->val<<" ";
            cur=cur->right;
        }
        std::cout<<std::endl;
    }
 
    void morrisPre(TreeNode*head){
        if(head==NULL)
            return;
        TreeNode*cur=head;
        TreeNode*mostRight=NULL;
        while(cur!=NULL){
            mostRight=cur->left;
            if(mostRight!=NULL){//如果有左子树执行
                while(mostRight->right!=NULL&&mostRight->right!=cur){
                    mostRight=mostRight->right;
                }
                if(mostRight->right==NULL){
                    mostRight->right=cur;
                    std::cout<<cur->val<<" ";
                    cur=cur->left;
                    continue;//相当于是cur将会有第二次访问的机会，所以这次不打印 并且左子树没有访问完 继续往下执行
                }else
                {
                    mostRight->right=NULL;
                }
            }else
                std::cout<<cur->val<<" ";
            cur=cur->right;
        }
        std::cout<<std::endl;
    }
 
    void morrisMid(TreeNode*head){
        if(head==NULL)
            return;
        TreeNode*cur=head;
        TreeNode*mostRight=NULL;
        while(cur!=NULL){
            mostRight=cur->left;
            if(mostRight!=NULL){//如果有左子树执行
                while(mostRight->right!=NULL&&mostRight->right!=cur){
                    mostRight=mostRight->right;
                }
                if(mostRight->right==NULL){
                    mostRight->right=cur;
                    cur=cur->left;
                    continue;//相当于是cur将会有第二次访问的机会，所以这次不打印 并且左子树没有访问完 继续往下执行
                }else
                {
                    mostRight->right=NULL;
                }
            }
            std::cout<<cur->val<<" ";
            cur=cur->right;
        }
        std::cout<<std::endl;
    }
 
 
    /*
     * 只关注能够访问两次的节点，当第二次访问时 逆序打印该节点的左子树的右边界 最后逆序打印整个树的右边界
     * */
    void morrisPos(TreeNode*head){
        if(head==NULL)
            return;
        TreeNode*cur=head;
        TreeNode*mostRight=NULL;
        while(cur!=NULL){
            mostRight=cur->left;
            if(mostRight!=NULL){//如果有左子树执行
                while(mostRight->right!=NULL&&mostRight->right!=cur){
                    mostRight=mostRight->right;
                }
                if(mostRight->right==NULL){
                    mostRight->right=cur;
                    cur=cur->left;
                    continue;//相当于是cur将会有第二次访问的机会，所以这次不打印 并且左子树没有访问完 继续往下执行
                }else
                {
                    mostRight->right=NULL;
                    printEdge(cur->left);
                }
            }
            //std::cout<<cur->val<<" ";
            cur=cur->right;
        }
        printEdge(head);
        std::cout<<std::endl;
    }
 
    void printEdge(TreeNode*root){
        root=rightReverse(root);//逆
        printTree(root);
        root=rightReverse(root);//反逆
    }
 
    void printTree(TreeNode*root){
        TreeNode *pre=root;
        while(pre!=NULL){
            std::cout<<pre->val<<" ";
            pre=pre->right;
        }
 
    }
 
    //左子树右边界的逆
    TreeNode* rightReverse(TreeNode*root){
        TreeNode*cur=root->right;
        TreeNode*pre=root;
        pre->right=NULL;
        while(cur!=NULL){
            TreeNode*tmp=cur;
            cur=cur->right;
            tmp->right=pre;
            pre=tmp;
        }
        return pre;
    }
};
```
