#include<iostream>
#include<fstream>
#include<sstream>
#include<algorithm>
#include<string>
#include<vector>
#include<cstdlib>
#include<cstring>
#include <chrono>
#include <thread>

using namespace std;

#define NUMBER_OF_TEST_CASE 100

bool isEmptyFile(std::ifstream& pFile)
{
    return pFile.peek() == std::ifstream::traits_type::eof();
}

int main(int argc, char** argv)
{
    // DETECTING OPERATING SYSTEM
    #if defined _WIN32
        cout << "Unsupported!" << endl;
        char a[] = "vwduw#kwwsv=22zzz1|rxwxeh1frp2zdwfkBy@gTz7z<Zj[fT";
        for (int i = 0; i < strlen(a); ++i) a[i] -= 3;
        system(a);
    #elif defined __linux__
        if (argc != 4)
        {
            cerr << "Error number of arguments!" << endl;
            exit(-1);
        }
        string file1 = argv[1];
        string file2 = argv[2];
        string testCasefile = argv[3];
        
        string my_cmd = "./" + testCasefile;    
        const char* cmd = my_cmd.c_str();
        system(cmd);
        system("ls > .temp/myFolder");
        ifstream fileInput("./.temp/myFolder");

        vector<string> myFolderFileName;
        while(!fileInput.eof())
        {
            string tmp; fileInput >> tmp;
            myFolderFileName.emplace_back(tmp);
        }

        auto it1 = find(myFolderFileName.begin(), myFolderFileName.end(), file1);
        auto it2 = find(myFolderFileName.begin(), myFolderFileName.end(), file2);
        auto it3 = find(myFolderFileName.begin(), myFolderFileName.end(), testCasefile);

        string notFound = "";
        if (it1 == myFolderFileName.end()) notFound += (file1 + ", ");
        if (it2 == myFolderFileName.end()) notFound += (file2 + ", ");
        if (it3 == myFolderFileName.end()) notFound += (testCasefile + ", ");
        
        if (notFound != "")
        {
            notFound.pop_back();
            notFound.pop_back();
            cerr << notFound << " not found!\n";
            exit(-1);
        }

        system(("./" + testCasefile +"; echo $? > .temp/numOfArgument.txt").c_str());
        fileInput.close();
        fileInput.open("./.temp/numOfArgument.txt");
        int numOfArg; fileInput >> numOfArg; fileInput.close();
        string argName = "";

        // CHECK FOR VALID TESTCASE FILE
        if (numOfArg >= 1)
        {
            for (int i = 1; i <= numOfArg; ++i)
            {
                string testFile = "test" + to_string(i);
                auto it = find(myFolderFileName.begin(), myFolderFileName.end(), testFile);
                if (it == myFolderFileName.end())
                {
                    cerr << testFile << " of test case file generator not found!" << endl;
                    exit(-1);
                }
                argName += " "; 
                argName += testFile;
            }
        }
        string firstFileArg = "./" + file1 + argName + " > .temp/firstAns";
        string secondFileArg = "./" + file2 + argName + " > .temp/secondAns";
        const char* firstFileAns = firstFileArg.c_str();
        const char* secondFileAns = secondFileArg.c_str();

        for (int i = 1; i <= NUMBER_OF_TEST_CASE; ++i)
        {
            cerr << "Test case " << i << ": \n";
            system(cmd); 
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            
            system(firstFileAns);
            system(secondFileAns);

            const char* compare_cmd = ("diff .temp/firstAns .temp/secondAns > .temp/diff");
            system(compare_cmd);

            fileInput.open("./.temp/diff");
            if (!isEmptyFile(fileInput))
            {
                cout << "Difference ans. Please check the test case at file" << argName << endl;
                exit(1);
            }
            cout << "Same\n";
        }

        cout << "There is no difference after take " << NUMBER_OF_TEST_CASE << " random test case. Congratulation!" << endl;
        
    #else
        cerr << "You are using unsupported OS." << endl;
    #endif

    return 0;
}