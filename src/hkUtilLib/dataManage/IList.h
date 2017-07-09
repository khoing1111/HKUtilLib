#pragma once

/////////////
// INCLUDE
#include "../Core.h"


namespace hkCore
{
    //////////////////////////
    // INTERFACE: IListNode
    template <typename T>
    class IListNode
    {
    public:
        virtual ~IListNode() {}

        virtual void Release() = 0;
        virtual void ReleaseThisOnly() = 0;
        virtual void ReleaseDataOnly() = 0;

        virtual void Set(T*) = 0;
        virtual void Set(Ptr<T>&) = 0;
        virtual T* Get() = 0;
        virtual bool IsNull() = 0;

        virtual IListNode<T>* Next() = 0;
        virtual IListNode<T>* Prev() = 0;

        virtual void SetNext(IListNode<T>*) = 0;
        virtual void SetPrev(IListNode<T>*) = 0;
    };


    //////////////////////
    // PREDECLARE CLASS
    template <typename T>
    class IIterator;


    //////////////////////
    // INTERFACE: IList
    template <typename T>
    class IList
    {
    public:
        virtual ~IList() {}

        //////////////////////
        // INTERFACE METHOD (Need to be override by it's derived class)
        virtual uint Size() = 0;

        virtual T* Get(uint index) = 0;
        virtual T* GetLast() = 0;
        virtual T* GetFirst() = 0;

        virtual T* operator[](uint index) = 0;      // This is basically Get(uint index method)

        virtual void Add(T*) = 0;
        virtual void Add(Ptr<T>&) = 0;

        virtual void Push(T*) = 0;
        virtual void Push(Ptr<T>&) = 0;

        virtual void Remove(T*) = 0;
        virtual void Remove(T&) = 0;
        virtual void Remove(Ptr<T>&) = 0;
        virtual void Remove(uint index) = 0;
        virtual void Clear() = 0;

        virtual void Pop() = 0;
        virtual void PopLast() = 0;

        virtual uint IndexOf(T&) = 0;
        virtual uint IndexOf(T*) = 0;
        virtual uint IndexOf(Ptr<T>&) = 0;

        virtual bool Exists(T*) = 0;
        virtual bool Exists(T&) = 0;
        virtual bool Exists(Ptr<T>&) = 0;

        virtual Ptr<IIterator<T>> GetIterator(uint index) = 0;
        virtual Ptr<IIterator<T>> GetIterator() = 0;

        virtual Ptr<IList<T>> Append(IList<T>& other) = 0;
        virtual Ptr<IList<T>> operator+(IList<T>& other) = 0;

        virtual void Remove(IIterator<T>* it) = 0;
    };


    //////////////////////////
    // INTERFACE: IIterator
    template <typename T>
    class IIterator
    {
    public:
        virtual ~IIterator() {}

        virtual T* Get() = 0;

        virtual bool Next() = 0;
        virtual bool Prev() = 0;

        virtual bool IsValid() = 0;

        virtual bool IteratorOf(IList<T>& list) = 0;

        virtual void Remove() = 0;
        virtual uint GetIndex() = 0;

        virtual IListNode<T>* GetNode() = 0;
        virtual IList<T>* GetList() = 0;
    };
}

////////////////
// PREDEFINED
#define ListIterator hkCore::IIterator