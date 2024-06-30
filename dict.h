// Do NOT add any other includes
#include <string> 
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class Dict {
private:
    // You can add attributes/helper functions here
    string separators= " .,-:!\"\'()?[];@";
    int size;
    long long capacity;
    float load_factor=0.75;
    int hasher(string s);
    void insert_to_table(string s);
    void resize();
    int wordcount();
    vector<vector<pair<string,int>>> hashtable;

    
public: 
    /* Please do not touch the attributes and 
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    Dict();

    ~Dict();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    int get_word_count(string word);

    void dump_dictionary(string filename);

    /* -----------------------------------------*/
};