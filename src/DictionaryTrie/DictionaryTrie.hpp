/**
 * TODO: File Header
 *
 * Author:
 */
#ifndef DICTIONARY_TRIE_HPP
#define DICTIONARY_TRIE_HPP

#include <queue>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

/**
 * The class for a dictionary ADT, implemented as either
 * a mulit-way trie or a ternary search tree.
 */
class DictionaryTrie {
  private:
    // TODO: add private members and helper methods here
    class Node {
      public:
        unsigned int freq;
        unordered_map<char, Node*> map_word;
        Node() { freq = 0; }
    };
    bool insert(Node*& root, string word, unsigned int freq);
    void deleteAll(Node*& root);
    void getAllchildren(Node*& root, string prefix);
    void findChildren(Node*& node, string word);
    typedef priority_queue<pair<int, string>, vector<pair<int, string>>,
                           less<pair<int, string>>>
        my_quene;

  public:
    Node* root;
    unsigned int iszie;
    vector<pair<int, string>> prefixword;
    /* TODO: add function header */
    DictionaryTrie();

    // void getAllchildren1(string prefix);
    /* TODO: add function header */
    bool insert(string word, unsigned int freq);

    /* TODO: add function header */
    bool find(string word) const;

    /* TODO: add function header */
    vector<string> predictCompletions(string prefix,
                                      unsigned int numCompletions);

    /* TODO: add function header */
    vector<string> predictUnderscores(string pattern,
                                      unsigned int numCompletions);

    /* TODO: add function header */
    ~DictionaryTrie();
};

#endif  // DICTIONARY_TRIE_HPP
