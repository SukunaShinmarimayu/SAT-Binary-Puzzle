#include"head.h"
//创建与CNF对应的文件
int createCNF(pcnf *L,char filename[80]) {
	pcNode p;    //新的句子
	plNode q;    //新的变元
	piNode r;    //新的索引
	int i;        
    //申请空间
	*L=(cnf *)malloc(sizeof(struct cnf));
	p=(cNode *)malloc(sizeof(struct cNode)); 
    //flag和mark设置为0
	p->flag=0;
	p->mark=1;
    //L的第一个语句时p
	(*L)->firstc=p;
	FILE *fp;
	int num=0;
	int k=0;   //变元个数           
	int m=0;   //子句数目          
	int flag;         
	char c;
    //打开文件
	fp=fopen(filename,"r");
	if(fp==NULL){
		printf("文件打开失败\n");
		return 0; 
	}
	fscanf(fp,"%c",&c);  
    //一直读入文件,一直到最后
	while(!feof(fp)){
        //第一行是c,跳过
		if(c=='c'){            
			while(c!='\n'){
				fscanf(fp,"%c",&c);
			}
			fscanf(fp,"%c",&c);	
		}
        //第一行是p
		else if(c=='p') {
			while(c!='\n'){
                //快速读入的板子
                //读入第一行
				while(c<'0'||c>'9'){
				    fscanf(fp,"%c",&c);
			    }
			    while(c>='0'&&c<='9'){        
				    num=num*10;
				    num+=c-'0';
				    fscanf(fp,"%c",&c); 
			    }
                //把这个数字加进去
			    (*L)->varinum=num;//改变变元的个数
                //申请索引表
				(*L)->Index_List=(inde *)malloc((num+1)*sizeof(inde));     
                //初始化索引表
				for(i=0;i<=num;i++){                  
					(*L)->Index_List[i].firstf=NULL;
					(*L)->Index_List[i].firstz=NULL;
				}
				num=0; 
                //处理掉空格之类的
				while(c<'0'||c>'9'){
				    fscanf(fp,"%c",&c);
			    }
                //接着输入变元的句子数
				while(c>='0'&&c<='9'){       
				    num=num*10;
				    num+=c-'0';
				    fscanf(fp,"%c",&c); 
			    }
				(*L)->claunum=num;        
				num=0;  
			}
            //把最后一个换行符去掉
			fscanf(fp,"%c",&c);	
		}
        //接着是正常的数字或者符号开头的情况
		else if((c>='0'&&c<='9')||(c=='-')){
            //给这个变元开辟新的空间
			q=(lNode *)malloc(sizeof(struct lNode));
			q->mark=1;
			p->firstl=q;
            //p的第一个元素就是p
            //一直读入
			while(c!='\n'){
				while(c!='0'){
					while(c!=' '){
                        //先默认这个是正确的
						flag=1; 
						while((c>='0'&&c<='9')||(c=='-')){
							if(c=='-'){
                                //如果是负号的,那就认为是错误的
							    fscanf(fp,"%c",&c);
								flag=0;	
							}
                            //快速读入的板子
							num=num*10;
				            num+=c-'0';
				            fscanf(fp,"%c",&c);  
						}
                        //建设索引
						r=(iNode *)malloc(sizeof(struct iNode));
						r->p_cnode=p;
                        //假的,添加:	                        
						if(flag==0){                    
						    q->l=-num;
							r->next=(*L)->Index_List[num].firstf;
							(*L)->Index_List[num].firstf=r;
						}
                        //真的,添加:
						else {                    
							q->l=num;
							r->next=(*L)->Index_List[num].firstz; 
							(*L)->Index_List[num].firstz=r; 
						}
						num=0;//准备读取下一个元素
						k++; 
					}
					fscanf(fp,"%c",&c);
                    //如果遇到0,就代表着一行已经结束了
					if(c=='0') q->next=NULL;
					else{
						q->next=(lNode *)malloc(sizeof(struct lNode));
						q=q->next; 
						q->mark=1;
					}
				}
				fscanf(fp,"%c",&c);
			}
			fscanf(fp,"%c",&c);
			p->l_count=k;//变元个数
			k=0;//初始化
			m++; //子句数目++
			//子句数量少于给定
			if(m<(*L)->claunum){
				p->next=(cNode *)malloc(sizeof(struct cNode));
				p=p->next;
				p->flag=0;
				p->mark=1;
			}
            //等于给定
			else p->next=NULL;
		}
		else fscanf(fp,"%c",&c);//在否则,消除其他字符的影响	
	}
	fclose(fp);
	return OK; 
}

//展示CNF文件
int showCNF(pcnf L){
    //空语句
	if(L->claunum==0){
		printf("cnf是空的\n");
		return OK; 
	}
	pcNode p=L->firstc;
	plNode q=p->firstl;   
	printf("cnf的变元数%dcnf的语句数%d\n",L->varinum,L->claunum);
	int i=1;
	int j; 
	while(p){
		if(p->mark==0) p=p->next; 
		else{
            //打印句子的数目和句子有的变元个数
			printf("第%d句有%d个文字   ",i++,p->l_count);
		    q=p->firstl;
		    j=1;
		    while(q){
		    	if(q->mark==0)  q=q->next;
		    	else{
		    		printf("第%d个文字为%d   ",j++,q->l);
			        q=q->next;
				}
		    }
		    printf("\n");
		    p=p->next;
		}
		
	}
	return OK;
}

int InitList(pcnf L,SqList &An){//为存储答案的顺序表分配存储空间 
	An.elem=(int *)malloc((L->varinum+1)*sizeof(int));//分配存储空间 
	if(!An.elem) {
		return ERROR;//分配存储空间失败 
	};
	An.length=L->varinum+1;//初始化线性表的长度为0 
	for(int i=1;i<An.length;i++){
		An.elem[i]=0;                        //表示没有经过单子句简化赋值 
		//printf("%d  ",An.elem[i]);                           查看程序运行进度，没有必要打开 
	}
	return OK; 
}