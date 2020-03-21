/*
Statement: ​ Your task is to create a large integer library, similar to what
we have in Java as BigInteger. Your library should provide
functionalities to store arbitrarily large integer and perform basic math
operations.
Operations to be implemented​ : Fast exponentiation, GCD of 2
integers and factorial.
*/

#include<bits/stdc++.h>
using namespace std;
#define ll long long int

bool compare(string a,string b)	{
	ll len1,len2,i;
	len1=a.length();
	len2=b.length();
	if(len1!=len2)
		return (len1>len2)?true:false;
	else	{
		for(i=0;i<len1;i++)	{
			if((a[i]-'0') == (b[i]-'0'))
				continue;
			else if((a[i]-'0') > (b[i]-'0'))
				return true;
			else
				return false;
		}
	}
}

string subtract(string a,string b)	{
	string temp="";
	if(compare(a,b)==false)	{
		temp=a;
		a=b;
		b=temp;
	}
	reverse(a.begin(),a.end());
	reverse(b.begin(),b.end());

	string diff="";
	ll i,j,d,carry=0,len1,len2;
	len1=a.length();
	len2=b.length();

	for(i=0;i<len2;i++)	{
		if((a[i]-'0')>=(b[i]-'0'))	{
			d=((a[i]-'0')-(b[i]-'0'))-carry;
			if(d>=0)	{
				carry=0;
			}
			else	{
				d=d+10;
				carry=1;
			}
		}
		else	{
			d=(((a[i]-'0')+10)-(b[i]-'0'))-carry;
			carry=1;
		}
		diff+=to_string(d);
	}
	for(j=i;j<len1;j++)	{
		d=(a[j]-'0')-carry;
		if(d<0)	{
			d+=10;
			carry=1;
		}
		else
			carry=0;

		diff+=to_string(d);
	}
	reverse(diff.begin(),diff.end());
	diff.erase(0, min(diff.find_first_not_of('0'), diff.size()-1));

	return diff;
}


string multiply(string a,string b)	{

	reverse(a.begin(),a.end());
	reverse(b.begin(),b.end());

	ll i,j,len1,len2;
	int flag=0;
	string str="";
	len1=a.length();
	len2=b.length();

	int c[100000]={0};
	
	for(i=0;i<len1;i++)	{
		for(j=0;j<len2;j++)	{
			c[i+j]+=((a[i]-'0')*(b[j]-'0'));
			if((c[i+j])>9)	{
				c[i+j+1]+=(c[i+j]/10);
				c[i+j]=(c[i+j]%10);
			}
			
		}	
	}
	for(i=(len1+len2-1);i>=0;i--)	{
		if(c[i]==0 && flag==0)	{
			continue;
		}
		else	{
			flag=1;
			str+=to_string(c[i]);
		}
	}
	str[len1+len2]='\0';	
	return str;
}

string dividebytwo(string a)	{

	int val[100000]={0};
	ll i,d=0;
	string str="";
	for(i=0;i<a.length();i++)	{
		val[i]+=(a[i]-'0');
		if(val[i]<2)	{
			val[i+1]+=10;
			d=0;
		}
		else	{
			d=val[i]/2;
			if((val[i]%2)!=0)
				val[i+1]+=10;
		}
		str+=to_string(d);
	}
	str.erase(0, min(str.find_first_not_of('0'), str.size()-1));
	return str;

}

string fastexpo(string a,string b)	{
	if(b=="0")
		return "1";
	else if(b=="1")
		return a;
	
	string exp;
	exp=fastexpo(a,dividebytwo(b));
	if((b[b.length()-1]-'0')%2==0)	
		return multiply(exp,exp);
	else
		return multiply(a,multiply(exp,exp));

}

string mygcd(string a,string b)	{
	if(a.empty())
		return b;
	while(b!=a)	{
		if(compare(a,b)==true)
			a=subtract(a,b);
		else if(compare(a,b)==false)
			b=subtract(b,a);
	}
	return a;
}

string factorial(string a)	{
	string fact="1";
	if(a.length()<=1 && a[0]=='1')
		return "1";
	else	{
		return multiply(a,factorial(subtract(a,fact)));
	}
		
}

int main()	{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	ll t;
	int k;
	string s1="",s2="",ans="";
	cin>>t;
	while(t--)	{
		cin>>k;
		if(k==1)	{
			cin>>s1;
			cin>>s2;
			ans=fastexpo(s1,s2);
			cout<<ans<<"\n";
		}
		else if(k==2)	{
			cin>>s1;
			cin>>s2;
			ans=mygcd(s1,s2);
			cout<<ans<<"\n";
		}
		else if(k==3)	{
			cin>>s1;
			ans=factorial(s1);
			cout<<ans<<"\n";
		}
	}
	return 0;
}
