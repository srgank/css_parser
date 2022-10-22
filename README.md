# CSS Header only parser
## C++

#include "cparsecss.hpp" 
#include <cstring> 
#include <iostream> 

int main()  
{  
    string css =  
        " h1{ "   
        " color: white; "   
        " text-align: center; "  
        " } "  
        " "  
        " p{ "   
        " font-family: verdana; "     
        " font-size: 20px; "     
        " } "  
        " "  
        " b2{ "  
        " font-family: verdana; "  
        " font-size: 20px; "  
        " } "  
        ;  
    
    CParseCSS p;  
    p.parse(css);  
    typeListData data = p.getData();  
      
    for (size_t i = 0; i < data.size(); i++) {  
        cout << data.at(i).selector << " " << data.at(i).name << " " << data.at(i).value << endl;  
    }  
}  


/////////////////  result /////////////////////////////////////////////////////////
                                                                                                
 h1  color           white  
 h1  text-align      center  
 p   font-family     verdana  
 p   font-size       20px  
 b2  font-family     verdana  
 b2  font-size       20px    
 
 If you like to support  you cana make donation 
 https://paypal.me/srdzank64?country.x=AL&locale.x=en_US
                                         
https://paypal.me/srdzank64?country.x=AL&locale.x=en_US                                         
