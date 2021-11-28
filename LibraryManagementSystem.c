#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
 
 //==========
#define true 1
#define false 0
#define boolean int
#define Key int
#define Value int
#define RED 1
#define BLACK 0
#define null NULL

#define QUEUE_MAXSIZE	10000	//��󳤶� 
#define ok 1
#define ElemType int

typedef struct{
	ElemType *base;
	int front;
	int rear;
}sqQueue, *Queue;

Queue createQueue();
boolean enQueue(Queue queue, ElemType data);
ElemType deQueue(Queue queue);
//==============
 
 
 
 //ͼ���š����������ߡ������硢�������ڡ�ISBN����Ρ����۵�
typedef struct Node{
	// ͼ���� 
	int key;
	// ���� 
	char name[30];
	// ���� 
	char author[30];
	// ������ 
	char press[30];
	// ��¼���ӽ��
    struct Node* left;
    // ��¼���ӽ��
    struct Node* right;
    // ��¼�����
    struct Node* parent;
	boolean color;
}Node, *NodeTree;
 
 
 
 //==========================
 void put_book();
 void put(NodeTree h, NodeTree newNode);
 void createTree();
 NodeTree new_Node(NodeTree h, NodeTree parent);
 void fixAfterRemove(NodeTree x);
 void fixAfterPut(NodeTree x);
 void print(NodeTree h);
 NodeTree get(NodeTree h, Key key);
 void find_number_book();
 void over();
 void print_book();
 void xianshi(NodeTree h);
 void menu();
 void Remove();
 void amend(Key key);
 //==========================
 
 //==========================
 NodeTree root;
 int nodeNumber = 0;
 //==========================
 
 
//==========================
void HideCursor()     //���ع��
{
 CONSOLE_CURSOR_INFO cursor_info = {1, 0}; 
 SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
 
void color(short x)
{
	if(x>=0&&x<=15)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),x);
	}
	else
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),x);
	}
} 
 
void toxy(int x, int y)      //������ƶ���X,Y���괦
{
COORD pos = { x , y };
HANDLE Out = GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleCursorPosition(Out, pos); 
}

//==========================
 
 




//==========================
/*
* ������������� 
*/ 
void createTree() {
	do{
    	system("cls");
		color(10);
		char t;
		root = (NodeTree)malloc(sizeof(Node));
		//����ͼ����Ϣ
		toxy(48,8);
		printf("������ͼ����(С��10λ��)��");    
		scanf("%d", &(root->key));getchar();
		toxy(48,10);
		printf("����������(С��10λ��)��");
		scanf("%s", &(root->name));getchar();
		toxy(48,12);
		printf("������������(С��10λ��)��");
		scanf("%s", &(root->author));getchar();
		toxy(48,14);
		printf("������ͼ�������(С��10λ��)��");
		scanf("%s", &(root->press));getchar();
		toxy(48,16);
		nodeNumber++;
		printf("���ڱ���....");
    	root->color = BLACK;
	    root->left = null;
	    root->right = null;
	    root->parent = null;
	    toxy(46,8);
		printf("-------------------------");
		toxy(46,9);
		printf("|                       |");
		toxy(46,10);
		printf("| ����ɹ����Ƿ������  |");
		toxy(46,12);
		printf("| 1.��             2.�� |");
		toxy(46,13);
		printf("|                       |");
		toxy(46,14);
		printf("-------------------------");
		while(1)    //������ѭ������Ч��ֹ������������ 
		{
			t=getch();
			if(t=='1')
			{
				put_book(); 
			 } 
			 else if(t=='2')
			 {
			 	menu();
			 }
		}
	}while(1);
}



// ͼ���š����������ߡ�������
void put_book() {
	do
	{
		system("cls");
		color(10);
		char t;
		NodeTree newNode = (Node*)malloc(sizeof(Node));
		//����ͼ����Ϣ
		toxy(48,8);
		printf("������ͼ����(С��10λ��)��");    
		scanf("%d", &(newNode->key));getchar();
		toxy(48,10);
		printf("����������(С��10λ��)��");
		scanf("%s", &(newNode->name));getchar();
		toxy(48,12);
		printf("������������(С��10λ��)��");
		scanf("%s", &(newNode->author));getchar();
		toxy(48,14);
		printf("������ͼ�������(С��10λ��)��");
		scanf("%s", &(newNode->press));getchar();
		toxy(48,16);
		printf("���ڱ���....");
		newNode->color = BLACK;
	    newNode->left = null;
	    newNode->right = null;
	    newNode->parent = null;
		put(root, newNode);
		Sleep(500);   //��ͣ0.5�� 
//		system("cls");
		toxy(46,8);
		printf("-------------------------");
		toxy(46,9);
		printf("|                       |");
		toxy(46,10);
		printf("| ����ɹ����Ƿ������  |");
		toxy(46,12);
		printf("| 1.��             2.�� |");
		toxy(46,13);
		printf("|                       |");
		toxy(46,14);
		printf("-------------------------");
		while(1)    //������ѭ������Ч��ֹ������������ 
		{
			t=getch();
			if(t=='1')
			{
				break;
			 } 
			 else if(t=='2')
			 {
			 	menu();
			 }
		}
	}while(1);
	
}


void createAndIn() {
	if(root == null) {
		createTree();
	} else {
		put_book();
	}
}

//==========================
/*
* ������� 
*  
*/ 
void exchange(NodeTree h, NodeTree newNode) {
	h->key = newNode->key;
	strcpy(h->author, newNode->author);
	strcpy(h->name, newNode->name);
	strcpy(h->press, newNode->press);
}


// ������������ɲ������
void put(NodeTree h, NodeTree newNode) {
    NodeTree parent;
    int cmp;
    // ���Ÿ����Ѱ�Ҳ���λ��
    do {
        parent = h;
        cmp = newNode->key-h->key;
        if (cmp < 0) {
            h = h->left;
        } else if (cmp > 0) {
            h = h->right;
        } else {
            exchange(h, newNode);
        }
    }while(h != null);

    NodeTree e = new_Node(newNode, parent);
    nodeNumber++;

    if (cmp < 0) {
        parent->left = e;
    } else {
        parent->right = e;
    }

    // ����
    fixAfterPut(e);
}


NodeTree new_Node(NodeTree h, NodeTree parent) {
    NodeTree newNode = (Node*)malloc(sizeof(Node));
    exchange(newNode, h);
    newNode->left = null;
    newNode->right = null;
    newNode->parent = parent;
    newNode->color = BLACK;
    return newNode;
}

// �жϵ�ǰ���ĸ�ָ�������Ƿ�Ϊ��ɫ
boolean isRed(NodeTree N) {
    if (N==null){
        return false;
    }

    return N->color==RED;
}

/*
        h                   pr(x)
      / \                   / \ 
     pl  pr(x)  ==>        h  rr
        /  \             / \ 
       rl  rr           pl rl
*/
// ��������
void rotateLeft(NodeTree h) {
    // 
    if (h != null){
        NodeTree x = h->right;
        h->right = x->left;
        if (x->left != null){
            x->left->parent = h;
        }
        x->parent = h->parent;
        if (h->parent == null) {
            root = x;
        } else if (h->parent->left==h) {
            h->parent->left = x;
        } else {
            h->parent->right = x;
        }
        x->left = h;
        h->parent = x;
    }
}

/*
           h             pl(x)
         / \            / \ 
     pl(x) pr  ==>     rl  h
   /  \                  / \
  rl  rr                rr  pr   
*/
// ��������
void rotateRight(NodeTree h) {
    if (h != null){
        NodeTree x = h->left;
        h->left = x->right;
        if (x->right != null) {
            x->right->parent = h;
        }
        x->parent = h->parent;
        if (h->parent==null) {
            root = h;
        } else if (h->parent->left == h) {
            h->parent->left = x;
        } else {
            h->parent->right = h;
        }
        x->right = h;
        h->parent = x;
    }
}


boolean colorOf(NodeTree node) {
    return node==null?BLACK:(node->color);
}

NodeTree parentOf(NodeTree node) {
    return node!=null?node->parent:null;
}

NodeTree leftOf(NodeTree node) {
    return node!=null?node->left:null;
}

NodeTree rightOf(NodeTree node) {
    return node!=null?node->right:null;
}

void setColor(NodeTree node, boolean color) {
    if (node != null) {
        node->color = color;
    }
}

void fixAfterPut(NodeTree x) {
    x->color = RED;
    // �����Ͼ��Ǹ�����Ǻ�ɫ�Ͳ���Ҫ�����ˣ���Ӧ�������2��3
    while (x->parent != null && x->parent->color == RED) {
        // 1��x�ĸ������үү������
        if (parentOf(x) == leftOf(parentOf(parentOf(x)))) {
            // ������
            NodeTree y = rightOf(parentOf(parentOf(x)));
            // ���������
            if (colorOf(y) == RED) {
                setColor(parentOf(x), BLACK);
                setColor(y, BLACK);
                setColor(parentOf(y), RED);
                // ����ȫ�ָ�Ϊwhileѭ��
                x = parentOf(parentOf(x));
            }

            // �ڶ������
            else {
                /*
                        3
                       /
                      2
                      \
                       2.5
                */
                if (x==rightOf(parentOf(x))){
                    x = parentOf(x);
                    rotateLeft(x);
                }
                // үү���
                setColor(parentOf(parentOf(x)), RED);
                // ���ױ��
                setColor(parentOf(x), BLACK);
                // ����үү�������
                rotateRight(parentOf(parentOf(x)));
            }
        } else {
            // ��3
            // ������
            NodeTree y = leftOf(parentOf(parentOf(x)));
            // ���������
            if (colorOf(y) == RED) {
                setColor(parentOf(x), BLACK);
                setColor(y, BLACK);
                setColor(parentOf(y), RED);
            }

            // �ڶ������
            else {
                /*
                        3
                       /
                      2
                      \
                       2.5
                */
                if (x==leftOf(parentOf(x))){
                    x = parentOf(x);
                    rotateRight(x);
                }
                // үү���
                setColor(parentOf(parentOf(x)), RED);
                // ���ױ��
                setColor(parentOf(x), BLACK);
                // ����үү�������
                rotateLeft(parentOf(parentOf(x)));
            }
        }
    }

    root->color = BLACK;
}

// ����key,�������ҳ���Ӧ��ֵ
NodeTree get(NodeTree h, Key key) {
    if (h == null) {
    	toxy(40, 14);
    	printf("�Բ���δ�ҵ�!...");Sleep(2000);
        menu();
    }
	
    if (key < h->key) {
        return get(h->left, key);
    } else if (key > h->key) {
        return get(h->right, key);
    } else {
        return h;
    }
}

// �ҵ�ָ������ǰ����㣬���ҵ�С��node�������ֵ
NodeTree predecessor(NodeTree node) {
    if (node == null) {
        return null;
    } else if (node->left!=null) {
        NodeTree p = node->left;
        while (p->right!=null) {
            p = p->right;
        }
        return p;
    } else {
        NodeTree p = node->parent;
        NodeTree ch = node;
        while (p != null && p->left == ch) {
            ch = p;
            p = p->parent;
        }
        return p;
    }

    
}

// �Һ�̽ڵ�,������node������Сֵ
NodeTree sucessor(NodeTree node) {
    if (node == null) {
        return null;
    } else if (node->right != null) {
        NodeTree p = node->right;
        while (p->left != null) {
            p = p->left;
        }

    return p;
    } else {
        NodeTree p = node->parent;
        NodeTree ch = node;
        while (p != null && p->right == ch){
            ch = p;
            p = p->parent;
        }
        return p;
    }
}




NodeTree getNode(Key key) {
    NodeTree node = root;
    while(node != null) {
        int cmp = key - node->key;
        if (cmp > 0) {
            node = node->right;
        } else if (cmp < 0) {
            node = node->left;
        } else {
            return node;
        }
    }

    return null;
}

/*
    ɾ��������
    1��ɾ��Ҷ�ӽ�㣬ֱ��ɾ��
    2��ɾ���Ľ����һ���ӽ�㣬��ô���ӽ��������
    3��ɾ���Ľ���������ӽ�㣬��ʱ��Ҫ�ҵ�ǰ�������ߺ�̽��������

*/
void deleteNode(NodeTree node) {
    // 3.node����������Ӻ���
    if (node->left != null && node->right != null) {
        NodeTree sucessorNode = sucessor(node);
        exchange(node, sucessorNode);
        node = sucessorNode;
    }

    NodeTree replacement = node->left!=null?node->left:node->right;
    // 2. �����㲻Ϊ��
    if (replacement != null) {
        // ����ߵĸ�ָ��ָ���ԭ��node�ĸ���
        replacement->parent = node->parent;
        // node�Ǹ��ڵ�
        if (node->parent == null) {
            root = replacement;
        } 
        // node�����ӣ����Դ�������Ȼ������
        else if(node == node->parent->left) {
            node->parent->left = replacement;
        } 
        // node���Һ��ӣ������������Ȼ���Һ���
        else {
            node->parent->right = replacement;
        }

        // �滻��ʱ����Ҫ����ƽ��
        if (node->color == BLACK) {
            //��Ҫ����
             fixAfterRemove(replacement);
        }
        free(node);
    } else if (node->parent == null) {
        // ɾ�������Ǹ��ڵ�
        root = null;
    } 
    // 1��node�����Ҷ�ӽ�㣬replacementΪnull
    else {
        
        // �ȵ���
        if (node->color == BLACK){
            fixAfterRemove(node);
        } 

        // ��ɾ��
        if (node->parent != null) {
            if (node->parent->left == node) {
                node->parent->left = null;
            } else if (node->parent->right == node) {
                node->parent->right = null;
            }
            node->parent = null;
            free(node);
        }
    }
}

NodeTree removeNode(Key key) {

    NodeTree node = getNode(key);
    
    if (node == null) {
        return;
    }
//    NodeTree delNode;
//	exchange(delNode, node);
    deleteNode(node);

//    return delNode;
}

void Remove() {		//ɾ����Ϣ
	do
	{
		system("cls");
		color(9);
		int number;
		char t,c;
		int i = 8;
		
		while(1)
		{
			toxy(45,i);
			printf("��������Ҫɾ����ͼ��ı�ţ�");
			scanf("%d",&number);//getchar();
			Sleep(500);
			toxy(40,8);
			printf("*********************ͼ������************************");
			toxy(40,10);
			printf("-----------------------------------------------------");
			toxy(40,11);
			printf("���          ����          ������           ���浥λ");
			toxy(40,12);
			printf("-----------------------------------------------------");
			toxy(40,14);
			NodeTree getNode = get(root, number);
			printf("%d%14s%14s%14s\n", getNode->key, getNode->name, getNode->author, getNode->press);
			if(!get(root, number))
			{
				toxy(45,++i);
				printf("�����������������!");
				Sleep(500);
			}
			else
			{
				break;
			}
		}
		toxy(40,8);
		printf("*********************ͼ������************************");
		toxy(40,10);
		printf("-----------------------------------------------------");
		toxy(40,11);
		printf("���          ����          ������           ���浥λ");
		toxy(40,12);
		printf("-----------------------------------------------------");
		toxy(40,14);
		NodeTree getNode = get(root, number);
		printf("%d%14s%14s%14s\n", getNode->key, getNode->name, getNode->author, getNode->press);
		
		
		color(7);
		toxy(50,16);
		printf("-------------------------");
		toxy(50,17);
		printf("|                       |");
		toxy(50,18);
		printf("|     �Ƿ�ȷ��ɾ����    |");
		toxy(50,20);
		printf("| 1.��             2.�� |");
		toxy(50,21);
		printf("|                       |");
		toxy(50,22);
		printf("-------------------------");
		while(1)
		{
			t=getch();
			if(t=='1')
			{
				break;
			} 
			else if(t=='2')
			{
				menu();
			}
		}
		system("cls");
		toxy(46,10);
		printf("����ɾ�������Ժ�....");
		removeNode(number);
		Sleep(500);
		system("cls");
		toxy(46,8);
		printf("-------------------------");
		toxy(46,9);
		printf("|                       |");
		toxy(46,10);
		printf("|  ɾ���ɹ����Ƿ������ |");
		toxy(46,12);
		printf("| 1.��             2.�� |");
		toxy(46,13);
		printf("|                       |");
		toxy(46,14);
		printf("-------------------------");
		while(1)
		{
			c=getch();
			if(c=='1')
			{
				break;
			}
			else if(c=='2')
			{
				menu();
			}
		}
	}while(1);	
}

// ɾ�������
void fixAfterRemove(NodeTree x) {
    // ���������
    while (x != root && colorOf(x) == BLACK) {
        // x�����ӵ����
        if (x == leftOf(parentOf(x))) {
            // �ֵܽ��
            NodeTree rnode = rightOf(parentOf(x));

            //�жϴ�ʱ�ֵܽ���Ƿ����������ֵܽ��
            if (colorOf(rnode) == RED) {
                setColor(rnode, BLACK);
                setColor(parentOf(x), RED);
                rotateLeft(parentOf(x));
                // �ҵ��������ֵܽ��
                rnode = rightOf(parentOf(x));
            }
            // ����������ֵܽ裬�ֵ�û�ý�
            // ���ﲢ�����ж�Ϊ��ɫ�������ж��Ƿ�Ϊ��
            if (colorOf(leftOf(rnode)) == BLACK && colorOf(rightOf(rnode)) == BLACK) {
                // �Ƚ���
                setColor(rnode, RED);
                x = parentOf(x);
            }

            // �����,���ֵܽ裬�ֵ��еĽ�
            else {
                // ������С������ֵܽ�㱾����3�������Ľ������
                if (colorOf(rightOf(rnode)) == BLACK) {
                    setColor(rnode, RED);
                    setColor(leftOf(rnode), BLACK);
                    rotateRight(rnode);
                    rnode = rightOf(parentOf(x));
                }
                setColor(rnode, colorOf(parentOf(x)));
                setColor(parentOf(rnode), BLACK);
                setColor(rightOf(rnode), BLACK);
                rotateLeft(parentOf(x));
                // ��ʾѭ������
                x = root;
            }

        }

        // x���Һ��ӵ����
        else {
            // �ֵܽ��
            NodeTree rnode = leftOf(parentOf(x));

            //�жϴ�ʱ�ֵܽ���Ƿ����������ֵܽ��
            if (colorOf(rnode) == RED) {
                setColor(rnode, BLACK);
                setColor(parentOf(x), RED);
                rotateRight(parentOf(x));
                // �ҵ��������ֵܽ��
                rnode = leftOf(parentOf(x));
            }
            // ����������ֵܽ裬�ֵ�û�ý�
            // ���ﲢ�����ж�Ϊ��ɫ�������ж��Ƿ�Ϊ��
            if (colorOf(rightOf(rnode)) == BLACK && colorOf(leftOf(rnode)) == BLACK) {
                // �Ƚ���
                setColor(rnode, RED);
                x = parentOf(x);
            }

            // �����,���ֵܽ裬�ֵ��еĽ�
            else {
                // ������С������ֵܽ�㱾����3�������Ľ������
                if (colorOf(leftOf(rnode)) == BLACK) {
                    setColor(rnode, RED);
                    setColor(rightOf(rnode), BLACK);
                    rotateLeft(rnode);
                    rnode = leftOf(parentOf(x));
                }
                setColor(rnode, colorOf(parentOf(x)));
                setColor(parentOf(rnode), BLACK);
                setColor(leftOf(rnode), BLACK);
                rotateRight(parentOf(x));
                // ��ʾѭ������
                x = root;
            }
        }
        
    }
    // ���һ���������Ǻ�ɫ����ֱ��Ⱦ�죬����ɾ���ĺ�ɫ�ڵ㣬�����������Ȼ����ƽ��
    setColor(x, BLACK);
}
//==========================



//==========================
/*
* ���Ҳ��� 
*  
*/ 

void find_number_book()   //��ͼ���Ų�ѯ 
{
	system("cls");
	color(8);
	toxy(46,8);
	int number;
	printf("��������Ҫ��ѯͼ��ı�ţ�");
	scanf("%d", &number);
	toxy(46,10);
	printf("���ڲ�ѯ....");
	Sleep(500);
	system("cls");
	toxy(40,8);
	printf("*********************ͼ������************************");
	toxy(40,10);
	printf("-----------------------------------------------------");
	toxy(40,11);
	printf("���          ����          ������           ���浥λ");
	toxy(40,12);
	printf("-----------------------------------------------------");
	toxy(40,14);
	NodeTree getNode = get(root, number);
	printf("%d%14s%14s%14s\n", getNode->key, getNode->name, getNode->author, getNode->press);
			
	
	toxy(46,16);
	printf("����������أ�");
	getch();
	menu();
}
//==========================


//==========================
 
void xianshi(NodeTree h){
 	static int i = 13;
    int j = 1; 
        toxy(40,i);
		printf("%d%14s%14s%14s\n", h->key, h->name, h->author, h->press);
		i++;
 }

void print(NodeTree h) {
	static int number = 0;
    if (h == null){
        return;
    }
    
	
	
    if (h->left != null) {
        print(h->left);
    }

	xianshi(h);
	nodeNumber++;

    if (h->right != null) {
        print(h->right);
    }

}

void printScanner() {
	print(root);
	toxy(45,13+nodeNumber);
	printf("�����������");
}
//==========================


//==========================
/*
* ��ӡȫ��ͼ�� 
*  
*/ 
void print_book() {  //ͼ������
	system("cls");
	color(6);
	toxy(46,10);
	printf("���ڲ�ѯ....");
	Sleep(500);
	system("cls");
	toxy(40,8);
	printf("*********************ͼ������************************");
	toxy(40,10);
	printf("-----------------------------------------------------");
	toxy(40,11);
	printf("���          ����          ������           ���浥λ");
	toxy(40,12);
	printf("-----------------------------------------------------");
	if(root == null)
	{
		toxy(45,11);
		printf("�����ʱû����Ŷ~�Ͽ�ȥ��Ӽ�����^_^(�����������)");
		getch();
		menu();
	}
	
	printScanner();
	
	getch();//�����Ժ��� 
}

//==========================




//==========================
/*
* �˳����� 
*  
*/ 
void over()       //�˳���� 
{
	char t;
	toxy(48,11);
	printf("-----------------------");
	toxy(48,12);
	printf("|   ��ȷ��Ҫ�˳���  |");
	toxy(48,14);
	printf("| 1.ȷ��     2.ȡ��   |");
	toxy(48,15);
	printf("-----------------------");
	while(1)
	{
		t=getch();         //����t
		switch(t)
		{
			case '1':
			system("cls");
		    color(6);
			toxy(48,10);
			printf("���ڰ�ȫ�˳�....");
			Sleep(1000);     //��ͣ1�� 
			system("cls");
			color(8);
			toxy(48,10);
			printf("�Ѱ�ȫ�˳����");
			toxy(48,12);
			printf("ллʹ�ã�");
			toxy(48,14);
			printf("by-by^_^");
			exit(0);  break; //��ֹ���� 
			case '2':
			menu(); break;   //���ú���������˵� 
			default :break;
		}
	}
} 
//==========================


//==========================
/*
* �޸�ͼ����Ϣ 
*  
*/ 
void amendBook() {
	
	do
	{
		system("cls");
		color(9);
		int number;
		char t,c;
		int i = 8;
		
		while(1)
		{
			toxy(45,i);
			printf("��������Ҫ�޸ĵ�ͼ��ı�ţ�");
			scanf("%d",&number);//getchar();
			Sleep(500);
			toxy(40,8);
			printf("*********************ͼ������************************");
			toxy(40,10);
			printf("-----------------------------------------------------");
			toxy(40,11);
			printf("���          ����          ������           ���浥λ");
			toxy(40,12);
			printf("-----------------------------------------------------");
			toxy(40,14);
			NodeTree getNode = get(root, number);
			printf("%d%14s%14s%14s\n", getNode->key, getNode->name, getNode->author, getNode->press);
			if(!get(root, number))
			{
				toxy(45,++i);
				printf("�����������������!");
				Sleep(500);
			}
			else
			{
				break;
			}
		}

		color(7);
		toxy(50,16);
		Sleep(500);
		printf("-------------------------");
		toxy(50,17);
		printf("|                       |");
		toxy(50,18);
		printf("|     �Ƿ���Ҫ�޸ģ�    |");
		toxy(50,20);
		printf("| 1.��             2.�� |");
		toxy(50,21);
		printf("|                       |");
		toxy(50,22);
		printf("-------------------------");
		while(1)
		{
			t=getch();
			if(t=='1')
			{
				break;
			} 
			else if(t=='2')
			{
				menu();
			}
		}
		system("cls");
		//�޸� 
		amend(number);
		color(7);
		toxy(50,16);
		printf("-------------------------");
		toxy(50,17);
		printf("|                       |");
		toxy(50,18);
		printf("|     �Ƿ�ȷ���޸ģ�    |");
		toxy(50,20);
		printf("| 1.��             2.�� |");
		toxy(50,21);
		printf("|                       |");
		toxy(50,22);
		printf("-------------------------");
		while(1)
		{
			t=getch();
			if(t=='1')
			{
				break;
			} 
			else if(t=='2')
			{
				menu();
			}
		}
		system("cls");
		toxy(46,10);
		printf("�����޸ģ����Ժ�....");
		Sleep(500);
		system("cls");
		toxy(46,8);
		printf("-------------------------");
		toxy(46,9);
		printf("|                       |");
		toxy(46,10);
		printf("|  ɾ���ɹ����Ƿ������ |");
		toxy(46,12);
		printf("| 1.��             2.�� |");
		toxy(46,13);
		printf("|                       |");
		toxy(46,14);
		printf("-------------------------");
		while(1)
		{
			c=getch();
			if(c=='1')
			{ 
				break; 
			}
			else if(c=='2')
			{
				menu();
			}
		}
	}while(1);
	
} 

void amend(Key key) {
	NodeTree Node = getNode(key);
    
    if (Node == null) {
        return;
    }
    //����ͼ����Ϣ
    color(9);
	toxy(48,8);
	printf("����������Ҫ�޸ĵ���Ϣ��\n");
	toxy(48,10);
	printf("����������(С��10λ��)��");
	scanf("%s", &(Node->name));getchar();
	toxy(48,12);
	printf("������������(С��10λ��)��");
	scanf("%s", &(Node->author));getchar();
	toxy(48,14);
	printf("������ͼ�������(С��10λ��)��");
	scanf("%s", &(Node->press));getchar();
	
} 
//==========================


//==========================
void menu()    //�˵� 
{
	do
	{
		system("cls");  //���� 
		HideCursor();  //���ع�� 
		color(15);    //����һ���ÿ�����ɫ 
		char t;
		toxy(50,5);//������ƶ�����50��5�����괦
		printf(" ͼ�����ϵͳ");
		toxy(48,8);
		printf("|     1.ͼ�����      |");
		toxy(48,10);
		printf("|     2.�޸���Ϣ      |");
		toxy(48,12);
		printf("|     3.ɾ����Ϣ      |");
		toxy(48,14);
		printf("|     4.ͼ���ѯ      |");
		toxy(48,16);
		printf("|     5.ͼ������      |");
		toxy(48,18);
		printf("|     6.�˳����      |");
		t=getch();    //�����Ժ��� 
		switch(t)
		{
			case '1': createAndIn();break;
			case '2': amendBook();//put_book();break;
			case '3': Remove();break;
			case '4': find_number_book();break;
			case '5': print_book();break;
			case '6': over();break;
			default : break;
		}
	}while(1);
}
//==========================




void main() {
	menu();
}
