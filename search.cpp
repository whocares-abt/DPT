// Do NOT add any other includes
#include "search.h"

#define lli long long int

// Helper functions declaration

// Copies all node parameters expect for left and right
void copy_node(Node * new_node, Node * node_to_copy);

// Converts a given string to lowercase and returns it
string get_lowercase(string str);

// Constructors and destroyers
SearchEngine::SearchEngine(){num_sentences = 0;}

SearchEngine::~SearchEngine(){
    int num_nodes = string_info.size();
    for (int i = 0; i < num_nodes; i++){
        delete string_info[i]; string_info[i] = nullptr;
    }
}

// Insert the sentence into the search engine
void SearchEngine::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    Node * new_node = new Node(book_code, page, paragraph, sentence_no, 0);
    string_info.push_back(new_node);
    sentences.push_back(get_lowercase(sentence));
    num_sentences++;
    return;
}

// Searches and returns all instances of the string in a linked list
Node* SearchEngine::search(string pattern, int& n_matches){
    Node * head = nullptr; Node * tail = nullptr;
    pattern = get_lowercase(pattern);

    for (int i = 0; i < num_sentences; i++){
        vector<int> offsets; string &sentence = sentences[i];
        get_offsets(sentence, pattern, offsets);
        int num_offsets = offsets.size();
        for (int j = 0; j < num_offsets; j++){
            Node * info_node = new Node();
            copy_node(info_node, string_info[i]);
            info_node->offset = offsets[j];
            insert_last_LL(head, tail, info_node, n_matches);
        }
    }

    return head;
}

// Inserts a node at the end of a LL
void SearchEngine::insert_last_LL(Node * &head, Node * &tail, Node * &new_node, int &n_matches){
    if (head == nullptr){
        head = new_node; tail = head; n_matches++; return;
    }
    tail->right = new_node; tail = new_node;
    n_matches++;
}


// Gives all the locations where there are offsets for a sentence
void SearchEngine::get_offsets(const string &sentence,const string &pattern, vector<int> &offsets){
    vector<int> poss_offsets;
    rolling_hash(sentence, pattern, poss_offsets);
    int num_offsets = 0, num_poss = poss_offsets.size();
    int pattern_size = pattern.size();

    for (int i = 0; i < num_poss; i++){
        bool flag = true; int offset = poss_offsets[i];
        if (offset + pattern_size <= sentence.size()){
            for (int j = 0; j < pattern_size; j++){
                if (sentence[offset + j] != pattern[j]){
                    flag = false; break;
                }
            }
        }
        if (flag){offsets.push_back(poss_offsets[i]);}
    }
}

// Gives all the possible locations where the rolling hash matches up with the original hash
void SearchEngine::rolling_hash(const string &sentence, const string &pattern, vector<int> &poss_offsets){
    // TODO: Create a better rolling hash algorithm
    if (sentence.size() < pattern.size()){return;}

    int pattern_len = pattern.size(), sentence_len = sentence.size();
    int last_index = (sentence_len - pattern_len); // For loop termination condition
    // Improvements - Using a random base instead of 256 for security
    lli pattern_hash = 0, curr_hash = 0, hash_helper = 1, prime = 2147483647, base = 256;

    for (int i = 0; i < pattern_len - 1; i++){
        hash_helper = (hash_helper*base)%prime;
    }

    for (int i = 0; i < pattern_len; i++){
        pattern_hash = (pattern_hash*base + pattern[i])%prime;
    }

    for (int i = 0; i < pattern_len; i++){
        curr_hash = (curr_hash*base + sentence[i])%prime;
    }

    for (int j = 0; j < last_index; j++){
        if (curr_hash == pattern_hash){
            poss_offsets.push_back(j);
        }
        curr_hash = (base*(curr_hash - hash_helper*sentence[j]) + sentence[j+pattern_len])%prime;
        if (curr_hash < 0){curr_hash = curr_hash + prime;}
    }

    if (curr_hash == pattern_hash){poss_offsets.push_back(last_index);}
}


// Helper functions definition
// Copies node parameters
void copy_node(Node * new_node, Node * node_to_copy){
    new_node->book_code = node_to_copy->book_code;
    new_node->paragraph = node_to_copy->paragraph;
    new_node->page = node_to_copy->page;
    new_node->sentence_no = node_to_copy->sentence_no;
    new_node->offset = node_to_copy->offset;
}

string get_lowercase(string str){
    string str2 = ""; int num_chars = str.size();
    for (int i = 0; i < num_chars; i++){
        char ch = str[i];
        if (ch <= 'Z' && ch >= 'A'){
            ch = ch - ('A' - 'a');
        }
        str2 += ch;
    }
    return str2;
}