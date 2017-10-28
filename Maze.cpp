#include<stdio.h>
#include<stdlib.h>

#define ERROR 1;
#define OK 1;

typedef struct {
	int ord;//序号
	int x, y;//坐标
	int dir;//方向，0-4代表东南西北
}ElemType;

typedef int MazeType, **Maze;

typedef struct StackNode {
	ElemType pos;
	StackNode *next;
}StackNode,*LinkStack;


void InitStack_L(LinkStack &S);//初始化栈
bool StackEmpty_L(LinkStack S);//判断栈是否为空
int Push_L(LinkStack &S, ElemType e);//元素入栈
int Pop_L(LinkStack &S, ElemType &e);//元素出栈
void NextPos(ElemType &e);//向既定方向走一步
void MarkPrint(Maze &maze, ElemType pos);//标记死胡同
void FootPrint(Maze &maze, ElemType pos);//标记走过的路
bool Pass(Maze maze, ElemType pos);//判断能否通过
bool operator == (ElemType M, ElemType N);//判断结构体相等
int ReadMaze(Maze &maze, int &m, int &n);//读迷宫
int PrintMaze(Maze maze, int m, int n);//打印路线
int MazePath(Maze &maze, ElemType start, ElemType end);//找路

int main() {
	int m, n;
	Maze maze;
	ElemType start, end;

	ReadMaze(maze, m, n);
	printf("迷宫如下(空格为通路，#为墙):\n");
	PrintMaze(maze, m, n);

	start.x = start.y = 1;
	end.x = m - 2;
	end.y = n - 2;

	if (MazePath(maze, start, end)) {
		printf("从入口到出口的路径为(*为路径):\n");
		PrintMaze(maze, m, n);
	} else
		printf("找不到从入口到出口的路径!\n");

	return 0;
}

void InitStack_L(LinkStack &S) {
	S = NULL;
}

bool StackEmpty_L(LinkStack S) {
	if (S)
		return false;
	else
		return true;
}

int Push_L(LinkStack &S, ElemType e) {
	LinkStack p;

	p = (LinkStack)malloc(sizeof(StackNode));
	if (!p)
		exit(0);
	else
	{
		p->pos.ord = e.ord;
		p->pos.x = e.x;
		p->pos.y = e.y;
		p->pos.dir = e.dir;
		p->next = S;
		S = p;
		return OK;
	}
}

int Pop_L(LinkStack &S, ElemType &e) {
	LinkStack p;

	if (S == NULL)
		exit(0);
	else {
		p = S;
		e.ord = p->pos.ord;
		e.x = p->pos.x;
		e.y = p->pos.y;
		e.dir = p->pos.dir;
		S = p->next;
		free(p);
		return OK;
	}
}

void NextPos(ElemType &NextPos) {
	int movei[4] = { 0,1,0,-1 };
	int movej[4] = { 1,0,-1,0 };
	if (NextPos.dir >= 4 || NextPos.dir < 0)
		return;
	NextPos.x = NextPos.x + movei[NextPos. dir];
	NextPos.y = NextPos.y + movej[NextPos.dir];
}

void MarkPrint(Maze &maze, ElemType pos) {
	maze[pos.x][pos.y] = 3;
}

void FootPrint(Maze &maze, ElemType pos) {
	maze[pos.x][pos.y] = 2;
}

bool Pass(Maze maze, ElemType pos) {
	if (!maze[pos.x][pos.y])
		return true;
	else
		return false;
}

bool operator ==(ElemType M, ElemType N) {
	return M.x == N.x&&M.y == N.y;
}

int ReadMaze(Maze &maze, int &m, int &n) {
	char *filename = "maze.txt";
	char ch;
	int i, j;

	FILE *mazefile;

	if ((mazefile = fopen(filename, "r")) == NULL) {
		printf("Could not open file\n");
		exit(0);
	}
	fscanf(mazefile, "%d %d\n", &m, &n);
	maze = new MazeType*[m];
	for (i = 0; i < m; i++)
		maze[i] = new MazeType[n];
		for (i = 0; i < m; i++){
			for (j = 0; j < n; j++) {
				fscanf(mazefile, "%c", &ch);
				maze[i][j] = ch == '1';
			}
			fscanf(mazefile, "\n");
	}
	return OK;
}

int PrintMaze(Maze maze, int m, int n) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			switch (maze[i][j]) {
				case 0:
					printf(" ");
					break;
				case 1:
					printf("#");
					break;
				case 2:
					printf("*");
					break;
				case 3:
					printf("@");
					break;
				default:
					break;
			};
		}
		printf("\n");
	}
	printf("\n");


	return OK;
}

int MazePath(Maze &maze, ElemType start, ElemType end) {
	int curstep;
	ElemType curpos;
	LinkStack S;
	InitStack_L(S);
	curpos.x = start.x;
	curpos.y = start.y;
	curstep = 1;

	do {
		if (Pass(maze, curpos)) {
			FootPrint(maze, curpos);
			curpos.ord = curstep;
			curpos.dir = 0;
			Push_L(S, curpos);
			if (curpos == end)
				return OK;
			NextPos(curpos);
			curstep++;
		} else {
			if (!StackEmpty_L(S)) {
				Pop_L(S, curpos);
				while (curpos.dir == 4 && !StackEmpty_L(S)) {
					MarkPrint(maze, curpos);
					Pop_L(S, curpos);
				}
				if (curpos.dir < 4) {
					curpos.dir++;
					Push_L(S, curpos);
					NextPos(curpos);
				}
			}
		}
	} while (!StackEmpty_L(S));

	return ERROR;
}
