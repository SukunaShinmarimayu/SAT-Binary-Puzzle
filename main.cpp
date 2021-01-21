#include"head.h"
using namespace std;
int main(){

    //cout<<"Hello,Wolrd!";
    //return 0;
    pcnf L; //建立cnf的物理存储结构
	SqList An;//建立线性表
	clock_t start, end;//计时的用处             
	double duration;//运行时间的储存器
	char filename[80];//打开的cnf文件的名字
    //下面定义switch语句的变元
    int op=1;// 总菜单
    int op_1=1;//对于SAT问题的菜单
    int op_2=1;//对于Puzzle问题的菜单
    int tag=1;
    int n;//n是维数
    while(op){
        //进入第一个菜单,用户决定是就进行一个简单的求解还是玩儿二进制数独
        printf("\n\n");
	    printf("      Menu for The SAT And Puzzle Sloving Programe \n");
	    printf("------------------------------------------------------\n");
        printf("    	  author:Sukuna CSXJ1902 From HUST\n");
	    printf("    	  1. sat       2. puzzle\n");
	    printf("          0. Exit                   \n");   
	    printf("------------------------------------------------------\n");
	    printf("   Please Choose Your Option[0~2]:");
	    scanf("%d",&op);
        switch(op){  
            //对于SAT的处理
	        case 1:
                op_1=1;
                while(op_1){
                    printf("\n\n");
	        		printf("     Menu for Linear Table On Sequence Structure    \n");
	        		printf("----------------------------------------------------\n");
	        		printf("       1. creatCNF         2. showCNF               \n");
	        		printf("       3. DPLL             4. test                  \n");
	        		printf("       5. prfAnswer        6. ResWrite             \n"); 
	        		printf("       0. Exit                                      \n");
	        		printf("----------------------------------------------------\n");
	        		printf("     Please Choose Your Option[0~6]:\n");
                    scanf("%d",&op_1);
	        		switch(op_1){
	        			case 1:
	        				printf("请输入文件名\n");
	        				scanf("%s",filename);
	        				if(createCNF(&L,filename)==OK) printf("文件创造成功\n");
							else{
								printf("文件创造失败\n");
								getchar();getchar();
								break; 
							} 
	                        if(InitList(L,An)==OK) printf("链表创造成功\n"); 
	                        else{
	                        	printf("链表创造失败\n");
								getchar();getchar();
								break;
							}
							getchar();getchar();
							break; 
						case 2:
							if(showCNF(L)==OK) printf("展示完毕\n");
							else printf("展示失败\n");
							getchar();getchar();
							break;
						case 3:
						    printf("\n开始求解\n");
						    start = clock(); 
	                        if(DPLL(L,An,1)==OK){
	                        	tag=1;
	                        	printf("求解完毕¶\n");
							}
	                        else{
	                        	tag=0;
	                        	printf("无解\n");
							} 
	                        end = clock(); 
	                        duration = ((double)(end - start))/ CLK_TCK*1000 ;
                            printf("运行的时间是:%f\n",duration);
                            getchar();getchar();
                            break;
                        case 4:
                        	if(test(L,An)==TRUE) printf("测试完毕\n");
                        	else printf("测试失败\n");
							getchar();getchar();
                            break;
						case 5:
						    printf("\n求解SAT问题的解:\n");
						    for(int i=1;i<An.length;i++){
						    	if(An.elem[i]==-1)  printf("%5d",-i);
						    	else printf("%5d",i);
						    	if(i%10==0)  printf("\n");
	                        }
	                        getchar();getchar();
                            break;
                        case 6:
                        	printf("\n写入解答中\n");
                        	if(ResWrite_1(tag,duration,An,filename)==OK) printf("写入成功");
                        	else printf("Ω写入失败\n");
                        	getchar();getchar();
                            break;
                        case 0:
						    break; 
					}
                }
                break;
            //对于puzzle游戏的处理
            case 2:
                op_2=1;
	        	while(op_2){
	        		system("cls");	printf("\n\n");
	        		printf("     Menu for Linear Table On Sequence Structure    \n");
	        		printf("----------------------------------------------------\n");
	        		printf("       1. WriteCNF         2. createCNF             \n");
	        		printf("       3. DPLL             4. test                  \n");
	        		printf("       5. prfAnswer        6. ResWrite              \n"); 
	        		printf("       0. Exit                                      \n");
	        		printf("----------------------------------------------------\n");
	        		printf("     Please Choose Your Option[0~6]:\n");
	        		scanf("%d",&op_2);
                    switch(op_2){
                        //将二进制数独转化成cnf的文件
                        case 1:
	        				printf("请输入写入的文件(保存二进制数独)的名字\n");
	        				scanf("%s",filename);
                            printf("请输入写入的文件(保存二进制数独)的维数\n");
	        				scanf("%d",n);
	        				if(WriteCNF(filename,n)==OK)  printf("写入文件成功\n");
							else printf("写入文件失败\n"); 
							getchar();getchar();
							break; 
						case 2:
							if(createCNF(&L,filename)==OK) printf("创建成功\n");
							else{
								printf("cnf创建失败\n");
								getchar();getchar();
								break; 
							} 
	                        if(InitList(L,An)==OK) printf("初始化成功\n"); 
	                        else{
	                        	printf("初始化失败\n");
								getchar();getchar();
								break;
							}
							getchar();getchar();
							break; 
						case 3:
						    start = clock(); 
	                        if(DPLL(L,An,1)==OK){
	                        	tag=1;
	                        	printf("完成\n");
							}
	                        else{
	                        	tag=0;
	                        	printf("失败\n"); 
							}
	                        end = clock(); 
	                        duration = ((double)(end - start))/ CLK_TCK*1000 ;
                            printf("时间是%f\n",duration);
                            getchar();getchar();
                            break;
                        case 4:
                        	printf("\n测试开始\n");
                        	if(test(L,An)==TRUE) printf("成功\n");
                        	else printf("失败\n");
							getchar();getchar();
                            break;
						case 5:
						    printf("\nAnswer:\n");
						    for(int i=1;i<An.length;i++){
						    	if(An.elem[i]==-1)  printf("0 ");
						    	else printf("1 ");
						    	if(i%6==0)  printf("\n");
	                        }
	                        getchar();getchar();
                            break;
                        case 6:
                        	printf("\nResWrite\n");
                        	if(ResWrite_2(tag,duration,An,filename)==OK) printf("写入成功\n");
                        	else printf("写入失败\n");
                        	getchar();getchar();
                            break;
                    }
                }
                break;
            case 0:
                break;
        }
    }
}