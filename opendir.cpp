/*
#include <Windows.h>
#include <vector>
#include <iostream>
*/
#include <dirent.h>
#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

vector<string> open(string path)
{

    DIR* dir;
    dirent* pdir;
    vector<string> files;

    dir = opendir(path.c_str());

    while (pdir = readdir(dir)) {
        files.push_back(pdir->d_name);
    }

    return files;
}

int isTextFile(string filename)
{
    for(int j=0; j<filename.length(); j++)
    {
        if(filename[j] == '.' && filename[j+1] == 't' && filename[j+2] == 'x' && filename[j+3] == 't')
        {
            //cout << filename << endl;
            return 1;
            break;
        }


    }
    return 0;
}

vector<string> getTextFiles(string path)
{
    vector<string> f;
    //string path;
    vector<string> files;
   // path = "C:\\Users\\HP\\Desktop";
    f = open(path); // or pass which dir to open

    ifstream file;
    for(int i=0; i<f.size(); i++)
    {
        string filename = f[i];
        if(isTextFile(filename))
        {
            files.push_back(f[i]);
        }


    }

    return files;
}

int main() {

    vector<string> f;
    string path = "C:\\Users\\HP\\Desktop";

    f = getTextFiles(path);

    for(int i=0; i<f.size(); i++)
    {
        cout << f[i] << endl;
    }

//n    file.open(f[22]);

    return 0;
}

/*
vector<string> GetFileNamesInDirectory(string directory) {

	vector<string> files;
	WIN32_FIND_DATA fileData;
	HANDLE hFind;

	if ( !((hFind = FindFirstFile(directory.c_str(), &fileData)) == INVALID_HANDLE_VALUE) )
	{
		while(FindNextFile(hFind, &fileData))
		{
			files.push_back(fileData.cFileName);
		}
	}

	FindClose(hFind);
	return files;
	}

int main() {

	vector<string> vFileNames = GetFileNamesInDirectory("*D:\\3rd Semester (new)\\SE305 SPL-I\\Similaritycheck");

	for (int i = 0; i < vFileNames.size(); i++) {
		cout << vFileNames[i] << endl;
	 }


	 return 0;

}
*/

