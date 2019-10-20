/**
 * TODO: File Header
 *
 * Author:
 */
#include "DictionaryTrie.hpp"
#include <iostream>

/* TODO */
DictionaryTrie::DictionaryTrie() {
    root = nullptr;
    iszie = 0;
}

/* TODO */
bool DictionaryTrie::insert(string word, unsigned int freq) {
    return insert(root, word, freq);
}

/* TODO */
bool DictionaryTrie::find(string word) const {
    if (root == nullptr) return false;
    Node* cur = root;

    for (int i = 0; i < word.length() - 1; i++) {
        cur = cur->map_word[word[i]];
        if (cur == nullptr) return false;
    }
    // the last key not equal
    if (cur->map_word.find(word[word.length() - 1]) == cur->map_word.end())
        return false;
    cur = cur->map_word[word[word.length() - 1]];
    return cur->freq > 0 ? true : false;
}

/* TODO */
vector<string> DictionaryTrie::predictCompletions(string prefix,
                                                  unsigned int numCompletions) {
    my_quene q;
    vector<string> words;
    getAllchildren(root, prefix);

    for (auto i : prefixword) {
        q.push(i);
        // words.push_back(i.second);
    }
    numCompletions = numCompletions < q.size() ? numCompletions : q.size();
    for (int j = 0; j < numCompletions; j++) {
        words.push_back((q.top().second));
        q.pop();
    }

    return words;
}

/* TODO */
std::vector<string> DictionaryTrie::predictUnderscores(
    string pattern, unsigned int numCompletions) {
    return {};
}

/* TODO */
DictionaryTrie::~DictionaryTrie() { deleteAll(root); }

bool DictionaryTrie::insert(Node*& root, string word, unsigned int freq) {
    if (root == nullptr) root = new Node();
    Node* node = root;
    for (int i = 0; i < word.length(); i++) {
        if (node->map_word.find(word[i]) == node->map_word.end()) {
            node->map_word[word[i]] = new Node();
            if (i == word.length() - 1) node->map_word[word[i]]->freq = freq;
        } else {
            if (i == word.length() - 1) {
                if (node->map_word[word[i]]->freq > 0)
                    return false;
                else
                    node->map_word[word[i]]->freq = freq;
            }
        }
        node = node->map_word[word[i]];
    }
    return true;
}
void DictionaryTrie::getAllchildren(Node*& root, string prefix) {
    Node* node = root;
    string temp = prefix;
    for (int i = 0; i < prefix.length(); i++) {
        if (node->map_word.find(prefix[i]) != node->map_word.end()) {
            node = node->map_word[prefix[i]];
        } else {
            return;
        }
    }
    if (node->freq > 0) prefixword.push_back(make_pair(node->freq, prefix));
    for (auto it : node->map_word) {
        if (it.second != nullptr) {
            temp = temp + it.first;
            findChildren(it.second, temp);
            temp = prefix;
        }
    }
    return;
}
void DictionaryTrie::findChildren(Node*& node, string word) {
    string temp = word;
    if (node == nullptr) return;
    if (node->freq > 0) prefixword.push_back(make_pair(node->freq, word));
    for (auto it : node->map_word) {
        if (it.second != nullptr) {
            temp = temp + it.first;
            findChildren(it.second, temp);
            temp = word;
        }
    }
}
void DictionaryTrie::deleteAll(Node*& root) {
    if (root == nullptr) return;
    for (auto it : root->map_word) {
        if (it.second != nullptr) {
            deleteAll(it.second);
            delete it.second;
        }
    }
    delete root;
}
// void getAllchildren1(string prefix) { getAllchildren(this.root, prefix); }