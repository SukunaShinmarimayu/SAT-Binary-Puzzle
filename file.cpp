#include"head.h"
//需要更改
int write(char* filename,int n){
    printf("请问你是想调用文件(1)还是让系统随机整一个(2)\n");

    return OK;
}
int WriteCNF(char filename[80],int n){     //将棋盘的初始条件的三个约束，变成cnf公式，写入文件 
	if(write(filename,n)!=OK)  return FALSE;
	if(rule_1(filename,n)!=OK) return FALSE;
	if(rule_2(filename,n)!=OK) return FALSE;
	if(rule_3(filename,n)!=OK) return FALSE;
	return OK;
}
int ResWrite_SAT(int res,double time,SqList &An,char filename[80]){       //Ω´«ÛΩ‚Ω·π˚–¥»ÎŒƒº˛ 
	int i=0;
	while(filename[i]!='\0') i++; 
	filename[i-3]='r';    
	filename[i-2]='e';
	filename[i-1]='s';
    filename[i-1]='.';
	FILE *fp;
	fp=fopen(filename,"w");
	if(fp==NULL){
		printf("打开文件失败\n");
		return ERROR; 
	}
	fprintf(fp,"s %d\n",res);    //res是求解结果，1表示满足，0表示不满足，-1未定
	fprintf(fp,"v \n");
    //把SAT的过程所有结果求进去
    for(i=1;i<An.length;i++){
    	if(An.elem[i]==-1)  fprintf(fp,"%5d",-i);
    	else fprintf(fp,"%5d",i);
    	if(i%10==0)  fprintf(fp,"\n");
	}
	fprintf(fp,"\nt %f ms\n",time);
	fclose(fp);
	return OK;
} 
int ResWrite_BP(int res,double time,SqList &An,char filename[80],int n){       //将求解结果写入文件 
	int i=0,j;
	while(filename[i]!='\0') i++; 
	filename[i-3]='r';    //只改变文件的扩展名 
	filename[i-2]='e';
	filename[i-1]='s';
	FILE *fp;
	fp=fopen(filename,"w");
	if(fp==NULL){
		printf("打开文件失败\n");
		return ERROR; 
	}
    //这个是把结果(数独的求解结果写进去)
	fprintf(fp,"s %d\n",res);    //res是求解结果，1表示满足，0表示不满足，-1未定
	fprintf(fp,"v \n");
    fprintf(fp,"Solve By:Sukuna's Programme\n  ");
    for(i=0;i<n;i++){
    	fprintf(fp,"----------------------------\n  ");
    	for(j=1;j<=n;j++){
    		if(An.elem[n*i+j]==1) fprintf(fp,"1  ");
    		else fprintf(fp,"0  ");
    		if(j!=n) fprintf(fp,"   ");
    		else fprintf(fp,"\n"); 
		}
	}
	fprintf(fp,"----------------------------\n");
	fprintf(fp,"\ntimes: %f ms\n",time);
	fclose(fp);
	return OK;
} 