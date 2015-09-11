#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

struct keywordinfo{
       string keyword;
       int id;
       int freq;
};

typedef struct keywordinfo keyworddata;

void load_data(vector <string> *keywords, 
               vector<string> *spammessages,
               vector<string> *lingmessages){
    string word;
    ifstream keyFile("keywords.txt");
    while(keyFile>>word) {
        (*keywords).push_back(word);
    }    
    
    ifstream spamFile("spam_filenames.txt");
    while(spamFile>>word) {
        (*spammessages).push_back(word);
    }    
    
    ifstream lingFile("ling_filenames.txt");
    while(lingFile>>word) {
        (*lingmessages).push_back(word);
    }    
}

void print_vector(vector<string> v){
    int i;
    for(i=0;i<v.size();i++){
        cout<<v[i]<<endl;
    }
}


int find_keyword(string keyword, vector<string>keywords){
     int i;
     for(i=0;i<keywords.size();i++){
           if (keyword.compare(keywords[i])==0) 
              return i;
     }
     return -1;
}

void find_words(string line, vector<string> *words){
     string word;
     stringstream ss(line);
     while (ss>>word)
           (*words).push_back(word);
}

string process_message(string filename, bool isling, vector<string> keywords){
     string line, out;
     stringstream s;
     keyworddata kdata;
     vector <keyworddata> v;
     vector <string> words;
     int pos,i, j, features, found;
     ifstream inFile(filename.c_str());
     out = "< message file = \""+filename+"\"";
     if (isling)
        out = out +" category = \""+"ham\"";
     else
        out = out +" category = \""+"spam\"";
     while(getline(inFile,line)){
        
        find_words(line,&words);
        for(i=0;i<words.size();i++){
          pos=find_keyword(words[i],keywords);
          if (pos!=-1) {
             found=-1;
             for(j=0;j<v.size();j++){
                 if (v[j].keyword.compare(words[i])==0) found=j;
             } 
             if (found==-1){
                kdata.keyword = words[i];kdata.id=pos;kdata.freq=1;
                v.push_back(kdata);
             }
             else{ v[found].freq++;}  
          }                                
        }         
        words.clear();              
      
     }      
     features=v.size();
     s<<features;
     out = out +" features = \""+s.str()+"\" >"+"\n";
     for(i=0;i<v.size();i++){
          s.str("");
          s<<v[i].id;
          out = out + " < feature token = \""+v[i].keyword+"\" id = \""+s.str()+"\" freq = \"";
          s.str("");
          s<<v[i].freq;
          out = out+s.str()+"\" />\n";
     }     
     out = out +"</ message >\n";
     return out;
}


int main(int argc, char** argv) {
    vector <string> keywords,spammessages, lingmessages;
    string result;
    stringstream s;
    int i, messagecounter=0;
    load_data(&keywords,&spammessages,&lingmessages );
    messagecounter=spammessages.size()+lingmessages.size();
    s.str("");
    s<<messagecounter;
    .
    .
    .
    
    system("pause");
}
