#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXLINE 1000
char HuffmanCode[128][MAXLINE] ;

/*题目分析
步骤 ： 首先，需要对读入进行处理。(两种正确命令，处理错误命令)
        压缩和解压
*/
struct Node{
    char chr ; 
    int times ;
    struct Node *left , *right ;
} ;
typedef struct Node Node ;
Node* initNode(char chr , int times) ;
void freeTree(Node* root) ;
void bubbleSort(Node** array , int n) ;
void insertSort(Node** array , int n) ;
Node* insert(Node* root , char* str , char c) ;
void zip(char* filename) ;
int* readFile(FILE* file) ;
Node* createHuffmanTree(int* wordTable) ;
void createHuffmanCode(Node* root) ;
void preorder(Node* root , char** str , int h) ;
void createHzipfile(FILE* fin , FILE* fout) ;
void unzip(char *filename) ;
int readCommand(char** filename , int argc, char *argv[]) ;
int isChr(char c) ;
int main(int argc, char *argv[])
{
    
    char* filename = 0 ;
    int command = readCommand(&filename , argc, argv) ;
    
    /*
    int command = 2 ;
    char filename[12] ; 
    strcpy(filename , "myfile.hzip") ;
    */
    
    
    if(command == 1) zip(filename) ;
    else if(command == 2) unzip(filename) ;
    else ;

    return 0 ;
}

/*两种错误
1. 完全错误
2. 扩展名错误
*/
int readCommand(char **filename, int argc, char *argv[]) {
    if (argc < 2 || argc > 3) {
        printf("Usage: hzip.exe [-u] <filename>\n");
        return -1;
    }

    int mode = 1; // 默认压缩
    const char *filearg = NULL;

    if (argc == 2) {
        filearg = argv[1]; // 直接取文件名
    } else if (argc == 3) {
        if (strcmp(argv[1], "-u") != 0) {
            printf("Usage: hzip.exe [-u] <filename>\n");
            return -1;
        }
        mode = 2; // 解压模式
        filearg = argv[2];
    }

    // 校验扩展名
    const char *ext = strrchr(filearg, '.');
    if (!ext) {
        printf("File extension error!\n");
        return -1;
    }

    if ((mode == 1 && strcmp(ext, ".txt") != 0) ||
        (mode == 2 && strcmp(ext, ".hzip") != 0)) {
        printf("File extension error!\n");
        return -1;
    }

    // 拷贝文件名
    *filename = (char*)malloc(strlen(filearg) + 1);
    if (!*filename) {
        perror("malloc failed");
        return -1;
    }
    strcpy(*filename, filearg);

    return mode; // 1 = 压缩，2 = 解压
}
int isChr(char c)
{
    return (c <= 'z' && c >= 'a') || (c <= 'Z' && c >= 'A') ;
}
Node* initNode(char chr , int times)
{
    Node* node = (Node*)malloc(sizeof(Node)) ;
    node -> chr = chr ;
    node -> times = times ;
    node -> right = node -> left = NULL ;

    return node ;
}
void bubbleSort(Node** array , int n) 
{
    for(int i = n - 1 ; i > 0 ; --i)
        for(int j = 0 ; j < i ; j++)
        {
            if((array[j] -> times < array[j + 1] -> times) ||
                ((array[j] -> times == array[j + 1] -> times) && (array[j] -> chr < array[j + 1] -> chr)))
            {
                Node* tmp = array[j] ;
                array[j] = array[j + 1] ;
                array[j + 1] = tmp ;
            }
        }
}
void insertSort(Node** array , int n)
{
    Node* target = array[n - 1] ;
    int i = n - 2 ;
    for(; i >= 0 ; i--)
    {
        if(target -> times >= array[i] -> times) 
        {
            array[i + 1] = array[i] ;
        }
        else break ;
    }
    array[i + 1] = target ;
}
void preorder(Node* root , char** str , int h) 
{
    if(!root) return ;
    if(!root -> left && !root -> right) {strcpy(HuffmanCode[root -> chr] , *str) ; return ;}
    (*str)[h] = '0' ;
    preorder(root -> left , str , h + 1) ;
    (*str)[h] = '1' ;
    preorder(root -> right , str , h + 1) ;
    (*str)[h] = 0 ;
}
void freeTree(Node* root)
{
    if(!root) return ;

    freeTree(root -> left) ;
    freeTree(root -> right) ;
    free(root) ;
}
/*压缩
1.读取输入文件并统计词频（结束符为0，词频为1）
2.生成huffman树
3.生成压缩文件
*/
void zip(char* filename)
{
    
    FILE* fin = fopen(filename , "r") ;
    // from filename.txt to filename.hzip
    int len = strlen(filename) ;
    char* output = (char*)malloc(sizeof(char) * (len + 2)) ;
    memset(output , 0 , sizeof(char) * (len + 2)) ;
    char* ptr1 = filename , *ptr2 = output ;
    while(*ptr1 != '.')
    {
        *ptr2 = *ptr1 ;
        ptr1 ++ ;
        ptr2 ++ ;
    }
    strcpy(ptr2 , ".hzip") ;
    FILE* fout = fopen(output , "w") ;
    int* ChrTable = readFile(fin) ;   //根据读入文件生成词频表。
    Node* root = createHuffmanTree(ChrTable) ;  
    createHuffmanCode(root) ;
    rewind(fin) ;
    createHzipfile(fin , fout) ;
    fclose(fin);
    fclose(fout) ;
}
int* readFile(FILE* file)
{
    char c = 0 ;
    int* table = (int* )malloc(sizeof(int) * 130) ;
    memset(table , 0 , sizeof(int) * 130) ;
    while(1)
    {
        c = fgetc(file) ;
        if(c == EOF) c = 0 ;
        table[c]++ ;
        if(c == 0) break ;
    }

    return table ;
}
Node* createHuffmanTree(int* wordTable)
{
    //将未出现的字符剔除 ， 设置Node* 栈
    Node** stack = (Node** )malloc(sizeof(Node*) * MAXLINE) ;
    memset(stack , 0 , sizeof(Node*) * 130) ;
    int top = 0 ;
    for(int i = 0 ; i < 128 ; ++i)
    {
        if(wordTable[i] != 0) stack[top++] = initNode(i , wordTable[i]) ;
    }
    free(wordTable) ;
    bubbleSort(stack , top) ;
    while(top > 1)
    {
        Node* node = initNode(0 , stack[top - 1] -> times + stack[top - 2] -> times) ;
        node -> left = stack[top - 1] ; 
        node -> right = stack[top - 2] ;
        top -= 2 ;
        stack[top++] = node ;
        insertSort(stack , top) ;
    }
    return stack[0] ;
}
void createHuffmanCode(Node* root)
{
    //前序遍历生成
    char* str = (char* )malloc(sizeof(char) * MAXLINE) ;
    memset(str , 0 , sizeof(char) * MAXLINE) ;
    preorder(root , &str , 0) ;

    free(str) ;
    freeTree(root) ;
}
void createHzipfile(FILE* fin , FILE* fout)
{
    fseek(fin , 0 , SEEK_SET) ;
    int num = 0 ;
    for(int i = 0 ; i < 128 ; ++i)
    {
        if(strlen(HuffmanCode[i])) num++ ;
    }
    unsigned char *pc , hc = 0 ;
    int i = 0 ;
    // 输出num 
    hc = num ;
    fputc(hc , fout) ;
    hc = 0 ;
    for(int j = 0 ; j < 128 ; ++j)
    {
        int len = strlen(HuffmanCode[j]) ;
        if(!len) continue ;
        hc = j ;
        fputc(hc , fout) ;
        hc = len ;
        fputc(hc , fout) ;
        pc = (unsigned char*)HuffmanCode[j] ;
        hc = 0 ;
        for(; *pc != '\0' ; pc++)
        {
            hc = (hc << 1) | (*pc - '0' );
            i++ ;
            if(i == 8) {fputc(hc , fout) ; i = 0 ;}
        }
        if(i != 0){
            hc = hc << (8 - i) ;
            fputc(hc , fout) ;
        }
        hc = 0 ; i = 0 ;
    }
    int c ;
    do{
        c = fgetc(fin) ;
        if(c == EOF) c = 0 ;

        for(pc = (unsigned char*)HuffmanCode[c] ; *pc != '\0' ; pc++)
        {
            hc = (hc << 1) | (*pc - '0') ;
            i++ ;
            if(i == 8) {fputc(hc , fout) ; i = 0 ;}
        }
        if(c == 0 && i != 0)
        {
            hc = hc << (8 - i) ;
            fputc(hc , fout) ;
            hc = 0 ; i = 0 ;
        }
    }while(c) ;
}
void unzip(char* filename)
{
    FILE* fin = fopen(filename , "r") ;
    // from filename.hzip to filename.txt
    int len = strlen(filename) ;
    char* output = (char*)malloc(sizeof(char) * (len )) ;
    memset(output , 0 , sizeof(char) * (len )) ;
    char* ptr1 = filename , *ptr2 = output ;
    while(*ptr1 != '.')
    {
        *ptr2 = *ptr1 ;
        ptr1 ++ ;
        ptr2 ++ ;
    }
    strcpy(ptr2 , ".txt") ;
    FILE* fout = fopen(output , "w") ;
    //生成HuffmanCode
    fseek(fin , 0 , SEEK_SET) ;
    int num = fgetc(fin) ;
    for(int i = 0 ; i < num ; i++)
    {
        unsigned char hc = fgetc(fin) ;
        int len = fgetc(fin) ; 
        unsigned char ans ;
        for(int i = 0 ; i < (int)len ; i++)
        {
            if(i % 8 == 0) ans = fgetc(fin) ;
            HuffmanCode[(int)hc][i] =( (ans >> (7 - (i % 8))) & 1 ) + '0' ;
        }
    }
    //处理HuffmanCode
    Node* root = NULL ;
    for(int i = 0 ; i < 128 ; ++i)
    {
        if(HuffmanCode[i][0] != 0){
            root = insert(root , HuffmanCode[i] , i) ;
        }
    }
    //转换hzip
    int i = 0 ;
    Node* ptr = root ;
    unsigned char hc = fgetc(fin);
    do{
        char c = ((hc >> (7 - i)) & 1) ;
        i++ ;
        if(c == 1) ptr = ptr -> right ;
        else ptr = ptr -> left ;
        if(!ptr -> left && !ptr -> right){
            fprintf(fout , "%c" , ptr -> chr) ;
            if(ptr -> chr == 0) goto ret ;
            ptr = root ;
        }

        if(i % 8 == 0) {hc = fgetc(fin) ; i = 0 ;}
    }while(1) ;
    ret : ;
    fclose(fin) ;
    fclose(fout) ;
} 
Node* insert(Node* root0 , char* str , char c) 
{
    if(!root0) root0 = initNode(0 , 0) ;
    Node* root = root0 ;
    int len = strlen(str) ;
    for(int i = 0 ; i < len ; ++i) 
    {
        if(str[i] == '0') {
            if(root -> left == NULL) root -> left = initNode(0 , 0) ;
            root = root -> left ;
        }
        else {
            if(root -> right == NULL) root -> right = initNode(0 , 0) ;
            root = root -> right ;
        }
    }
    root -> chr = c ;

    return root0 ;
}