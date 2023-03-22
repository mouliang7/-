#include<stdio.h>
#include<Windows.h>
#include<string.h>

void gotoxy(int x, int y) 
{
    COORD coord = {x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
//打印格子用
void printf_cell(int x,int y,char z)
{
    gotoxy(x,y);  printf("_______");
    gotoxy(x,y+1);printf("|  %c  |",z);
    gotoxy(x,y+2);printf("|_____|");
    
}
//打印菜单
void printf_menu(void)
{
    gotoxy(1,1);    printf("|_______________________________________|\n");
    gotoxy(1,2);    printf("|                                       |\n");
    gotoxy(1,3);    printf("|          欢迎使用多功能计算器         |\n");//打印出来是对齐的，不明原因
    gotoxy(1,4);    printf("|_______________________________________|\n");
    gotoxy(1,5);    printf("|                                       |\n");
    gotoxy(1,6);    printf("|                    042230315 罗朋亮   |\n");
    gotoxy(1,7);    printf("|_______________________________________|\n");
    gotoxy(1,8);    printf("|                                       |\n");
    gotoxy(1,9);    printf("| ___ ___ ___ ___ ___ ___ ___ ___ ___ __|\n");
    gotoxy(1,10);   printf("|_______________________________________|\n");
    gotoxy(1,11);   printf("|                                       |\n");
    gotoxy(1,12);   printf("|                                       |\n");
    gotoxy(1,13);   printf("|                                       |\n");
    gotoxy(1,14);   printf("|                                       |\n");
    gotoxy(1,15);   printf("|                                       |\n");
    gotoxy(1,16);   printf("|                                       |\n");
    gotoxy(1,17);   printf("|                                       |\n");
    gotoxy(1,18);   printf("|                                       |\n");
    gotoxy(1,19);   printf("|                                       |\n");
    gotoxy(1,20);   printf("|                                       |\n");
    gotoxy(1,21);   printf("|                                       |\n");
    gotoxy(1,22);   printf("|                                       |\n");
    gotoxy(1,23);   printf("|_______________________________________|\n");
    int i,j,z;
    char arr[16]={"987x654-321+0= /"};
    for(i=3,j=11,z=0;z<16;i+=10,z++)//循环打印~，会比一行一行写省点劲
    {
        printf_cell(i,j,arr[z]);
        if(i==33)
        {
            i=-7;
            j+=3;
        }
    }
}
//判断字数是否为数字或'.'
int is_num(char op)
{
    if((op>='0')&&(op<='9'))
        return 1;
    else if (op=='.')
        return 2;
    else
        return 0;
}
//判断字符是否为+-*/
int is_operation(char op)
{
    if((op=='+')||(op=='-')||(op=='*')||(op=='/'))
        return 1;
    else 
        return 0;
}
//判断字符是否为()[]{},并对左右括号进行区分
int is_brack(char op)
{
    if((op=='(')||(op=='[')||(op=='{'))
        return 1;
    else if((op==')')||(op==']')||(op=='}'))
        return -1;
    else
        return 0;
}
//判断+-*/优先级
int priority(char op)
{
    if((op=='+')||(op=='-'))
        return 1;
    else if((op=='*')||(op=='/'))
        return 2;
    else if(is_brack(op)==1)
        return 0;
    else
        return -1;
}
//改变evalpost形参中指针所用
//返回指针应偏移值
int pointer_move(int* i)
{
    int z=0;
	while (((char)*i!='\32')&&((char)*i!='\0'))
    {
        if(is_operation((char)*i)==1)
        {
            i = (int*)((char*)(i) + 1);
            z+=2;
            break;
        }
        if (is_num((char)*i)!= 0)
        {
            i = (int*)((char*)(i) + 1);
            z++;
        }
    }
    z++;
    return z;
}
//因为scanf不能输入空格，故用getchar实现
//同时具有检错的功能
void My_scanf(char e[])
{
    //123分别代表()[]{}
    int i,left1=0,left2=0,left3=0,right1=0,right2=0,right3=0;
    char rece;
    for(i=0; ;i++)
    {
        rece=getchar();
        if(rece=='\n')
            break;
        if((i==0)&&((rece=='*')||(rece=='/')))
        {
            printf("输入错误(*或/前无参数)\n");
            exit(1);
        }
        //准备进行检错模块编写
        if(rece=='(')
            left1++;
        if(rece=='[')
            left2++;
        if(rece=='{')
            left3++;
        if(rece==')')
            right1++;
        if(rece==']')
            right2++;
        if(rece=='}')
            right3++;
        e[i]=rece;
    }
    //括号不成对错误
    if((left1!=right1)||(left2!=right2)||(left3!=right3))
    {
        printf("输入错误(*或/前无参数)\n");
        exit(1);
    }
}
//字符串预处理,g[]输入，e[]输出,
void zhuanhuan(char g[],char e[])
{
    int i,j;
    for(i=0,j=0;g[i]!='\0';i++,j++)
    {
        if((i==0)&&((g[i]=='+')||(g[i]=='-')))
        {
            e[j]='0';
            e[j+1]=g[i];
            j++;
            continue;
        }
        if(((g[i]=='+')||(g[i]=='-'))&&(((g[i-1])<'0')||((g[i-1])>'9')))//+-前无数字则在前一位加一个0
        {
            e[j]='0';
            e[j+1]=g[i];
            j++;
            continue;
        }

        e[j]=g[i];
    }
}
//中缀表达式转后缀表达式
void postfix(char e[],char f[])
{
    int i,j,k;//分别e f tmp数组使用
    char tmp[100];
    memset(tmp,'\0',100);

    for(i=0,j=0,k=0;e[i]!='\0';i++)
    {
        if(is_num(e[i])!=0)//压数字和小数点(因为char存不了浮点数)
        {
            f[j]=e[i];
            j++;
            continue;
        }
        
        if(is_operation(e[i])==1)//+-*/压栈
        {
            f[j]='\32';
            j++;
            if(k==0)
            {
                tmp[k]=e[i];
                k++;
                continue;
            }
            else if(priority(tmp[k-1])>=priority(e[i]))//栈顶优先级低则将其弹出
            {
                f[j]=tmp[k-1];
                f[j+1]='\32';
                j+=2;
                tmp[k-1]=e[i];
                continue;
            }
            else
            {
                tmp[k]=e[i];
                k++;
                continue;
            }
        }

        if(is_brack(e[i])==1)//左括号直接压入栈
        {
            f[j]='\32';
            j++;
            tmp[k]=e[i];
            k++;
            continue;
        }

        if(is_brack(e[i])==-1)//右括号应该将括号内运算符弹出
        {
            f[j]='\32';
            j++;
            for(;is_brack(tmp[k-1])!=1;k--)
            {
                f[j]='\32';
                j++;
                f[j]=tmp[k-1];
                tmp[k-1]='\0';
                f[j+1]='\32';
                j+=2;
            }
            k--;
            tmp[k]='\0';
        }
    }
    for(;k>0;k--)
    {
        f[j]='\32';
        j++;
        f[j]=tmp[k-1];
        f[j+1]='\32';
        j+=2;
    }
}
//输出x^n
double My_pow(double x,int n)
{
    double result=1.0;
	int i;
    if(n==0)
        return 1;
    if((x==0)||(x==1))
    {
        result=x;
        return result;
    }
    for(i=1;i<=n;i++)
    {
        result*=x;
    }
    return result; 
}
//将后缀表达式char数组中浮点数转换出来并对+-*/识别
double readnum(char f[], int* i)
{
    //zs,z分别用于整数存储与计数//xs,x用于小数存储与计数//flag用于是否有小数的判断
    int zs[100] = { 0 }, xs[100] = { 0 }; 
    int z = 0, x = 0, flag = 0,zl=0;
    double result = 0.0;
    i = (int*)((char*)(i));//char*必须先转换成int*，如此强转是为了让偏移量+1而不是+4
    while (1)
    {
        if (is_num((char)*i) == 1)
        {
            if (flag == 0)//整数部分
            {
                zs[z] = (char)*i-'0';//强转成(char)才会给出正确值
                i = (int*)((char*)(i) + 1);
                z++;
                continue;
            }
            if (flag == 1)//小数部分
            {
                xs[x] = (char)*i-'0';
                i = (int*)((char*)(i) + 1);
                x++;
                continue;
            }
        }
        if (is_num((char)*i) == 2)//读入小数点时置flag于1开始小数部分转换
        {
            i = (int*)((char*)(i) + 1);
            flag = 1;
            continue;
        }
        if ((char)*i == '\32')//等于空格开始转换
        {
            i = (int*)((char*)i + 1);
            int sz;
            if (flag == 0)//仅有整数部分
            {
                for (sz = 0; sz < z; sz++)
                {
                    result += My_pow(10, z - sz - 1) * zs[sz];
                }
                return result;
            }
            if (flag == 1)//整数与小数
            {
                for (sz = 0; sz < z; sz++)
                {
                    result += My_pow(10, z - sz - 1) * zs[sz];
                }
                for (sz = 0; sz < x; sz++)
                {
                    result += My_pow(0.1, sz + 1) * xs[sz];
                }
                return result;
            }
        }
    }
    return result;
}
//计算最终数值
double evalpost(char f[])
{
    double outcome[100];
    memset(outcome,0,100);
    int x;
    int *i=(int*)f;

    for(x=0;((char)*i!='\0');x++)
    {
        if((char)*i=='\32')
    {
        i=(int*)((char*)i+1);
        x--;
        continue;
    }
        if(is_operation((char)*i)==1)//*i指向操作符进行运算
        {
            if((char)*i=='+')
            {
                outcome[x-2]=outcome[x-1]+outcome[x-2];
                outcome[x-1]=0;
                x-=2;
            }
            if((char)*i=='-')
            {
                outcome[x-2]=outcome[x-2]-outcome[x-1];
                outcome[x-1]=0;
                x-=2;
            }
            if((char)*i=='*')
            {
                outcome[x-2]=outcome[x-1]*outcome[x-2];
               outcome[x-1]=0;
                x-=2;
            }
            if((char)*i=='/')
            {
                outcome[x-2]=outcome[x-2]/outcome[x-1];
                outcome[x-1]=0;
                x-=2;
            }
            i=(int*)((char*)i+2);
            continue;
        }
        if(is_num((char)*i)==1)
        {
            outcome[x]=readnum(f,i);
            i=(int*)((char*)i+pointer_move(i));
            continue;
        }
    }
    return outcome[0];
}

void run(char cal1[],char cal2[])
{
    printf_menu();
    fflush(stdin);//scanf前清除缓冲区不然会有问题
    while(getchar()!='\n');
    gotoxy(3,9); My_scanf(cal1);
    zhuanhuan(cal1,cal2);
    memset(cal1,'\0',100);
    postfix(cal2,cal1);
    gotoxy(30,9);printf("=%.2lf",evalpost(cal1));
    Sleep(2000);
    fflush(stdin);//scanf后清除缓冲区不然会有问题
    while(getchar()!='\n');
}

int main()
{
    char cal1[100],cal2[100];
    int caozuo=0;
    do
    {
        memset(cal1,'\0',100);
        memset(cal2,'\0',100);

        system("cls");//防止在其他行输入数字一直存留
        printf_menu();
        gotoxy(3,9); printf("是否使用计算器?");
        gotoxy(18,9);
        scanf("%d",&caozuo);
        switch(caozuo)
        {
            case 1:run(cal1,cal2);break;
            case 0:break;
            default:break;
        }
    }while(caozuo==1);
    
    gotoxy(1,24);printf("已退出\n");
    return 0;
}