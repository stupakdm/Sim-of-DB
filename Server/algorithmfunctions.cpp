#include "algorithmfunctions.h"

AlgorithmFunctions::AlgorithmFunctions()
{
}

string AlgorithmFunctions::pass_coder(string st, int num) {
    string crypted = "";

    for (int i=0;i < (int)st.size(); i++)
            crypted += st[i] ^ (char)num;
    //cout << crypted << endl;
    return crypted;
}

string AlgorithmFunctions::pass_decoder(string st, int num) {
    string decrypted = "";

    for (int i=0;i < (int)st.size(); i++)
            decrypted += st[i] ^ (char)num;
    //cout << decrypted << endl;
    return decrypted;
}

int AlgorithmFunctions::binary_search(vector<struct user> s_arr, string login) {
    int l = 0;
    int r = s_arr.size();
    int mid;

    while (1) {
        mid  = (l+r)/2;
        //cout << s_arr[mid].login << endl;
        if (login < s_arr[mid].login) {
            r = mid -1;
        }
        else if (login > s_arr[mid].login)
        {
            l = mid + 1;
        }
        else
        {
            return mid;
        }
        if (l> r)
            return -1;
    }
}
void AlgorithmFunctions::quicksort(vector<struct user>& s_arr, int first, int last) {
    int i = first, j = last;
    struct user x = s_arr[(first+last)/2];
    do {
        while (s_arr[i].login < x.login) i++;
        while (s_arr[j].login > x.login) j--;

        if (i <= j) {
            if (s_arr[i].login > s_arr[j].login) iter_swap(s_arr.begin()+i, s_arr.begin()+j);
            i++;
            j--;

        }
    } while (i <= j);

    if (i < last) {
        quicksort(s_arr, i, last);
    }
    if (first < j)
        quicksort(s_arr, first, j);
}
