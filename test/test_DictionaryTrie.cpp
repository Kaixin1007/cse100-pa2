/**
 * TODO: File HEADER
 *
 * Author:
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "DictionaryTrie.hpp"
#include "util.hpp"

using namespace std;
using namespace testing;

/* Empty test */
TEST(DictTrieTests, EMPTY_TEST) {
    DictionaryTrie dict;

    ASSERT_EQ(dict.find("abrakadabra"), false);
}
TEST(DictTrieTests, INSERT_TEST) {
    DictionaryTrie dict;
    vector<string> test;
    dict.insert("abc", 2);
    dict.insert("ab", 3);
    dict.insert("a", 4);
    dict.insert("ba", 5);
    dict.insert("aaaaaaa", 6);
    dict.insert("aefgw", 7);
    dict.insert("degre", 3);
    ASSERT_EQ(dict.find("ab"), true);
    ASSERT_EQ(dict.find("abeed"), false);
    ASSERT_EQ(dict.insert("ab", 5), false);
    // cout << dict.predictCompletions("a", 10) << endl;
    test = dict.predictCompletions("a", 10);
    // for (auto i : test) {
    //     cout << i << endl;
    // }
    cout << "stop!" << endl;
}

/* TODO */
