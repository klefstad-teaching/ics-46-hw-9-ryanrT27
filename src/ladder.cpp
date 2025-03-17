#include "ladder.h"

//  Check the input right away to ensure the start and end words are not the same word, 
// because that condition may lead to an infinite loop! If invalid input 
// occurs, your program should print an error message.
void error(string word1, string word2, string msg){
    cout << "Error: " << '(' << word1 << word2 << ')' << endl;
}

// I used the concept of edit distance to compare words to see if they are neighbors. 
// (Hint: the lengths are either the same or differ by one character between neighbor words.)
bool edit_distance_within(const std::string& str1, const std::string& str2, int d){
    int w1size = str1.size();
    int w2size = str2.size();
    if (abs(w1size - w2size) > 1) return false;

    int charnum_difference = 0;
    if (w1size == w2size){
        for(int i = 0; i < w1size; ++i){
            if(str1[i] != str2[i]) ++charnum_difference;
            if (charnum_difference > d) return false;
        }
    }
    else {
        int i = 0, j = 0;
        while (i < w1size && j < w2size){
            if (str1[i] != str2[j]) {
                ++charnum_difference;
                if (charnum_difference > d) return false;
                if (w1size > w2size) ++i; //skip whichever word is longer after finding a mismatch
                else {++j;}
            }
            else{
                ++i;
                ++j;
            }
        }
    }
    if (i < w1size) charnum_difference += (w1size - 1);
    if (j < w2size) charnum_difference += (w2size - 2);
    return charnum_difference <= d;
}
bool is_adjacent(const string& word1, const string& word2) {
    
}
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){

}
void load_words(set<string> & word_list, const string& file_name){

}
void print_word_ladder(const vector<string>& ladder){

}
#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
void verify_word_ladder(){
    //as per write up
    set<string> word_list;

    load_words(word_list, "words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);

    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);

    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);

    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);

    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);

    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);

}