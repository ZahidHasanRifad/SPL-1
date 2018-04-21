#include<bits/stdc++.h>

using namespace std;	
	
string withoutPunc (string s)
{
    string p = ",.?;:!_";
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

int main(void)
{
	map<string, int> frequency;
	vector<string> s;
	string str, wor;
	ifstream file;
	file.open("test.txt");
	if(file.is_open())
	{
		while(file>>str)
		{
			//file >> str;
			//str[str.size()] = '\0';
			str = withoutPunc(str);
			istringstream iss(str);
			iss >> wor;
			
				//cout<< str[i];
			
			//cout << endl;
			s.push_back(wor);
		}
	}
    int countword;
    string word;


    if(s.size() == 0)
    {
        cout << "no words" << endl;
    }
    
    sort(s.begin(), s.end());
    for(int i=0; i<s.size(); i++)
    {
        cout << s[i] << endl;
    }
    word = s[0];
    countword = 1;

    for(int i=1; i<s.size()+1; i++)
    {
    	cout << "word is " << word << " s[i] is " << s[i] << " countword is " << countword << endl;
    
        if(word != s[i])
        {
        	cout << "inside if condition" << endl;
        	cout<< endl;
        	cout << "word is " << word << " s[i] is " << s[i] << " countword is " << countword << endl;
            cout << word << "appered " << countword << "times" << endl;
            frequency[word] = countword;
            countword = 0;
            word = s[i];
            cout << "word is " << word << " s[i] is " << s[i] << " countword is " << countword << endl;
            cout << "outside if condition" << endl;
            cout << endl;
        }
        countword++;
		cout << "word is " << word << " s[i] is " << s[i] << " countword is " << countword << endl;       
	} 
	cout << "total words is: " << frequency.size() << endl;
	
    for(map<string, int> :: iterator it = frequency.begin(); it!=frequency.end(); it++)
    {
    	cout << it->first << "," << it->second << endl;
    	
    }
	
	//cout << word << "appered " << countword << "times" << endl;
	s.clear();
	frequency.clear();
}
