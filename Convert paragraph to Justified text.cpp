//Justified String
string foo(vector<string> &A, int l, int s, int e){
    int len= 0;
    for (int i=s;i<=e;i++) 
        len+=A[i].size();
    if (e==s){
        string ans=A[s];
        while (ans.size()<l) ans+=' ';
        return ans;
    }
    int a= (l-len)/(e-s);
    int b = (l-len)%(e-s);
    string ans="";
    ans+=A[s];
    for (int i=s+1;i<=e;i++){
        for (int j=0; j<a; j++) ans += ' ';
        if (i-(s+1)<b) ans+= ' ';
        ans+=A[i];
    }
    return ans;
}

string foo1(vector<string> &A, int b, int s, int e){
    string q=A[s];
    for (int i=s+1;i<=e;i++){
        q+=' '+A[i]; 
    }
    while (q.size()<b) 
        q+=' ';
    return q;
}

vector<string> Solution::fullJustify(vector<string> &A, int B) {
    vector<string> ans;
    int n=A.size();
    int i=0;
    int start=0;
    int prev=0;
    while (i<n){
        int l1=A[i].size();
        if ((i==start?0:1)+l1+prev>B){
            ans.push_back(foo(A,B,start, i-1));
            start=i;
            prev=l1;
        }
        else
            prev+=l1+((i==start)?0:1);
        i++;
    }
    if (start!=n){
        ans.push_back(foo1(A,B,start, n-1));
    }
    return ans;
}
