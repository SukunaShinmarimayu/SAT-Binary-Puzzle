#include"head.h"
//数独全部会转化成格子状的物体,标记为1 2 3 4 5 6 7 8 9……
//行列转化公式:i+6*n
int rule_1(char filename[80],int n){
	FILE *fp;
	fp=fopen(filename,"a+");
	if(fp==NULL){
		printf("打开文件失败\n");
		return 0; 
	} 
	int i,j,k;                 //约束1，每一行，每一列，没有连续的三个0或者三个1 
	for(i=1;i<=n;i++){             //每一行 考虑 
		for(j=1;j<=n/2+1;j++){
			for(k=0;k<=2;k++){
				fprintf(fp,"%d ",(i-1)*n+j+k);      
			}
			fprintf(fp,"0\n"); 
			for(k=0;k<=2;k++){
				fprintf(fp,"%d ",-((i-1)*n+j+k)); 
			}
			fprintf(fp,"0\n");
		}
	}
	for(j=1;j<=n;j++){            //每一列考虑 
		for(i=1;i<=n/2+1;i++){
			for(k=0;k<=2;k++){
				for(k=0;k<=2;k++){
				fprintf(fp,"%d ",(i-1)*n+j+k*n);
			}
			fprintf(fp,"0\n"); 
			for(k=0;k<=2;k++){
				fprintf(fp,"%d ",-((i-1)*n+j+k*n)); 
			}
			fprintf(fp,"0\n");
			}
		}
	}
    fclose(fp);
	return OK; 
} //此时，子句数为96个，变元为1~36 
void DFS(FILE*fp,int a[],int n,int count,int r){
    if(count==n/2+1){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(a[j]) fprintf(fp,"%d ",(i)*n+j-1);
            }
        }
        fprintf(fp,"0\n");
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(a[j]) fprintf(fp,"%d ",-(i)*n+j-1);
            }
        }
        fprintf(fp,"0\n");
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(a[i]) fprintf(fp,"%d ",(i)*n+j-1);
            }
        }
        fprintf(fp,"0\n");
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(a[i]) fprintf(fp,"%d ",-(i)*n+j-1);
            }
        }
        fprintf(fp,"0\n");        
    }
    a[r]=1;
    DFS(fp,a,n,count+1,r+1);
    a[r]=0;
    DFS(fp,a,n,count,r+1);
}
int rule_2(char filename[80],int n){      //约束2，每一行 ，每一列的0与1数目相等（=3），即任意4个单元，不全为0，不全为1 
    FILE *fp;
	fp=fopen(filename,"a+");
	if(fp==NULL){
		printf("打开文件失败\n");
		return 0; 
	} 
	int a[n];
    for(int i=0;i<n;i++){
        a[i]=0;
    }
    DFS(fp,a,n,0,0);
	fclose(fp);
	return OK; 
}
void DFS(FILE*fp,int a[],int n,int count,int r,int choose){
    if(count==choose){
        for(int i=1;i<n;i++){
            for(int j=i+1;j<n;j++){
                for(int k=0;k<n;k++){
                    if(a[k]) {
                        fprintf(fp,"%d ",-(i)*n+k-1);
                        fprintf(fp,"%d ",-(j)*n+k-1);
                    }
                    else{
                        fprintf(fp,"%d ",(i)*n+k-1);
                        fprintf(fp,"%d ",(j)*n+k-1);
                    }
                }
                fprintf(fp,"0\n");
            }
        }
        for(int i=1;i<n;i++){
            for(int j=i+1;j<n;j++){
                for(int k=0;k<n;k++){
                    if(a[k]) {
                        fprintf(fp,"%d ",-k*n+i-1);
                        fprintf(fp,"%d ",-k*n+j-1);
                    }
                    else {
                        fprintf(fp,"%d ",k*n+i-1);
                        fprintf(fp,"%d ",k*n+j-1);
                    }
                }
                fprintf(fp,"0\n");
            }
        }
    }
    a[r]=1;
    DFS(fp,a,n,count+1,r+1,choose);
    a[r]=0;
    DFS(fp,a,n,count,r+1,choose);
}
int rule_3(char filename[80],int n){                //约束三，没有两行，两列相同 
    FILE *fp;
	fp=fopen(filename,"a+");
	if(fp==NULL){
		printf("打开文件失败\n");
		return 0; 
	} 
    int a[n];
    for(int i=0;i<n;i++){
        a[i]=0;
    }
	for(int i=0;i<n;i++){
        DFS(fp,a,n,0,0,i);
    }
	fclose(fp);
	return OK;
}