#include "ladder.h"

//  Check the input right away to ensure the start and end words are not the same word, 
// because that condition may lead to an infinite loop! If invalid input 
// occurs, your program should print an error message.
void error(string word1, string word2, string msg){
    cout << "Error: " << '(' << word1 << word2 << ')' << msg << endl;
}

// I used the concept of edit distance to compare words to see if they are neighbors. 
// (Hint: the lengths are either the same or differ by one character between neighbor words.)
bool edit_distance_within(const std::string& str1, const std::string& str2, int d){
    int w1size = str1.size();
    int w2size = str2.size();
    if (abs(w1size - w2size) > d) return false;

    int charnum_difference = 0;
    int i = 0, j = 0;

    if (w1size == w2size){
        for(; i < w1size; ++i){
            if(str1[i] != str2[i]) ++charnum_difference;
            if (charnum_difference > d) return false;
        }
    }
    else {
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
        if (i < w1size || j < w2size) ++charnum_difference;
    }
    return charnum_difference <= d;
}
bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    if (begin_word == end_word) {
        error(begin_word, end_word, "Words cannot be equal.");
        return {};
    }
    //start word ladder q
    queue<vector<string>> word_ladder;
    word_ladder.push({begin_word});
    // create set of strings visited
    set<string> been_visited;
    been_visited.insert(begin_word);

    while (!word_ladder.empty()){
        vector<string> lad = word_ladder.front();
        word_ladder.pop();
        string last_word = lad.back();
        for (const string& word : word_list) {
            if (is_adjacent(last_word, word) && been_visited.find(word) == been_visited.end()){
                been_visited.insert(word);
                vector<string> new_ladder = lad;
                new_ladder.push_back(word);
                if (word == end_word) return new_ladder;
                word_ladder.push(new_ladder);
            }
        }
    }
    return {};
}
void load_words(set<string> & word_list, const string& file_name){
    ifstream file(file_name);
    if (!file) {
        //couldn't open file womp womp
        return;
    }
    string word;
    while (file >> word) {
        word_list.insert(word);
    }
    file.close();
}
void print_word_ladder(const vector<string>& ladder){
    if (ladder.empty()) return;
    for (size_t i = 0; i < ladder.size(); ++i)
        cout << ladder[i] << " ";
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
void verify_word_ladder(){
    //as per write up
    set<string> word_list;

    load_words(word_list, "src/words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);

    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);

    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);

    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);

    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);

    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);

}