#include"head.h"
//删除子句
int RemoveClause(pcnf L,int flag){
    pcNode p;//子句
    plNode q;//文字
    piNode r;//索引
    if(flag>0){
        //先删除子句
        r=L->Index_List[flag].firstz;
        while(r){
            //mark为0,代表子句从这个索引表里删除了
			if(r->p_cnode->mark==0)   r=r->next;
			else{
				r->p_cnode->mark=0;//标记为删除
				r->p_cnode->flag=flag;//标记因为谁而倍删除
				L->claunum--;//子句的个数减少
				r=r->next;
			}
        }
        r=L->Index_List[flag].firstf; //接着删除含有-flag的子句
		while(r){
            //如果已经被删掉了,那就退出,下一个
			if(r->p_cnode->mark==0)  r=r->next;
			else{
                //如果没有删掉,就删除子句的里面的文字
				q=r->p_cnode->firstl;
				while(q){
                    //删除掉里面的文字
					if(q->mark==0)  q=q->next;
					else{
						if(q->l==-flag){
							q->mark=0;
							r->p_cnode->l_count--;
							break;
						}
						q=q->next;
					}
				}
				r=r->next;
			}
		} 
    }
    //如果这个flag是假的,也是一样,只不过二者顺序换一换
    else{
		r=L->Index_List[-flag].firstf;
		while(r){
			if(r->p_cnode->mark==0)   r=r->next;
			else{
				r->p_cnode->mark=0;
				r->p_cnode->flag=flag;
				L->claunum--;
				r=r->next;
			}
		}
		r=L->Index_List[-flag].firstz; 
		while(r){
			if(r->p_cnode->mark==0)  r=r->next;
			else{
				q=r->p_cnode->firstl;
				while(q){
					if(q->mark==0)  q=q->next;
					else{
						if(q->l==-flag){
							q->mark=0;
							r->p_cnode->l_count--;
							break;
						}
						q=q->next;
					}
				}
				r=r->next;
			}
		} 
	}
	
    L->varinum--; 
	return OK;
    //最后文字个数-1
}
//回溯
int AddClause(pcnf L,int flag){
    pcNode p;    //
	plNode q;    //
	piNode r;    //
    if(flag>0){
        //从令其为真的元素开始寻找
        r=L->Index_List[flag].firstz;          
		while(r){
            //如果没有被删除,跳过
			if(r->p_cnode->mark==1)  r=r->next;
			else{
                //已经被删除了,并且是因为回溯的元素删除,那么就:复原
				if(r->p_cnode->flag==flag){
					r->p_cnode->mark=1;
					r->p_cnode->flag=0;
					L->claunum++;
				}
				r=r->next;
			}
		}
        //原来的文字也退回来
        r=L->Index_List[flag].firstf;      
		while(r){
			q=r->p_cnode->firstl;
			while(q){
				if(q->mark==0&&q->l==-flag){
					q->mark=1;
					r->p_cnode->l_count++;
					break;
				}
				q=q->next;
			}
			r=r->next;
		}  
    }
    else{
        r=L->Index_List[flag].firstf;
        while(r){
            if(r->p_cnode->mark==1) r=r->next;
            else{
                if(r->p_cnode->flag==flag){
                    r->p_cnode->mark=1;
                    r->p_cnode->flag=0;
					L->claunum++;
                }
                r=r->next;
            }
        }
        r=L->Index_List[flag].firstz;
        while(r){
            q=r->p_cnode->firstl;
            while(q){
                if(q->mark==0&&q->l==-flag){
					q->mark=1;
					r->p_cnode->l_count++;
					break;
				}
				q=q->next;
            }
            r=r->next;
        }
    }
    L->varinum++;
    return OK;
}
//寻找我们想要的文字
int Findl(pcnf L,SqList &An){
	pcNode p;
	plNode q;
	int i;
	int flag=0; 
	p=L->firstc;
	while(p){
		if(p->mark==1&&p->l_count==1){      //寻找单子句 
			q=p->firstl;
			while(q){
				if(q->mark==1){
					if(q->l>0) 	An.elem[q->l]=1;
					else    An.elem[-(q->l)]=-1;
					return q->l;
				}
				else q=q->next;
			}
		}
		else p=p->next;
	}
	//单子句不存在，就寻找出现次数最多的那个变元
	int *a=(int *)malloc((2*An.length-1)*sizeof(int));     //构建数组a，存储各变元出现的次数
	for(i=0;i<2*An.length-1;i++){
		a[i]=0;
	}
	p=L->firstc; 
	while(p){                //记录各变元出现的次数 
		if(p->mark==0) p=p->next;
		else{
			q=p->firstl;
			while(q){
                //表示已经被删除了,不成立
				if(q->mark==0) q=q->next;
				else{
					if(q->l>0) a[2*(q->l)-1]++;
					else if(q->l<0)    a[2*(-(q->l))]++;
					q=q->next;
				}
			}
			p=p->next;
		}
	} 
    //打个哈希就行了
	for(i=1;i<2*An.length-1;i++){    //找出出现次数的最大值 
		if(a[i]>flag)  flag=a[i];
	} 
	for(i=1;i<2*An.length-1;i++){  //找到变元 
		if(a[i]==flag)  break;
	}
	free(a);
    //这里是判断究竟是TRUE还是FALSE
	if(i%2) {
		An.elem[(i+1)/2]=1;
		 return ((i+1)/2);
	}
	else{
		An.elem[i/2]=-1;
		 return (-(i/2));
	}
}
//寻找空子句
int EmptyClause(pcnf L){
    //指导第一个元素        
	pcNode p=L->firstc;
    //用while循环寻找空子句
	while(p){
		if(p->l_count==0&&p->mark==1) return OK;
		p=p->next;
	}
	return FALSE;
}
//now_l就是上一步表现为真的变量
//如果传的是负数,就代表是假的
int DPLL(pcnf L,SqList &An,int now_l){
    int next_l;//下一个关键字
    //如果L的子句的个数为0,那么这个是成立的
    if(L->claunum==0) return OK;
    else{
        //如果有空子句:把结果抹除,并且返回无解
        if(EmptyClause(L)==OK){
            //处理now
            if(AddClause(L,now_l)!=OK) printf("Fail!\n");
            if(now_l>0) An.elem[now_l]=0;
            else An.elem[-now_l]=0;
            return FALSE;
        }
        //找不到空子句,那就说明这个命题暂时可以解
        else{
            //寻找下一个为真的命题变元
            next_l=Findl(L,An);
            //找不到,那这个命题就是不可以满足的
            if(next_l==0) return FALSE;
            if(RemoveClause(L,next_l)!=OK) printf("Failed!\n");
            //用下一个元素进行化简
            if (DPLL(L,An,next_l)==OK) return OK;
            else{
                //还原到原来的形式
                if(AddClause(L,next_l)!=OK) printf("Failed\n");
				if(RemoveClause(L,-next_l)!=OK) printf("Failed\n");
                //如果找到的next_l可以化简,那么就可以把最后的结果写进去
                //如果不行,看看回来行不行
                if(DPLL(L,An,-next_l)==OK){
					if(next_l>0) An.elem[next_l]=-1;
					else  An.elem[-next_l]=1;
					return OK;
				}
                //如果不能化简,可以近似认为是无解
                else{
                    if(AddClause(L,-next_l)!=OK) printf("Failed!\n");  
                    if(next_l>0) An.elem[next_l]=0;
					else An.elem[-next_l]=0;
                    return FALSE;
                }               
            }            
        }
    }
}