#include <bitset>
#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <ctime> 
#include <random> 
#include <cstdlib>
using namespace std;

int getRandomNumber(int min, int max)
{
    static const double fraction = 0.2 / (static_cast<double>(RAND_MAX) + 1.0);
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

int getProb(double p)
{
    std::random_device rd{};
    std::mt19937 rng{ rd() };
    std::bernoulli_distribution d(p);

    return d(rng);
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

vector<vector<int>> HMatrix = {
    {1, 1, 0, 1, 1, 0, 0, 1, 0, 0},
    {0, 1, 1, 0, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 1, 1, 1},
    {1, 1, 0, 0, 0, 1, 1, 0, 1, 0},
    {0, 0, 1, 0, 0, 1, 0, 1, 0, 1}
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


vector<double> LLR(vector<int> msg, double probability) {
    vector<double> retvec(msg.size());
    double prob1 = log(probability / (1 - probability));
    double prob0 = log((1 - probability) / probability);
    for (int i = 0; i < msg.size(); i++) {
        if (msg[i] == 0) {
            retvec[i] = prob0;
        }
        else {
            retvec[i] = prob1;
        };
    }
    return retvec;
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


double prod(vector<double> str) {
    double ret = 1;
    for (int i = 0; i < str.size(); i++) {
        ret = ret * str[i];
    }
    return ret;
}


vector<double> sum(vector<vector<double>> matr) {
    vector<double> ret(matr[0].size());
    for (int i = 0; i < matr[0].size(); i++)
    {
        ret[i] = 0;
        for (int j = 0; j < matr.size(); j++)
        {
            ret[i] += matr[j][i];
        }
    }
    return ret;
}


vector<vector<double>> calc_E(vector<vector<double>> M) {
    vector<vector<double>> Hmirr(HMatrix.size());
    vector<vector<double>> E = M;

    for (int i = 0; i < HMatrix.size(); i++)
    {
        for (int j = 0; j < HMatrix[0].size(); j++)
        {
            if (HMatrix[i][j] == 0) 
            {
                Hmirr[i].push_back(double(1));
            }
            else 
            {
                Hmirr[i].push_back(double(0));
            }
        }
    }

    for (int i = 0; i < M.size(); i++) {
        for (int j = 0; j < M[0].size(); j++) {
            M[i][j] = M[i][j] / 2;
            M[i][j] = tanh(M[i][j]) + Hmirr[i][j];
        }
    }
    for (int i = 0; i < M.size(); i++) {
		for (int j = 0; j < M[0].size(); j++) {
            if (HMatrix[i][j] != 0) {
                E[i][j] = log((1 + prod(M[i]) / M[i][j]) / (1 - prod(M[i]) / M[i][j]));
            }
        }
    }

    return E;
}


vector<double> calc_l(vector<vector<double>> E, vector<double> msg) {
    vector<double> sumE = sum(E);
    for (int i = 0; i < sumE.size(); i++)
    {
        sumE[i] += msg[i];
    }
    
    return sumE;
}

vector<int> tobool(vector<double> msg) {
    vector<int> ret(msg.size());
    for (int i = 0; i < msg.size(); i++)
    {
        if (msg[i] > 0) 
        {
            ret[i] = 0;
        }
        else 
        {
            ret[i] = 1;
        }
    }
    return ret;
}


vector<vector<double>> calc_M(vector<vector<double>> M, vector<vector<double>> E, vector<double> msg)
{
    bool stop = false; 
    vector<int> compare = { 0, 0, 0, 0, 0 };
    for (int j = 0; j < HMatrix.size(); j++) {
        for (int i = 0; i < HMatrix[0].size(); i++) {
            if (HMatrix[j][i] != 0) {
                double counter = 0;
                for (int k = 0; k < E.size(); k++) {
                    counter += E[k][i];
                }
                M[j][i] = counter - E[j][i] + msg[i];
            }
        }
    }
    return M;
}


vector<int> SPA(vector<vector<int>> matrixx, vector<double> msg) {
    vector<int> compare = { 0, 0, 0, 0, 0 };
    vector<vector<int>> matrix = HMatrix;

    vector<vector<double>> M(matrix.size());
    vector<double> v(matrix[0].size());
    bool stop = false;

    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[0].size(); j++)
        {
            v[j] = msg[j] * matrix[i][j];
        }
        M[i] = v;
    }

    int I = 0;
    int Imax = 1000;
    while (!stop) {

        vector<vector<double>> E = calc_E(M);
        vector<double> l = calc_l(E, msg);

        vector<int> boolL = tobool(l);
        vector<int> encoded = MultiplyMatrix(boolL, HTMatrix);

        if (encoded == compare)
        {
            vector<int> vecslice = slice(boolL, 5, 10);
            stop = true;
            return vecslice;
        }
        else
        {
            M = calc_M(M, E, msg);
            I++;
        }
        if (I < Imax) {
            vector<int> vecslice = slice(boolL, 5, 10);
            stop = true;
            return vecslice;
        }
    }
}


vector<int> parity(vector<int> msg, vector<vector<int>> matrix, double mistakeprob, int mistake) {
    vector<int> compare = { 0, 0, 0, 0, 0 };
    
    vector<double> llrvector = LLR(msg, mistakeprob);

    for (int i = 0; i < llrvector.size(); i++) {
        if (getProb(mistakeprob)) {
            llrvector[i] = llrvector[i] * -1;
        };
    }
    
    vector<int> juu = SPA(matrix, llrvector);
    return juu;
}

vector<int> division(vector<int> str, vector<vector<int>> matrix, double mistakeprob, int mistake) {
    vector<int> compare = { 0, 0, 0, 0, 0 };
    vector<int> retvec;
    for (int i = 0; i < str.size() / 10; i++) {
        vector<int> vectorlet = revec(slice(str, i * 10, 10 + i * 10));
        vector<int> vecslice = parity(vectorlet, matrix, mistakeprob, mistake);
        retvec.insert(retvec.end(), vecslice.begin(), vecslice.end());

    }
    retvec = slice(retvec, 0, retvec.size() - retvec.size() % 2);
    return retvec;
}



int main()
{
    srand(time(0));

    while (1) {
        double mistakeprob = 0.1;
        int mistake = 1;
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

            vector<int> checkedvec = division(encoded_vector, HTMatrix, mistakeprob, mistake);

            string decoded = vec_to_str(checkedvec);
            cout << "encoded: " << bit_to_ch(decoded) << endl;
        }
    }
}
