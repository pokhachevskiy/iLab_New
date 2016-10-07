#ifndef STL_CVECTOR_H_INCLUDED
#define STL_CVECTOR_H_INCLUDED
#include <iostream>
#include <stdexcept>
#include <assert.h>
#include <cstdlib>
#define TPL template<typename T>
const int MULTIPLIER = 2;

/*
= -, == +, != +, < +, <= +, >+, >= +, []+. Функцию assign +, insert - , push_back+, pop_back+, clear+, at+.
*/




TPL
class Array
{
    private:
        static const size_t INIT_SIZE = 10e2;
        T* data_;
        size_t pos;
        size_t size_;
        void Vector_resize (const int a);
        void Assert_OK()const;
        void copy(const Array<T>& that);
    public:
        class iterator;
        class reverse_iterator;
        iterator begin()const
        {
            iterator that(data_);
            return that;
        }
        iterator end()const
        {
            iterator that(data_ + pos);
            return that;
        }
        iterator rbegin()const
        {
            iterator that(data_ + pos);
            return that;
        }
        iterator rend()const
        {
            iterator that(data_);
            return that;
        }



        Array<T> (); //
        Array<T> (const Array<T>& that);
        explicit Array<T> (size_t INIT_size); //
        ~Array<T> ();


        void assign( size_t count, const T& value ); // first count values with value
        void insert( const iterator& posit, size_t count, const T& value ); //from posit insert count position with value

        void clear();
        void push_back( const T& value ); //input elem to the end
        void pop_back(); //just pop last element delete it and so
        const T& at( size_t posisiton );
        bool Vector_OK()const;


        const T& operator [] (const size_t ind)const;
        bool is_empty()const;
        T& operator [] (const size_t ind);
        void Vector_Dump()const;
        Array<T>& operator = (const Array<T>& vec);
        bool operator == (const Array<T>& that)const;
        bool operator < (const Array<T>& that)const;
        bool operator > (const Array<T>& that)const;
        bool operator >= (const Array<T>& that)const;
        bool operator <= (const Array<T>& that)const;
        bool operator != (const Array<T>& that)const;
        //friend CVector<T> operator + <> (const CVector<T>& lhs, const CVector<T>& rhs);
        //friend CVector<T> operator * <> (const CVector<T>& vec, int num);
};
TPL
void Array<T>::copy(const Array<T>& that)
{
    delete[] data_;
    pos = that.pos;
    data_ = new T[size_ = that.size_];
    auto th_it = begin();
    for (auto it = that.begin(); it != that.end(); ++it, ++th_it)
    {
        *th_it = *it;
    }
}




TPL
class Array<T>::iterator
{
    private:
        T* vec_pointer;
    public:
        iterator(T* ptr): vec_pointer(ptr)
        {}
        iterator& operator++ ()
        {
            ++vec_pointer;
            return *this;
        }
        T& operator*()
        {
            return *vec_pointer;
        }
        const T* get()const
        {
            return vec_pointer;
        }
        void operator = (const iterator& that)
        {
            *vec_pointer = that.vec_pointer;
        }

        bool operator != (const iterator& rhs)const
        {
            return (vec_pointer != rhs.vec_pointer);
        }
        bool operator == (const iterator& rhs)const
        {
            return !(vec_pointer != rhs.vec_pointer);
        }
        iterator operator + (const size_t& ind)const
        {
            return vec_pointer + ind;
        }
};

TPL
class Array<T>::reverse_iterator
{
    private:
        T* vec_pointer;
    public:
        iterator(T* ptr): vec_pointer(ptr)
        {}
        iterator& operator++ ()
        {
            --vec_pointer;
            return *this;
        }
        T& operator*()
        {
            return *vec_pointer;
        }
        const T* get()const
        {
            return vec_pointer;
        }
        void operator = (const iterator& that)
        {
            *vec_pointer = that.vec_pointer;
        }

        bool operator != (const iterator& rhs)const
        {
            return (vec_pointer != rhs.vec_pointer);
        }
        bool operator == (const iterator& rhs)const
        {
            return !(vec_pointer != rhs.vec_pointer);
        }
        iterator operator + (const size_t& ind)const
        {
            return vec_pointer - ind;
        }
};


TPL
Array<T>& Array<T>::operator = (const Array<T>& vec)
{
    if (&vec != this)
        copy(vec);
    return *this;
}
TPL
void Array<T>::insert( const iterator& posit, size_t count, const T& value )
{
    if (posit.get() >= end().get())
        assign(count, value);
    else
    {
        Array<T> res(size_ + count);
        for (auto it = begin(); it != posit; ++it)
            res.push_back(*it);

        res.assign(count, value);

        for (auto it = posit; it != end(); ++it)
            res.push_back(*it);
        *this = res;
        std::cout<<"*this[ 2 ]"<<(*this)[2] << std::endl;
        std::cout<<"*this [ 1 ]"<<(*this)[1] << std::endl;
        std::cout<<"*this[ 0 ]"<<(*this)[0] << std::endl;
        std::cout<<"*this.pos  "<<(*this).pos << std::endl;

    }
}


TPL
bool Array<T>::operator < (const Array<T>& that)const
{
    if (size_ < that.size_)
        return true;
    if (size_ > that.size_)
        return false;
    bool fl = true;
    auto th_it = that.begin();
    auto it = begin();
    for(; th_it != that.end(); ++it, ++th_it)
        if (*it == *th_it)
        {
            continue;
        }
        else if (*it < *th_it)
        {
            fl = false;
            break;
        }
    return !fl;
}

TPL
void Array<T>::assign( const size_t count, const T& value )
{
    for (size_t i = 0; i < count; i++)
        push_back(value);
}
TPL
bool Array<T>::operator > (const Array<T>& that)const
{
    return (that < *this);
}
TPL
bool Array<T>::operator >= (const Array<T>& that)const
{
    return (that < *this) || (that == *this);
}

TPL
bool Array<T>::operator <= (const Array<T>& that)const
{
    return (that >= *this);
}

TPL
bool Array<T>::operator == (const Array<T>& that)const
{
    bool fl = true;
    auto th_it = that.begin();
    auto it = begin();
    for(; ((th_it != that.end()) && (it != end())); ++it, ++th_it)
        if (*it != *th_it)
        {
            fl = false;
            break;
        }
    return (fl && (that.pos == pos) && (that.size_ == size_));
}
TPL
bool Array<T>::operator != (const Array<T>& that)const
{
    return (!(*this == that));
}


TPL
void Array<T>::push_back( const T& value )
{
 //   std::cout<<"push back try to call first assert! \n";
    Assert_OK();

    if (pos == size_)
        Vector_resize(1);
    data_[pos++] = value;
 //   std::cout<<"push back try to call second assert! \n";
    Assert_OK();
}

TPL
void Array<T>::pop_back()
{
    Assert_OK();
    if (pos == 0)
    {
        std::cout<<"Vector IS UNDERFLOW\n";
        exit(-1);
    }
    data_[--pos] = (T)NULL;

    Vector_resize(0);
    Assert_OK();
}

//Constructors and destructor
TPL
Array<T>::Array(size_t INIT_size): pos(0), size_(INIT_size)
{
    if (INIT_size <= 0)
        throw (const std::out_of_range)("_size <= 0");
    else
        data_ = new T[INIT_size];
}
TPL
Array<T>::Array (const Array<T>& that)
{
    size_ = that.size_;
    pos = that.pos;
    data_ = new T[that.size_];
    auto th_it = begin();
    for (auto it = that.begin(); it != that.end(); ++it, ++th_it)
    {
        *th_it = *it;
       // std::cout << *th_it << std:: endl;
    }
    Assert_OK();
}

TPL
Array<T>::Array(): pos(0), size_(INIT_SIZE)
{
    data_ = new T[INIT_SIZE];
}

TPL
Array<T>::~Array()
{
    delete[] data_;
    pos = 0;
    size_ = 0;
}
//_________________________________________


// a shows the type of resize: 0 for contraction and 1 for elongation
TPL
void Array<T>::Vector_resize (const int a)
{
 //   std::cout << " vector resize call first assert! \n";
    Assert_OK();
    if (!size_)
        size_++;
    int new_size_ = size_;
    if ((a == 0) && (pos < 3*(size_)/8))
        new_size_ /= MULTIPLIER;
    if (a == 1)
        new_size_ *= MULTIPLIER;
    if (a || ((a == 0) && (pos < 3*(size_)/8)))
    {
        T* temp = new T[new_size_];
        for (size_t i = 0; i < pos; i++)
            temp[i] = data_[i];
        delete[] data_;
        data_ = temp;
    }
    size_ = new_size_;
//    std::cout << " vector resize call second assert! \n";
    Assert_OK();
}


TPL
const T& Array<T>::at( size_t position )
{
    return (*this)[position];
}


TPL
void Array<T>::clear()
{
    delete[] data_;
    data_ = nullptr;
    pos = 0;
    size_ = 0;
}


TPL
const T& Array<T>::operator [] (const size_t ind)const
{
    if ((is_empty()) || (ind < 0) || (ind >= pos))
    {
        std::cout<<"Irregular index or Vector is empty\n"<<std::endl;
        exit(-1);
    }
    return data_[ind];
}
TPL
T& Array<T>::operator [] (const size_t ind)
{
    if ((is_empty()) || (ind < 0) || (ind >= pos))
    {
        std::cout<<"Irregular index or Vector is empty\n"<<std::endl;
        exit(-1);
    }
    return data_[ind];
}
TPL
bool Array<T>::Vector_OK()const
{
    ////////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //////////////////////
    return ((!data_) && (!pos) && (!size_)) || (!((data_ == NULL) || (pos < 0) || (this == NULL) || (size_ < 0) || (pos > size_)));
}
TPL
void Array<T>::Assert_OK()const
{
    if (!Vector_OK())
    {
        Vector_Dump();
        assert(!"Bad object Vector");
    }
}

TPL
bool Array<T>::is_empty()const
{
    return ((pos <= 0) || (size_ <= 0));
}

//__________________________________________________________
TPL
void Array<T>::Vector_Dump()const
{
    if (is_empty())
        std::cout<<"Vector is Empty!\n";
    else
    {
        for (size_t i = 0; i < pos; i++)
            std::cout<<data_[i]<<" data_["<<i<<"] "<<std::endl;
        std::cout<<"Addresses: &data = "<<&data_<<", &this = "<<this<<std::endl;
        std::cout<<"Number of elements = "<<pos<<std::endl;
    }
}

#endif // STL_CVECTOR_H_INCLUDED
