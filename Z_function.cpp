vector<int> calculateZ(const string& input) {
    int n = input.size();
    vector<int> Z(n); 
    int left = 0, right = 0;

    for (int k = 1; k < n; k++) {
        if (k > right) {
            // k is outside the current Z-box
            left = right = k;

           // try to extend the match beyond current right
            while (right < n && input[right] == input[right - left])
                right++;

            Z[k] = right - left;
            right--;
        } else {
            // k is inside the current Z-box
            int k1 = k - left; // index in the prefix corresponding to k

            // ff the value is within the window, copy it
            if (Z[k1] < right - k + 1) {
                Z[k] = Z[k1];
            } else {
                // try to extend the match beyond current right
                left = k;
                while (right < n && input[right] == input[right - left])
                    right++;

                Z[k] = right - left;
                right--;
            }
        }
    }

    return Z;
}
