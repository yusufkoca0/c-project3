how to compile and run:
> g++ -o Main *.cpp -std=c++11
> ./Main  input1.txt output.txt

input1.txt includes the commands.

insert(k,v): inserts the word k to the trie and matches it with the its translation v.

search(k): searchs the word k in the trie dictionary.

delete(k): deletes the word k from the trie.

list: lists the dictionary.

Program constructs a dictionary using a trie.