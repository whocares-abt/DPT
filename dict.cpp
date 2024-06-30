// Do NOT add any other includes
#include "dict.h"

int Dict::hasher(string word){
    // Improvements - improve the hash function
    int h=0;
    int prime=59;
    int n=word.size();
    for(int i=0;i<n;i++){
        int term = int(word[i]);
        term *= prime;
        h += term;
        h %= capacity;
    }
    return h%capacity;
}

void Dict::insert_to_table(string word){
    int h = hasher(word);
    int n = hashtable[h].size();
    for(int i = 0; i < n; i++){
        if(hashtable[h][i].first==word){
            hashtable[h][i].second++;
            return;
        }
    }
    pair<string,int> pair;
    pair.first=word;
    pair.second=1;
    size++;
    hashtable[h].push_back(pair);
    if(size > load_factor*capacity){
        resize();
    }
}

void Dict::resize(){    
    int n = capacity;
    capacity *= 2;
    vector<vector<pair<string,int>>> newtable = hashtable;
    hashtable.clear();
    hashtable.resize(capacity);
    for(int i=0;i<n;i++){
        int m = newtable[i].size();
        for(int j = 0; j < m; j++){
            string word = newtable[i][j].first;
            int h = hasher(word);
            hashtable[h].push_back(newtable[i][j]);
        }
    }
    newtable.clear();
}

Dict::Dict(){
    size=0;
    capacity=128;
    hashtable.resize(capacity);
}

Dict::~Dict(){
    hashtable.clear();
    size=0;
}

void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    vector<string> words;
    string word="";
    long long n=sentence.size();
    for(int i=0;i<n;i++){
        int flag=1;
        char c=sentence[i];
        for(int j=0;j<15;j++){
            if(c==separators[j]){
                if(word.size()>0){
                    for(int j=0;j<word.size();j++){
                        word[j]=tolower(word[j]);
                    }
                    words.push_back(word);
                    word="";
                }
                flag=0;
            }
        }
        
            if(flag!=0){
                word+=c;
            }
    }
    if(word.size()>0){
        for(int j=0;j<word.size();j++){
            word[j]=tolower(word[j]);
        }
        words.push_back(word);
        word="";
    }
    for(int i=0;i<words.size();i++){
        insert_to_table(words[i]);
    }    
}

int Dict::get_word_count(string word){
    int h=hasher(word);
    int n=hashtable[h].size();
    for(int i=0;i<n;i++){
        if(hashtable[h][i].first==word){
            return hashtable[h][i].second;
        }
    }
    return 0;
}

void Dict::dump_dictionary(string filename){
    ofstream outfile;
    outfile.open(filename);
    for(int i = 0; i < capacity; i++){
        int n = hashtable[i].size();
        for(int j = 0; j < n; j++){
            string word = hashtable[i][j].first;
            int count = hashtable[i][j].second;
            outfile << word+", "+to_string(count) << endl;
        }
    }
    outfile.close();
}
