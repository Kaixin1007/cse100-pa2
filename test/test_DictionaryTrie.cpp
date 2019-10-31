/*
 * @Descripttion: Test file about DictionaryTries' function
 * @version: 1.0
 * @Author: Kaixin Lin
 * @Date: 2019-10-29 22:01:59
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
/* insert test */
TEST(DictTrieTests, INSERT_TEST) {
    DictionaryTrie dict;
    vector<string> test, test1, test2;
    dict.insert("and", 15);
    dict.insert("ant", 15);
    dict.insert("at", 9);
    dict.insert("ba", 5);
    dict.insert("aaa", 6);
    dict.insert("aef", 7);
    dict.insert("degr", 8);
    dict.insert("american", 12);
    dict.insert("america", 11);
    dict.insert("am", 16);
    dict.insert("again", 13);
    dict.insert("aga", 1);
    dict.insert("a", 11);
    ASSERT_EQ(dict.find("at"), true);
    ASSERT_EQ(dict.find("abeed"), false);
    ASSERT_EQ(dict.insert("a", 5), false);
    test = dict.predictCompletions("a", 8);
    test1 = dict.predictCompletions("am", 8);
    test2 = dict.predictCompletions("an", 8);
}
// underscores test
TEST(DictTrieTests, UNDERSCORES_TEST) {
    vector<string> t1, t2;
    DictionaryTrie dict;
    dict.insert("and", 15);
    dict.insert("at", 9);
    dict.insert("ba", 5);
    dict.insert("aaa", 6);
    dict.insert("aef", 7);
    dict.insert("degr", 8);
    dict.insert("american", 12);
    dict.insert("america", 11);
    dict.insert("am", 15);
    dict.insert("again", 13);
    dict.insert("aga", 1);
    dict.insert("a", 11);
    dict.insert("ant", 15);

    t1 = dict.predictUnderscores("__", 10);
    t2 = dict.predictUnderscores("_a", 10);
}