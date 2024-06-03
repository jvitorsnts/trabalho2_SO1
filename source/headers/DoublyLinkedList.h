//! Copyright [2023] <João Vitor dos Santos>
#include <cstdint>
#include <stdexcept>

namespace structures {

template<typename T>
class DoublyLinkedList {
 public:
    DoublyLinkedList();  // construtor
    ~DoublyLinkedList();  // destrutor
    void clear();   // limpa lista

    void push_back(const T& data);  // insere no fim
    void push_front(const T& data);  // insere no início
    void insert(const T& data, std::size_t index);  // insere na posição
    void insert_sorted(const T& data);  // insere em ordem

    T pop(std::size_t index);  // retira da posição
    T pop_back();  // retira do fim
    T pop_front();  // retira do início
    void remove(const T& data);  // retira específico

    bool empty() const;  // lista vazia
    bool contains(const T& data) const;  // contém

    T& at(std::size_t index);  // acesso a um elemento (checando limites)
    const T& at(std::size_t index) const;  // getter constante a um elemento

    std::size_t find(const T& data) const;  // posição de um dado
    std::size_t size() const;  // tamanho

 private:
    class Node {  // implementar cada um dos métodos de Node
     public:
        // construtor: data
        explicit Node(const T& data):
            data_{data}
        {}
        // construtor: data e next
        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}
        // construtor: data, next e prev
        Node(const T& data, Node* prev, Node* next):
            data_{data},
            next_{next},
            prev_{prev}
        {}

        // getter: data
        T& data() {
            return data_;
        }
        // getter const: data
        const T& data() const {
            return data_;
        }

        // getter: prev
        Node* prev() {
            return prev_;
        }
        // getter const: prev
        const Node* prev() const {
            return prev_;
        }
        // setter: prev
        void prev(Node* node) {
            prev_ = node;
        }

        // getter: next
        Node* next() {
            return next_;
        }
        // getter const: next
        const Node* next() const {
            return next_;
        }
        // setter: next
        void next(Node* node) {
            next_ = node;
        }

     private:
        T data_;  // dado
        Node* prev_;  // anterior
        Node* next_;  // proximo
    };

    Node* head;  // primeiro da lista
    Node* tail;  // ultimo da lista
    std::size_t size_;
};

}  // namespace structures

// construtor
template<typename T>
structures::DoublyLinkedList<T>::DoublyLinkedList() {
    head = nullptr;
    tail = nullptr;
    size_ = 0u;
}

// destrutor
template<typename T>
structures::DoublyLinkedList<T>::~DoublyLinkedList() {
    clear();
}

// limpa lista
template<typename T>
void structures::DoublyLinkedList<T>::clear() {
    Node * atual, * anterior;
    atual = head;
    while (atual != nullptr) {
        anterior = atual;
        atual = atual->next();
        delete anterior;
    }
    head = nullptr;
    tail = nullptr;
    size_ = 0u;
}

// insere no fim
template<typename T>
void structures::DoublyLinkedList<T>::push_back(const T& data) {
    insert(data, size());
}

// insere no inicio
template<typename T>
void structures::DoublyLinkedList<T>::push_front(const T& data) {
    Node * novo;
    novo = new Node(data);
    if (novo == nullptr) {
        throw std::out_of_range("Lista cheia");
    } else {
        novo->next(head);
        novo->prev(nullptr);
        head = novo;
        if (novo->next() != nullptr) {
            (novo->next())->prev(novo);
        } else {
            tail = novo;
        }
        size_++;
    }
}

// insere na posição
template<typename T>
void structures::DoublyLinkedList<T>::insert(const T& data, std::size_t index) {
    Node * anterior, * novo;
    if (index < 0u || index > size()) {
        throw std::out_of_range("Fora escopo");
    } else {
        if (index == 0u) {
            push_front(data);
        } else {
            novo = new Node(data);
            if (novo == nullptr) {
                throw std::out_of_range("Lista cheia");
            } else {
                anterior = head;
                for (std::size_t i = 1u; i < index; i++) {
                    anterior = anterior->next();
                }
                novo->next(anterior->next());
                if (novo->next() != nullptr) {
                    (novo->next())->prev(novo);
                } else {
                    tail = novo;
                }
                novo->next(anterior->next());
                anterior->next(novo);
                novo->prev(anterior);
                size_++;
            }
        }
    }
}

// insere em ordem
template<typename T>
void structures::DoublyLinkedList<T>::insert_sorted(const T& data) {
    Node* atual;
    std::size_t index;
    atual = head;
    index = 0u;
    while (atual != nullptr && atual->data() < data) {
        atual = atual->next();
        index++;
    }
    insert(data, index);
}

// retira da posição
template<typename T>
T structures::DoublyLinkedList<T>::pop(std::size_t index) {
    Node * anterior, * eliminar;
    T volta;
    if (index < 0u || index >= size()) {
        throw std::out_of_range("Fora escopo");
    } else {
        if (index == 0u) {
            return (pop_front());
        } else {
            anterior = head;
            for (std::size_t i = 1u; i < index; i++) {
                anterior = anterior->next();
            }
            eliminar = anterior->next();
            volta = eliminar->data();
            anterior->next(eliminar->next());
            if (eliminar->next() != nullptr) {
                (eliminar->next())->prev(anterior);
            } else {
                tail = anterior;
            }
        }
    }
    size_--;
    delete eliminar;
    return volta;
}

// retira do fim
template<typename T>
T structures::DoublyLinkedList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("Lista vazia");
    }
    return (pop(size()-1u));
}

// retira do inicio
template<typename T>
T structures::DoublyLinkedList<T>::pop_front() {
    Node * saiu;
    T volta;
    if (empty()) {
        throw std::out_of_range("Lista vazia");
    } else {
        saiu = head;
        volta = saiu->data();
        head = saiu->next();
        if (head != nullptr) {
            head->prev(nullptr);
        } else {
            tail = nullptr;
        }
    }
    size_--;
    delete saiu;
    return volta;
}

// retira elemento
template<typename T>
void structures::DoublyLinkedList<T>::remove(const T& data) {
    if (empty()) {
        throw std::out_of_range("Lista vazia");
    } else {
        if (contains(data)) {
            pop(find(data));
        }
    }
}

// lista vazia
template<typename T>
bool structures::DoublyLinkedList<T>::empty() const {
    return (size() == 0u);
}

// contem elemento
template<typename T>
bool structures::DoublyLinkedList<T>::contains(const T& data) const {
    Node* atual;
    atual = head;
    for (std::size_t i = 0; i < size(); i++) {
        if (atual->data() == data) {
            return true;
        }
        atual = atual->next();
    }
    return false;
}

// acesso elemento(checa limites)
template<typename T>
T& structures::DoublyLinkedList<T>::at(std::size_t index) {
    Node* atual;
    if (empty()) {
        throw std::out_of_range("Lista Vazia");
    } else if (index < 0u || index >= size()) {
        throw std::out_of_range("Fora escopo");
    } else {
        atual = head;
        for (std::size_t i = 1u; i <= index; i++) {
            atual = atual->next();
        }
        return atual->data();
    }
}

// getter const elemento
template<typename T>
const T& structures::DoublyLinkedList<T>::at(std::size_t index) const {
    Node* atual;
    if (empty()) {
        throw std::out_of_range("Lista vazia");
    } else {
        atual = head;
        for (std::size_t i = 1u; i <= index; i++) {
            atual = atual->next();
        }
        return atual->data();
    }
}

// posicao elemento
template<typename T>
std::size_t structures::DoublyLinkedList<T>::find(const T& data) const {
    Node* atual;
    atual = head;
    for (std::size_t i = 0u; i < size(); i++) {
        if (atual->data() == data) {
            return i;
        }
        atual = atual->next();
    }
    return size();
}

// tamanho
template<typename T>
std::size_t structures::DoublyLinkedList<T>::size() const {
    return size_;
}
