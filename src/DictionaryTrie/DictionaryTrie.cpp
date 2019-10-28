/**
 * DictionaryTrie.cpp
 *
 * Author:Kaixin Lin
 * Finished PA2
 * It implements MWT to achieve auto-completer included predict Underscores and
 * predict Completions
 */
#include "DictionaryTrie.hpp"
#include <iostream>

/* TODO */
DictionaryTrie::DictionaryTrie() { root = nullptr; }

/* TODO */
bool DictionaryTrie::insert(string word, unsigned int freq) {
    return insert(root, word, freq, 0);
    // return insert(root, word, freq);
}

/* TODO */
bool DictionaryTrie::find(string word) const {
    if (root == nullptr) return false;
    Node* cur = root;

    for (int i = 0; i < word.length() - 1; i++) {
        if (cur->map_word.find(word[word.length() - 1]) == cur->map_word.end())
            return false;
        cur = cur->map_word[word[i]];
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
    my_quene empty;
    swap(empty, prefixword);  // clear quene
    getAllchildren(root, prefix, numCompletions);
    numCompletions =
        numCompletions < prefixword.size() ? numCompletions : prefixword.size();

    vector<string> words(numCompletions);
    for (int j = 0; j < numCompletions; j++) {
        // words[numCompletions - 1 - j] = prefixword.top().second;
        words[numCompletions - 1 - j] = prefixword.top().second;
        prefixword.pop();
    }

    return words;
}

/* TODO */
std::vector<string> DictionaryTrie::predictUnderscores(
    string pattern, unsigned int numCompletions) {
    Node* node = root;
    predictUnderscoresHelper(node, pattern, numCompletions, 0, "");
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

/* TODO */
DictionaryTrie::~DictionaryTrie() { deleteAll(root); }

bool DictionaryTrie::insert(Node*& root, string word, unsigned int freq,
                            unsigned int count) {
    if (root == nullptr) root = new Node();
    Node* node = root;
    bool isNew = false;
    node->max_freq = node->max_freq > freq ? node->max_freq : freq;

    if (node->map_word.find(word[count]) == node->map_word.end()) {
        // the node doesn't exist  new Node
        node->map_word[word[count]] = new Node();
        isNew = true;
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

        if (isNew) {
            node->word_sort.push_back(make_pair(next->max_freq, word[count]));
        } else {
            // find the object
            char character = word[count];
            auto it = find_if(node->word_sort.begin(), node->word_sort.end(),
                              [&character](const pair<int, char>& element) {
                                  return element.second == character;
                              });
            it->first = it->first > next->max_freq ? it->first : next->max_freq;
        }
        sort(node->word_sort.begin(), node->word_sort.end(),
             greater<pair<int, char>>());

        // node->word_sort.push(make_pair(freq, word[count]));
        // if ((node->word_sort1.empty()))
        //     node->word_sort1.push_back(make_pair(freq, word[count]));
        // else {
        //     pair<int, char> value = make_pair(freq, word[count]);
        //     auto pos =
        //         lower_bound(node->word_sort1.begin(), node->word_sort1.end(),
        //                     value, greater<pair<int, char>>());
        //     // auto pos = find_if(node->word_sort1.begin(),
        //     // node->word_sort1.end(),
        //     //                    [ns](auto s) { return s.first < ns.first;
        //     }); node->word_sort1.insert(pos, value);
        // }
        return true;
    }
    // if subtree insert successfully, update the word_sort variable
    Node* nextNode = node->map_word[word[count]];
    bool sub = insert(nextNode, word, freq, count + 1);
    if (sub == true) {
        if (isNew) {
            node->word_sort.push_back(
                make_pair(nextNode->max_freq, word[count]));
        } else {
            // find the object
            char character = word[count];
            auto it = find_if(node->word_sort.begin(), node->word_sort.end(),
                              [&character](const pair<int, char>& element) {
                                  return element.second == character;
                              });
            it->first =
                it->first > nextNode->max_freq ? it->first : nextNode->max_freq;
        }
        sort(node->word_sort.begin(), node->word_sort.end(),
             greater<pair<int, char>>());

        // node->word_sort.push(make_pair(freq, word[count]));

        // if ((node->word_sort1.empty()))
        //     node->word_sort1.push_back(make_pair(freq, word[count]));
        // else {
        //     pair<int, char> value = make_pair(freq, word[count]);
        //     auto pos =
        //         lower_bound(node->word_sort1.begin(), node->word_sort1.end(),
        //                     value, greater<pair<int, char>>());
        //     node->word_sort1.insert(pos, value);
        // }
    }

    return true && sub;
}

// bool DictionaryTrie::insert(Node*& root, string word, unsigned int freq) {
//     if (root == nullptr) root = new Node();
//     Node* node = root;

//     for (int i = 0; i < word.length(); i++) {
//         if (node->map_word.find(word[i]) == node->map_word.end()) {
//             // if this node doesn't have this character, new a Node
//             node->map_word[word[i]] = new Node();
//             // if to the this word's end
//             if (i == word.length() - 1) node->map_word[word[i]]->freq = freq;
//         } else {
//             // if exist this word, return false
//             if (i == word.length() - 1) {
//                 if (node->map_word[word[i]]->freq > 0)
//                     return false;
//                 else
//                     node->map_word[word[i]]->freq = freq;
//             }
//         }

//         // update max_freq variable
//         node->max_freq = node->max_freq > freq ? node->max_freq : freq;
//         node = node->map_word[word[i]];
//     }
//     // update max_freq variable
//     node->max_freq = node->max_freq > freq ? node->max_freq : freq;
//     return true;
// }
void DictionaryTrie::getAllchildren(Node*& root, string prefix,
                                    unsigned int numCompletions) {
    Node* node = root;
    string temp = prefix;
    unsigned int cnt = 0;
    // run to the prefix's end word
    for (int i = 0; i < prefix.length(); ++i) {
        if (node->map_word.find(prefix[i]) != node->map_word.end()) {
            node = node->map_word[prefix[i]];
        } else {
            return;
        }
    }
    findChildren(node, prefix, numCompletions);
    // while ((!(node->word_sort.empty())) && cnt < numCompletions) {
    //     findChildren(node, prefix, numCompletions);
    //     cnt++;
    // }
    // if (node->freq > 0) {
    //     prefixword.push(make_pair(node->freq, prefix));
    // }
    return;
}

//
// void DictionaryTrie::findChildren(Node*& root, string word,
//                                   unsigned int numCompletions) {
//     string temp = word;
//     Node* node = root;
//     if (node == nullptr) return;
//     pair<int, char> max_node = node->word_sort1[numCompletions];
//     while (max_node.first != node->map_word[max_node.second]->freq) {
//         temp += max_node.second;
//         node->word_sort.pop();
//         node = node->map_word[max_node.second];
//     }
// }
void DictionaryTrie::findChildren(Node*& node, string word,
                                  unsigned int numCompletions) {
    // Node* node = root;
    pair<int, char> curNode;
    pair<int, string> insNode;
    if (node == nullptr) return;
    // if (prefixword.size() >= numCompletions)  // heap max
    //     if ((prefixword.top().first > node->max_freq)) return;
    // if node exists
    if (node->freq > 0) {
        insNode = make_pair(node->freq, word);
        if (prefixword.size() < numCompletions) {
            prefixword.push(insNode);
        } else {
            if (prefixword.top() < insNode) {
                prefixword.push(insNode);
                prefixword.pop();
            }
        }
    }

    // iterator nodes according to max_frequency order
    // for (int i = 0; i < node->word_sort.size(); i++) {
    //     curNode = node->word_sort[i];
    //     // when current node < heap.min,  break down
    //     if (prefixword.size() >= numCompletions) {
    //         if (prefixword.top().first > curNode.first) {
    //             break;
    //         }
    //     }
    //     findChildren(node->map_word[curNode.second], word + curNode.second,
    //                  numCompletions);
    // }
    string temp;
    for (auto it : node->map_word) {
        if (it.second != nullptr) {
            temp = temp + it.first;
            findChildren(it.second, temp, numCompletions);
            temp = word;
        }
    }
}

//
// void DictionaryTrie::findChildren(Node*& root, string word,
//                                   unsigned int numCompletions) {
//     string temp = word;
//     Node* node = root;
//     if (node == nullptr) return;
//     pair<int, char> max_node = node->word_sort.top();
//     // // if (prefixword.size() >= numCompletions)
//     // //     // heap max
//     // //     if ((prefixword.top().first > node->max_freq)) return;
//     // pair<int, char> max_node = node->word_sort.top();
//
//     // while (max_node.first != node->map_word[max_node.second]->freq) {
//     //     temp += max_node.second;
//     //     node->word_sort.pop();
//     //     node = node->map_word[max_node.second];
//     //     max_node = node->word_sort.top();
//     //     }
//     // pair<int, string> test = make_pair(max_node.first, temp +
//     // max_node.second); prefixword.push(test); node->word_sort.pop();

//     if (max_node.first == node->map_word[max_node.second]->freq) {
//         pair<int, string> test =
//             make_pair(max_node.first, word + max_node.second);
//         prefixword.push(test);
//         node->word_sort.pop();
//     } else {
//         // no the end
//         temp = temp + max_node.second;
//         findChildren(node->map_word[max_node.second], temp,
//         numCompletions); node->word_sort.pop();
//     }

//     // if (!(node->word_sort.empty())) {
//     //     pair<int, char> max_node = node->word_sort.top();
//     //     temp = temp + max_node.second;
//     //     findChildren(node->map_word[max_node.second], temp,
//     numCompletions);
//     //     node->word_sort.pop();
//     // } else {
//     //     // add
//     //     if (node->freq > 0) {
//     //         pair<int, string> test = make_pair(node->freq, word);
//     //         if (prefixword.size() < numCompletions) {
//     //             prefixword.push(test);
//     //         } else {
//     //             if (prefixword.top() < test) {
//     //                 prefixword.pop();
//     //                 prefixword.push(test);
//     //             }
//     //         }
//     //     }
//     // }

//     // for(int i = 0;i<node->word_sort.size();i++){
//     //     temp = temp + node->word_sort[]
//     // }
//     // addPrefixword(make_pair(node->freq, word), numCompletions);
//     // while (!(node->word_sort.empty())) {
//     //     pair<int, char> max_node = node->word_sort.top();
//     //     temp = temp + max_node.second;
//     //     findChildren(node->map_word[max_node.second], temp,
//     numCompletions);
//     //     node->word_sort.pop();
//     //     temp = word;
//     // }
//     // for (auto it : node->map_word) {
//     //     if (it.second != nullptr) {
//     //         temp = temp + it.first;
//     //         findChildren(it.second, temp, numCompletions);
//     //         temp = word;
//     //     }
//     // }
// }
void DictionaryTrie::deleteAll(Node*& root) {
    if (root == nullptr) return;
    for (auto it : root->map_word) {
        deleteAll(it.second);
    }
    delete root;
}
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
                if (underscoresword.top() < insNode) {
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
// void DictionaryTrie::addPrefixword(const pair<int, string>& node,
//                                    unsigned int numCompletions) {
//     if (prefixword.size() < numCompletions) {
//         prefixword.push(node);
//     } else {
//         if (prefixword.top() < node) {
//             prefixword.pop();
//             prefixword.push(node);
//         }
//     }
//     // prefixword.push_back(node);
// }
// //bool DictionaryTrie::cmp(pair<int, string>& a, pair<int, string>& b) {
//     if (a.first == b.first) {
//         return a.second > b.second;
//     }

//     return a.first > b.first;
// }