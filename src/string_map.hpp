template<typename T>
string_map<T>::Nodo::Nodo(){
    for(int i=0;i<256;i++){
        siguientes.push_back(nullptr);
    }
    definicion= nullptr;
}


template <typename T>
string_map<T>::string_map(){
    _raiz=nullptr;
    _size= 0;
}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() { *this = aCopiar; } // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.




template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
    for(int i=this->_claves.size();i>0;i--){
        if(this->count(this->_claves[i])==1){
            this->erase(this->_claves[i]);
        }
    }
    for(int i=0;i<d._claves.size();i++){
        if(d.count(d._claves[i])==1) {
            this->insert(make_pair(d._claves[i],d.at(d._claves[i])));
        }
    }
    return *this;
}

template <typename T>
string_map<T>::~string_map(){
    for(int i=0;i<_claves.size();i++){
        if(count(_claves[i])==1) {
            this->erase(_claves[i]);
        }
    }
    delete _raiz;
}

void string_map<T>::insert(const pair<string, T>& elem){
    if(_raiz==nullptr){
        _raiz= new Nodo();
    }
    Nodo* nodoActual= _raiz;
    int i= 0;
    while(i<get<0>(elem).length()){
        if(nodoActual->siguientes[get<0>(elem)[i]]!= nullptr){
            nodoActual=nodoActual->siguientes[int(get<0>(elem)[i])];
            i++;
        } else{
            nodoActual->siguientes[int(get<0>(elem)[i])]= new Nodo;
            nodoActual=nodoActual->siguientes[int(get<0>(elem)[i])];
            i++;
        }
    }
     if(nodoActual -> definicion!= nullptr){
         delete nodoActual->definicion;
         nodoActual-> definicion= nullptr;
         _size--;
     }
    nodoActual->definicion= new T(get<1>(elem));
    _size++;
    _claves.push_back(get<0>(elem));
}

template <typename T>
T& string_map<T>::operator[](const string& clave){
    // COMPLETAR
}


template <typename T>
int string_map<T>::count(const string& clave) const{
    int res= 0;
    bool PuedeEstar=true;
    if(_raiz==nullptr){
        PuedeEstar=false;
    }
    Nodo* nodoActual= _raiz;
    int i= 0;
    while(i<clave.length() && PuedeEstar){
        if(nodoActual->siguientes[int(clave[i])]!=nullptr){
            nodoActual=nodoActual->siguientes[int(clave[i])];
            i++;
        } else{
            PuedeEstar=false;
        }
    }
    if(PuedeEstar && nodoActual->definicion!=nullptr){
        res=1;
    }
    return res;
}

template <typename T>
const T& string_map<T>::at(const string& clave) const {
    Nodo* nodoActual=_raiz;
    for(int i=0;i<clave.length();i++){
        nodoActual=nodoActual->siguientes[int(clave[i])];
    }
    return *(nodoActual->definicion);

}

template <typename T>
T& string_map<T>::at(const string& clave) {
    Nodo* nodoActual=_raiz;
    for(int i=0;i<clave.length();i++){
        nodoActual=nodoActual->siguientes[int(clave[i])];
    }
    return *(nodoActual->definicion);
}

template<typename T>
int string_map<T>::cantHijos(const Nodo* n){
    int res=0;
    for(int i=0;i<n->siguientes.size();i++){
        if(n->siguientes[i]!=nullptr){
            res++;
        }
    }
    return res;
}

template<typename T>
void string_map<T>::borrarHijos(Nodo *n,string s) {
    Nodo* nodoActual=n->siguientes[int(s[0])];
    n->siguientes[int(s[0])]=nullptr;
    for(int i=0;i<s.length();i++){
        if(i==s.length()-1){
            delete nodoActual->definicion;
            delete nodoActual;
        } else {
            Nodo *temp = nodoActual->siguientes[int(s[i + 1])];
            delete nodoActual;
            nodoActual = temp;
        }
    }
}

template <typename T>
void string_map<T>::erase(const string& clave) {
    Nodo* nodoActual = _raiz;
    Nodo* ultimoNodo = _raiz;
    string letrasABorrar;
    string vacio;
    int i = 0;
    while (i < clave.length()) {
        if (this->cantHijos(nodoActual) > 1 || (nodoActual->definicion!=nullptr && i!=clave.length()-1)) {
            ultimoNodo = nodoActual;
            letrasABorrar=vacio;
        }
        letrasABorrar.push_back(clave[i]);
        nodoActual = nodoActual->siguientes[int(clave[i])];
        i++;
    }
    //caso el ultimo nodo es el del significado
    if (cantHijos(nodoActual) > 0) {
        delete nodoActual->definicion;
        nodoActual->definicion = nullptr;
    } else { //otro caso
        borrarHijos(ultimoNodo,letrasABorrar);
    }
    _size--;
}

template <typename T>
int string_map<T>::size() const{
    return _size;
}

template <typename T>
bool string_map<T>::empty() const{
    return this->size()==0;
}
