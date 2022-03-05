#include<stdio.h>
#include<math.h>
#include<string.h>
#include<windows.h>
#include"demo.h"
//����ͷ�ļ� 

#define N 50
#define Max 0x3f3f3f
//����״̬ 



	typedef struct Scenein
	{
		char name[20];
		int SceneNum;
		char Introduce[1000];
	}Scene;//����������Ϣ 
	
	struct Scene_side_ride
	{
		int ScenePoint;
		int SceneSide;
		int load[N][N];
		Scene s[N];
	}Ride;//ͼ 
	
	struct LoadToPlace{
		int way[50];
		int size;
	}stack;//����ջ 
	
	



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

void amendScene()//�޸ľ��� 
{
	int x;
	printf("�������޸ľ���ı��:"); 
	scanf("%d",&x);
	if(x<1||x>NStart)
	{
		printf("��������ȷ�ľ����ţ�\n");
	}
	else
	{
				char newname[20];
				printf("������������:");
				scanf("%s",newname);
				strcpy(Ride.s[x-1].name,newname);
				amendScenename(x,newname);
				printf("�޸ĳɹ���\n");
				char newinfor[50];
				printf("�������µĽ���:");
				scanf("%s",newinfor);
				strcpy(Ride.s[x-1].Introduce,newinfor);
				amendSceneinfor(x,newinfor);
				printf("�޸ĳɹ���\n");
				int amendNum;
				int newload;
				while(1)
				{
					printf("������Ҫ�޸ĵ���������(-1�˳�):");
				scanf("%d",&amendNum);
				if(amendNum==-1) 
				{
					printf("����ɣ�\n");
					break;
				}
				else if(0<amendNum&&amendNum<NStart&&amendNum!=x&&Ride.s[amendNum].SceneNum!=-1)
				{
					printf("��������Ȩ��:");
					scanf("%d",&newload);
					Ride.load[amendNum-1][x-1]=Ride.load[x-1][amendNum-1]=newload;
					amendload(amendNum,x,newload);
					printf("�޸ĳɹ���\n");
					Ride.s[x-1].SceneNum=x;
				}
				else
				{
					printf("���벻�Ϸ���");
				}
			}
	}
}

void loginmune()
{
	while(1)
	{
		int x;
		printf("����������������������������������������������������������������������������������������\n");
		printf("��           *****����Ա�˵�******          ��\n");
		printf("��           *****0.�˳�**********          ��\n");
		printf("��           ****1.���Ӿ���  ****           ��\n");
		printf("��           *****2.ɾ������ ****           ��\n");
		printf("��           ****3.�޸��˺���Ϣ**           ��\n");
		printf("��           ****4.�޸ľ���******           ��\n");
		printf("��           ********************           ��\n");
		printf("����������������������������������������������������������������������������������������\n");
		scanf("%d",&x);
		switch(x)
		{
			case 0:
				printf("���˳�����Աģʽ\n");
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
				printf("���벻�Ϸ���\n");
				break; 
		}
		if(x==0)
		break;
	} 
}

void login()
{
	char inputname[20]={NULL},inputkey[20]={NULL};
	printf("��ӭʹ�ù���Աϵͳ�����¼:\n");
	printf("�û���:");
	scanf("%s",inputname);
	if(!strcmp(inputname,username))
	{
		printf("����:");
		scanf("%s",inputkey);
		if(!strcmp(inputkey,userkey))
		{
			loginmune();
		}
		else
		{
			printf("�������\n"); 
		}
	}
	else
	{
		printf("�˺Ŵ���\n");
	}
}


void loginamend()
{
	char newname[20],newkey[20];
	printf("�������µ��˺�:");
	scanf("%s",newname);
	printf("�������µ�����:");
	scanf("%s",newkey);
	FILE *fp;
	fp=fopen("USER.txt","w");
	fprintf(fp,"%s\n%s",newname,newkey);
	fclose(fp);
}


void DeleteScene()//ɾ������ 
{
	int deleteNum;
	printf("������ɾ���ľ���ı��(0�˳�ϵͳ)");
	scanf("%d",&deleteNum);
	if(deleteNum==0)
	{
		printf("���˳�ϵͳ\n");
	}
	else if(deleteNum<0||deleteNum>NStart)
	{
		printf("���벻�Ϸ���");
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
		strcpy(Ride.s[deleteNum-1].name,"������");
		strcpy(Ride.s[deleteNum-1].Introduce,"������");
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

void AddScene()//���Ӿ��� 
{
	
	char newscene[20];
	int count=0;
	printf("���������ľ�������ƣ��˳�Ϊ�˳�ϵͳ��:");
	scanf("%s",newscene);
	if(strcmp(newscene,"�˳�")==0)
	{
	printf("���˳�ϵͳ\n");	
		}
	else
	{
		operation(0,newscene);
		strcpy(Ride.s[NStart].name,newscene);
		char newinfor[100];
		printf("�������¾������:");
		scanf("%s",newinfor);
		strcpy(Ride.s[NStart].Introduce,newinfor);
		operation(1,newinfor);
		while(1)
		{
			printf("�����������ľ�����(-1�˳�):");
			int newnum;
			scanf("%d",&newnum);
			if(newnum==-1)
			{
				if(!count)
				{
					printf("��������һ���������㣡");
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
				printf("������������Ȩ��:");
				int newload;
				scanf("%d",&newload);
				Ride.load[NStart][newnum-1]=Ride.load[newnum-1][NStart]=newload; 
				operation2(newnum,newload);
				count++;
			}
			else
			{
				printf("��������ȷ���������㣡\n");
			}
		}
	}
}

void ShowLoad(int start,int end)//��ӡ���·�� 
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
	printf("%d��%d���·��Ϊ:",start+1,end+1);
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
	printf("����̾���Ϊ��%d\n",List[end]);
}



void Dijkstra(Scene_side_ride &G,int start)//�������·�� 
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

void MakeRide()//��ʼ��·����Ϣ 
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


void MakeSceneinfor()//��ʼ������ 
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
	
	void FindScene()//����Ų��� 
	{
		int n;
		while(1)
		{
		printf("����������Ҫ���ҵľ����ţ�0Ϊ�˳�ϵͳ����");
		scanf("%d",&n);
		if(n==0)
		{
			printf("���˳���ѯϵͳ\n");
			break;
		} 
		else if(n<0||n>NStart||Ride.s[n-1].SceneNum==-1)
		{
			
			printf("����������ݲ��Ϸ������������룡\n");
			continue;
		}
		else
		{
			printf("��ѯ������£�\n");
			printf("%d.%s\n%s\n",n,Ride.s[n-1].name,Ride.s[n-1].Introduce);
		}
		}
	}
	
	void FindScene_CN()//�����Ʋ��� 
	{
		char n[100];
		int i;
		while(1)
		{
		printf("����������Ҫ���ҵľ�������(�˳�Ϊ�˳�ϵͳ):");
		scanf("%s",n);
		if(strcmp(n,"�˳�")==0)
		{
			break;
		}
		for(i=0;i<NStart;i++)
		{
		if(strcmp(n,Ride.s[i].name)==0)
		{
			printf("����Ϊ��ѯ���:\n");
			printf("%d.%s\n%s\n",i+1,Ride.s[i].name,Ride.s[i].Introduce);
			break; 
		}
		 }
		 if(i==NStart)
		 {
		 	printf("δ��ѯ����ؽ����\n");
		  }
		  int i=0;
		
		}
	}
	
	void menu()//���˵� 
	{
		int MenuNum;
		int FindNum;
		void MakeMap();//�������� 
		
		printf("����������������������������������������������������������������������������������������\n");
		printf("��********************�˵�******************��\n");
		printf("��*           1.��ӡ��ͼ                   *��\n");
		printf("��*           2.��ѯ������Ϣ               *��\n");
		printf("��*           3.��ѯ������·��             *��\n");
		printf("��*           4.����Աϵͳ                 *��\n");
		printf("��******************************************��\n");
		printf("����������������������������������������������������������������������������������������\n");
		scanf("%d",&MenuNum);
		switch(MenuNum)
		{
			case 1:
				MakeMap();
				break; 
			case 2:
				printf("��ѡ���ѯ��ʽ:\n1.����Ų���\n2.�����Ʋ���\n");
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
						printf("���벻�Ϸ���\n");
						break;
				}
				break;
			case 3:
				int a,b;
				while(1)
				{
				printf("���������\n");
				scanf("%d",&a);
				if(a<1||a>NStart)
				{
					printf("��������ȷ�����ݣ�\n");
				}
				else
				{
					break;
				}
				}
				while(1)
				{
					printf("�������յ�\n");
				scanf("%d",&b);
				if(b<1||b>NStart)
				{
					printf("��������ȷ�����ݣ�\n");
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
				printf("���벻�Ϸ���\n");
				break;
		}
	}
	
	
	void MakeMap()//���Ƶ�ͼ 
	{
		printf("***********************************У԰ȫ��ͼ****************************************\n");
		printf("*************************************************************************************\n");
		printf("*                                 ѧ����Ԣ                                          *\n");
		printf("*                                    (6)                                            *\n");
		printf("*                                     |                                             *\n");
		printf("*        (1)                          |                                             *\n");
		printf("*      ������һһһһһһһһһһһѧ��ʳ��һһһһһ\\                              *\n");
		printf("*         |                         (7)                \\                            *\n");
		printf("*         |                          |                  \\                           *\n");
		printf("*         |                          |                  (5)                         *\n");
		printf("*         \\                          |                 ͼ���                       *\n");
		printf("*          \\                         |                /   \\   \\                     *\n");
		printf("*           \\                һһһһ|һһһһһһ   /     \\   \\                    *\n");
		printf("*            \\              |                     | /      |     \\                  *\n");
		printf("*             \\             |                      /       |       \\                *\n");
		printf("*              \\            |                     /     һһһ       \\   (10)       *\n");
		printf("*               \\           |        (3)          |   | ���� | һһһ���´�ҵ     *\n");
		printf("*            ʯ�ͻ�һһһһ |      ������         |   |   (4)  |         ����       *\n");
		printf("*              (2)          |                   |       һһһ            /         *\n");
		printf("*                            \\                  |         |              /          *\n");
		printf("*                             \\                 |         |             /           *\n");
		printf("*                              һһһһһһһһһ         |            /            *\n");
		printf("*                                       \\                 |           /             *\n");
		printf("*                                        \\                |         /               *\n");
		printf("*                                         \\               |        /                *\n");
		printf("*                                          \\              |       /                 *\n");
		printf("*                                            \\         �ڶ���ѧ¥                   *\n");
		printf("*                                              \\        (8)  \\                      *\n");
		printf("*                                                \\             \\                    *\n");
		printf("*                                                  \\          (9)                   *\n");
		printf("*                                                    һһһһ���Ľ�ѧ¥             *\n");
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
	 
	 
	 void amendload(int amendnum,int x,int load)//�޸�Ȩ�� 
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
	printf("       ��ӭʹ������ʯ�ʹ�ѧ����ϵͳ������\n"); 
	while(1)
	{
		menu();
	}
}










































