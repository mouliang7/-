#include<stdio.h>
#include<Windows.h>
#include<string.h>
//ָ��λ�ô�ӡ����
void gotoxy(int x, int y)
{
    COORD coord = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
//��ӡ������
void printf_cell(int x, int y, char z)
{
    gotoxy(x, y);  printf("_______");
    gotoxy(x, y + 1); printf("|  %c  |", z);
    gotoxy(x, y + 2); printf("|_____|");

}
//��ӡ�˵�
void printf_menu(void)
{
    gotoxy(1, 1);    printf("|_______________________________________|\n");
    gotoxy(1, 2);    printf("|                                       |\n");
    gotoxy(1, 3);    printf("|          ��ӭʹ�ö๦�ܼ�����         |\n");//��ӡ�����Ƕ���ģ�������Ӣ��ռ���Ȳ�һ��
    gotoxy(1, 4);    printf("|_______________________________________|\n");
    gotoxy(1, 5);    printf("|                                       |\n");
    gotoxy(1, 6);    printf("|                    042230315 ������   |\n");
    gotoxy(1, 7);    printf("|_______________________________________|\n");
    gotoxy(1, 8);    printf("|                                       |\n");
    gotoxy(1, 9);    printf("| ___ ___ ___ ___ ___ ___ ___ ___ ___ __|\n");
    gotoxy(1, 10);   printf("|_______________________________________|\n");
    gotoxy(1, 11);   printf("|                                       |\n");
    gotoxy(1, 12);   printf("|                                       |\n");
    gotoxy(1, 13);   printf("|                                       |\n");
    gotoxy(1, 14);   printf("|                                       |\n");
    gotoxy(1, 15);   printf("|                                       |\n");
    gotoxy(1, 16);   printf("|                                       |\n");
    gotoxy(1, 17);   printf("|                                       |\n");
    gotoxy(1, 18);   printf("|                                       |\n");
    gotoxy(1, 19);   printf("|                                       |\n");
    gotoxy(1, 20);   printf("|                                       |\n");
    gotoxy(1, 21);   printf("|                                       |\n");
    gotoxy(1, 22);   printf("|                                       |\n");
    gotoxy(1, 23);   printf("|_______________________________________|\n");
    int i, j, z;
    char arr[17] = { "987x654-321+0= /" };
    for (i = 3, j = 11, z = 0; z < 16; i += 10, z++)//ѭ����ӡ~�����һ��һ��дʡ�㾢
    {
        printf_cell(i, j, arr[z]);
        if (i == 33)
        {
            i = -7;
            j += 3;
        }
    }
}
//�ж������Ƿ�Ϊ���ֻ�'.'
//���ַ���1��'.'����2�����෵��0
int is_num(char op)
{
    if ((op >= '0') && (op <= '9'))
        return 1;
    else if (op == '.')
        return 2;
    else
        return 0;
}
//�ж��ַ��Ƿ�Ϊ+-*/
//�����������1�����򷵻�0
int is_operation(char op)
{
    if ((op == '+') || (op == '-') || (op == '*') || (op == '/'))
        return 1;
    else
        return 0;
}
//�ж��ַ��Ƿ�Ϊ()[]{},�����������Ž�������
//�����ŷ���1�������ŷ���-1�����෵��0
int is_brack(char op)
{
    if ((op == '(') || (op == '[') || (op == '{'))
        return 1;
    else if ((op == ')') || (op == ']') || (op == '}'))
        return -1;
    else
        return 0;
}
int Is_Brack_Kind(char in)
{
    if ((in == '(') || (in == ')'))
        return 1;
    if ((in == '[') || (in == ']'))
        return 2;
    if ((in == '{') || (in == '}'))
        return 3;
    return 0;
}
//�ж�+-*/���ȼ�
//+-����1��/*����2�����ŷ���0������-1
int priority(char op)
{
    if ((op == '+') || (op == '-'))
        return 1;
    else if ((op == '*') || (op == '/'))
        return 2;
    else if (is_brack(op) == 1)
        return 0;
    else
        return -1;
}
//�ı�evalpost�β���ָ������
//����ָ��Ӧƫ��ֵ
int pointer_move(int* i)
{
    int z = 0;
    while (((char)*i != ' ') && ((char)*i != '\0'))
    {
        if (is_operation((char)*i) == 1)
        {
            i = (int*)((char*)(i)+1);
            z += 2;
            break;
        }
        if (is_num((char)*i) != 0)
        {
            i = (int*)((char*)(i)+1);
            z++;
        }
    }
    z++;
    return z;
}
//��Ϊscanf��������ո񣬹���getcharʵ��
//ͬʱ���м��Ĺ���
void My_scanf(char e[])
{
    //123�ֱ����()[]{}
    int i, left1 = 0, left2 = 0, left3 = 0, right1 = 0, right2 = 0, right3 = 0;
    //��������˳����ж�
    //()֮�䲻����{}[]�Ĵ��ڣ�[]�䲻����{}�Ĵ���
    int Brack1_Flag = 0, Brack2_Flag = 0;
    char rece;
    for (i = 0; ; i++)
    {
        rece = getchar();
        if (rece == '\n')
            break;
        if (Brack1_Flag == 1)
        {
            if ((Is_Brack_Kind(rece) == 2) || (Is_Brack_Kind(rece) == 3))
            {
                gotoxy(30, 9); gotoxy(30, 9); printf("�����������\n");
                exit(1);
            }
        }
        else if (Brack2_Flag == 1)
        {
            if (Is_Brack_Kind(rece) == 3)
            {
                gotoxy(30, 9); gotoxy(30, 9); printf("�����������\n");
                exit(1);
            }
        }
        //�����޹ط��ű���
        if ((is_num(rece) == 0) && (is_brack(rece) == 0) && (is_operation(rece) == 0) && (rece != ' '))
        {
            gotoxy(30, 9); printf("�����޹ط���\n");
            exit(1);
        }
        //�Բ�ͬ�����������Ž��м���
        //�����ŵ�����Ӧ����ڵ�������������
        //left/right1 ���ڼ���() 2���ڼ���[] 3���ڼ���{}
        if (rece == '(')
        {
            left1++;
            Brack1_Flag = 1;
        }
        if (rece == '[')
        {
            left2++;
            Brack2_Flag = 1;
        }
        if (rece == '{')
            left3++;
        //�����ż���ͬʱ���������жϣ�������������������ϵ˵��˳�����
        if (rece == ')')
        {
            right1++;
            Brack1_Flag = 0;
            if (left1 < right1)
            {
                gotoxy(30, 9); gotoxy(30, 9); printf("�����������\n");
                exit(1);
            }
        }
        if (rece == ']')
        {
            right2++;
            Brack2_Flag = 0;
            if (left2 < right2)
            {
                gotoxy(30, 9); printf("�����������\n");
                exit(1);
            }
        }
        if (rece == '}')
        {
            right3++;
            if (left3 < right3)
            {
                gotoxy(30, 9); printf("�����������\n");
                exit(1);
            }
        }
        e[i] = rece;
    }
    e[i] = '\0';
    //���ս��������ж�
    if ((left1 != right1) || (left2 != right2) || (left3 != right3))
    {
        gotoxy(30, 9); printf("�����������\n");
        exit(1);
    }
}
//�ַ���Ԥ����,g[]���룬e[]���
//��Ҫ�����Ǽ��Ͷ���-(+)1+2����ʽ��ת��Ϊ0-(+)1+2
void zhuanhuan(char g[], char e[])
{
    int i, j;
    for (i = 0, j = 0; g[i] != '\0'; i++, j++)
    {
        if (g[i] == ' ')
            continue;
        //-1/+1ת��Ϊ0-1/0+1
        //i=0��g[i]=+/-ʱ�����ж��Ҳ��ڵ�һ��λ����0
        if ((i == 0) && ((g[i] == '+') || (g[i] == '-')))
        {
            e[j] = '0';
            e[j + 1] = g[i];
            j++;
            continue;
        }
        //+-�����ж��Ƿ����
        if ((i != 0) && ((g[i] == '+') || (g[i] == '-')))
        {
            //+-������ĩβ
            if (g[i + 1] == '\0')
            {
                gotoxy(30, 9); printf("*/ǰ����ִ���\n");
                exit(1);
            }
            //+-�ұ߲���ʱ������
            if (is_brack(g[i + 1] == -1))
            {
                gotoxy(30, 9); printf("+-����ִ���\n");
                exit(1);
            }
            //��߲�����������
            else if ((g[i - 1] < '0') || (g[i - 1] > '9'))
            {
                if (is_brack(g[i - 1]) != -1)
                {
                    gotoxy(30, 9); printf("+-ǰ����ִ���\n");
                    exit(1);
                }
            }
        }
        //+-ǰ�����ֲ��Ҳ�������������ǰһλ��һ��0
        if (((((g[i] == '+') || (g[i] == '-')) && (((g[i - 1]) < '0') || ((g[i - 1]) > '9')))) && (is_brack(g[i - 1]) != -1))
        {
            e[j] = '0';
            e[j + 1] = g[i];
            j++;
            continue;
        }
        //*/ǰ������в���,i=0�ж��������
        if ((i == 0) && ((g[i] == '*') || (g[i] == '/')))
        {
            gotoxy(30, 9); printf("*/ǰ����ִ���\n");
            exit(1);
        }
        if ((i != 0) && ((g[i] == '*') || (g[i] == '/')))
        {
            //*/��߲����������ţ��ұ߲���ʱ������
            if ((is_brack(g[i - 1]) == 1) || (is_brack(g[i + 1] == -1)))
            {
                gotoxy(30, 9); printf("*/ǰ����ִ���\n");
                exit(1);
            }
            //*/���ܷ�ĩβ
            if (g[i + 1] == '\0')
            {
                gotoxy(30, 9); printf("*/ǰ����ִ���\n");
                exit(1);
            }
        }
        //�޴�ʱת��
        e[j] = g[i];
    }
}
//��׺���ʽת��׺���ʽ
void postfix(char e[], char f[])
{
    int i, j, k;//�ֱ�e f tmp����ʹ��
    char tmp[100];
    memset(tmp, '\0', 100);

    for (i = 0, j = 0, k = 0; e[i] != '\0'; i++)
    {
        if (is_num(e[i]) != 0)//ѹ���ֺ�С����(��Ϊchar�治�˸�����)
        {
            f[j] = e[i];
            j++;
            continue;
        }

        if (is_operation(e[i]) == 1)//+-*/ѹջ
        {
            f[j] = ' ';
            j++;
            if (k == 0)
            {
                tmp[k] = e[i];
                k++;
                continue;
            }
            else if (priority(tmp[k - 1]) >= priority(e[i]))//ջ�����ȼ��ͻ���ͬ���䵯��
            {
                while (priority(tmp[k - 1]) >= priority(e[i]))
                {
                    f[j] = tmp[k - 1];
                    tmp[k - 1] = ' ';
                    k--;
                    f[j + 1] = ' ';
                    j += 2;
                }
                k++;
                tmp[k - 1] = e[i];
                continue;
            }
            else//����ʹ���
            {
                tmp[k] = e[i];
                k++;
                continue;
            }
        }

        if (is_brack(e[i]) == 1)//������ֱ��ѹ��ջ
        {
            f[j] = ' ';
            j++;
            tmp[k] = e[i];
            k++;
            continue;
        }

        if (is_brack(e[i]) == -1)//������Ӧ�ý����������������
        {
            f[j] = ' ';
            j++;
            for (; is_brack(tmp[k - 1]) != 1; k--)
            {
                f[j] = ' ';
                j++;
                f[j] = tmp[k - 1];
                tmp[k - 1] = '\0';
                f[j + 1] = ' ';
                j += 2;
            }
            k--;
            tmp[k] = '\0';
        }
    }
    //��������ջ�������ȫ������
    for (; k > 0; k--)
    {
        f[j] = ' ';
        j++;
        f[j] = tmp[k - 1];
        f[j + 1] = ' ';
        j += 2;
    }
}
//���x^n
double My_pow(double x, int n)
{
    double result = 1.0;
    int i;
    if (n == 0)
        return 1;
    if ((x == 0) || (x == 1))
    {
        result = x;
        return result;
    }
    for (i = 1; i <= n; i++)
    {
        result *= x;
    }
    return result;
}
//����׺���ʽchar�����и�����ת����������+-*/ʶ��
double readnum(char f[], int* i)
{
    //zs,z�ֱ����������洢�����//xs,x����С���洢�����//flag�����Ƿ���С�����ж�
    int zs[100] = { 0 }, xs[100] = { 0 };
    int z = 0, x = 0, flag = 0, zl = 0;
    double result = 0.0;
    i = (int*)((char*)(i));//char*������ת����int*�����ǿת��Ϊ����ƫ����+1������+4
    while (1)
    {
        if (is_num((char)*i) == 1)
        {
            if (flag == 0)//��������
            {
                zs[z] = (char)*i - '0';//ǿת��(char)�Ż������ȷֵ
                i = (int*)((char*)(i)+1);
                z++;
                continue;
            }
            if (flag == 1)//С������
            {
                if ((is_num((char)*((char*)(i) + 1))!=1) || (is_num((char)*((char*)(i) - 1))!=1))
                {
                    printf("С���������\n");
                    exit(1);
                }
                xs[x] = (char)*i - '0';
                i = (int*)((char*)(i)+1);
                x++;
                continue;
            }
        }
        if (is_num((char)*i) == 2)//����С����ʱ��flag��1��ʼС������ת��
        {
            i = (int*)((char*)(i)+1);
            flag = 1;
            continue;
        }
        if (((char)*i == ' ') || ((char)*i == '\0'))//���ڿո�ʼת��
        {
            i = (int*)((char*)i + 1);
            int sz;
            if (flag == 0)//������������
            {
                for (sz = 0; sz < z; sz++)
                {
                    result += My_pow(10, z - sz - 1) * zs[sz];
                }
                return result;
            }
            if (flag == 1)//������С��ת��
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
//����������ֵ
double evalpost(char f[])
{
    double outcome[100];
    memset(outcome, 0, 100);
    int* i = (int*)f;

    for (int x = 0; ((char)*i != '\0'); x++)
    {
        if ((char)*i == ' ')
        {
            i = (int*)((char*)i + 1);
            x--;
            continue;
        }
        if (is_operation((char)*i) == 1)//*iָ���������������
        {
            if ((char)*i == '+')
            {
                outcome[x - 2] = outcome[x - 1] + outcome[x - 2];
                outcome[x - 1] = 0;
                x -= 2;
            }
            if ((char)*i == '-')
            {
                outcome[x - 2] = outcome[x - 2] - outcome[x - 1];
                outcome[x - 1] = 0;
                x -= 2;
            }
            if ((char)*i == '*')
            {
                outcome[x - 2] = outcome[x - 1] * outcome[x - 2];
                outcome[x - 1] = 0;
                x -= 2;
            }
            if ((char)*i == '/')
            {
                outcome[x - 2] = outcome[x - 2] / outcome[x - 1];
                outcome[x - 1] = 0;
                x -= 2;
            }
            i = (int*)((char*)i + 2);
            continue;
        }
        if (is_num((char)*i) == 1)
        {
            outcome[x] = readnum(f, i);
            i = (int*)((char*)i + pointer_move(i));
            continue;
        }
    }
    return outcome[0];
}
//������Ҫ����
void run(char cal1[], char cal2[])
{
    printf_menu();
    fflush(stdin);//scanfǰ�����������Ȼ��������
    while (getchar() != '\n');
    gotoxy(3, 9); My_scanf(cal1);
    zhuanhuan(cal1, cal2);
    memset(cal1, '\0', 100);
    postfix(cal2, cal1);
    gotoxy(30, 9); printf("=%.2lf", evalpost(cal1));
    fflush(stdin);//scanf�������������Ȼ��������
    while (getchar() != '\n');
}

int main()
{
    char cal1[100], cal2[100];
    int operation = 0;
    //����ṹ
    //do while�ɱ�֤������һ���ӡ���������ж��Ƿ����������
    do
    {
        memset(cal1, '\0', 100);
        memset(cal2, '\0', 100);
        system("cls");//��ֹ����������������һֱ����
        printf_menu();
        gotoxy(3, 9); printf("�Ƿ�ʹ�ü�����?");
        gotoxy(18, 9);
        scanf("%d", &operation);
        switch (operation)
        {
        case 1:run(cal1, cal2); break;
        case 0:break;
        default:break;
        }
    } while (operation != 0);

    gotoxy(1, 24); printf("���˳�\n");
    return 0;
}