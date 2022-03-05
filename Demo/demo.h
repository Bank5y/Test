struct Scene_side_ride;
struct Scenein; 

void FindScene();//按编号寻找 （完成） 
void FindScene_CN();//按名字寻找  （完成） 
void MakeSceneinfor();//初始化校园数据 （完成） 
void MakeMap();//绘制地图 （完成）
void menu();//菜单 （完成） 
void MakeRide();//初始化图数据（完成） 
void Dijkstra(Scene_side_ride &G,int start);//计算最短路径（完成） 
void ShowLoad(int start,int end);//打印最短路径 
void AddScene();//增加景点信息（完成） 
void DeleteScene();//删除景点信息 （完成） 
void amendScene();//修改景点信息 （完成）
void login();//管理员登录（完成） 
void loginmenu();//管理员菜单（完成） 
void loginamend();//修改管理员账号 （完成）
void file_readUser();//读取管理员信息(完成) 
void operation(int way,char *information);//操作集 
void operation2(int newnum,int newload);//操作集（路程） 
void addnstart();//增加景点数计数器
void amendSceneinfor(int num,char *infor);//（修改信息） 
void amendload(int amendnum,int x,int load);//（修改权重）
void amendScenename(int num,char *name); 
