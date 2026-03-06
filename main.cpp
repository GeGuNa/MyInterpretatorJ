#include <iostream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

bool iequals(const char* a, const char* b) {
    while (*a && *b) {
        if (std::tolower(static_cast<unsigned char>(*a)) != 
            std::tolower(static_cast<unsigned char>(*b)))
            return false;
        ++a; ++b;
    }
    return *a == *b;
}


bool isLetter(char c) {
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           (c == '_');
}



bool isAlpha(char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_'; }

bool isDigit(char c) { return c >= '0' && c <= '9'; }

bool isAlphaNumeric(char c) { return isAlpha(c) || isDigit(c); }


bool my_isspace(char c)
{
    return (c == ' '  ||   // 0x20
            c == '\f' ||   // 0x0C
            c == '\n' ||   // 0x0A
            c == '\r' ||   // 0x0D
            c == '\t' ||   // 0x09
            c == '\v');    // 0x0B
}

bool WhiteSpace(int c)
{
    unsigned char ch = static_cast<unsigned char>(c);

    return (ch == ' ' || (ch >= 0x09 && ch <= 0x0D));
}

/*
isAtEnd() { ...} 
peek() { ...} 

string val;
size_t line;
        while (!isAtEnd() && peek() != '"') {
            if (peek() == '\n') line++;
            val += advance();
        }

    }

*/

int main(int argc, char*argv[]) {

enum Tkns {
    TOKEN_NONE,
    TOKEN_IDENTIFIER, 
    TOKEN_NUMBER,   
    TOKEN_STRING,    
    TOKEN_OPERATORS = 2, 

    TOKEN_AUTO = 1,
    TOKEN_INT,
    TOKEN_FLOAT,
    TOKEN_DOUBLE,
    TOKEN_STRING_TYPE, 
    TOKEN_FN,          
    
 
    TOKEN_PLUS,      
    TOKEN_MINUS,    
    TOKEN_STAR,       
    TOKEN_SLASH,      
    TOKEN_EQUALS,    
    TOKEN_SEMICOLON,  
    TOKEN_LPAREN,    
    TOKEN_RPAREN,    
    TOKEN_LBRACE,     
    TOKEN_RBRACE,    
    TOKEN_COMMA,     
    TOKEN_EOF        
};

struct Token {
    string type;
    string value;
};

std::vector<Token> Tkqns;

string code = "";
std::string cod2e = R"(
	   int ddd = 15;
	   float deqqq =  15.3;
      int a = 10 + 5 * 2;
      int b = (1 + 2) * 3;
      auto c = 100 - 20 / 4;
      float fqq = 15.3*2/5;
      D = a + d;
      str kkkk = "aabbcc";
      str cccc = "bubu";
      int kz = 1111;
      
   //kzqwek
   
   int llllllllll  = 152;   
      
      
      
)";


size_t i = 0, line = 0;


while (i < cod2e.length()) {
	
	char c = cod2e[i];
	
	if (std::isspace(c)) {
		i++; continue;
	}
	
	

	if (isAlpha(c)) {
		string val;
		size_t start = i;
		string typeString;
		Tkns type;
		
		while (i < cod2e.size() && isAlpha(cod2e[i])) {
            val += cod2e[i];
            i++;
      }
    
    
    
    // if (val == "int" || val == "float"||val == "string"||val == "str"||val == "auto") {
     
		if (val == "int") {type = TOKEN_INT; typeString = "int"; line = 0; }
		else if (val == "float") {type = TOKEN_FLOAT; typeString = "float"; line = 0; }
		else if (val == "string" || val == "str") {type = TOKEN_STRING_TYPE; typeString = "str"; line = 0; }
		else if (val == "auto") {type = TOKEN_AUTO; typeString = "auto"; line = 0; }
		else {type = TOKEN_AUTO; typeString = "token identifier"; line = 0; }
		//Tkqns.push_back({typeString, val});
     	Tkqns.push_back({"", val});
     
     
   //  } else {
     
     
     
     
     //	if (c == '+' || c == '-' || c == '*' || c == '/'  || c == ';'  || c == ')'  || c == '(') 
	  //    string czq = string(1, c);
	//	else
		//	string czq = val;
     	
     //		Tkqns.push_back({"Just_Variable ", czq});
     
     //}


 
      
      
      
      
      
      continue;
	}
	
	
	if (isDigit(c)) {
			size_t qwhr = i;
			bool isFloat = false;

			
			while (i < cod2e.size() && isdigit(cod2e[i])) {
               i++;
         }
         
         if (i < cod2e.size() && cod2e[i] == '.') {
               isFloat = true;
               i++;
               while (i < cod2e.size() && isdigit(cod2e[i])) {
                  i++;
               }
         }
         
			string intrqz = cod2e.substr(qwhr, i - qwhr);


         string tyzzzpe = isFloat ? "Float " : " Integer";



			
			Tkqns.push_back({tyzzzpe, intrqz});

			continue;
		}
		
		if (c == '"') {
			//cout << cod2e[i] << " zzz11111111111 = \n ";
			string val;
			i++;
			
		   while (i < cod2e.size() && cod2e[i] != '"') {
                  val += cod2e[i];
                  i++;
                  //cout << cod2e[i+1] << " zzz333333333333333333 = \n ";
         } i++;
			//i+=2;
			
		//	if (cod2e[i] != ';') {
			// 	cout << " it shall end with ; \n";
			//	break;
		//	}
			
			//cout << cod2e[i+1] << " zzz = \n ";
			
			Tkqns.push_back({"String", val});
			continue;
		}

	   //if (c != '\0') {
		//string valqq = string(1, cod2e[i]);
		
		
		if (c == '/' && cod2e[i+1] == '/') {
		
			i+=2;
		
		
				//Tkqns.push_back({"for comments", "/"}); 
					//i++;

			string val;
			while (i < cod2e.size() && cod2e[i] != '\n') {
				val += cod2e[i];
				i++;
}
			
			Tkqns.push_back({"COMMENTS ", val}); 
			continue;
				//i++;
				
			
		
		
		}
		
		
		
		if (c == '/') {
				Tkqns.push_back({"TOKEN_SLASH", "/"}); 
				i++;
				continue;
		}

			
 			 switch (c) {
            case '+': Tkqns.push_back({"TOKEN_PLUS", "+"}); break;
            case '-': Tkqns.push_back({"TOKEN_MINUS", "-"}); break;
            case '*': Tkqns.push_back({"TOKEN_STAR", "*"}); break;
            //case '/': Tkqns.push_back({"TOKEN_SLASH", "/"}); break;
            case '=': Tkqns.push_back({"TOKEN_EQUALS", "="}); break;
            case ';': Tkqns.push_back({"TOKEN_SEMICOLON", ";"}); break;
            case '(': Tkqns.push_back({"TOKEN_LPAREN", "("}); break;
            case ')': Tkqns.push_back({"TOKEN_RPAREN", ")"}); break;
            case '{': Tkqns.push_back({"TOKEN_LBRACE", "{"}); break;
            case '}': Tkqns.push_back({"TOKEN_RBRACE", "}"}); break;
            case ',': Tkqns.push_back({"TOKEN_COMMA", ","}); break;
            default: 
                std::cerr << "Unknown character: " << c << std::endl; 
                break;
        }			
			
			
			
			
			
			
			
			
			
			i++; 

}
		
  Tkqns.push_back({"TOKEN_END", ""});    	
		
		
		
	//}





for (auto dq : Tkqns) {
	cout << dq.type << " " << dq.value << "  \n";
}


cout << "  \n\n\n\n";

std::vector<string> aba;
aba.push_back("zzzz");
aba.push_back("zzzzwwwwwwwww");

for(string a : aba) {
cout << a << "\n";
}


cout << aba.size() << " length of a code \n";



int aq2 = 15;
int beqz = 25;

cout << aq2+beqz << "\n";

cout << "Welcome \n ";
cout << " Js Like programming language, interpretator not a compiled one  \n"; 



string zq = "aba";

if (isAlpha(zq[0])) {
	cout << "yeah it is \n";
} else {
	
	cout << "no it isn't \n";
}





/*

string code = "int x = (1+2)*3;";
string code2 = "int c = 1+2*3;";

cout << "=== LEXER ===" << "\n";



for (size_t i = 0; i < code.length(); i++) {
  cout << i << "\n";
}
*/






/*for (size_t i = 0; i < code2.size(); i++) {
  cout << i << "\n";
}*/






return 0;
}
