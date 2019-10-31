/*
 * @Descripttion: class definition and Function declaration of MWT operation and
 * auto-completer
 * @version: 1.0
 * @Author: Kaixin Lin
 * @Date: 2019-10-29 22:01:59
 */

#ifndef DICTIONARY_TRIE_HPP
#define DICTIONARY_TRIE_HPP

#include <algorithm>
#include <queue>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

/**
 * The class is for a dictionary ADT, implemented as either
 * a mulit-way trie or a ternary search tree.
 */
class DictionaryTrie {
  private:
    // The class is for a MWT node,
    // included frequency in the node, nodes, and the frequency max in the
    // subtree
    class Node {
      public:
        // stores the node's frequency
        unsigned int freq;
        // store all the children
        unordered_map<char, Node*> map_word;
        // stores the node's children max frequency
        unsigned int max_freq;
        // stores sorted words according to their frequency
        // constructor
        Node() { freq = max_freq = 0; }
    };

    /**
     * @name:   insert
     * @brief:  insert helper function
     * @return: Retun true if insert successfully
     */
    bool insert(Node*& root, string word, unsigned int freq,
                unsigned int count);

    /**
     * @name:   deleteAll
     * @brief:  delete destructor helper function
     */
    void deleteAll(Node*& root);

    /**
     * @name:   getAllchildren
     * @brief:  DFS function to look for all children
     */
    void getAllchildren(Node*& root, string prefix,
                        unsigned int numCompletions);
    /**
     * @name:   findChildren
     * @brief:  DFS helper function to look for all children
     */
    void findChildren(Node*& node, string word, unsigned int numCompletions);

    /**
     * @name:   predictUnderscoresHelper
     * @brief:  predict Underscores helper function
     * @return: void
     */
    void predictUnderscoresHelper(Node*& root, string pattern,
                                  unsigned int numCompletions,
                                  unsigned int count, string str);
    /**
     * @name:   comparePair
     * @brief:  compared function according to frequency and alphabetical order
     * @param:  Comparative variable
     * @return: Return true if p1 > p2
     */
    bool comparePair(const pair<int, string>& p1, const pair<int, string>& p2);

    // structure for my_quene to compare
    struct cmp {
        // compare function for prefix
        bool operator()(const pair<int, string>& a, const pair<int, string>& b);
    };
    // priority_quene for node
    typedef priority_queue<pair<int, string>, vector<pair<int, string>>, cmp>
        my_quene;
    typedef priority_queue<pair<int, char>, vector<pair<int, char>>,
                           less<pair<int, char>>>
        my_node_quene;

  public:
    Node* root;
    // store result in heap
    my_quene prefixword;
    my_quene underscoresword;

    /* DictionaryTrie constructor */
    DictionaryTrie();

    /**
     * @name:   insert
     * @brief:  insert word to MWT
     * @return: Return true if insert successfully
     */
    bool insert(string word, unsigned int freq);

    /**
     * @name:   find
     * @brief:  find word in MWT
     * @return: Return true if find the word
     */
    bool find(string word) const;

    /**
     * @name:   predictCompletions
     * @brief:  predict Completions function
     * @return: Return a vector holding up to numCompletions of the most
     * frequent completions of prefix
     */
    vector<string> predictCompletions(string prefix,
                                      unsigned int numCompletions);

    /**
     * @name:   predictUnderscores
     * @brief:  predict Underscores function
     * @return: Return a vector holding up to numCompletions of the most
     * frequent valid completions of pattern
     */
    vector<string> predictUnderscores(string pattern,
                                      unsigned int numCompletions);

    /* DictionaryTrie destructor  */
    ~DictionaryTrie();
};

#endif  // DICTIONARY_TRIE_HPP
