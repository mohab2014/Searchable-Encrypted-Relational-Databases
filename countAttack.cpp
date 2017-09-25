//Author: Mohamed Ahmed Abdelraheem
//Email: moh.ahm.abdelraheem@gmail.com
//Implementation of Cash et al. Count Attack published at CCS2015
#include <cstdlib>

#include <algorithm>
#include <cstdio>
#include <vector>
#include <string>

#include <iterator>
#include <iostream>
#include <sstream>

#include <fstream>
#include <map>
#include <set>
//#define MAX 32562//299286//32562

using namespace std;




//--------------------------------------------------------------

set<string> split(const char *str, char c)
{
    set<string> result;

    do
    {
        const char *begin = str;

        while(*str != c && *str)
            str++;

        result.insert(string(begin, str));
    } while (0 != *str++);

    return result;
}
//--------------------------------------------------------------
void Tokenize(const string& str,
                      vector<string>& tokens,
                      const string& delimiters = " ")
{
    // Skip delimiters at beginning.
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    string::size_type pos     = str.find_first_of(delimiters, lastPos);

    while (string::npos != pos || string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }
}




//----------------------------------------------
int main(int argc, char* argv[]) 
{
  
    
    
  std::ifstream allKeywordsFile, observedKNOWMatrixFile, observedMatrixFile, resultFileSize, obsQueryFile, cheatSheetFile;
  
  
     
  if(argc != 10)
  {

       std::cout<<"./countAttack allKeywordsfile obsFullMatFile TotalKeywords ResultSizeFile obsQueryMat QuerySize NO_OF_RECORDS cheatsheet folderName\n";
       exit(1);
  }

  allKeywordsFile.open(argv[1]);
  
  observedKNOWMatrixFile.open(argv[2]);
  
  int total = atoi(argv[3]);
  
  resultFileSize.open(argv[4]);
  
  
  obsQueryFile.open(argv[5]);
  
  
  int querySize = atoi(argv[6]);
  
  int MAX = atoi(argv[7]);
  
  
  
  int* noMissedColumnsPerRecord = new int[MAX+1];
  
  for(int i = 0;i < MAX+1;i++)
      noMissedColumnsPerRecord[i] = 0;
  
  cheatSheetFile.open(argv[8]);  
  //string* allKeywords[] = new string[total+1];
  //int*    keywordResultSize = new int[total+1];
  
  int ** CImatrix = new int*[total+1];
  int ** CTmatrix = new int*[querySize+1];
  
  
  for(int i = 0; i < total+1; ++i) 
       CImatrix[i] = new int[total+1];
  
  for(int i = 0; i < total+1;i++)
  {
      for(int j = 0;j < total+1;j++)
      {
          CImatrix[i][j] = 0;
          
      }
  }      
   
  for(int i = 0; i < querySize+1; ++i) 
       CTmatrix[i] = new int[querySize+1];
       
  
  for(int i = 0; i < querySize+1;i++)
  {
      for(int j = 0;j < querySize+1;j++)
      {
          CTmatrix[i][j] = 0;
          
      }
  }      
  
       
  map<string, int> keywordNo;
  map<string,int> keywordSize;
  
  vector<string> allkeywordsList;
  
  map<string,int> recoveredQueries;
  
  map<string,vector<int>> resolvedQueriesMap;
  
  
  
  int count = 0;
  allkeywordsList.push_back("dummy keyword at 0");
  
  for( std::string line; getline(allKeywordsFile, line ); )
  {
        //...for each line in input...
        //keywordsList.push_back(line);
        count++;
        //allKeywords[count] = line;
        allkeywordsList.push_back(line);
        
        keywordNo[line] = count;
     
        //cout<<line<<", "<<keywordNo[line]<<", "<<count<<endl;
       
  }
  
  //exit(1);
  
  int countSheet = 0;
  
  string sheetQueries[total+1];
  
  for( std::string line; getline(cheatSheetFile, line ); )
  {
        //...for each line in input...
        //keywordsList.push_back(line);
        countSheet++;
        //allKeywords[count] = line;
        //allkeywordsList.push_back(line);
        
        sheetQueries[countSheet] = line;
     
    
       
  }
  
  int x, y, f; //read the three integers, queries number x and y and their joint frequency value f 
  char c1, c2; //read two commas
  
  
  
  while (observedKNOWMatrixFile >> x >> c1 >> y >> c2 >> f)
  {
      
      CImatrix[x][y] = f;
      CImatrix[y][x] = f;
      /*string keywordX = allkeywordsList[x].substr(0,allkeywordsList[x].find_first_of(":"));
      
      string keywordY = allkeywordsList[y].substr(0,allkeywordsList[y].find_first_of(":"));
      
      if(x == y)
        CImatrix[x][y] = f;
      else if(keywordX == keywordY)
      {
        
        cout<<keywordX<<":"<<keywordY<<"="<<CImatrix[x][y]<<",x = "<<x<<",y = "<<y<<",f= "<<f<<endl;
        CImatrix[x][y] = 0;  
        CImatrix[y][x] = 0;         
      } 
      else
      {
        CImatrix[x][y] = -1;  
        CImatrix[y][x] = -1;  
      }*/
          
        
      //cout<<keywordX<<":"<<keywordY<<"="<<CImatrix[x][y]<<",x = "<<x<<",y = "<<y<<",f= "<<f<<endl;
      //find the attribute names of query no x and query no y
      //allkeywordsList[x]
      //allkeywordsList[y]
      
      //cout<<"CImatrix["<<x<<"]["<<y<<"] = "<<CImatrix[x][y]<<";"<<endl;*/
  }
 
       
  //exit(1);     

  vector<string>* keywordsListIndex = new vector<string>[MAX+1];
  
  int resultSize[MAX+1] = {0};
          
  for( std::string line; getline(resultFileSize, line ); )
  {
        //...for each line in input...
        //keywordsList.push_back(line);
       
        vector<string> tokens; // Create vector to hold our words

    
        Tokenize(line, tokens);
        
        
        
        
        //keywordsList.push_back(tokens[0]);
        
        //keywordResultSize[count] = atoi(tokens[1].c_str());
        int result = atoi(tokens[2].c_str());
        
        //cout<<"line = "<<line<<", keyword = "<<tokens[0]<<", size = "<<result<<", tokens[1] =  "<<tokens[1]<<endl;
        resultSize[result]++;
        keywordsListIndex[result].push_back(tokens[0]);
       
  }    
  
  
  /*std::ofstream uniquefile("uniqueAdult2");
  
  //map<string, int> uniqueCountKeywords;
  
  //string queryNoKnown[]; 
  
  for(int i = 1;i < MAX;i++)
      if(resultSize[i] == 1) //keywordsListIndex[i].size()== 1)
          uniquefile<< keywordsListIndex[i][0]<<endl;        
       
  uniquefile.close();*/
       
       
  vector<string> knownQueryList;
  vector<int> knownQueryNoList;
  
  vector<string>* unresolvedCandidateList= new vector<string>[querySize+1];
  vector<int> unresolvedQueryNoList;
  
  
  
  
  
  while (obsQueryFile >> x >> c1 >> y >> c2 >> f)
  {

      CTmatrix[x][y] = f;
      CTmatrix[y][x] = f;
      
      //cout<<"CTmatrix["<<x<<"]["<<y<<"] = "<<CTmatrix[x][y]<<";"<<endl;
      
  }
 
  
  
  
  knownQueryList.push_back("dummy keyword at 0");
  knownQueryNoList.push_back(-1);
  
  vector<string> knownQueryListAttributeName;
  
  knownQueryListAttributeName.push_back("dummy attribute name");
  
  //Loop through CTmatrix to find queries with unique Count and add them to known queries
  
  int uniqueCount = 0;
  
  for(int i = 1;i < querySize+1;i++)
  {
      if(resultSize[CTmatrix[i][i]] == 1)
      {
          //then query no i has unique Count, CTmatrix[i][i] is size of query i
          knownQueryList.push_back(keywordsListIndex[CTmatrix[i][i]][0]);
          knownQueryNoList.push_back(i);
          cout<<"query i = "<<i<<" is "<<keywordsListIndex[CTmatrix[i][i]][0]<<endl;
          uniqueCount++;          
          
          string attributeName = keywordsListIndex[CTmatrix[i][i]][0].substr(0,keywordsListIndex[CTmatrix[i][i]][0].find_first_of(":"));
          
          knownQueryListAttributeName.push_back(attributeName);
          recoveredQueries[attributeName] = i; 
          resolvedQueriesMap[attributeName].push_back(i);
      }
      else
      {
          unresolvedQueryNoList.push_back(i); 
          //potential candidates for queryNo 'i'
          cout<<"query i = "<<i<<", result size = "<<CTmatrix[i][i]<<", no of ties = "<<keywordsListIndex[CTmatrix[i][i]].size()<<", alt = "<<resultSize[CTmatrix[i][i]]<<endl;
          for(int j = 0; j < keywordsListIndex[CTmatrix[i][i]].size();j++)
              unresolvedCandidateList[i].push_back(keywordsListIndex[CTmatrix[i][i]][j]);
      
      
      }
  }
  
  cout<<"No queries with unique count = "<<uniqueCount<<endl;
  cout<<"COUNT ATTACK STARTS to resolve "<<unresolvedQueryNoList.size()<<" queries."<<endl;

  //vector<int> unresolvedQueryNoListCopy = unresolvedQueryNoList;
  
  bool knowledgeIncrease;
  
  
  int loopNo = 1;
  
  int resolved = 0;
  
  bool* resolvedQueries = new bool[querySize+1];
  
  for(int j = 0;j <querySize+1;j++)
             resolvedQueries[j] = false;
  
  int queryNoCT1;
  
  do
  {
      knowledgeIncrease = false;
      
      for(int i = 0;i < unresolvedQueryNoList.size();i++)
      {
          //set candidate keywords S
          //S contains all elements where count(qi) = count(s) 
          
          vector<int> S;
          
          queryNoCT1 = unresolvedQueryNoList[i]; //query no of unresolved query i
          
          
          //cout<<"i = "<<i<<", CT1 = "<<queryNoCT1<<", no of ties = "<<unresolvedCandidateList[queryNoCT1].size()<<", size = "<<CTmatrix[queryNoCT1][queryNoCT1]<<endl;
          
          for(int j = 0; j < unresolvedCandidateList[queryNoCT1].size();j++)
          {
             S.push_back(keywordNo[unresolvedCandidateList[queryNoCT1][j]]);
             //cout<<"keywordno, j = "<<j<<", "<<keywordNo[unresolvedCandidateList[queryNoCT1][j]]<<", "<<unresolvedCandidateList[queryNoCT1][j]<<endl;
          }
         
          //known queries are in knownQueryList (i,k) //knownQueryList[i(queryno in CTmatrix)](plaintext keyword) but  keywordNo[knownQueryList[i]] gives queryNo in CI
          
          
          bool* removeS = new bool[S.size()];
          
          for(int j = 0;j < S.size();j++)
              removeS[j] = false;

          //vector<int> copyS = S;
          
          for(int j = 0;j < S.size();j++)
          {
              
          
              //cout<<" S["<<j<<"] = "<<S[j]<<" keyword = "<<unresolvedCandidateList[queryNoCT1][j]<<", ";
              
              int queryNoCI1 = S[j]; //guess query no in knowledge matrix
              
              //cout<<" query i1 = "<< queryNoCI1<<", query t1 = "<<queryNoCT1<<", ";
              
              //Cash et al Count Attack
                    
              for(int k = 1;k < knownQueryList.size();k++)
              {
                  
                  
                     int queryNoCI2 = keywordNo[knownQueryList[k]]; //keyword no of known query k
                     
                     int queryNoCT2 =   knownQueryNoList[k]; //query no of known query k
                     
                     
                     if(CTmatrix[queryNoCT1][queryNoCT2] != CImatrix[queryNoCI1][queryNoCI2])
                     {
                            
                            //cout<<" query i2 = "<< queryNoCI2<<", query t2 = "<<queryNoCT2<<", ";
                            //cout<<" remove j = "<<j<<",";
                            removeS[j] = true;
                            break;
                     
                     }
                     
                     
                     
              }
              
             
          }
         
          
          
          
        
          
          int correct_j = -1;
          int nofalse = 0;
          
          for(int j = 0;j < S.size();j++)
              if(removeS[j] == false)
              {
                  correct_j = j;
                  nofalse++;
              }
          
          cout<<"query no = "<<queryNoCT1<<", known size = "<<knownQueryList.size()<<", nofalse = "<<nofalse<<", correct_j = "<<correct_j<<" Sj = "<<S[correct_j]<<", S size = "<<S.size()<<".\n";
          
          
          if(nofalse == 1)
          {
              
              cout<<"query no = "<<queryNoCT1<<" has been resolved. Its value is "<<allkeywordsList[S[correct_j]]<<", no of resolved = "<<++resolved<<endl;
              
              //might not be need if map contains all attribute names
              string attributeName = allkeywordsList[S[correct_j]].substr(0,allkeywordsList[S[correct_j]].find_first_of(":"));
              
              recoveredQueries[attributeName] = queryNoCT1;
              
              knowledgeIncrease = true;
              
              knownQueryList.push_back(allkeywordsList[S[correct_j]]);
              //cout<<" push 1 i = "<<i;
              knownQueryNoList.push_back(queryNoCT1);
              knownQueryListAttributeName.push_back(attributeName);
              
              resolvedQueriesMap[attributeName].push_back(queryNoCT1);
              //cout<<" push i = "<<i<<endl;

              //unresolvedQueryNoListCopy.erase(unresolvedQueryNoListCopy.begin() + i);
              //save resolved i's in order to avoid them next time
              //resolvedQueries.push_back(i);
              resolvedQueries[queryNoCT1] = true;
              
              
          }
          else
          {
                if(S.size() == 2)
                {
                  cout<<"S size = 2"<<endl;
                  for(int j = 0;j < S.size();j++)
                     cout<<" S["<<j<<"] = "<<S[j]<<" keyword = "<<unresolvedCandidateList[queryNoCT1][j]<<endl;
              
                }
          
        
          }
          
          
          cout<<"------------------------------------------------------------------------------"<<endl;
          
      }
      
      vector<int> newUnresolvedList;
      
      for(int i = 0;i < unresolvedQueryNoList.size();i++)
      {
          
          if(!resolvedQueries[unresolvedQueryNoList[i]])
              newUnresolvedList.push_back(unresolvedQueryNoList[i]);
          
      }
      
      
      unresolvedQueryNoList = newUnresolvedList;//unresolvedQueryNoListCopy;
      
      if(unresolvedQueryNoList.size() == 0)
          break;
      
      
      
      cout<<"loopNo = "<<loopNo<<endl;
      loopNo++;
      cout<<"knowledge Increase = "<<knowledgeIncrease<<endl;
      
  }while(knowledgeIncrease); //knowledgeIncrease
       
  
  int unresolvedNo = querySize-uniqueCount-resolved;
  
  
  cout<<"No of  queries recovered with unique count = "<<uniqueCount<<endl;
  cout<<"No of queries recovered with co-occurrence matrices = "<<resolved<<" out of "<<querySize-uniqueCount<<" queries."<<endl;
  cout<<"No of unresolved queries = "<<unresolvedNo<<" queries."<<endl;
  cout<<"Total number of queries recovered = "<<resolved+uniqueCount<<" out of "<<querySize<<" queries."<<endl;     
  
  //exit(1);
  if(unresolvedNo)
  {
       
       for(int i = 0;i < unresolvedQueryNoList.size();i++)
       {
           
           cout<<(i+1)<<": query no = "<<unresolvedQueryNoList[i]<<" is unresolved. Size = "<<CTmatrix[unresolvedQueryNoList[i]][unresolvedQueryNoList[i]]<<", keyword = "<<sheetQueries[unresolvedQueryNoList[i]]<<endl;
           //fetch query result file whose name is qi.txt where i = unresolvedQueryNoList[i] 
           
           string qFileName = "./"+string(argv[9])+"/q" + to_string(unresolvedQueryNoList[i]) + ".txt";
      
           std::ifstream qFile(qFileName);

            if(qFile.fail())
            {
               cout<<"fail to open file named "<<qFileName<<"\n";
               continue;

           }
           std::string qRStext;
           getline( qFile, qRStext );

      
           //remove secret 20 bytes secret tag and the first space char
           qRStext.erase(0,41);

           //cout<<"q1 result set length = " <<q1RStext.substr(0,q1RStext.find_first_of(' '))<<"\n";


      
           //observedQMatrix[q1][q1] = stoi(q1RStext.substr(0,q1RStext.find_first_of(' ')));
           qRStext = qRStext.substr(qRStext.find_first_of(' ')+1);

  
           set<string> qSet = split(qRStext.data(),' ');
 
           set<string>:: iterator it;
           
           for( it = qSet.begin(); it!=qSet.end(); ++it)
           {
               string s = *it;
               noMissedColumnsPerRecord[atoi(s.c_str())]++;
           }
           
       }
       
       //analyze record recovery rate
       
       int noFullRecords[100] = {0};
       int noFull = 0;
       
       for(int i =  1;i < MAX+1;i++)
       {
         if(noMissedColumnsPerRecord[i] == 0)
         {
             noFull++;
         }
         noFullRecords[noMissedColumnsPerRecord[i]]++;
       }
       
       cout<<"Number of records that are fully recovered = "<<noFull<<", "<<noFullRecords[0]<<endl;
       
       for(int i = 0;i < 20;i++)
       {
           
           cout<<"Number of records with "<<i<<" unresolved attributes = "<<noFullRecords[i]<<endl;
           
       }
       
      
  }
  
  
  cout<<"No of  queries recovered with unique count = "<<uniqueCount<<endl;
  cout<<"No of queries recovered with co-occurrence matrices = "<<resolved<<" out of "<<querySize-uniqueCount<<" queries."<<endl;
  cout<<"No of unresolved queries = "<<unresolvedNo<<" queries."<<endl;
  cout<<"Total number of queries recovered = "<<resolved+uniqueCount<<" out of "<<querySize<<" queries."<<endl;    
       
  allKeywordsFile.close();
  //observedMatrixFile.close();
  
  //outfile.close();
  
  cheatSheetFile.close();
  
  
  for(int i = 0; i < total+1; ++i) 
      delete [] CImatrix[i];

  delete [] CImatrix;
  
  
  for(int i = 0; i < querySize+1; ++i) 
       delete [] CTmatrix[i];
       
  delete [] CTmatrix;
    
  
  delete [] keywordsListIndex;
  delete [] unresolvedCandidateList;
  delete [] resolvedQueries;
  delete [] noMissedColumnsPerRecord;
  
  return 0;
}