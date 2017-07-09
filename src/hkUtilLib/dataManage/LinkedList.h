#pragma once

/////////////
// INCLUDE
#include "IList.h"


namespace hkCore
{
    /////////////////////
    // CLASS: ListNode
    //==========================================================================================
#pragma region ListNode
    //==========================================================================================
    template <typename T>
    class ListNode : public IListNode <T>
    {
    public:
        ListNode<T>()
        {
            next = nullptr;
            prev = nullptr;
        }

        ~ListNode<T>()
        {
            Release();
        }

        ////////////////////////
        // OVERRIDE INTERFACE
        void Release() override
        {
            if (next != nullptr)
                delete next;

            ReleaseThisOnly();
        }

        virtual void ReleaseThisOnly() override
        {
            ReleaseDataOnly();

            next = nullptr;
            prev = nullptr;
        }

        virtual void ReleaseDataOnly() override
        {
            if (m_data)
                delete m_data;

            m_data = nullptr;
        }

        virtual void Set(T* data) override
        {
            // First, we need to release it's previous data
            ReleaseDataOnly();
            m_data = data;
        }

        virtual void Set(Ptr<T>& data) override
        {
            // First, we need to release it's previous data
            ReleaseDataOnly();

            if (data != nullptr)
                m_data = &data.Get();
        }

        virtual T* Get() override
        {
            return m_data;
        }

        virtual bool IsNull() override
        {
            return m_data == nullptr;
        }

        virtual IListNode<T>* Next()
        {
            return next;
        }

        virtual IListNode<T>* Prev()
        {
            return prev;
        }

        virtual void SetNext(IListNode<T>* node)
        {
            next = node;
        }

        virtual void SetPrev(IListNode<T>* node)
        {
            prev = node;
        }

    protected:
        T* m_data;
        IListNode<T>* next;
        IListNode<T>* prev;
    };
    //==========================================================================================
#pragma endregion //ListNode
    //==========================================================================================



    //==========================================================================================
#pragma region // Iterator
    //==========================================================================================
    /////////////////////////////////
    // PRIVATE SUB CLASS: Iterator
    template<typename T>
    class ListItemIterator : public IIterator<T>
    {
    public:
        ListItemIterator()
        {
            m_parent = nullptr;
            m_it = nullptr;
        }

        ListItemIterator(IList<T>& list)
        {
            m_parent = &list;
            m_it = nullptr;
        }

        ListItemIterator(IList<T>& list, IListNode<T>* begin)
        {
            m_parent = &list;
            m_it = begin;
        }

        ListItemIterator(const ListItemIterator<T>& clone)
        {
            m_it = clone.m_it;
            m_parent = clone.m_parent;
        }

        ListItemIterator(IIterator<T>& clone)
        {
            m_it = clone.GetNode();
            m_parent = clone.GetList();
        }

        ~ListItemIterator()
        {
            m_it = nullptr;
            m_parent = nullptr;
        }

        void operator=(const ListItemIterator<T>& clone)
        {
            m_it = clone.m_it;
            m_parent = clone.m_parent;
        }

        ////////////////////////
        // OVERRIDE INTERFACE
        virtual T* Get() override
        {
            if (m_it)
                return m_it->Get();

            return nullptr;
        }

        virtual bool Next() override
        {
            if (m_it && m_it->Next() != nullptr)
            {
                m_it = m_it->Next();
                return true;
            }

            return false;
        }

        virtual bool Prev() override
        {
            if (m_it && m_it->Prev() != nullptr)
            {
                m_it = m_it->Prev();
                return true;
            }

            return false;
        }

        virtual bool IsValid() override
        {
            return m_it != nullptr;
        }

        virtual bool IteratorOf(IList<T>& list) override
        {
            return m_parent == &list;
        }

        virtual void Remove() override
        {
            if (m_it == nullptr)
                return;

            if (m_it->Next())
            {
                IListNode<T>* tmp = m_it->Next();
                m_parent->Remove(this);
                m_it = tmp;
            }
            else
            {
                m_it = m_it->Prev();
                m_parent->PopLast();
            }
        }

        virtual uint GetIndex() override
        {
            uint result = -1;
            IListNode<T>* tmp = m_it;
            while (tmp)
            {
                tmp = tmp->Prev();
                result++;
            }

            return result;
        }

        virtual IListNode<T>* GetNode() override
        {
            return m_it;
        }

        virtual IList<T>* GetList() override
        {
            return m_parent;
        }

    private:
        IList<T>* m_parent;
        IListNode<T>* m_it;
    };
    //==========================================================================================
#pragma endregion // Iterator
    //==========================================================================================



    //==========================================================================================
#pragma region LinkedList
    //==========================================================================================
    ////////////////////////
    // CLASS: LinkedList
    template <typename T>
    class LinkedList : public IList<T>
    {
    public:
        typedef typename ListItemIterator<T> Iterator;

    public:
        LinkedList()
        {
            m_size = 0;
        }

        ~LinkedList()
        {
            Clear();
        }

        ////////////////////////
        // OVERRIDE INTERFACE
        virtual uint Size() override
        {
            return m_size;
        }

        virtual T* Get(uint index) override
        {
            IListNode<T>* node = GetNode(index);
            return node ? node->Get() : nullptr;
        }

        virtual T* GetLast() override
        {
            if (m_last)
                return m_last->Get();

            return nullptr;
        }

        virtual T* GetFirst() override
        {
            if (m_first)
                return m_first->Get();

            return nullptr;
        }

        virtual T* operator[](uint index) override
        {
            return Get(index);
        }

        virtual void Remove(uint index) override
        {
            Remove(GetNode(index));
        }

        virtual void Remove(T& item) override
        {
            Remove(GetNode(item));
        }

        virtual void Remove(T* item) override
        {
            if (item == nullptr)
                return;

            Remove(GetNode(*item));
        }

        virtual void Remove(Ptr<T>& item) override
        {
            if (item != nullptr)
                Remove(GetNode(item.Get()));
        }

        virtual void Clear() override
        {
            if (m_first)
                delete m_first;

            m_first = nullptr;
            m_last = nullptr;
            m_size = 0;
        }

        virtual void Pop() override
        {
            if (m_size == 0)
                return;

            if (m_size == 1)
            {
                delete m_first;
                m_first = nullptr;
                m_last = nullptr;
                m_size = 0;
            }
            else
            {
                IListNode<T>* tmp = m_first;
                m_first = m_first->Next();
                if (m_first)
                    m_first->SetPrev(nullptr);

                tmp->ReleaseThisOnly();
                delete tmp;

                m_size--;
            }
        }

        virtual void PopLast()
        {
            if (m_size <= 1)
                Pop();
            else
            {
                IListNode<T>* tmp = m_last;
                m_last = m_last->Prev();
                if (m_last)
                    m_last->SetNext(nullptr);

                tmp->ReleaseThisOnly();
                delete tmp;

                m_size--;
            }
        }

        virtual uint IndexOf(T& item) override
        {
            IListNode<T>* tmp = m_first;

            uint index = 0;
            while (tmp != nullptr)
            {
                if (!tmp->IsNull() && tmp->Get() == &item)
                    return index;

                tmp = tmp->Next();
                index++;
            }

            return -1;
        }

        virtual uint IndexOf(T* item) override
        {
            if (item == nullptr)
                return -1;

            return IndexOf(*item);
        }

        virtual uint IndexOf(Ptr<T>& item) override
        {
            if (item == nullptr)
                return -1;

            return IndexOf(item.Get());
        }

        virtual bool Exists(T* item) override
        {
            return IndexOf(item) >= 0;
        }

        virtual bool Exists(T& item) override
        {
            return IndexOf(item) >= 0;
        }

        virtual bool Exists(Ptr<T>& item) override
        {
            return IndexOf(item) >= 0;
        }

        Ptr<IIterator<T>> GetIterator(uint index) override
        {
            return new Iterator(*this, GetNode(index));
        }

        Ptr<IIterator<T>> GetIterator() override
        {
            return new Iterator(*this, m_first);
        }

        virtual void Add(T *item) override
        {
            AddNodeToLast()->Set(item);
        }

        virtual void Add(Ptr<T>& item) override
        {
            AddNodeToLast()->Set(item);
        }

        virtual void Push(T* item) override
        {
            AddNodeToFirst()->Set(item);
        }

        virtual void Push(Ptr<T>& ptr) override
        {
            Push(&ptr.Get());
        }

        virtual Ptr<IList<T>> Append(IList<T>& other) override
        {
            Ptr<IList<T>> result(new LinkedList());

            Ptr<IIterator<T>> thisIterator = GetIterator();
            if (thisIterator->IsValid())
            {
                do
                {
                    result->Add(thisIterator->Get());
                } while (thisIterator->Next());
            }

            Ptr<IIterator<T>> otherIterator = other.GetIterator();
            if (otherIterator->IsValid())
            {
                do
                {
                    result->Add(otherIterator->Get());
                } while (otherIterator->Next());
            }

            return result;
        }

        virtual Ptr<IList<T>> operator+(IList<T>& other) override
        {
            return Append(other);
        }

        virtual void Remove(IIterator<T>* it) override
        {
            if (it->IteratorOf(*this))
                Remove(it->GetNode());
        }

    protected:
        virtual void Remove(IListNode<T>* node)
        {
            if (node != nullptr)
            {
                if (m_first == node)
                    m_first = node->Next();

                if (m_last == node)
                    m_last = node->Prev();

                // Reset linked list relationship
                if (node->Next() != nullptr)
                    node->Next()->SetPrev(node->Prev());

                if (node->Prev() != nullptr)
                    node->Prev()->SetNext(node->Next());

                // Release it's data
                node->ReleaseThisOnly();
                delete node;

                m_size--;
            }
        }

        virtual uint IndexOf(IListNode<T>* node)
        {
            uint result = -1;
            while (node)
            {
                result++;
                node = node->Prev();
            }

            return result;
        }

        IListNode<T>* GetNode(uint index)
        {
            IListNode<T>* tmp = m_first;
            while (tmp && !tmp->IsNull() && index-- > 0)
            {
                tmp = tmp->Next();
            }

            return tmp;
        }

        IListNode<T>* GetNode(T& item)
        {
            IListNode<T>* tmp = m_first;
            while (tmp != nullptr)
            {
                if (!tmp->IsNull() && tmp->Get() == &item)
                    return tmp;

                tmp = tmp->Next();
            }

            return nullptr;
        }

        ListNode<T>* AddNodeToLast()
        {
            ListNode<T>* newNode = new ListNode<T>();

            if (m_last != nullptr)
            {
                m_last->SetNext(newNode);
                newNode->SetPrev(m_last);
                m_last = newNode;
            }
            else
            {
                m_first = newNode;
                m_last = m_first;
            }

            m_size++;

            return newNode;
        }

        ListNode<T>* AddNodeToFirst()
        {
            ListNode<T>* newNode = new ListNode<T>();

            if (!m_first)
            {
                m_first = newNode;
                m_last = m_first;
            }
            else
            {
                m_first->SetPrev(newNode);
                newNode->SetNext(newNode);
                m_first = newNode;
            }

            m_size++;

            return newNode;
        }

    protected:
        IListNode<T>* m_first;
        IListNode<T>* m_last;

    protected:
        uint m_size = 0;
    };
    //==========================================================================================
#pragma endregion // LinkedList
    //==========================================================================================
}


////////////////////////////////////////////////////////////////////////////////////////////
// DEFINE
#define LinkedList hkCore::LinkedList        // Linked list