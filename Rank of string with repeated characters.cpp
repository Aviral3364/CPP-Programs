//Rank of string with repeated characters
void foo(int arr[],string A,int n){
    for(int i=0;i<n;i++){
        int p=A[i];
        if(p<97){
            arr[p-65]++;
        }
        else{
            arr[p-71]++;
        }
    }
    return;
}

int fac1(long long int n){
    if(n==0)
        return 1;
    long long int f=1;
    for(long long int i=1;i<=n;i++){
        f=f*i;
        f=f%1000003;
    }
    return (int)f;
}

long long int foo2(long long int base,int power,int mod){
    if(power==0)
        return 1;
    long long int temp=foo2(base,power/2,mod);
    if(power%2==0)
        return ((temp%1000003)*(temp%1000003))%1000003;
    else{  
        if(power>0)  
            return ((base%1000003)*(temp%1000003)*(temp%1000003))%1000003;  
        else
            return ((temp*temp)/base)%mod;  
    }
}

long long int fac(long long int n){
    if(n==0)
        return 1;
    long long int f=1;
    for(long long int i=1;i<=n;++i){
        f*=i;
    }
    return f;
}

int poo(int arr[],int index,int i,int n){
    long long int cnt=fac1(n-i-1);
    long long int cnt1=1,cnt2=0;
    for(int j=0;j<index;++j){
        if(arr[j]==0)
            continue;
        cnt1=cnt;
        for(int k=0;k<52;k++){
            if(arr[k]==0)
                continue;
            int p;
            if(k==j)
                p=arr[k]-1;
            else
                p=arr[k];
            cnt1=cnt1*(foo2(fac(p),1000003-2,1000003)%1000003);
            cnt1=cnt1%1000003;
        }
        cnt2+=cnt1;
        cnt2=cnt2%1000003;
    }
    arr[index]--;
    return (int)cnt2%1000003;
}

int Solution::findRank(string A) {
    int n=A.length();
    int arr[52];
    for(int i=0;i<52;++i){
        arr[i]=0;
    }
    foo(arr,A,n);
    int rnk=1;
    for(int i=0;i<n;i++){
        int z=A[i];
        int index;
        if(z<97)
            index=z-65;
        else
            index=z-71;
        rnk=rnk+poo(arr,index,i,n);
        rnk=rnk%1000003;
    }
    return rnk;
}
