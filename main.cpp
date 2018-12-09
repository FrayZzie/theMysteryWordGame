#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <vector>

using namespace std;

string drawLetters(string word)
{
    string drawedWord;
    int position = 0;

    while (0 != word.size())
    {
        position = rand() % word.size();
        drawedWord += word[position];
        word.erase(position, 1);
    }

    // Reroll the letters if the result is the word
    if (word == drawedWord && 1 < word.size())
    {
        return drawLetters(word);
    }

    return drawedWord;
}

string drawWordFromDictionary(string filePath)
{
    vector<string> words;
    string line;
    int lineCount = 0;
    ifstream dictionaryFile(filePath);
    if (dictionaryFile.is_open())
    {
        while (getline(dictionaryFile, line))
        {
            words.push_back(line);
            lineCount++;
        }
        dictionaryFile.close();
    }

    return words[rand() % lineCount];
}

bool guessWord(string targetWord)
{
    string testedWord;
    cout << "Quel est ce mot ? " << endl;

    cin >> testedWord;
    if (testedWord == targetWord)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void mysteryWordGame(string targetWord, int maxTentativeCount = 5)
{
    int tentativeCount (0);
    while (tentativeCount < maxTentativeCount)
    {
        if (guessWord(targetWord))
        {
            cout << "Bien jouer !" << endl;

            return;
        }
        cout << "Perdu !" << endl;
        tentativeCount ++;
    }
}

void clearTerminal()
{
    for(int i (0); i < 100; i++)
    {
        cout << endl;
    }
}

bool questionReplay()
{
    char response;
    cout << "Voulez vous rejouer ? (o/n)" << endl;
    cin >> response;
    if (response == 'o')
    {
        return true;
    }
    return false;
}

string drawWord()
{
    string targetWord;
    int playerCount;
    cout << "Voulez vous jouer seul ou a 2 ? (1/2)" << endl;
    cin >> playerCount;
    if (playerCount == 2)
    {
        cout << "Choisissez un mot" << endl;
        cin >> targetWord;

        return targetWord;
    }
    if (playerCount == 1)
    {
        return drawWordFromDictionary("dico.txt");
    }

}

int main()
{
    bool game(true);


    while (game)
    {
        string targetWord = drawWord();
        string mixedWord = drawLetters(targetWord);
        srand(time(0));
        clearTerminal();
        cout << "Le mot mixée est : " << mixedWord << endl;
        mysteryWordGame(targetWord);
        game = questionReplay();
    }
    cout << "Au revoir" << endl;
    return 0;
}
