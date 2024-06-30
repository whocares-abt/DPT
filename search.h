// Do NOT add any other includes
#include <string> 
#include <vector>
#include <iostream>
#include "Node.h"
using namespace std;

class SearchEngine {
private:
    // You can add attributes/helper functions here
    // Attributes
    vector<Node *> string_info;
    vector<string> sentences;
    int num_sentences;

    // Helper functions
    void rolling_hash(const string &sentence, const string &pattern, vector<int> &poss_offsets);
    void get_offsets(const string &sentence, const string &pattern, vector<int> &offsets);
    void insert_last_LL(Node * &head, Node * &tail, Node * &new_node, int &n_matches);

public: 
    /* Please do not touch the attributes and 
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    SearchEngine();

    ~SearchEngine();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    Node* search(string pattern, int& n_matches);

    /* -----------------------------------------*/
};