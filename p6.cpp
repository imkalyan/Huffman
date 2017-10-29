#include <bits/stdc++.h>
#include<stdio.h>
#include<string>
#include<stdlib.h>
#include <queue>
using namespace std;
struct Heap
   {
        char ch;
        string code;                
        int freq;             
        Heap *left, *right; 
     
        Heap(char ch, int freq)
        {
            left = right = NULL;
            this->ch=ch;
            this->freq = freq;
        }
    };
     
struct mycompare
    {
        bool operator()(Heap* l, Heap* r)
        {
            return (l->freq > r->freq);
        }
    };


void storecode(struct Heap* head,string s)
{
	if(head==NULL)
		return;
	
	if(head->ch!='`')
		head->code = s;
	else{		
	storecode(head->left,s+"0");
	storecode(head->right,s+"1");	
	}

}
string str="";
void getcode(struct Heap* head,char ch)
{
	if(head==NULL)
		return;
	if(head->ch ==ch){
		str+=head->code;
	}
	getcode(head->left,ch);
	getcode(head->right,ch);

}

Heap* huffmaan()
{
	char ch;
	int A[256],i;
	priority_queue<Heap*, vector<Heap*>, mycompare> minheap;
	 struct Heap *firstmin, *secmin, *temp;
	FILE *fp=fopen("input.txt","r+");
	for(i=0;i<256;i++)
		A[i]=0;	
	while(fscanf(fp,"%c",&ch)!=EOF)
	{
		if(int(ch)>0)
			A[int(ch)]++;
	}
	fclose(fp);
	
	for(i=0;i<256;i++){	
		if(A[int(i)]>0){
			minheap.push(new Heap((char)(i),A[i]));
		}			
	}	 
       do
         {
            
	    firstmin = minheap.top();
            minheap.pop();
     
            secmin = minheap.top();
            minheap.pop();
	    int add1 = firstmin->freq + secmin->freq;
	
            temp = new Heap('`',add1);
            temp->left = firstmin;
            temp->right = secmin;
            minheap.push(temp);
        }while (minheap.size() != 1);
	storecode(minheap.top(),"");
return minheap.top();
}
int bintodec(string s)
{

	int d,b,j;
	b=1;d=0;
	for(j=s.size()-1;j>=0;j--)
	{
		if(s[j]=='1')
		{
	
			d=d+b;
			
		}
		b=b*2;
	}
	return d;
}
int size[1000000];
int count1=0;
void encode(Heap *head)
{
	int i;char ch;
	FILE *fp2=fopen("encode.txt","w+");
	FILE *fp5=fopen("input.txt","r+");
	while(fscanf(fp5,"%c",&ch)==1){
		getcode(head,ch);
	}
	fclose(fp5);
	
	
	int num[8];
	int y;
	
		int j=0;
		for(i=0;i<str.size()/8;i++,j=j+8){
			string su=str.substr(j,8);
			size[count1++]=su.size();
			  y=bintodec(str.substr(j,8));	
		          fprintf(fp2,"%c",(char)(y));
			}
			
			if(str.size()%8!=0){
				string sub=str.substr(str.size()-str.size()%8,str.size());
				size[count1++]=sub.size();
				y=bintodec(str.substr(str.size()-str.size()%8,str.size()));
				fprintf(fp2,"%c",(char)(y));
				}
		fclose(fp2);	
		cout << "encoding..... done"<< "\n" ; 
}
int c=0;
string dectobin(int i,string s3)
{
	
	int d,b,j;
	int a[100],x=0;
	b=1;d=0;
	string l;
	while(i>0)
	{
		int r=i%2;
		i=i/2;
		a[x++]=r;
	}
	if(x<size[c])
	{
		for(j=x;j<size[c];++j)
			a[j]=0;
	
	}
	for(j=size[c]-1;j>=0;j--)
	{
		stringstream ss;
		ss << a[j];
		 l=ss.str();
		s3+=l;
	}
	c++;
	return s3;
}
void traverse(Heap *head,string z){
	Heap *root=head;
	cout << "\n" ;
	FILE *fp=fopen("out.txt","w+");
	for(int y=0;y<z.size();y++)
	{
		if(head==NULL)
			return;
		else{
			if(z[y]=='1'){
				root=root->right;
				if(root->ch!='`'){
					fprintf(fp,"%c",root->ch);
					root=head;		
					}
			}
			else{
				root=root->left;
				if(root->ch!='`'){
					fprintf(fp,"%c",root->ch);
					root=head;		
					}
			}
		}
	}
	fclose(fp);
}

void decode(Heap *head)
{
	string decode="";
	FILE *fp3=fopen("encode.txt","r+");
	char ch;
	FILE *fp4 = fopen("out.txt","w+");
	
	while(fscanf(fp3,"%c",&ch)!=EOF)
	{
		if((int)(ch)<0)
			decode=dectobin((int)(ch)+256,decode);
		else
		 	decode=dectobin((int)(ch),decode);	
		
	}
	cout  << "Decoding...done"<< "\n" ;
	traverse(head,decode);
	fclose(fp3);
	fclose(fp4);
	
}

int main()
{
	Heap *head;
	head=huffmaan();
	encode(head);
	decode(head);
return 0;
}
