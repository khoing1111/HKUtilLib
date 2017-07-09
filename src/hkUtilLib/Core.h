#pragma once

/////////////
// INCLUDE
#include "String.h"


////////////
// DEFINE
#define uint unsigned int
#define ulong unsigned long
#define uchar unsigned char


//////////////////
// CORE METHODE
namespace hkCore
{
    //////////////////////
    // PREDEFINED CLASS
    class String;

    /// <summary>
    /// IPtrContainer store a source of Pointer (Ptr) data
    /// <para>It's also have with it some additional information:</para>
    /// <para>- Number of reference to this container (Increase everytime a pointer bind to it and
    /// decrease when pointer unbind out of container)</para>
    /// <para>- Number of Strong-reference (A strong reference is a reference form a strong pointer,
    /// when Strong-reference number reach zero, Container data get release/delete)</para>
    /// <para>- Size of data (Which is used in case of an array)</para>
    /// </summary>
    class IPtrContainer
    {
    public:
        IPtrContainer();
        IPtrContainer(IPtrContainer&);
        IPtrContainer(uint size);
        virtual ~IPtrContainer();

        /// <summary>
        /// Add an reference to Container list
        /// <para>A reference will be add to the end of reference list</para>
        /// <para>Each reference represent a different expression of data (Usually obtain by cast data pointer from
        /// one type to another</para>
        /// </summary>
        /// <param name="variant">The variant.</param>
        virtual void Reference(IPtrContainer* variant);

        /// <summary>
        /// Unlinks A reference. To understand reference please read <seealso cref="IPtrContainer.Reference"/>
        /// </summary>
        /// <returns></returns>
        virtual bool Unlink();

        /// <summary>
        /// Sizes of data (In case of array pointer)
        /// </summary>
        /// <returns></returns>
        virtual uint Size();

        /// <summary>
        /// Lock this container. A locked container will not delete/release it's data when it's strong reference counter
        /// decrease to zero
        /// </summary>
        /// <returns></returns>
        virtual void Lock();

        /// <summary>
        /// UnLock this container. (Opposite of Lock, please read <seealso cref="IPtrContainer.Lock"/>)
        /// </summary>
        /// <returns></returns>
        virtual void UnLock();

        virtual void Bind(bool isStrong = true) = 0;
        virtual bool UnBind(bool isStrong = true) = 0;
        virtual bool IsNull() = 0;
        virtual bool Exist(uint index) = 0;

    protected:
        uint m_numRef;
        uint m_numStrongRef;
        uint m_size;
        bool m_isLock;

        IPtrContainer* m_nextVariant;
        IPtrContainer* m_prevVariant;
    };

    /// <summary>
    /// PtrContainer store a source of Pointer (Ptr) data with type T
    /// <para>It's also have with it some additional information:</para>
    /// <para>- Number of reference to this container (Increase everytime a pointer bind to it and
    /// decrease when pointer unbind out of container)</para>
    /// <para>- Number of Strong-reference (A strong reference is a reference form a strong pointer,
    /// when Strong-reference number reach zero, Container data get release/delete)</para>
    /// <para>- Size of data (Which is used in case of an array)</para>
    /// </summary>
    template <typename T>
    class PtrContainer : public IPtrContainer
    {
    public:
        PtrContainer()
        {
            m_src = nullptr;
        }

        PtrContainer(PtrContainer<T>& clone)
        {
            Reference(&clone);
        }

        PtrContainer(T* input)
        {
            m_src = input;
        }

        PtrContainer(T* input, uint size) : IPtrContainer(size)
        {
            m_src = input;
        }

        PtrContainer(uint size) : IPtrContainer(size)
        {
            if (size > 0)
                m_src = new T[size]();
            else
                m_src = nullptr;
        }

        ~PtrContainer()
        {
            if (!Unlink() && m_src)
            {
                if (m_size == 0)
                    delete m_src;
                else
                    delete[] m_src;

                m_src = nullptr;
            }
        }

        /// <summary>
        /// Bind a pointer to this container. When user access pointer, it will return this
        /// container's data.
        /// <para>
        /// input isTrong = true if this is a strong reference. Meaning, if the pointer get release 
        /// and it is the last strong reference to this container. This container will delete/release 
        /// it's data
        /// </para>
        /// <param name="isStrong">is strong binding</param>
        /// </summary>
        /// <returns></returns>
        virtual void Bind(bool isStrong) override
        {
            m_numRef++;
            if (isStrong) m_numStrongRef++;
        }

        /// <summary>
        /// Unbind a pointer out of container. Decrease it's reference count and if isStrong = true,
        /// strong reference counter will also get decrease.
        /// <para>
        /// This method return true if the reference count reach zero (Which mean this pointer is
        /// the last pointer bind to this container). And in turn telling the pointer to 
        /// delete/release this container.
        /// </para>
        /// <param name="isStrong">is strong binding</param>
        /// </summary>
        /// <returns></returns>
        virtual bool UnBind(bool isStrong = true) override
        {
            if (isStrong && m_numStrongRef > 0)
            {
                m_numStrongRef--;
                if (m_numStrongRef == 0 && m_src)
                {
                    if (!Unlink() && !m_isLock)
                    {
                        if (m_size == 0)
                            delete m_src;
                        else
                            delete[] m_src;
                    }

                    m_src = nullptr;
                }
            }

            if (m_numRef > 0)
                m_numRef--;

            return m_numRef == 0;
        }

        /// <summary>
        /// Return true if the data is null
        /// </summary>
        /// <returns></returns>
        virtual bool IsNull() override
        {
            return m_src == nullptr;
        }

        /// <summary>
        /// In case this container contain an array. Use Exist method to check if index
        /// is in the range of the array or if array element at index is null
        /// </summary>
        /// <param name="index">Array's member index</param>
        /// <returns></returns>
        virtual bool Exist(uint index) override
        {
            return Get(index) != nullptr;
        }

        /// <summary>
        /// Return data
        /// </summary>
        /// <returns></returns>
        T* Get()
        {
            return m_src;
        }

        /// <summary>
        /// Return data at index position (For array only)
        /// </summary>
        /// <param name="index">Array's member index</param>
        /// <returns></returns>
        T* Get(uint index)
        {
            if (m_size != 0 && index < m_size)
                return m_src + index;
            else
                return nullptr;
        }

    protected:
        T* m_src;
    };


    /////////////////----------------------------------------------------------------------
    // CLASS: IPtr
    template <typename T>
    class IPtr
    {
    public:
        IPtr()
        {
            m_ptrContainer = nullptr;
        }

        IPtr(T* input)
        {
            m_ptrContainer = new PtrContainer<T>(input);
            Bind();
        }

        IPtr(T* input, IPtrContainer* ref)
        {
            // Create new data container
            m_ptrContainer = new PtrContainer<T>(input);
            Bind();

            // Bind it with input reference
            if (ref)
                ref->Reference(m_ptrContainer);
        }

        virtual ~IPtr()
        {
        }

        virtual void Release()
        {
            // Release it's data content
            if (UnBind())
                delete m_ptrContainer;

            m_ptrContainer = nullptr;
        }

        virtual bool operator==(const T* other)
        {
            T* src = nullptr;

            if (m_ptrContainer)
                src = m_ptrContainer->Get();

            if (src == nullptr && other == nullptr)
                return true;

            if (src == nullptr || other == nullptr)
                return false;

            return src == other;
        }

        virtual bool operator==(const T* other) const
        {
            T* src = nullptr;

            if (m_ptrContainer)
                src = m_ptrContainer->Get();

            if (src && other == nullptr)
                return true;

            if (src == nullptr || other == nullptr)
                return false;

            return src == other;
        }

        virtual bool operator!=(const T* other)
        {
            return !operator==(other);
        }

        virtual bool operator!=(const T* other) const
        {
            return !operator==(other);
        }

        virtual bool operator==(const IPtr<T>& other)
        {
            return m_ptrContainer == other.m_ptrContainer;
        }

        virtual bool operator==(const IPtr<T>& other) const
        {
            return m_ptrContainer == other.m_ptrContainer;
        }

        virtual bool operator!=(const IPtr<T>& other)
        {
            return m_ptrContainer != other.m_ptrContainer;
        }

        virtual bool operator!=(const IPtr<T>& other) const
        {
            return m_ptrContainer != other.m_ptrContainer;
        }

        virtual void operator=(const IPtr<T>& other)
        {
            Release();

            if (other.m_ptrContainer)
            {
                // Reference to exists pointer data
                m_ptrContainer = other.m_ptrContainer;

                // Bind it with pointer data
                Bind();
            }
        }

    protected:
        inline virtual void Bind() = 0;
        inline virtual bool UnBind() = 0;

    protected:
        PtrContainer<T>* m_ptrContainer;
    };


    ////////////////----------------------------------------------------------------------
    // CLASS: Ptr
    template <typename T>
    class Ptr : public IPtr<T>
    {
    public:
        Ptr()
        {
            m_ptrContainer = nullptr;
        }

        Ptr(const Ptr<T>& clone)
        {
            // Reference to exists pointer data
            m_ptrContainer = clone.m_ptrContainer;

            // Bind it with pointer data
            Bind();
        }

        Ptr(T* input)
        {
            m_ptrContainer = new PtrContainer<T>(input);
            Bind();
        }

        Ptr(T* input, IPtrContainer* ref)
        {
            // Create new data container
            m_ptrContainer = new PtrContainer<T>(input);
            Bind();

            // Bind it with input reference
            if (ref)
                ref->Reference(m_ptrContainer);
        }

        virtual ~Ptr()
        {
            Release();
        }

        void Set(T* input)
        {
            // Release old data container
            Release();

            // Create and bind new data container
            m_ptrContainer = new PtrContainer<T>(input);
            Bind();
        }

        virtual void operator=(T* src)
        {
            Set(src);
        }

        T& Get()
        {
            return *(m_ptrContainer->Get());
        }

        T& Get() const
        {
            return *(m_ptrContainer->Get());
        }

        T* operator->()
        {
            return m_ptrContainer->Get();
        }

        T* operator->() const
        {
            return m_ptrContainer->Get();
        }

        template <typename U>
        Ptr<U> As()
        {
            if (m_ptrContainer == nullptr || m_ptrContainer->IsNull())
                return nullptr;

            U* tmp = dynamic_cast<U*>(&Get());
            if (tmp == nullptr)
                return nullptr;

            return Ptr<U>(tmp, m_ptrContainer);
        }

        template <typename U>
        Ptr<U> As() const
        {
            if (m_ptrContainer == nullptr || m_ptrContainer->IsNull())
                return nullptr;

            U* tmp = dynamic_cast<U*>(&Get());
            if (tmp == nullptr)
                return nullptr;

            return Ptr<U>(tmp, m_ptrContainer);
        }

    protected:
        inline virtual void Bind() override
        {
            if (m_ptrContainer)
                m_ptrContainer->Bind(true);
        }

        inline virtual bool UnBind() override
        {
            if (m_ptrContainer)
                return m_ptrContainer->UnBind(true);

            return false;
        }
    };


    ////////////////////----------------------------------------------------------------------
    // CLASS: WeakPtr
    template <typename T>
    class WeakPtr : public Ptr<T>
    {
    public:
        WeakPtr()
        {
            m_ptrContainer = nullptr;
        }

        WeakPtr(const WeakPtr<T>& clone)
        {
            // Reference to exists pointer data
            m_ptrContainer = clone.m_ptrContainer;

            // Bind it with pointer data
            Bind();
        }

        WeakPtr(const Ptr<T>& clone) : Ptr<T>(clone)
        {
            // Recall bind method using child method
            Ptr::UnBind();
            Bind();
        }

        WeakPtr(T* input)
        {
            m_ptrContainer = new PtrContainer<T>(input);
            Bind();

            // Because we initialize this weak-pointer with an pointer,
            // we need to lock it's data to make sure that in the future
            // if an strong-pointer happen to bind to it's data container.
            // That strong-pointer will not delete it's data
            m_ptrContainer->Lock();
        }

        virtual ~WeakPtr()
        {
            Release();
        }

    protected:
        inline virtual void Bind() override
        {
            if (m_ptrContainer)
                m_ptrContainer->Bind(false);
        }

        inline virtual bool UnBind() override
        {
            if (m_ptrContainer)
                return m_ptrContainer->UnBind(false);

            return false;
        }
    };


    /////////////////////----------------------------------------------------------------------
    // CLASS: ArrPtr
    template<typename T>
    class ArrPtr : public IPtr<T>
    {
    public:
        ArrPtr()
        {
            m_ptrContainer = nullptr;
        }

        ArrPtr(const ArrPtr<T>& clone)
        {
            // Reference to exists pointer data
            m_ptrContainer = clone.m_ptrContainer;

            // Bind it with pointer data
            Bind();
        }

        ArrPtr(uint size)
        {
            m_ptrContainer = new PtrContainer<T>(size);
            Bind();
        }

        ArrPtr(T* input, uint size)
        {
            m_ptrContainer = new PtrContainer<T>(input, size);
            Bind();
        }

        ArrPtr(T* input, uint size, IPtrContainer* ref)
        {
            m_ptrContainer = new PtrContainer<T>(input, size);
            Bind();

            if (ref != nullptr)
                ref->Reference(m_ptrContainer);
        }

        virtual ~ArrPtr()
        {
            Release();
        }

        void Set(T* input, uint size)
        {
            Release();

            m_ptrContainer = new PtrContainer<T>(input, size);
            Bind();
        }

        T& Get(uint index)
        {
            return m_ptrContainer->Get()[index];
        }

        T& Get(uint index) const
        {
            return m_ptrContainer->Get()[index];
        }

        T& operator[](uint index)
        {
            return Get(index);
        }

        T& operator[](uint index) const
        {
            return Get(index);
        }

        uint Size()
        {
            return m_ptrContainer == nullptr ? 0 : m_ptrContainer->Size();
        }

        bool Exist(uint index)
        {
            return m_ptrContainer == nullptr ? false :
                (m_ptrContainer->Exist(index) && (m_ptrContainer->Get() + index) != nullptr);
        }

    protected:
        inline virtual void Bind() override
        {
            if (m_ptrContainer)
                m_ptrContainer->Bind(true);
        }

        inline virtual bool UnBind() override
        {
            if (m_ptrContainer)
                return m_ptrContainer->UnBind(true);

            return false;
        }
    };


    ///////////////////////----------------------------------------------------------------------
    // CLASS: WeakArrPtr
    template<typename T>
    class WeakArrPtr : public IPtr<T>
    {
    public:
        WeakArrPtr()
        {
            m_ptrContainer = nullptr;
        }

        WeakArrPtr(const WeakArrPtr<T>& clone)
        {
            // Reference to exists pointer data
            m_ptrContainer = clone.m_ptrContainer;

            // Bind it with pointer data
            Bind();
        }

        WeakArrPtr(const ArrPtr<T>& clone) : ArrPtr(clone)
        {
            // Recall bind method using child method
            ArrPtr::UnBind();
            Bind();
        }

        WeakArrPtr(T* input, uint size)
        {
            m_ptrContainer = new PtrContainer<T>(input, size);
            Bind();

            // Because we initialize this weak-pointer with an pointer,
            // we need to lock it's data to make sure that in the future
            // if an strong-pointer happen to bind to it's data container.
            // That strong-pointer will not delete it's data
            m_ptrContainer->Lock();
        }

        virtual ~WeakArrPtr()
        {
            Release();
        }

    protected:
        inline virtual void Bind() override
        {
            if (m_ptrContainer)
                m_ptrContainer->Bind(false);
        }

        inline virtual bool UnBind() override
        {
            if (m_ptrContainer)
                return m_ptrContainer->UnBind(false);

            return false;
        }
    };


    ////////////////////-----------------------------------------------------------------------
    // Method use to create new matrix pointer and delete matrix pointer
    // Please take note that below functions will not guarantee total safefy for pointer.
    // Use with care.
    template<typename T>
    T** new_pp(uint x, uint y)
    {
        T** result;

        result = new T*[x];
        for (uint i = 0; i < x; i++)
            result[i] = new T[y];

        return result;
    }

    template<typename T>
    void delete_pp(T** pp, uint x)
    {
        if (pp)
        {
            for (uint i = 0; i < x; i++)
            {
                if (pp[i])
                    delete[] pp[i];
            }

            delete[] pp;
        }
    }

    template<typename T>
    T** clone_pp(T** src, uint w, uint h)
    {
        T** result = new_pp<T>(w, h);
        if (result)
        {
            for (uint i = 0; i < w; i++)
                memcpy(result[i], src[i], sizeof(T) * h);
        }

        return result;
    }

    template<typename T>
    bool is_equal_pp(T** src1, T** src2, uint w, uint h)
    {
        for (uint i = 0; i < w; i++)
            if (memcmp(&src1[i], &src2[i], sizeof(T) * h) != 0)
                return false;

        return true;
    }
}


///////////////
// PREDEFINE
#define hk_is_equal_pp hkCore::is_equal_pp
#define hk_delete_pp hkCore::delete_pp
#define hk_clone_pp hkCore::clone_pp
#define hk_new_pp hkCore::new_pp

#define hkObject hkCore::Object

#define SPtr hkCore::Ptr
#define ArrPtr hkCore::ArrPtr

#define ObjPtr hkCore::ObjPtr

#define WPtr hkCore::WeakPtr
#define WArrPtr hkCore::WeakArrPtr
