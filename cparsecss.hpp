//  ------------------------------------------------------------
//	RenderLib (February 2020)
//  Copyright(c) 2019 - 2021 Srdzan Kostenarov
//  e-mail: srdzan.kostenarov@yahoo.com
//  ------------------------------------------------------------


#ifndef CPARSECSS_H
#define CPARSECSS_H
#include <string>
#include <vector>

#define SELECTOR 0
#define DECLARATIONNAME 1
#define DECLARATIONVALUE 2

using namespace std;

typedef struct {
    string selector;
    string name;
    string value;
} typeData;

typedef vector<typeData> typeListData;

typedef struct {
    string name;
    string value;
    long long name_start_pos;
    long long name_end_pos;
    long long value_start_pos;
    long long value_end_pos;
} CSSDeclaration;

typedef struct {
    string selector;
    vector<CSSDeclaration> declarations;
} CSSItem;

typedef struct {
    string orig;
    CSSItem info;
} CSSItemElement;

struct StateTypeE {
    long long  count;
    char cssChar;
};


/*
   The CParseCSS class is dedicated to parse css content
*/
class CParseCSS 
{
public:
    explicit CParseCSS();
    void parse(const string&);
    typeListData getData();

private:
    void CreateCSSParts(string css, vector<string>& listCss);
    CSSItem  CreateCSSDetails(string css);
    void convertToTypeData();

private:
    vector<CSSItemElement> listelements;
    vector<typeData> mData;
};


struct StateType {
    long long  count;
    char cssChar;
};


/*
    CParserCSSContent is class based on state machine pattern,
    dedicated to split css content into list of css items
    each items contain css seloector, names and values
*/
class CParserCSSContent
{
    class State* current;
public:
    CParserCSSContent();
    void setCurrent(State* s) {
        current = s;
    }
    void leftBracked(StateType attr);
    void rightBracked(StateType attr);
    void character(StateType attr);
public:
    int numLeftBracked;
    int numRightBracked;
    string itemString;
    vector<string> listcss;
};


class State
{
public:
    virtual void leftBracked(CParserCSSContent* m, StateType attr);
    virtual void rightBracked(CParserCSSContent* m, StateType attr);
    virtual void character(CParserCSSContent* m, StateType attr);
};


class LBRACKED : public State
{
public:
    LBRACKED();
    ~LBRACKED();
    void leftBracked(CParserCSSContent* m, StateType attr);
    void rightBracked(CParserCSSContent* m, StateType attr);
    void character(CParserCSSContent* m, StateType attr);
};

class RBRACKED : public State
{
public:
    RBRACKED();
    ~RBRACKED();
    void leftBracked(CParserCSSContent* m, StateType attr);
    void rightBracked(CParserCSSContent* m, StateType attr);
    void character(CParserCSSContent* m, StateType attr);
};

class CHARACTER : public State
{
public:
    CHARACTER();
    ~CHARACTER();
    void leftBracked(CParserCSSContent* m, StateType attr);
    void rightBracked(CParserCSSContent* m, StateType attr);
    void character(CParserCSSContent* m, StateType attr);
};

/*
    CParserCSSElement is class based on state machine pattern,
    dedicated to parse css content item to get
    css seloector, names and values
*/
class CParserCSSElement
{
    class Statelement* current;
public:
    CParserCSSElement();
    void setCurrent(Statelement* s) {
        current = s;
    }
    void leftBracked(StateTypeE attr);
    void rightBracked(StateTypeE attr);
    void character(StateTypeE attr);
    void colon(StateTypeE attr);
    void semicolon(StateTypeE attr);

    int numLeftBracked;
    int numRightBracked;
    string itemString;
    string selectorString;
    string declarationNameString;
    string declarationValueString;
    vector<string> listcss;
    void setState(int estate) { mstate = estate; }
    int getState() { return mstate; }
    CSSItem itemCSS;
    long long nameStartPos;
    long long nameEndPos;
    long long valueStartPos;
    long long valueEndPos;
private:
    int mstate;
};


class Statelement
{
public:
    virtual void leftBracked(CParserCSSElement* m, StateTypeE attr);
    virtual void rightBracked(CParserCSSElement* m, StateTypeE attr);
    virtual void character(CParserCSSElement* m, StateTypeE attr);
    virtual void colon(CParserCSSElement* m, StateTypeE attr);
    virtual void semicolon(CParserCSSElement* m, StateTypeE attr);
};


class LBRACKED_E : public Statelement
{
public:
    LBRACKED_E();
    ~LBRACKED_E();
    void leftBracked(CParserCSSElement* m, StateTypeE attr);
    void rightBracked(CParserCSSElement* m, StateTypeE attr);
    void character(CParserCSSElement* m, StateTypeE attr);
    void colon(CParserCSSElement* m, StateTypeE attr);
    void semicolon(CParserCSSElement* m, StateTypeE attr);
};

class RBRACKED_E : public Statelement
{
public:
    RBRACKED_E();
    ~RBRACKED_E();
    void leftBracked(CParserCSSElement* m, StateTypeE attr);
    void rightBracked(CParserCSSElement* m, StateTypeE attr);
    void character(CParserCSSElement* m, StateTypeE attr);
    void colon(CParserCSSElement* m, StateTypeE attr);
    void semicolon(CParserCSSElement* m, StateTypeE attr);
};

class CHARACTER_E : public Statelement
{
public:
    CHARACTER_E();
    ~CHARACTER_E();
    void leftBracked(CParserCSSElement* m, StateTypeE attr);
    void rightBracked(CParserCSSElement* m, StateTypeE attr);
    void character(CParserCSSElement* m, StateTypeE attr);
    void colon(CParserCSSElement* m, StateTypeE attr);
    void semicolon(CParserCSSElement* m, StateTypeE attr);
};

class COLON_E : public Statelement
{
public:
    COLON_E();
    ~COLON_E();
    void leftBracked(CParserCSSElement* m, StateTypeE attr);
    void rightBracked(CParserCSSElement* m, StateTypeE attr);
    void character(CParserCSSElement* m, StateTypeE attr);
    void colon(CParserCSSElement* m, StateTypeE attr);
    void semicolon(CParserCSSElement* m, StateTypeE attr);
};

class SEMICOLON_E : public Statelement
{
public:
    SEMICOLON_E();
    ~SEMICOLON_E();
    void leftBracked(CParserCSSElement* m, StateTypeE attr);
    void rightBracked(CParserCSSElement* m, StateTypeE attr);
    void character(CParserCSSElement* m, StateTypeE attr);
    void colon(CParserCSSElement* m, StateTypeE attr);
    void semicolon(CParserCSSElement* m, StateTypeE attr);
};


 /*
  * constructor
  */
CParseCSS::CParseCSS() {

}

/*
 * parser
 */
void CParseCSS::parse(const string& pss) {
    vector<string> listCss;
    // function CreateCSSParts split css code into list of css parts
    CreateCSSParts(pss, listCss);

    listelements.clear();

    // loop into css parts to extract values
    for (size_t i = 0; i < listCss.size(); i++) {
        CSSItemElement item;
        // keep css part without changes into itemC.orig values
        item.orig = listCss.at(i);

        // parse css part to extract names ,values and position in string
        item.info = CreateCSSDetails(listCss.at(i));

        // push back extracted data into listelements
        listelements.push_back(item);
    }
    // Data from list 'listelements' are analized and prepared for CEditor class
    convertToTypeData();
}

/*
 * Create list of css items from css string
*/
void CParseCSS::CreateCSSParts(string css, vector<string>& listCss) {

    // array of callback functions
    void(CParserCSSContent:: * ptrs[])(StateType attr) = {
        &CParserCSSContent::leftBracked,
        &CParserCSSContent::rightBracked,
        &CParserCSSContent::character,
    };

    CParserCSSContent fsm;
    int num;
    long long count = 0;

    // loop into css content 
    for (string::iterator it = css.begin(); it != css.end(); it++)
    {
        StateType attr;
        attr.count = count;
        attr.cssChar = *it;
        count++;
        if (*it == '{') {
            //type leftBracked
            num = 0;
        }
        else if (*it == '}') {
            //type rigntBracked
            num = 1;
        }
        else {
            num = 2;
        }

        // call the callback function
        (fsm.*ptrs[num])(attr);
    }
    listCss = fsm.listcss;
    fsm.listcss.clear();
}

// * Create details info from css itemC
CSSItem CParseCSS::CreateCSSDetails(string css) {
    // array of callback functions
    void(CParserCSSElement:: * ptrs[])(StateTypeE attr) = {
        &CParserCSSElement::leftBracked,
        &CParserCSSElement::rightBracked,
        &CParserCSSElement::colon,
        &CParserCSSElement::semicolon,
        &CParserCSSElement::character,
    };

    // set values
    CParserCSSElement fsm;
    int num;
    long long count = 0;

    // loop into css string content (char by char)
    for (string::iterator it = css.begin(); it != css.end(); it++)
    {
        StateTypeE attr;
        attr.count = count;
        attr.cssChar = *it;
        count++;
        if (*it == '{') {
            //type leftBracked
            num = 0;
        }
        else if (*it == '}') {
            //type rigntBracked
            num = 1;
        }
        else if (*it == ':') {
            //type column
            num = 2;
        }
        else if (*it == ';') {
            //type semicolumn
            num = 3;
        }
        else {
            num = 4;
        }

        // call callback function
        (fsm.*ptrs[num])(attr);
    }

    // return parsed items
    return fsm.itemCSS;
}


void CParseCSS::convertToTypeData() {
    mData.clear();

    // loop into vector of items
    for (size_t i = 0; i < listelements.size(); i++) {
        CSSItem info = listelements.at(i).info;
        //info.selector;
        for (size_t j = 0; j < info.declarations.size(); j++) {
            //set values
            typeData item;
            item.selector = info.selector;
            item.name = info.declarations.at(j).name;
            item.value = info.declarations.at(j).value;
            mData.push_back(item);
        }
    }
}


typeListData CParseCSS::getData() {
    return mData;
}


// class stateMachine 
CParserCSSContent::CParserCSSContent() {
    current = new CHARACTER();
    //cout << '\n';
    numLeftBracked = 0;
}

// base fuction leftBracked
void CParserCSSContent::leftBracked(StateType attr) {
    current->leftBracked(this, attr);
}

// base fuction rightBracked
void CParserCSSContent::rightBracked(StateType attr) {
    current->rightBracked(this, attr);
}

// base fuction character
void CParserCSSContent::character(StateType attr) {
    current->character(this, attr);
}

// class State;
void State::leftBracked(CParserCSSContent* m, StateType attr) {
}
void State::rightBracked(CParserCSSContent* m, StateType attr) {
}
void State::character(CParserCSSContent* m, StateType attr) {
}


// type character
CHARACTER::CHARACTER() {

}

CHARACTER::~CHARACTER() {

}

// previous state character, new leftbracked 
void CHARACTER::leftBracked(CParserCSSContent* m, StateType attr) {
    // set char into string vector
    m->itemString.push_back(attr.cssChar);

    // set new state
    m->setCurrent(new LBRACKED());
    m->numLeftBracked++;
    delete this;
}

// previous state character, new rightbracked 
void CHARACTER::rightBracked(CParserCSSContent* m, StateType attr) {
    // set char into string vector
    m->itemString.push_back(attr.cssChar);

    // string is pushback into vector of strings
    m->numRightBracked++;
    if (m->numLeftBracked == m->numRightBracked) {
        m->listcss.push_back(m->itemString);
        m->itemString.clear();
    }

    // set new state
    m->setCurrent(new RBRACKED());
    delete this;
}

// previous state character, new character
void CHARACTER::character(CParserCSSContent* m, StateType attr) {
    // set char into string vector
    m->itemString.push_back(attr.cssChar);
}

// type left bracked
LBRACKED::LBRACKED() {

}

LBRACKED::~LBRACKED() {

}

// previous state leftbracked, new leftbracked 
void LBRACKED::leftBracked(CParserCSSContent* m, StateType attr) {
    // set char into string vector
    m->itemString.push_back(attr.cssChar);
    m->numLeftBracked++;

    //set new state
    m->setCurrent(new LBRACKED());
    delete this;
}

// previous state leftbracked, new rightbracked 
void LBRACKED::rightBracked(CParserCSSContent* m, StateType attr) {
    m->numRightBracked++;

    // set new state
    m->setCurrent(new RBRACKED());
    delete this;
}

// previous state leftbracked, new character
void LBRACKED::character(CParserCSSContent* m, StateType attr) {
    // set char into string vector
    m->itemString.push_back(attr.cssChar);

    // set new state
    m->setCurrent(new CHARACTER());
    delete this;
}

// type right bracked
RBRACKED::RBRACKED() {

}

RBRACKED::~RBRACKED() {

}

// previous state rightbracked, new leftbracked 
void RBRACKED::leftBracked(CParserCSSContent* m, StateType attr) {
    // set new state
    m->setCurrent(new LBRACKED());
    delete this;
}

// previous state rightbracked, new rightbracked 
void RBRACKED::rightBracked(CParserCSSContent* m, StateType attr) {
    // set char into string vector
    m->itemString.push_back(attr.cssChar);

    m->numRightBracked++;
    if (m->numLeftBracked == m->numRightBracked) {
        m->listcss.push_back(m->itemString);
        m->itemString.clear();
    }

    //set new state
    m->setCurrent(new RBRACKED());
    delete this;
}

// previous state rightbracked, new character
void RBRACKED::character(CParserCSSContent* m, StateType attr) {
    // set char into string vector
    m->itemString.push_back(attr.cssChar);

    // set new state
    m->setCurrent(new CHARACTER());
    delete this;
}


// constructor
CParserCSSElement::CParserCSSElement() {
    current = new CHARACTER_E();
    //    cout << '\n';
    numLeftBracked = 0;
    setState(SELECTOR);
}

// base fuction leftBracked
void CParserCSSElement::leftBracked(StateTypeE attr) {
    current->leftBracked(this, attr);
}

// base fuction rightBracked
void CParserCSSElement::rightBracked(StateTypeE attr) {
    current->rightBracked(this, attr);
}

// base fuction character
void CParserCSSElement::character(StateTypeE attr) {
    current->character(this, attr);
}

// base fuction colon
void CParserCSSElement::colon(StateTypeE attr) {
    current->colon(this, attr);
}

// base fuction semicolon
void CParserCSSElement::semicolon(StateTypeE attr) {
    current->semicolon(this, attr);
}


// class State;
void Statelement::leftBracked(CParserCSSElement* m, StateTypeE attr) {
}
void Statelement::rightBracked(CParserCSSElement* m, StateTypeE attr) {
}
void Statelement::character(CParserCSSElement* m, StateTypeE attr) {
}
void Statelement::colon(CParserCSSElement* m, StateTypeE attr) {
}
void Statelement::semicolon(CParserCSSElement* m, StateTypeE attr) {
}

// type character
CHARACTER_E::CHARACTER_E() {

}

CHARACTER_E::~CHARACTER_E() {

}

// previous state character, new leftbracked 
void CHARACTER_E::leftBracked(CParserCSSElement* m, StateTypeE attr) {
    // push char in string vector
    m->itemString.push_back(attr.cssChar);

    //set new state	
    m->setCurrent(new LBRACKED_E());

    m->numLeftBracked++;
    if (m->numLeftBracked == 1) {
        m->setState(DECLARATIONNAME);
        m->nameStartPos = attr.count + 1;
    }
    else if (m->numLeftBracked > 1) {
        //TODO
    }

    delete this;
}

// previous state character, new rightbracked 
void CHARACTER_E::rightBracked(CParserCSSElement* m, StateTypeE attr) {
    // push char in string vector
    m->itemString.push_back(attr.cssChar);

    //set new state
    m->setCurrent(new RBRACKED_E());

    m->numRightBracked++;
    delete this;
}

// previous state character, new character 
void CHARACTER_E::character(CParserCSSElement* m, StateTypeE attr) {

    // push char in string vector
    m->itemString.push_back(attr.cssChar);

    if (m->getState() == DECLARATIONNAME) {
        m->declarationNameString.push_back(attr.cssChar);
    }
    else if (m->getState() == DECLARATIONVALUE) {
        m->declarationValueString.push_back(attr.cssChar);
    }
    else if (m->getState() == SELECTOR) {
        if (attr.cssChar == '\n') {
            m->selectorString.clear();
        }
        else {
            m->selectorString.push_back(attr.cssChar);
        }
    }
}

// previous state character, new colon 
void CHARACTER_E::colon(CParserCSSElement* m, StateTypeE attr) {
    if (m->getState() == DECLARATIONNAME) {
        m->setState(DECLARATIONVALUE);
        m->nameEndPos = attr.count;
        m->valueStartPos = attr.count + 1;

        // set new state
        m->setCurrent(new COLON_E());
        delete this;
    }
    else if (m->getState() == SELECTOR) {
        // push char in string vector
        m->itemString.push_back(attr.cssChar);
    }
}

// previous state character, new semicolon
void CHARACTER_E::semicolon(CParserCSSElement* m, StateTypeE attr) {
    if (m->getState() == DECLARATIONVALUE) {
        m->setState(DECLARATIONNAME);
        m->valueEndPos = attr.count;
    }

    // set new state
    m->setCurrent(new SEMICOLON_E());
    delete this;
}



// type left bracked
LBRACKED_E::LBRACKED_E() {

}

LBRACKED_E::~LBRACKED_E() {

}

void LBRACKED_E::leftBracked(CParserCSSElement* m, StateTypeE attr) {

}

// previous state leftbracked, new rightbracked
void LBRACKED_E::rightBracked(CParserCSSElement* m, StateTypeE attr) {
    //set new state
    m->setCurrent(new RBRACKED_E());

    m->numRightBracked++;
    delete this;
}

// previous state leftbracked, new character
void LBRACKED_E::character(CParserCSSElement* m, StateTypeE attr) {
    // push char in string vector
    m->itemString.push_back(attr.cssChar);

    if (m->getState() == SELECTOR) {
        m->setState(DECLARATIONNAME);
    }

    //set new state
    m->setCurrent(new CHARACTER_E());
    delete this;
}

// previous state leftbracked, new colon
void LBRACKED_E::colon(CParserCSSElement* m, StateTypeE attr) {
    //set new state
    m->setCurrent(new COLON_E());
    delete this;
}

// previous state leftbracked, new semicolon
void LBRACKED_E::semicolon(CParserCSSElement* m, StateTypeE attr) {
    //set new state
    m->setCurrent(new SEMICOLON_E());
    delete this;
}


// type right bracked
RBRACKED_E::RBRACKED_E() {

}

RBRACKED_E::~RBRACKED_E() {

}

// previous state rightbracked, new leftbracked
void RBRACKED_E::leftBracked(CParserCSSElement* m, StateTypeE attr) {
    // set new state
    m->setCurrent(new LBRACKED_E());
    delete this;
}

// previous state rightbracked, new rightbracked
void RBRACKED_E::rightBracked(CParserCSSElement* m, StateTypeE attr) {
}

// previous state rightbracked, new character
void RBRACKED_E::character(CParserCSSElement* m, StateTypeE attr) {
    if (m->numLeftBracked == m->numRightBracked) {
        // push string vector into list of css items
        m->listcss.push_back(m->itemString);
        m->itemString.clear();
    }
    m->setCurrent(new CHARACTER_E());
    delete this;
}

// previous state rightbracked, new colon
void RBRACKED_E::colon(CParserCSSElement* m, StateTypeE attr) {
    // set new state
    m->setCurrent(new COLON_E());
    delete this;
}

// previous state rightbracked, new semicolon
void RBRACKED_E::semicolon(CParserCSSElement* m, StateTypeE attr) {
    //set new state
    m->setCurrent(new SEMICOLON_E());
    delete this;
}


// type right bracked
COLON_E::COLON_E() {

}

COLON_E::~COLON_E() {

}
// previous state colon, new leftbracked
void COLON_E::leftBracked(CParserCSSElement* m, StateTypeE attr) {
    // set new state
    m->setCurrent(new LBRACKED_E());
    delete this;
}

// previous state colon, new rightbracked
void COLON_E::rightBracked(CParserCSSElement* m, StateTypeE attr) {
    //set new state
    m->setCurrent(new RBRACKED_E());
    delete this;
}

// previous state colon, new character
void COLON_E::character(CParserCSSElement* m, StateTypeE attr) {
    // set new state
    m->setCurrent(new CHARACTER_E());
    delete this;
}

// previous state colon, new colon
void COLON_E::colon(CParserCSSElement* m, StateTypeE attr) {
    // set new state	
    m->setCurrent(new COLON_E());
    delete this;
}

// previous state colon, new semicolon
void COLON_E::semicolon(CParserCSSElement* m, StateTypeE attr) {
    // set new state
    m->setCurrent(new SEMICOLON_E());
    delete this;
}


// type right bracked
SEMICOLON_E::SEMICOLON_E() {

}

SEMICOLON_E::~SEMICOLON_E() {

}

// previous state semicolon, new leftbracked
void SEMICOLON_E::leftBracked(CParserCSSElement* m, StateTypeE attr) {
    // set new state
    m->setCurrent(new LBRACKED_E());
    delete this;
}

// previous state semicolon, new rightbracked
void SEMICOLON_E::rightBracked(CParserCSSElement* m, StateTypeE attr) {
    //set new state
    m->setCurrent(new RBRACKED_E());
    delete this;
}

// previous state semicolon, new character
void SEMICOLON_E::character(CParserCSSElement* m, StateTypeE attr) {

    /*
     prepare item with name, value
     and position data
     and push back into itemCSS
    */
    CSSDeclaration itemDeclaration;
    itemDeclaration.name = m->declarationNameString;
    itemDeclaration.name_start_pos = m->nameStartPos;
    itemDeclaration.name_end_pos = m->nameEndPos;
    itemDeclaration.value = m->declarationValueString;
    itemDeclaration.value_start_pos = m->valueStartPos;
    itemDeclaration.value_end_pos = m->valueEndPos;
    m->declarationNameString.clear();
    m->declarationValueString.clear();
    if (m->getState() != SELECTOR) {
        m->itemCSS.declarations.push_back(itemDeclaration);
        m->itemCSS.selector = m->selectorString;
    }
    m->nameStartPos = attr.count;

    // set new state
    m->setCurrent(new CHARACTER_E());
    delete this;
}

// previous state semicolon, new colon
void SEMICOLON_E::colon(CParserCSSElement* m, StateTypeE attr) {
    // set new state
    m->setCurrent(new COLON_E());
    delete this;
}

void SEMICOLON_E::semicolon(CParserCSSElement* m, StateTypeE attr) {
    // set new state
    m->setCurrent(new SEMICOLON_E());
    delete this;
}

#endif // CPARSECSS_H
