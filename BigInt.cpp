#include<iostream>
using namespace std;
inline int to_int(char c)
{
    return (int)c-48;
}
class BigInteger{
    public:
    string num;
    BigInteger()
    {
        num="";
    }
    BigInteger(string s)
    {
        num=s;
        this->trim();
    }
    string getval()
    {
        return this->num;
    }
    void setval(string val)
    {
        this->num=val;
        this->trim();
    }
    void trim()
    {
        int j=0;
        while(this->num[j]=='0')
            j++;
        this->num=this->num.substr(j,this->num.size()-j);
    }
    string add (BigInteger B)
    {
        string res="";
        this->trim();
        B.trim();
        if(this->num=="" && B.num=="")
            return "0";
        if(B.num=="")
            return this->num;
        if(this->num=="")
            return B.num;
        if(this->num.size()<18 && B.num.size()<18)
        {
            return to_string(stoull(this->num)+stoull(B.num));
        }
        int sz1=this->num.size();
        int sz2=B.num.size();
        int d1=sz1-1;
        int d2=sz2-1;
        int sum=0,carry=0,cur_dig=0;;
        while(d1>=0 && d2>=0)
        {
            sum=to_int(this->num[d1])+to_int(B.num[d2])+carry;
            cur_dig=sum%10;
            res=to_string(cur_dig)+res;
            if(sum>9)
                carry=1;
            else
                carry=0;
            d1--;
            d2--;
        }
        while(d1>=0)
        {
            if(carry==0)
            {
                res=this->num.substr(0,d1+1)+res;
                break;
            }
            sum=to_int(this->num[d1])+carry;
            cur_dig=sum%10;
            res=to_string(cur_dig)+res;
            if(sum>9)
                carry=1;
            else
                carry=0;
            d1--;
        }
        while(d2>=0)
        {
            if(carry==0)
            {
                res=B.num.substr(0,d2+1)+res;
                break;
            }
            sum=to_int(B.num[d2])+carry;
            cur_dig=sum%10;
            res=to_string(cur_dig)+res;
            if(sum>9)
                carry=1;
            else
                carry=0;
            d2--;
        }
        if(carry>0)
            res=to_string(carry)+res;
        return res;
    }
    string sub(BigInteger B)
    {
        this->trim();
        B.trim();
        if(this->num.compare(B.num)==0)
            return "0";
        if(this->num=="" && B.num=="")
            return "0";
        if(B.num=="")
            return this->num;
        string res="";
        int borrow=0;
        int sz1=this->num.size();
        int sz2=B.num.size();
        int d1=sz1-1,d2=sz2-1;
        int num1=0,num2=0;
        BigInteger diff;
        while(d1>=0 && d2>=0)
        {
            num1=to_int(this->num[d1]);
            num2=to_int(B.num[d2]);
            if(borrow==0 && num1>=num2)
            {
                res=to_string(num1-num2)+res;
            }
            else if (borrow==0 && num1<num2)
            {
                borrow=1;
                res=to_string(10+num1-num2)+res;
            }
            else if(borrow==1 && num1>num2)
            {
                res=to_string(num1-num2-borrow)+res;
                borrow=0;
            }
            else
            {
                res=to_string(10+num1-num2-borrow)+res;                
                borrow=1;
            }
            d1--;
            d2--;
        }
        while(d1>=0)
        {

            if(borrow==0)
            {
                res=this->num.substr(0,d1+1)+res;
                break;
            }
            else
            {
                if(to_int(this->num[d1])>0)
                {
                    res=to_string(to_int(this->num[d1])-borrow)+res;
                    borrow=0;
                }
                else
                {
                    res=to_string(10+to_int(this->num[d1])-borrow)+res;
                }
            }
            d1--;
        }
        diff.num=res;
        diff.trim();
        return diff.num;
    }
    string mul(BigInteger B)
    {
        this->trim();
        B.trim();
        if(this->num=="" || B.num=="")
            return "0";
        if(this->num.size()+B.num.size()<19)
        {
            unsigned long long n1=stoull(this->num);
            unsigned long long n2=stoull(B.num);
            n2*=n1;
            return to_string(n2);
        }
        BigInteger res;
        int sz1=0;
        int sz2=0;
        string num1,num2;
        if(this->num.size()>=B.num.size())
        {
            sz1=this->num.size();
            sz2=B.num.size();
            num1=this->num;
            num2=B.num;
        }
        else
        {
            sz1=B.num.size();
            sz2=this->num.size();
            num1=B.num;
            num2=this->num;
        }
        string temp="";
        int mul=1,carry=0,dig=0,prod=0;
        for(int j=sz2-1;j>=0;j--)
        {
            temp="";
            carry=0;
            mul=to_int(num2[j]);
            for(int k=sz1-1;k>=0;k--)
            {
                dig=to_int(num1[k]);
                prod=mul*dig+carry;
                carry=prod/10;
                temp=to_string(prod%10)+temp;
            }
            if(carry>0)
                temp=to_string(carry)+temp;
            for(int p=sz2-1;p>j;p--)
                temp=temp+"0";
            BigInteger btemp(temp);
            res=res.add(btemp);
        }
        return res.num;
    }
    string exponent(unsigned long long x)
    {
        this->trim();
        if(this->num=="" && x==0)
            return "1";
        if(this->num=="")
            return "0";   
        if(x==0)
            return "1";
        BigInteger res("1");
        BigInteger temp(this->num);
        while(x>0)
        {
            if(x&1)
                res.num=res.mul(temp);
            temp.num=temp.mul(temp);
            x=x>>1;
        }
        return res.num;
    }
    string divby2()
    {
        this->trim();
        if(this->num=="1" || this->num=="")
            return "0";
        if(this->num=="2")
            return "1";
        int x=2;
        int len=1,rem=0;
        string qt="";
        for(int p=0;p<this->num.size();p++)
        {
            int d=to_int(num[p]);
            d=rem*10+d;
            if(d>=x)
            {
                qt+=to_string(d/x);
                rem=d%x;
            }
            else if(p+1<this->num.size())
            {
                if(p!=0)
                    qt+="0";
                d=d*10+to_int(num[p+1]);
                d=rem*10+d;
                qt+=to_string(d/x);
                rem=d%x;
                p++;
            }
            else if(d<x && p+1==this->num.size())
                qt+="0";
        }
        return qt;
    }
    void swap(BigInteger *B)
    {
        this->trim();
        B->trim();
        string temp="";
        if(this->num=="")
        {
            this->num=B->num;
            B->num="";
            return;
        }
        if(B->num=="")
            return;
        if((B->num.size()==this->num.size()&&B->num.compare(this->num)<=0)||(B->num.size()<this->num.size()))
        {
            return;
        }
        else
        {
            temp=B->num;
            B->num=this->num;
            this->num=temp;
        }
    }
    string gcd(BigInteger B)
    {
        this->trim();
        B.trim();
        if(this->num=="" && B.num=="")
            return "0";
        BigInteger large(this->num);
        BigInteger small(B.num);
        large.swap(&small);
        string temp;
        int large_last=0,small_last=0,cnt=0;
        while(small.num!="" && small.num!=large.num)
        {
            large_last=to_int(large.num[large.num.size()-1]);
            small_last=to_int(small.num[small.num.size()-1]);
            if(large_last%2==0 && small_last%2==0)
            {
                cnt++;
                large.num=large.divby2();
                small.num=small.divby2();
            }
            else if(large_last%2==0 && small_last%2!=0)
            {
                large.num=large.divby2();
            }
            else if(large_last%2!=0 && small_last%2==0)
            {
                small.num=small.divby2();
            }
            else if(large_last%2!=0 && small_last%2!=0)
            {
                BigInteger diff(large.sub(small));
                diff.trim();
                large.num=diff.divby2();
            }
            large.trim();
            small.trim();
            large.swap(&small);
            if(large.num.compare(small.num)==0)
            {
                break;
            }
        }
        if(cnt>0)
        {
            BigInteger temp("2");
            BigInteger res("");
            res.num=temp.exponent(cnt);
            res.trim();
            res.num=res.mul(large);
            return res.num;
        }
        return large.num;
    }
    string factorial()
    {
        this->trim();
        if(this->num=="" || this->num=="1")
            return "1";
        BigInteger res("1");
        string temp="2";
        BigInteger inc("1");
        string prod="1";
        if(this->num.size()<18)
        {
            unsigned long long num=stoull(this->num);
            unsigned long long resl=1,k=2;
            while (k<999999999 && resl<999999999 && k<=num)
            {
                resl*=k;
                k+=1;
            }
            res.num=to_string(resl);
            if(k==num)
                return res.num;
            temp=to_string(k);
        }
        while((temp.size()==this->num.size()&&temp.compare(this->num)<=0)||(temp.size()<this->num.size()))
        {
            BigInteger temp1(temp);
            if(res.num.size()+temp1.num.size()<18)
                res.num=to_string(stoull(res.num)*stoull(temp1.num));
            else
                res.num=res.mul(temp1);
            temp=temp1.add(inc);
        }
        return res.num;
    }
    
};
string expr_eval(string expr)
{
    expr+="$";
    int op_cnt=0,cur_start=0,opd_ind=0,opr_ind=0;
    string prev_op="";
    for(int j=0;j<expr.size();j++)
        if(expr[j]=='+' || expr[j]=='-' || expr[j]=='x')
            op_cnt++;
    BigInteger operands[op_cnt+1];
    string operators[op_cnt];
    for(int j=0;j<expr.size();j++)
    {
        if (expr[j]=='+' || expr[j]=='-' || expr[j]=='x' || expr[j]=='$')
        {
            operands[opd_ind].setval(expr.substr(cur_start,j-cur_start));
            cur_start=j+1;
            if (prev_op=="x")
            {
                string temp=operands[opd_ind-1].mul(operands[opd_ind]);
                operands[opd_ind].setval("");
                operands[opd_ind-1].setval(temp);
                opd_ind--;
            }
            if(expr[j]!='x' && expr[j]!='$')
            {
                operators[opr_ind++]=expr[j];
            }
            opd_ind++;
            prev_op=expr[j];
        }
    }
    BigInteger res;
    res.setval(operands[0].getval());
    int k=1;
    for(int j=0;j<opr_ind;j++)
    {
        if(operators[j]=="+")
        {   
            res.setval(res.add(operands[k++]));
        }
        else
        {
            res.setval(res.sub(operands[k++]));
        }
    }
    res.trim();
    if(res.getval()=="")
            return "0";
    return res.getval();
}
int main()
{
    int ch;
    cin>>ch;
    switch(ch)
    {
        case 1:
            {
            string num;
            unsigned long long exp;
            cin>>num;
            cin>>exp;
            BigInteger base("");
            base.setval(num);
            string res=base.exponent(exp);
            cout<<res<<endl;
            }
            break;
        case 2:
            {
            string num1,num2;
            cin>>num1>>num2;
            BigInteger A(num1);
            BigInteger B(num2);
            string res=A.gcd(B);
            cout<<res<<endl;
            }
            break;
        case 3:
            {
            string num4;
            cin>>num4;
            BigInteger C(num4);
            cout<<C.factorial()<<endl;
            }
            break;
        case 4:
            {
            string expr="";
            cin>>expr;
            cout<<expr_eval(expr)<<endl;
            }
    }
    return 0;
}