#include<bits/stdc++.h>

using namespace std;

map <string, bool> stop;
int main(void)
{
	vector<string> stopwords;
    string s;
    //for(int i=0; i<5; i++)
    //{
	stopwords.push_back("political");
	stopwords.push_back("about");
	stopwords.push_back("Koreas");
	stopwords.push_back("also");
	stopwords.push_back("while");
    	
    	//stopwords["political"] = true;

    //}

    for(int i = 0; i < stopwords.size(); i++){
    	string s = stopwords[i];
    	stop[s] = true;
    }
 
    ifstream stopwordfile;
    stopwordfile.open("stop_words.txt");
    int i=0;
    if(stopwordfile.is_open())
    {
        while(stopwordfile >> s)
        {
            
            if(stop.find(s) != stop.end()){
            	stop.erase(s);
            }
        }
    }
    else
        cout << "can't open the stopword file." << endl;
	cout << "the actual size of vector is" << stopwords.size() << endl;
   /* for(int i=0; i<stopwords.size(); i++)
    {
        cout << stopwords[i] << endl;
    }*/

    for(map <string, bool>::iterator it = stop.begin(); it != stop.end(); it++){

    	cout << it -> first << endl;
    }
}
