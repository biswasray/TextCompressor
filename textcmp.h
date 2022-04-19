#include<stdio.h>
#include<stdlib.h>
#define MAX_TREE_HT 200
static char charmap[256][256];
struct MinHeapNode {
    char data;
    unsigned freq;
    struct MinHeapNode *left, *right;
};

struct MinHeap {
    unsigned size;
    unsigned capacity;
    struct MinHeapNode** array;
};
struct MinHeapNode* newNode(char data, unsigned freq)
{
    struct MinHeapNode* temp = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}
struct MinHeap* createMinHeap(unsigned capacity) {
  
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}
void swapMinHeapNode(struct MinHeapNode** a,struct MinHeapNode** b) {
  
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct MinHeap* minHeap, int idx) {
  
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
  
    if (left < minHeap->size
        && minHeap->array[left]->freq
               < minHeap->array[smallest]->freq)
        smallest = left;
  
    if (right < minHeap->size
        && minHeap->array[right]->freq
               < minHeap->array[smallest]->freq)
        smallest = right;
  
    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[smallest],
                        &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}
int isSizeOne(struct MinHeap* minHeap)
{
  
    return (minHeap->size == 1);
}
struct MinHeapNode* extractMin(struct MinHeap* minHeap)
  
{
  
    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
  
    --minHeap->size;
    minHeapify(minHeap, 0);
  
    return temp;
}
void insertMinHeap(struct MinHeap* minHeap,struct MinHeapNode* minHeapNode) {
  
    ++minHeap->size;
    int i = minHeap->size - 1;
  
    while (i
           && minHeapNode->freq
                  < minHeap->array[(i - 1) / 2]->freq) {
  
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
  
    minHeap->array[i] = minHeapNode;
}
void buildMinHeap(struct MinHeap* minHeap)
  
{
  
    int n = minHeap->size - 1;
    int i;
  
    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}
void printArr(int arr[], int n,int c)
{
    int i;
    for (i = 0; i < n; ++i) {
        sprintf(charmap[c]+i,"%d", arr[i]);
        //printf("%d", arr[i]);
    }
    //printf("\n");
}
int isLeaf(struct MinHeapNode* root) {
  
    return !(root->left) && !(root->right);
}
struct MinHeap* createAndBuildMinHeap(char data[],int freq[], int size) {
  
    struct MinHeap* minHeap = createMinHeap(size);
  
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);
  
    minHeap->size = size;
    buildMinHeap(minHeap);
  
    return minHeap;
}
struct MinHeapNode* buildHuffmanTree(char data[],int freq[], int size) {
    struct MinHeapNode *left, *right, *top;
    struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);
    while (!isSizeOne(minHeap)) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);
        top = newNode('$', left->freq + right->freq);
  
        top->left = left;
        top->right = right;
  
        insertMinHeap(minHeap, top);
    }
    return extractMin(minHeap);
}
void printCodes(struct MinHeapNode* root, int arr[],int top) {
    if (root->left) {
  
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }
    if (root->right) {
  
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }
    if (isLeaf(root)) {
  
        //printf("%c: ", root->data);
        printArr(arr, top,(int)root->data);
    }
}
void HuffmanCodes(char data[], int freq[], int size)
  
{
    struct MinHeapNode* root = buildHuffmanTree(data, freq, size);
    int arr[MAX_TREE_HT], top = 0;
  
    printCodes(root, arr, top);
}


char* getStringFromFile(char* filename) {
    FILE *file=fopen(filename,"r");
    if(file==NULL) {
        printf("File note Found !!!\n");
        return NULL;
    }
    int size=256*sizeof(char);
    char *str=(char*)malloc(size);
    int i=0;
    char c;
    do {
        c=(char)getc(file);
        str[i++]=c;
        if(i>=size) {
            size+=256*sizeof(char);
            str=(char*)realloc(str,size);
        }
    }while(c!=EOF);
    fclose(file);
    str[i]='\0';
    return str;
}
char* getBitsFromFile(char* filename) {
    FILE *file=fopen(filename,"rb");
    if(file==NULL) {
        printf("File note Found !!!\n");
        return NULL;
    }
    int size=256*sizeof(char);
    char *str=(char*)malloc(size);
    int index=0;
    char ch,c;
    do {
        ch=(char)getc(file);
        c=ch;
        char t[8];
        for(int i=7;i>=0;i--) {
            t[i]='0'+(c&1);
            c=c>>1;
        }
        
        for(int i=0;i<8;i++) {
            str[index++]=t[i];
            if(index>=size) {
                size+=256*sizeof(char);
                str=(char*)realloc(str,size);
            }
        }
    }while(ch!=EOF);
    fclose(file);
    str[index]='\0';
    return str;
}

char streamOfBitsToChar(char *str) {
    int res=0,i;
    for(i=0;str[i]!=0;i++)
        res=(res<<1)+(str[i]-'0');
    return (char)res;
}

char stringTo8BitStream(char *str) {
    char ch=0;
    int i;
    for(i=0;i<8;i++) {
        ch=(ch<<1)+(str[i]-'0');
    }
    return ch;
}
int lengthOfString(char *str) {
    int i,n=0;
    for(i=0;str[i]!=0;i++)
        n++;
    return 0;
}

char* streamOfBitsToString(char *str,int n) {
    int i;
    char *res=(char*)malloc((n/8)+1);
    for(i=0;i<(n/8)+1;i++)
        res[i]=0;
    for(i=0;str[i]!=0;i++)
        res[i/8]=(res[i/8]<<1)+(str[i]-'0');
    int s=8*((i/8)+1);
    for(;i<s;i++)
        res[i/8]=res[i/8]<<1;
    return res;
}

// void writeTableInFile(FILE *file,char arr[],int n) {
//     for(int i=0;i<n;i++) {
//         putc(arr[i],file);
//         putc(-2,file);
//         putc(charmap[(int)arr[i]],file);
//     }
//     putc(-3,file);
// }
void writeStreamInFile(FILE *file,char arr[],int n) {
    
}

char* tableToStream(int arr[],int n) {
    char* res=(char*)malloc(3*n*sizeof(char)+sizeof(char));
    res[0]=(char)n;
    int i,j=1;
    for(i=0;i<n;i++) {
        res[j++]=(char)arr[i];
        res[j++]=stringTo8BitStream(charmap[(int)arr[i]]);
        res[j++]=lengthOfString(charmap[(int)arr[i]]);
    }
    res[j++]=-1;
    return res;
}

void engine(char* filename) {
    char *str=getStringFromFile(filename);
    int i,n=0;
    static char freq[256];
    for(i=0;str[i]!=0;i++) {
        if(freq[(int)str[i]]==0)
            n++;
        freq[(int)str[i]]++;
    }
    char arr[n];
    int f[n];
    int j=0;
    for(i=0;i<256;i++) {
        if(freq[i]>0) {
            arr[j]=(char)i;
            //printf("")
            f[j++]=freq[i];
        }
    }
    HuffmanCodes(arr,f,n);
    for(i=0;i<n;i++) {
        printf("%d : %s\n",arr[i],charmap[(int)arr[i]]);
    }
}