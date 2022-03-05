#include<stdio.h>
#include<math.h>
#include<string.h>
#include<windows.h>
#include"demo.h"
//定义头文件 

#define N 50
#define Max 0x3f3f3f
//定义状态 



	typedef struct Scenein
	{
		char name[20];
		int SceneNum;
		char Introduce[1000];
	}Scene;//各个景点信息 
	
	struct Scene_side_ride
	{
		int ScenePoint;
		int SceneSide;
		int load[N][N];
		Scene s[N];
	}Ride;//图 
	
	struct LoadToPlace{
		int way[50];
		int size;
	}stack;//创建栈 
	
	



int List[N],path[N];
bool tof[N];
int NStart=10;
char username[20]={NULL},userkey[20]={NULL};

void addnstart()
{
	FILE *fp;
	fp=fopen("Data.txt","w");
	fprintf(fp,"%d",NStart);
	fclose(fp);
}

void operation2(int newnum,int newload)
{
	FILE *fp;
	fp=fopen("LoadData.txt","a");
	if(fp==NULL)
	{
		printf("NOT FIND GIT!");
		exit(-1);
	}
	fprintf(fp,"%d %d %d",NStart,newnum,newload);
	fclose(fp);
}
void operation(int way,char *information)
{
	FILE *fp,*fread;
	switch(way)
	{
		case 0:
			fp=fopen("SceneName.txt","a");
			if(fp==NULL)
			{
				printf("NOT FIND GIT!");
				exit(-1);
			}
			fprintf(fp,"%d %s\n",NStart,information);
			fclose(fp);
			break;
		case 1:
			fread=fopen("SceneInfor.txt","a");
			if(fp=NULL)
			{
				printf("NOT FIND GIT!");
				exit(-1);
			}
			fprintf(fread,"%s\n",information);
			fclose(fread);
			break;
			
	}
}

void file_readUser()
 {
  char nowname[20]={NULL},nowkey[20]={NULL};
  int i;
 FILE *fpRead=fopen("USER.txt","r");
 if(fpRead==NULL) exit(0);
 for(i=0;i<20;i++)
 {
  fscanf(fpRead,"%s\n%s",nowname,nowkey);
  strcpy(username,nowname);
  strcpy(userkey,nowkey);
 }
 }

void amendScene()//修改景点 
{
	int x;
	printf("请输入修改景点的编号:"); 
	scanf("%d",&x);
	if(x<1||x>NStart)
	{
		printf("请输入正确的景点编号！\n");
	}
	else
	{
				char newname[20];
				printf("请输入新名称:");
				scanf("%s",newname);
				strcpy(Ride.s[x-1].name,newname);
				amendScenename(x,newname);
				printf("修改成功！\n");
				char newinfor[50];
				printf("请输入新的介绍:");
				scanf("%s",newinfor);
				strcpy(Ride.s[x-1].Introduce,newinfor);
				amendSceneinfor(x,newinfor);
				printf("修改成功！\n");
				int amendNum;
				int newload;
				while(1)
				{
					printf("请输入要修改的相连景点(-1退出):");
				scanf("%d",&amendNum);
				if(amendNum==-1) 
				{
					printf("已完成！\n");
					break;
				}
				else if(0<amendNum&&amendNum<NStart&&amendNum!=x&&Ride.s[amendNum].SceneNum!=-1)
				{
					printf("请输入新权重:");
					scanf("%d",&newload);
					Ride.load[amendNum-1][x-1]=Ride.load[x-1][amendNum-1]=newload;
					amendload(amendNum,x,newload);
					printf("修改成功！\n");
					Ride.s[x-1].SceneNum=x;
				}
				else
				{
					printf("输入不合法！");
				}
			}
	}
}

void loginmune()
{
	while(1)
	{
		int x;
		printf("┏──────────────────────────────────────────┒\n");
		printf("│           *****管理员菜单******          │\n");
		printf("│           *****0.退出**********          │\n");
		printf("│           ****1.增加景点  ****           │\n");
		printf("│           *****2.删除景点 ****           │\n");
		printf("│           ****3.修改账号信息**           │\n");
		printf("│           ****4.修改景点******           │\n");
		printf("│           ********************           │\n");
		printf("┕──────────────────────────────────────────┘\n");
		scanf("%d",&x);
		switch(x)
		{
			case 0:
				printf("已退出管理员模式\n");
				break;
			case 1:
				AddScene();
				break;
			case 2:
				DeleteScene();
				break;
			case 3:
				loginamend();
				break;
			case 4:
				amendScene();
				break;
			default:
				printf("输入不合法！\n");
				break; 
		}
		if(x==0)
		break;
	} 
}

void login()
{
	char inputname[20]={NULL},inputkey[20]={NULL};
	printf("欢迎使用管理员系统！请登录:\n");
	printf("用户名:");
	scanf("%s",inputname);
	if(!strcmp(inputname,username))
	{
		printf("密码:");
		scanf("%s",inputkey);
		if(!strcmp(inputkey,userkey))
		{
			loginmune();
		}
		else
		{
			printf("密码错误！\n"); 
		}
	}
	else
	{
		printf("账号错误！\n");
	}
}


void loginamend()
{
	char newname[20],newkey[20];
	printf("请输入新的账号:");
	scanf("%s",newname);
	printf("请输入新的密码:");
	scanf("%s",newkey);
	FILE *fp;
	fp=fopen("USER.txt","w");
	fprintf(fp,"%s\n%s",newname,newkey);
	fclose(fp);
}


void DeleteScene()//删除景点 
{
	int deleteNum;
	printf("请输入删除的景点的编号(0退出系统)");
	scanf("%d",&deleteNum);
	if(deleteNum==0)
	{
		printf("已退出系统\n");
	}
	else if(deleteNum<0||deleteNum>NStart)
	{
		printf("输入不合法！");
	}
	else
	{
		FILE *fp,*fw;
		fp=fopen("SceneName.txt","r");
		int count=0,number[20];
		char Scenename[20],newScenename[20][20];
		int SceneNum;
		for(int i;i<NStart;i++)
		{
			Ride.load[deleteNum-1][i]=Ride.load[i][deleteNum-1]=Max;
		}
		strcpy(Ride.s[deleteNum-1].name,"空数据");
		strcpy(Ride.s[deleteNum-1].Introduce,"空数据");
		Ride.s[deleteNum-1].SceneNum=-1; 
		while(fscanf(fp,"%d %s",&SceneNum,Scenename)!=EOF)
		{
			if(SceneNum!=deleteNum)
			{
				number[count]=SceneNum;
				strcpy(newScenename[count],Scenename);
			}
			else
			{
				number[count]=-1;
				strcpy(newScenename[count],Scenename);
			}
			count++;
		}
    	fclose(fp);
    	fw=fopen("SceneName.txt","w");
    	for(int i=0;i<count;i++)
    	{
    		fprintf(fp,"%d %s\n",number[i],newScenename[i]);
		}
		fclose(fw);
		printf("successful\n");
	}
}

void AddScene()//增加景点 
{
	
	char newscene[20];
	int count=0;
	printf("请输入加入的景点的名称（退出为退出系统）:");
	scanf("%s",newscene);
	if(strcmp(newscene,"退出")==0)
	{
	printf("已退出系统\n");	
		}
	else
	{
		operation(0,newscene);
		strcpy(Ride.s[NStart].name,newscene);
		char newinfor[100];
		printf("请输入新景点介绍:");
		scanf("%s",newinfor);
		strcpy(Ride.s[NStart].Introduce,newinfor);
		operation(1,newinfor);
		while(1)
		{
			printf("请输入相连的景点编号(-1退出):");
			int newnum;
			scanf("%d",&newnum);
			if(newnum==-1)
			{
				if(!count)
				{
					printf("至少输入一个相连景点！");
				}
				else
				{
					NStart++;
					addnstart();
					Ride.s[NStart-1].SceneNum=NStart;
					break;
				}
			}
			else if(0<newnum&&newnum<NStart)
			{
				printf("请输入相连的权重:");
				int newload;
				scanf("%d",&newload);
				Ride.load[NStart][newnum-1]=Ride.load[newnum-1][NStart]=newload; 
				operation2(newnum,newload);
				count++;
			}
			else
			{
				printf("请输入正确的相连景点！\n");
			}
		}
	}
}

void ShowLoad(int start,int end)//打印最短路径 
{
	void Dijkstra(Scene_side_ride &G,int start);
	Dijkstra(Ride,start);
	stack.size=-1;
	int x=end;
	while(1)
	{
		if(x==-1)
		break;
		stack.size++;
		stack.way[stack.size]=x;
		x=path[x];
	}
	stack.size++;
	stack.way[stack.size]=start;
	printf("%d到%d最短路径为:",start+1,end+1);
	while(stack.size>=0)
	{
		if(stack.size>0)
		{
			printf("%s->",Ride.s[stack.way[stack.size]].name);
		}
		else
		{
			printf("%s\n",Ride.s[stack.way[stack.size]].name);
		}
		stack.size--;
	}
	printf("其最短距离为：%d\n",List[end]);
}



void Dijkstra(Scene_side_ride &G,int start)//计算最短路径 
{
	
	memset(path,-1,sizeof(path));
	int i,count=0,NewList,j,d;
	for(i=0;i<NStart;i++)
	{
		tof[i]=false;
		List[i]=G.load[start][i];
		if(Ride.s[i].SceneNum==-1)
		{
			tof[i]=true;
		}
	}
	tof[start]=true;
	List[start]=0;
	while(count<N)
	{
		d=Max;
		for(i=0;i<NStart;i++)
		{
			if(!tof[i] && List[i]<d)
			{
				d=List[i];
				j=i;
			}
		}
		tof[j]=true;
		count++;
		for(i=0;i<NStart;i++)
		{
			NewList=d+G.load[j][i];
			if(!tof[i]&&NewList<List[i])
			{
				List[i]=NewList;
				path[i]=j;
			}
			
		}
	}
}

void MakeRide()//初始化路径信息 
{
	FILE *fp;
	int i,k;
	for(i=0;i<N;i++)
	{
		for(k=0;k<N;k++)
		{
			Ride.load[i][k]=Max;
		}
	}
	fp=fopen("LoadData.txt","r");
	if(fp==NULL)
	{
		printf("ERORRE!");
		exit(-1);
	} 
	int Num1=0,Num2=0,LoadNum=0;
	while(fscanf(fp,"%d %d %d",&Num1,&Num2,&LoadNum)!=EOF)
	{
		Ride.load[Num1][Num2]=Ride.load[Num2][Num1]=LoadNum;
		fgetc(fp);
	}
}


void MakeSceneinfor()//初始化数据 
	{
		int i;
		for(i=0;i<NStart;i++)
		{
			Ride.s[i].SceneNum=i+1;
		}
		FILE *fp,*fread;
		fp=fopen("SceneName.txt","r");
		int SceneNum,SceneNum2;
		char Scenename[20],SceneInfor[1000]={NULL};
		if(fp==NULL)
		{
			printf("Not Find Git!");
			exit(-1);
		}
		while(fscanf(fp,"%d %s",&SceneNum,Scenename)!=EOF)
		{
			if(SceneNum==-1)
			{
				continue;
			}
			strcpy(Ride.s[SceneNum].name,Scenename);
			fgetc(fp);
		}
		fread=fopen("SceneInfor.txt","r");
		if(fread==NULL)
		{
			printf("Not Find Git!");
			exit(-1);
		}
		for(int j=0;j<NStart;j++)
		{
			fscanf(fread,"%s",SceneInfor);
			strcpy(Ride.s[j].Introduce,SceneInfor);
		}
	}
	
	void FindScene()//按编号查找 
	{
		int n;
		while(1)
		{
		printf("请输入你需要查找的景点编号（0为退出系统）：");
		scanf("%d",&n);
		if(n==0)
		{
			printf("已退出查询系统\n");
			break;
		} 
		else if(n<0||n>NStart||Ride.s[n-1].SceneNum==-1)
		{
			
			printf("您输入的数据不合法，请重新输入！\n");
			continue;
		}
		else
		{
			printf("查询结果如下：\n");
			printf("%d.%s\n%s\n",n,Ride.s[n-1].name,Ride.s[n-1].Introduce);
		}
		}
	}
	
	void FindScene_CN()//按名称查找 
	{
		char n[100];
		int i;
		while(1)
		{
		printf("请输入你需要查找的景点名称(退出为退出系统):");
		scanf("%s",n);
		if(strcmp(n,"退出")==0)
		{
			break;
		}
		for(i=0;i<NStart;i++)
		{
		if(strcmp(n,Ride.s[i].name)==0)
		{
			printf("以下为查询结果:\n");
			printf("%d.%s\n%s\n",i+1,Ride.s[i].name,Ride.s[i].Introduce);
			break; 
		}
		 }
		 if(i==NStart)
		 {
		 	printf("未查询到相关结果！\n");
		  }
		  int i=0;
		
		}
	}
	
	void menu()//主菜单 
	{
		int MenuNum;
		int FindNum;
		void MakeMap();//声明函数 
		
		printf("┏──────────────────────────────────────────┒\n");
		printf("│********************菜单******************│\n");
		printf("│*           1.打印地图                   *│\n");
		printf("│*           2.查询景点信息               *│\n");
		printf("│*           3.查询两景点路径             *│\n");
		printf("│*           4.管理员系统                 *│\n");
		printf("│******************************************│\n");
		printf("┕──────────────────────────────────────────┘\n");
		scanf("%d",&MenuNum);
		switch(MenuNum)
		{
			case 1:
				MakeMap();
				break; 
			case 2:
				printf("请选择查询方式:\n1.按编号查找\n2.按名称查找\n");
				scanf("%d",&FindNum);
				switch(FindNum)
				{
					case 1:
						FindScene();
						break;
					case 2:
						FindScene_CN();
						break;
					default:
						printf("输入不合法！\n");
						break;
				}
				break;
			case 3:
				int a,b;
				while(1)
				{
				printf("请输入起点\n");
				scanf("%d",&a);
				if(a<1||a>NStart)
				{
					printf("请输入正确的数据！\n");
				}
				else
				{
					break;
				}
				}
				while(1)
				{
					printf("请输入终点\n");
				scanf("%d",&b);
				if(b<1||b>NStart)
				{
					printf("请输入正确的数据！\n");
				}
				else
				{
					break;
				}
				}
				ShowLoad(a-1,b-1);
				break;
			case 4:
				login();
				break; 
			default:
				printf("输入不合法！\n");
				break;
		}
	}
	
	
	void MakeMap()//绘制地图 
	{
		printf("***********************************校园全景图****************************************\n");
		printf("*************************************************************************************\n");
		printf("*                                 学生公寓                                          *\n");
		printf("*                                    (6)                                            *\n");
		printf("*                                     |                                             *\n");
		printf("*        (1)                          |                                             *\n");
		printf("*      体育馆一一一一一一一一一一一学生食堂一一一一一\\                              *\n");
		printf("*         |                         (7)                \\                            *\n");
		printf("*         |                          |                  \\                           *\n");
		printf("*         |                          |                  (5)                         *\n");
		printf("*         \\                          |                 图书馆                       *\n");
		printf("*          \\                         |                /   \\   \\                     *\n");
		printf("*           \\                一一一一|一一一一一一   /     \\   \\                    *\n");
		printf("*            \\              |                     | /      |     \\                  *\n");
		printf("*             \\             |                      /       |       \\                *\n");
		printf("*              \\            |                     /     一一一       \\   (10)       *\n");
		printf("*               \\           |        (3)          |   | 天鹅湖 | 一一一创新创业     *\n");
		printf("*            石油魂一一一一 |      龙井湖         |   |   (4)  |         基地       *\n");
		printf("*              (2)          |                   |       一一一            /         *\n");
		printf("*                            \\                  |         |              /          *\n");
		printf("*                             \\                 |         |             /           *\n");
		printf("*                              一一一一一一一一一         |            /            *\n");
		printf("*                                       \\                 |           /             *\n");
		printf("*                                        \\                |         /               *\n");
		printf("*                                         \\               |        /                *\n");
		printf("*                                          \\              |       /                 *\n");
		printf("*                                            \\         第二教学楼                   *\n");
		printf("*                                              \\        (8)  \\                      *\n");
		printf("*                                                \\             \\                    *\n");
		printf("*                                                  \\          (9)                   *\n");
		printf("*                                                    一一一一第四教学楼             *\n");
		printf("*************************************************************************************\n\n\n");
	 }  
	 
	 void amendScenename(int num,char *name)
	 {
	 	int Bnum;
		char Bname[20];
		int Snum[20],count=0;
	 	char nname[20][20];
		FILE *fp,*fw;
	 	fp=fopen("SceneName.txt","r");
	 	while(fscanf(fp,"%d %s",&Bnum,Bname)!=EOF)
	 	{
	 		if(count==num-1)
	 		{
	 			Snum[count]=count;
	 			strcpy(nname[count],name);
			 }
			 else
			 {
			 	Snum[count]=Bnum;
			 	strcpy(nname[count],Bname);
			 }
			 count++;
		 }
		 fclose(fp);
		 fw=fopen("SceneName.txt","w");
		 for(int i=0;i<count;i++)
		 {
		 	fprintf(fw,"%d %s\n",i,nname[i]);
		 }
		 fclose(fw);
	 }
	 
	 void amendSceneinfor(int num,char *infor)
	 {
		char Binfor[100];
		int count=0;
	 	char ninfor[20][1000];
		FILE *fp,*fw;
	 	fp=fopen("SceneInfor.txt","r");
	 	while(fscanf(fp,"%s\n",Binfor)!=EOF)
	 	{
			 if(count==num-1)
	 		{
	 			strcpy(ninfor[count],infor);
			}
			 else
			 {
			 	strcpy(ninfor[count],Binfor);
			 }
			 count++;
		 }
		 fclose(fp);
		 fw=fopen("SceneInfor.txt","w");
		 printf("%s\n",ninfor[0]);
		 for(int i=0;i<count;i++)
		 {
		 	fprintf(fw,"%s\n",ninfor[i]);
		 }
		 fclose(fw);
	 }
	 
	 
	 void amendload(int amendnum,int x,int load)//修改权重 
	 {
	 	int Num1,Num2,LoadNum;
		 char iload[20][20];
		 FILE *fp,*fw;

	 	for(int i=0;i<20;i++)
	 	{
	 		for(int j=0;j<20;j++)
	 		{
	 			iload[i][j]=-1;
			 }
		 }
		 fp=fopen("LoadData.txt","r");
		 while(fscanf(fp,"%d %d %d",&Num1,&Num2,&LoadNum)!=EOF)
	{
		iload[Num1][Num2]=LoadNum;
	}
		 fclose(fp);
		 fw=fopen("LoadData.txt","w");
		 for(int i=0;i<20;i++)
		 {
		 	for(int j=0;j<20;j++)
		 	{
		 		if(i==amendnum-1&&j==x-1)
		 		{
		 			iload[i][j]=load;
				 }
				if(i==x-1&&j==amendnum-1)
				{
					iload[i][j]=load;
				}
				 if (iload[i][j]!=-1)
		 		{
		 			fprintf(fw,"%d %d %d\n",i,j,iload[i][j]);
				 }
			 }
		 }
		 fclose(fw);
	 }
	
int main()
{
	FILE *fp;
	fp=fopen("Data.txt","r");
	fscanf(fp,"%d",&NStart);
	MakeSceneinfor();
	MakeRide();
	file_readUser();
	printf("       欢迎使用西南石油大学导航系统！！！\n"); 
	while(1)
	{
		menu();
	}
}










































