#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <array>
#include <cstdint>
#include <stdexcept>
#include <type_traits>


using namespace std;


template<int Bits> struct int_traits;
template<> struct int_traits<8>   { using type = uint8_t; };
template<> struct int_traits<16>  { using type = uint16_t; };
template<> struct int_traits<32>  { using type = uint32_t; };
template<> struct int_traits<64>  { using type = uint64_t; };
#if defined(__SIZEOF_INT128__)
template<> struct int_traits<128> { using type = unsigned __int128; };
#endif

template<int Bits>
constexpr bool is_supported_width = (Bits == 8 || Bits == 16 || Bits == 32 || Bits == 64 || Bits == 128);



template<typename T>
T parse_integer(const std::string& str) {
    if (str.empty()) throw std::invalid_argument("Empty input string");

    size_t pos = 0;
    int base = 10;
    if (str.size() > 2 && str[0] == '0' && (str[1] == 'x' || str[1] == 'X')) {
        base = 16;
        pos = 2;
    }

    T val = 0;
    constexpr T max_val = static_cast<T>(~0);
    
    for (; pos < str.size(); ++pos) {
        char c = str[pos];
        int digit = 0;
        if (c >= '0' && c <= '9')      digit = c - '0';
        else if (c >= 'a' && c <= 'f') digit = c - 'a' + 10;
        else if (c >= 'A' && c <= 'F') digit = c - 'A' + 10;
        else throw std::invalid_argument("Invalid character in integer string");

        if (digit >= base) throw std::invalid_argument("Digit out of range for detected base");
        if (base == 16 && val > (max_val >> 4)) throw std::overflow_error("Hex overflow");
        if (base == 10 && val > (max_val / 10)) throw std::overflow_error("Decimal overflow");

        val = val * base + digit;
    }
    return val;
}


template<typename T>
constexpr std::array<uint8_t, sizeof(T)> to_endian_bytes(T value, bool little_endian) {
    std::array<uint8_t, sizeof(T)> bytes{};
    for (size_t i = 0; i < sizeof(T); ++i) {
        size_t idx = little_endian ? i : (sizeof(T) - 1 - i);
        bytes[idx] = static_cast<uint8_t>(value >> (i * 8));
    }
    return bytes;
}


template<int Bits>
auto to_little_endian(const std::string& s) {
    static_assert(is_supported_width<Bits>, "Unsupported bit width. Use 8, 16, 32, 64, or 128.");
#if !defined(__SIZEOF_INT128__) && (Bits == 128)
    static_assert(sizeof(int) == 0, "128-bit requires compiler with __int128 (GCC/Clang).");
#endif
    using T = typename int_traits<Bits>::type;
    return to_endian_bytes<T>(parse_integer<T>(s), true);
}

template<int Bits>
auto to_big_endian(const std::string& s) {
    static_assert(is_supported_width<Bits>, "Unsupported bit width. Use 8, 16, 32, 64, or 128.");
#if !defined(__SIZEOF_INT128__) && (Bits == 128)
    static_assert(sizeof(int) == 0, "128-bit requires compiler with __int128 (GCC/Clang).");
#endif
    using T = typename int_traits<Bits>::type;
    return to_endian_bytes<T>(parse_integer<T>(s), false);
}

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
      
      
     if (a > 15) {
    	 print ("zzz2222");
     } else {
     	print ("zzz");
     } 
      
      
      int adqwe = 155;
      
      
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
		//else if (val == "if") {type = TOKEN_AUTO; typeString = "if"; line = 0; }
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
		
		
		if (c == '=' && cod2e[i+1] == '=') {
				Tkqns.push_back({"TOkenIFequal ", "=="}); 
				i+=2;
				continue;
		}
		
		if (c == '<' && cod2e[i+1] == '=') {
				Tkqns.push_back({"lsoreq", "<="}); 
				i+=2;
				continue;
		}
		
		if (c == '>' && cod2e[i+1] == '=') {
				Tkqns.push_back({"gtoreq", ">="}); 
				i+=2;
				continue;
		}

			
 			 switch (c) {
 			 case '>': Tkqns.push_back({"TOKEN_GT", ">"}); break;
 			 case '<': Tkqns.push_back({"TOKEN_LS", "<"}); break;
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
