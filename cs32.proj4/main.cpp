//main.cpp

#include "PersonProfile.h"
#include "AttributeTranslator.h"
#include "MemberDatabase.h"
#include "MatchMaker.h"
#include "provided.h"
#include "RadixTree.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
//#include "translator.txt"
//using namespace std;

const std::string MEMBERS_FILE    = "members.txt";
const std::string TRANSLATOR_FILE = "translator.txt";

bool findMatches(MemberDatabase& mdb, AttributeTranslator& at);

int main() {
    
    
    /*
    
    AttributeTranslator a;
    vector<AttValPair> v;
    a.Load(TRANSLATOR_FILE);
    v = a.FindCompatibleAttValPairs(AttValPair("job", "chef"));
    cout << v.size() << endl;
    for(int i = 0; i < v.size(); i++){
        cout << v[i].attribute << "-->" << v[i].value << endl;
    }
     */
    /*
    std::vector<PersonProfile> vc;
    for(int i= 0; i < 10; i++){
        string b = "";
        for(int j = 0; j < i; j++){
            b += 'o';
        }
        PersonProfile p(b, b);
        vc.push_back(p);
    }
    for(int k = 0; k < v.size(); k++){
        cout << vc[k].GetName() << "-->" << vc[k].GetEmail() << endl;
    }
     */
    
    
    /*
     Elian Castaneda
     ElianCastan0@ymail.com
     3
     job,electrician
     hobby,writing
     trait,libidinous
     */
    /*
    MemberDatabase mdb;
    mdb.LoadDatabase(MEMBERS_FILE);
    AttributeTranslator at;
    at.Load(TRANSLATOR_FILE);
    MatchMaker mm(mdb, at);
    std::vector<EmailCount> e = mm.IdentifyRankedMatches("WinsMill655@aim.com", 8);
    for(int i = 0; i < e.size(); i++){
        cout << e[i].email << "  :  " << e[i].count << endl;
    }
    */
    
    
    
    /*
    std::string a = "hello,cheetos,job,cooking";
    istringstream iss(a);
    std::string att1;
    std::string val1;
    std::string att2;
    std::string val2;
    std::string both;
    
    std::getline(iss, att1, ',');
    std::getline(iss, val1, ',');
    std::getline(iss, att2, ',');
    std::getline(iss, val2, ',');
    
    both = att1 + ','+ val1;
    
    cout << att1 << endl;
    cout << val1 << endl;
    cout << att2 << endl;
    cout << val2 << endl;
    cout << both << endl;
    */
    
    /*
    RadixTree<int> test;
    test.insert("a", 1);
    test.insert("b", 2);
    int* the = test.search("a");
    cout << *the << endl;
    
    AttValPair avp;
    avp = AttValPair("hobby", "cooking");
    AttValPair b;
    b = AttValPair("hobby", "being super cool");
    AttValPair c;
    c = AttValPair("job", "coding");
    AttValPair d;
    d = AttValPair("hobby", "cooking");
    
    PersonProfile* bro;
    bro = new PersonProfile("brody", "bjizzle@gmail.com");
    
    bro->AddAttValPair(avp);
    bro->AddAttValPair(b);
    bro->AddAttValPair(c);
    bro->AddAttValPair(d);
    
    cout << bro->GetNumAttValPairs() << endl;
    
    for (int k = 0; k != bro->GetNumAttValPairs(); k++) {
    AttValPair av;
    bro->GetAttVal(k, av);
    std::cout << av.attribute << " -> " << av.value << std::endl;
    }
    
    */
    
    
    
    
    MemberDatabase mdb;
    if (!mdb.LoadDatabase(MEMBERS_FILE))
    {
        std::cout << "Error loading " << MEMBERS_FILE << std::endl;
        return 1;
    }
    AttributeTranslator at;
    if (!at.Load(TRANSLATOR_FILE))
    {
        std::cout << "Error loading " << TRANSLATOR_FILE << std::endl;
        return 1;
    }

    while(findMatches(mdb, at));

    std::cout << "Happy dating!" << std::endl;

     
}

bool findMatches(MemberDatabase& mdb, AttributeTranslator& at)
{
      // Prompt for email
    std::string email;
    //const PersonProfile* pp;
    const PersonProfile* pp;
    for (;;) {
        std::cout << "Enter the member's email for whom you want to find matches: ";
        std::getline(std::cin, email);
        if (email.empty())
            return false;
        pp = mdb.GetMemberByEmail(email);
        if (pp != nullptr)
            break;
        std::cout << "That email is not in the member database." << std::endl;
    }

      // Show member's attribute-value pairs
    std::cout << "The member has the following attributes:" << std::endl;
    for (int k = 0; k != pp->GetNumAttValPairs(); k++) {
        AttValPair av;
        pp->GetAttVal(k, av);
        std::cout << av.attribute << " --> " << av.value << std::endl;
    }

      // Prompt user for threshold
    int threshold;
    std::cout << "How many shared attributes must matches have? ";
    std::cin >> threshold;
    std::cin.ignore(10000, '\n');

      // Print matches and the number of matching translated attributes
    MatchMaker mm(mdb, at);
    std::vector<EmailCount> emails = mm.IdentifyRankedMatches(email, threshold);
    if (emails.empty())
        std::cout << "No member was a good enough match." << std::endl;
    else {
        std::cout << "The following members were good matches:" << std::endl;;
        for (auto& emailCount : emails) {
            const PersonProfile* pp = mdb.GetMemberByEmail(emailCount.email);
            std::cout << pp->GetName() << " at " << emailCount.email << " with "
                      << emailCount.count << " matches!" << std::endl;
        }
    }
    std::cout << std::endl;
    return true;
}

