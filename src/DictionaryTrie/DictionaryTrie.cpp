/*
 * @Descripttion: It implements MWT to achieve auto-completer
 * included predict Underscores and predict Completions
 * @version: 1.0
 * @Author: Kaixin Lin
 * @Date: 2019-10-29 22:01:59
 */

#include "DictionaryTrie.hpp"
#include <iostream>

/* DictionaryTrie constructor */
DictionaryTrie::DictionaryTrie() { root = nullptr; }

/**
 * @name:   insert
 * @brief:  insert a word to MWT
 * @return: Return true if insert successfully
 */
bool DictionaryTrie::insert(string word, unsigned int freq) {
    return insert(root, word, freq, 0);
    // return insert(root, word, freq);
}

/**
 * @name:   find
 * @brief:  find word in MWT
 * @return: Return true if find the word
 */
bool DictionaryTrie::find(string word) const {
    if (root == nullptr) return false;
    if (word == "") return false;
    Node* cur = root;

    for (int i = 0; i < word.length() - 1; i++) {
        if (cur->map_word.find(word[i]) == cur->map_word.end()) return false;
        cur = cur->map_word[word[i]];
    }
    // the last key not equal
    if (cur->map_word.find(word[word.length() - 1]) == cur->map_word.end())
        return false;
    cur = cur->map_word[word[word.length() - 1]];
    return cur->freq > 0 ? true : false;
}

/**
 * @name:   predictCompletions
 * @brief:  predict Completions function
 * @return: Return a vector holding up to numCompletions of the most
 * frequent completions of prefix
 */
vector<string> DictionaryTrie::predictCompletions(string prefix,
                                                  unsigned int numCompletions) {
    if (numCompletions == 0 || prefix == "") return {};
    my_quene empty;
    swap(empty, prefixword);  // clear quene
    getAllchildren(root, prefix, numCompletions);
    // update numCompletions according to the prefixword's size
    numCompletions =
        numCompletions < prefixword.size() ? numCompletions : prefixword.size();

    vector<string> words(numCompletions);
    for (int j = 0; j < numCompletions; j++) {
        words[numCompletions - 1 - j] = prefixword.top().second;
        prefixword.pop();
    }

    return words;
}

/**
 * @name:   predictUnderscores
 * @brief:  predict Underscores function
 * @return: Return a vector holding up to numCompletions of the most
 * frequent valid completions of pattern
 */
std::vector<string> DictionaryTrie::predictUnderscores(
    string pattern, unsigned int numCompletions) {
    if (numCompletions == 0 || pattern == "") return {};
    Node* node = root;
    // clear underscoresword
    my_quene empty;
    swap(empty, underscoresword);

    predictUnderscoresHelper(node, pattern, numCompletions, 0, "");
    // update numCompletions
    numCompletions = numCompletions < underscoresword.size()
                         ? numCompletions
                         : underscoresword.size();

    vector<string> words(numCompletions);
    for (int j = 0; j < numCompletions; j++) {
        words[numCompletions - 1 - j] = underscoresword.top().second;
        underscoresword.pop();
    }

    return words;
}

/* DictionaryTrie destructor  */
DictionaryTrie::~DictionaryTrie() { deleteAll(root); }

/*insert help function*/
bool DictionaryTrie::insert(Node*& root, string word, unsigned int freq,
                            unsigned int count) {
    if (root == nullptr) root = new Node();
    Node* node = root;
    node->max_freq = node->max_freq > freq ? node->max_freq : freq;

    if (node->map_word.find(word[count]) == node->map_word.end()) {
        // the node doesn't exist  new Node
        node->map_word[word[count]] = new Node();

    } else {
        // if the end node exists and its frequency >0 the insert fails.
        if (count == word.length() - 1) {
            if (node->map_word[word[count]]->freq > 0) return false;
        }
    }
    // if the node is the end
    if (count == word.length() - 1) {
        Node* next = node->map_word[word[count]];
        next->freq = freq;
        next->max_freq = next->max_freq > freq ? next->max_freq : freq;
        return true;
    }
    // if subtree insert successfully, update the word_sort variable
    Node* nextNode = node->map_word[word[count]];
    bool sub = insert(nextNode, word, freq, count + 1);
    return true && sub;
}

/**
 * @name:   getAllchildren
 * @brief:  DFS function to look for all children
 */
void DictionaryTrie::getAllchildren(Node*& root, string prefix,
                                    unsigned int numCompletions) {
    Node* node = root;
    // run to the prefix's end word
    for (int i = 0; i < prefix.length(); ++i) {
        if (node->map_word.find(prefix[i]) != node->map_word.end()) {
            node = node->map_word[prefix[i]];
        } else {
            return;
        }
    }
    findChildren(node, prefix, numCompletions);
    return;
}

/**
 * @name:   findChildren
 * @brief:  DFS helper function to look for all children
 */
void DictionaryTrie::findChildren(Node*& node, string word,
                                  unsigned int numCompletions) {
    pair<int, char> curNode;    // store temp node in MWT
    pair<int, string> insNode;  // store temp node in prefixword
    my_node_quene myquene;
    if (node == nullptr) return;
    // if node exists, update the heap
    if (node->freq > 0) {
        insNode = make_pair(node->freq, word);
        if (prefixword.size() < numCompletions) {
            prefixword.push(insNode);
        } else {
            if (comparePair(prefixword.top(), insNode)) {
                prefixword.push(insNode);
                prefixword.pop();
            }
        }
    }
    // use heap to search kth biggest node according to the maxBelow frequency
    // iterator the whole node and push to the heap
    for (auto it : node->map_word) {
        curNode = make_pair(it.second->max_freq, it.first);
        myquene.push(curNode);
    }
    int length = myquene.size();
    // get the kth biggest children in this node
    for (int i = 0; i < length; ++i) {
        curNode = myquene.top();
        // if prefixword smallest node is bigger than the current node, break
        // the loop
        if (prefixword.size() >= numCompletions)
            if (prefixword.top().first > curNode.first) break;

        myquene.pop();
        string wordnext = word + curNode.second;
        findChildren(node->map_word[curNode.second], wordnext, numCompletions);
    }
}

/**
 * @name:   deleteAll
 * @brief:  delete destructor helper function
 */
void DictionaryTrie::deleteAll(Node*& root) {
    if (root == nullptr) return;
    for (auto it : root->map_word) {
        deleteAll(it.second);
    }
    delete root;
}
/*predictUnderscores Help function*/
void DictionaryTrie::predictUnderscoresHelper(Node*& root, string pattern,
                                              unsigned int num,
                                              unsigned int count, string str) {
    if (root == nullptr) return;
    Node* node = root;
    // when go to the end, insert
    if (count == pattern.size()) {
        if (node->freq > 0) {
            pair<int, string> insNode = make_pair(node->freq, str);
            if (underscoresword.size() < num) {
                underscoresword.push(insNode);
            } else {
                if (comparePair(underscoresword.top(), insNode)) {
                    underscoresword.push(insNode);
                    underscoresword.pop();
                }
            }
        }

        return;
    }
    if (pattern[count] != '_') {
        if (node->map_word.find(pattern[count]) != node->map_word.end()) {
            str += pattern[count];
            Node* next = node->map_word[pattern[count]];
            predictUnderscoresHelper(next, pattern, num, count + 1, str);
        } else
            return;
    } else {
        for (auto it = node->map_word.begin(); it != node->map_word.end();
             ++it) {
            string temp = str;
            temp += it->first;
            Node* next = node->map_word[it->first];
            predictUnderscoresHelper(next, pattern, num, count + 1, temp);
        }
    }
}
/**
 * @name:   comparePair
 * @brief:  compared function according to frequency and alphabetical order
 * @param:  Comparative variable
 * @return: Return true if p1 > p2
 */
bool DictionaryTrie::comparePair(const pair<int, string>& p1,
                                 const pair<int, string>& p2) {
    if (p1.first == p2.first) return p1.second > p2.second;
    return p1.first < p2.first;
}

// compare function for prefix
bool DictionaryTrie::cmp::operator()(const pair<int, string>& a,
                                     const pair<int, string>& b) {
    if (a.first == b.first) {
        return a.second < b.second;
    }

    return a.first > b.first;
}