/*
* TextDialog.h
*/
#ifndef _DEFINED_textarea
#define _DEFINED_textarea

#include <string>
#include "common_game.h"
#include "parser.h"

using namespace std;



class TextDialog
{
    public:
        TextDialog();
        TextDialog(string speech);
        ~TextDialog();
        
        //reset the iterator
        void resetIterator();
        bool moreDialogs();
        string getNextDialog();
        void setAction(string);
        string getAction();
        
        
    private:
        string userString;
        vector<string> dialogs;
        int iterator; 
        string action;
        
};

#endif
