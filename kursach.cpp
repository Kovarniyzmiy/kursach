#include <bitset>
#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <ctime> 
#include <cstdlib>
using namespace std;

int getRandomNumber(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

vector<vector<int>> HMultiplyMatrix = {
    {1, 0, 0, 0, 0, 0, 1, 1, 0, 1},
    {0, 1, 0, 0, 0, 1, 0, 0, 0, 1},
    {0, 0, 1, 0, 0, 1, 1, 1, 1, 0},
    {0, 0, 0, 1, 0, 1, 0, 0, 1, 0},
    {0, 0, 0, 0, 1, 0, 0, 1, 1, 1}
};

vector<vector<int>> HTMatrix = {
    {1, 0, 0, 1, 0},
    {1, 1, 0, 1, 0},
    {0, 1, 0, 0, 1},
    {1, 0, 1, 0, 0},
    {1, 1, 0, 0, 0},
    {0, 1, 0, 1, 1},
    {0, 1, 0, 1, 0},
    {1, 0, 1, 0, 1},
    {0, 0, 1, 1, 0},
    {0, 0, 1, 0, 1}
};


vector<int> str_to_vec(string str) {
    vector<int> msg_vector(str.begin(), str.end());

    for (int i = 0; i < msg_vector.size(); i++) {
        msg_vector[i] = int(msg_vector[i]) % 2;
    }
    return msg_vector;
}


string vec_to_str(vector<int> vec) {
    string str;

    for (int i = 0; i < vec.size(); i++) {
        str += to_string(vec[i]);
    }
    return str;
}


vector<int> MultiplyMatrix(vector<int> slice, vector<vector<int>> matrix) {
    vector<int> ret = {};
    for (int i=0; i < matrix[0].size(); i++) {
        int counter = 0;
        for (int j = 0; j < slice.size(); j++) {
            counter += int(slice[j]) *  int(matrix[j][i]);
        }
        ret.push_back(counter %2);
    }
    return ret;
}


vector<int> slice(const vector<int>& v, int start = 0, int end = -1) {
    int oldlen = v.size();
    int newlen;

    if (end == -1 or end >= oldlen) {
        newlen = oldlen - start;
    }
    else {
        newlen = end - start;
    }

    vector<int> nv(newlen);

    for (int i = 0; i < newlen; i++) {
        nv[i] = v[start + i];
    }
    return nv;
}


string ch_to_bit(string str) {
    string ret_str = "";
    for (int j = 0; j < str.length(); j++) {
        std::bitset<8> c(str[j]);
        ret_str = ret_str + c.to_string();
    }
    return ret_str;
}


string bit_to_ch(string str) {
    string ret_str = "";
    for (int j = 0; j < str.length()/8; j++) {
        std::bitset<8> a(str.substr(8*(j), 8));
        ret_str = ret_str + char(a.to_ulong());
    }
    return ret_str;
}


vector<int> revec(vector<int> vec) {
    vector<int> retvec;
    vector<int> slicevec1 = slice(vec, 5, 10);
    vector<int> slicevec2 = slice(vec, 0, 5);
    retvec.insert(retvec.end(), slicevec1.begin(), slicevec1.end());
    retvec.insert(retvec.end(), slicevec2.begin(), slicevec2.end());
    return retvec;
}


string multiply(vector<int> str, vector<vector<int>> matrix) {
    for (int j = 0; j < str.size() % 5; j++) {
        str.push_back(0);
    }
    string ret_string;
    for (int i = 0; i < str.size()/5; i++) {
        vector<int> encoded = MultiplyMatrix(slice(str, i * 5, 5 + i * 5), matrix);
        ret_string += vec_to_str(encoded);

    }
    return ret_string;
}


vector<int> parity(vector<int> msg, vector<vector<int>> matrix) {

    vector<int> compare = { 0, 0, 0, 0, 0 };
    for (int i = 0; i < getRandomNumber(0, 2); i++) {
        int ran = getRandomNumber(0, msg.size() - 1);
        msg[ran] = 0;
    }
    bool stop = true;
    while (stop) {
        vector<int> encoded = MultiplyMatrix(msg, matrix);

        if (encoded == compare) {
            vector<int> vecslice = slice(msg, 5, 10);
            stop = false;
            return vecslice;
        }
        else {
            bool br = false;
            vector<int> encoded = MultiplyMatrix(msg, matrix);
            for (int j = 0; j < matrix.size(); j++) {
                if (matrix[j][0] == encoded[0] &&
                    matrix[j][1] == encoded[1] &&
                    matrix[j][2] == encoded[2] &&
                    matrix[j][3] == encoded[3] &&
                    matrix[j][4] == encoded[4]) {
                    if (msg[j] == 1) {
                        msg[j] = 0;
                    }
                    else {
                        msg[j] = 1;
                    }
                    br = true;
                    cout << "corrected bit number " << j << endl;
                }
                if (br) {
                    break;
                }
            }
            for (int j = 0; j < matrix.size(); j++) {
                for (int i = 0; i < matrix.size(); i++) {
                    if ((matrix[j][0] + matrix[i][0]) % 2 == encoded[0] &&
                        (matrix[j][1] + matrix[i][1]) % 2 == encoded[1] &&
                        (matrix[j][2] + matrix[i][2]) % 2 == encoded[2] &&
                        (matrix[j][3] + matrix[i][3]) % 2 == encoded[3] &&
                        (matrix[j][4] + matrix[i][4]) % 2 == encoded[4]) {
                        if (msg[j] == 1) {
                            msg[j] = 0;
                        }
                        else {
                            msg[j] = 1;
                        }
                        if (msg[i] == 1) {
                            msg[i] = 0;
                        }
                        else {
                            msg[i] = 1;
                        }
                        br = true;
                        cout << "corrected bits number " << j << ", " << i << endl;
                    }
                    if (br) {
                        break;
                    }
                }
                if (br) {
                    break;
                }
            }
        }
    };
}

vector<int> division(vector<int> str, vector<vector<int>> matrix) {
    vector<int> compare = { 0, 0, 0, 0, 0 };
    vector<int> retvec;
    for (int i = 0; i < str.size() / 10; i++) {
        vector<int> vectorlet = revec(slice(str, i * 10, 10 + i * 10));
        vector<int> vecslice = parity(vectorlet, matrix);
        retvec.insert(retvec.end(), vecslice.begin(), vecslice.end());

    }
    retvec = slice(retvec, 0, retvec.size() - retvec.size() % 2);
    return retvec;
}


int main()
{
    srand(time(0));
    while (1) {
        string inp;
        string localstr;
        cout << "enter your string or stop to quit" << endl;
        cin >> inp;
        if (inp == "stop") {
            break;
        } else {
            localstr = inp;
            string bin_string = ch_to_bit(localstr);
            vector<int> vector_bin_string = str_to_vec(bin_string);

            string encoded = multiply(vector_bin_string, HMultiplyMatrix);

            vector<int> encoded_vector = str_to_vec(encoded);

            vector<int> checkedvec = division(encoded_vector, HTMatrix);

            string decoded = vec_to_str(checkedvec);
            cout << bit_to_ch(decoded) << endl;
        }

    
    }
}
