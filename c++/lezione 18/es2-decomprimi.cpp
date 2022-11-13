/*
Decomprimi la stringa

Data una stringa, la si è compressa secondo le seguenti regole:

ogni carattere va inserito nella stringa 
compressa seguito dal numero di volte consecutive che si ripete
il numero non può essere superiore a 9. Se un carattere si ripete 
più di 9 volte, si spezza la sequenza in più sequenze di lunghezza 
massima. Per esempio, una sequenza di 23 caratteri 'a' sarà rappresentata 
come a9a9a5 in quanto 9+9+5 = 23
Si desidera creare un programma per la decompressione delle stringhe. 
La stringa decompressa deve essere memorizzata in un oggetto string
della lunghezza corretta.

Esempio:

Data la stringa compressa:

a1b7c2d9d3

si deve restituire la stringa:

abbbbbbbccdddddddddddd

La stringa vuota viene decompressa nella stringa vuota.
*/

#include <iostream>
#include <string>

std::string decomprimi(const std::string& s) {

    std::string res;
    
    int i = 0;
    while(i<s.length()){
    	
    	char c = s[i++];
    	size_t n = s[i++] - '0';
    	
    	res.append(n,c);
    	
	}
    
    return res;

}

int main() {
    std::string buff;
    std::string res;
    
    std::cin>>buff;
    
    res = decomprimi(buff);
    
    std::cout<<res;
    
    return 0;
}
