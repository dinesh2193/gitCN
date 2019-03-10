#include<bits/stdc++.h>
using namespace std;
int main()
{
	string ip;
	cout<<"Enter input in binary form:";
	cin>>ip;
	map<int,vector<int> > bit;

	int m = ip.length();
	int r = log2(m)+1;
	r = log2(m+r)+1;
	int len = m+r;
	char msg[len+2];

	for(int i=0;i<=len;i++)
	{
		msg[i]='2';
	}
	msg[len+1]='\0';
	int p=log2(len)+1;
	for(int i=0;i<p;i++)
	{
		vector<int> v;
		bit.insert(make_pair(pow(2,i),v));
	}
	map<int,vector<int> > :: iterator itr;
	int j = 0;
	for(int i=1;i<=len;i++)
	{
		if(bit.find(i)==bit.end())
		{
			msg[i]=ip[j++];
		}
	}
	
	for(itr = bit.begin();itr!=bit.end();itr++)
	{
		int pos = log2(itr->first);
		pos++;
		for(int i=1;i<=len;i++)
		{
			int shift = i;
			for(int j=1;j<pos;j++)
			{
				shift = shift>>1;
			}
			//cout<<shift<<":"<<pos<<endl;
			if(shift&1)
			{
				//cout<<"came="<<i<<":"<<pos<<endl;
				itr->second.push_back(i);
			}
		}
	}

	
	for(itr = bit.begin();itr!=bit.end();itr++)
	{
		int c=0;
		for(int i=1;i<itr->second.size();i++)
		{
			if(msg[itr->second[i]]=='1')c++;
		}
		//cout<<"c:"<<c<<endl;
		if(c%2==0)
		{
			msg[itr->first]='0';
		}
		else
		{
			msg[itr->first]='1';
		}
	}
	
	cout<<msg<<endl;

	int b = rand()%len;
	b++;

	if(msg[b]=='1')msg[b]='0';
	else msg[b]='1';
	cout<<"changed bit is:"<<b<<endl;
	cout<<msg<<endl;
	int sum =0;
	for(itr = bit.begin();itr!=bit.end();itr++)
	{
		int c=0;
		for(int i=0;i<itr->second.size();i++)
		{
			if(msg[itr->second[i]]=='1')c++;
		}
		
		if(c%2==1)
		{
			sum+=(itr->first);
		}
		
	}
	cout<<"correction bit is:"<<sum;

	
}
