struct Scene_side_ride;
struct Scenein; 

void FindScene();//�����Ѱ�� ����ɣ� 
void FindScene_CN();//������Ѱ��  ����ɣ� 
void MakeSceneinfor();//��ʼ��У԰���� ����ɣ� 
void MakeMap();//���Ƶ�ͼ ����ɣ�
void menu();//�˵� ����ɣ� 
void MakeRide();//��ʼ��ͼ���ݣ���ɣ� 
void Dijkstra(Scene_side_ride &G,int start);//�������·������ɣ� 
void ShowLoad(int start,int end);//��ӡ���·�� 
void AddScene();//���Ӿ�����Ϣ����ɣ� 
void DeleteScene();//ɾ��������Ϣ ����ɣ� 
void amendScene();//�޸ľ�����Ϣ ����ɣ�
void login();//����Ա��¼����ɣ� 
void loginmenu();//����Ա�˵�����ɣ� 
void loginamend();//�޸Ĺ���Ա�˺� ����ɣ�
void file_readUser();//��ȡ����Ա��Ϣ(���) 
void operation(int way,char *information);//������ 
void operation2(int newnum,int newload);//��������·�̣� 
void addnstart();//���Ӿ�����������
void amendSceneinfor(int num,char *infor);//���޸���Ϣ�� 
void amendload(int amendnum,int x,int load);//���޸�Ȩ�أ�
void amendScenename(int num,char *name); 
