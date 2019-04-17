Hash(int hashTableSize);
~Hash();
void addWord(std::string word);
bool isInTable(std::string word);
void incrementCount(std::string word);
void printTopN(int n);
int getNumCollisions();
int getNumItems();
int getTotalNumWords();

/* member functions */
unsigned int getHash(std::string word);
wordItem* searchTable(std::string word);