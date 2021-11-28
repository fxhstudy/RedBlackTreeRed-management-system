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

#define QUEUE_MAXSIZE	10000	//最大长度 
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
 
 
 
 //图书编号、书名、作者、出版社、出版日期、ISBN、版次、定价等
typedef struct Node{
	// 图书编号 
	int key;
	// 书名 
	char name[30];
	// 作者 
	char author[30];
	// 出版社 
	char press[30];
	// 记录左子结点
    struct Node* left;
    // 记录右子结点
    struct Node* right;
    // 记录父结点
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
void HideCursor()     //隐藏光标
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
 
void toxy(int x, int y)      //将光标移动到X,Y坐标处
{
COORD pos = { x , y };
HANDLE Out = GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleCursorPosition(Out, pos); 
}

//==========================
 
 




//==========================
/*
* 往树中添加数据 
*/ 
void createTree() {
	do{
    	system("cls");
		color(10);
		char t;
		root = (NodeTree)malloc(sizeof(Node));
		//输入图书信息
		toxy(48,8);
		printf("请输入图书编号(小于10位数)：");    
		scanf("%d", &(root->key));getchar();
		toxy(48,10);
		printf("请输入书名(小于10位数)：");
		scanf("%s", &(root->name));getchar();
		toxy(48,12);
		printf("请输入作者名(小于10位数)：");
		scanf("%s", &(root->author));getchar();
		toxy(48,14);
		printf("请输入图书出版社(小于10位数)：");
		scanf("%s", &(root->press));getchar();
		toxy(48,16);
		nodeNumber++;
		printf("正在保存....");
    	root->color = BLACK;
	    root->left = null;
	    root->right = null;
	    root->parent = null;
	    toxy(46,8);
		printf("-------------------------");
		toxy(46,9);
		printf("|                       |");
		toxy(46,10);
		printf("| 保存成功！是否继续？  |");
		toxy(46,12);
		printf("| 1.是             2.否 |");
		toxy(46,13);
		printf("|                       |");
		toxy(46,14);
		printf("-------------------------");
		while(1)    //利用死循环可有效防止其他按键干扰 
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



// 图书编号、书名、作者、出版社
void put_book() {
	do
	{
		system("cls");
		color(10);
		char t;
		NodeTree newNode = (Node*)malloc(sizeof(Node));
		//输入图书信息
		toxy(48,8);
		printf("请输入图书编号(小于10位数)：");    
		scanf("%d", &(newNode->key));getchar();
		toxy(48,10);
		printf("请输入书名(小于10位数)：");
		scanf("%s", &(newNode->name));getchar();
		toxy(48,12);
		printf("请输入作者名(小于10位数)：");
		scanf("%s", &(newNode->author));getchar();
		toxy(48,14);
		printf("请输入图书出版社(小于10位数)：");
		scanf("%s", &(newNode->press));getchar();
		toxy(48,16);
		printf("正在保存....");
		newNode->color = BLACK;
	    newNode->left = null;
	    newNode->right = null;
	    newNode->parent = null;
		put(root, newNode);
		Sleep(500);   //暂停0.5秒 
//		system("cls");
		toxy(46,8);
		printf("-------------------------");
		toxy(46,9);
		printf("|                       |");
		toxy(46,10);
		printf("| 保存成功！是否继续？  |");
		toxy(46,12);
		printf("| 1.是             2.否 |");
		toxy(46,13);
		printf("|                       |");
		toxy(46,14);
		printf("-------------------------");
		while(1)    //利用死循环可有效防止其他按键干扰 
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
* 插入操作 
*  
*/ 
void exchange(NodeTree h, NodeTree newNode) {
	h->key = newNode->key;
	strcpy(h->author, newNode->author);
	strcpy(h->name, newNode->name);
	strcpy(h->press, newNode->press);
}


// 在整个树上完成插入操作
void put(NodeTree h, NodeTree newNode) {
    NodeTree parent;
    int cmp;
    // 沿着根结点寻找插入位置
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

    // 调整
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

// 判断当前结点的父指向链接是否为红色
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
// 左旋调整
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
// 右旋调整
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
    // 本质上就是父结点是黑色就不需要调整了，对应情况就是2，3
    while (x->parent != null && x->parent->color == RED) {
        // 1、x的父结点是爷爷的左孩子
        if (parentOf(x) == leftOf(parentOf(parentOf(x)))) {
            // 叔叔结点
            NodeTree y = rightOf(parentOf(parentOf(x)));
            // 第三种情况
            if (colorOf(y) == RED) {
                setColor(parentOf(x), BLACK);
                setColor(y, BLACK);
                setColor(parentOf(y), RED);
                // 考虑全局改为while循环
                x = parentOf(parentOf(x));
            }

            // 第二种情况
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
                // 爷爷变红
                setColor(parentOf(parentOf(x)), RED);
                // 父亲变黑
                setColor(parentOf(x), BLACK);
                // 根据爷爷结点右旋
                rotateRight(parentOf(parentOf(x)));
            }
        } else {
            // 右3
            // 叔叔结点
            NodeTree y = leftOf(parentOf(parentOf(x)));
            // 第三种情况
            if (colorOf(y) == RED) {
                setColor(parentOf(x), BLACK);
                setColor(y, BLACK);
                setColor(parentOf(y), RED);
            }

            // 第二种情况
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
                // 爷爷变红
                setColor(parentOf(parentOf(x)), RED);
                // 父亲变黑
                setColor(parentOf(x), BLACK);
                // 根据爷爷结点右旋
                rotateLeft(parentOf(parentOf(x)));
            }
        }
    }

    root->color = BLACK;
}

// 根据key,从树中找出对应的值
NodeTree get(NodeTree h, Key key) {
    if (h == null) {
    	toxy(40, 14);
    	printf("对不起未找到!...");Sleep(2000);
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

// 找到指定结点的前驱结点，即找到小于node结点的最大值
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

// 找后继节点,即大于node结点的最小值
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
    删除操作：
    1、删除叶子结点，直接删除
    2、删除的结点有一个子结点，那么用子结点来代替
    3、删除的结点有两个子结点，此时需要找到前驱结点或者后继结点来代替

*/
void deleteNode(NodeTree node) {
    // 3.node结点有两个子孩子
    if (node->left != null && node->right != null) {
        NodeTree sucessorNode = sucessor(node);
        exchange(node, sucessorNode);
        node = sucessorNode;
    }

    NodeTree replacement = node->left!=null?node->left:node->right;
    // 2. 替代结点不为空
    if (replacement != null) {
        // 替代者的父指针指向的原来node的父亲
        replacement->parent = node->parent;
        // node是根节点
        if (node->parent == null) {
            root = replacement;
        } 
        // node是左孩子，所以代替者依然是左孩子
        else if(node == node->parent->left) {
            node->parent->left = replacement;
        } 
        // node是右孩子，所以替代者依然是右孩子
        else {
            node->parent->right = replacement;
        }

        // 替换完时候需要调整平衡
        if (node->color == BLACK) {
            //需要调整
             fixAfterRemove(replacement);
        }
        free(node);
    } else if (node->parent == null) {
        // 删除结点就是根节点
        root = null;
    } 
    // 1、node结点是叶子结点，replacement为null
    else {
        
        // 先调整
        if (node->color == BLACK){
            fixAfterRemove(node);
        } 

        // 再删除
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

void Remove() {		//删除信息
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
			printf("请输入您要删除的图书的编号：");
			scanf("%d",&number);//getchar();
			Sleep(500);
			toxy(40,8);
			printf("*********************图书总览************************");
			toxy(40,10);
			printf("-----------------------------------------------------");
			toxy(40,11);
			printf("编号          书名          作者名           出版单位");
			toxy(40,12);
			printf("-----------------------------------------------------");
			toxy(40,14);
			NodeTree getNode = get(root, number);
			printf("%d%14s%14s%14s\n", getNode->key, getNode->name, getNode->author, getNode->press);
			if(!get(root, number))
			{
				toxy(45,++i);
				printf("输入错误，请重新输入!");
				Sleep(500);
			}
			else
			{
				break;
			}
		}
		toxy(40,8);
		printf("*********************图书总览************************");
		toxy(40,10);
		printf("-----------------------------------------------------");
		toxy(40,11);
		printf("编号          书名          作者名           出版单位");
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
		printf("|     是否确认删除？    |");
		toxy(50,20);
		printf("| 1.是             2.否 |");
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
		printf("正在删除，请稍后....");
		removeNode(number);
		Sleep(500);
		system("cls");
		toxy(46,8);
		printf("-------------------------");
		toxy(46,9);
		printf("|                       |");
		toxy(46,10);
		printf("|  删除成功，是否继续？ |");
		toxy(46,12);
		printf("| 1.是             2.否 |");
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

// 删除后调整
void fixAfterRemove(NodeTree x) {
    // 情况二、三
    while (x != root && colorOf(x) == BLACK) {
        // x是左孩子的情况
        if (x == leftOf(parentOf(x))) {
            // 兄弟结点
            NodeTree rnode = rightOf(parentOf(x));

            //判断此时兄弟结点是否是真正的兄弟结点
            if (colorOf(rnode) == RED) {
                setColor(rnode, BLACK);
                setColor(parentOf(x), RED);
                rotateLeft(parentOf(x));
                // 找到真正的兄弟结点
                rnode = rightOf(parentOf(x));
            }
            // 情况三，找兄弟借，兄弟没得借
            // 这里并不是判断为黑色，而是判断是否为空
            if (colorOf(leftOf(rnode)) == BLACK && colorOf(rightOf(rnode)) == BLACK) {
                // 比较难
                setColor(rnode, RED);
                x = parentOf(x);
            }

            // 情况二,找兄弟借，兄弟有的借
            else {
                // 分两种小情况：兄弟结点本来是3结点或者四结点的情况
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
                // 表示循环结束
                x = root;
            }

        }

        // x是右孩子的情况
        else {
            // 兄弟结点
            NodeTree rnode = leftOf(parentOf(x));

            //判断此时兄弟结点是否是真正的兄弟结点
            if (colorOf(rnode) == RED) {
                setColor(rnode, BLACK);
                setColor(parentOf(x), RED);
                rotateRight(parentOf(x));
                // 找到真正的兄弟结点
                rnode = leftOf(parentOf(x));
            }
            // 情况三，找兄弟借，兄弟没得借
            // 这里并不是判断为黑色，而是判断是否为空
            if (colorOf(rightOf(rnode)) == BLACK && colorOf(leftOf(rnode)) == BLACK) {
                // 比较难
                setColor(rnode, RED);
                x = parentOf(x);
            }

            // 情况二,找兄弟借，兄弟有的借
            else {
                // 分两种小情况：兄弟结点本来是3结点或者四结点的情况
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
                // 表示循环结束
                x = root;
            }
        }
        
    }
    // 情况一、替代结点是红色，则直接染红，补偿删除的黑色节点，这样红黑树依然保持平衡
    setColor(x, BLACK);
}
//==========================



//==========================
/*
* 查找操作 
*  
*/ 

void find_number_book()   //按图书编号查询 
{
	system("cls");
	color(8);
	toxy(46,8);
	int number;
	printf("请输入您要查询图书的编号：");
	scanf("%d", &number);
	toxy(46,10);
	printf("正在查询....");
	Sleep(500);
	system("cls");
	toxy(40,8);
	printf("*********************图书总览************************");
	toxy(40,10);
	printf("-----------------------------------------------------");
	toxy(40,11);
	printf("编号          书名          作者名           出版单位");
	toxy(40,12);
	printf("-----------------------------------------------------");
	toxy(40,14);
	NodeTree getNode = get(root, number);
	printf("%d%14s%14s%14s\n", getNode->key, getNode->name, getNode->author, getNode->press);
			
	
	toxy(46,16);
	printf("按任意键返回！");
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
	printf("按任意键返回");
}
//==========================


//==========================
/*
* 打印全部图书 
*  
*/ 
void print_book() {  //图书总览
	system("cls");
	color(6);
	toxy(46,10);
	printf("正在查询....");
	Sleep(500);
	system("cls");
	toxy(40,8);
	printf("*********************图书总览************************");
	toxy(40,10);
	printf("-----------------------------------------------------");
	toxy(40,11);
	printf("编号          书名          作者名           出版单位");
	toxy(40,12);
	printf("-----------------------------------------------------");
	if(root == null)
	{
		toxy(45,11);
		printf("书库暂时没有书哦~赶快去添加几本吧^_^(按任意键返回)");
		getch();
		menu();
	}
	
	printScanner();
	
	getch();//不回显函数 
}

//==========================




//==========================
/*
* 退出操作 
*  
*/ 
void over()       //退出软件 
{
	char t;
	toxy(48,11);
	printf("-----------------------");
	toxy(48,12);
	printf("|   您确定要退出吗？  |");
	toxy(48,14);
	printf("| 1.确定     2.取消   |");
	toxy(48,15);
	printf("-----------------------");
	while(1)
	{
		t=getch();         //输入t
		switch(t)
		{
			case '1':
			system("cls");
		    color(6);
			toxy(48,10);
			printf("正在安全退出....");
			Sleep(1000);     //暂停1秒 
			system("cls");
			color(8);
			toxy(48,10);
			printf("已安全退出软件");
			toxy(48,12);
			printf("谢谢使用！");
			toxy(48,14);
			printf("by-by^_^");
			exit(0);  break; //终止程序 
			case '2':
			menu(); break;   //调用函数，进入菜单 
			default :break;
		}
	}
} 
//==========================


//==========================
/*
* 修改图书信息 
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
			printf("请输入您要修改的图书的编号：");
			scanf("%d",&number);//getchar();
			Sleep(500);
			toxy(40,8);
			printf("*********************图书总览************************");
			toxy(40,10);
			printf("-----------------------------------------------------");
			toxy(40,11);
			printf("编号          书名          作者名           出版单位");
			toxy(40,12);
			printf("-----------------------------------------------------");
			toxy(40,14);
			NodeTree getNode = get(root, number);
			printf("%d%14s%14s%14s\n", getNode->key, getNode->name, getNode->author, getNode->press);
			if(!get(root, number))
			{
				toxy(45,++i);
				printf("输入错误，请重新输入!");
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
		printf("|     是否需要修改？    |");
		toxy(50,20);
		printf("| 1.是             2.否 |");
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
		//修改 
		amend(number);
		color(7);
		toxy(50,16);
		printf("-------------------------");
		toxy(50,17);
		printf("|                       |");
		toxy(50,18);
		printf("|     是否确认修改？    |");
		toxy(50,20);
		printf("| 1.是             2.否 |");
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
		printf("正在修改，请稍后....");
		Sleep(500);
		system("cls");
		toxy(46,8);
		printf("-------------------------");
		toxy(46,9);
		printf("|                       |");
		toxy(46,10);
		printf("|  删除成功，是否继续？ |");
		toxy(46,12);
		printf("| 1.是             2.否 |");
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
    //输入图书信息
    color(9);
	toxy(48,8);
	printf("请输入你需要修改的信息：\n");
	toxy(48,10);
	printf("请输入书名(小于10位数)：");
	scanf("%s", &(Node->name));getchar();
	toxy(48,12);
	printf("请输入作者名(小于10位数)：");
	scanf("%s", &(Node->author));getchar();
	toxy(48,14);
	printf("请输入图书出版社(小于10位数)：");
	scanf("%s", &(Node->press));getchar();
	
} 
//==========================


//==========================
void menu()    //菜单 
{
	do
	{
		system("cls");  //清屏 
		HideCursor();  //隐藏光标 
		color(15);    //设置一个好看的颜色 
		char t;
		toxy(50,5);//将光标移动到（50，5）坐标处
		printf(" 图书管理系统");
		toxy(48,8);
		printf("|     1.图书入库      |");
		toxy(48,10);
		printf("|     2.修改信息      |");
		toxy(48,12);
		printf("|     3.删除信息      |");
		toxy(48,14);
		printf("|     4.图书查询      |");
		toxy(48,16);
		printf("|     5.图书总览      |");
		toxy(48,18);
		printf("|     6.退出软件      |");
		t=getch();    //不回显函数 
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
