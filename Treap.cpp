#include <iostream>

class Node {
public:
    int clave;
    int prioridad;
    Node* izq;
    Node* der;

    Node(int c, int p):clave(c), prioridad(p), izq(nullptr), der(nullptr) {

    }
};

class Treap {
private:
    Node* root;

    Node* insert(Node* nodo, int c, int p);

    Node* erase(Node* nodo, int c);

    bool search(Node* nodo, int c);

    Node* rotarIzquierda(Node* nodo);

    Node* rotarDerecha(Node* nodo);

    void inorder(Node* root) ;

    void preorder(Node* root);

    void postorder(Node* root) ;
   
    Node* merge(Node* izq, Node* der);

    void split(Node* t, int clave, Node*& izq, Node*& der);

public:
    Treap();

    void insertar(int c) {
        int p = rand();
        root = insert(root, c, p);
    }

    void eliminar(int c) {
        root = erase(root, c);
    }

    bool buscar(int c) {
        return search(root, c);
    }

    void inorder() {
        inorder(root);
    }

    void preorder() {
        preorder(root);
    }

    void postorder() {
        postorder(root);
    }

    void dividir(int clave, Node*& izq, Node*& der) {
    split(root, clave, izq, der);}

    Node* unirTreaps(Node* a, Node* b) {return merge(a, b);}

    ~Treap() {
    }
};

Node* Treap::insert(Node* nodo,int c,int p){
    if (nodo == nullptr) {
        return new Node(c, p);
    }
    if (c < nodo->clave) {
        nodo->izq = insert(nodo->izq, c, p);
        if (nodo->izq->prioridad > nodo->prioridad) {
            nodo = rotarDerecha(nodo);
        }
    }
    else if (c > nodo->clave) {
        nodo->der = insert(nodo->der, c, p);
        if (nodo->der->prioridad > nodo->prioridad) {
            nodo = rotarIzquierda(nodo);
        }
    }
    return nodo;
}

Node* Treap::erase(Node* nodo, int c){
        if (nodo == nullptr) {
            return nullptr;
        }

        if (c < nodo->clave) {
            nodo->izq = erase(nodo->izq, c);
        }
        else if (c > nodo->clave) {
            nodo->der = erase(nodo->der, c);
        }
        else {
            if (nodo->izq == nullptr) {
                Node* temp = nodo->der;
                delete nodo;
                return temp;
            }
            else if (nodo->der == nullptr) {
                Node* temp = nodo->izq;
                delete nodo;
                return temp;
            }
            else {
                if (nodo->izq->prioridad > nodo->der->prioridad) {
                    nodo = rotarDerecha(nodo);
                    nodo->der = erase(nodo->der, c);
                } else {
                    nodo = rotarIzquierda(nodo);
                    nodo->izq = erase(nodo->izq, c);
                }
            }
        }
        return nodo;
    }


bool Treap::search(Node* nodo, int c){
        if (nodo == nullptr) {
            return false;
        }
        if (c < nodo->clave) {
            return search(nodo->izq, c);
        }
        else if (c > nodo->clave) {
            return search(nodo->der, c);
        }
        else {
            return true;
        }
    }

Node* Treap::rotarIzquierda(Node* nodo)
    {
        Node* temp = nodo->der;
        Node* temp2 = temp->izq;
        temp->izq = nodo;
        nodo->der = temp2;
        return temp;
    }

Node* Treap::rotarDerecha(Node* nodo)
    {
        Node* temp = nodo->izq;
        Node* temp2 = temp->der;
        temp->der = nodo;
        nodo->izq = temp2;
        return temp;
    }


void Treap::inorder(Node* root)
    {
        if (root == nullptr) {
            return;
        }
        inorder(root->izq);
        std::cout << root->clave<< ", " << std::endl;
        inorder(root->der);
    }

    void Treap::preorder(Node* root)
     {
        if (root == nullptr) {
            return;
        }
        std::cout << root->clave<< ", " << std::endl;
        preorder(root->izq);
        preorder(root->der);
    }

void Treap::postorder(Node* root)
    {
        if (root == nullptr) {
            return;
        }
        postorder(root->izq);
        postorder(root->der);
        std::cout << root->clave<< ", " << std::endl;
    }

Node* Treap::merge(Node* izq, Node* der) {
    if (!izq || !der)
        return izq ? izq : der;

    if (izq->prioridad > der->prioridad) {
        izq->der = merge(izq->der, der);
        return izq;
    } else {
        der->izq = merge(izq, der->izq);
        return der;
    }
}


void Treap::split(Node* t, int clave, Node*& izq, Node*& der) {
    if (!t) {
        izq = der = nullptr;
    } else if (clave < t->clave) {
        split(t->izq, clave, izq, t->izq);
        der = t;
    } else {
        split(t->der, clave, t->der, der);
        izq = t;
    }
}