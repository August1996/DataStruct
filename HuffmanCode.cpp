//
//  main.cpp
//  HuffmanCode
//
//  Created by 余彬 on 16/9/11.
//  Copyright © 2016年 余彬. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

class TableNode{
public:
    char *data;
    int weight;
    string code;
};

class TreeNode {
public:
    TreeNode();
    TreeNode(char *data,int weight);
    char *data;
    int weight;
    TreeNode *lChild;
    TreeNode *rChild;
};

TreeNode::TreeNode(){
    this->data = NULL;
    this->lChild = NULL;
    this->rChild = NULL;
}

TreeNode::TreeNode(char *data,int weight){
    this->data = data;
    this->weight = weight;
    this->lChild = NULL;
    this->rChild = NULL;
}

class Huffman{
public:
    Huffman(const char *data,int n);
    string encode(string str);
    string decode(string code);
private:
    void buildTree();   //生成哈夫曼树
    void buildTable();  //生成哈夫曼编码
    void traverse(TreeNode *treeNode,string *code,int &tableTop); //遍历哈夫曼树生成code
    
    TreeNode *tree;   //哈夫曼树
    TreeNode *pRoot;  //哈夫曼树顶点
    TableNode *table; //哈夫曼编码表
    int length; //有效数据长度
    int totalLength;    //哈夫曼顶点个数
};


//初始化哈夫曼类
Huffman::Huffman(const char *data,int n){
    
    //统计每种字符出现的次数
    int statics[256];
    
    for(int i = 0;i < 256;i++){
        statics[i] = 0;
    }
    
   
    
    int totalCharCount = 0; //一共有多少种字符
    for(int i = 0;i < n;i++){
        if(statics[data[i]] == 0){
            totalCharCount++;
        }
        statics[data[i]]++;
    }
    
    //初始化类的一些属性
    this->length = totalCharCount;
    this->totalLength = 2 * this->length - 1;
    this->tree = new TreeNode[this->totalLength];
    
    int cntCharCount = 0;   //当前生成TreeNode的个数
    int top = 0;    //存放哈夫曼树的数组顶部
    for(int i = 0;i < 256;i++){
        if(statics[i] != 0){
            char *data = new char;
            *data = (char)i;
            TreeNode treeNode(data,statics[i]);
            this->tree[top++] = treeNode;
            cntCharCount++;
            
            if(cntCharCount == totalCharCount){
                break;
            }
            //可加可不加，加了性能好一点。
            //不加就需要遍历256次。
            
        }
        
    }
    
    this->buildTree();  //创建哈夫曼树
    this->buildTable(); //创建哈夫曼编码表
}

//建立哈夫曼树
void Huffman::buildTree(){
    bool *isCombinded = new bool[this->totalLength];
    //标记某个节点是否已经被合并过，已经被合并过则不进行最小值与次小值筛选
    
    for(int i = 0;i < this->totalLength;i++){
        isCombinded[i] = false;
    }
    
    int minIndex = 0;   //最小值的下标
    int secMinIndex = 1;    //次小值的下标
    
    int top = this->length; //存放哈夫曼树的数组的顶部位置（当前长度）
    while(top < this->totalLength){
        minIndex = -1;
        for(int i = 0;i < top;i++){
            if(!isCombinded[i]){
                if(minIndex == -1){
                    minIndex = i;
                }else{
                    secMinIndex = i;
                }
            }
        }
        
        for(int j = 1;j < top;j++){
            if(isCombinded[j]){
                continue;
            }
            //如果已经合并过的节点，则不参与筛选
            
            //找出最小的两个节点下标
            TreeNode minNode = this->tree[minIndex];
            TreeNode secMinNode = this->tree[secMinIndex];
            TreeNode cntNode = this->tree[j];
            
            if(cntNode.weight < minNode.weight){
                secMinIndex = minIndex;
                minIndex = j;
            }else if(cntNode.weight < secMinNode.weight && j != minIndex){
                secMinIndex = j;
            }
        }
        //合并最小的两个节点
        TreeNode *pMinNode = &this->tree[minIndex];
        TreeNode *pSecMinNode = &this->tree[secMinIndex];
        TreeNode *pNewNode = &this->tree[top++];
        
        pNewNode->weight = pMinNode->weight + pSecMinNode->weight;
        pNewNode->lChild = pMinNode;
        pNewNode->rChild = pSecMinNode;
        
        if(top == this->totalLength){
            this->pRoot = pNewNode;
        }
        
        //设置下面两个下标为已经合并过
        isCombinded[minIndex] = true;
        isCombinded[secMinIndex] = true;
        
    }
}

void Huffman::traverse(TreeNode *treeNode, string *code,int &tableTop){
    
    bool isAdd = false; //判断当前的code是否已经被记录，防止重复写入哈夫曼表码表
    
    if(treeNode->lChild != NULL){
        code->append("0");
        this->traverse(treeNode->lChild,code,tableTop);
        code->pop_back();
        //因为每次递归code都会添加一个字符，所以每次递归函数执行完则恢复状态，弹出那个字符
    }else{
        isAdd = true;
        this->table[tableTop].data = treeNode->data;
        this->table[tableTop].weight = treeNode->weight;
        this->table[tableTop++].code = *new string(code->data());
    }
    
    if(treeNode->rChild != NULL){
        code->append("1");
        this->traverse(treeNode->rChild,code,tableTop);
        code->pop_back();
    }else if(!isAdd){
        this->table[tableTop].data = treeNode->data;
        this->table[tableTop].weight = treeNode->weight;
        this->table[tableTop++].code = *new string(code->data());
    }
}

//建立哈夫曼编码表
void Huffman::buildTable(){
    string code;
    int tableTop = 0;
    this->table = new TableNode[length];
    this->traverse(this->pRoot,&code,tableTop);
}

//编码，拆分str，每个字符对应一个哈夫曼编码。查找哈夫曼编码表来确定哈夫曼表码。
string Huffman::encode(string str){
    string code;
    for(int i = 0;i < str.length();i++){
        for(int j = 0;j < this->length;j++){
            TableNode *tableNode = &this->table[j];
            const char *strData = str.c_str();
            const char *tableData = tableNode->data;
            if(strData[i] == tableData[0]){
                code.append(tableNode->code);
                break;
            }
        }
    }
    return code;
}

//解码，根据哈夫曼编码去遍历哈夫曼树，0往左走，1往右走。
string Huffman::decode(string code){
    string decode;
    TreeNode *pNode = this->pRoot;
    for(int i = 0;i <= code.length();i++){
        if(pNode->data == NULL){
            char c = code.c_str()[i];
            if(c == '0'){
                pNode = pNode->lChild;
            }else if(c == '1'){
                pNode = pNode->rChild;
            }
        }else{
            decode.append(pNode->data);
            pNode = this->pRoot;
            i--;
        }
        
    }
    
    return decode;
}



int main(int argc, const char * argv[]) {
    
    
    string str = "ABCDEFGABCDE";
    Huffman huffman(str.c_str(),(int)str.length());
    string code = huffman.encode("BBACE");
    cout<<code<<endl;
    
    string decode = huffman.decode(code);
    cout<<decode<<endl;
    return 0;
}
