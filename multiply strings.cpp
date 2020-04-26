//Multiply two strings A and B
string Solution::multiply(string A, string B) {
    string str;
    string str1;
    int q=48;
    str1.push_back(48);
    int carry=0;
    int a=A.length();
    int b=B.length();
    int p=0,n;
    for(int i=(a-1);i>=0;--i){
        n=str1.length();
        p=0;
        while(p<(a-i-1)){
            char z=str1[p];
            str.push_back(z);
            p++;
        }
        int r=A[i]-48;
        for(int j=(b-1);j>=0;--j){
            int l=B[j]-48;
            if(p<=(n-1)){
                q=str1[p]-48;
                p++;
            }
            else
                q=0;
            q+=carry;
            carry=0;
            q+=(l*r);
            if(q>9){
                carry=q/10;
                q=q%10;
            }
            q=q+48;
            str.push_back(q);
        }
        if(carry!=0){
            carry+=48;
            str.push_back(carry);
            carry=0;
        }
        str.swap(str1);
        str.resize(0);
    }
    n=str1.length();  
    for(int i=(n-1);i>=0;--i){
        if(str1[i]=='0')
            str1.pop_back();
        else
            break;
    }
    if(str1.length()==0){
        q=48;
        str1.push_back(q);
        return str1;
    }
    reverse(str1.begin(), str1.end());
    return str1;
}
