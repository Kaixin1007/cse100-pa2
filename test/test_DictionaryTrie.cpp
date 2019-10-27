/**
 * TODO: test_DictionaryTrie.cpp
 *
 * Author:Kaixin Lin
 * Finished PA2
 * Test file about DictionaryTries
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
    vector<string> test, test1, test2;
    dict.insert("abc", 2);
    dict.insert("ab", 3);
    dict.insert("a", 10);
    // dict.insert("an", 12);
    dict.insert("and", 11);
    dict.insert("at", 9);
    dict.insert("ba", 5);
    dict.insert("aaa", 6);
    dict.insert("aef", 7);
    dict.insert("degr", 8);
    ASSERT_EQ(dict.find("ab"), true);
    ASSERT_EQ(dict.find("abeed"), false);
    ASSERT_EQ(dict.insert("ab", 5), false);
    test = dict.predictCompletions("a", 4);
    test1 = dict.predictCompletions("a", 2);
    // for (auto i : test) {
    //     cout << i << endl;
    // }
    cout << "stop!" << endl;
}
