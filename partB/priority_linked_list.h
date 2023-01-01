#ifndef PRIORITY_LINKED_LIST_H_
#define PRIORITY_LINKED_LIST_H_

#include <iostream>

const int ZERO = 0;
const int POSITIVE = 1;
const int NEGATIVE = -1;

/**
* Generic node class that contain element and next node.
* 
*   Node            - Constructor for node, set element in node.
    Node            - Copy constructor.
    operator=       - Operator= for node.
    ~Node           - Destructor that delete the element.
*/
namespace mtm {
    template<class Element>
    class Node {
    public:
        /**
        * Node: constructor.
        * @param  -  generic element.
        */
        Node(const Element& element);
        
        /*
        * Node: Copy Constructor.
        */
        Node(const Node<Element>& node);
        
        /*
        * operator=: operator= for node
        * @param  -  node
        * @return:
        *   new node
        */
        Node<Element>& operator=(const Node<Element>& node);
        
        /**
        * ~Node: Destructor- delete the element
        */
        ~Node();

        Element* element;   // generic pointer element 
        Node* next;         // next node
    };


    /**
    * Generic Priority List Container
    *
    * Implements a priority list container type.
    * The following functions are available:
    *   PriorityLinkedList	    - Creates a new empty priority list with a function obejct(cor).
    *   PriorityLinkedList      - Copy constructor.
    *   ~PriorityLinkedList		- Destructor- that delete all the nodes in the list.
    *   insert		            - Insert the element according to the function object.
    *   deleteNodeByElement	    - Delete element.
    *   isElementInLinkedList	- Returns whether or not an element exists inside the priority list.
    *   getSize  	            - Returns the size of the list.
    *   getFirst                - Get the first node element in the list -- element head.
    *   getNext		            - Get the next element node(external use).
    *   getFirstNode	        - Get the head.
    *   getLastNode		        - Get the last node.
    */
    template <class Element, class CompareElements>
    class PriorityLinkedList {
    private:
        Node<Element>* head;
        int size, current_node_number;

        /**
        * compareElement: Compare Elements
        * @param: element1, and element2
        * @return
        *   ZERO: if element1 equal to element2
        *   Positive: if element2 is equal or geater than elmenet1
        *   Nexgative: if element1 is grater than element2
        */
        CompareElements compareElements;
    public:
        /**
        * PriorityLinkedList: set the first node to nullptr, and set the object function
        *
        * @param _compareElement - Function object to sort the element
        */
        PriorityLinkedList<Element, CompareElements>(CompareElements _compareElement);
        
        /**
        * PriorityLinkedList: Copy constructor
        * @param list  -  the list that we have to copy
        */
        PriorityLinkedList<Element, CompareElements>(const PriorityLinkedList<Element, CompareElements>& list);
       
        /**
        * ~PriorityLinkedList: Destructor: delete all the nodes in the list
        */
        ~PriorityLinkedList();
       
        /**
        * insert: insert element to list, we have to insert by the function object,
        *         so, the list will be sorted
        * @param t_element  -  element that will be inserted to the list
        */
        void insert(const Element& t_element);
        
        /**
        * deleteNodeByElement: delete element in the list
        * @param  -  element that we will delete
        */
        void deleteNodeByElement(const Element& t_element);
        
        /**
        * isElementInLinkedList: check if the element in the list
        * @param  t_element  -  The element to look for. Will be compared using the omparison function.
        * @return
        * 	  false - if one or more of the inputs is null, or if the key element was not found.
        * 	  true - if the key element was found in the priority list.
        */
        bool isElementInLinkedList(const Element& t_element);
       
        /**
        * getSize: returns the size of the list
        * @return
        *   intger size 
        */
        int getSize() const;

        /**
        * getFirst: return the first node element
        * @return
        *   head element
        */
        const Element& getFirst(const PriorityLinkedList<Element, CompareElements>& list);
        
        /**
        * getNext: return the next node element.
        * @return
        *   next element
        */
        const Element& getNext(const PriorityLinkedList<Element, CompareElements>& list);
        
        /**
        * getFirstNode: get the head.
        * @return 
        *   first node
        */
        Node<Element>* getFirstNode(const PriorityLinkedList<Element, CompareElements>& list);
        
        /*
        * getLastNode: get the last node.
        * @return 
        *   last node
        */
        Node<Element>* getLastNode(const PriorityLinkedList<Element, CompareElements>& list);
       
        /*
        * operator=: operator= for the list
        * @param  -  list
        * @return
        *   new list
        */
        PriorityLinkedList<Element, CompareElements>& operator=(
            const PriorityLinkedList<Element, CompareElements>& list);
    };

    template<class Element>
    inline Node<Element>::Node(const Element& _element) : element(new Element(_element)) { next = nullptr; }

    template<class Element>
    inline Node<Element>::Node(const Node<Element>& node)
    {
        element = new Element(*(node.element));
        if (node.next) {
            next = new Node<Element>(*(node.next));
        }
        else {
            next = nullptr;
        }
    }

    template<class Element>
    inline Node<Element>& Node<Element>::operator=(const Node<Element>& node)
    {
        if (this == &node) {
            return *this;
        }
        element = new Element(*(node.element));
        if (node.next != nullptr) {
            delete this->next; 
            next = new Node<Element>(*(node.next));
        }
        else {
            next = nullptr;
        }
        return *this;
    }

    template<class Element>
    inline Node<Element>::~Node()
    {
        delete element;
    }

    template<class Element, class CompareElements>
    inline PriorityLinkedList<Element, CompareElements>::PriorityLinkedList(CompareElements _compareElement) :
        head(nullptr),
        size(0), current_node_number(0), compareElements(_compareElement) {}
  
    template<class Element, class CompareElements>
    inline PriorityLinkedList<Element, CompareElements>::PriorityLinkedList(
                    const PriorityLinkedList<Element, CompareElements>& list)
    {
        head = nullptr;
        compareElements = list.compareElements;
        Node<Element>* current_node = list.head;
        
        while (current_node != nullptr) {
            this->insert(*(current_node->element));
            current_node = current_node->next;
        }
        
        size = list.size;
        current_node_number = list.current_node_number;
    }

    template<class Element, class CompareElements>
    inline PriorityLinkedList<Element, CompareElements>::~PriorityLinkedList()
    {
        Node<Element>* current_node = head;
        while (current_node != nullptr) {
            Node<Element>* to_delete = current_node;
            current_node = current_node->next;
            delete to_delete;
        }
    }

    template<class Element, class CompareElements>
    inline void PriorityLinkedList<Element, CompareElements>::insert(const Element& _element)
    {
        Node<Element>* node_to_add = new Node<Element>(_element);
        if (head == nullptr) {
            head = node_to_add;
        }
        else if (compareElements(*(head->element), _element) < ZERO) {
            node_to_add->next = head;
            head = node_to_add;
        }
        else {
            Node<Element>* current_node = head;
            while (current_node->next != nullptr &&
                compareElements(*(current_node->next->element),_element) >= ZERO) {
                current_node = current_node->next;
            }
            // add the node between the current node and the next of it
            if (current_node->next) {
                Node<Element>* temp = current_node->next;
                current_node->next = node_to_add;
                node_to_add->next = temp;
            }
            else {
                current_node->next = node_to_add;
            }
        }
        size++;
    }

    template<class Element, class CompareElements>
    inline void PriorityLinkedList<Element, CompareElements>::deleteNodeByElement(const Element& _element)
    {
        if (compareElements(*(head->element), _element) == ZERO) {
            Node<Element>* to_delete = head;
            head = to_delete->next;
            delete to_delete;
            size--;
            return;
        }
        Node<Element>* current_node = head;
        Node<Element>* previous_node = current_node;
        while ((current_node != nullptr) && compareElements(*(current_node->element), _element) != ZERO) {
            previous_node = current_node;
            current_node = current_node->next;
        }

        if (current_node != nullptr) {
            Node<Element>* next_current_node_temp = current_node->next;
            previous_node->next = next_current_node_temp;
            delete current_node;
            size--;
            return;
        }
    }

    template<class Element, class CompareElements>
    inline bool PriorityLinkedList<Element, CompareElements>::isElementInLinkedList(const Element& _element)
    {
        for (Node<Element>* ptr = head; ptr != nullptr; ptr = ptr->next) {
            if (compareElements(*(ptr->element), _element) == ZERO) {
                return true;
            }
        }
        return false;
    }

    template<class Element, class CompareElements>
    inline int PriorityLinkedList<Element, CompareElements>::getSize() const
    {
        return size;
    }


    template<class Element, class CompareElements>
    inline const Element& PriorityLinkedList<Element, CompareElements>::getFirst(
                        const PriorityLinkedList<Element, CompareElements>& list)
    {
        current_node_number = 1;
        return *(list.head->element);
    }

    template<class Element, class CompareElements>
    inline const Element& PriorityLinkedList<Element, CompareElements>::getNext(
                    const PriorityLinkedList<Element, CompareElements>& list)
    {
        int counter = 0;
        Node<Element>* current_node;
        for (current_node = head; counter < list.current_node_number;
            counter++, current_node = current_node->next) {
        }
        current_node_number++;
        return *(current_node->element);
    }
    template<class Element, class CompareElements>
    inline Node<Element>* PriorityLinkedList<Element, CompareElements>::getFirstNode(
                const PriorityLinkedList<Element, CompareElements>& list)
    {
        return (list.head);
    }

    template<class Element, class CompareElements>
    inline Node<Element>* PriorityLinkedList<Element, CompareElements>::getLastNode(
                const PriorityLinkedList<Element, CompareElements>& list)
    {
        Node<Element>* last_node = list.head;
        
        for (int i = 0; i < list.getSize() - 1; i++) {
            last_node = last_node->next;
        }
        
        return last_node; 
    }
    template<class Element, class CompareElements>
    inline PriorityLinkedList<Element, CompareElements>& PriorityLinkedList<Element, CompareElements>::operator=(
        const PriorityLinkedList<Element, CompareElements>& list)
    {
        if (this == &list) {
            return *this;
        }

        if (this != nullptr) {
            for (Node<Element>* ptr = head; ptr != nullptr; ptr = ptr->next) {
                Node<Element>* to_delete = ptr;
                delete to_delete;
            }
        }
        Node<Element>* current_node = list.head;
        while (current_node != nullptr) {
            this->insert(current_node->element);
            current_node = current_node->next;
        }

        size = list.size;
        return *this;
    }
}
#endif //PRIORITY_LINKED_LIST_H_
