vector<int>LPS(const string& pattern) {
    int n = pattern.size();
    vector<int> lps(n); // pi 
    int len = 0; 

    lps[0] = 0; // always 0

    int i = 1;
    while (i < n) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                // try shorter prefix
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }

    return lps;
}

void KMP(const string& pattern, const string& text) {
    int m = pattern.size();
    int n = text.size();

    vector<int> lps=LPS(pattern);

    int i = 0; // idx for text
    int j = 0; // idx for pattern

    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == m) {
            //found
            cout<<"Pattern found at idx"<<(i - j)<<endl;
            j=lps[j-1]; //continue searching
        } else if (i<n&&pattern[j]!=text[i]) {
            // mismatch after some match
            if (j != 0) {
                j=lps[j - 1]; //try matching with shorter prefix
            } else {
                i++;
            }
        }
    }
}
