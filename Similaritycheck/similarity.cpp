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
            //cout << "inside if condition" << endl;
            //cout<< endl;
            //cout << "word is " << word << " s[i] is " << s[i] << " countword is " << countword << endl;
            //cout << word << "appered " << countword << "times" << endl;
            frequency[word] = countword;
            countword = 0;
            word = s[i];
            //cout << "word is " << word << " s[i] is " << s[i] << " countword is " << countword << endl;
            //cout << "outside if condition" << endl;
            //cout << endl;
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
/*
    for(map<string, bool>:: iterator i = check.begin(); i!=check.end(); i++)
    {
        cout << "in check" << i->first << endl;
    }
    cout << "check size is : " << check.size() << endl;
*/
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
/*
    for(int i=0; i<withoutStop.size(); i++)
    {
        cout << "in withoutStop " << withoutStop[i] << endl;
    }
*/
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
/*
vector<string> removestopword(vector<string> v)
{
    vector<string> stopwords;
    vector<string> freshwords;
    cout << "into the function" << endl;
    stopwords = getStopWords();
    cout << "get stop word" << endl;
    int j=0;
    for(int i=0; i<stopwords.size()-1; i++)
    {
        cout << "inside for loop" << endl;
        if(stopwords[i] != v[j])
        {
            cout << "if condition" << endl;
            freshwords.push_back(v[j]);
            cout << "pushed " << freshwords[i] << endl;
            cout << j << endl;
        }
        else
            cout << "stop word: " <<  v[j] << endl;
        j++;
    }
    cout << "before return" << endl;
    return freshwords;
}
*/

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
    result =(double) (1+log(re));
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
    int totalterm = tv.size();                      // total number of term of a document.
    cout << "withoutstopwords total words is " << ttv.size() << endl;
    cout << "Total Term is: " << totalterm << endl;
    //cout << "In row " << rowtfm.size() << endl;
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
/*
map<string, double> IDF(vector<string> tdv, int numberOfDocuments)
{
    map<string, double> idfm;
    map<string, int> rowdfm;
    vector<string> dv;

    dv = getWithoutStopWords(tdv);
    rowdfm = wordFrequency(dv);

    for(map<string, int> :: iterator it = rowdfm.begin(); it != rowdfm.end(); it++)
    {
        string term = it->first;
        int freq = it->second;
        double idf = (double) caltulateIDF(freq, numberOfDocuments);
        idfm[term] = idf;
    }

    dv.clear();
    rowdfm.clear();
    return idfm;
}

*/
map<string, double> IDF2(vector<string> totalwordofdocuments, vector<string> *dtv, int numberOfDocuments)
{

    int countdf=0;
    vector<string> tv;
    vector<string> u;
    map<string, double> idfm;
    map<string, int> rowfrq[numberOfDocuments];

    vector<string> doct[numberOfDocuments];
    //vector<string> uniq[numberOfDocuments];

    tv = getWithoutStopWords(totalwordofdocuments);                 // get total words of documents.
    u = uniquewords(tv);                                            // get the unique words of documents.

    int totalword = u.size();

    for(int i=0; i<numberOfDocuments; i++)
    {
        doct[i] = getWithoutStopWords(dtv[i]);                      // get total word of a document.
        rowfrq[i] = wordFrequency(doct[i]);
        //uniq[i] = uniquewords(doct[i]);                         // get the rowcount of word of a document.
        cout << "in IDF2 row count for file " << i+1 << "is" << rowfrq[i].size() << endl;
        //cout << "in IDF2 row count for file " << i+1 << "is" << uniq[i].size() << endl;
    }
    cout << " IDF2 totalword is " << totalword << endl;

    for(int i=0; i<totalword; i++)
    {
        string t = u[i];
        for(int j=0; j<numberOfDocuments; j++)
        {

            for(map<string, int>:: iterator it = rowfrq[j].begin(); it!=rowfrq[j].end(); it++)
            //for(int k=0; k<uniq[i].size(); k++)
            {
                if(t == it->first)
            //    if(t==uniq[i][k])
                {
                    countdf++;
                }
            }
        }
        //cout << "count of word "<< t <<  " in document is : " << countdf << endl;
        double idfv = caltulateIDF(countdf, numberOfDocuments);
        //if(idfv == 1)
        	//cout << "Similar word is " << t << endl;
        idfm[t] = idfv;
        countdf = 0;
    }
    for(int i=0; i<numberOfDocuments; i++)
    {
        rowfrq[i].clear();
        //uniq[i].clear();
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

map<string, double> wordVectorofDocument(map<string, double> tf, map<string, double> score)
{
	map<string, double> vec;

	for(map<string, double>:: iterator it = tf.begin(); it!=tf.end(); it++)
	{
		string s = it->first;
		for(map<string, double>:: iterator its = score.begin(); its!=score.end(); its++)
		{
			if(s == its->first)
			{
				vec[s] = its->second;
			}
		}
	}
	return vec;
}

map<string, double>* wordVectorofDocuments(map<string, double> *tf, map<string, double> score, int numberOfDocuments)
{
	map<string, double> vec[numberOfDocuments];
	for(int i=0; i<numberOfDocuments; i++)
	{
		for(map<string, double>:: iterator it = tf[i].begin(); it!=tf[i].end(); it++)
		{
			string s = it->first;
			for(map<string, double>:: iterator its = score.begin(); its!=score.end(); its++)
			{
				if(s == its->first)
				{
					vec[i][s] = its->second;
				}
			}
		}
	}

	return vec;
}

double dotproduct(map<string, double> vec1, map<string, double> vec2)
{
	double result = 0.0;
	map<string, double>:: iterator v2 = vec2.begin();
	for(map<string, double>:: iterator v1 = vec1.begin(); (v1 != vec1.end()) && (v2 != vec2.end()); v1++)
	{
		double value1 = v1->second;
		double value2 = v2->second;

		result += value1*value2;
		v2++;
	}
	return result;
}

double valueofVector(map<string, double> vec)
{
	double result = 0.0;
	double samplesum = 0.0;
	for(map<string, double>:: iterator v = vec.begin(); v != vec.end(); v++)
	{
		double value = v->second;
		samplesum += value*value;
	}

	result = sqrt(samplesum);
	return result;
}

double getCosineValue(map<string, double> vec1, map<string, double> vec2)
{
	double cosinevalue;

	cosinevalue = (double) dotproduct(vec1, vec2)/(valueofVector(vec1)*valueofVector(vec2));

	return cosinevalue;
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

    ofstream frequencyFile,cosinFile;
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
    ifile.open("README.txt");
    int numoffiles = getnumberofline(ifile);
    ifstream file;
    string filename;
    if(ifile.is_open())
    {
        while(ifile>>filename)
        {
            file.open(filename);
            if(file.is_open())
            {
                words = getTotalWords(file);
            }
            else
                cout << "Can't open File." << endl;
        }

    }
    else
        cout << "Can't open the README file." << endl;
    */
    /*
    for(int i=0; i<words.size(); i++)
    {
        words[i] = withoutPunc(words[i]);
        //cout << words[i] << endl;
    }
*/
    string name66 = "File1.txt";

    file1.open(name66);
    file2.open("File2.txt");
    file3.open("../Similaritycheck/FileArchive/File3.txt");
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

    int numberOfDocuments = 5;
    for(int i=0; i<numberOfDocuments; i++)
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

    for(int i=0; i<numberOfDocuments; i++)
    {
        //cout << "File " << i+1 << endl;
        tf[i] = TF(words[i]);
        //for(map<string, double> :: iterator itf = tf[i].begin(); itf != tf[i].end(); itf++)
        //{
            //cout << itf->first << "         "  << itf->second << endl;
        //}
        //.cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
    }

    idf = IDF2(totalwords,words, numberOfDocuments);
    //rowfreq = wordFrequency(withoutstopwords);
    score = getscore(tf, idf, numberOfDocuments);
    //map<string, double> :: iterator its = score.begin();
    /*
    for(its = score.begin(); its != score.end(); its++)
    {
        cout << its->first << " , " << its->second << endl;
    }
    */
    //int files = words.size();
    double* scores = new double[numberOfDocuments];
    scores = getScoreforFile(tf,score,numberOfDocuments);
    /*
    for(int i=0; i<5; i++)
    {
        cout << "File" << i+1 << "score is " << scores[i] << endl;
    }
    /*
    map<string, int>::iterator i = rowfreq.begin();
    for(map<string, double> :: iterator it=idf.begin(); it!=idf.end() && i!=rowfreq.end(); it++)
    {
        cout << it->first << " , " << i->first << " , " << i->second << " , " << it->second << endl;
        i++;
    }
    */
    pritn(tf, rowcou, idf, score, scores, numberOfDocuments);
    cout << "total words is: idf " << idf.size() << endl;
    cout << "total words is: score " << score.size() << endl;
    cout << "total words in: rowfreq " << rowfreq.size() << endl;

/*
    map<string, double> vector1;
    map<string, double> vector2;

    vector1 = wordVectorofDocument(tf[0], score);
    vector2 = wordVectorofDocument(tf[1], score);

    double cosine = getCosineValue(vector1, vector2);

    cout << "the cosine value is: " << cosine << endl;
    */

    cosinFile.open("Cosine.csv");
    map<string, double> wordVectorofDocuments[numberOfDocuments];
    double cosinevalues[numberOfDocuments][numberOfDocuments];
    for(int i=0; i<numberOfDocuments; i++)
    {
    	wordVectorofDocuments[i] = wordVectorofDocument(tf[i], score);
    }
    cout << "the cosine values are "<< endl;
    cosinFile << " " << "," <<"file1" << "," << "file2" << "," << "file3" << "," << "file4" << "," << "file5" << endl;
    for(int i=0; i<numberOfDocuments; i++)
    {
        cosinFile << "file" << i+1 << ",";
    	for(int j=0; j<numberOfDocuments; j++)
    	{
    		cosinevalues[i][j] = getCosineValue(wordVectorofDocuments[i], wordVectorofDocuments[j]);
    		cout << cosinevalues[i][j] << " ";
    		cosinFile << cosinevalues[i][j] << ",";

    	}
    	cout << endl;
    	cosinFile << endl;
    }
    //double degree = acos(cosine);

    //cout << "the degree is: " << degree << endl;

    /*
    for(int i=0; i<5; i++)
    {
        for(map<string, double>:: iterator itff= tf[i].begin(); itff != tf[i].end(); itff++)
        {
            map<string, double> :: iterator itss = score.begin();
            map<string, int> :: iterator itrw = rowfreq.begin();
            string ss = itff->first;
            for(map<string, double> :: iterator itddf = idf.begin(); (itddf != idf.end() || itss != score.end() || itrw != rowfreq.end()); itddf++)
            {
                string ssd = itddf->first;
                string sss = itss->first;
                string ssr = itrw->first;
                if((ss == ssd)&& (ss == sss) && (ss == ssr))
                {

                    cout << ss << " " << itrw->second << "  " <<  itff->second << "     " << ss << " " <<  itddf->second << "      " << ss << " " << itss->second << endl;

                }
                itss++;
                itrw++;
            //cout << ss << "     " << itff->second << endl;
            }
        }
    }

*/
    //for(map<string, double> :: iterator it=tf[0].begin(); it!=tf[0].end() && i!=rowfreq.end(); it++)
    //{
      //  cout << it->first << " , " << i->first << " , " << i->second << " , " << it->second << endl;
        //i++;
    //}


    //for(int i=0; i<words.size(); i++)
    //{
      //  cout << words[i] << endl;
    //}



///////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
/*
    withoutstopwords = getWithoutStopWords(words);
    cout << "total fresh words " << withoutstopwords.size() << endl;

    frequencyFile.open("termFrequency.csv");
    frequency = wordFrequency(withoutstopwords);
    map<string, int> :: iterator it = frequency.begin();
    for(it = frequency.begin(); it!=frequency.end(); it++)
    {
        cout << it->first << "," << it->second << endl;
        if(!frequencyFile)
        {
            cout << "frequencyFile can't be opened." << endl;
        }
        else
            frequencyFile << it->first << "," << it->second << endl;
    }
    uniqueword = uniquewords(withoutstopwords);

    cout << "Unique words are" << endl;
    for(int i=0; i<uniqueword.size(); i++)
    {
        cout << uniqueword[i] << endl;
    }
  ///////////////////////////////////////
*/
/*
    //stopwords = getStopWords();
    cout << "is segment" << endl;
    fresh = removestopword(words);
    cout << "after calling" << endl;
    for(int i=0; i<fresh.size(); i++)
    {
        cout << fresh[i] << endl;

    }
  */
    //fresh.clear();
    uniqueword.clear();
    for(int i=0; i<5; i++)
    {
        words[i].clear();
        tf[i].clear();

    }
    withoutstopwords.clear();
    idf.clear();
    score.clear();
    rowfreq.clear();
}
