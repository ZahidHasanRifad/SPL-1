#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include<algorithm>
//#include<istringstream>
#include<bits/stdc++.h>

using namespace std;


int getnumberofline(ifstream &file)
{
    string line;
    int lines=0;
    while(getline(file, line))
    {
        lines++;
    }
    return lines;
}


/// this function takes a string and return a string which have no punctuation mark.
string withoutPunc (string s)
{
    string p = ",.?;:!(){}[]";
    string ss;

    for(int i=0; i<p.length(); i++)
    {
        for(int j=0; j<s.length(); j++)
        {
            if(s[j] == p[i])
            {
                s[j] = ' ';

            }

        }

    }
    return s;
}

/* this function takes a vector which have words.
    calculate the number of same word occurences.
    store the word and the number of occurences in a map and return the map.
    
*/
map<string, int> wordFrequency(vector<string> s)
{
    map<string, int> frequency;
    int countword;
    string word;

    cout << "in word frequency " << s.size() <<  endl;

    if(s.size() == 0)
    {
        cout << "no words" << endl;
    }
    sort(s.begin(), s.end());

    //for(int i=0; i<s.size(); i++)
    //{
     //   cout << s[i] << endl;
    //}
    s.push_back(" ");
    word = s[0];
    countword = 1;

    for(int i=1; i<s.size(); i++)
    {
        //cout << "word is " << word << " s[i] is " << s[i] << " countword is " << countword << endl;
        if(word != s[i])
        {
            frequency[word] = countword;
            countword = 0;
            word = s[i];
        }
        countword++;
        //cout << "word is " << word << " s[i] is " << s[i] << " countword is " << countword << endl;

    }


    return frequency;
}

/*  this funtion takes a file and store total words of the file.
    when it store words it check the punctuation and remove it then
    push the word into a vector and return the vector.
*/

vector<string> getTotalWords(ifstream &file)
{
    vector<string> words;
    string word, str;

    while(file >> word)
    {
        //file >> word;

        word = withoutPunc(word);
        istringstream iss(word);
        iss >> str;
        words.push_back(str);
    }
    return words;
}

/*
    takes a vector of all words of a file
    return the unique word of the file.
*/

vector<string> uniquewords(vector<string> v)
{
    map<string, int> m;

    vector<string> word;
    m = wordFrequency(v);

    map<string, int>:: iterator it = m.begin();
    int i=0;
    for(it = m.begin(); it !=m.end(); it++)
    {
        word.push_back(it->first);
    }

    return word;
}

/*
    takes a vector which have stop words
    remove the stop word if found.
    the stopwords.txt file only contain the lowercase letter
    so the parameter vector must be convert into lowercase letter
    otherwise it can't remove the stop word which have a uppercase letter.
    check the word is stop word or not if it is stop word erase the word from map.
    store the fresh word into a vector and return the vector.
*/

vector<string> getWithoutStopWords(vector<string> words)
{
    vector<string> word;
    vector<string> withoutStop;
    vector<string> v;
    map<string, bool> check;
    string s;

    for(int i=0; i<words.size(); i++)
    {
        string s = words[i];
        for(int j=0; j<s.length(); j++)
        {
            s[j] = tolower(s[j]);
        }
        word.push_back(s);
    }
    for(int i=0; i<words.size(); i++)
    {
        string s = words[i];
        for(int j=0; j<s.length(); j++)
        {
            s[j] = tolower(s[j]);
        }
        //cout << s << endl;
        check[s] = true;
        //cout << "pushed " << s << " into check" << endl;
    }

    ifstream stopwordfile;
    stopwordfile.open("stop_words.txt");
    if(stopwordfile.is_open())
    {
        while(stopwordfile >> s)
        {
            //stopwordfile >> s;
            //stopwords.push_back(s);
            if(check.find(s) != check.end())
            {
                check.erase(s);
            }
        }
    }
    else
        cout << "can't open the stopword file." << endl;

    for(map<string, bool> :: iterator it = check.begin(); it!=check.end(); it++)
    {
        withoutStop.push_back(it->first);
        //cout << "in map" << it->first << endl;
    }

    for(int i=0; i<words.size(); i++)
    {
        for(int j=0; j<withoutStop.size(); j++)
        {
            if(word[i] == withoutStop[j])
            {
                v.push_back(word[i]);
                //cout << "v is     " << words[i] << endl;
            }
        }
    }
    withoutStop.clear();
    check.clear();
    word.clear();
    return v;
}


double calculateTF(int numberOfTerms, int totalTerms)
{
    double result;
    result =(double) numberOfTerms/totalTerms;
    return result;
}
double caltulateIDF(int numberOfTerms, int numberOfDocuments)
{
    double result;
    double re=(double) numberOfDocuments/numberOfTerms;
    result =(double) log(re);
    return result;
}
double calculateWeight(double tf, double idf)
{
    double result;
    result = tf*idf;
    return result;
}

map<string, double> TF(vector<string> ttv)
{
    map<string, double> tfm;                         // term frequency map which contain term, and frequency.
    map<string, int> rowtfm;                        // term count map. which contain term and number of term.
    vector<string> tv;                              //term vector. which contain term and no stop words.

    tv = getWithoutStopWords(ttv);                    // getting fresh word.
    rowtfm = wordFrequency(tv);                        // getting term and number of term.
    int totalterm = rowtfm.size();                      // total number of term of a document.

    cout << "Total Term is: " << totalterm << endl;
    cout << "In row " << rowtfm.size() << endl;
    for(map<string, int> :: iterator it = rowtfm.begin(); it != rowtfm.end(); it++)
    {
        string term = it->first;
        int freq = it->second;

        double tf = (double) calculateTF(freq, totalterm);
        tfm[term] = tf;
        //cout << term << "   " << freq << "      " <<tf << endl;
    }

    tv.clear();
    rowtfm.clear();
    return tfm;

}

map<string, double> IDF2(vector<string> totalwordofdocuments, vector<string> *dtv, int numberOfDocuments)
{

    int countdf=0;
    vector<string> tv;
    vector<string> u;
    map<string, double> idfm;
    map<string, int> rowfrq[numberOfDocuments];
    vector<string> doct[numberOfDocuments];

    tv = getWithoutStopWords(totalwordofdocuments);                 // get total words of documents.
    u = uniquewords(tv);                                            // get the unique words of documents.

    int totalword = u.size();

    for(int i=0; i<numberOfDocuments; i++)
    {
        doct[i] = getWithoutStopWords(dtv[i]);                      // get total word of a document.
        rowfrq[i] = wordFrequency(doct[i]);                         // get the rowcount of word of a document.
        //cout << "in IDF2 row count for file " << i+1 << "is" << rowfrq[i].size() << endl;
    }
    cout << " IDF2 totalword is " << totalword << endl;

    for(int i=0; i<totalword; i++)
    {
        string t = u[i];
        for(int j=0; j<numberOfDocuments; j++)
        {

            for(map<string, int>:: iterator it = rowfrq[j].begin(); it!=rowfrq[j].end(); it++)
            {
                if(t == it->first)
                {
                    countdf++;
                }
            }
        }
        //cout << "count of word "<< t <<  " in document is : " << countdf << endl;

        idfm[t] = caltulateIDF(countdf, numberOfDocuments);
        countdf = 0;
    }
    for(int i=0; i<numberOfDocuments; i++)
    {
        rowfrq[i].clear();
        doct[i].clear();
    }
    tv.clear();
    u.clear();
    return idfm;
}

map<string, double> getscore(map<string, double> *tf, map<string, double> idf, int numberOfDocuments)
{
    map<string, double> s;
    for(int i=0; i<numberOfDocuments; i++)
    {
        map<string, double>:: iterator itf = tf[i].begin();
        map<string, double>:: iterator itdf = idf.begin();
        //int j =0;
        for(itf = tf[i].begin(); itf != tf[i].end(); itf++)
        {
            string stf = itf->first;
            //cout << stf << endl;
            //int k=0;
            for(itdf = idf.begin(); itdf!=idf.end(); itdf++)
            {
                string sdf = itdf->first;
                if(stf == sdf)
                {

                    double sc = calculateWeight(itf->second, itdf->second);
                    s[stf] = sc;

                    //cout << stf << "    " << itf->second << "   "<< sdf << "    " << sc << endl;
                }
           //     k++;
            }
            //cout << "k is   " <<  k << endl;
            //j++ ;
        }
        ///cout << "j is    " << j <<endl;
    }
    return s;
}

double* getScoreforFile(map<string, double> *tf, map<string, double> totalscore, int numberOfDocuments)
{
    //int files = tf.size();
    double* score = new double[numberOfDocuments];
    double coutnscore = 0.0;
    for(int i=0; i<numberOfDocuments; i++)
    {
        for(map<string, double>:: iterator itf = tf[i].begin(); itf != tf[i].end(); itf++)
        {
            string s = itf->first;
            for(map<string, double>:: iterator its = totalscore.begin(); its != totalscore.end(); its++)
            {
                if(s == its->first)
                {
                    coutnscore += its->second;
                }
            }

        }

        score[i] = coutnscore;
        coutnscore = 0.0;
    }

    return score;
}

void pritn(map<string, double> *tf, map<string, int> *rowfreq, map<string, double> idf, map<string, double> score, double *filescore, int numberOfDocuments)
{

    ofstream file;
    file.open("SPL.csv");
    if(file.is_open())
    {
        file << "Term" << "," << "count" << "," << "Term Frequency" << "," << "IDF" << "," << "Score" <<endl;
        for(int i=0; i<numberOfDocuments; i++)
        {

            cout << "File " << i+1 << endl;

            map<string, int> :: iterator itr = rowfreq[i].begin();
            for(map<string, double>:: iterator itf = tf[i].begin(); (itf != tf[i].end() || itr != rowfreq[i].end()); itf++)
            {
                map<string, double>:: iterator its = score.begin();
                //map<string, int>:: iterator itrw = rowfreq.begin();

                string s = itf->first;
                int rc = itr->second;
                for(map<string, double>:: iterator itdf = idf.begin(); (itdf != idf.end()) || (its != score.end()); itdf++)
                {
                    string sd = itdf->first;
                    string ss = its->first;
                    //string sr = itrw->first;
                    if((s==sd) && (s==ss))
                    {
                        //cout << s << "|            " << itf->second << "|              " << itdf->second << "|             " << its->second <<endl;
                        cout << s << "," << rc << "," << itf->second << "," << itdf->second << "," << its->second <<endl;
                        file << s << "," << rc << "," << itf->second << "," << itdf->second << "," << its->second <<endl;
                    }
                    its++;
                    //itrw++;
                }
                itr++;
            }
            cout << "File " << i+1 << "Score is " << filescore[i] <<endl;
            cout << "--------------------------------------------------------------------------------------------------------------------------------------------" << endl;
            cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
        }
    }

}

int main(void)
{
    ifstream ifile, file1, file2, file3, file4, file5;

    ofstream frequencyFile;
    vector<string> words[5];
    vector<string> uniqueword;
    vector<string> withoutstopwords;
    vector<string> fresh;
    vector<string> withoutforeach[5];
    map<string, double> tf[5];
    map<string, double> idf;
    map<string, double> score;
    map<string, int> rowfreq;
    map<string, int> rowcou[5];

    vector<string> totalwords;
    /*
    vector<char[]> files;
    ifile.open("README.txt");
    if(ifile.is_open())
    {
        while(ifile>>filename)
        {
            files.push_back(filename);
            cout << filename << endl;
        }
    }
*/


    file1.open("File1.txt");
    file2.open("File2.txt");
    file3.open("File3.txt");
    file4.open("File4.txt");
    file5.open("File5.txt");
    if(file1.is_open() && file2.is_open() && file3.is_open() && file4.is_open() && file5.is_open())
    {
        words[0] = getTotalWords(file1);
        words[1] = getTotalWords(file2);
        words[2] = getTotalWords(file3);
        words[3] = getTotalWords(file4);
        words[4] = getTotalWords(file5);
    }
    for(int i=0; i<5; i++)
    {
        withoutforeach[i] = getWithoutStopWords(words[i]);
        rowcou[i] = wordFrequency(withoutforeach[i]);

        int len = words[i].size();
        for(int j=0; j<len; j++)
        {
            string str = words[i][j];
            totalwords.push_back(str);
        }
    }

    withoutstopwords = getWithoutStopWords(totalwords);
    rowfreq = wordFrequency(withoutstopwords);

    for(int i=0; i<5; i++)
    {
        //cout << "File " << i+1 << endl;
        tf[i] = TF(words[i]);

    }

    idf = IDF2(totalwords,words, 5);
    //rowfreq = wordFrequency(withoutstopwords);
    score = getscore(tf, idf, 5);

    double* scores = new double[5];
    scores = getScoreforFile(tf,score,5);

    pritn(tf, rowcou, idf, score, scores, 5);
    cout << "total words is: idf " << idf.size() << endl;
    cout << "total words is: score " << score.size() << endl;
    cout << "total words in: rowfreq " << rowfreq.size() << endl;

    //fresh.clear();
    uniqueword.clear();
    for(int i=0; i<5; i++)
    {
        words[i].clear();
        tf[i].clear();
        rowcou[i].clear();

    }
    withoutstopwords.clear();
    idf.clear();
    score.clear();
    rowfreq.clear();
}
