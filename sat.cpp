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
	(*L)->first_c=p;
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
				c=fgetc(fp);
			}
			c=fgetc(fp);
		}
        //第一列是p
		else if(c=='p') {
			while(c!='\n'){
                //快速读入的板子
                //读入第一行
				while(c<'0'||c>'9'){
				    c=fgetc(fp);
			    }
			    while(c>='0'&&c<='9'){        
				    num=num*10;
				    num+=c-'0';
				    c=fgetc(fp);
			    }
                //把这个数字加进去
			    (*L)->vari_num=num;//改变变元的个数
                //申请索引表
				(*L)->Index_List=(inde *)malloc((num+1)*sizeof(inde));     
                //初始化索引表
				for(i=0;i<=num;i++){                  
					(*L)->Index_List[i].first_F=NULL;
					(*L)->Index_List[i].first_T=NULL;
				}
				num=0; 
                //处理掉空格之类的
				while(c<'0'||c>'9'){
				    c=fgetc(fp);
			    }
                //接着输入变元的句子数
				while(c>='0'&&c<='9'){       
				    num=num*10;
				    num+=c-'0';
				    c=fgetc(fp);
			    }
				(*L)->clau_num=num;        
				num=0;  
			}
            //把最后一个换行符去掉
			c=fgetc(fp);
		}
		//这个flag就是统计正负
        //接着是正常的数字或者符号开头的情况
		else if((c>='0'&&c<='9')||(c=='-')){
            //给这个变元开辟新的空间
			q=(lNode *)malloc(sizeof(struct lNode));
			q->mark=1;
			p->first_l=q;
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
							    c=fgetc(fp);
								flag=0;	
							}
                            //快速读入的板子
							num=num*10;
				            num+=c-'0';
				            c=fgetc(fp);
						}
                        //建设索引
						r=(iNode *)malloc(sizeof(struct iNode));
						r->p_cnode=p;
                        //假的,添加:	                        
						if(flag==0){                    
						    q->l=-num;
							r->next=(*L)->Index_List[num].first_F;
							(*L)->Index_List[num].first_F=r;
						}
                        //真的,添加:
						else {                    
							q->l=num;
							r->next=(*L)->Index_List[num].first_T; 
							(*L)->Index_List[num].first_T=r; 
						}
						num=0;//准备读取下一个元素
						k++; 
					}
					c=fgetc(fp);
                    //如果遇到0,就代表着一行已经结束了
					if(c=='0') q->next=NULL;
					else{
						q->next=(lNode *)malloc(sizeof(struct lNode));
						q=q->next; 
						q->mark=1;
					}
				}
				//换行符
				c=fgetc(fp);
			}
			c=fgetc(fp);
			p->l_count=k;//变元个数
			k=0;//初始化
			m++; //子句数目++
			//子句数量少于给定,就继续申请接着来
			if(m<(*L)->clau_num){
				p->next=(cNode *)malloc(sizeof(struct cNode));
				p=p->next;
				p->flag=0;
				p->mark=1;
			}
            //等于给定
			else p->next=NULL;
		}
		else c=fgetc(fp);//在否则,消除其他字符的影响	
	}
	fclose(fp);
	return OK; 
}

//展示CNF文件
int showCNF(pcnf L){
    //空语句
	if(L->clau_num==0){
		printf("cnf是空的\n");
		return OK; 
	}
	pcNode p=L->first_c;
	plNode q=p->first_l;   
	printf("cnf的变元数%dcnf的语句数%d\n",L->vari_num,L->clau_num);
	int i=1;
	int j; 
	while(p){
		if(p->mark==0) p=p->next; 
		else{
            //打印句子的数目和句子有的变元个数
			printf("%d %d",i++,p->l_count);
		    q=p->first_l;
		    j=1;
		    while(q){
		    	if(q->mark==0)  q=q->next;
		    	else{
		    		printf("%d%d   ",j++,q->l);
			        q=q->next;
				}
		    }
		    printf("\n");
		    p=p->next;
		}
	}
	return OK;
}

int InitList(pcnf L,SqList &An){
	An.elem=(int *)malloc((L->vari_num+1)*sizeof(int));
	if(!An.elem) {
		return ERROR;
	};
	An.length=L->vari_num+1;
	for(int i=1;i<An.length;i++){
		An.elem[i]=0;                        
	}
	return OK; 
}