/**
 * TODO: DictionaryTrie.hpp
 *
 * Author:Kaixin Lin
 * Finished PA2
 * It implements MWT to achieve auto-completer included predict Underscores and
 *  predict Completions
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
 * The class for a dictionary ADT, implemented as either
 * a mulit-way trie or a ternary search tree.
 */
class DictionaryTrie {
  private:
    typedef priority_queue<pair<int, char>, vector<pair<int, char>>,
                           less<pair<int, char>>>
        my_node_quene;
    // The class for a MWT node,
    // included frequency in the node, nodes, and the frequency max in the
    // subtree
    class Node {
      public:
        // stores the node's frequency
        unsigned int freq;
        // store all the subtree
        unordered_map<char, Node*> map_word;
        // stores the node's max frequency
        unsigned int max_freq;
        // stores sorted words according to their frequency
        // vector<pair<int, char>> word_sort;

        // constructor
        Node() { freq = max_freq = 0; }
    };
    /**
     * @brief insert helper function
     * @return Retun true if insert successfully
     */
    bool insert(Node*& root, string word, unsigned int freq,
                unsigned int count);
    // bool insert(Node*& root, string word, unsigned int freq);

    /**
     * @brief delete destructor helper function
     */
    void deleteAll(Node*& root);

    /**
     * @brief DFS function to look for all children
     */
    void getAllchildren(Node*& root, string prefix,
                        unsigned int numCompletions);
    /**
     * @brief DFS helper function to look for all children
     */
    void findChildren(Node*& root, string word, unsigned int numCompletions);
    // // void addPrefixword(const pair<int, string>& node,
    //                    unsigned int numCompletions);
    // priority_queue 最小堆
    // 比较函数  p1<p2 返回真 否则为假  频率一样 字母越小 越大
    bool comparePair(const pair<int, string>& p1, const pair<int, string>& p2);
    bool comparePair_2(const pair<int, char>& p1, const pair<int, char>& p2);
    struct cmp {
        bool operator()(const pair<int, string>& a,
                        const pair<int, string>& b) {
            if (a.first == b.first) {
                return a.second < b.second;
            }

            return a.first > b.first;
        }
    };
    typedef priority_queue<pair<int, string>, vector<pair<int, string>>, cmp>
        my_quene;

  public:
    Node* root;
    // vector<pair<int, string>> prefixword;
    my_quene prefixword;
    my_quene underscoresword;
    /* DictionaryTrie constructor */
    DictionaryTrie();

    /** insert word to MWT
     *  return true if insert successfully
     */
    bool insert(string word, unsigned int freq);

    /** find word in MWT
     *  return true if find the word
     */
    bool find(string word) const;

    /** predict Completions function
     *  return top-k word in vector
     */
    vector<string> predictCompletions(string prefix,
                                      unsigned int numCompletions);

    /* TODO: add function header */
    vector<string> predictUnderscores(string pattern,
                                      unsigned int numCompletions);

    void predictUnderscoresHelper(Node*& node, string pattern,
                                  unsigned int numCompletions,
                                  unsigned int count, string str);

    /* DictionaryTrie destructor  */
    ~DictionaryTrie();
};
/**
 * @brief Descending order comparison function according to the word's
 * freuency
 */
// bool DictionaryTrie::cmp(pair<int, string>& a, pair<int, string>& b);

#endif  // DICTIONARY_TRIE_HPP
