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

vector<string> getTotalWords(ifstream &file)
{
    vector<string> words;
    string word, str;
    
    while(file >> word)
    {
        //file >> word;

        //word = withoutPunc(word);
        //istringstream iss(word);
        //iss >> str;
        words.push_back(word);
    }
    return words;
}

vector<string> getfilenames(ifstream &file)
{
	vector<string> files;
	string filename; 
	while(getline(file, filename))
	{
		cout << filename << endl;
		files.push_back(filename);
	}
	return files;
}

int main(void)
{


	ifstream ifile,file;
	//string filename;
	vector<string> words, filename;
	ifile.open("README.txt");
	/*
	if(ifile.is_open())
	{
		while(ifile >> filename)
		{
			cout << filename << endl;
		}
		cout << "the number of line this file is " << getnumberofline(ifile) << endl;
	}
	*/
	//file.open("README.txt");
    //ifile.open("README.txt");
    //int numoffiles = getnumberofline(ifile);
    
    int lines;
    if(ifile.is_open())
    {
    	filename = getfilenames(ifile);
    	lines = filename.size();
    	cout << lines << endl;
    
        //for(int i=0; i<lines; i++)
        //{
        	
		//}
        
    }
    else
        cout << "Can't open the README file." << endl;
        
    string f = filename[0];
    cout << f << endl;
    string ss = "File1.txt";
            file.open(ss);
            if(file.is_open())
            {
                words = getTotalWords(file);
            }
            else
                cout << "Can't open File." << endl;
    
    for(int i=0; i<words.size(); i++)
    {
    	cout << words[i] << endl;
    }
	
	return 0;
}
