/*
* TextDialog.cpp
*/

#include "textdialog.h"

/*
* TextDialog
*/

TextDialog::TextDialog()
{
    
}

TextDialog::~TextDialog()
{
    
}

TextDialog::TextDialog(string speech)
{
    userString = speech;
    vector<string> words;
    Parser::tokenize(speech, words);
    string currDialog = "";
    
    //loop through and put into seperate dialogs.
    for(int word = 0; word < words.size(); word++)
    {
        if( currDialog.length() + words[word].length() + 1 > (LINE_LENGTH - 2) * NUM_LINES )
        {
            dialogs.push_back(currDialog);
            currDialog = "";
        }
        currDialog.append(" ");
        currDialog.append(words[word]);
    }
    dialogs.push_back(currDialog);
    iterator = 0;
}

void TextDialog::resetIterator()
{
    iterator = 0;
}

bool TextDialog::moreDialogs()
{
    return iterator < dialogs.size();
}

string TextDialog::getNextDialog()
{
    return dialogs[iterator++];   
}

