#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <stack>
bool f(std::string str){
    if (str == "if" || str == "while" || str == "or" || str == "and" || str == "neq"  || str == "eq" || str == "<" || str == ">" || str == "print"){
        return true;
    }
    return false;
}
bool f(char c){
    if (c == '(' || c == ')' || c == '=' 
        || c == '*' || c == '/' || c == '+' || c == '-' || 
          c == '&' || c == '|' || c == '>' || c == '<' || c  == '%'){
            return true;
    }
    return false;
}
enum class token_t{
    num,
    neg, // for 1 unar -
    varb, // variable
    par, // ()
    logic, // for and , or
    cond, // for > < and eq
    key_w, // key words like 'if', 'print','while'
    oper1, // + -
    oper2, // * /
    eq // only for =

};
struct token{
    token_t t;
    std::string str;
};

class node{
    public:
    node* right = nullptr;
    node* left = nullptr;
    std::string oper = ""; // operation
    token il; // just in case if has numbers means size_t left
    token ir; // means size_t right
    ~node(){
        delete right;
        delete left;
    }
};








//handling math expression




node* mathh(std::vector<token> a,std::vector<node*> &b, size_t c){
     size_t counter_pars = 0;
     size_t in_par = 0; // contains index of first par
     node* ret = nullptr;
     if( a.size() == 1){
        node* r = new node;
        token o;
        o.t = token_t::num;
        o.str = "0";
        r->oper = "+";
        r->ir = a[0];
        r->il = o;
        b[c] = r;
        return r;
     }
     for( size_t i  = 0; i < a.size(); ++i){
       if( a[i].t == token_t::par){
            if( a[i].str == "("){
                if(counter_pars == 0){
                    counter_pars++;
                    in_par = i;
                }else{
                    counter_pars++;
                }

            }else{
                counter_pars--;
                if(counter_pars == 0){
                    std::vector<token> d;
                    for(size_t y =  in_par+1; y < i; ++y){
                        d.push_back(a[y]);
                    }
                    node* f = mathh(d,b, in_par+c);
                    ret = f;
                    for(size_t y =  in_par+c; y <= in_par+d.size()+c+1; ++y){
                        b[y] =f;
                    }
                }
            }
       }
     }
     for( size_t y = 0; y< a.size(); ++y){
         if(b[y+c] != nullptr){
            continue;
        }
        if(a[y].t == token_t::neg){
            node* n = new node;
            if(b[y+c+1] != nullptr){
                n->right = b[y+c+1];
                node* tret = b[y+c+1];
                for(size_t uh = 0; uh < b.size(); ++uh){
                    
                    if(b[uh] == tret){
                        b[uh] = n;
                    }
                }
            }else{
                n->ir = a[y+1];
                b[y+1+c] = n;
            }
            token opo;
            opo.t = token_t::num;
            opo.str = "0";
            n->il = opo;
            b[y+c] = n;
            n->oper = a[y].str;
            ret =n;
            size_t isos = 0;
        }   
    }
    for( size_t y = 0; y< a.size(); ++y){
         if(b[y+c] != nullptr){
            continue;
        }
        if(a[y].t == token_t::oper2){
            node* n = new node;
            if(b[y+c-1] != nullptr){
                n->left = b[y+c-1];
                node* tret = b[y+c-1];
                for(size_t uh = 0; uh < b.size(); ++uh){
                    if(b[uh] == tret){
                        b[uh] = n;
                    }
                }
            }else{
                n->il = a[y-1];
                b[y+c-1] = n;
            }
            if(b[y+c+1] != nullptr){
                n->right = b[y+c+1];
                node* tret = b[y+c+1];
                for(size_t uh = 0; uh < b.size(); ++uh){
                    
                    if(b[uh] == tret){
                        b[uh] = n;
                    }
                }
            }else{
                n->ir = a[y+1];
                b[y+1+c] = n;

            }
            b[y+c] = n;
            n->oper = a[y].str;
            ret =n;
            size_t isos = 0;
        }   
    }
    for( size_t y = 0; y< a.size(); ++y){
        if(b[y+c] != nullptr){
            continue;
        }
        if(a[y].t == token_t::oper1){
            node* n = new node;
            if(b[y+c-1] != nullptr){
                n->left = b[y+c-1];
                node* tret = b[y+c-1];
                for(size_t uh = 0; uh < b.size(); ++uh){
                    if(b[uh] == tret){
                        b[uh] = n;
                    }
                }
            }else{
                n->il = a[y-1];
                b[y+c-1] = n;
            }
            if(b[y+c+1] != nullptr){
                n->right = b[y+c+1];
                node* tret = b[y+c+1];
                for(size_t uh = 0; uh < b.size(); ++uh){
                    if(b[uh] == tret){
                        b[uh] = n;
                    }
                }
            }else{
                n->ir = a[y+1];
                b[y+1+c] = n;
            }
            n->oper = a[y].str;
            ret =n;
            b[y+c] = n;
            size_t isos_bib = 0;
        }
    }
    
            
            
        
    
    return ret;
}








// handling tree





std::string handling_tree(node* a){
    std::string ret = "";
    if(a == nullptr){
        return ret;
    }

    if( a->left == nullptr && a->right == nullptr){
        if( a->il.t == token_t::varb){
            ret+= "\tmov rax, ["+a->il.str+"0] \n";
        }else{
            ret+= "\tmov rax, "+a->il.str+" \n";
        }
        if( a->ir.t == token_t::varb){
            ret+= "\tmov rdx, ["+a->ir.str+"0] \n";
        }else{
            ret+= "\tmov rdx, "+a->ir.str+" \n";
        }
        if( a->oper == "*"){
            ret+="\timul rdx\n\tpush rax\n\n\n";
        }else if( a->oper == "+"){
            ret+="\tadd rax, rdx\n\tpush rax\n\n\n";
        }else if( a->oper == "-"){
            ret+="\tsub rax, rdx\n\tpush rax\n\n\n";
            
        }else if( a->oper == "/"){
            ret+="\tmov rbx, rdx\n\txor rdx, rdx\n\tidiv rbx\n\tpush rax\n\n\n";
        }else{
            ret+="\tmov rbx, rdx\n\txor rdx, rdx\n\tidiv rbx\n\tpush rdx\n\n\n";
        }

        
    }else if( a->right != nullptr && a->left == nullptr){
        ret+= handling_tree(a->right);
        ret+= "\tpop rdx\n";
        if( a->il.t == token_t::varb){
            ret+= "\tmov rax, ["+a->il.str+"0] \n";
        }else{
            ret+= "\tmov rax, "+a->il.str+" \n";
        }
        if( a->oper == "*"){
            ret+="\timul rdx\n\tpush rax\n\n\n";
        }else if( a->oper == "+"){
            ret+="\tadd rax, rdx\n\tpush rax\n\n\n";
        }else if( a->oper == "-"){
            ret+="\tsub rax, rdx\n\tpush rax\n\n\n";
            
        }else if( a->oper == "/"){
            ret+="\tmov rbx, rdx\n\txor rdx, rdx\n\tidiv rbx\n\tpush rax\n\n\n";
        }else{
            ret+="\tmov rbx, rdx\n\txor rdx, rdx\n\tidiv rbx\n\tpush rdx\n\n\n";
        }
    }else if( a->right == nullptr && a->left != nullptr){
        ret+= handling_tree(a->left);
        ret+= "\tpop rax\n";
        if( a->ir.t == token_t::varb){
            ret+= "\tmov rdx, ["+a->ir.str+"0] \n";
        }else{
            ret+= "\tmov rdx, "+a->ir.str+" \n";
        }
        if( a->oper == "*"){
            ret+="\timul rdx\n\tpush rax\n\n\n";
        }else if( a->oper == "+"){
            ret+="\tadd rax, rdx\n\tpush rax\n\n\n";
        }else if( a->oper == "-"){
            ret+="\tsub rax, rdx\n\tpush rax\n\n\n";
            
        }else if( a->oper == "/"){
            ret+="\tmov rbx, rdx\n\txor rdx, rdx\n\tidiv rbx\n\tpush rax\n\n\n";
        }else{
            ret+="\tmov rbx, rdx\n\txor rdx, rdx\n\tidiv rbx\n\tpush rdx\n\n\n";
        }
    }else{
        ret+= handling_tree(a->right);
        ret+= handling_tree(a->left);
        ret+= "\tpop rax\n";
        ret+= "\tpop rdx\n";
        if( a->oper == "*"){
            ret+="\timul rdx\n\tpush rax\n\n\n";
        }else if( a->oper == "+"){
            ret+="\tadd rax, rdx\n\tpush rax\n\n\n";
        }else if( a->oper == "-"){
            ret+="\tsub rax, rdx\n\tpush rax\n\n\n";
            
        }else if( a->oper == "/"){
            ret+="\tmov rbx, rdx\n\txor rdx, rdx\n\tidiv rbx\n\tpush rax\n\n\n";
        }else{
            ret+="\tmov rbx, rdx\n\txor rdx, rdx\n\tidiv rbx\n\tpush rdx\n\n\n";
        }
    }
    return ret;
}









std::vector<token> token_tree;









int main(){
//starting programm

    std::ifstream file("f.dk"); // my code file
    std::ofstream output_file("output.asm");
    std::string str = ""; // just to help to break code into tokens 
    std::vector<std::vector<std::string>> tree; // whole code
    std::vector<std::string> branch; // line in blocks(tokens without token type still)
    std::set<std::string> myset; // set of all variables
    output_file<<"global _start\nextern _print\nsection .data\n";
    char s;
    std::string code="";
    size_t loop = 0; // for making unique name in loops

//breaking into blocks

    while(file.get(s)){
        if( s != '\n'){
            if (s == 32){
                if( !str.empty())                
                    branch.push_back(str);
                str = "";
            }else{
                if ( f(s)){
                    if( !str.empty())                
                        branch.push_back(str);
                    str = "";
                    str+= s;
                    branch.push_back(str);
                    str = "";
                    continue;
                }
                if (s == ';' || s == '{' || s == '}'){
                    if(!str.empty())
                        branch.push_back(str);
                    tree.push_back(branch);
                    branch.clear();
                    str = "";
                }else{
                    str+=s;

                }
            }
        }
    }



//tokenezation








    for(size_t i = 0; i < tree.size(); ++i){
        for(size_t j = 0; j < tree[i].size() ; ++j){
            if( tree[i][j] == "and" || tree[i][j] == "or"){
                token o;
                o.t = token_t::logic;
                o.str = tree[i][j];
                token_tree.push_back(o);
                continue;

            }
            if( tree[i][j] == ">" || tree[i][j] == "<" || tree[i][j] == "eq"){
                token o;
                o.t = token_t::logic;
                o.str = tree[i][j];
                token_tree.push_back(o);
                continue;

            }
            if(f(tree[i][j])){
                token o;
                o.t = token_t::key_w;
                o.str = tree[i][j];
                token_tree.push_back(o);
                continue;
            }
            if (f(tree[i][j][0])){
                if(tree[i][j][0] == '='){
                    token o;
                    o.t = token_t::eq;
                    o.str = tree[i][j];
                    token_tree.push_back(o);
                    continue;
                }
                if(tree[i][j][0] == '+' || tree[i][j][0] == '-'){
                    if (tree[i][j][0] == '-'){
                        if ( token_tree[j-1].t == token_t::eq || token_tree[j-1].t == token_t::oper1 || token_tree[j-1].t == token_t::oper2 ||  token_tree[j-1].str ==  "("){
                            token o;
                            o.t = token_t::neg;
                            o.str = tree[i][j];
                            token_tree.push_back(o);
                            continue;
                        }
                    }
                    token o;
                    o.t = token_t::oper1;
                    o.str = tree[i][j];
                    token_tree.push_back(o);
                    continue;
                }
                if(tree[i][j][0] == '*' || tree[i][j][0] == '/' || tree[i][j][0] == '%'){
                    token o;
                    o.t = token_t::oper2;
                    o.str = tree[i][j];
                    token_tree.push_back(o);
                    continue;
                }
                if(tree[i][j][0] == '(' || tree[i][j][0] == ')'){
                    token o;
                    o.t = token_t::par;
                    o.str = tree[i][j];
                    token_tree.push_back(o);
                    continue;
                }
            }
            if( tree[i][j][0] >= '0' && tree[i][j][0] <= '9'){
                token o;
                o.t = token_t::num;
                o.str = tree[i][j];
                token_tree.push_back(o);
                continue;
                    
            }
            token o;
            o.t = token_t::varb;
            o.str = tree[i][j];
            token_tree.push_back(o);
            myset.insert(tree[i][j]);
        }









//making code
    std::vector<node*> blocks_numbers;// vector to assign for each token their number
    blocks_numbers.resize(token_tree.size()); // obviously it should have the size of token_tree
    // for assign
            
        // only for 3 sized token_tree
        if( token_tree[0].t == token_t::varb){
            if( token_tree.size() == 3){
                if( token_tree[2].t == token_t::varb || token_tree[2].t == token_t::num ){
                    if( token_tree[2].t == token_t::varb){
                        if (myset.find(token_tree[2].str) != myset.end() ){
                            code+="\tpush rax\n\tmov rax, ["+token_tree[2].str+'0'+"]\n\tmov ["+token_tree[0].str+'0'+"], rax\n\tpop rax\n\n";
                        }else{
                            std::cout<<"Unknown var "<<token_tree[2].str<<"\n";
                        }
                    }else{
                        code+="\tpush rax\n\tmov rax, "+token_tree[2].str+"\n\tmov ["+token_tree[0].str+'0'+"], rax\n\tpop rax\n\n";
                    }
                }else{
                    std::cout<<"trying to assign something else than var or num\n";
                    return 1;
                }
            }else if (token_tree.size() > 3){
                code += "\tpush rax\n\tpush rbx\n\tpush rdx\n\n";
                node* node_link = mathh(token_tree,blocks_numbers,0);
                code+= handling_tree(node_link);
                code+= "\tpop rax\n\tmov ["+token_tree[0].str+"0], rax\n\n" ;
                blocks_numbers.clear();
                code += "\tpop rdx\n\tpop rbx\n\tpop rax\n\n";
                delete node_link;
            } 
        }
        if(token_tree[0].t == token_t::key_w ){
            std::stack<std::string> st; // for nested loops
            if(token_tree[0].str == "print"){
                if( token_tree[1].t == token_t::varb){
                    code+="\n\n\tpush r15\n\tmov r15, ["+token_tree[1].str+"0]\n\tcall _print\n\tpop r15\n";
                }else{
                    code+="\n\n\tpush r15\n\tmov r15, "+token_tree[1].str+"\n\tcall _print\n\tpop r15\n";
                }
            }
            if (token_tree[0].str == "while"){
                
            }
        }
    








    //tokenezation output

        for(size_t y = 0 ;  y < token_tree.size(); ++y){
            std::string type_tok_cout = "";
            if( token_tree[y].t == token_t::varb)
                type_tok_cout = "varb";
            if( token_tree[y].t == token_t::par)
                type_tok_cout = "par";
            if( token_tree[y].t == token_t::oper1)
                type_tok_cout = "oper1";
            if( token_tree[y].t == token_t::oper2)
                type_tok_cout = "oper2";
            if( token_tree[y].t == token_t::num)
                type_tok_cout = "num";
            if( token_tree[y].t == token_t::key_w)
                type_tok_cout = "key_w";
            if( token_tree[y].t == token_t::eq)
                type_tok_cout = "eq";
            if( token_tree[y].t == token_t::neg)
                type_tok_cout = "neg";
            if( token_tree[y].t == token_t::logic)
                type_tok_cout = "logic";
            if( token_tree[y].t == token_t::cond)
                type_tok_cout = "cond";
            std::cout<<type_tok_cout<<'\t';
        }
        std::cout<<'\n';
        for(size_t y = 0 ;  y < token_tree.size(); ++y){
            std::cout<< token_tree[y].str<<"\t";
        }
        std::cout<<'\n';
        token_tree.clear();
    }


//writeing in file





    for(std::string i : myset){
        output_file<<'\t'<<i<<'0'<<" dq 0\n";
    }

    output_file<<"section .text\n_start:\n"<<code<<"\nexit:\nmov rax, 60\nsyscall";






//output in terminal

    // for(size_t i = 0; i < tree.size(); ++i){
    //     for(size_t j = 0; j < tree[i].size() ; ++j){
    //         std::cout<<tree[i][j]<<" ";
    //     }
    //     std::cout<<'\n';
    // }
    file.close();
    output_file.close();
}
