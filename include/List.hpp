/*
 * List.hpp
 *
 *  Created on: 2017/06/26
 *      Author: osamu
 */

#ifndef INCLUDE_LIST_HPP_
#define INCLUDE_LIST_HPP_

#include <cstddef>
#include <cassert>
#include "FixedSizeAllocator.hpp"

struct ListNodeBase
{
    ListNodeBase* prev;
    ListNodeBase* next;

    ListNodeBase()
        : prev(this), next(this)
    {
    }

    void attachAfter(ListNodeBase* target)
    {
        prev = target;
        next = target->next;

        target->next->prev = this;
        target->next = this; // last things to do.
    }

    void detach()
    {
        prev->next = next;
        next->prev = prev;
    }
};

template<class T>
struct ListNode : public ListNodeBase
{
    T data;

    ListNode(const T& data);
};

template<class T>
ListNode<T>::ListNode(const T& data)
        : ListNodeBase(), data(data)
{
}

template<class T> class ListConstIterator;

template<class T>
class ListIterator
{
private:
    ListNodeBase* node;
    friend ListConstIterator<T>;
public:
    explicit ListIterator(ListNodeBase* node);
    ~ListIterator();

    bool operator==(const ListIterator<T>& rhs) const;
    bool operator!=(const ListIterator<T>& rhs) const;
    T& operator*() const;
    ListIterator<T> operator++();
    ListIterator<T> operator++(int);
};

template<class T>
ListIterator<T>::ListIterator(ListNodeBase* node)
    : node(node)
{
}

template<class T>
ListIterator<T>::~ListIterator()
{
}

template<class T>
bool ListIterator<T>::operator==(const ListIterator<T>& rhs) const
{
    return node == rhs.node;
}

template<class T>
bool ListIterator<T>::operator!=(const ListIterator<T>& rhs) const
{
    return !(*this == rhs);
}

template<class T>
T& ListIterator<T>::operator*() const
{
    return static_cast<ListNode<T>*>(node)->data;
}


template<class T>
ListIterator<T> ListIterator<T>::operator++()
{
    node = node->next;
    return *this;
}

template<class T>
ListIterator<T> ListIterator<T>::operator++(int)
{
    ListIterator<T> result = *this;
    node = node->next;
    return result;
}

template<class T>
class ListConstIterator
{
private:
    const ListNodeBase* node;

public:
    explicit ListConstIterator(const ListNodeBase* node);
    ListConstIterator(const ListIterator<T>& it);
    ~ListConstIterator();

    bool operator==(const ListConstIterator<T>& rhs) const;
    bool operator!=(const ListConstIterator<T>& rhs) const;
    const T& operator*() const;
    ListConstIterator<T> operator++();
    ListConstIterator<T> operator++(int);
};

template<class T>
ListConstIterator<T>::ListConstIterator(const ListNodeBase* node)
    : node(node)
{
}

template<class T>
ListConstIterator<T>::ListConstIterator(const ListIterator<T>& it)
    : node(it.node)
{
}

template<class T>
ListConstIterator<T>::~ListConstIterator()
{
}

template<class T>
bool ListConstIterator<T>::operator==(const ListConstIterator<T>& rhs) const
{
    return node == rhs.node;
}

template<class T>
bool ListConstIterator<T>::operator!=(const ListConstIterator<T>& rhs) const
{
    return !(*this == rhs);
}

template<class T>
const T& ListConstIterator<T>::operator*() const
{
    return static_cast<const ListNode<T> *>(node)->data;
}


template<class T>
ListConstIterator<T> ListConstIterator<T>::operator++()
{
    node = node->next;
    return *this;
}

template<class T>
ListConstIterator<T> ListConstIterator<T>::operator++(int)
{
    ListConstIterator<T> result = *this;
    node = node->next;
    return result;
}

template<class T, class Allocator_type = FixedSizeAllocator<ListNode<T> > >
class List
{
private:
    typedef ListNode<T> ListNode_t;

    Allocator_type allocator;

    std::size_t size_;
    ListNodeBase root;

    void addAfter(ListNodeBase* target, const T& data);
    void remove(ListNodeBase* removingNode);
    void deleteNode(ListNodeBase* deletingNode);

public:
    typedef ListNode<T> ListNode_type;
    typedef ListIterator<T> iterator;
    typedef ListConstIterator<T> const_iterator;

    explicit List(Allocator_type allocator = Allocator_type());
    ~List();

    size_t size();

    T& front();
    T& back();

    void push_front(const T& data);
    void pop_front();
    void push_back(const T& data);
    void pop_back();
    void clear();

    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

    Allocator_type getAllocator();
};

template<class T, class Allocator_type>
List<T, Allocator_type>::List(Allocator_type allocator)
    : allocator(allocator), size_(0)
{
}

template<class T, class Allocator_type>
List<T, Allocator_type>::~List()
{
    clear();
}

template<class T, class Allocator_type>
size_t List<T, Allocator_type>::size()
{
    return size_;
}

template<class T, class Allocator_type>
T& List<T, Allocator_type>::front()
{
    assert(size() != 0);

    return static_cast<ListNode<T>*>(root.next)->data; // if size() == 0, result has no guarantee for exception free.
}

template<class T, class Allocator_type>
T& List<T, Allocator_type>::back()
{
    assert(size() != 0);

    return static_cast<ListNode<T>*>(root.prev)->data; // if size() == 0, result has no guarantee for exception free.
}

template<class T, class Allocator_type>
void List<T, Allocator_type>::push_front(const T& data)
{
    addAfter(&root, data);
}

template<class T, class Allocator_type>
void List<T, Allocator_type>::pop_front()
{
    remove(root.next);
}

template<class T, class Allocator_type>
void List<T, Allocator_type>::push_back(const T& data)
{
    addAfter(root.prev, data);
}

template<class T, class Allocator_type>
void List<T, Allocator_type>::pop_back()
{
    remove(root.prev);
}

template<class T, class Allocator_type>
void List<T, Allocator_type>::clear()
{
    ListNodeBase* removingNode = root.next;
    while (removingNode != &root)
    {
        ListNodeBase* nextRemovingNode = removingNode->next;
        deleteNode(removingNode);
        removingNode = nextRemovingNode;
    }

    root.next = root.prev = &root;
    size_ = 0;
}

template<class T, class Allocator_type>
void List<T, Allocator_type>::addAfter(ListNodeBase* target, const T& data)
{
    ListNode_t* newNode = static_cast<ListNode_t*>(allocator.allocate());
    if (newNode == nullptr)
    {
        return;
    }

    new (newNode) ListNode_t(data);

    newNode->attachAfter(target);

    size_ += 1;
}

template<class T, class Allocator_type>
void List<T, Allocator_type>::remove(ListNodeBase* removingNode)
{
    if (size_ == 0)
    {
        return;
    }

    removingNode->detach();
    deleteNode(removingNode);

    size_ -= 1;
}

template<class T, class Allocator_type>
void List<T, Allocator_type>::deleteNode(ListNodeBase* deletingNode)
{
    static_cast<ListNode_t*>(deletingNode)->~ListNode_t();
    allocator.deallocate(deletingNode);
}

template<class T, class Allocator_type>
typename List<T, Allocator_type>::iterator List<T, Allocator_type>::begin()
{
    return iterator(root.next);
}

template<class T, class Allocator_type>
typename List<T, Allocator_type>::iterator List<T, Allocator_type>::end()
{
    return iterator(&root);
}

template<class T, class Allocator_type>
typename List<T, Allocator_type>::const_iterator List<T, Allocator_type>::begin() const
{
    return const_iterator(root.next);
}

template<class T, class Allocator_type>
typename List<T, Allocator_type>::const_iterator List<T, Allocator_type>::end() const
{
    return const_iterator(&root);
}

template<class T, class Allocator_type>
Allocator_type List<T, Allocator_type>::getAllocator()
{
    return allocator;
}

#endif /* INCLUDE_LIST_HPP_ */
