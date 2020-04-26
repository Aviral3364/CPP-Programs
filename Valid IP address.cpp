//Valid IP address
bool isValid(string s) {
    if (s.size() > 1 && s[0]  ==  '0')
        return false;
    if (stoi(s) <= 255 && stoi(s) >= 0)
        return true;
    else
        return false;
}
vector<string> Solution::restoreIpAddresses(string s) {
    vector<string> ans;
    if ((s.size()>12)||(s.size()<4))
        return ans;
    for (int i=1;i<4;i++) {
        string f=s.substr(0, i);
        if (!isValid(f))
            continue;
        for (int j=1;i+j<s.size() && j<4;j++) {
            string se=s.substr(i,j);
            if (!isValid(se))
                continue;
            for (int k=1;i+j+k<s.size() && k<4;k++) {
                string t=s.substr(i+j,k);
                string fo=s.substr(i+j+k);
                if (isValid(t) && isValid(fo)) {
                    string curr=f+"."+se+"."+t+"."+fo;
                    ans.push_back(curr);
                }
            }
        }
    }
 
    return ans;
}