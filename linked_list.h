
#ifndef MY_LINKED_LIST_H
#define MY_LINKED_LIST_H

#include <initializer_list>
#include <utility>

using namespace std;

// #define begin first

template <typename T>
class nodo {
    T x;
    nodo<T>* prev_value = nullptr;
    nodo<T>* next_value = nullptr;
public:
    nodo(const T val) : x(val) {};
    nodo () = default;
    ~nodo () = default;
    T& value () { return this->x; }
    auto next() { return next_value; }
    auto prev() { return prev_value; }
    void update_next_value(nodo<T>* some_node) { next_value = some_node; }
    void update_prev_value(nodo<T>* some_node) { prev_value = some_node; };
};

namespace gabo {

    // Intentar completar un double linked list
    template<typename T>
    class linked_list {
        nodo<T>* prim = nullptr;
        nodo<T>* ult = nullptr;
        int sz{};
            public:

        // Constructores
        template<typename ...params>
        linked_list(params&&... lst) {
            initializer_list<T> temp = {forward<params>(lst)...};
            for(const auto &i : temp){
                push_back(i);
            }
        }

        linked_list() = default;
        ~linked_list() {
            clear();
        }


        // Getters
        auto first () { return prim; }
        auto last () { return ult; }
        int size() { return sz; }

        // Métodos
        void push_back(const T val){
            auto* temp = new nodo<T>(val);
            if(prim == nullptr) {
                prim = temp;
                ult = temp;
            }
            else {
                ult->update_next_value(temp);
                temp->update_prev_value(ult);
                ult = ult->next();
            }
            sz++;
            temp = nullptr;
        }
        void pop_back() {
            if(prim == ult) {
                prim =  nullptr;
                delete ult;
                ult = nullptr;
            }
            else {
                auto *temp = ult->prev();
                delete ult;
                ult = nullptr;
                ult = temp;
                temp = nullptr;
            }
            sz--;
        }
        // Falta caso en que se pop_front() con un elemento en la estructura.
        void pop_front(){
            auto* temp = prim->next();
            delete prim;
            prim = nullptr;
            prim = temp;
            temp = nullptr;
            //delete temp;
            sz--;
        }
        void erase(int pos) {
            if(pos + 1 == sz) {
                pop_back();
            }
            else if (pos == 0) {
                pop_front();
            }
            else {
                auto *it = prim;
                while (pos--) it = it->next();
                auto right = it->next();
                auto left = it->prev();
                left->update_next_value(right);
                right->update_prev_value(left);
                delete it;
                it = left = right = nullptr;
                sz--;
            }
        }
        void insert(int pos, T val){
            auto* temp = new nodo<T>(val);
            if(sz == 0 || pos == sz) {
                push_back(val);
            }
            else {
                auto *right = prim;
                while (pos--) right = right->next();
                auto *left = right->prev();
                temp->update_prev_value(left);
                temp->update_next_value(right);
                right->update_prev_value(temp);
                left->update_next_value(temp);
                sz++;
                right = left = nullptr;
            }
            temp = nullptr;
        }
        void clear() {
            while(sz){
                pop_back();
            }
        }
    };
};



#endif
