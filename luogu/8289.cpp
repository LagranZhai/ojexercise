#include<iostream>
#include<string>
#include<map>
#include<set>
using namespace std;

map< string,string > de;
set<string> ing;
int check(char x){
	if(x>='A'&&x<='Z')return 1;
	if(x>='0'&&x<='9')return 1;
	if(x>='a'&&x<='z')return 1;
	if(x=='_')return 1;
	return 0;
}
void lookfor(string ss){
	 		int i=0,l=0,r=0;
			string cur;
			int maxI=ss.size();
			while(i!=maxI){
				char x=ss[i]; 
				if(!check(x)){
					r=i;
					if(l==r){
						cout<<ss[i];
						l=i+1;
						i++;
						continue;
					}
		  			cur=ss.substr(l,r-l);
		  			map< string,string > ::iterator myit;
		  			myit=de.find(cur);
		  			if(myit==de.end()){
		  				cout<<cur<<ss[i];
					}
		  			else{
		  				//ing.insert(cur);
		  				string sess=myit->second;
		  				if(ing.find(cur)!=ing.end()){
		  					cout<<cur<<ss[i];
						}
						else{
							ing.insert(cur);
							lookfor(sess);
							cout<<ss[i];
							ing.erase(cur);
						}		  				
					}
					l=i+1;					
				}
				i++;
			}
		r=i;
		if(l==r){
			return;
		}
		cur=ss.substr(l,r-l);
		map< string,string > ::iterator myit;
		myit=de.find(cur);
		if(myit==de.end()){
			cout<<cur;
		}
		else{
			//ing.insert(cur);
			string sess=myit->second;
			if(ing.find(cur)!=ing.end()){
				cout<<cur;
			}
			else{
			ing.insert(cur);
			lookfor(sess);
			ing.erase(cur);
			}	  				
		}	
}
int main(){
	freopen("hack.in", "r", stdin);
	int n=0;

//	map< string,string > de;
	scanf("%d",&n);
	cin.ignore();
//	string nline;
//	getline(cin,nline);
	while(n--){
		//cout<<"1";
		string c;
		getline(cin,c);
		//cout<<c;
		if(c[0]=='#'){
			if(c[1]=='d'){
				int i=8,p=8;
				string key,word;
				while(c[i]!=' '){
					i++;
				}
				i--;
				key=c.substr(8,i-7);
				//cout<<"key:"<<key<<endl;
				i+=2;
				p=c.size()-1;
				word=c.substr(i,p-i+1);
				//cout<<"word"<<word<<endl;
				de.insert(pair < string,string > (key,word));
				cout<<'\n';
		 	}
		 	else{
		 		string des;
		 		int b=7;
		 		while(c[b]!=' '){
		 			b++;
				}
				b--;
				des=c.substr(7,b-6);
				de.erase(des);
				cout<<'\n';
			}
		}
		else{
			lookfor(c);
			cout<<'\n';
		}
	}

	
	fclose(stdin);
	return 0;
}
